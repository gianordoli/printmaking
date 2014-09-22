//
//  Topic.cpp
//  pomodoro
//
//  Created by Gabriel Gianordoli on 9/21/14.
//
//

#include "Topic.h"

void Topic::setup(string _name, vector<string> _dates){
    name = _name;
    dates = _dates;
    for (int i = 0; i < dates.size(); i++) {
        hours.push_back(0.0);
    }
    totalHours = 0.0;
}

void Topic::update(){
    
}

void Topic::draw(int _index, bool _drawLabels, string _chartType){
    
    // Label
    if(_drawLabels){
        ofPoint labelPos = ofPoint(ofGetWidth() - 300, (_index + 1) * 20);
        ofSetColor(color);
        ofDrawBitmapString("[" + ofToString(_index + 1) + "] " + name + ": " + ofToString(totalHours) + " h", labelPos);
    }
    
    if(_chartType == "bar"){
        drawBars();
    }else if(_chartType == "area"){
        drawArea();
    }else if(_chartType == "polar"){
        drawPolar();
    }
    
}

void Topic::drawBars(){
    for (int i = 0; i < hours.size(); i++) {
        ofFill();
        ofSetColor(color);
        ofRect(pos[i], size[i].x, -size[i].y);
        
        ofNoFill();
        ofSetColor(255);
        ofSetLineWidth(1);
        ofRect(pos[i], size[i].x, -size[i].y);
    }
}

void Topic::drawPolar(){

    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

    ofFill();
    ofSetColor(color);
    
    ofBeginShape();
    for(int i = 0; i < innerPolarPos.size(); i++){
        ofVertex(innerPolarPos[i]);
    }
    
    for(int i = outerPolarPos.size() - 1; i >= 0 ; i--){
        ofVertex(outerPolarPos[i]);
    }
    ofEndShape(true);
    
    ofPopMatrix();
}

void Topic::drawArea(){
    
    ofFill();
    ofSetColor(color);
    
    ofBeginShape();
    for(int i = 0; i < pos.size(); i++){
        ofVertex(pos[i]);
    }
    
    for(int i = pos.size() - 1; i >= 0 ; i--){
        ofPoint newPos = ofPoint(pos[i].x, pos[i].y - size[i].y);
        ofVertex(newPos);
    }
    ofEndShape();
}

void Topic::calculateHours(){
    for (int i = 0; i < hours.size(); i++) {
        totalHours += hours[i];
    }
}

void Topic::setPolar(int _index, vector<Topic> & allTopics, float _innerRadius, float _outerRadius, float _maxHoursPerDay){
    
    for (int i = 0; i < hours.size(); i++) {
        float prevHours = 0.0;
        for (int j = 0; j < _index; j++) {
            //            cout << allTopics[j].name << ": " << allTopics[j].hours[i] << endl;
            prevHours += allTopics[j].hours[i];
        }
        //        cout << prevHours << endl;
        
        float angle = ofMap(i, 0, hours.size() - 1, -PI*0.5, PI*1.5);
        float radius1 = ofMap(prevHours, 0, _maxHoursPerDay, _innerRadius, _outerRadius);
        float radius2 = ofMap(prevHours + hours[i], 0, _maxHoursPerDay, _innerRadius, _outerRadius);
        
        ofPoint thisInnerPolarPos, thisOuterPolarPos;
        thisInnerPolarPos = ofPoint(cos(angle) * radius1, sin(angle) * radius1);
        thisOuterPolarPos = ofPoint(cos(angle) * radius2, sin(angle) * radius2);
        
        innerPolarPos.push_back(thisInnerPolarPos);
        outerPolarPos.push_back(thisOuterPolarPos);
    }
}

void Topic::setBars(int _index, vector<Topic> & allTopics, ofPoint _chartPos, ofPoint _chartSize, float _maxHoursPerDay){
    
    for (int i = 0; i < hours.size(); i++) {
        float prevHours = 0.0;
        for (int j = 0; j < _index; j++) {
            //            cout << allTopics[j].name << ": " << allTopics[j].hours[i] << endl;
            prevHours += allTopics[j].hours[i];
        }
        //        cout << prevHours << endl;
        
        ofPoint thisPos, thisSize;
        thisPos.x = ofMap(i, 0, hours.size() - 1, _chartPos.x, _chartPos.x + _chartSize.x);
        thisPos.y = ofMap(prevHours,
                          0, _maxHoursPerDay,
                          _chartPos.y + _chartSize.y, _chartPos.y);
        //        cout << thisPos.y << endl;
        
        thisSize.x = _chartSize.x / hours.size();
        thisSize.y = ofMap(hours[i],
                           0, _maxHoursPerDay,
                           0, _chartSize.y);
        //        cout << thisSize.y << endl;
        
        pos.push_back(thisPos);
        size.push_back(thisSize);
    }
}

void Topic::setColor(int _index, int _numTopics){
//    color.setHsb(ofMap(_index, 0, _numTopics - 1, 0, 160), 255, 255);

    if (_index % 2 == 0) {
        color.setHsb(ofMap(_index, 0, _numTopics - 1, 0, 125), 255, 255);
    }else{
        color.setHsb(ofMap(_index, 0, _numTopics - 1, 125, 250), 255, 255);
    }
}