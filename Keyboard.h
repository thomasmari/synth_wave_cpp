#pragma once

class ofApp;

class Keyboard
{
        static constexpr int kNumWhiteKeys = 10;
        static constexpr int kNumBlackKeys = 7; 
		const std::map<char, float> keys_to_freq = {
		{static_cast <char> ('q'), 130.81f}, // C3
		{static_cast <char> ('s'), 146.83f}, // D3
		{static_cast <char> ('d'), 164.81f}, // E3
		{static_cast <char> ('f'), 174.61f}, // F3
		{static_cast <char> ('g'), 196.00f}, // G3
		{static_cast <char> ('h'), 220.00f}, // A3
		{static_cast <char> ('j'), 246.94f}, // B3
		{static_cast <char> ('k'), 261.63f}, // C4
		{static_cast <char> ('l'), 293.66f},  // D4
        {static_cast <char> ('m'), 329.63f}, // E4 
		{static_cast <char> ('z'), 138.59f}, // C#3 / Db3
		{static_cast <char> ('e'), 155.56f}, // D#3 / Eb3
		{static_cast <char> ('t'), 185.00f}, // F#3 / Gb3
		{static_cast <char> ('y'), 207.65f}, // G#3 / Ab3
		{static_cast <char> ('u'), 233.08f}, // A#3 / Bb3
		{static_cast <char> ('o'), 277.18f}, // C#4 / Db4
		{static_cast <char> ('p'), 311.13f}  // D#4 / Eb4
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
