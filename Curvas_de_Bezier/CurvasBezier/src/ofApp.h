
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream> 
#include <math.h> 
#include "ofxGui.h"
using namespace std;

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
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


		float interpolar(float x, float y, float accur);
		std::vector<ofVec2f> curvaBezier(std::vector<ofVec2f>& anchor, float accur);

		//ofxIntSlider degree;
		ofxIntSlider accuracy;
		ofxButton limpiar;
		ofxButton dibujar;
		ofxPanel gui;
		std::vector<ofVec2f> controlPts;
		bool drawPressed;
		
};
