#include <SFML/Graphics.hpp>
/*Libreria usada solo en Windows - debe ir antes que las demás librerias*/
#include<windows.h>

#include <algorithm>
#include <GL/glut.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf;
bool firstClick = true;

using namespace std;

void setPixel(int x, int y)
{
	glColor3f(0.0, 0.0, 1.0); //Set pixel to black  
	glBegin(GL_POINTS);
	glVertex2i(x, y); //Set pixel coordinates 
	glEnd();
}

void setPixelDDA(int x, int y)
{
	glColor3f(1.0, 0.0, 0.0); //Set pixel to black  
	glBegin(GL_POINTS);
	glVertex2i(x, y); //Set pixel coordinates 
	glEnd();
}

void lineDDA(GLfloat m) {
	xi += 100;
	xf += 100;

	GLint dx = xf - xi;
	GLint dy = yf - yi;
	GLint steps;
	GLfloat xIncrement, yIncrement, x = xi, y = yi;

	if (abs(dx) > abs(dy)) steps = abs(dx);
	else steps = abs(dy);

	xIncrement = dx / GLfloat(steps);
	yIncrement = dy / GLfloat(steps);
	//setPixel(x + 0.5, y + 0.5);

	for (int i = 1; i <= steps; ++i)
	{
		setPixelDDA((x + 0.5), (y + 0.5));
		x += xIncrement;
		y += yIncrement;
	}
}

//Draw line if X distance is greater than Y
void bresenhamX(int x0, int y0, int x1, int y1, int dx, int dy)
{
	int i, j, k;

	i = 2 * dy - dx;
	j = 2 * dy;
	k = 2 * (dy - dx);
	if (!(x0 < x1)) {
		swap(x0, x1);
		swap(y0, y1);
	}
	setPixel(x0, y0);
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
		setPixel(x0, y0);
	}
}

//Draw line if X distance is lesser than Y
void bresenhamY(int x0, int y0, int x1, int y1, int dx, int dy)
{
	int i, j, k;

	i = 2 * dx - dy;
	j = 2 * dx;
	k = 2 * (dx - dy);
	if (!(y0 < y1)) {
		swap(x0, x1);
		swap(y0, y1);
	}
	setPixel(x0, y0);
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
		setPixel(x0, y0);
	}
}

//Called by mouse(), will call the appropriate function depending on the length of the X and Y axis
void bresenham(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	if (dx >= dy)
		bresenhamX(x0, y0, x1, y1, dx, dy);
	else
		bresenhamY(x0, y0, x1, y1, dx, dy);
}

//Calls Bresenham function when the mouse has traced a line
bool drawLine = false;

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (firstClick) {
			xi = x;
			yi = (wh - y);
			firstClick = false;
			drawLine = false;
		}
		else {
			xf = x;
			yf = (wh - y);
			firstClick = true;
			drawLine = true;
		}
	}
	glutPostRedisplay();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // Press escape to exit.
		exit(0);
		break;
	default:
		break;
	}
}

// Drawing (display) routine.
void drawScene(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set foreground color
	glColor3f(1.0, 1.0, 1.0); // Clear screen to background color.
	glClear(GL_COLOR_BUFFER_BIT);   //Flush created objects to the screen, i.e., force rendering.
	if (drawLine)
	{
		bresenham(xi, yi, xf, yf);
		GLfloat m = (yf - yi) / (xf - xi);
		//DDA(xi, yi, xf, yf);
		lineDDA(m);	
	}
	glFlush();
}

// OpenGL window reshape routine.
void setup()
{
	glViewport(0, 0, ww, wh); // Set viewport size to be entire OpenGL window.
	glMatrixMode(GL_PROJECTION); // Set matrix mode to projection.
	glLoadIdentity(); // Clear current projection matrix to identity.
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh); // Specify the orthographic (or perpendicular) projection, i.e., define the viewing box.
	glMatrixMode(GL_MODELVIEW); // Set matrix mode to modelview.
}

// Main routine: defines window properties, creates window, registers callback routines and begins processing.
int main(int argc, char **argv)
{
	glutInit(&argc, argv); // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode as single-buffered and RGB color.
	glutInitWindowSize(ww, wh); // Set OpenGL window size.
	glutInitWindowPosition(100, 100); // Set position of OpenGL window upper-left corner.
	glutCreateWindow("Line Drawing Algorithms"); // Create OpenGL window with title.
	glutDisplayFunc(drawScene); // Register display routine.
	setup(); // Register reshape routine.
	glutKeyboardFunc(keyInput); // Register keyboard routine.
	glutMouseFunc(mouse); // Begin processing.
	glutMainLoop();
	return 0;
}