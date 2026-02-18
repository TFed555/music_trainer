#include "oscillator.h"
#include <cmath>

float Oscillator::sine() {
    double val = std::sin(phase);
    phase += 2.0 * M_PI * frequency / sampleRate;
    return static_cast<float>(val);
}
