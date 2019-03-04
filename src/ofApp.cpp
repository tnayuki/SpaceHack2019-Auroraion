#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    videoPlayer.load("aurora - HD 720p.mov");

    colorImage.allocate(videoPlayer.getWidth(), videoPlayer.getHeight());
    saturationImage.allocate(videoPlayer.getWidth(), videoPlayer.getHeight());

    videoPlayer.play();

    oscReceiver.setup(8888);
    midiOut.openVirtualPort();
}

//--------------------------------------------------------------
void ofApp::update(){
    int auroraLevel = 0;
    
    videoPlayer.update();

    colorImage.setFromPixels(videoPlayer.getPixels());
    colorImage.convertRgbToHsv();
    colorImage.convertToGrayscalePlanarImage(saturationImage, 2);

    ofPixels &colorPixels = colorImage.getPixels();
    ofPixels &saturationPixels = saturationImage.getPixels();
    for (int i = 0; i < saturationPixels.size(); i++) {
        if (saturationPixels[i] > 60) {
            colorPixels[i * 3] = 0;
            colorPixels[i * 3 + 1] = 255;
            colorPixels[i * 3 + 2] = 0;
            
            auroraLevel++;
        } else {
            colorPixels[i * 3] = 0;
            colorPixels[i * 3 + 1] = 0;
            colorPixels[i * 3 + 2] = 0;
        }
    }
    
    colorImage.flagImageChanged();

    ofxOscMessage oscMessage;
    while (oscReceiver.getNextMessage(oscMessage)) {
        auroraLevel = auroraLevel + oscMessage.getArgAsInt(0) * 10 - 10000;
    }
    
    midiOut.sendNoteOn(1, auroraLevel / 1000);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    colorImage.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
