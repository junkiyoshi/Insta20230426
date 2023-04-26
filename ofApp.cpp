#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	int len = 25;

	this->face.clear();
	this->frame.clear();

	frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	auto base_noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	this->camera_location = glm::vec3(
		ofMap(ofNoise(base_noise_seed.x, (ofGetFrameNum()) * 0.005), 0, 1, -500, 500),
		ofMap(ofNoise(base_noise_seed.y, (ofGetFrameNum()) * 0.005), 0, 1, -500, 500),
		ofMap(ofNoise(base_noise_seed.z, (ofGetFrameNum()) * 0.005), 0, 1, -500, 500));

	this->target_location = glm::vec3(
		ofMap(ofNoise(base_noise_seed.x, (ofGetFrameNum() + len) * 0.005), 0, 1, -500, 500),
		ofMap(ofNoise(base_noise_seed.y, (ofGetFrameNum() + len) * 0.005), 0, 1, -500, 500),
		ofMap(ofNoise(base_noise_seed.z, (ofGetFrameNum() + len) * 0.005), 0, 1, -500, 500));

	for (int k = 0; k < 36; k++) {

		auto param = glm::vec3(3, 0, 0);
		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto start_index = this->face.getNumVertices();

		ofColor color;
		for (int i = 0; i < len; i++) {

			int index = this->face.getNumVertices();

			auto base_location = glm::vec3(
				ofMap(ofNoise(base_noise_seed.x, (i + ofGetFrameNum()) * 0.005), 0, 1, -500, 500),
				ofMap(ofNoise(base_noise_seed.y, (i + ofGetFrameNum()) * 0.005), 0, 1, -500, 500),
				ofMap(ofNoise(base_noise_seed.z, (i + ofGetFrameNum()) * 0.005), 0, 1, -500, 500));

			auto location = glm::vec3(
				ofMap(ofNoise(noise_seed.x, (i + ofGetFrameNum()) * 0.01), 0, 1, -50, 50),
				ofMap(ofNoise(noise_seed.y, (i + ofGetFrameNum()) * 0.01), 0, 1, -50, 50),
				ofMap(ofNoise(noise_seed.z, (i + ofGetFrameNum()) * 0.01), 0, 1, -50, 50));

			location += base_location;

			this->face.addVertex(location + param);
			this->face.addVertex(location - param);

			color.setHsb(ofMap(k, 0, 36, 0, 255), 255, 255);

			this->face.addColor(ofColor(color, 128));
			this->face.addColor(ofColor(color, 128));

			this->frame.addVertex(location + param);
			this->frame.addVertex(location - param);

			this->frame.addColor(color);
			this->frame.addColor(color);

			if (i > 0) {

				this->face.addIndex(index + 0); this->face.addIndex(index - 1); this->face.addIndex(index - 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index - 1);

				this->frame.addIndex(index + 0); this->frame.addIndex(index - 2);
				this->frame.addIndex(index + 1); this->frame.addIndex(index - 1);
			}
		}

		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 1);
		this->frame.addIndex(frame.getNumVertices() - 1); this->frame.addIndex(frame.getNumVertices() - 2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto camera_location = this->camera_location + glm::vec3(0, 0, 100);

	this->cam.setPosition(camera_location);
	this->cam.setTarget(target_location);
	this->cam.lookAt(target_location);

	this->cam.begin();

	this->face.drawFaces();
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}