#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(34, 34, 34);
	
	int bufferSize		= 512;
	sampleRate 			= 44100;
	phase 				= 0;
	phaseAdder 			= 0.0f;
	phaseAdderTarget 	= 0.0f;
	volume				= 0.1f;
	mode_audio = "poly"; //"mono" or "poly"

	if (mode_audio == "poly") {
		MAX_VOICES = 10;
	} else if (mode_audio == "mono") {
		MAX_VOICES = 1;
	}

	monoAudio.assign(bufferSize, 0.0);
	frequencies.assign(bufferSize, 0.0);
	oscillators.resize(MAX_VOICES);
	
	soundStream.printDeviceList();

	ofSoundStreamSettings settings;
	keyboard.setup(this);
	// Gui sliders
	gui.setup("Synthetizer Controls");
    
    // On calcule la position : largeur totale - largeur du GUI (souvent 200 ou 210 pixels par défaut)
    // On laisse une petite marge de 10 pixels pour l'esthétique
    float guiWidth = gui.getWidth();
    gui.setPosition(ofGetWidth() - guiWidth - 10, 10);
    gui.add(gainSlider.setup("Gain", 0.5f, 0.0f, 1.0f));
    gui.add(brillanceSlider.setup("Brillance", 8.0f, 1.0f, 15.0f));

    modeGroup.setup("Oscillator Mode");
    modeGroup.add(squareToggle.setup(oscillo_modes[0], true)); // Square default
    modeGroup.add(sawToggle.setup(oscillo_modes[1], false));
    modeGroup.add(sinusToggle.setup(oscillo_modes[2], false));
    modeGroup.add(pianoToggle.setup(oscillo_modes[3], false));


    modePolyphony.setup("Polyphony Mode");
    modePolyphony.add(polyToggle.setup("Poly", true)); // Polyphony default
    
    gui.add(&modeGroup);
    gui.add(&modePolyphony);

    // Listeners
    squareToggle.addListener(this, &ofApp::modeChanged);
    sawToggle.addListener(this, &ofApp::modeChanged);
    sinusToggle.addListener(this, &ofApp::modeChanged);
    pianoToggle.addListener(this, &ofApp::modeChanged);
    polyToggle.addListener(this, &ofApp::change_polyphony_mode);
	
	// oscillo setup qnd keyboard setup
    keyboard.setup(this);
	// if you want to set the device id to be different than the default:
	//
	//	auto devices = soundStream.getDeviceList();
	//	settings.setOutDevice(devices[3]);

	// you can also get devices for an specific api:
	//
	//	auto devices = soundStream.getDeviceList(ofSoundDevice::Api::PULSE);
	//	settings.setOutDevice(devices[0]);

	// or get the default device for an specific api:
	//
	// settings.api = ofSoundDevice::Api::PULSE;

	// or by name:
	//
	//	auto devices = soundStream.getMatchingDevices("default");
	//	if(!devices.empty()){
	//		settings.setOutDevice(devices[0]);
	//	}


	// Latest linux versions default to the HDMI output
	// this usually fixes that. Also check the list of available
	// devices if sound doesn't work

	//settings.setApi(ofSoundDevice::MS_ASIO);
	//settings.setApi(ofSoundDevice::MS_WASAPI);
	//settings.setApi(ofSoundDevice::MS_DS);

	auto devices = soundStream.getMatchingDevices("default");
	if(!devices.empty()){
		settings.setOutDevice(devices[0]);
	}




	settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 0;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);

	// on OSX: if you want to use ofSoundPlayer together with ofSoundStream you need to synchronize buffersizes.
	// use ofFmodSetBuffersize(bufferSize) to set the buffersize in fmodx prior to loading a file.
}

