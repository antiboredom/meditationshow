//
//  Looper.hpp
//  pelosi
//
//  Created by Sam Lavigne on 4/9/18.
//

#ifndef Looper_hpp
#define Looper_hpp

#include "ofMain.h"
#include "ofxFilterLibrary.h"
#include "ofxAnimatableFloat.h"


class Looper {
  public:
  
  void setup(string path, float _x, float _y, int _offset, int _total);
  void update();
  Boolean draw();
  void updateBuffers();
  
  float x, y;
  int offset, total, totalFrames, currentFrame, drawFunction;
  ofVideoPlayer player;
  ChromaKeyBlendFilter * chroma;
  vector <ofFbo> buffers;
  vector <ofxAnimatableFloat*> animations;
  vector <float> multipliers;

  Looper();
};

#endif /* Looper_hpp */
