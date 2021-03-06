#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

#include "BicycleController.h"
#include "VideoController.h"
#include "RenderController.h"
#include "ImageCaptureController.h"
#include "ImageDisplayController.h"

class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	bool bShowDebug;
	bool bShowFullScreen;
	bool bShowCursor;

	ofxImGui gui;

	BicycleController bicycleController;
	VideoController videoController;
	ImageCaptureController imageCaptureController;
	ImageDisplayController imageDisplayController;
	RenderController renderController;

	ofTrueTypeFont font;

};
