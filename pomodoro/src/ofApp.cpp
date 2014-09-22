#include "ofApp.h"

bool sortByCount(const Topic & a, const Topic & b){
    return a.totalHours > b.totalHours;
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowShape(800, 1000);
    ofPoint chartPos = ofPoint(ofGetWidth() * 0.1, ofGetHeight() * 0.1);
    ofPoint chartSize = ofPoint(ofGetWidth() * 0.8, ofGetHeight() * 0.8);
    drawLabels = true;
    chartType = 0;
    
    // 0: Load tsv file
    ofBuffer file = ofBufferFromFile("pomodoro.tsv");
    
    // 1: Get all possible dates
    vector<string> allDates;
    string prevDate = "";
    while (!file.isLastLine()){
        string line = file.getNextLine();
        vector <string> split = ofSplitString(line, "\t");
        string thisDate = split[0];
        
        if(thisDate != prevDate){
            allDates.push_back(thisDate);
        }
        prevDate = thisDate;
    }
    
    // 2: Create topics with names and pass all possible dates
    file.resetLineReader();
    while (!file.isLastLine()){
        string line = file.getNextLine();
        vector <string> split = ofSplitString(line, "\t");
        string thisName = split[1];
        
        bool nameIsStored = false;
        
        for (int i = 0; i < allTopics.size(); i++) {
            
            if(allTopics[i].name == thisName){
                
                nameIsStored = true;
            }
        }
        
        if(!nameIsStored){
            Topic thisTopic;
            thisTopic.setup(thisName, allDates);
            allTopics.push_back(thisTopic);
        }
    }

    // 3: Fill out hours
    file.resetLineReader();
    while (!file.isLastLine()){
        string line = file.getNextLine();
        vector <string> split = ofSplitString(line, "\t");
        string thisName = split[1];
        string thisDate = split[0];
        float theseHours = split[5].size() * 0.5;

        for (int i = 0; i < allTopics.size(); i++) {

            if(allTopics[i].name == thisName){

                for (int j = 0; j < allTopics[i].dates.size(); j++){

                    if (allTopics[i].dates[j] == thisDate) {

                        allTopics[i].hours[j] += theseHours;
                    }
                }
            }
        }
    }
    
    // 4: Calculate the total hours for each topic
    for (int i = 0; i < allTopics.size(); i++) {
        allTopics[i].calculateHours();
    }

    // 5: Sort by total hours
    sort(allTopics.begin(), allTopics.end(), sortByCount);
    
    // 6: Before setting the vertices, we need to know
    // what is the highest value of hours for one day
    vector<float> allHours;
    for (int i = 0; i < allTopics[0].hours.size(); i++) {
        float sumOfHours = 0.0;
        for (int j = 0; j < allTopics.size(); j++) {
//            cout << allTopics[j].hours[i] << endl;
            sumOfHours += allTopics[j].hours[i];
        }
//        cout << "****************************" << endl;
//        cout << sumOfHours << endl;
//        cout << "****************************" << endl;
        allHours.push_back(sumOfHours);
    }
    float maxHoursPerDay = 0.0;
    for (int i = 0; i < allHours.size(); i++) {
//        cout << allHours[i] << endl;
        if (allHours[i] > maxHoursPerDay) {
            maxHoursPerDay = allHours[i];
        }
    }
    cout << maxHoursPerDay << endl;
    
    // 7: Set bars (and area vertices)
    for (int i = 0; i < allTopics.size(); i++) {
        allTopics[i].setBars(i, allTopics, chartPos, chartSize, maxHoursPerDay);
    }
    
    // 7: Set polar coordinates
    float innerRadius = ofGetWidth() * 0.05;
    float outerRadius = ofGetWidth() * 0.45;
    for (int i = 0; i < allTopics.size(); i++) {
        allTopics[i].setPolar(i, allTopics, innerRadius, outerRadius, maxHoursPerDay);
    }
    
    // 8: Set colors
    for (int i = 0; i < allTopics.size(); i++) {
        allTopics[i].setColor(i, allTopics.size());
    }
}

//--------------------------------------------------------------
void ofApp::debug(){
    
    cout << "**************************************" << endl;
    
    for (int i = 0; i < allTopics.size(); i++) {
        cout << allTopics[i].name << ": " << allTopics[i].totalHours << endl;
        for (int j = 0; j < allTopics[i].dates.size(); j++) {
            cout << "\t" << allTopics[i].dates[j] << "\t" << allTopics[i].hours[j] << endl;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(255);    
    
    if(isSavingPDF){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }else{
        ofSetColor(0);
        ofDrawBitmapString("Press RETURN to save pdf file.", 10, ofGetHeight() - 10);
    }

    for (int i = 0; i < allTopics.size(); i++) {
        switch (chartType) {
            case 0:
                allTopics[i].draw(i, drawLabels, "bar");
                break;
                
            case 1:
                allTopics[i].draw(i, drawLabels, "area");
                break;
                
            default:
                allTopics[i].draw(i, drawLabels, "polar");
                break;
        }
    }
    
    if(isSavingPDF){
        ofEndSaveScreenAsPDF();
        isSavingPDF = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // Toggle labels visibility
    if(key == ' '){
        drawLabels = (drawLabels) ? (0) : (1);
        
    // Save PDF
    }else if( key == OF_KEY_RETURN){
        isSavingPDF = true;
        
    // Change chart type
    }else if(key == OF_KEY_LEFT || OF_KEY_RIGHT){
        if (key == OF_KEY_LEFT) {
            chartType --;
        }else if(key == OF_KEY_RIGHT){
            chartType ++;
        }
        if(chartType < 0){
            chartType = 2;
        }else if (chartType > 2){
            chartType = 0;
        }
    }
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
