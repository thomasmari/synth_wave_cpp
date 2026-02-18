#include "Keyboard.h"

//--------------------------------------------------------------
void Keyboard::setup() {
    // Initialize an empty keyboard (or placeholder frequencies)
    keyList.clear();
}

//--------------------------------------------------------------
void Keyboard::draw() {
    // Nothing to draw for now
}

//--------------------------------------------------------------
float Keyboard::get_frequency(int key) {
    // Return a valid frequency if key exists, otherwise 0
	// Generate a random number between 0 and 100
	// int randomNum = rand() % 101;
    return 220.0f ; // Add a random offset to the base frequency
    // return 220.0f + randomNum * 10.0f; // Add a random offset to the base frequency
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