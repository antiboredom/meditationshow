//
//  Looper.cpp
//  pelosi
//
//  Created by Sam Lavigne on 4/9/18.
//

#include "Looper.hpp"

Looper::Looper(){
};

void Looper::setup(string path, float _x, float _y, int _offset, int _total){
  x = _x;
  y = _y;
  offset = _offset;
  total = _total;
  drawFunction = rand() % 4;
  drawFunction = 1;
  
  buffers.clear();
  
  player.load(path);
  player.setLoopState(OF_LOOP_NORMAL);
  player.setVolume(0.1);
  player.play();
  
  float similarity = ofRandom(0.3, 0.5);
  float blend = ofRandom(0.05, 0.2);

  //chroma = new ChromaKeyBlendFilter(ofVec3f(0.f, 0.f, 1.f), similarity, blend);
  chroma = new ChromaKeyBlendFilter(ofVec3f(0.f, 0.f, 1.f), 0.43f, 0.18f);
  
  ofFbo fbo;
  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  fbo.begin();
  ofClear(10.0, 10.0, 10.0, 0.0);
  fbo.end();
  chroma->setSecondTexture(fbo.getTexture());
  
  totalFrames = int(player.getDuration() * 30);
  //totalFrames = player.getTotalNumFrames();
  currentFrame = 0;
  
  animations.clear();
  for (int i = 0; i < 10; i++){
    ofxAnimatableFloat *a = new ofxAnimatableFloat();
    a->animateFromTo(-1.0, 1.0);
    a->setCurve(ofRandom(1.0) >= 0.5 ? LINEAR : EASE_IN);
    a->setRepeatType(ofRandom(1.0) >= 0.5 ? LOOP_BACK_AND_FORTH : LOOP);
    a->setDuration(ofRandom(20.0, 60.0));
    animations.push_back(a);
  }
  
  multipliers.clear();
  for (int i = 0; i < 10; i++){
    multipliers.push_back(ofRandom(1.0));
  }
}

void Looper::update() {
  player.update();
  for (int i=0; i < animations.size(); i++){
    animations[i]->update(1.0f/30.0f);
  }
}

void Looper::updateBuffers() {
  if (buffers.size() < totalFrames && player.isLoaded() && player.isPlaying() && player.getCurrentFrame() > 0 && player.isFrameNew()) {
    ofFbo fbo;
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    chroma->begin();
    player.draw(0, 0);
    chroma->end();
    fbo.end();
    buffers.push_back(fbo);
  }
  
  if (buffers.size() == totalFrames && player.isPlaying()) {
    player.stop();
    player.closeMovie();
  }
}

Boolean Looper::draw() {
  updateBuffers();
  
  if (buffers.size() != totalFrames && drawFunction != 4) {
    return false;
  }
  
  float _x = x;
  float _y = y;
  
  switch (drawFunction)
  {
    case 0:
      for (int i = 0; i < total; i++) {
        int frameNum = (currentFrame + i*offset) % (totalFrames);
        if (buffers.size() > frameNum) {
          ofEnableAlphaBlending();
          ofSetColor(255,255,255, fabs(sin(ofMap(float(frameNum), 0.0, float(totalFrames), 0.0, PI))*200 + 55));
//          ofSetColor(0,0,0,10);

          //chroma->begin();
          ofPushMatrix();
          float scale = sin((float(i)+float(frameNum))/900.0)*2.0 + 1;
          //scale = fabs(animations[2]->val())*2;//float(i)+float(frameNum);
          ofScale(scale, scale);

          buffers[frameNum].draw(_x-300.0, y);
          ofPopMatrix();
          //chroma->end();
          ofSetColor(255,255,255, 255);
          ofDisableAlphaBlending();

          _x += fabs(animations[0]->val())*100;//ofMap(ofGetMouseX(), 0, ofGetWidth(), -2000, 2000);
          _y += 30;
        }
      }
      break;
    case 1:
      for (int i = 0; i < total; i++) {
        int frameNum = (currentFrame + i*offset) % (totalFrames);
        if (buffers.size() > frameNum) {
          //chroma->begin();
          //ofEnableAlphaBlending();
          ofPushMatrix();
          ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
          ofRotate(360.0 * (float(i)/float(total)));
          //float scale = sin((float(i)+float(frameNum))/900.0)*2.0 + 1;
          //ofScale(scale, scale);
          //ofSetColor(255,255,255, fabs(sin(ofMap(float(frameNum), 0.0, float(totalFrames), 0.0, PI))*200 + 50));
          //buffers[frameNum].draw(sin(ofGetFrameNum()/100.0)*400, -400);
          buffers[frameNum].draw(animations[0]->val()*400, -400);
          //ofSetColor(255,255,255, 255);

          ofPopMatrix();
          //ofDisableAlphaBlending();
          //chroma->end();
        }
      }
      break;
    case 2:
      for (int i = 0; i < total; i++) {
        int frameNum = (currentFrame + i*offset) % (totalFrames);
        if (buffers.size() > frameNum) {
          //chroma->begin();
          //ofEnableAlphaBlending();
          ofPushMatrix();
          //float scale = sin((float(i)+float(frameNum))/900.0)*2.0 + 1;
          //ofScale(scale, scale);
          //ofSetColor(255,255,255, fabs(sin(ofMap(float(frameNum), 0.0, float(totalFrames), 0.0, PI))*200 + 50));
          buffers[frameNum].draw(_x, _y);
          ofPopMatrix();
          //ofSetColor(255,255,255, 255);
          //ofDisableAlphaBlending();
          //chroma->end();
          _x += multipliers[0]*20;
          //_y += multipliers[1]*10;
        }
      }
      break;
    case 3:
      for (int i = 0; i < total; i++) {
        int frameNum = (currentFrame + i*offset) % (totalFrames);
        if (buffers.size() > frameNum) {
          //chroma->begin();
          //ofEnableAlphaBlending();
          ofPushMatrix();
          ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
          ofRotate(360.0 * (float(i)/float(total)));
          float scale = sin((float(i)+float(frameNum))/(multipliers[0]*400.0))*3.0 + 1;
          ofScale(scale, scale);
          //ofSetColor(255,255,255, fabs(sin(ofMap(float(frameNum), 0.0, float(totalFrames), 0.0, PI))*200 + 50));
          //buffers[frameNum].draw(sin(ofGetFrameNum()/100.0)*400, -400);
          ofPushMatrix();
          ofRotate(animations[1]->val()*500);
          
          buffers[frameNum].draw(animations[0]->val()*400, -400);
          //ofSetColor(255,255,255, 255);
          ofPopMatrix();
          ofPopMatrix();
          //ofDisableAlphaBlending();
          //chroma->end();
        }
      }
      break;
    case 4:
      
      chroma->begin();
      player.draw(x, y);
      chroma->end();
    
      break;
  }
  
  currentFrame ++;
  if (currentFrame >= totalFrames) currentFrame = 0;
}
