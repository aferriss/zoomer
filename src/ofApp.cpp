#include "ofApp.h"
#include "ofxEasing.h"

//--------------------------------------------------------------
void ofApp::setup(){
    w = 1920;
    h = 1080;
    
    ofSetWindowShape(w, h);
    ofSetFrameRate(30);
    ofSetVerticalSync(false);
    
    fbo.allocate(w, h, GL_RGB);
    video.load("faceCropTrimSlow.mp4");
    video.play();
    
    
    recorder.setVideoCodec("mpeg4");
    recorder.setVideoBitrate("100000k");
    
    save = false;
    scale = 5.0;
    amt = 0.001;
    
    inc = 0;
    
    fbo.begin();
        ofClear(0,255);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if(floor(video.getPosition()*video.getDuration()) == 188){
        recorder.close();
    }
    
    
    ofSetWindowTitle(ofToString(floor(video.getPosition()*video.getDuration())));
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(video.isFrameNew()){
        pos = ofClamp(5 - ofxeasing::map_clamp(inc, 0, 5400, 0, 4, &ofxeasing::quad::easeOut), 1,5);
        
        fbo.begin();
            ofPushMatrix();
            ofTranslate(w/2, h/2);
            ofScale(pos, pos);
                video.draw(-w/2,-h/2);
            ofPopMatrix();
        fbo.end();
        inc++;
        
        if(save){
            ofPixels p;
            fbo.readToPixels(p);
            recorder.addFrame(p);
        }
    }
    
    fbo.draw(0,0);
//    scale -= amt;
//    scale = ofClamp(scale, 1.0, 5.0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        recorder.setup("videos/" + ofGetTimestampString() + ".mov", w, h, 30);
        recorder.start();
        save = true;
    }
    
    if(key == '['){
        amt -= 0.00001;
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
