// --- Managers.cpp ---
#include "Managers.h"

// --- Stepper ---
AccelStepper myStepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// --- Splint states ---
SplintState currentSplintState = HOLD;
SplintState lastEvaluatedState = HOLD;
SplintState proposedState = HOLD;

String splintStatus = "idle";

// --- Flags ---
bool isRunning = false;
bool isAlarming = false;
bool alarmState = false;
bool restConfirmed = false;
bool LoosenDuringAlarm = false;
bool postAlarmTightening = false;
bool triggerCalibration = false;
bool hasAlarmOccurred = false;
bool alarmFromMassage = false;

// --- Threshold ---
float dynamicThreshold = EMG_THRESHOLD;

// --- Timers ---
unsigned long aboveThresholdStart = 0;
unsigned long aboveThresholdStart1 = 0;
unsigned long stateChangeStartTime = 0;
unsigned long startTime = 0;
unsigned long lastMassageTime = 0;
unsigned long alarmStartTime = 0;
unsigned long lastBlinkTime = 0;
unsigned long postAlarmRestStart = 0;
unsigned long restDelayStart = 0;

// --- Calibration ---
bool calibrating = false;
unsigned long calibStart = 0;
float calibSum = 0;
int calibCount = 0;

// --- Sensor readings ---
float filteredEMG = 0.0;
float emgreading = 0.0;
float fsrreading = 0.0;
float EMAFSR = 0;
float EMAEMG = 0;