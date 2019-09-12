#include "ofApp.h"

ofMesh mesh;
ofVec3f vertices[4];
ofVec3f moveRight(5.0, 0.0, 0.0);
ofVec3f moveLeft(-5.0, 0.0, 0.0);
ofVec3f moveDown(0.0, 5.0, 0.0);
ofVec3f moveUp(0.0, -5.0, 0.0);
ofVec3f centro;
float angulo = 90;
float escalarGrande = 1.1;
float escalarChico = 0.9;

//--------------------------------------------------------------
void ofApp::setup() {

	ofVec3f v1(462, 334, 0);
	ofVec3f v2(462, 434, 0);
	ofVec3f v3(562, 434, 0);
	ofVec3f v4(562, 334, 0);

	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
	vertices[3] = v4;

	mesh.setMode(OF_PRIMITIVE_LINE_LOOP);

	int tamano_del_array = sizeof(vertices);
	int tamano_del_tipo_de_dato = sizeof(ofVec3f);
	int cantidad_elementos = tamano_del_array / tamano_del_tipo_de_dato;

	for (int i = 0; i < 4; i++) {
		mesh.addVertex(vertices[i]);
	}
}

//--------------------------------------------------------------
void ofApp::update() {


	int mitadY = ((vertices[1].y - vertices[0].y) / 2) + vertices[0].y;
	int mitadX = ((vertices[4].x - vertices[0].x) / 2) + vertices[0].x;

	centro.set(mitadX, mitadY, 0);



}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(ofColor::red);
	ofNoFill();
	ofBeginShape();
	ofVertex(400, 0);
	ofVertex(400, 100);
	ofVertex(500, 100);
	ofVertex(500, 0);
	ofEndShape(true);

	ofSetColor(ofColor::blue);
	ofFill();
	mesh.clearVertices();
	for (int i = 0; i < 4; i++) {
		mesh.addVertex(vertices[i]);
	}
	mesh.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {


	if (key == OF_KEY_LEFT) {
		for (int i = 0; i < 4; i++)
		{
			vertices[i] += moveLeft;
		}
	}
	if (key == OF_KEY_RIGHT) {

		for (int i = 0; i < 4; i++)
		{
			vertices[i] += moveRight;
		}
	}
	if (key == OF_KEY_UP) {
		for (int i = 0; i < 4; i++)
		{
			vertices[i] += moveUp;
		}
	}
	if (key == OF_KEY_DOWN) {
		for (int i = 0; i < 4; i++)
		{
			vertices[i] += moveDown;
		}
	}
	if (key == 'm'){
		for (int i = 0; i < 4; i++)
		{
			vertices[i].x = centro.x + (((vertices[i].x - centro.x)*cos(angulo))-((vertices[i].y-centro.y)*sin(angulo)));
			vertices[i].y = centro.y + (((vertices[i].x - centro.x)*sin(angulo))+((vertices[i].y-centro.y)*cos(angulo)));
		}
	}

	if (key == 'h') {
		vertices[0].x = vertices[0].x - ((vertices[0].x * escalarGrande) - vertices[0].x);
		vertices[0].y = vertices[0].y - ((vertices[0].y * escalarGrande) - vertices[0].y);

		vertices[1].x = vertices[1].x - ((vertices[1].x * escalarGrande) - vertices[1].x);
		vertices[1].y = vertices[1].y + ((vertices[1].y * escalarGrande) - vertices[1].y);

		vertices[2].x = vertices[2].x + ((vertices[2].x * escalarGrande) - vertices[2].x);
		vertices[2].y = vertices[2].y + ((vertices[2].y * escalarGrande) - vertices[2].y);

		vertices[3].x = vertices[3].x + ((vertices[3].x * escalarGrande) - vertices[3]).x;
		vertices[3].y = vertices[3].y - ((vertices[3].y * escalarGrande) - vertices[3]).y;
	}
	if (key == 'g') {

		vertices[0].x = vertices[0].x + (vertices[0].x - (vertices[0].x * escalarChico));
		vertices[0].y = vertices[0].y + (vertices[0].y - (vertices[0].y * escalarChico));

		vertices[1].x = vertices[1].x + (vertices[1].x - (vertices[1].x * escalarChico));
		vertices[1].y = vertices[1].y - (vertices[1].y - (vertices[1].y * escalarChico));

		vertices[2].x = vertices[2].x - (vertices[2].x - (vertices[2].x * escalarChico));
		vertices[2].y = vertices[2].y - (vertices[2].y - (vertices[2].y * escalarChico));

		vertices[3].x = vertices[3].x - (vertices[3].x - (vertices[3].x * escalarChico));
		vertices[3].y = vertices[3].y + (vertices[3].y - (vertices[3].y * escalarChico));
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//Draw line if X distance is greater than Y
void ofApp::bresenhamX(int x0, int y0, int x1, int y1, int dx, int dy)
{
	int i, j, k;

	i = 2 * dy - dx;
	j = 2 * dy;
	k = 2 * (dy - dx);
	if (!(x0 < x1)) {
		swap(x0, x1);
		swap(y0, y1);
	}
	ofPoint(x0, y0);
	while (x0 < x1) {
		if (i < 0)
			i += j;
		else {
			if (y0 < y1)
				++y0;
			else
				--y0;
			i += k;
		}
		++x0;
		ofPoint(x0, y0);
	}
}

//Draw line if X distance is lesser than Y
void ofApp::bresenhamY(int x0, int y0, int x1, int y1, int dx, int dy)
{
	int i, j, k;

	i = 2 * dx - dy;
	j = 2 * dx;
	k = 2 * (dx - dy);
	if (!(y0 < y1)) {
		swap(x0, x1);
		swap(y0, y1);
	}
	ofPoint(x0, y0);
	while (y0 < y1) {
		if (i < 0)
			i += j;
		else {
			if (x0 > x1)
				--x0;
			else
				++x0;
			i += k;
		}
		++y0;
		ofPoint(x0, y0);
	}
}

//Called by mouse(), will call the appropriate function depending on the length of the X and Y axis
void ofApp::bresenham(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
		bresenhamX(x0, y0, x1, y1, dx, dy);
	else
		bresenhamY(x0, y0, x1, y1, dx, dy);
}


