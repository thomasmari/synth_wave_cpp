#pragma once

class ofApp;

class Keyboard
{
        static constexpr int kNumWhiteKeys = 10;
        static constexpr int kNumBlackKeys = 7; 
		const 	std::map<char, float> keys_to_freq = {
		{'q', 130.81f}, // C3
		{'s', 146.83f}, // D3
		{'d', 164.81f}, // E3
		{'f', 174.61f}, // F3
		{'g', 196.00f}, // G3
		{'h', 220.00f}, // A3
		{'j', 246.94f}, // B3
		{'k', 261.63f}, // C4
		{'l', 293.66f},  // D4
        {'m', 329.63f}, // E4 
		{'z', 138.59f}, // C#3 / Db3
		{'e', 155.56f}, // D#3 / Eb3
		{'t', 185.00f}, // F#3 / Gb3
		{'y', 207.65f}, // G#3 / Ab3
		{'u', 233.08f}, // A#3 / Bb3
		{'o', 277.18f}, // C#4 / Db4
		{'p', 311.13f}  // D#4 / Eb4
		};	
		
        public:
                Keyboard();

                // Method
                void setup(ofApp* inParent);
                void draw();
                float get_frequency (int key);
                void keyPressed(int key);
                void keyReleased(int key);

                // Attributes
                bool whitePressed[kNumWhiteKeys];
                bool blackPressed[kNumBlackKeys];

                const char whiteMap[kNumWhiteKeys] = {'q','s','d','f','g','h','j','k','l','m'};
                const char blackMap[kNumBlackKeys] = {'z','e','t','y','u','o','p'};

                float keyWidth;
                float keyHeight;

                ofApp* parent;

};
