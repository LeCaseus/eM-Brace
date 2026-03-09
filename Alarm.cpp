// --- Alarm.cpp ---
#include "Managers.h"
#include <pitches.h>

void manageAlarm(unsigned long currentMillis, float pressure_kPa) {
  if (isAlarming) {
    hasAlarmOccurred = true;
    // --- Active alarm ---
    if (currentMillis - alarmStartTime >= ALARM_DURATION) {
      // End alarm
      isAlarming = false;
      alarmState = false;
      LoosenDuringAlarm = false;   // clear override
      restConfirmed = false;
      digitalWrite(LED, LOW);
      noTone(BUZZER);
      analogWrite(MOTOR_PIN, 0);
      splintStatus = "Alarm ended";
    } else {
      // --- Blinking Phase ---
      if (currentMillis - lastBlinkTime >= ALARM_BLINK_INTERVAL) {
        lastBlinkTime = currentMillis;
        alarmState = !alarmState;
        digitalWrite(LED, alarmState);

        // if (alarmState) {
        //   tone(BUZZER, NOTE_C5);
        // } else {
        //   noTone(BUZZER);
        // }
      }

      // --- Force loosening while alarm is active ---
      if (!LoosenDuringAlarm) {
        LoosenDuringAlarm = true;
        splintStatus = "Alarm active: Splint loosening";
      }
    }
  }

  // --- Post-alarm rest ---
  if (hasAlarmOccurred && !isAlarming && !restConfirmed) {
    if (myStepper.distanceToGo() == 0 && myStepper.currentPosition() == 0) {
      restConfirmed = true;
      restDelayStart = currentMillis;   // start waiting period
    }
  }

  // --- Post-alarm tightening after wait ---
  if (hasAlarmOccurred && restConfirmed && !postAlarmTightening) {
    if (currentMillis - restDelayStart >= 5000) {  // wait 5 seconds
      if (pressure_kPa < PRESSURE_LOWER) {
        digitalWrite(ENABLE_PIN, LOW);
        myStepper.stop();
        myStepper.moveTo(2750);
        currentSplintState = TIGHTENING;
        postAlarmTightening = true;
        splintStatus = "Post-alarm: Splint tightening resumed after delay";
      }
    }
  }

  // --- Post-alarm massage calibration ---
  if (hasAlarmOccurred && alarmFromMassage &&
      postAlarmTightening && myStepper.distanceToGo() == 0 &&
      (pressure_kPa >= PRESSURE_UPPER || myStepper.currentPosition() == 2750) &&
      !isRunning && !calibrating) {
    triggerCalibration = true;  // new global flag
    postAlarmTightening = false;
    lastMassageTime = currentMillis;
    splintStatus = "Post-alarm: Calibration queued";
  }

  // --- Global alarm cleanup ---
  if (hasAlarmOccurred && !isAlarming && postAlarmTightening && myStepper.distanceToGo() == 0) {
    hasAlarmOccurred = false;
    alarmFromMassage = false;
    splintStatus = "Alarm cycle complete";
  }

}