//
//  Topic.h
//  pomodoro
//
//  Created by Gabriel Gianordoli on 9/21/14.
//
//

#pragma once
#include "ofMain.h"

class Topic{
public:
    void setup(string _name, vector<string> _dates);
    void update();
    void draw(int _index, bool _drawLabels, string _chartType);
    
    void calculateHours();
    void setBars(int _index, vector<Topic> & allTopics, ofPoint _chartPos, ofPoint _chartSize, float _maxHoursPerDay);
    void setPolar(int _index, vector<Topic> & allTopics, float _innerRadius, float _outerRadius, float _maxHoursPerDay);
        
    void setColor(int _index, int _numTopics);
    
    void drawBars();
    void drawArea();
    void drawPolar();
    
    // Data
    string name;
    vector<string> dates;   // all possible dates, even when there's no hour registered
    vector<float> hours;    // sum of hours per day; 0 is possible
    float totalHours;       // sum of all hours worked
    
    // Layout
    ofColor color;
    vector<ofPoint> pos;
    vector<ofPoint> size;
    
    vector<ofPoint> innerPolarPos;
    vector<ofPoint> outerPolarPos;
};