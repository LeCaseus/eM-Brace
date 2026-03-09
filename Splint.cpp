// --- Splint.cpp ---
#include "Managers.h"
#include <AccelStepper.h>

void manageSplint(unsigned long currentMillis, float emgValue, float pressure_kPa) {
  // --- Alarm override check ---
  if (LoosenDuringAlarm) {
    if (currentSplintState != LOOSENING) {
      digitalWrite(ENABLE_PIN, LOW);
      myStepper.stop();
      myStepper.moveTo(-1);
      currentSplintState = LOOSENING;
      splintStatus = "Alarm override: Splint loosening";
    }
    return;
  }

  if (!isRunning && !isAlarming && !calibrating && !LoosenDuringAlarm && 
    emgValue > dynamicThreshold) {
    if (aboveThresholdStart1 == 0) {
      aboveThresholdStart1 = currentMillis;
    } else if (currentMillis - aboveThresholdStart1 >= 3000) {  // same debounce time
      isAlarming = true;
      alarmStartTime = currentMillis;
      aboveThresholdStart1 = 0;
      alarmFromMassage = false;
      splintStatus = "Alarm triggered outside massage";

    }
  } else {
    aboveThresholdStart1 = 0;
  }

  // --- Safety: stop if pressure is too high ---
  if (pressure_kPa >= PRESSURE_UPPER && !LoosenDuringAlarm) {
    if (currentSplintState != HOLD) {
      myStepper.stop();
      currentSplintState = HOLD;
      splintStatus = "Pressure threshold reached: Holding position";
    }
  }
  
  // --- Determine target state based on EMG ---
  proposedState = HOLD;
  if (emgValue > dynamicThreshold) {
    proposedState = LOOSENING;
  } 
  else if (emgValue <= dynamicThreshold && pressure_kPa < PRESSURE_UPPER) {
    proposedState = TIGHTENING;
  }

  // --- Debounce state changes ---
  if (proposedState != lastEvaluatedState) {
    lastEvaluatedState = proposedState;
    stateChangeStartTime = currentMillis;
  }
  
  if (currentMillis - stateChangeStartTime >= STATE_DEBOUNCE && 
      currentSplintState != proposedState) {
    
    digitalWrite(ENABLE_PIN, LOW);
    myStepper.stop();
    
    if (proposedState == LOOSENING) {
      myStepper.moveTo(-1);
      splintStatus = "Splint Loosening";
    } else if (proposedState == TIGHTENING) {
      myStepper.moveTo(2750);
      splintStatus = "Splint Tightening";
    }

    currentSplintState = proposedState;
  }
}