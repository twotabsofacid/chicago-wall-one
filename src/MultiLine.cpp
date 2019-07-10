//
//  MultiLine.cpp
//  MultiLines
//
//
//

#include "MultiLine.hpp"

MultiLine::MultiLine()
{
	float width = ofGetWidth();
	float height = ofGetHeight();
    start = glm::vec2(ofRandom(width), ofRandom(height));
    middle = glm::vec2(ofRandom(width), ofRandom(height));
    end = glm::vec2(ofRandom(width), ofRandom(height));
    incMax = 500;
    inc = 0;
    setup();
}

MultiLine::MultiLine(glm::vec2 _start, glm::vec2 _middle, glm::vec2 _end, int _incMax) {
	start = _start;
	middle = _middle;
	end = _end;
	incMax = _incMax;
	inc = 0;
    setup();
}

void MultiLine::setup() {
	path.setCurveResolution(100);
	ofSetCircleResolution(100);
	color = ofColor(255, 40, 20);
}

void MultiLine::update(int _inc) {
	inc = _inc;
}

void MultiLine::draw() {
	ofPushStyle();
	path.clear();
	path.setStrokeColor(color);
	path.setFilled(false);
	path.setStrokeWidth(4);
	path.moveTo(start);
	// Lerp the ending X and Y positions,
	// so that we start by going halfway to the middle position,
	// and then switch to heading towards the desired end position
	float lerpEndX = inc < incMax/2.0 ? ofLerp(start.x, middle.x/2.0, (float)inc/(incMax/2.0)) : ofLerp(middle.x/2.0, end.x, ofClamp(((float)inc - incMax/2.0)/(incMax/2.0), 0.0, 1.0));
	float lerpEndY = inc < incMax/2.0 ? ofLerp(start.y, middle.y/2.0, (float)inc/(incMax/2.0)) : ofLerp(middle.y/2.0, end.y, ofClamp(((float)inc - incMax/2.0)/(incMax/2.0), 0.0, 1.0));
	// Quad Bezier function through the three points to create the animated curve
	path.quadBezierTo(glm::vec2(start.x, start.y), glm::vec2(ofLerp(start.x, middle.x, ofClamp((float)inc/incMax, 0.0, 1.0)), ofLerp(start.y, middle.y, ofClamp((float)inc/incMax, 0.0, 1.0))), glm::vec2(lerpEndX, lerpEndY));
	path.draw();
	ofPopStyle();
}
