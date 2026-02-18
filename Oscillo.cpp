#pragma once
#include "ofMain.h"
#include <string>
#include <cmath>

using std::string;

void Oscillo::setup(){
	frequency = 440.0f;    
        gain = 0.5f;           
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
	if (m == "square" || m == "saw") mode = m; 
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


float Oscillo::audioOut() {
    float sample = 0.0f;  // va stocker le sample final

    if (mode == "square") {
        float factor = 4.0f / M_PI;   // facteur global pour onde carrée
        for (int k = 0; k < brillance; k++) {
            int n = 2 * k + 1;  // seuls les harmoniques impaires
            sample += sin(n * phase) / n;
        }
        sample *= factor * gain;
    }
    else if (mode == "saw") {
        float factor = 2.0f / M_PI;   // facteur global pour dent de scie
        for (int k = 1; k <= brillance; k++) {
            float sign = (k % 2 == 0) ? -1.0f : 1.0f;
            sample += sign * sin(k * phase) / k;
        }
        sample *= factor * gain;
    }

    // incrémenter la phase pour avancer dans l’onde
    phase += 2.0f * M_PI * frequency / 44100.0f; 
	// permey de remettre la phase dans 0 2pi
    if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI; 
    return sample;
}
