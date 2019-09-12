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
int numpuntos = 0;
ofVec3f puntos[1000];
bool adentro1 = false;
bool adentro2 = false;
bool adentro3 = false;
ofVec3f c1(875, 175, 0);
ofVec3f c2(300, 350, 0);
ofVec3f c3(525, 625, 0);
int turno = 0;

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

//--------------------------------------------------------------3
void ofApp::update() {

	float mitadY = ((vertices[2].y - vertices[0].y)/2) + vertices[0].y;
	float mitadX = ((vertices[3].x - vertices[1].x)/2) + vertices[1].x;

	centro.set(mitadX, mitadY, 0);

	if (turno == 1) {
		bresenham(centro.x, centro.y, c1.x, c1.y);
	}
	if (turno == 2) {
		bresenham(centro.x, centro.y, c2.x, c2.y);
	}
	if (turno == 3) {
		bresenham(centro.x, centro.y, c3.x, c3.y);
	}
	if (turno == 4) {
		turno = 0;
	}


	
	if (adentro1 == false) {
		adentro1 = adentro(vertices, ofVec3f(800, 100, 0), ofVec3f(800, 250, 0), ofVec3f(950, 250, 0), ofVec3f(950, 100, 0));
	}
	else {
		adentro1 = true;
	}
	if (adentro2 == false) {
		adentro2 = adentro(vertices, ofVec3f(300, 300, 0), ofVec3f(250, 350, 0), ofVec3f(300, 400, 0), ofVec3f(350, 350, 0));
	} else {
		adentro2 = true;
	}
	if (adentro3 == false) {
		adentro3 = adentro(vertices, ofVec3f(500, 600, 0), ofVec3f(500, 650, 0), ofVec3f(550, 650, 0), ofVec3f(550, 600, 0));
	} else {
		adentro3 = true;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofPushMatrix();
	if (adentro1 == false) {
		ofSetColor(ofColor::red);
		ofNoFill();
		ofBeginShape();
		ofVertex(800, 100);
		ofVertex(800, 250);
		ofVertex(950, 250);
		ofVertex(950, 100);
		ofEndShape(true);
	}

	if (adentro2 == false) {
		ofSetColor(ofColor::red);
		ofNoFill();
		ofBeginShape();
		ofVertex(300, 300);
		ofVertex(250, 350);
		ofVertex(300, 400);
		ofVertex(350, 350);
		ofEndShape(true);
	}

	if (adentro3 == false) {
		ofSetColor(ofColor::red);
		ofNoFill();
		ofBeginShape();
		ofVertex(500, 600);
		ofVertex(500, 650);
		ofVertex(550, 650);
		ofVertex(550, 600);
		ofEndShape(true);
	}

	ofSetColor(ofColor::blue);
	ofFill();
	mesh.clearVertices();
	for (int i = 0; i < 4; i++) {
		mesh.addVertex(vertices[i]);
	}

	mesh.draw();

	if ( turno != 0) {
		for (int i = 0; i < numpuntos; i++) {
			ofCircle(puntos[i].x, puntos[i].y, puntos[i].z);
		}
	}

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
			//vertices[i].x = vertices[3].x + (((vertices[i].x-vertices[3].x)*cos(angulo))-((vertices[i].y-vertices[3].y)*sin(angulo)));
			//vertices[i].y = vertices[3].y + (((vertices[i].x-vertices[3].x)*sin(angulo))+((vertices[i].y-vertices[3].y)*cos(angulo)));

			ofVec2f r(vertices[i].x, vertices[i].y);
			r.rotate(10,ofVec2f(centro.x,centro.y));

			vertices[i] = ofVec3f(r.x, r.y, 0);
			
		}
	}

	if (key == 'h') {

		for (int i = 0; i < 4; i++)
		{
			vertices[i].x = vertices[i].x * escalarGrande;
			vertices[i].y = vertices[i].y * escalarGrande;
		}
	}
	if (key == 'g') {

		for (int i = 0; i < 4; i++)
		{
			vertices[i].x = vertices[i].x * escalarChico;
			vertices[i].y = vertices[i].y * escalarChico;
		}
	}
	if (key == 'j') {
		turno += 1;
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
	numpuntos += 1;
	puntos[numpuntos-1]= ofVec3f(x0, y0, 1);
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
		puntos[numpuntos - 1] = ofVec3f(x0, y0, 1);
		numpuntos += 1;
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
	numpuntos += 1;
	puntos[numpuntos - 1] = ofVec3f(x0, y0, 1);
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
		puntos[numpuntos - 1] = ofVec3f(x0, y0, 1);
		numpuntos += 1;
	}
}

//Called by mouse(), will call the appropriate function depending on the length of the X and Y axis
void ofApp::bresenham(int x0, int y0, int x1, int y1)
{
	numpuntos = 0;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
		bresenhamX(x0, y0, x1, y1, dx, dy);
	else
		bresenhamY(x0, y0, x1, y1, dx, dy);
}

bool ofApp::adentro(ofVec3f vertices[4], ofVec3f v1, ofVec3f v2, ofVec3f v3, ofVec3f v4) {

	int cont = 0;
	for(int i = 0; i < 4; i++) {
		if ((vertices[i].x >= v2.x && vertices[i].x <= v4.x) && (vertices[i].y >= v1.y && vertices[i].y <= v3.y)) {
			cont += 1;
		}
	}
	
	if (cont == 4) {
		return true;
	}
	else {
		return false;
	}

}


