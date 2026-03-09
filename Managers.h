// --- Managers.h ---
#pragma once
#include <Arduino.h>
#include <AccelStepper.h>

// --- Pin Definitions ---
const int MOTOR_PIN = 0;       // Massager (N20 Motor)

// Splint driver (DRV8825)
#define STEP_PIN 32   
#define DIR_PIN 33    
#define ENABLE_PIN 21 

// Microstepping control
#define M0_PIN 26    
#define M1_PIN 27    
#define M2_PIN 14    

// Alarm system
#define BUZZER 4   
#define LED 22     

// --- System Constants ---
const float PRESSURE_UPPER = 4.3;
const float PRESSURE_LOWER = 4.3;
const int STEPPER_SPEED = 500;
const float EMG_THRESHOLD = 10.0;

// --- Timeouts & Intervals (ms) ---
const unsigned long MASSAGE_DURATION     = 150000;  // 150s
const unsigned long MASSAGE_INTERVAL     = 60000;   // 60s (previously 30s)
const unsigned long STATE_DEBOUNCE       = 3000;    // 3s
const unsigned long ALARM_DURATION       = 9000;    // 9s
const unsigned long ALARM_BLINK_INTERVAL = 1000;    // 1s

// --- Splint states ---
enum SplintState { HOLD, LOOSENING, TIGHTENING };

// ---- Extern variables (defined once in Managers.cpp) ----
extern SplintState currentSplintState;
extern SplintState lastEvaluatedState;
extern SplintState proposedState;

extern AccelStepper myStepper;

extern bool isRunning;
extern bool isAlarming;
extern bool alarmState;

extern float dynamicThreshold;
extern unsigned long aboveThresholdStart;
extern unsigned long aboveThresholdStart1;

extern String splintStatus;

// Timing
extern unsigned long stateChangeStartTime;
extern unsigned long startTime;
extern unsigned long lastMassageTime;
extern unsigned long alarmStartTime;
extern unsigned long lastBlinkTime;
extern unsigned long restDelayStart;

// Calibration
extern bool calibrating;
extern unsigned long calibStart;
extern float calibSum;
extern int calibCount;

// Sensor readings
extern float filteredEMG;
extern float emgreading;
extern float fsrreading;
extern float EMAFSR;
extern float EMAEMG;

// Post-alarm recovery state
extern bool LoosenDuringAlarm;
extern bool hasAlarmOccurred;
extern unsigned long postAlarmRestStart;
extern bool postAlarmTightening;
extern bool restConfirmed;
extern bool triggerCalibration;
extern bool alarmFromMassage;

// --- Function Prototypes ---
void manageSplint(unsigned long currentMillis, float emgValue, float pressure_kPa);
void manageMassager(unsigned long currentMillis, float emgValue, float pressure_kPa);
void manageAlarm(unsigned long currentMillis, float pressure_kPa);