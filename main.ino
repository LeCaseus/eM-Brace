#include "WebPage.h"
#include "eMFilters.h"
#include "Managers.h"

// --- Buffers ---
float pressureMovingAvg[AVG_SAMPLES] = {0};

void setup() {
  Serial.begin(115200);

  // --- Pins ---
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(M2_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  
  // --- Stepper driver ---
  digitalWrite(M0_PIN, LOW);
  digitalWrite(M1_PIN, LOW);
  digitalWrite(M2_PIN, LOW);
  digitalWrite(ENABLE_PIN, LOW);  // Enable motor driver
  
  myStepper.setPinsInverted(true, false, true);
  myStepper.setMaxSpeed(STEPPER_SPEED);
  myStepper.setAcceleration(500);
  myStepper.setCurrentPosition(0);
  
  // --- Wi-Fi ---
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());

  // --- Web server ---
  server.on("/", [](){ server.send(200,"text/html", htmlPage()); });
  server.on("/data", [](){ 
  String json = "{";
  // json += "\"filtered\":" + String(filteredEMG, 4) + ",";
  json += "\"EMG\":" + String(emgreading, 4) + ",";
  json += "\"threshold\":" + String(dynamicThreshold, 4) + ",";
  json += "\"fsr\":" + String(fsrreading, 4);
  json += ",\"status\":\"" + splintStatus + "\"";
  json += "}";
  server.send(200,"application/json",json);
  });


  server.begin();
}

void loop() {
  server.handleClient(); // handle web requests
  unsigned long currentMillis = millis();
  
  // --- Sensors ---
  float rawEMG = (analogRead(36) * (5.0 / 4095.0));
  float rawFSR = analogRead(34);
  EMAFSR = 0.05 * rawFSR + (1 - 0.05) * EMAFSR;
  float calibFSR = pow(10, 2.658628) * pow(((3.3 * 5100.0) / ((EMAFSR / 4095.0) * 3.3) - 5100.0), -0.432107);

  float y = process(bp1, rawEMG);
  y = process(bp2, y);
  y = process(notch, y);
  filteredEMG = fabs(y);

  float mass_kg = calibFSR / 9.81;
  float area = 0.045 * 0.045;     // FSR area in m²
  float filteredPressure = calibFSR / (area * 1000.0);

  // --- Moving Averages ---
  EMAEMG = 0.05 * filteredEMG + (1 - 0.05) * EMAEMG;
  float pressure_kPa = addToMovingAverage(pressureMovingAvg, filteredPressure);

  // EMG conversion
  float displayGain = 1000.0; // relative
  float filteredEMG_uV = (EMAEMG * 1e6) / displayGain; // convert to uV range

  // --- Systems ---
  manageSplint(currentMillis, filteredEMG_uV, pressure_kPa);
  manageMassager(currentMillis, filteredEMG_uV, pressure_kPa);
  manageAlarm(currentMillis, pressure_kPa);

  // --- Web update ---
  emgreading = filteredEMG_uV;
  fsrreading = pressure_kPa;
  
  Serial.println(emgreading);
  
  // --- Stepper ---
  if (currentSplintState != HOLD) {
    myStepper.run();
  }
}
