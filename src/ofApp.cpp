#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofDisableArbTex();
  ofEnableSmoothing();
  ofEnableAlphaBlending();

  ofSetFrameRate(30);
  ofSetWindowTitle("meditation show");
  
  mainOutputSyphonServer.setName("meditation show");
  mClient.setup();
  
  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  //mClient.set("","Simple Server");
  
  newBG();
  
  backtrack.load("audio/bg.wav");
  words.load("audio/capitalistslow.wav");
  wordsFast.load("audio/capitalist.wav");
  
  backtrack.play();
  backtrack.setLoop(true);
  
  words.play();
  words.setLoop(true);

  looper.setup("capitalist.mp4", 0, 0, 5, 10);
  
  bloomfilter = new BloomFilter(ofGetWidth(), ofGetHeight());
  bloomfilter->updateParameter("bloom", 0.0f);
  
  fgopacity = bgopacity = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
  myPlayer.update();
  looper.update();
  if (looper.buffers.size() >= looper.totalFrames) fgopacity += 0.7;
  if (fgopacity > 255) fgopacity = 255;
  
  if (ofGetFrameNum() % 3000 == 0) randomHand();
  if (ofGetFrameNum() % 5000 == 0) newBG();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0, 0, 0);
//  myPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
  //bloomfilter->updateParameter("bloom", ofMap(ofGetFrameNum()%5000, 0, 5000, 0.0, 0.4));
//  bloomfilter->updateParameter("bloom", ofMap(ofGetMouseX(), 0, 1280, 0.1, 0.4));
//  bloomfilter->updateParameter("bloom", 100.0f);
  //bloomfilter->begin();
  ofPushMatrix();
  ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
  float bgscale = ofMap(ofGetFrameNum()%5000, 0, 5000, 0.5, 2);
  ofScale(bgscale, bgscale);
  bgimage.setAnchorPoint(bgimage.getWidth()/2, bgimage.getHeight()/2);
  bgimage.draw(0, 0);
  ofPopMatrix();
  //bloomfilter->end();

  
  fbo.begin();
  ofClear(255, 255, 255, 0);
  looper.draw();
  fbo.end();
  
  ofSetColor(255, 255, 255, fgopacity);
  fbo.draw(0, 0);
  ofSetColor(255, 255, 255, 255);

  mainOutputSyphonServer.publishScreen();
}

void ofApp::randomHand() {
  fgopacity = 0;
  string folders[3] = {"close", "wide", "slow"};
  string path = folders[int(ofRandom(3))] + "/hand" + to_string(int(ofRandom(1, 10))) + ".mp4";
  if (ofRandom(1.0) >= 0.9) {
    path = "capitalist.mp4";
  }
  int offset = int(ofRandom(3, 10));
  int total = int(ofRandom(7, 20));
  
  cout << path << endl;
  
  looper.setup(path, 0, 0.0, offset, total);
}

void ofApp::newBG() {
//  string path = "bgs/sunset" + to_string(int(ofRandom(1, 5))) + ".mp4";
//  cout << path;
//  cout << "\n";
//
//  myPlayer.load(path);
//  myPlayer.play();
//  myPlayer.setLoopState(OF_LOOP_NORMAL);
  
  string path = "bgs/" + to_string(int(ofRandom(1, 8))) + ".jpg";
  cout << path;
  cout << "\n";

  bgimage.load(path);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  randomHand();

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
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
