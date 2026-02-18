#pragma once

#include "ofMain.h"

class Keyboard{

        public:
                // Method
                void setup();
                void draw();
                float get_frequency (int key);
                void keyPressed(int key);
                void keyReleased(int key);

                // Attributes
                vector <float> keyList;
                vector<bool> whitePressed;
        vector<bool> blackPressed;
                vector<int> whiteMap = {'q','s','d','f','g','h','j','k','l'};
                vector<int> blackMap = {'z','e','t','y','u','o','p'};

                int numWhiteKeys = 10;
                float keyWidth;
                float keyHeight;

};
