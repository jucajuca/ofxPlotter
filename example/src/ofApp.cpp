#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    plotter["sin1"].addGuideline(0.75);
    plotter["sin1"].setPlotLength(600); 
    plotter["sin1"].setColor( ofColor(255,0,0) );

    plotter["sin2"].addGuideline(0.25);
    plotter["sin2"].setPlotLength(600); 
    plotter["sin2"].setColor( ofColor(0,255,0) );

    plotter["sin3"].addGuideline(0.5);
    plotter["sin3"].setPlotLength(600); 
    plotter["sin3"].setColor( ofColor(0,0,255) );


}

//--------------------------------------------------------------
void ofApp::update(){
    plotter["sin1"].setCurrentValue( sin(ofGetElapsedTimef() * 1) );
    plotter["sin2"].setCurrentValue( sin(ofGetElapsedTimef() * 4) );
    plotter["sin3"].setCurrentValue( sin(ofGetElapsedTimef() * 8) );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    plotter.drawAllVertical(0, 0, ofGetWidth(), ofGetHeight());
    
    
}

