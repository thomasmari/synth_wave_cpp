#include "ofMain.h"
#include "Oscillo.h"
#include <string>
#include <cmath>

using std::string;

void Oscillo::setup(){
	frequency = 440.0f;    
        gain = 0.0f;  // start with no sound         
        mode = "square";       
        brillance = 10;
		phase = 0.0f;
}


// --------------- getter ---------------------

float Oscillo::get_frequency(){
	return frequency;
}

float Oscillo::get_gain(){
	return gain;
}

string Oscillo::get_mode(){
	return mode;
}

int Oscillo::get_brillance(){
	return brillance;
}


// ---------------------- setters ---------------------

void Oscillo::set_frequency(float f){
	if (f>0){
		frequency = f;
	}
}

void Oscillo::set_gain(float g) { 
	if (g >= 0 && g <= 1){
		gain = g;
	}  
}

void Oscillo::set_mode(string m) { 
	if (m == "square" || m == "saw" || m == "sinus" || m == "piano") {
		mode = m;
	}
}


void Oscillo::set_brillance(int b) { 
	if (b > 0){
		brillance = b; 
	} 
}


// ------------- fonction ppales -----------

void Oscillo::stop() {
    gain = 0.0f;
}


void Oscillo::audioOut(ofSoundBuffer & buffer) {
    int buffer_size = buffer.getNumFrames(); // taille du buffer // assuming mono not stereo
    if (mode == "square") {
        for (int n=0; n<buffer_size; n++) {
            // define sample  
            float sample = 0.0f;  // va stocker le sample final
            float factor = 4.0f / M_PI;   // facteur global pour onde carrée
            for (int k = 0; k < brillance; k++) {
                int h = 2 * k + 1;  // seuls les harmoniques impaires
                sample += sin(h * phase) / h;
            }
            sample *= factor * gain;
            // set sample for both channels (stereo)
			buffer[n*buffer.getNumChannels()] = sample; //left channel
			buffer[n*buffer.getNumChannels() + 1] = sample; //right channel
            // incrémenter la phase pour avancer dans l’onde
            phase += 2.0f * M_PI * frequency / 44100.0f;    
        }

    }
    else if (mode == "saw") {
                for (int n=0; n<buffer_size; n++) {
            // define sample
            float sample = 0.0f;  // va stocker le sample final  
            float factor = 2.0f / M_PI;   // facteur global pour dent de scie
            for (int k = 1; k <= brillance; k++) {
                float sign = (k % 2 == 0) ? -1.0f : 1.0f;
                sample += sign * sin(k * phase) / k;
            }
            sample *= factor * gain;
            // set sample for both channels (stereo)
			buffer[n*buffer.getNumChannels()] = sample; //left channel
			buffer[n*buffer.getNumChannels() + 1] = sample; //right channel
            // incrémenter la phase pour avancer dans l’onde
            phase += 2.0f * M_PI * frequency / 44100.0f;    
        }
    }
    else if (mode == "sinus") {
        for (int n=0; n<buffer_size; n++) {
            // define sample 
            float sample = sin(phase);
            sample *= gain;
            // set sample for both channels (stereo)
			buffer[n*buffer.getNumChannels()] = sample; //left channel
			buffer[n*buffer.getNumChannels() + 1] = sample; //right channel
            // incrémenter la phase pour avancer dans l’onde
            phase += 2.0f * M_PI * frequency / 44100.0f;
			if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI;
    
	}
	
	}
	else if (mode == "piano") {
    for (int n=0; n<buffer_size; n++) {
        // Attack / decay simulée
        float env = 1.0f; // enveloppe par défaut
        if (gain > 0.0f) {
            env = exp(-phase / (44100.0f * 0.3)); // décroissance exponentielle ~0.3s
        }

        // Harmoniques pour enrichir le son
        float sample = 0.0f;
        for (int k = 1; k <= brillance; k++) {
            float sign = (k % 2 == 0) ? -1.0f : 1.0f;
            sample += sign * sin(k * phase) / k;
        }
        sample *= (2.0f / M_PI) * gain * env;

        buffer[n*buffer.getNumChannels()] = sample; // left
        buffer[n*buffer.getNumChannels()+1] = sample; // right

        // incrémenter phase
        phase += 2.0f * M_PI * frequency / 44100.0f;
        if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI;
    }
}

}
