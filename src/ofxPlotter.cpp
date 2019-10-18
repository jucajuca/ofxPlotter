//
//  ofxPlotter.cpp
//
//  Created by Juan Carlos Carvajal B.
//  juan-carlos.info
//
//  Based on the plugin by zebra on 06/05/16.
//
//

#include "ofxPlotter.h"


ofxPlotter::dataCollection::dataCollection() :  plotColor ( ofColor(0) ) ,
                                                autoRange ( true ),
                                                drawOverlay ( true ),
                                                drawInfo    ( true ),
                                                plotLength ( 400 ),
                                                maxValue ( 0 ),
                                                minValue ( 0 ) {

    records.clear();
    singleValue tmpValue;
    records.assign( plotLength, tmpValue );

}

void ofxPlotter::dataCollection::setPlotLength (int plotLength){
    this->plotLength = plotLength;
    records.clear();
    singleValue tmpValue;
    records.assign( plotLength, tmpValue );
}


ofxPlotter::ofxPlotter() {

    ofAddListener(ofEvents().update, this, &::ofxPlotter::update);

}

void ofxPlotter::updateHistory() {

    map<string, dataCollection>::iterator it;

    for ( it = plotData.begin(); it != plotData.end(); it++) {

        dataCollection *itDataCollection = &(it->second);

        itDataCollection->records.push_back( itDataCollection->currentValue );

        if ( int( itDataCollection->records.size() ) > itDataCollection->plotLength ){

            itDataCollection->records.erase( itDataCollection->records.begin() );

        }

    }

}


void ofxPlotter::drawPlot(string plot){

    drawPlot (plot, 0, 0, ofGetHeight(), ofGetWidth() ) ;

}

void ofxPlotter::drawPlot(string plot, int x, int y, int width, int height) {

    vector<singleValue>* records =  &(plotData[plot].records);

    float sum = 0;
    float & max = plotData[plot].maxValue;
    float & min = plotData[plot].minValue;

    // Measuring the function scale
    if ( plotData[plot].autoRange ) {

        for ( unsigned long i = 0; i < records->size(); i++ ) {
            float value = (*records)[i].getF();
            sum += value;
            if (value > max) max = value;
            if (value < min) min = value;
        }

    }

    float stepWidth = width / records->size();

    ofPushMatrix();
    ofPushStyle();
        ofTranslate(x, y);

        ofPoint p, p2;
        for ( int j = 0; j < records->size(); j++) {

            float mappedY = 1 - ofMap( (*records)[j].getF(), min, max, 0, 1);
            float mappedX = ofMap(j, 0,records->size(),0, width );

            p = ofPoint( mappedX , mappedY * float(height) );

            ofSetColor( plotData[plot].plotColor );
            ofSetLineWidth(2);
            if (j != 0) ofDrawLine(p2, p);

            p2 = p;

        }

        if ( plotData[plot].drawOverlay) {
            drawOverlay(plot, x, y, width, height);
        }

        if ( plotData[plot].drawInfo) {
            drawInfo(plot, x, y, width, height);
        }

        if ( plotData[plot].drawGuidelines) {
            drawGuidelines(plot, x, y, width, height);
        }
    ofPopMatrix();
    ofPopStyle();
}

/*
 *
 *  Draw all the plots contained in the map in a vertical layout
 *
 *
*/


void ofxPlotter::drawAllVertical() {

    drawAllVertical(0, 0, ofGetHeight(), ofGetWidth() );

}

void ofxPlotter::drawAllVertical(float x, float y, float width, float height) {

    map<string, dataCollection>::iterator it;

    int plotDataSize = plotData.size();
    int i = 0;

    float dy = height / plotDataSize + 1;

    for ( it = plotData.begin(); it != plotData.end(); it++) {

        drawPlot(it->first, x, dy * i , width, dy);
        i++;

    }

}

/*
 *
 *  Draw all the plots contained in the map in a horizontal layout
 *
 *
*/


void ofxPlotter::drawAllHorizontal() {

    drawAllHorizontal(0, 0, ofGetHeight(), ofGetWidth() );

}

void ofxPlotter::drawAllHorizontal(float x, float y, float width, float height) {

    map<string, dataCollection>::iterator it;

    int plotDataSize = plotData.size();
    int i = 0;

    float dx = width  / plotDataSize + 1;
    // float dy = height / plotDataSize + 1;

    for ( it = plotData.begin(); it != plotData.end(); it++) {

        drawPlot(it->first, dx * i, y, dx, height);
        i++;

    }

}

/*
 *
 *  *** DRAW EXTRAS ***
 *
 *
*/


void ofxPlotter::drawOverlay(string plot, float x, float y, float width, float height) {

    vector<singleValue>* records =  &(plotData[plot].records);

    if (!ofRectangle(x, y, width, height).inside(ofGetMouseX(), ofGetMouseY())) return;

    float mx = (ofGetMouseX()  - x);
    float my = (ofGetMouseY()  - y);

    //ofSetColor(128);

    int position = int ( ofMap( mx, 0, width, 0,records->size() )  );
    string tmpString = ofToString( (*records)[position].getF() );
    ofDrawBitmapString( tmpString, mx, my);

}

void ofxPlotter::drawGuidelines(string plot, float x, float y, float width, float height) {

    vector<float>* guidelines =  &(plotData[plot].guidelines);

    if ( !guidelines->size() ) return;

    float & max = plotData[plot].maxValue;
    float & min = plotData[plot].minValue;

    for (vector<float>::iterator it = guidelines->begin(); it != guidelines->end(); it++) {

        float mappedY = ofMap( *it, min, max, 0, 1) * float(height);
        ofDrawLine(0, mappedY, width, mappedY );

    }

}


void ofxPlotter::drawInfo (string plot, float x, float y, float width, float height) {

    dataCollection *iDataCollection = &(plotData[plot]);

    ofSetColor(iDataCollection->plotColor);

    // Plot name
    // ofDrawRectangle(width - plot.length() * 8, yspace / 2 - 12, plot.length() * 8, 15);
    ofDrawBitmapString( plot , width - plot.length() * 8, height / 2);

    // Max value
    string maxValue = ofToString ( iDataCollection->maxValue );
    //ofDrawRectangle(0, 0, maxValue.length() * 8, 15);
    ofDrawBitmapString( maxValue, 0, 12 );

    // Min value
    string minValue = ofToString ( iDataCollection->minValue );
    //ofDrawRectangle(0, height - 12, minValue.length() * 8, 15);
    ofDrawBitmapString(minValue, 0, height);

}

