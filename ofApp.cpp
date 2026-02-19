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

	monoAudio.assign(bufferSize, 0.0);
	frequencies.assign(bufferSize, 0.0);
	
	soundStream.printDeviceList();

	ofSoundStreamSettings settings;
	oscillo.setup();
	keyboard.setup(this);
	// Gui sliders
gui.setup("Synth Controls");
    gui.add(gainSlider.setup("Gain", 0.5f, 0.0f, 1.0f));
    gui.add(brillanceSlider.setup("Brillance", 8.0f, 1.0f, 15.0f));

    modeGroup.setup("Oscillator Mode");
    modeGroup.add(squareToggle.setup(oscillo_modes[0], true)); // Square default
    modeGroup.add(sawToggle.setup(oscillo_modes[1], false));
    modeGroup.add(sinusToggle.setup(oscillo_modes[2], false));
    modeGroup.add(pianoToggle.setup(oscillo_modes[3], false));
    
    gui.add(&modeGroup);

    // Listeners
    squareToggle.addListener(this, &ofApp::modeChanged);
    sawToggle.addListener(this, &ofApp::modeChanged);
    sinusToggle.addListener(this, &ofApp::modeChanged);
    pianoToggle.addListener(this, &ofApp::modeChanged);
	
	// oscillo setup qnd keyboard setup
    oscillo.setup();
    oscillo.set_mode(oscillo_modes[0]); // Set initial mode
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
		ofDrawBitmapString("Channel", 4, 18);
		
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 900, 200);

		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);
					
			ofBeginShape();
			for (unsigned int i = 0; i < monoAudio.size(); i++){
				float x =  ofMap(i, 0, monoAudio.size(), 0, 900, true);
				ofVertex(x, 100 -monoAudio[i]*180.0f);
			}
			ofEndShape(false);
			
		ofPopMatrix();
	ofPopStyle();

	// draw the spectrum:
	ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 350, 0);
			
		ofSetColor(225);
		ofDrawBitmapString("Spectrum", 4, 18);
		
		ofSetLineWidth(1);	
		ofDrawRectangle(0, 0, 900, 200);

		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);
					
			ofBeginShape();
			for (unsigned int i = 0; i < frequencies.size(); i++){
				float x =  ofMap(i, 0, frequencies.size()/2.0f, 0, 900, true);
				ofVertex(x, 100.0f - 100.0f*frequencies[i]);
			}
			ofEndShape(false);	
		ofPopMatrix();
	ofPopStyle();
	
		
	ofSetColor(225);
	string reportString = "volume: ("+ofToString(volume, 2)+") modify with -/+ keys\npan: ("+ofToString(pan, 2)+") modify with mouse x\nsynthesis: ";
	reportString += "sine wave (" + ofToString(targetFrequency, 2) + "hz) modify with mouse y";
	ofDrawBitmapString(reportString, 32, 579);
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
void ofApp::keyPressed  (int key){
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
	// call oscillo to update the frequency spectrum
	oscillo.audioOut(buffer);
	monoAudio = buffer.getBuffer(); 
	// Update frequency spectrum
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
	oscillo.set_frequency(frequency);
	oscillo.set_gain(gainSlider);     // Utilise la valeur du slider
	oscillo.set_brillance((int)brillanceSlider); // Utilise la valeur du slider	
	oscillo.set_frequency(frequency);
	if (sinusToggle) {
		oscillo.set_mode("sinus");
	} else if(squareToggle) {
		oscillo.set_mode("square");
	} else if(sawToggle) {
	oscillo.set_mode("saw");
	} else if(pianoToggle) {
		oscillo.set_mode("piano");
	}
}

void ofApp::noteEnd(int key){
		oscillo.stop(); // no polyphony implemented, so we just stop the oscillo when a key is released
}

//Elle assure qu'un seul toggle est actif et met à jour l'objet oscillo.
void ofApp::modeChanged(bool & val){
    // Determine which toggle was clicked by comparing with current oscillo mode
    string current = oscillo.get_mode();

    // Case: Square clicked
    if(squareToggle && current != oscillo_modes[0]) {
        sawToggle = false; sinusToggle = false; pianoToggle = false;
        oscillo.set_mode(oscillo_modes[0]);
    }
    // Case: Saw clicked
    else if(sawToggle && current != oscillo_modes[1]) {
        squareToggle = false; sinusToggle = false; pianoToggle = false;
        oscillo.set_mode(oscillo_modes[1]);
    }
    // Case: Sinus clicked
    else if(sinusToggle && current != oscillo_modes[2]) {
        squareToggle = false; sawToggle = false; pianoToggle = false;
        oscillo.set_mode(oscillo_modes[2]);
    }
    // Case: Piano clicked
    else if(pianoToggle && current != oscillo_modes[3]) {
        squareToggle = false; sawToggle = false; sinusToggle = false;
        oscillo.set_mode(oscillo_modes[3]);
    }

    // Guard: Prevent turning off the active mode (Keep at least one true)
    if (!squareToggle && !sawToggle && !sinusToggle && !pianoToggle) {
        if (current == oscillo_modes[0]) squareToggle = true;
        else if (current == oscillo_modes[1]) sawToggle = true;
        else if (current == oscillo_modes[2]) sinusToggle = true;
        else if (current == oscillo_modes[3]) pianoToggle = true;
    }
}
