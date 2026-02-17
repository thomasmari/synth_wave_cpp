#pragma once

#include "ofMain.h"

class Keyboard : public ofBaseApp {

	public:
		// Method
		void setup();
		void draw();
		float get_frequency (int key);
		// Attributes
		vector <float> keyList;
};
