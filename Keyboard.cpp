#pragma once

#include "ofMain.h"
#include "Keyboard.h"


//--------------------------------------------------------------
void Keyboard::setup() {
    // Initialize an empty keyboard (or placeholder frequencies)
    keyWidth = ofGetWidth() / numWhiteKeys;
    keyHeight = ofGetHeight() * 0.4;

    whitePressed.assign(numWhiteKeys, false);
    blackPressed.assign(numWhiteKeys, false);
}

//--------------------------------------------------------------
void Keyboard::draw() {
    // Nothing to draw for now
}

//--------------------------------------------------------------
float Keyboard::get_frequency(int key) {
    // Return a valid frequency if key exists, otherwise 0
    if (key >= 0 && key < keyList.size()) {
        return keyList[key];
    }
    return 0.0f;
}

//--------------------------------------------------------------
void Keyboard::keyPressed(int key) {
    // Ensure vector is large enough
    if (key >= keyList.size()) {
        keyList.resize(key + 1, 0.0f);
    }

    // Assign a dummy frequency (example: MIDI-style mapping)
    keyList[key] = 440.0f;
}

//--------------------------------------------------------------
void Keyboard::keyReleased(int key) {
    if (key >= 0 && key < keyList.size()) {
        keyList[key] = 0.0f;
    }
}

