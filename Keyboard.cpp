#include "ofMain.h"
#include "ofApp.h"
#include "Keyboard.h"

Keyboard::Keyboard(){}

//--------------------------------------------------------------
void Keyboard::setup(ofApp* inParent) 
{
    parent = inParent;
	// White keys frequencies from A3 to B4
	// White keys: C3 D3 E3 F3 G3 A3 B3 C4 D4 E4
	const float WHITE_KEY_FREQUENCIES[] = {
		130.81f, // C3
		146.83f, // D3
		164.81f, // E3
		174.61f, // F3
		196.00f, // G3
		220.00f, // A3
		246.94f, // B3
		261.63f, // C4
		293.66f, // D4
		329.63f  // E4
	};
const int WHITE_KEY_COUNT = 10;

	// Black keys: C#3 D#3 F#3 G#3 A#3 C#4 D#4
	const float BLACK_KEY_FREQUENCIES[] = {
		138.59f, // C#3 / Db3
		155.56f, // D#3 / Eb3
		185.00f, // F#3 / Gb3
		207.65f, // G#3 / Ab3
		233.08f, // A#3 / Bb3
		277.18f, // C#4 / Db4
		311.13f  // D#4 / Eb4
	};

	const int BLACK_KEY_COUNT = 7;

	// std::map<char, float> keys_to_freq = {
	// 	{'q', 130.81f}, // C3
	// 	{'s', 146.83f}, // D3
	// 	{'d', 164.81f}, // E3
	// 	{'f', 174.61f}, // F3
	// 	{'g', 196.00f}, // G3
	// 	{'h', 220.00f}, // A3
	// 	{'j', 246.94f}, // B3
	// 	{'k', 261.63f}, // C4
	// 	{'l', 293.66f},  // D4
	// 	{'z', 138.59f}, // C#3 / Db3
	// 	{'e', 155.56f}, // D#3 / Eb3
	// 	{'t', 185.00f}, // F#3 / Gb3
	// 	{'y', 207.65f}, // G#3 / Ab3
	// 	{'u', 233.08f}, // A#3 / Bb3
	// 	{'o', 277.18f}, // C#4 / Db4
	// 	{'p', 311.13f}  // D#4 / Eb4
	// 	};	
    // Initialize an empty keyboard (or placeholder frequencies)
    keyWidth = ofGetWidth() / kNumWhiteKeys;
    keyHeight = ofGetHeight() * 0.4;

    for (int i = 0; i < kNumWhiteKeys; i++) {
        whitePressed[i] = false;
    }

    for (int i = 0; i < kNumWhiteKeys; i++) {
        blackPressed[i] = false;
    }

    for (int i = 0; i < kNumWhiteKeys; i++) {
        freqListWhite[i] = WHITE_KEY_FREQUENCIES[i];
    }

    for (int i = 0; i < kNumBlackKeys; i++) {
        freqListBlack[i] = BLACK_KEY_FREQUENCIES[i];
    }

}

//--------------------------------------------------------------
void Keyboard::draw() {

     // White Keys
    for (int i = 0; i < kNumWhiteKeys; i++) {

        if (whitePressed[i])
            ofSetColor(255, 255, 0, 255);    //Yellow
        else
            ofSetColor(255, 255, 255, 255);        //White   

        ofDrawRectangle(i * keyWidth, 0, keyWidth, keyHeight);
        ofSetColor(0);  //Black               
        ofNoFill();
        ofDrawRectangle(i * keyWidth, 0, keyWidth, keyHeight);
        ofFill();
    }

    // Black keys
    int blackIndex = 0;
    for (int i = 0; i < kNumWhiteKeys; i++) {
        
        bool skip = (i  == 2) || (i  == 6) || (i == 9);
        if (skip) continue;

        float x = i * keyWidth + keyWidth * 0.75;

        if (blackPressed[blackIndex])
            ofSetColor(255, 255, 0);     //Yellow
        else
            ofSetColor(0);     // Black        

        ofDrawRectangle(x, 0, keyWidth * 0.5, keyHeight * 0.6);
        blackIndex++;
    }
}

//--------------------------------------------------------------
float Keyboard::get_frequency(int key) {

    float currentFreq = 0.0f; // default frequency if key not found, should not happen
	if (keys_to_freq.find(key) != keys_to_freq.end()) {
		return keys_to_freq[key];
	}
	else {
		return currentFreq;
	}
}

//--------------------------------------------------------------
void Keyboard::keyPressed(int key) {
	// if key is found in the keyboard mapping, we set the corresponding key as pressed and we call parent->noteStart with the corresponding frequency. If the key is not found, we do nothing (no sound should be played).
	bool keyFound = false;
	float currentFreq = 5000.0f; // default frequency if key not found, should not happen
    // White

    for (int i = 0; i < kNumWhiteKeys; i++) {
        if (key == whiteMap[i]) {
            whitePressed[i] = true;
            float currentFreq = freqListWhite[i];
            keyFound = true;
        }
    }

    // Black
    for (int i = 0; i < kNumBlackKeys; i++) {
        if (key == blackMap[i]) {
            blackPressed[i] = true;
            float currentFreq = freqListBlack[i];
			keyFound = true; 
        }
    }
	if (keyFound) {
    	parent->noteStart(key, currentFreq);
	}
}

//--------------------------------------------------------------
void Keyboard::keyReleased(int key) {

    // White
    for (int i = 0; i < kNumWhiteKeys; i++) {
        if (key == whiteMap[i]) {
            whitePressed[i] = false;
        }
    }

    // Black
    for (int i = 0; i < kNumBlackKeys; i++) {
        if (key == blackMap[i]) {
            blackPressed[i] = false;
        }
    }
    parent->noteEnd(key);
}

