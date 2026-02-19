#pragma once

#include "ofMain.h"

class Oscillo : public ofBaseApp{

	public:
		// Methods
		void setup();
		void audioOut(ofSoundBuffer & buffer);
		float get_frequency();
		float get_gain();
		string get_mode();
		int get_brillance();
		void set_mode(string mode);
		void set_brillance(int brillance);
		void set_gain(float gain);
		void set_frequency(float frequency);
		void stop(); // mettre le volume a zero 	
		
	private:
		// Attributes
		float frequency;
		string mode;
		int brillance;
		float gain;
		float phase;
		float note_gain; // amplitude courante de la note
		float elapsed;
		// tentative pour diminuer le son de la note comme un "piano"
		float env;           // valeur actuelle de l’enveloppe
		float decayRate;     // vitesse de décroissance
		bool noteOn; 

};
