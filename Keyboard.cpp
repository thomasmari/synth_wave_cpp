#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "Keyboard.h"

Keyboard::Keyboard(){}

//--------------------------------------------------------------
void Keyboard::setup(ofApp* inParent) 
{
    parent = inParent;

    // Initialize an empty keyboard (or placeholder frequencies)
    keyWidth = ofGetWidth() / kNumWhiteKeys;
    keyHeight = ofGetHeight() * 0.4;

    for (int i = 0; i < kNumWhiteKeys; i++) {
        whitePressed[i] = false;
    }

    for (int i = 0; i < kNumWhiteKeys - 1; i++) {
        blackPressed[i] = false;
    }

    for (int i = 0; i < kNumWhiteKeys; i++) {
        freqListWhite[i] = 440;
    }

    for (int i = 0; i < kNumBlackKeys - 1; i++) {
        freqListBlack[i] = 440;
    }

}

//--------------------------------------------------------------
void Keyboard::draw() {

     // White Keys
    for (int i = 0; i < kNumWhiteKeys; i++) {
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
    for (int i = 0; i < kNumWhiteKeys; i++) {
        
        bool skip = (i % kNumWhiteKeys == 2) || (i % kNumWhiteKeys == 6);
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
    for (int i = 0; i < kNumWhiteKeys; i++) {
        if (key == whiteMap[i]) {
            whitePressed[i] = true;
            currentFreq = freqListWhite[i];
        }
    }

    // Black
    for (int i = 0; i < kNumBlackKeys; i++) {
        if (key == blackMap[i]) {
            blackPressed[i] = true;
            currentFreq = freqListBlack[i]; 
        }
    }
    return currentFreq; 
}

//--------------------------------------------------------------
void Keyboard::keyPressed(int key) {

    float currentFreq = 0;

    // White
    for (int i = 0; i < kNumWhiteKeys; i++) {
        if (key == whiteMap[i]) {
            whitePressed[i] = true;
            currentFreq = freqListWhite[i];
        }
    }

    // Black
    for (int i = 0; i < kNumBlackKeys; i++) {
        if (key == blackMap[i]) {
            blackPressed[i] = true;
            currentFreq = freqListBlack[i]; 
        }
    }

    parent->noteStart(key, currentFreq);
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

