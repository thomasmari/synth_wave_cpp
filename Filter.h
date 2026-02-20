#pragma once
#include "ofMain.h"

class Filter
{
        float targetFrequency;
        float gain;
        float qualityFactor;
        float omega0;
        float alpha;
        public:                
        // Method
        void setup();
        void draw();
        void audioOut(ofSoundBuffer & buffer);
        void setQuality(float & quality);
        void setFrequency(float & frequency);
        void setGain(float & g);
        void setActive(bool & active);
        bool isActive();
        // Attributes
        bool active;
        float b0, b1, b2, a0, a1, a2;
        float x1, x2, y1, y2; // for filter state       
};
