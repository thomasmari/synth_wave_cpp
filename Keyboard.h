#pragma once

#include "ofMain.h"

class Keyboard : public ofBaseApp {

	public:
		// Method
		void setup();
		void draw();
		float get_frequency (int key);
		void keyPressed(int key);
		void keyReleased(int key);
		// Attributes
		vector <float> keyList;
};
