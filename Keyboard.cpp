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
    freqListWhite.assign(numWhiteKeys, 440);
    freqListBlack.assign(7, 440);
}

//--------------------------------------------------------------
void Keyboard::draw() {

     // White Keys
    for (int i = 0; i < numWhiteKeys; i++) {
        if (whitePressed[i])
            ofSetColor(255, 255, 0);    //Yellow
        else
            ofSetColor(255);        //White   

        ofDrawRectangle(i * keyWidth, 0, keyWidth, keyHeight);

        ofSetColor(0);  //Black               
        ofNoFill();
        ofDrawRectangle(i * keyWidth, 0, keyWidth, keyHeight);
        ofFill();
    }

    // Black keys
    int blackIndex = 0;
    for (int i = 0; i < numWhiteKeys; i++) {
        
        bool skip = (i % numWhiteKeys == 2) || (i % numWhiteKeys == 6);
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

    float currentFreq = 0;

    // White
    for (int i = 0; i < whiteMap.size(); i++) {
        if (key == whiteMap[i]) {
            whitePressed[i] = true;
            currentFreq = freqListWhite[i];
        }
    }

    // Black
    for (int i = 0; i < blackMap.size(); i++) {
        if (key == blackMap[i]) {
            blackPressed[i] = true;
            currentFreq = freqListBlack[i]; 
        }
    }
    return currentFreq; 
}

//--------------------------------------------------------------
void Keyboard::keyPressed(int key) {
    // Ensure vector is large enough
    if (key >= keyList.size()) {
        keyList.resize(key + 1, 0.0f);
    }

    // Assign a dummy frequency (example: MIDI-style mapping)
    keyList[key] = 440.0f;

    // parent->newNotePressed(key, frequency)
}

//--------------------------------------------------------------
void Keyboard::keyReleased(int key) {
    if (key >= 0 && key < keyList.size()) {
        keyList[key] = 0.0f;
    }

    // parent->noteReleased(key)
}

