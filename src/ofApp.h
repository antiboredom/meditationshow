#pragma once

#include "ofMain.h"
#include "ofxFilterLibrary.h"
#include "ofxSyphon.h"
#include "Looper.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
  
    void randomHand();
    void newBG();
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
  
    ofVideoPlayer myPlayer;
    Looper looper;
    ofxSyphonServer mainOutputSyphonServer;  
    ofxSyphonClient mClient;
    BloomFilter * bloomfilter;
    ofFbo fbo;
    float fgopacity, bgopacity;
    ofImage bgimage;
  
    ofSoundPlayer words, backtrack, wordsFast;
		
};
