#pragma once

class ofApp;

class Keyboard
{
        static constexpr int kNumWhiteKeys = 10;
        static constexpr int kNumBlackKeys = 7; 

        public:
                Keyboard();

                // Method
                void setup(ofApp* inParent);
                void draw();
                float get_frequency (int key);
                void keyPressed(int key);
                void keyReleased(int key);

                // Attributes
                float freqListWhite[kNumWhiteKeys];
                float freqListBlack[kNumBlackKeys];
                bool whitePressed[kNumWhiteKeys];
                bool blackPressed[kNumBlackKeys];

                const char whiteMap[kNumWhiteKeys] = {'q','s','d','f','g','h','j','k','l','m'};
                const char blackMap[kNumBlackKeys] = {'z','e','t','y','u','o','p'};

                float keyWidth;
                float keyHeight;

                ofApp* parent;

};
