#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	auto span = 100;
	for (auto radius = 0; radius < ofGetWidth(); radius += span) {

		for (auto z = -300; z <= 300; z += 100) {

			auto noise_value = ofNoise((z + 300) * 0.005, radius * 0.005 + ofGetFrameNum() * 0.005);
			if (noise_value > 0.5) {

				vector<glm::vec3> in, out, fill_in, fill_out;
				for (auto deg = 0; deg <= 360; deg += 1) {

					in.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z));
					out.push_back(glm::vec3((radius + span) * cos(deg * DEG_TO_RAD), (radius + span) * sin(deg * DEG_TO_RAD), z));

					fill_in.push_back(glm::vec3((radius + 3) * cos(deg * DEG_TO_RAD), (radius + 3) * sin(deg * DEG_TO_RAD), z));
					fill_out.push_back(glm::vec3((radius + span - 3) * cos(deg * DEG_TO_RAD), (radius + span - 3) * sin(deg * DEG_TO_RAD), z));
				}

				ofFill();
				ofSetColor(239);
				ofBeginShape();
				ofVertices(fill_out);
				ofNextContour(true);
				ofVertices(fill_in);
				ofEndShape();

				ofNoFill();
				ofSetColor(39);
				ofBeginShape();
				ofVertices(out);
				ofNextContour(true);
				ofVertices(in);
				ofEndShape();
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}