#include "Filter.h"


//--------------------------------------------------------------
void Filter::setup() 
{  
    active = false;
    targetFrequency = 1000.0f; // default frequency
    gain = 0.0f; // default gain
    qualityFactor = 1.0f; // default quality factor
    x1 = x2 = y1 = y2 = 0.0f;   
}

//--------------------------------------------------------------
void Filter::draw() {
// nothing for now
}
//--------------------------------------------------------------
void Filter::audioOut(ofSoundBuffer & buffer) {
    // IIR filter implementation
    if (!active) return; // If filter is not active, do nothing
    omega0 = 2.0f * M_PI * targetFrequency / 44100.0f;
    alpha = tanf(omega0 / 2.0f * qualityFactor);
    b0 = alpha;
    b1 = 0.0f;
    b2 = -alpha;
    a0 = 1.0f + alpha;
    a1 = -2.0f * cos(omega0);
    a2 = 1.0f - alpha;
    for (size_t i = 0; i < buffer.size(); i++) {
        float input = buffer[i];
        float output = (b0/a0) * input + (b1/a0) * x1 + (b2/a0) * x2 - (a1/a0) * y1 - (a2/a0) * y2;
        buffer[i] = output;
        x2 = x1;
        x1 = input;
        y2 = y1;
        y1 = output;
    }
}
void Filter::setQuality(float & quality) {
    qualityFactor = quality;
}   
void Filter::setFrequency(float & frequency) {
    targetFrequency = frequency;
}
void Filter::setGain(float & g) {
    gain = g;
}
void Filter::setActive(bool & a) {
    active = a;
}
bool Filter::isActive() {
    return active;
}   
