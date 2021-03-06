#include "ofApp.h"
//#define USE_BIKE 1
#define USE_CAM 1

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0);
	ofSetVerticalSync(false);
	ofSetFrameRate(1000);
	ofSetLogLevel(OF_LOG_NOTICE);

	bShowDebug = true;
	bShowFullScreen = false;
	bShowCursor = true;

	ofSetFullscreen(bShowFullScreen);
	if (bShowCursor) {
		ofShowCursor();
	}
	else {
		ofHideCursor();
	}
#ifdef USE_BIKE
	bicycleController.setup();
	videoController.setup();
#elif USE_CAM
	imageCaptureController.setup();
	imageDisplayController.setup();
	renderController.setup();
#endif
	font.load(ofToDataPath("fonts/verdana.ttf"), 96, true);
#
}

//--------------------------------------------------------------
void ofApp::update() {
#ifdef USE_BIKE
	bicycleController.update();
	videoController.update();
#elif USE_CAM
	imageCaptureController.update();
	imageDisplayController.update();
	//renderController.update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw() {
#ifdef USE_BIKE
	double avgVelocity = bicycleController.getAverageVelocity();
	double normalisedVelocity = bicycleController.getNormalisedVelocity();
	double dstTravelled = bicycleController.getDistanceTravelled();

	ostringstream os;
	os << std::setprecision(1) << std::fixed << avgVelocity << " km/h" << endl << dstTravelled << " m";

	videoController.setSpeed(normalisedVelocity);

	videoController.getVideoTexture().draw(0, 0, ofGetWidth(), ofGetHeight());
	font.drawString(os.str(), 1000, 400);
#elif USE_CAM
	
	renderController.begin();
	{
		imageDisplayController.getDisplayFBO().draw(0, 0);
	}
	renderController.end();

	renderController.draw();

	imageCaptureController.getCameraTexture().draw(0, 0, ofGetWidth() / 4, ofGetHeight() / 4);

#endif

	if (bShowDebug) {

		gui.begin();
		{
#ifdef USE_BIKE
			bicycleController.drawGUI();
			videoController.drawGUI();
#elif USE_CAM
			imageCaptureController.drawGUI();
			imageDisplayController.drawGUI();
			renderController.drawGUI();
#endif
			ImGui::Spacing(); ImGui::Spacing();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		gui.end();

	}

}

//--------------------------------------------------------------
void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	switch (key) {
	case 'd':
	{
		bShowDebug ^= true;
	}
	break;
	case 'f':
	{
		bShowFullScreen ^= true;
		ofSetFullscreen(bShowFullScreen);
	}
	break;
	case 'm':
	{
		bShowCursor ^= true;
		if (bShowCursor) {
			ofShowCursor();
		}
		else {
			ofHideCursor();
		}
	}
	break;
	case ' ':
	{
#ifdef USE_BIKE
		bicycleController.triggerSensor(BicycleController::SENSOR_KEYBOARD);
#else
		imageCaptureController.triggerSensor(ImageCaptureController::SENSOR_KEYBOARD);
#endif

	}
	break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	renderController.mouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	renderController.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	renderController.mouseReleased(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
