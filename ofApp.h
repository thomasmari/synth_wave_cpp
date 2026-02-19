#pragma once

#include "ofMain.h"
#include "Oscillo.h"
#include "Keyboard.h"
#include "ofxGui.h" // for the GUI slidders

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void audioOut(ofSoundBuffer & buffer);
		void computeFourierTransform(ofSoundBuffer & buffer);

		void noteStart(int key, float frequency);
		void noteEnd(int key);

		ofSoundStream soundStream;

		Keyboard keyboard;

		float 	pan;
		int		sampleRate;
		float 	volume;
		string  mode_audio;
		int MAX_VOICES;

		vector <float> monoAudio;
		vector <float> frequencies;
		vector<Oscillo> oscillators;

		//------------------- for the simple sine wave synthesis
		float 	targetFrequency;
		float 	phase;
		float 	phaseAdder;
		float 	phaseAdderTarget;
		const string oscillo_modes[4] = {"square", "saw", "sinus", "piano"};
		string current_oscillator_mode = oscillo_modes[0]; // default mode
// GUI Sliders et Panneaux
// ... inside class ofApp ...
    ofxPanel gui;
    ofxFloatSlider brillanceSlider;
    ofxFloatSlider gainSlider;
    
    ofxGuiGroup modeGroup;
    ofxToggle sinusToggle;
    ofxToggle squareToggle;
    ofxToggle sawToggle;
    ofxToggle pianoToggle; // Added piano
	    


    // Use the array as defined
    void modeChanged(bool & val);
};