void ofApp::change_polyphony_mode(bool & val){
	if (!polyToggle) {
		mode_audio = "mono";
		MAX_VOICES = 1;
	} else if (polyToggle) {
		mode_audio = "poly";
		MAX_VOICES = 10;
	}
	oscillators.resize(MAX_VOICES);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(225);
	ofNoFill();

	// draw the GUI sildders:
	gui.draw();
	
	// draw the mono channel:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 150, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Channel (mono)", 4, 18);
		
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 700, 200);
		int numberOfActiveOscillators = 0;
		for (auto &o : oscillators) {
			if (o.is_active()) {
				numberOfActiveOscillators++;
			}
		}
		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);
					
			ofBeginShape();
			for (unsigned int i = 0; i < monoAudio.size(); i++){
				float x =  ofMap(i, 0, monoAudio.size(), 0, 700, true);
	        
        // On extrait le signe et on applique une racine carrée pour "gonfler" les petites valeurs
        float sign = (monoAudio[i] > 0) ? 1.0f : -1.0f;
		float normal_value = 0.8f * monoAudio[i] / numberOfActiveOscillators ; // valeur absolue
        float compressedValue = 2*log10(1+normal_value)/log10(2) - 1.0f; // 0.8f pour éviter de toucher les bords du rectangle	
        
        // On map la valeur compressée [-1, 1] vers la hauteur du rectangle [200, 0]
        float y = ofMap(compressedValue, -1.0f, 1.0f, 75.0f, 0.0f);
		ofVertex(x, y);
			}
			ofEndShape(false);
			
		ofPopMatrix();
	ofPopStyle();



// draw the spectrum:
ofPushStyle();
    ofPushMatrix();
    ofTranslate(32, 350, 0);
        
    ofSetColor(225);
    ofDrawBitmapString("Spectrum (Log Log)", 4, 18);
    
    ofSetLineWidth(1);  
    ofDrawRectangle(0, 0, 700, 200);

    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
                
    ofBeginShape();
    // On commence à i=1 car log(0) n'existe pas
    for (unsigned int i = 1; i < frequencies.size() / 2.0f; i++){
        
        // --- AXE X : LOG FREQUENCY ---
        // On calcule la position normalisée log(i) / log(max)
        float logX = log10(i) / log10(frequencies.size() / 2.0f);
        float x = logX * 700;

        // --- AXE Y : LOG INTENSITY (dB) ---
        // Conversion en dB : 20 * log10(amplitude)
        // On ajoute 0.0001f pour éviter le log(0)
        float db = 20.0f * log10(frequencies[i] + 0.0001f);
        
        // On définit une plage de dB à afficher (ex: de -60dB à 0dB)
        // -60dB sera le bas du rectangle (200px), 0dB sera le haut (0px)
        float y = ofMap(db, -60, 0, 200, 0, true);
        
        ofVertex(x, y);
    }
    ofEndShape(false);  
    ofPopMatrix();
