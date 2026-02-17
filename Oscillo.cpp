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

float Oscillo::stop() {
    gain = 0.0f;
}


float Oscillo::audioOut(){
	float sample = 0.0f; // va stocker sample final
	// n = nb harmonique qu'on prend = la brillance (on stop a la brillance)
	for (int n=1; n <= brillance;n++){
		float amplitude = 1.0f / n;
		// pour la synthese "carre" on doit sauter tous les harminique paire
		if (mode == "square" && n % 2 == 0) continue;
		// ajoute l'harmonique à l'échnatillon
        sample += amplitude * sin(n * phase);
	}
	// multiplie le son par le volume 
	sample *= gain;

	// incrémenter la phase pour avancer dans l’onde
    phase += 2.0f * M_PI * frequency / 44100.0f; 
	// permey de remettre la phase dans 0 2pi
    if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI;

    return sample;
}
