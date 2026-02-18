#include "ofMain.h"
#include "ofApp.h"
#include "Keyboard.h"

Keyboard::Keyboard(){}

//--------------------------------------------------------------
void Keyboard::setup(ofApp* inParent) 
{
    parent = inParent;
    keyWidth = ofGetWidth() / kNumWhiteKeys;
    keyHeight = ofGetHeight() * 0.4;

    for (int i = 0; i < kNumWhiteKeys; i++) {
        whitePressed[i] = false;
    }

    for (int i = 0; i < kNumBlackKeys; i++) {
        blackPressed[i] = false;
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
	int offset =0;
    for (int i = 0; i < kNumBlackKeys; i++) {
        if  ((i  == 2)  || (i  == 5)) {
			offset +=1;
		}

        float x = offset * keyWidth + keyWidth * 0.75;

        if (blackPressed[i])
            ofSetColor(255, 255, 0);     //Yellow
        else
            ofSetColor(0);     // Black        

        ofDrawRectangle(x, 0, keyWidth * 0.5, keyHeight * 0.6);
        offset++;
    }
}

//--------------------------------------------------------------
float Keyboard::get_frequency(int key) {
    auto it = keys_to_freq.find(static_cast<char>(key));
    if (it != keys_to_freq.end()) {
        return it->second;
    }
    return 0.0f;
}


//--------------------------------------------------------------
void Keyboard::keyPressed(int key) {
	// if key is found in the keyboard mapping, we set the corresponding key as pressed and we call parent->noteStart with the corresponding frequency. If the key is not found, we do nothing (no sound should be played).
	// retriev the set of key in the keyboard mapping and check if the pressed key is in this set. If it is, we set the corresponding key as pressed and we call parent->noteStart with the corresponding frequency. If the key is not found, we do nothing (no sound should be played).
	if (keys_to_freq.find(static_cast<char>(key)) != keys_to_freq.end()) {
		// Key is found in the mapping
		float frequency = keys_to_freq.at(static_cast<char>(key));
		// Update the pressed state of the key
		for (int i = 0; i < kNumWhiteKeys; i++) {
			if (key == whiteMap[i]) {
				whitePressed[i] = true;
			}
		}
		for (int i = 0; i < kNumBlackKeys; i++) {
			if (key == blackMap[i]) {
				blackPressed[i] = true;
			}
		}
		parent->noteStart(key, frequency); // Notify the parent app about the note start
	}
	else {
		// Key is not found in the mapping, do nothing
	}
}

//--------------------------------------------------------------
void Keyboard::keyReleased(int key) {
	if (keys_to_freq.find(static_cast<char>(key)) != keys_to_freq.end()) {
		// Key is found in the mapping
		// Update the pressed state of the key
		for (int i = 0; i < kNumWhiteKeys; i++) {
			if (key == whiteMap[i]) {
				whitePressed[i] = false;
			}
		}
		for (int i = 0; i < kNumBlackKeys; i++) {
			if (key == blackMap[i]) {
				blackPressed[i] = false;
			}
		}
    	parent->noteEnd(key);
	}
	else {
		// Key is not found in the mapping, do nothing
	}

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

