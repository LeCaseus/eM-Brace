// --- eMFilters.h ---
#pragma once

// --- filter structure + function ---
struct Biquad {
  float b0, b1, b2, a1, a2;
  float z1, z2;
};

inline float process(Biquad &f, float x) {
  float y = f.b0 * x + f.z1;
  f.z1 = f.b1 * x - f.a1 * y + f.z2;
  f.z2 = f.b2 * x - f.a2 * y;
  return y;
}

// --- Bandpass biquad coefficients (Fs = 600 Hz) ---
inline Biquad bp1 = { 0.3913, 0.7827, 0.3913, 0.5768, 0.2619,  0, 0 };
inline Biquad bp2 = { 1.0000, -2.0000, 1.0000, -1.7050, 0.7477,  0, 0 };

// --- Notch biquad coefficients (Fs = 600 Hz) ---
inline Biquad notch = { 0.9896, -1.7142, 0.9896, -1.7142, 0.9793,  0, 0 };

// --- Moving Average ---
const int AVG_SAMPLES = 300;
inline int avgIndex = 0;

inline float addToMovingAverage(float avgArray[], float newValue) {
  avgArray[avgIndex] = newValue;
  avgIndex = (avgIndex + 1) % AVG_SAMPLES;
  
  float sum = 0;
  for (int i = 0; i < AVG_SAMPLES; i++) {
    sum += avgArray[i];
  }
  
  return sum / AVG_SAMPLES;
}