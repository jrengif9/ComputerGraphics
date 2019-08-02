#include <SFML/Graphics.hpp>
/*Libreria usada solo en Windows - debe ir antes que las demás librerias*/
#include<windows.h>
/*Libreria del OpenGL*/
#include<GL/glut.h>


using namespace sf;

#include<stdlib.h>
#include<stdio.h>

float xInit, xEnd, yInit, yEnd;

void display(void)
{
	float dy, dx, step, x, y, k, Xin, Yin;
	dx = xEnd - xInit;
	dy = yEnd - yInit;

	if (abs(dx) > abs(dy))
	{
		step = abs(dx);
	}
	else
		step = abs(dy);

	Xin = dx / step;
	Yin = dy / step;

	x = xInit;
	y = yInit;
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

	for (k = 1; k <= step; k++)
	{
		x = x + Xin;
		y = y + Yin;

		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
	}


	glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
	printf("Enter the value of xInit : ");
	scanf_s("%f", &xInit);
	printf("Enter the value of yInit : ");
	scanf_s("%f", &yInit);
	printf("Enter the value of xEnd : ");
	scanf_s("%f", &xEnd);
	printf("Enter the value of yEnd : ");
	scanf_s("%f", &yEnd);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("DDA Line Algo");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}