ofPopStyle();
	
 // draw the keyboard:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 650, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Keyboard", 4, 18);
		
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 900, 200);

		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);
		ofFill();
		keyboard.draw();
		ofPopMatrix();
	ofPopStyle();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '-' || key == '_' ){
		volume -= 0.05;
		volume = std::max(volume, 0.f);
	} else if (key == '+' || key == '=' ){
		volume += 0.05;
		volume = std::min(volume, 1.f);
	}
	else if (key >= 'a' && key <= 'z') {
		keyboard.keyPressed(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){
	if (key >= 'a' && key <= 'z') {
		keyboard.keyReleased(key);
	}	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	int width = ofGetWidth();
	pan = (float)x / (float)width;
	float height = (float)ofGetHeight();
	float heightPct = ((height-y) / height);
	targetFrequency = 22000.0f * heightPct;
	phaseAdderTarget = (targetFrequency / (float) sampleRate) * glm::two_pi<float>();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	int width = ofGetWidth();
	pan = (float)x / (float)width;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){
	if (mode_audio == "mono") {
		for(auto &o : oscillators){
		// Initialize the output buffer to zero
		for(size_t i=0; i<buffer.size(); i++) buffer[i] = 0.0f;
		// call oscillo to update the frequency spectrum
		o.audioOut(buffer);
		}
	} else if (mode_audio == "poly") {
		// Initialize the output buffer to zero
		for(size_t i=0; i<buffer.size(); i++) buffer[i] = 0.0f;

		// Sum all active oscillators
		for(auto &o : oscillators){
    		o.audioOut(buffer);
        	}
    	}
	// Save the current audio buffer for visualization
	monoAudio = buffer.getBuffer();        	
	computeFourierTransform(buffer); 
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::computeFourierTransform(ofSoundBuffer & buffer){
	int N= buffer.getNumFrames();
	for(int k=0;k<N;k++) {
		float F1 = 0;
		float F2 = 0;
		for(int n=0;n<N;n++) {
			float xn = (buffer.getSample(n, 0) + buffer.getSample(n, 1)) / 2.0f; // get sample for left channel 
			F1 += xn * cos(2.0f * PI * k * n / N);
			F2 += xn * sin(2.0f * PI * k * n / N);
		}
		frequencies[k] = sqrt(F1*F1 + F2*F2);
		frequencies[k] /= N;
	}
}

void ofApp::noteStart(int key, float frequency){
	//mono and polyphony implementation:

	// If note is already playing, do nothing
	for (auto &o : oscillators) {
		if (o.is_active() && o.get_key() == key) {
			return; // Note is already playing, do nothing
		}
	}

	// Try to find a free oscillator
	for (auto &o : oscillators) {
		if (!o.is_active()) {
			o.setup();
			o.set_key(key);
			o.set_frequency(frequency);
			o.set_gain(gainSlider);
			if (sinusToggle) {
				o.set_mode("sinus");
			} else if(squareToggle) {
				o.set_mode("square");
			} else if(sawToggle) {
				o.set_mode("saw");
			} else if(pianoToggle) {
				o.set_mode("piano");
			}
			o.set_brillance((int)brillanceSlider);
			o.start();
			return;
		}
	}

	// If none are free, replace the first one
	auto &o = oscillators[0];
	o.stop();
	o.setup();
	o.set_key(key);
	o.set_frequency(frequency);
	o.set_gain(gainSlider);
	if (sinusToggle) {
		o.set_mode("sinus");
	} else if(squareToggle) {
		o.set_mode("square");
	} else if(sawToggle) {
		o.set_mode("saw");
	} else if(pianoToggle) {
		o.set_mode("piano");
	}
	o.set_brillance((int)brillanceSlider);
	o.start();
}

void ofApp::noteEnd(int key){
		for (auto &o : oscillators) {
			if (o.is_active() && o.get_key() == key) {
				o.set_gain(0.0f);
				o.stop();
				break;
			}
		}

}

//Elle assure qu'un seul toggle est actif et met à jour l'objet oscillo.
void ofApp::modeChanged(bool & val){
    // Determine which toggle was clicked by comparing with current oscillo mode


    // Case: Square clicked
    if(squareToggle && current_oscillator_mode != oscillo_modes[0]) {
        sawToggle = false; sinusToggle = false; pianoToggle = false;
		for (auto &o : oscillators) {
			if (o.is_active()) {
				o.set_mode(oscillo_modes[0]);	
			}
		}
    }
    // Case: Saw clicked
    else if(sawToggle && current_oscillator_mode != oscillo_modes[1]) {
        squareToggle = false; sinusToggle = false; pianoToggle = false;
		for (auto &o : oscillators) {
			if (o.is_active()) {
				o.set_mode(oscillo_modes[1]);	
			}
		}
    }
    // Case: Sinus clicked
    else if(sinusToggle && current_oscillator_mode != oscillo_modes[2]) {
        squareToggle = false; sawToggle = false; pianoToggle = false;
		for (auto &o : oscillators) {
			if (o.is_active()) {
				o.set_mode(oscillo_modes[2]);	
			}
		}
    }
    // Case: Piano clicked
    else if(pianoToggle && current_oscillator_mode != oscillo_modes[3]) {
        squareToggle = false; sawToggle = false; sinusToggle = false;
		for (auto &o : oscillators) {
			if (o.is_active()) {
				o.set_mode(oscillo_modes[3]);	
			}
		}
    }


    // Guard: Prevent turning off the active mode (Keep at least one true)
    if (!squareToggle && !sawToggle && !sinusToggle && !pianoToggle) {
        if (current_oscillator_mode == oscillo_modes[0]) squareToggle = true; 
        else if (current_oscillator_mode == oscillo_modes[1]) sawToggle = true; 
        else if (current_oscillator_mode == oscillo_modes[2]) sinusToggle = true; 
        else if (current_oscillator_mode == oscillo_modes[3]) pianoToggle = true; 
    }
	// Update current mode after ensuring one toggle is active
        if (squareToggle && current_oscillator_mode != oscillo_modes[0]) current_oscillator_mode = oscillo_modes[0];
        else if (sawToggle && current_oscillator_mode != oscillo_modes[1]) current_oscillator_mode = oscillo_modes[1];
        else if (sinusToggle && current_oscillator_mode != oscillo_modes[2]) current_oscillator_mode = oscillo_modes[2]; 	
        else if (pianoToggle && current_oscillator_mode != oscillo_modes[3]) current_oscillator_mode = oscillo_modes[3];
    }
