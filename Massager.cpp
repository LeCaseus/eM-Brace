// --- Massager.cpp ---
#include "Managers.h"

void manageMassager(unsigned long currentMillis, float emgValue, float pressure_kPa) {
  if (triggerCalibration && !isRunning && !isAlarming && !calibrating) {
    calibrating = true;
    triggerCalibration = false;
    calibStart = currentMillis;
    calibSum = 0;
    calibCount = 0;
    lastMassageTime = currentMillis;
    splintStatus = "Calibration started (post-alarm)";
  }

  // --- Calibration start ---
  if (!isRunning && !isAlarming && !calibrating &&
      currentMillis - lastMassageTime >= MASSAGE_INTERVAL &&
      (pressure_kPa >= PRESSURE_UPPER || myStepper.distanceToGo() == 0) &&
      myStepper.currentPosition() != 0) {
      
    calibrating = true;
    calibStart = currentMillis;
    calibSum = 0;
    calibCount = 0;
    splintStatus = "Calibration started";
  }

  if (calibrating) {
    calibSum += emgValue;
    calibCount++;
    if (currentMillis - calibStart >= 10000) {
      float baseline = calibSum / calibCount;
      dynamicThreshold = max(baseline * 2.0, 10.0);
      calibrating = false;
      startTime = currentMillis;
      isRunning = true;
      lastMassageTime = currentMillis;

      splintStatus = "calibration complete"; 
      // Serial.print("Calibration complete. Baseline = ");
      // Serial.print(baseline, 4);
      // Serial.print(" µV, Threshold = ");
      // Serial.println(dynamicThreshold, 4);
      // Serial.println("Massager activated");
    }
  }

  // --- Massage control ---
  if (isRunning) {
    if (currentMillis - startTime >= MASSAGE_DURATION) {
      isRunning = false;
      lastMassageTime = currentMillis;
      analogWrite(MOTOR_PIN, 0);
      splintStatus = "Massage Ended";
    } else {
      analogWrite(MOTOR_PIN, 150);
      splintStatus = "Massage Active";
    }
  } else {
    analogWrite(MOTOR_PIN, 0);
  }

  // --- Alarm interupt ---
  if (isRunning) {
    if (emgValue > dynamicThreshold) {
      if (aboveThresholdStart == 0) {
        aboveThresholdStart = currentMillis;
      } else if (currentMillis - aboveThresholdStart >= 3000) { // 3s debounce
        isAlarming = true;
        isRunning = false;
        alarmStartTime = currentMillis;
        aboveThresholdStart = 0;
        analogWrite(MOTOR_PIN, 0);
        alarmFromMassage = true;
        splintStatus = "Alarm triggered during massage";

      }
    } else {
      aboveThresholdStart = 0;
    }
  }
}