#pragma once

#include "ofMain.h"

class ofApp;

class Keyboard
{
        static constexpr int kNumWhiteKeys = 10;
        static constexpr int kNumBlackKeys = 7; 

        public:
                Keyboard(ofApp* parent);

                // Method
                void setup();
                void draw();
                float get_frequency (int key);
                void keyPressed(int key);
                void keyReleased(int key);

                // Attributes
                float freqListWhite[kNumWhiteKeys];
                float freqListBlack[kNumBlackKeys];
                bool whitePressed[kNumWhiteKeys];
                bool blackPressed[kNumBlackKeys];

                const char whiteMap = {'q','s','d','f','g','h','j','k','l'};
                const char blackMap = {'z','e','t','y','u','o','p'};

                float keyWidth;
                float keyHeight;

                ofApp* parent;

};
