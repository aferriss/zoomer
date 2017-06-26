#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = 1920;
    h = 1080;
    
    ofSetWindowShape(w, h);
//    ofSetFrameRate(30);
//    ofSetVerticalSync(false);
    
    fbo.allocate(w, h, GL_RGBA);
    video.load("faceCropTrimSlow.mp4");
    video.play();
    
    
    recorder.setVideoCodec("mpeg");
    recorder.setVideoBitrate("100000k");
    
    save = false;
    scale = 5.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if(save){
        ofPixels p;
        fbo.readToPixels(p);
        recorder.addFrame(p);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    if(video.isFrameNew()){
        fbo.begin();
            ofPushMatrix();
            ofTranslate(w/2, h/2);
            ofScale(scale, scale);
                video.draw(-w/2,-h/2);
            ofPopMatrix();
        fbo.end();
//    }
    
    fbo.draw(0,0);
    scale -= 0.001;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        recorder.setup("videos/" + ofGetTimestampString() + ".mov", w, h, 30);
        recorder.start();
        save = true;
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
//--------------------------------------------------------------
void ofApp::exit(){
    recorder.close();
}
