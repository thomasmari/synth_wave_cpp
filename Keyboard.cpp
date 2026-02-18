#pragma once

#include "ofMain.h"

void Keyboard::setup(){
    keyWidth = ofGetWidth() / numWhiteKeys;
    keyHeight = ofGetHeight() * 0.4;

    whitePressed.assign(numWhiteKeys, false);
    blackPressed.assign(numWhiteKeys, false);


}

void draw(){

    for (unsigned i=0; i < whiteMap.size(); i++){
        if whitePressed[i]{

        }
    }

}

float get_frequency (int key);
void keyPressed(int key);
void keyReleased(int key);

