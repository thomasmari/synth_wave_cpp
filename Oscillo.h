#pragma once

#include "ofMain.h"

class Oscillo : public ofBaseApp{

	public:
		// Methods
		void setup();
		void audioOut(ofSoundBuffer & buffer);
		float get_sample(float sampleRate);
		float get_frequency();
		float get_gain();
		string get_mode();
		int get_key();
		int get_brillance();
		void set_mode(string mode);
		void set_brillance(int brillance);
		void set_gain(float gain);
		void set_frequency(float frequency);
		void set_key(int key);
		void start();
		void stop();  
		bool is_active();	
		
	private:
		// Attributes
		float frequency;
		string mode;
		int brillance;
		float gain;
		float phase;
		int key;
		bool active;

};
