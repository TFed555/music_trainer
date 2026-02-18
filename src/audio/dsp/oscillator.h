#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#pragma once

class Oscillator {
public:
    void setSampleRate(int rate) { sampleRate = rate; };
    void setFrequency(double freq) { frequency = freq; };
    float sine();
private:
    double sampleRate = 44100.0;
    double frequency = 440.0;
    double phase = 0.0;
};

#endif // OSCILLATOR_H
