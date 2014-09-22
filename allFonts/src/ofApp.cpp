#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(460, 600);

	oneShot = false;
	pdfRendering = false;

    fontSize = 6;
//    fontSize = 120;
    
    string fontsDir = "/Library/Fonts";
	dir.listDir(fontsDir);
	dir.sort();
//    cout << dir.size() << endl;
    for(int i = 0; i < dir.size(); i++){
//    for(int i = 0; i < 100; i++){
        string fileName = dir.getName(i);
        string fileType = fileName.substr(fileName.length() - 3, fileName.length() - 1);
//        cout << fileName.substr(0, 4) << endl;
//        cout << fileType << endl;
        if((fileType == "ttf" || fileType == "otf")
           && fileName != "NISC18030.ttf"
           && fileName.substr(0, 4) != "STIX"){
//            cout << "Found a font" << endl;
            ofTrueTypeFont currFont;
            currFont.loadFont(fontsDir + "/" + fileName, fontSize, false, false, true);
            allFonts.push_back(currFont);
            fontNames.push_back(fileName);
            
            cout << fileName << endl;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if( oneShot ){
		ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
	}
    
    ofBackground(0);
    
    // DRAW FONT LIST
    ofSetColor(255);
    float x = 0;
    float y = 0;
    for(int i = 0; i < allFonts.size(); i ++){
//        allFonts[i].drawString(fontNames[i], x, y);
//        string upperCaseName = toUpperCase(fontNames[i]);
//        allFonts[i].drawStringAsShapes(upperCaseName, x, y);
        allFonts[i].drawStringAsShapes(fontNames[i], x, y);
        y += fontSize * 1.25;
        if(y > ofGetHeight()){
            x += ofGetWidth() * 0.33;
            y = 0;
        }
    }
    
//    // DRAW LETTER
//    char letter = 'B';
//    
//    for(int i = 0; i < allFonts.size(); i ++){
//        ofTTFCharacter testChar = allFonts[i].getCharacterAsPoints(letter);
//        
//        ofSetColor(225);
//        ofNoFill();
//        
//        ofPushMatrix();
//            ofTranslate(0, fontSize);
//                ofBeginShape();
//                    for(int k = 0; k <(int)testChar.getOutline().size(); k++){
//                        if( k!= 0)ofNextContour(true) ;
//                        for(int i = 0; i < (int)testChar.getOutline()[k].size(); i++){
//                            ofVertex(testChar.getOutline()[k].getVertices()[i].x, testChar.getOutline()[k].getVertices()[i].y);
//                        }
//                    }
//                ofEndShape( true );
//        ofPopMatrix();
//    }

	if( oneShot ){
		ofEndSaveScreenAsPDF();
		oneShot = false;
	}
}

string ofApp::toUpperCase ( string str ){
	string strUpper = "";
    
	for( int i=0; i<str.length(); i++ )
	{
		strUpper += toupper( str[ i ] );
	}
    
	return strUpper;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if( !pdfRendering && key == 's' ){
		oneShot = true;
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
