//
//  ofxPlotter.cpp
//
//  Created by Juan Carlos Carvajal B.
//  juan-carlos.info
//
//  Based on the plugin by zebra on 06/05/16.
//
//

#ifndef ofxPlotter_h
#define ofxPlotter_h

#include <map>
#include <string>
#include <vector>

#include "ofMain.h"

using namespace std;


class ofxPlotter {
    
    public:

    struct singleValue {
    public:

        singleValue() : inner_value (0) { }

        // Float righthand
        void operator<<(float righthand) {
            inner_value = righthand;
        }

        // Int righthand
        void operator<<(int righthand) {
            inner_value = righthand;
        }

        void setCurrentValue(float righthand) {
            inner_value = righthand;
        }

        void setCurrentValue(int righthand) {
            inner_value = float(righthand);
        }

        // void setNullValue() { inner_value = NAN; }

        float getF() {
            return inner_value;
        }

        float inner_value;
        
    };

    struct dataCollection{

        dataCollection(); // : plotColor ( ofColor(0) ) , autoRange ( True ), drawOverlay ( False ), plotLength ( 300 )  {  }
        ofColor             plotColor;
        singleValue         currentValue;
        vector<singleValue> records;
        vector<float>       guidelines;
        int    plotLength;
        float  maxValue;
        float  minValue;
        bool   autoRange;
        bool   drawOverlay;
        bool   drawInfo;
        bool   drawGuidelines;

        void setCurrentValue (int   currentValue)   { this->currentValue.setCurrentValue(currentValue); }
        void setCurrentValue (float currentValue)   { this->currentValue.setCurrentValue(currentValue); }
        void setMinMaxValue  (float maxValue, float minValue )   { this->maxValue = maxValue; this->minValue = minValue; autoRange = false; }
        void setPlotLength   (int   plotLength); //      { this->plotLength = plotLength; }
        int getplotLength() { return plotLength; }
        void setColor(ofColor plotColor) { this->plotColor = plotColor; }
        void addGuideline(float guideline) { guidelines.push_back(guideline); }

    };

    ofxPlotter();
    ofxPlotter( int plotLength );

    void update(ofEventArgs & args) { updateHistory(); }
    void updateHistory();

    void drawAllVertical();
    void drawAllVertical(float x, float y, float width, float height);

    void drawAllHorizontal();
    void drawAllHorizontal(float x, float y, float width, float height);

    void drawPlot(string plot);
    void drawPlot(string plot, int x, int y, int width, int height);

    void drawOverlay(string plot, float x, float y, float width, float height);
    void drawInfo(string plot, float x, float y, float width, float height);
    void drawGuidelines(string plot, float x, float y, float width, float height);

    dataCollection& operator[](string name) {
        return (dataCollection&)plotData[name];

    }

    map<string, dataCollection> plotData;

};

#endif /* ofxPlotter_h */
