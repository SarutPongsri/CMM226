// mouse motion function callback demonstration
// created by suriyong L.
// may 20, 2006
// august 22, 2012
// simulated object is triangle at 0,0,0
// the object is moved to mouse position
// it is still moved when the left key is pressed

#include "stdafx.h"
#include <GL/glut.h> // (or others, depending on the system in use)
#include <stdio.h>
#include <conio.h>
#include <cmath>

#define RED 1.0,0.0,0.0 // RGB code for red color
#define WHITE_A 1.0,1.0,1.0,1.0 //REG code for white and alpha
#define BLACK_A 0.0,0.0,0.0,0.0
#define GREEN 0.159,1.0,0.620,1.0



#define Cy_PI 3.14159265
#define DEF_D 5

int colorMode = 0;
float phi = 0;
float deltaPhi = 0;
// WCS volume limit
float left = -9.0;
float right = 9.0;
float bottom = -9.0;
float top = 9.0;
float znear = 18;
float zfar = -18.0;

// RCS for window limit
int win_width = 1024;
int win_height = 768;
float win_position_x = 10;
float win_position_y = 10;

//Build ChessBoard
float xView = 0;
float yView = -5;
float zView = -4;
float x_Point = -10;
float y_Point = 0.1;
float z_Point = 10;
float xLookAt = 0;
float yLookAt = 0;
float zLookAt = 1;

// mouse position start
float xstart = 0;
float ystart = 0;

/* some_where_on_board */
float j = 0, k = 0, l = 0;
float type[6] = { 1,2,3,4,5,6 }; //type of pawn
int v = 0, s = 0;
double poX[] = { 1,2,3,4,5,6,7,8 };
double poZ[] = { 1,2,3,4,5,6,7,8 };
int ChoTyp = 0;


/* colorButton */
int reD[17] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
int rEd[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
/*ช่อง 64 ช่อง*/
float aRr[16] = { 1,2,3,4,5,6,7,8,9, 10, 11, 12, 13, 14, 15, 16 };
float aRr2[16] = { 17, 18, 19, 20, 21, 22, 23, 24 , 25, 26, 27, 28, 29, 30, 31, 32 };
float aRr3[16] = { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48 };
float aRr4[16] = { 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64 };
int arR2[8] = { 1,2,3,4,5,6,7,8 };

/* Choose_Act */
int select = 0;
int go = 0;
/* Set */
int ready = 0;
float states;
void GreenArea()
{
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);

	/* TOP */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point);
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);
	glVertex3f(x_Point, y_Point, z_Point - 2);
	/* BOTTOM */
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);
	glVertex3f(x_Point, -y_Point, z_Point - 2);
	/* FRONT */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
										   /* BACK */
	glVertex3f(x_Point, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point - 2);//top right corner
											   /* LEFT */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
										   /* RIGHT */
	glVertex3f(x_Point + 2, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);//top right corner
	glEnd();
}
void BlueArea()
{
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);

	/* TOP */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point);
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);
	glVertex3f(x_Point, y_Point, z_Point - 2);
	/* BOTTOM */
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);
	glVertex3f(x_Point, -y_Point, z_Point - 2);
	/* FRONT */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
										   /* BACK */
	glVertex3f(x_Point, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point - 2);//top right corner
											   /* LEFT */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
										   /* RIGHT */
	glVertex3f(x_Point + 2, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);//top right corner
	glEnd();
}

/* Position */
float A1;
float A2;
float A3;
float A4;
float A5;
float A6;
float A7;
float A8;
float B1;
float B2;
float B3;
float B4;
float B5;
float B6;
float B7;
float B8;
float C1;
float C2;
float C3;
float C4;
float C5;
float C6;
float C7;
float C8;
float D1;
float D2;
float D3;
float D4;
float D5;
float D6;
float D7;
float D8;
float E1;
float E2;
float E3;
float E4;
float E5;
float E6;
float E7;
float E8;
float F1;
float F2;
float F3;
float F4;
float F5;
float F6;
float F7;
float F8;
float G1;
float G2;
float G3;
float G4;
float G5;
float G6;
float G7;
float G8;
float H1;
float H2;
float H3;
float H4;
float H5;
float H6;
float H7;
float H8;

/*float arr[7][8][3]=
{
{
{ 7,0.1,9 },{ 5,0.1,9 },{ 3,0.1,9 },{ 1,0.1,9 },{ -1,0.1,9 },{ -3,0.1,9 },{ -5,0.1,9 },{ -7,0.1,9 }
},
{
{ 7,0.1,5 },{ 5,0.1,5 },{ 3,0.1,5 },{ 1,0.1,5 },{ -1,0.1,5 },{ -3,0.1,5 },{ -5,0.1,5 },{ -7,0.1,5 }
},
{
{ 7,0.1,3 },{ 5,0.1,3 },{ 3,0.1,3 },{ 1,0.1,3 },{ -1,0.1,3 },{ -3,0.1,3 },{ -5,0.1,3 },{ -7,0.1,3 }
},
{
{ 7,0.1,1 },{ 5,0.1,1 },{ 3,0.1,1 },{ 1,0.1,1 },{ -1,0.1,1 },{ -3,0.1,1 },{ -5,0.1,1 },{ -7,0.1,1 }
},
{
{ 7,0.1,-1 },{ 5,0.1,-1 },{ 3,0.1,-1 },{ 1,-0.1,1 },{ -1,0.1-1 },{ -3,0.1,-1 },{ -5,0.1,-1 },{ -7,0.1,-1 }
},
{
{ 7,0.1,-3 },{ 5,0.1,-3 },{ 3,0.1,-3 },{ 1,0.1,-3 },{ -1,0.1,-3 },{ -3,0.1,-3 },{ -5,0.1,-3 },{ -7,0.1,-3 }
},
{
{ 7,0.1,-5 },{ 5,0.1,-5 },{ 3,0.1,-5 },{ 1,0.1,-5 },{ -1,0.1,-5 },{ -3,0.1,-5 },{ -5,0.1,-5 },{ -7,0.1,-5 }
}
};
*/
float xUnitRatio = (right - left) / (float)win_width;
float yUnitRatio = (top - bottom) / (float)win_height;
int xMovePixel;
int yMovePixel;
float xMoveUnit;
float yMoveUnit;


void motion(int x, int y) {
	/*glTranslatef((x - xstart)*right / (float)win_width, (win_height - y - ystart)*top / (float)win_height, 0);
	xstart = x;
	ystart = win_height - y;
	printf("motion x=%3.3f, y=%3.3f\n", xstart, ystart);
	*/glutPostRedisplay();
}

void init(void) {
	glClearColor(GREEN); // Set display-window color to white.

	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glLoadIdentity();
	glOrtho(left, right, bottom, top, znear, zfar);
}
//Build Circle
/*
float pi = 3.14159265;
void sphere(float radius, int nslice, int nstack) {
glBegin(GL_QUADS);
for (int j = 0; j < nslice; j++) {
for (int i = 0; i < nstack; i++) {
float thetar = 2 * pi * i / nslice;
float iphi = pi * j / nstack;
float x = radius * sin(iphi)*cos(thetar);
float y = radius * cos(iphi);
float z = radius * sin(iphi)*sin(thetar);
glVertex3f(x, y, z);
float iphi_plus = pi * (j + 1) / nstack;
x = radius * sin(iphi_plus)*cos(thetar);
y = radius * cos(iphi_plus);
z = radius * sin(iphi_plus)*sin(thetar);
glVertex3f(x, y, z);
}
}
glEnd();
}
*/


int color = 0;

void square_black(void) {

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);

	/* TOP */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point);
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);
	glVertex3f(x_Point, y_Point, z_Point - 2);
	/* BOTTOM */
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);
	glVertex3f(x_Point, -y_Point, z_Point - 2);
	/* FRONT */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
										   /* BACK */
	glVertex3f(x_Point, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point - 2);//top right corner
											   /* LEFT */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
										   /* RIGHT */
	glVertex3f(x_Point + 2, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);//top right corner
	glEnd();
	color = 0;
}
void square_white(void) {
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	/* TOP */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point);
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);
	glVertex3f(x_Point, y_Point, z_Point - 2);
	/* BOTTOM */
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);
	glVertex3f(x_Point, -y_Point, z_Point - 2);
	/* FRONT */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
										   /* BACK */
	glVertex3f(x_Point, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point - 2);//top right corner
											   /* LEFT */
	glVertex3f(x_Point, y_Point, z_Point);//top right corner
	glVertex3f(x_Point, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point, -y_Point, z_Point);//top right corner
										   /* RIGHT */
	glVertex3f(x_Point + 2, y_Point, z_Point);//top right corner
	glVertex3f(x_Point + 2, y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point - 2);//top right corner
	glVertex3f(x_Point + 2, -y_Point, z_Point);//top right corner
	glEnd();
	color = 1;
}

/* BuildCylinderT_Yong */
/*Red*/
void Pawn1(float poXpa1, float poYpa1, float poZpa1) {
	glTranslatef(poX[1], 0.1, poZ[3]);
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn
	ChoTyp = 1;

	// ฝาปิด(ล่าง)
	/*
	glBegin(GL_POLYGON);
	for (int b = 0; b < 20; b++)
	{
	float theta = b * (2 * Cy_PI / 20);
	glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
	}*/
}
void Pawn2() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn
	ChoTyp = 2;

	// ฝาปิด(ล่าง)
	/*
	glBegin(GL_POLYGON);
	for (int b = 0; b < 20; b++)
	{
	float theta = b * (2 * Cy_PI / 20);
	glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
	}*/
}
void Pawn3() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn
	ChoTyp = 3;

	// ฝาปิด(ล่าง)
	/*
	glBegin(GL_POLYGON);
	for (int b = 0; b < 20; b++)
	{
	float theta = b * (2 * Cy_PI / 20);
	glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
	}*/
}
void Pawn4() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 4; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Pawn5() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 5; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Pawn6() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn
	ChoTyp = 6;

	// ฝาปิด(ล่าง)
	/*
	glBegin(GL_POLYGON);
	for (int b = 0; b < 20; b++)
	{
	float theta = b * (2 * Cy_PI / 20);
	glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
	}*/
}
void Pawn7() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Pawn8() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Ship1() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.5f, 0.5f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + 1.3, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + 1.8, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + 1.3, z_Cy_Point*1.3); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*0.1, y_Point + 2.1, z_Cy_Point*0.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 1.8, z_Cy_Point); //เส้นล่าง }
	}
	/* Top */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta) / 1.5;
		z_Cy_Point = sin(theta) / 1.5;
		glVertex3f(x_Cy_Point*0.1, y_Point + 2.6, z_Cy_Point*0.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 2.1, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	type[2] = 1;
	ChoTyp = 9;
}
void Ship2() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.5f, 0.5f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + 1.3, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + 1.8, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + 1.3, z_Cy_Point*1.3); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*0.1, y_Point + 2.1, z_Cy_Point*0.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 1.8, z_Cy_Point); //เส้นล่าง }
	}
	/* Top */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta) / 1.5;
		z_Cy_Point = sin(theta) / 1.5;
		glVertex3f(x_Cy_Point*0.1, y_Point + 2.6, z_Cy_Point*0.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 2.1, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	type[2] = 1;
	ChoTyp = 10;
}
void Mha1() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(0.5f, 0.5f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.3, y_Point + 2.0, z_Cy_Point / 1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นล่าง }
	}

	glEnd();
	glPushMatrix(); //Body
	glTranslatef(-4.1, 0, -8);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(4.8, 5, 9); //LTF
	glVertex3f(3.3, 5, 9); //RTF
	glVertex3f(3.3, 5, 7); //RTB
	glVertex3f(4.8, 5, 7); //LTB
	glVertex3f(4.8, 5, 9); //LTF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.5, 5, 9); //RTF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(3.5, 5, 7); //RTB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(4.8, 5, 7); //LTB
	glEnd();
	glPopMatrix();
	glPushMatrix();//Head
				   //glColor3f(0, 1, 0);
	glScaled(.8, .7, .7);
	glRotatef(45, 1, 0, 0);
	glTranslatef(-4.1, 0, -13);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(5, 6, 9); //LTF
	glVertex3f(3.3, 6, 9); //RTF
	glVertex3f(3, 6, 6); //RTB
	glVertex3f(5.3, 6, 6); //LTB
	glVertex3f(5, 6, 9); //LTF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, 6, 9); //RTF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(3.3, 6, 7); //RTB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, 6, 7); //LTB
	glEnd();
	glPopMatrix();
	glPopMatrix();
	type[3] = 1;
	ChoTyp = 11;
}
void Mha2() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(0.5f, 0.5f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.3, y_Point + 2.0, z_Cy_Point / 1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นล่าง }
	}

	glEnd();
	glPushMatrix(); //Body
	glTranslatef(-4.1, 0, -8);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(4.8, 5, 9); //LTF
	glVertex3f(3.3, 5, 9); //RTF
	glVertex3f(3.3, 5, 7); //RTB
	glVertex3f(4.8, 5, 7); //LTB
	glVertex3f(4.8, 5, 9); //LTF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.5, 5, 9); //RTF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(3.5, 5, 7); //RTB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(4.8, 5, 7); //LTB
	glEnd();
	glPopMatrix();
	glPushMatrix();//Head
				   //glColor3f(0, 1, 0);
	glScaled(.8, .7, .7);
	glRotatef(45, 1, 0, 0);
	glTranslatef(-4.1, 0, -13);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(5, 6, 9); //LTF
	glVertex3f(3.3, 6, 9); //RTF
	glVertex3f(3, 6, 6); //RTB
	glVertex3f(5.3, 6, 6); //LTB
	glVertex3f(5, 6, 9); //LTF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, 6, 9); //RTF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(3.3, 6, 7); //RTB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, 6, 7); //LTB
	glEnd();
	glPopMatrix();
	glPopMatrix();
	type[3] = 1;
	ChoTyp = 12;
}
void Juk1() {
	glPushMatrix();
	glScaled(.3, .3, .3);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 19, y_Point + 3.2, z_Cy_Point / 19); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นล่าง }
	}

	glEnd();
	glPopMatrix();
	type[4] = 1;
	ChoTyp = 13;
}
void Kon1() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 19, y_Point + 3.2, z_Cy_Point / 19); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นล่าง }
	}

	glEnd();
	glPopMatrix();
	type[5] = 1;
	ChoTyp = 14;
}
void Kon2() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 19, y_Point + 3.2, z_Cy_Point / 19); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นล่าง }
	}

	glEnd();
	glPopMatrix();
	type[5] = 1;
	ChoTyp = 15;
}
void Kun1() {
	glPushMatrix();
	glScaled(.7, .7, .7);
	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 19, y_Point + 3.2, z_Cy_Point / 19); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นล่าง }
	}

	glEnd();
	glPopMatrix();
	type[6] = 1;
	ChoTyp = 16;
}

/*Blue*/
void Pawn9() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn
	ChoTyp = 2;

	// ฝาปิด(ล่าง)
	/*
	glBegin(GL_POLYGON);
	for (int b = 0; b < 20; b++)
	{
	float theta = b * (2 * Cy_PI / 20);
	glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
	}*/
}
void Pawn10() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn
	ChoTyp = 3;

	// ฝาปิด(ล่าง)
	/*
	glBegin(GL_POLYGON);
	for (int b = 0; b < 20; b++)
	{
	float theta = b * (2 * Cy_PI / 20);
	glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
	}*/
}
void Pawn11() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 4; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Pawn12() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 5; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Pawn13() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn
	ChoTyp = 6;

	// ฝาปิด(ล่าง)
	/*
	glBegin(GL_POLYGON);
	for (int b = 0; b < 20; b++)
	{
	float theta = b * (2 * Cy_PI / 20);
	glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
	}*/
}
void Pawn14() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Pawn15() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Pawn16() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .4, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	// ฝาปิด(บน)
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.0);
	glScaled(.5, .5, .5);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_POLYGON);
	for (int b = 0; b < 360; b++)
	{
		float theta = b * (2 * Cy_PI / 360);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex2f(x_Cy_Point, z_Cy_Point);

	}
	glEnd();
	glPopMatrix();
	type[1] = 1; //pawn

				 // ฝาปิด(ล่าง)
				 /*
				 glBegin(GL_POLYGON);
				 for (int b = 0; b < 20; b++)
				 {
				 float theta = b * (2 * Cy_PI / 20);
				 glVertex3f(x_Cy_Point, y_Point+1, z_Cy_Point);
				 }*/
}
void Ship3() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.5f, 0.5f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + 1.3, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + 1.8, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + 1.3, z_Cy_Point*1.3); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*0.1, y_Point + 2.1, z_Cy_Point*0.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 1.8, z_Cy_Point); //เส้นล่าง }
	}
	/* Top */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta) / 1.5;
		z_Cy_Point = sin(theta) / 1.5;
		glVertex3f(x_Cy_Point*0.1, y_Point + 2.6, z_Cy_Point*0.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 2.1, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	type[2] = 1;
	ChoTyp = 9;
}
void Ship4() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(1.0f, 0.5f, 0.5f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + 1.3, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + 1.8, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + 1.3, z_Cy_Point*1.3); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*0.1, y_Point + 2.1, z_Cy_Point*0.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 1.8, z_Cy_Point); //เส้นล่าง }
	}
	/* Top */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta) / 1.5;
		z_Cy_Point = sin(theta) / 1.5;
		glVertex3f(x_Cy_Point*0.1, y_Point + 2.6, z_Cy_Point*0.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 2.1, z_Cy_Point); //เส้นล่าง }
	}
	glEnd();
	glPopMatrix();
	type[2] = 1;
	ChoTyp = 10;
}
void Mha3() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(0.5f, 0.5f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.3, y_Point + 2.0, z_Cy_Point / 1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นล่าง }
	}

	glEnd();
	glPushMatrix(); //Body
	glTranslatef(-4.1, 0, -8);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(4.8, 5, 9); //LTF
	glVertex3f(3.3, 5, 9); //RTF
	glVertex3f(3.3, 5, 7); //RTB
	glVertex3f(4.8, 5, 7); //LTB
	glVertex3f(4.8, 5, 9); //LTF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.5, 5, 9); //RTF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(3.5, 5, 7); //RTB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(4.8, 5, 7); //LTB
	glEnd();
	glPopMatrix();
	glPushMatrix();//Head
				   //glColor3f(0, 1, 0);
	glScaled(.8, .7, .7);
	glRotatef(45, 1, 0, 0);
	glTranslatef(-4.1, 0, -13);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(5, 6, 9); //LTF
	glVertex3f(3.3, 6, 9); //RTF
	glVertex3f(3, 6, 6); //RTB
	glVertex3f(5.3, 6, 6); //LTB
	glVertex3f(5, 6, 9); //LTF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, 6, 9); //RTF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(3.3, 6, 7); //RTB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, 6, 7); //LTB
	glEnd();
	glPopMatrix();
	glPopMatrix();
	type[3] = 1;
	ChoTyp = 11;
}
void Mha4() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(0.5f, 0.5f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .3, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.3, y_Point + 2.0, z_Cy_Point / 1.3); //เส้นบน สูง 
		glVertex3f(x_Cy_Point*1.3, y_Point + .8, z_Cy_Point*1.3); //เส้นล่าง }
	}

	glEnd();
	glPushMatrix(); //Body
	glTranslatef(-4.1, 0, -8);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(4.8, 5, 9); //LTF
	glVertex3f(3.3, 5, 9); //RTF
	glVertex3f(3.3, 5, 7); //RTB
	glVertex3f(4.8, 5, 7); //LTB
	glVertex3f(4.8, 5, 9); //LTF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.5, 5, 9); //RTF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(3.5, 5, 7); //RTB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(4.8, 5, 7); //LTB
	glEnd();
	glPopMatrix();
	glPushMatrix();//Head
				   //glColor3f(0, 1, 0);
	glScaled(.8, .7, .7);
	glRotatef(45, 1, 0, 0);
	glTranslatef(-4.1, 0, -13);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, .5, 9); //LBF
	glVertex3f(5, 6, 9); //LTF
	glVertex3f(3.3, 6, 9); //RTF
	glVertex3f(3, 6, 6); //RTB
	glVertex3f(5.3, 6, 6); //LTB
	glVertex3f(5, 6, 9); //LTF
	glVertex3f(3.3, .5, 9); //RBF
	glVertex3f(3.3, 6, 9); //RTF
	glVertex3f(3.3, .5, 7); //RBB
	glVertex3f(3.3, 6, 7); //RTB
	glVertex3f(5, .5, 7); //LBB
	glVertex3f(5, 6, 7); //LTB
	glEnd();
	glPopMatrix();
	glPopMatrix();
	type[3] = 1;
	ChoTyp = 12;
}
void Juk2() {
	glPushMatrix();
	glScaled(.3, .3, .3);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 19, y_Point + 3.2, z_Cy_Point / 19); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นล่าง }
	}

	glEnd();
	glPopMatrix();
	type[4] = 1;
	ChoTyp = 13;
}
void Kon3() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 19, y_Point + 3.2, z_Cy_Point / 19); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นล่าง }
	}

	glEnd();
	glPopMatrix();
	type[5] = 1;
	ChoTyp = 14;
}
void Kon4() {
	glPushMatrix();
	glScaled(.5, .5, .5);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 19, y_Point + 3.2, z_Cy_Point / 19); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นล่าง }
	}

	glEnd();
	glPopMatrix();
	type[5] = 1;
	ChoTyp = 15;
}
void Kun2() {
	glPushMatrix();
	glScaled(.7, .7, .7);
	//glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	float x_Cy_Point = 0;
	float y_Cy_Point = 0;
	float z_Cy_Point = 0;
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + 0, z_Cy_Point); //เส้นล่าง }
	}
	/* Body */
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นบน สูง 
		glVertex3f(x_Cy_Point, y_Point + .2, z_Cy_Point); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.5, y_Point + .5, z_Cy_Point / 1.5); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.5, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point * 1.1, y_Point + 1.9, z_Cy_Point * 1.1); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 1.4, y_Point + 2.1, z_Cy_Point / 1.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 2.4, y_Point + 2.3, z_Cy_Point / 2.4); //เส้นล่าง }
	}
	for (int b = 0; b <= 20; b++)
	{
		float theta = (b * 2 * Cy_PI / 20);
		x_Cy_Point = cos(theta);
		z_Cy_Point = sin(theta);
		glVertex3f(x_Cy_Point / 19, y_Point + 3.2, z_Cy_Point / 19); //เส้นบน สูง 
		glVertex3f(x_Cy_Point / 4.8, y_Point + 3.0, z_Cy_Point / 4.8); //เส้นล่าง }
	}

	glEnd();
	glPopMatrix();
	type[6] = 1;
	ChoTyp = 16;
}

void mouse(int button, int state, int x, int y) {


	/* -CharButt- */
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		xMovePixel = x - xstart;
		yMovePixel = win_height - y - ystart;
		xMoveUnit = xMovePixel * xUnitRatio;
		yMoveUnit = yMovePixel * yUnitRatio;
		//glTranslatef(xMoveUnit, yMoveUnit, 0);  /* yMoveUnit - ค่าแกนวายใหม่ ,xMoveUnit - ค่าแกนเอ็กซ์ใหม่ */
		/* - ChangColorChar - */
		{	/* 1 Column*/
			if (xMoveUnit >= 3 && xMoveUnit <= 4.5 && yMoveUnit >= 5 && yMoveUnit <= 6.5) // A1
			{
				reD[1] = 255;
				aRr[1] = 1;

			}
			else
			{
				reD[1] = 0;
				aRr[1] = 0;
				aRr[2] = 0;
				aRr[3] = 0;
				aRr[4] = 0;
				aRr[5] = 0;
				aRr[6] = 0;
				aRr[7] = 0;
				aRr[8] = 0;
				aRr[9] = 0;
				aRr[10] = 0;
				aRr[11] = 0;
				aRr[12] = 0;
				aRr[13] = 0;
				aRr[14] = 0;
				aRr[15] = 0;
				aRr[16] = 0;
				aRr2[17] = 0;
				aRr2[18] = 0;
				aRr2[19] = 0;
				aRr2[20] = 0;
				aRr2[21] = 0;
				aRr2[22] = 0;
				aRr2[23] = 0;
				aRr2[24] = 0;
				aRr2[25] = 0;
				aRr2[26] = 0;
				aRr2[27] = 0;
				aRr2[28] = 0;
				aRr2[29] = 0;
				aRr2[30] = 0;
				aRr2[31] = 0;
				aRr2[32] = 0;
				aRr3[33] = 0;
				aRr3[34] = 0;
				aRr3[35] = 0;
				aRr3[36] = 0;
				aRr3[37] = 0;
				aRr3[38] = 0;
				aRr3[39] = 0;
				aRr3[40] = 0;
				aRr3[41] = 0;
				aRr3[42] = 0;
				aRr3[43] = 0;
				aRr3[44] = 0;
				aRr3[45] = 0;
				aRr3[46] = 0;
				aRr3[47] = 0;
				aRr3[48] = 0;
				aRr4[49] = 0;
				aRr4[50] = 0;
				aRr4[51] = 0;
				aRr4[52] = 0;
				aRr4[53] = 0;
				aRr4[54] = 0;
				aRr4[55] = 0;
				aRr4[56] = 0;
				aRr4[57] = 0;
				aRr4[58] = 0;
				aRr4[59] = 0;
				aRr4[60] = 0;
				aRr4[61] = 0;
				aRr4[62] = 0;
				aRr4[63] = 0;
				aRr4[64] = 0;
				
			}
			if (xMoveUnit >= 4.5 && xMoveUnit <= 6 && yMoveUnit >= 5 && yMoveUnit <= 6.5) // B1
			{
				reD[1] = 255;
				aRr[2] = 1;

			}
			else
			{
				reD[2] = 0;
			}
			if (xMoveUnit >= 6 && xMoveUnit <= 7.5 && yMoveUnit >= 5 && yMoveUnit <= 6.5) // C1
			{
				reD[1] = 255;
				aRr[3] = 1;

			}
			else
			{
				reD[3] = 0;
			}
			if (xMoveUnit >= 7.5 && xMoveUnit <= 9 && yMoveUnit >= 5 && yMoveUnit <= 6.5) // D1
			{
				reD[1] = 255;
				aRr[4] = 1;

			}
			else
			{
				reD[4] = 0;
			}
			if (xMoveUnit >= 9 && xMoveUnit <= 10.5 && yMoveUnit >= 5 && yMoveUnit <= 6.5) // E1
			{
				reD[1] = 255;
				aRr[5] = 1;

			}
			else
			{
				reD[5] = 0;
			}
			if (xMoveUnit >= 10.5 && xMoveUnit <= 12 && yMoveUnit >= 5 && yMoveUnit <= 6.5) // F1
			{
				reD[1] = 255;
				aRr[6] = 1;

			}
			else
			{
				reD[6] = 0;
			}
			if (xMoveUnit >= 12 && xMoveUnit <= 13.5 && yMoveUnit >= 5 && yMoveUnit <= 6.5) // G1
			{
				reD[1] = 255;
				aRr[7] = 1;

			}
			else
			{
				reD[7] = 0;
			}
			if (xMoveUnit >= 13.5 && xMoveUnit <= 15 && yMoveUnit >= 5 && yMoveUnit <= 6.5) // H1
			{
				reD[1] = 255;
				aRr[8] = 1;

			}
			else
			{
				reD[8] = 0;
			}
			/* 2 Column*/
			if (xMoveUnit >= 3 && xMoveUnit <= 4.5 && yMoveUnit >= 6.5 && yMoveUnit <= 8) // A2
			{
				reD[1] = 255;
				aRr[9] = 1;

			}
			else
			{
				reD[9] = 0;
			}
			if (xMoveUnit >= 4.5 && xMoveUnit <= 6 && yMoveUnit >= 6.5 && yMoveUnit <= 8) // B2
			{
				reD[1] = 255;
				aRr[10] = 1;

			}
			else
			{
				reD[10] = 0;
			}
			if (xMoveUnit >= 6 && xMoveUnit <= 7.5 && yMoveUnit >= 6.5 && yMoveUnit <= 8) // C2
			{
				reD[1] = 255;
				aRr[11] = 1;

			}
			else
			{
				reD[11] = 0;
			}
			if (xMoveUnit >= 7.5 && xMoveUnit <= 9 && yMoveUnit >= 6.5 && yMoveUnit <= 8) // D2
			{
				reD[1] = 255;
				aRr[12] = 1;

			}
			else
			{
				reD[12] = 0;
			}
			if (xMoveUnit >= 9 && xMoveUnit <= 10.5 && yMoveUnit >= 6.5 && yMoveUnit <= 8) // E2
			{
				reD[1] = 255;
				aRr[13] = 1;

			}
			else
			{
				reD[13] = 0;
			}
			if (xMoveUnit >= 10.5 && xMoveUnit <= 12 && yMoveUnit >= 6.5 && yMoveUnit <= 8) // F2
			{
				reD[1] = 255;
				aRr[14] = 1;

			}
			else
			{
				reD[14] = 0;
			}
			if (xMoveUnit >= 12 && xMoveUnit <= 13.5 && yMoveUnit >= 6.5 && yMoveUnit <= 8) // G2
			{
				reD[1] = 255;
				aRr[15] = 1;

			}
			else
			{
				reD[15] = 0;
			}
			if (xMoveUnit >= 13.5 && xMoveUnit <= 15 && yMoveUnit >= 6.5 && yMoveUnit <= 8) // H2
			{
				reD[1] = 255;
				aRr[16] = 1;

			}
			else
			{
				reD[16] = 0;
			}
			/* 3 Column */
			if (xMoveUnit >= 3 && xMoveUnit <= 4.5 && yMoveUnit >= 8 && yMoveUnit <= 9.3) // A3
			{
				reD[1] = 255;
				aRr2[17] = 1;
				ready = 13;
			}
			
			else
			{
				reD[17] = 0;
			}
			
			if (xMoveUnit >= 4.5 && xMoveUnit <= 6 && yMoveUnit >= 8 && yMoveUnit <= 9.3) // B3
			{
				reD[1] = 255;
				aRr2[18] = 1;

			}
			else
			{
				reD[18] = 0;
			}
			if (xMoveUnit >= 6 && xMoveUnit <= 7.5 && yMoveUnit >= 8 && yMoveUnit <= 9.3) // C3
			{
				reD[1] = 255;
				aRr2[19] = 1;

			}
			else
			{
				reD[19] = 0;
			}
			if (xMoveUnit >= 7.5 && xMoveUnit <= 9 && yMoveUnit >= 8 && yMoveUnit <= 9.3) // D3
			{
				reD[1] = 255;
				aRr2[20] = 1;

			}
			else
			{
				reD[20] = 0;
			}
			if (xMoveUnit >= 9 && xMoveUnit <= 10.5 && yMoveUnit >= 8 && yMoveUnit <= 9.3) // E3
			{
				reD[1] = 255;
				aRr2[21] = 1;

			}
			else
			{
				reD[21] = 0;
			}
			if (xMoveUnit >= 10.5 && xMoveUnit <= 12 && yMoveUnit >= 8 && yMoveUnit <= 9.3) // F3
			{
				reD[1] = 255;
				aRr2[22] = 1;

			}
			else
			{
				reD[22] = 0;
			}
			if (xMoveUnit >= 12 && xMoveUnit <= 13.5 && yMoveUnit >= 8 && yMoveUnit <= 9.3) // G3
			{
				reD[1] = 255;
				aRr2[23] = 1;

			}
			else
			{
				reD[23] = 0;
			}
			if (xMoveUnit >= 13.5 && xMoveUnit <= 15 && yMoveUnit >= 8 && yMoveUnit <= 9.3) // H3
			{
				reD[1] = 255;
				aRr2[24] = 1;

			}
			else
			{
				reD[24] = 0;
			}
			/* 4 Column */
			if (xMoveUnit >= 3 && xMoveUnit <= 4.5 && yMoveUnit >= 9.3 && yMoveUnit <= 10.9) // A4
			{
				reD[1] = 255;
				aRr2[25] = 1;
				go = 14;
			}
			else
			{
				
				reD[25] = 0;
	
			}
						
			if (xMoveUnit >= 4.5 && xMoveUnit <= 6 && yMoveUnit >= 9.3 && yMoveUnit <= 10.9) // B4
			{
				reD[1] = 255;
				aRr2[26] = 1;

			}
			else
			{
				reD[26] = 0;
			}
			if (xMoveUnit >= 6 && xMoveUnit <= 7.5 && yMoveUnit >= 9.3 && yMoveUnit <= 10.9) // C4
			{
				reD[1] = 255;
				aRr2[27] = 1;

			}
			else
			{
				reD[27] = 0;
			}
			if (xMoveUnit >= 7.5 && xMoveUnit <= 9 && yMoveUnit >= 9.3 && yMoveUnit <= 10.9) // D4
			{
				reD[1] = 255;
				aRr2[28] = 1;

			}
			else
			{
				reD[28] = 0;
			}
			if (xMoveUnit >= 9 && xMoveUnit <= 10.5 && yMoveUnit >= 9.3 && yMoveUnit <= 10.9) // E4
			{
				reD[1] = 255;
				aRr2[29] = 1;

			}
			else
			{
				reD[29] = 0;
			}
			if (xMoveUnit >= 10.5 && xMoveUnit <= 12 && yMoveUnit >= 9.3 && yMoveUnit <= 10.9) // F4
			{
				reD[1] = 255;
				aRr2[30] = 1;

			}
			else
			{
				reD[30] = 0;
			}
			if (xMoveUnit >= 12 && xMoveUnit <= 13.5 && yMoveUnit >= 9.3 && yMoveUnit <= 10.9) // G4
			{
				reD[1] = 255;
				aRr2[31] = 1;

			}
			else
			{
				reD[31] = 0;
			}
			if (xMoveUnit >= 13.5 && xMoveUnit <= 15 && yMoveUnit >= 9.3 && yMoveUnit <= 10.9) // H4
			{
				reD[1] = 255;
				aRr2[32] = 1;

			}
			else
			{
				reD[32] = 0;
			}
			/* 5 Column*/
			if (xMoveUnit >= 3 && xMoveUnit <= 4.5 && yMoveUnit >= 10.9 && yMoveUnit <= 12.3) // A5
			{
				reD[1] = 255;
				aRr3[33] = 1;

			}
			else
			{
				reD[1] = 0;
			}
			if (xMoveUnit >= 4.5 && xMoveUnit <= 6 && yMoveUnit >= 10.9 && yMoveUnit <= 12.3) // B5
			{
				reD[1] = 255;
				aRr3[34] = 1;

			}
			else
			{
				reD[2] = 0;
			}
			if (xMoveUnit >= 6 && xMoveUnit <= 7.5 && yMoveUnit >= 10.9 && yMoveUnit <= 12.3) // C5
			{
				reD[1] = 255;
				aRr3[35] = 1;

			}
			else
			{
				reD[3] = 0;
			}
			if (xMoveUnit >= 7.5 && xMoveUnit <= 9 && yMoveUnit >= 10.9 && yMoveUnit <= 12.3) // D5
			{
				reD[1] = 255;
				aRr3[36] = 1;

			}
			else
			{
				reD[4] = 0;
			}
			if (xMoveUnit >= 9 && xMoveUnit <= 10.5 && yMoveUnit >= 10.9 && yMoveUnit <= 12.3) // E5
			{
				reD[1] = 255;
				aRr3[37] = 1;

			}
			else
			{
				reD[5] = 0;
			}
			if (xMoveUnit >= 10.5 && xMoveUnit <= 12 && yMoveUnit >= 10.9 && yMoveUnit <= 12.3) // F5
			{
				reD[1] = 255;
				aRr3[38] = 1;

			}
			else
			{
				reD[6] = 0;
			}
			if (xMoveUnit >= 12 && xMoveUnit <= 13.5 && yMoveUnit >= 10.9 && yMoveUnit <= 12.3) // G5
			{
				reD[1] = 255;
				aRr3[39] = 1;

			}
			else
			{
				reD[7] = 0;
			}
			if (xMoveUnit >= 13.5 && xMoveUnit <= 15 && yMoveUnit >= 10.9 && yMoveUnit <= 12.3) // H5
			{
				reD[1] = 255;
				aRr3[40] = 1;

			}
			else
			{
				reD[8] = 0;
			}
			/* 6 Column*/
			if (xMoveUnit >= 3 && xMoveUnit <= 4.5 && yMoveUnit >= 12.3 && yMoveUnit <= 13.7) // A6
			{
				reD[1] = 255;
				aRr3[41] = 1;

			}
			else
			{
				reD[1] = 0;
			}
			if (xMoveUnit >= 4.5 && xMoveUnit <= 6 && yMoveUnit >= 12.3 && yMoveUnit <= 13.7) // B6
			{
				reD[1] = 255;
				aRr3[42] = 1;

			}
			else
			{
				reD[2] = 0;
			}
			if (xMoveUnit >= 6 && xMoveUnit <= 7.5 && yMoveUnit >= 12.3 && yMoveUnit <= 13.7) // C6
			{
				reD[1] = 255;
				aRr3[43] = 1;

			}
			else
			{
				reD[3] = 0;
			}
			if (xMoveUnit >= 7.5 && xMoveUnit <= 9 && yMoveUnit >= 12.3 && yMoveUnit <= 13.7) // D6
			{
				reD[1] = 255;
				aRr3[44] = 1;

			}
			else
			{
				reD[4] = 0;
			}
			if (xMoveUnit >= 9 && xMoveUnit <= 10.5 && yMoveUnit >= 12.3 && yMoveUnit <= 13.7) // E6
			{
				reD[1] = 255;
				aRr3[45] = 1;
			}
			else
			{
				reD[5] = 0;
			}
			if (xMoveUnit >= 10.5 && xMoveUnit <= 12 && yMoveUnit >= 12.3 && yMoveUnit <= 13.7) // F6
			{
				reD[1] = 255;
				aRr3[46] = 1;

			}
			else
			{
				reD[6] = 0;
			}
			if (xMoveUnit >= 12 && xMoveUnit <= 13.5 && yMoveUnit >= 12.3 && yMoveUnit <= 13.7) // G6
			{
				reD[1] = 255;
				aRr3[47] = 1;

			}
			else
			{
				reD[7] = 0;
			}
			if (xMoveUnit >= 13.5 && xMoveUnit <= 15 && yMoveUnit >= 12.3 && yMoveUnit <= 13.7) // H6
			{
				reD[1] = 255;
				aRr3[48] = 1;

			}
			else
			{
				reD[8] = 0;
			}
			/* 7 Column*/
			if (xMoveUnit >= 3 && xMoveUnit <= 4.5 && yMoveUnit >= 13.7 && yMoveUnit <= 15.1) // A7
			{
				reD[1] = 255;
				aRr4[49] = 1;

			}
			else
			{
				reD[1] = 0;
			}
			if (xMoveUnit >= 4.5 && xMoveUnit <= 6 && yMoveUnit >= 13.7 && yMoveUnit <= 15.1) // B7
			{
				reD[1] = 255;
				aRr4[50] = 1;

			}
			else
			{
				reD[2] = 0;
			}
			if (xMoveUnit >= 6 && xMoveUnit <= 7.5 && yMoveUnit >= 13.7 && yMoveUnit <= 15.1) // C7
			{
				reD[1] = 255;
				aRr4[51] = 1;

			}
			else
			{
				reD[3] = 0;
			}
			if (xMoveUnit >= 7.5 && xMoveUnit <= 9 && yMoveUnit >= 13.7 && yMoveUnit <= 15.1) // D7
			{
				reD[1] = 255;
				aRr4[52] = 1;

			}
			else
			{
				reD[4] = 0;
			}
			if (xMoveUnit >= 9 && xMoveUnit <= 10.5 && yMoveUnit >= 13.7 && yMoveUnit <= 15.1) // E7
			{
				reD[1] = 255;
				aRr4[53] = 1;

			}
			else
			{
				reD[5] = 0;
			}
			if (xMoveUnit >= 10.5 && xMoveUnit <= 12 && yMoveUnit >= 13.7 && yMoveUnit <= 15.1) // F7
			{
				reD[1] = 255;
				aRr4[54] = 1;

			}
			else
			{
				reD[6] = 0;
			}
			if (xMoveUnit >= 12 && xMoveUnit <= 13.5 && yMoveUnit >= 13.7 && yMoveUnit <= 15.1) // G7
			{
				reD[1] = 255;
				aRr4[55] = 1;

			}
			else
			{
				reD[7] = 0;
			}
			if (xMoveUnit >= 13.5 && xMoveUnit <= 15 && yMoveUnit >= 13.7 && yMoveUnit <= 15.1) // H7
			{
				reD[1] = 255;
				aRr4[56] = 1;

			}
			else
			{
				reD[8] = 0;
			}
			/* 8 Column*/
			if (xMoveUnit >= 3 && xMoveUnit <= 4.5 && yMoveUnit >= 15.1 && yMoveUnit <= 16.5) // A8
			{
				reD[1] = 255;
				aRr4[57] = 1;

			}
			else
			{
				reD[1] = 0;
			}
			if (xMoveUnit >= 4.5 && xMoveUnit <= 6 && yMoveUnit >= 15.1 && yMoveUnit <= 16.5) // B8
			{
				reD[1] = 255;
				aRr4[58] = 1;

			}
			else
			{
				reD[2] = 0;
			}
			if (xMoveUnit >= 6 && xMoveUnit <= 7.5 && yMoveUnit >= 15.1 && yMoveUnit <= 16.5) // C8
			{
				reD[1] = 255;
				aRr4[59] = 1;

			}
			else
			{
				reD[3] = 0;
			}
			if (xMoveUnit >= 7.5 && xMoveUnit <= 9 && yMoveUnit >= 15.1 && yMoveUnit <= 16.5) // D8
			{
				reD[1] = 255;
				aRr4[60] = 1;

			}
			else
			{
				reD[4] = 0;
			}
			if (xMoveUnit >= 9 && xMoveUnit <= 10.5 && yMoveUnit >= 15.1 && yMoveUnit <= 16.5) // E8
			{
				reD[1] = 255;
				aRr4[61] = 1;

			}
			else
			{
				reD[5] = 0;
			}
			if (xMoveUnit >= 10.5 && xMoveUnit <= 12 && yMoveUnit >= 15.1 && yMoveUnit <= 16.5) // F8
			{
				reD[1] = 255;
				aRr4[62] = 1;

			}
			else
			{
				reD[6] = 0;
			}
			if (xMoveUnit >= 12 && xMoveUnit <= 13.5 && yMoveUnit >= 15.1 && yMoveUnit <= 16.5) // G8
			{
				reD[1] = 255;
				aRr4[63] = 1;

			}
			else
			{
				reD[7] = 0;
			}
			if (xMoveUnit >= 13.5 && xMoveUnit <= 15 && yMoveUnit >= 15.1 && yMoveUnit <= 16.5) // H8
			{
				reD[1] = 255;
				aRr4[64] = 1;

			}
			else
			{
				reD[8] = 0;
			}

			if (xMoveUnit >= 10 && xMoveUnit <= 14 && yMoveUnit >= 0.4 && yMoveUnit <= 1.6) // Button Clear
			{
				reD[9] = 255;

				aRr[1] = 0;
				aRr[2] = 0;
				aRr[3] = 0;
				aRr[4] = 0;
				aRr[5] = 0;
				aRr[6] = 0;
				aRr[7] = 0;
				aRr[8] = 0;
				aRr[9] = 0;
				aRr[10] = 0;
				aRr[11] = 0;
				aRr[12] = 0;
				aRr[13] = 0;
				aRr[14] = 0;
				aRr[15] = 0;
				aRr[16] = 0;
				aRr2[17] = 0;
				aRr2[18] = 0;
				aRr2[19] = 0;
				aRr2[20] = 0;
				aRr2[21] = 0;
				aRr2[22] = 0;
				aRr2[23] = 0;
				aRr2[24] = 0;
				aRr2[25] = 0;
				aRr2[26] = 0;
				aRr2[27] = 0;
				aRr2[28] = 0;
				aRr2[29] = 0;
				aRr2[30] = 0;
				aRr2[31] = 0;
				aRr2[32] = 0;
				aRr3[33] = 0;
				aRr3[34] = 0;
				aRr3[35] = 0;
				aRr3[36] = 0;
				aRr3[37] = 0;
				aRr3[38] = 0;
				aRr3[39] = 0;
				aRr3[40] = 0;
				aRr3[41] = 0;
				aRr3[42] = 0;
				aRr3[43] = 0;
				aRr3[44] = 0;
				aRr3[45] = 0;
				aRr3[46] = 0;
				aRr3[47] = 0;
				aRr3[48] = 0;
				aRr4[49] = 0;
				aRr4[50] = 0;
				aRr4[51] = 0;
				aRr4[52] = 0;
				aRr4[53] = 0;
				aRr4[54] = 0;
				aRr4[55] = 0;
				aRr4[56] = 0;
				aRr4[57] = 0;
				aRr4[58] = 0;
				aRr4[59] = 0;
				aRr4[60] = 0;
				aRr4[61] = 0;
				aRr4[62] = 0;
				aRr4[63] = 0;
				aRr4[64] = 0;

				arR2[1] = 0;
				arR2[2] = 0;
				arR2[3] = 0;
				arR2[4] = 0;
				arR2[5] = 0;
				arR2[6] = 0;
				arR2[7] = 0;
				arR2[8] = 0;

				xView = 0;
				yView = -5;
				zView = -4;
				xLookAt = 0;
				yLookAt = 0;
				zLookAt = 1;

				select = 0;

				states = 0;
				go = 0;
			}
			else
			{
				reD[9] = 0;
			}

		}


	}
	/* -NumButt- */


	glutPostRedisplay();
}

/* Button */
int x_button_po = 72; //72
int y_button_po = 16; //16
void glEnable2D()
{
	int vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}
void glDisable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Choose_Button()
{
	glEnable2D();
	// button
	glBegin(GL_QUADS);
	glColor3ub(reD[9], 0, 0);
	glVertex2d(x_button_po + 560, y_button_po);
	glColor3ub(reD[9], 0, 0);
	glVertex2d(x_button_po + 720, y_button_po);
	glColor3ub(reD[9], 0, 0);
	glVertex2d(x_button_po + 720, y_button_po + 50);
	glColor3ub(reD[9], 0, 0);
	glVertex2d(x_button_po + 560, y_button_po + 50);
	glEnd();


	glDisable2D();
}
void Show_Screen()
{
	glEnable2D();
	// select
	glBegin(GL_QUADS);
	glColor3ub(0, 205, 0);
	glVertex2d(x_button_po + 560, y_button_po + 60);
	glColor3ub(0, 205, 0);
	glVertex2d(x_button_po + 640, y_button_po + 60);
	glColor3ub(0, 205, 0);
	glVertex2d(x_button_po + 640, y_button_po + 110);
	glColor3ub(0, 205, 0);
	glVertex2d(x_button_po + 560, y_button_po + 110);
	// move
	glColor3ub(0, 0, 255);
	glVertex2d(x_button_po + 640, y_button_po + 60);
	glColor3ub(0, 0, 255);
	glVertex2d(x_button_po + 720, y_button_po + 60);
	glColor3ub(0, 0, 255);
	glVertex2d(x_button_po + 720, y_button_po + 110);
	glColor3ub(0, 0, 255);
	glVertex2d(x_button_po + 640, y_button_po + 110);
	glEnd();

	glDisable2D();
}
void Select()
{
	glEnable2D();

	glBegin(GL_LINES);
	/*S*/
	glColor3ub(255, 255, 255);
	glVertex2d(x_button_po + 565, y_button_po + 90);
	glColor3ub(255, 255, 255);
	glVertex2d(x_button_po + 565, y_button_po + 80);

	glColor3ub(255, 255, 255);
	glVertex2d(x_button_po + 715, y_button_po + 90);
	glColor3ub(255, 255, 255);
	glVertex2d(x_button_po + 565, y_button_po + 90);

	glColor3ub(255, 255, 255);
	glVertex2d(x_button_po + 565, y_button_po + 80);
	glColor3ub(255, 255, 255);
	glVertex2d(x_button_po + 715, y_button_po + 80);

	glColor3ub(255, 255, 255);
	glVertex2d(x_button_po + 565, y_button_po + 80);
	glColor3ub(255, 255, 255);
	glVertex2d(x_button_po + 715, y_button_po + 80);

	glEnd();

	glDisable2D();
}

void SELECTbot()
{

	if (xMoveUnit >= 10 && xMoveUnit <= 12.8 && yMoveUnit >= 0.2 && yMoveUnit <= 1.4) //choose
	{
		if (select == 11)
		{
			glEnable2D();
			// A
			glBegin(GL_LINES);
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 570, y_button_po + 100);
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 590, y_button_po + 100);

			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 570, y_button_po + 100);
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 570, y_button_po + 70);

			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 570, y_button_po + 85);
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 590, y_button_po + 85);

			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 590, y_button_po + 100);
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 590, y_button_po + 70);
			// 1
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 600, y_button_po + 100);
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 610, y_button_po + 100);

			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 610, y_button_po + 100);
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 610, y_button_po + 70);

			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 600, y_button_po + 70);
			glColor3ub(255, 255, 255);
			glVertex2d(x_button_po + 620, y_button_po + 70);
			glEnd();

			glDisable2D();
		}
	}
}



void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear display window.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xView, yView, zView, xLookAt, yLookAt, zLookAt, 0, 1, 0);

	
	//SELECTbot();
	//Char_On_Top_Num();
	//Char_On_Top_Char();
	//Select();
	/* Button_Clik */

	//Button_Last_Char();
	Choose_Button();
	//Show_Screen();

	/* set poX & poY */
	poX[1] = 7;  //A
	poX[2] = 5;  //B
	poX[3] = 3;  //C
	poX[4] = 1;  //D
	poX[5] = -1;  //E
	poX[6] = -3;  //F
	poX[7] = -5;  //G
	poX[8] = -7;  //H

	poZ[1] = 9;  //1
	poZ[2] = 7;  //2
	poZ[3] = 5;  //3
	poZ[4] = 3;  //4
	poZ[5] = 1;  //5
	poZ[6] = -1;  //6
	poZ[7] = -3;  //7
	poZ[8] = -5;  //8


//Sun
	/*glPushMatrix();
				  glRotatef(phi / 30, 0, 1, 0);
				  glScaled(1.0, 1.0, 1.0);// Circle size
				  glColor3f(1, 0, 0);
				  sphere(1.0, 50, 50);
				  glPopMatrix();

				  glRotatef(phi, 0, 1, 0);
				  glTranslatef(3, 0, 0);
				  */
 /* Num */
	{
		glPushMatrix();
		glTranslated(0.5, 1, 1);
		glColor3f(0.0, 0.0, 1.0);
		/*-1-*/
		glPushMatrix();
		glTranslatef(9, 0, 5);
		glScaled(.1, .1, .1);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 1);
		glVertex3f(-5, 0, 1);
		glVertex3f(-5, 0, 2);
		glVertex3f(-2, 0, 2);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-5, 0, 2);
		glVertex3f(-5, 0, 7);
		glVertex3f(-4, 0, 7);
		glVertex3f(-4, 0, 2);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 7);
		glVertex3f(-7, 0, 7);
		glVertex3f(-7, 0, 8);
		glVertex3f(-2, 0, 8);
		glEnd();
		glPopMatrix();
		/*-2-*/
		glPushMatrix();
		glTranslatef(9, 0, 3);
		glScaled(.1, .1, .1);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 1);
		glVertex3f(-7, 0, 1);
		glVertex3f(-7, 0, 2);
		glVertex3f(-2, 0, 2);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-6, 0, 2);
		glVertex3f(-7, 0, 2);
		glVertex3f(-7, 0, 4);
		glVertex3f(-6, 0, 4);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 4);
		glVertex3f(-7, 0, 4);
		glVertex3f(-7, 0, 5);
		glVertex3f(-2, 0, 5);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 5);
		glVertex3f(-3, 0, 5);
		glVertex3f(-3, 0, 7);
		glVertex3f(-2, 0, 7);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 7);
		glVertex3f(-7, 0, 7);
		glVertex3f(-7, 0, 8);
		glVertex3f(-2, 0, 8);
		glEnd();
		glPopMatrix();
		/*-3-*/
		glPushMatrix();
		glTranslatef(9, 0, 1);
		glScaled(.1, .1, .1);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 1);
		glVertex3f(-7, 0, 1);
		glVertex3f(-7, 0, 2);
		glVertex3f(-2, 0, 2);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-6, 0, 2);
		glVertex3f(-7, 0, 2);
		glVertex3f(-7, 0, 4);
		glVertex3f(-6, 0, 4);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 4);
		glVertex3f(-7, 0, 4);
		glVertex3f(-7, 0, 5);
		glVertex3f(-2, 0, 5);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-6, 0, 5);
		glVertex3f(-7, 0, 5);
		glVertex3f(-7, 0, 7);
		glVertex3f(-6, 0, 7);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 7);
		glVertex3f(-7, 0, 7);
		glVertex3f(-7, 0, 8);
		glVertex3f(-2, 0, 8);
		glEnd();
		glPopMatrix();
		/*-4-*/
		glPushMatrix();
		glTranslatef(9, 0, -1);
		glScaled(.1, .1, .1);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 1);
		glVertex3f(-3, 0, 1);
		glVertex3f(-3, 0, 4);
		glVertex3f(-2, 0, 4);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 4);
		glVertex3f(-6, 0, 4);
		glVertex3f(-6, 0, 5);
		glVertex3f(-2, 0, 5);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-6, 0, 1);
		glVertex3f(-7, 0, 1);
		glVertex3f(-7, 0, 8);
		glVertex3f(-6, 0, 8);
		glEnd();
		glPopMatrix();
		/*-5-*/
		glPushMatrix();
		glTranslatef(9, 0, -3);
		glScaled(.1, .1, .1);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 1);
		glVertex3f(-7, 0, 1);
		glVertex3f(-7, 0, 2);
		glVertex3f(-2, 0, 2);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 2);
		glVertex3f(-3, 0, 2);
		glVertex3f(-3, 0, 4);
		glVertex3f(-2, 0, 4);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 4);
		glVertex3f(-7, 0, 4);
		glVertex3f(-7, 0, 5);
		glVertex3f(-2, 0, 5);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-6, 0, 5);
		glVertex3f(-7, 0, 5);
		glVertex3f(-7, 0, 7);
		glVertex3f(-6, 0, 7);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 7);
		glVertex3f(-7, 0, 7);
		glVertex3f(-7, 0, 8);
		glVertex3f(-2, 0, 8);
		glEnd();
		glPopMatrix();
		/*-6-*/
		glPushMatrix();
		glTranslatef(9, 0, -5);
		glScaled(.1, .1, .1);
		glBegin(GL_POLYGON);
		glVertex3f(-3, 0, 1);
		glVertex3f(-7, 0, 1);
		glVertex3f(-7, 0, 2);
		glVertex3f(-3, 0, 2);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 1);
		glVertex3f(-3, 0, 1);
		glVertex3f(-3, 0, 8);
		glVertex3f(-2, 0, 8);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-3, 0, 7);
		glVertex3f(-7, 0, 7);
		glVertex3f(-7, 0, 8);
		glVertex3f(-3, 0, 8);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-6, 0, 5);
		glVertex3f(-7, 0, 5);
		glVertex3f(-7, 0, 7);
		glVertex3f(-6, 0, 7);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-3, 0, 4);
		glVertex3f(-7, 0, 4);
		glVertex3f(-7, 0, 5);
		glVertex3f(-3, 0, 5);
		glEnd();
		glPopMatrix();
		/*-7-*/
		glPushMatrix();
		glTranslatef(9, 0, -7);
		glScaled(.1, .1, .1);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 1);
		glVertex3f(-7, 0, 1);
		glVertex3f(-7, 0, 2);
		glVertex3f(-2, 0, 2);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-6, 0, 2);
		glVertex3f(-7, 0, 2);
		glVertex3f(-7, 0, 8);
		glVertex3f(-6, 0, 8);
		glEnd();
		glPopMatrix();
		/*-8-*/
		glPushMatrix();
		glTranslatef(9, 0, -9);
		glScaled(.1, .1, .1);
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 1);
		glVertex3f(-7, 0, 1);
		glVertex3f(-7, 0, 2);
		glVertex3f(-2, 0, 2);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-6, 0, 2);
		glVertex3f(-7, 0, 2);
		glVertex3f(-7, 0, 7);
		glVertex3f(-6, 0, 7);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 7);
		glVertex3f(-7, 0, 7);
		glVertex3f(-7, 0, 8);
		glVertex3f(-2, 0, 8);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-2, 0, 2);
		glVertex3f(-3, 0, 2);
		glVertex3f(-3, 0, 7);
		glVertex3f(-2, 0, 7);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(-3, 0, 4);
		glVertex3f(-6, 0, 4);
		glVertex3f(-6, 0, 5);
		glVertex3f(-3, 0, 5);
		glEnd();
		glPopMatrix();
		glPopMatrix();
	}
	{
		/* Char */
		{
			glPushMatrix();
			glTranslated(0, 1, 1.5);
			glColor3f(0.0, 0.0, 1.0);
			/*-A-*/
			glPushMatrix();
			glTranslatef(7.5, 0, 7);
			glScaled(.1, .1, .1);
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 1);
			glVertex3f(-7, 0, 1);
			glVertex3f(-7, 0, 2);
			glVertex3f(-2, 0, 2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 2);
			glVertex3f(-3, 0, 2);
			glVertex3f(-3, 0, 8);
			glVertex3f(-2, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-6, 0, 2);
			glVertex3f(-7, 0, 2);
			glVertex3f(-7, 0, 8);
			glVertex3f(-6, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 4);
			glVertex3f(-6, 0, 4);
			glVertex3f(-6, 0, 5);
			glVertex3f(-3, 0, 5);
			glEnd();
			glPopMatrix();
			/*-B-*/
			glPushMatrix();
			glTranslatef(5.5, 0, 7);
			glScaled(.1, .1, .1);
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 1);
			glVertex3f(-3, 0, 1);
			glVertex3f(-3, 0, 8);
			glVertex3f(-2, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 1);
			glVertex3f(-6, 0, 1);
			glVertex3f(-6, 0, 2);
			glVertex3f(-3, 0, 2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 4);
			glVertex3f(-6, 0, 4);
			glVertex3f(-6, 0, 5);
			glVertex3f(-3, 0, 5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 7);
			glVertex3f(-6, 0, 7);
			glVertex3f(-6, 0, 8);
			glVertex3f(-3, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-6, 0, 2);
			glVertex3f(-7, 0, 2);
			glVertex3f(-7, 0, 4);
			glVertex3f(-6, 0, 4);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-6, 0, 5);
			glVertex3f(-7, 0, 5);
			glVertex3f(-7, 0, 7);
			glVertex3f(-6, 0, 7);
			glEnd();
			glPopMatrix();
			/*-C-*/
			glPushMatrix();
			glTranslatef(3.5, 0, 7);
			glScaled(.1, .1, .1);
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 1);
			glVertex3f(-6, 0, 1);
			glVertex3f(-6, 0, 2);
			glVertex3f(-3, 0, 2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 2);
			glVertex3f(-3, 0, 2);
			glVertex3f(-3, 0, 7);
			glVertex3f(-2, 0, 7);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 7);
			glVertex3f(-6, 0, 7);
			glVertex3f(-6, 0, 8);
			glVertex3f(-3, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-6, 0, 2);
			glVertex3f(-7, 0, 2);
			glVertex3f(-7, 0, 3);
			glVertex3f(-6, 0, 3);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-6, 0, 6);
			glVertex3f(-7, 0, 6);
			glVertex3f(-7, 0, 7);
			glVertex3f(-6, 0, 7);
			glEnd();
			glPopMatrix();
			/*-D-*/
			glPushMatrix();
			glTranslatef(1.5, 0, 7);
			glScaled(.1, .1, .1);
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 1);
			glVertex3f(-6, 0, 1);
			glVertex3f(-6, 0, 2);
			glVertex3f(-3, 0, 2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 1);
			glVertex3f(-3, 0, 1);
			glVertex3f(-3, 0, 8);
			glVertex3f(-2, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 7);
			glVertex3f(-6, 0, 7);
			glVertex3f(-6, 0, 8);
			glVertex3f(-3, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-6, 0, 2);
			glVertex3f(-7, 0, 2);
			glVertex3f(-7, 0, 7);
			glVertex3f(-6, 0, 7);
			glEnd();
			glPopMatrix();
			/*-E-*/
			glPushMatrix();
			glTranslatef(-0.5, 0, 7);
			glScaled(.1, .1, .1);
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 1);
			glVertex3f(-3, 0, 1);
			glVertex3f(-3, 0, 8);
			glVertex3f(-2, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 1);
			glVertex3f(-7, 0, 1);
			glVertex3f(-7, 0, 2);
			glVertex3f(-3, 0, 2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 4);
			glVertex3f(-6, 0, 4);
			glVertex3f(-6, 0, 5);
			glVertex3f(-3, 0, 5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 7);
			glVertex3f(-7, 0, 7);
			glVertex3f(-7, 0, 8);
			glVertex3f(-3, 0, 8);
			glEnd();
			glPopMatrix();
			/*-F-*/
			glPushMatrix();
			glTranslatef(-2.5, 0, 7);
			glScaled(.1, .1, .1);
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 1);
			glVertex3f(-3, 0, 1);
			glVertex3f(-3, 0, 8);
			glVertex3f(-2, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 1);
			glVertex3f(-7, 0, 1);
			glVertex3f(-7, 0, 2);
			glVertex3f(-3, 0, 2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 4);
			glVertex3f(-6, 0, 4);
			glVertex3f(-6, 0, 5);
			glVertex3f(-3, 0, 5);
			glEnd();
			glPopMatrix();
			/*-G-*/
			glPushMatrix();
			glTranslatef(-4.5, 0, 7);
			glScaled(.1, .1, .1);
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 1);
			glVertex3f(-6, 0, 1);
			glVertex3f(-6, 0, 2);
			glVertex3f(-3, 0, 2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 2);
			glVertex3f(-3, 0, 2);
			glVertex3f(-3, 0, 7);
			glVertex3f(-2, 0, 7);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 7);
			glVertex3f(-6, 0, 7);
			glVertex3f(-6, 0, 8);
			glVertex3f(-3, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-6, 0, 5);
			glVertex3f(-7, 0, 5);
			glVertex3f(-7, 0, 7);
			glVertex3f(-6, 0, 7);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-4, 0, 4);
			glVertex3f(-6, 0, 4);
			glVertex3f(-6, 0, 5);
			glVertex3f(-4, 0, 5);
			glEnd();
			glPopMatrix();
			/*-G-*/
			glPushMatrix();
			glTranslatef(-6.5, 0, 7);
			glScaled(.1, .1, .1);
			glBegin(GL_POLYGON);
			glVertex3f(-2, 0, 1);
			glVertex3f(-3, 0, 1);
			glVertex3f(-3, 0, 8);
			glVertex3f(-2, 0, 8);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-3, 0, 4);
			glVertex3f(-6, 0, 4);
			glVertex3f(-6, 0, 5);
			glVertex3f(-3, 0, 5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-6, 0, 1);
			glVertex3f(-7, 0, 1);
			glVertex3f(-7, 0, 8);
			glVertex3f(-6, 0, 8);
			glEnd();
			glPopMatrix();
			glPopMatrix();

		}
	}
	glPushMatrix();
	glTranslated(0, 1, -2.5);
	/* BOARD */
	{
		glPushMatrix();
		for (int j = 0; j < 8; j++) //black first
		{
			if (color == 0 || color == 2 || color == 4 || color == 6)
			{
				glTranslatef(2, 0, 0);
				square_black();
			}
			else
			{
				glTranslatef(2, 0, 0);
				square_white();
			}
			color += 1;
		}

		glTranslated(-16, 0, -2);
		color = 0;
		for (int j = 0; j < 8; j++) //white first
		{
			if (color == 0)
			{
				glTranslatef(2, 0, 0);
				square_white();
			}
			else
			{
				glTranslatef(2, 0, 0);
				square_black();
			}
		}

		glTranslated(-16, 0, -2);
		for (int j = 0; j < 8; j++) //black first
		{
			if (color == 0 || color == 2 || color == 4 || color == 6)
			{
				glTranslatef(2, 0, 0);
				square_black();
			}
			else
			{
				glTranslatef(2, 0, 0);
				square_white();
			}
			color += 1;
		}

		glTranslated(-16, 0, -2);
		color = 0;
		for (int j = 0; j < 8; j++) //white first
		{
			if (color == 0)
			{
				glTranslatef(2, 0, 0);
				square_white();
			}
			else
			{
				glTranslatef(2, 0, 0);
				square_black();
			}
		}

		glTranslated(-16, 0, -2);
		for (int j = 0; j < 8; j++) //black first
		{
			if (color == 0 || color == 2 || color == 4 || color == 6)
			{
				glTranslatef(2, 0, 0);
				square_black();
			}
			else
			{
				glTranslatef(2, 0, 0);
				square_white();
			}
			color += 1;
		}

		glTranslated(-16, 0, -2);
		color = 0;
		for (int j = 0; j < 8; j++) //white first
		{
			if (color == 0)
			{
				glTranslatef(2, 0, 0);
				square_white();
			}
			else
			{
				glTranslatef(2, 0, 0);
				square_black();
			}
		}

		glTranslated(-16, 0, -2);
		for (int j = 0; j < 8; j++) //black first
		{
			if (color == 0 || color == 2 || color == 4 || color == 6)
			{
				glTranslatef(2, 0, 0);
				square_black();
			}
			else
			{
				glTranslatef(2, 0, 0);
				square_white();
			}
			color += 1;
		}

		glTranslated(-16, 0, -2);
		color = 0;
		for (int j = 0; j < 8; j++) //white first
		{
			if (color == 0)
			{
				glTranslatef(2, 0, 0);
				square_white();
			}
			else
			{
				glTranslatef(2, 0, 0);
				square_black();
			}
		}
		glPopMatrix();
	}
	/* RED */
	{
		// pawn
		{
			glColor3f(1.0, 0.0, 0.0);
			glPushMatrix();
			Pawn1(poX[1],0.1,poZ[3]);
			A3 = 1;  //ถึงตรงนี้
			glPopMatrix();
			glPushMatrix();
			glTranslatef(poX[2], 0.1, poZ[3]);
			Pawn2();
			B3 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(poX[3], 0.1, poZ[3]);
			Pawn3();
			C3 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(poX[4], 0.1, poZ[3]);
			Pawn4();
			D3 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(poX[5], 0.1, poZ[3]);
			Pawn5();
			E3 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(poX[6], 0.1, poZ[3]);
			Pawn6();
			F3 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(poX[7], 0.1, poZ[3]);
			Pawn7();
			G3 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(poX[8], 0.1, poZ[3]);
			Pawn8();
			H3 = 1;
			glPopMatrix();
		}
		{

		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(poX[1], 0.1, poZ[1]);
		Ship1();
		A1 = 1;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(poX[2], 0, poZ[1]);
		Mha1();
		B1 = 1;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(poX[3], 0.1, poZ[1]);
		Kon1();
		C1 = 1;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(poX[4], 0.1, poZ[1]);
		Kun1();
		D1 = 1;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(poX[5], 0.1, poZ[1]);
		Juk1();
		E1 = 1;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(poX[6], 0.1, poZ[1]);
		Kon2();
		F1 = 1;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(poX[7], 0, poZ[1]);
		Mha2();
		G1 = 1;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(poX[8], 0.1, poZ[1]);
		Ship2();
		H1 = 1;
		glPopMatrix();
		}
	}
	/* BLUE */
	{
		glPushMatrix();
		glRotatef(180, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -4.0);
		// pawn
		{
			glColor3f(0.0, 0.0, 1.0);
			glPushMatrix();
			glTranslatef(7, 0.1, 5);
			Pawn9();
			A6 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(5, 0.1, 5);
			Pawn10();
			B6 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(3, 0.1, 5);
			Pawn11();
			C6 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(1, 0.1, 5);
			Pawn12();
			D6 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-1, 0.1, 5);
			Pawn13();
			E6 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-3, 0.1, 5);
			Pawn14();
			F6 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-5, 0.1, 5);
			Pawn15();
			G6 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-7, 0.1, 5);
			Pawn16();
			H6 = 1;
			glPopMatrix();
		}
		{
			glColor3f(0.0, 0.0, 1.0);
			glPushMatrix();
			glTranslatef(7, 0.1, 9);
			Ship3();
			A8 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(5, 0, 9);
			Mha4();
			B8 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(3, 0.1, 9);
			Kon3();
			C8 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(1, 0.1, 9);
			Kun2();
			D8 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-1, 0.1, 9);
			Juk2();
			E8 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-3, 0.1, 9);
			Kon4();
			F8 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-5, 0, 9);
			Mha4();
			G8 = 1;
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-7, 0.1, 9);
			Ship4();
			H8 = 1;
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	/* -ChosePawn- */
	/* - 1 colum- */
	{
		if (aRr[1] == 1 && A1 == 1) //ship
		{
			if (A2 == 1)
			{
				glPushMatrix();
				glTranslatef(16, 1.05, -2.5);
				GreenArea();
				glPopMatrix();

			}
			else
			{
				if (A3 == 1)
				{
					glPushMatrix();
					glTranslatef(16, 1.05, -2.5);
					GreenArea();
					glPopMatrix();
					glPushMatrix();
					glTranslatef(16, 1.05, -4.5);
					GreenArea();
					glPopMatrix();
				}
				else
				{
					if (A4 == 1)
					{
						glPushMatrix();
						glTranslatef(16, 1.05, -2.5);
						GreenArea();
						glPopMatrix();
						glPushMatrix();
						glTranslatef(16, 1.05, -4.5);
						GreenArea();
						glPopMatrix();
						glPushMatrix();
						glTranslatef(16, 1.05, -6.5);
						GreenArea();
						glPopMatrix();
					}
					else
					{
						if (A5 == 1)
						{
							glPushMatrix();
							glTranslatef(16, 1.05, -2.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(16, 1.05, -4.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(16, 1.05, -6.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(16, 1.05, -8.5);
							GreenArea();
							glPopMatrix();
						}
						else
						{
							if (A6 == 1)
							{
								glPushMatrix();
								glTranslatef(16, 1.05, -2.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(16, 1.05, -4.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(16, 1.05, -6.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(16, 1.05, -8.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(16, 1.05, -10.5);
								GreenArea();
								glPopMatrix();
							}
							else
							{
								if (A7 == 1)
								{
									glPushMatrix();
									glTranslatef(16, 1.05, -2.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -4.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -6.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -8.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -10.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -12.5);
									GreenArea();
									glPopMatrix();
								}
								else
								{
									if (A8 == 1)
									{
										glPushMatrix();
										glTranslatef(16, 1.05, -2.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -4.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -6.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -8.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -10.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -12.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -14.5);
										GreenArea();
										glPopMatrix();
									}
									else
									{
										glPushMatrix();
										glTranslatef(16, 1.05, -2.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -4.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -6.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -8.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -10.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -12.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -14.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(16, 1.05, -16.5);
										GreenArea();
										glPopMatrix();
									}
								}
							}
						}
					}
				}
			}
			//select = 10;
		}
		
		if (aRr[2] == 1 && B1 == 1) //Mha
		{
			glPushMatrix();
			glTranslatef(14, 1.05, -2.5);
			GreenArea();
			glPopMatrix();
			if (A3 != 1) //MhaAtB1
			{
				glPushMatrix();
				glTranslatef(16, 1.05, -6.5);
				GreenArea();
				glPopMatrix();
			}
			if (C3 != 1)
			{
				glPushMatrix();
				glTranslatef(12, 1.05, -6.5);
				GreenArea();
				glPopMatrix();
			}
			if (D2 != 1)
			{
				glPushMatrix();
				glTranslatef(10, 1.05, -4.5);
				GreenArea();
				glPopMatrix();
			}

		}
		if (aRr[3] == 1 && C1 == 1) //Kon1
		{
			glPushMatrix();
			glTranslatef(12, 1.05, -2.5);
			GreenArea();
			glPopMatrix();
			if (B2 != 1)//KunAtC1
			{
				glPushMatrix();
				glTranslatef(14, 1.05, -4.5); //B2
				GreenArea();
				glPopMatrix();
			}
			if (C2 != 1)
			{
				glPushMatrix();
				glTranslatef(12, 1.05, -4.5); //C2
				GreenArea();
				glPopMatrix();
			}
			if (D2 != 1)
			{
				glPushMatrix();
				glTranslatef(10, 1.05, -4.5); //D2
				GreenArea();
				glPopMatrix();
			}

		}
		if (aRr[4] == 1 && D1 == 1)//Kun
		{

			glPushMatrix();
			glTranslatef(10, 1.05, -2.5);
			GreenArea();
			glPopMatrix();

			if (C2 != 1)//KunAtD1
			{
				glPushMatrix();
				glTranslatef(12, 1.05, -4.5);
				GreenArea();
				glPopMatrix();
			}
			if (D2 != 1)
			{
				glPushMatrix();
				glTranslatef(10, 1.05, -4.5);
				GreenArea();
				glPopMatrix();
			}
			if (E2 != 1)
			{
				glPushMatrix();
				glTranslatef(8, 1.05, -4.5);
				GreenArea();
				glPopMatrix();
			}
			if (C1 != 1)
			{
				glPushMatrix();
				glTranslatef(12, 1.05, -2.5);
				GreenArea();
				glPopMatrix();
			}
			if (E1 != 1)
			{
				glPushMatrix();
				glTranslatef(8, 1.05, -2.5);
				GreenArea();
				glPopMatrix();
			}

		}
		if (aRr[5] == 1 && E1 == 1)//MEd
		{
			glPushMatrix();
			glTranslatef(8, 1.05, -2.5);
			GreenArea();
			glPopMatrix();
			if (D2 != 1) //MedAtE1
			{
				glPushMatrix();
				glTranslatef(10, 1.05, -4.5);
				GreenArea();
				glPopMatrix();
			}
			if (F2 != 1)
			{
				glPushMatrix();
				glTranslatef(6, 1.05, -4.5);
				GreenArea();
				glPopMatrix();
			}

		}
		if (aRr[6] == 1 && F1 == 1) //Kon2
		{
			glPushMatrix();
			glTranslatef(6, 1.05, -2.5);
			GreenArea();
			glPopMatrix();
			if (E2 != 1)//Kon2AtF1
			{
				glPushMatrix();
				glTranslatef(8, 1.05, -4.5); //E2
				GreenArea();
				glPopMatrix();
			}
			if (F2 != 1)
			{
				glPushMatrix();
				glTranslatef(6, 1.05, -4.5); //F2
				GreenArea();
				glPopMatrix();
			}
			if (G2 != 1)
			{
				glPushMatrix();
				glTranslatef(4, 1.05, -4.5); //G2
				GreenArea();
				glPopMatrix();
			}

		}
		if (aRr[7] == 1 && G1 == 1)//Mha2
		{
			glPushMatrix();
			glTranslatef(4, 1.05, -2.5);
			GreenArea();
			glPopMatrix();
			if (E2 != 1) //MhaAtG1
			{
				glPushMatrix();
				glTranslatef(8, 1.05, -4.5);//E2
				GreenArea();
				glPopMatrix();
			}
			if (F3 != 1)
			{
				glPushMatrix();
				glTranslatef(6, 1.05, -6.5); //F3
				GreenArea();
				glPopMatrix();
			}
			if (H3 != 1)
			{
				glPushMatrix();
				glTranslatef(2, 1.05, -4.5); //H3
				GreenArea();
				glPopMatrix();
			}

		}
		if (aRr[8] == 1 && H1 == 1)//Ship2
		{
			glPushMatrix();
			glTranslatef(2, 1.05, -2.5); //ShipAtH1
			GreenArea();
			glPopMatrix();
			if (H2 != 1)
			{
				glPushMatrix();
				glTranslatef(2, 1.05, -4.5);
				GreenArea();
				glPopMatrix();
			}
			else
			{
				if (H2 != 1 && H3 != 1)
				{
					glPushMatrix();
					glTranslatef(2, 1.05, -4.5);
					GreenArea();
					glPopMatrix();
					glPushMatrix();
					glTranslatef(2, 1.05, -6.5);
					GreenArea();
					glPopMatrix();
				}
				else
				{
					if (H2 != 1 && H3 != 1 && H4 != 1)
					{
						glPushMatrix();
						glTranslatef(2, 1.05, -4.5);
						GreenArea();
						glPopMatrix();
						glPushMatrix();
						glTranslatef(2, 1.05, -6.5);
						GreenArea();
						glPopMatrix();
						glPushMatrix();
						glTranslatef(2, 1.05, -8.5);
						GreenArea();
						glPopMatrix();
					}
					else
					{
						if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1)
						{
							glPushMatrix();
							glTranslatef(2, 1.05, -4.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(2, 1.05, -6.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(2, 1.05, -8.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(2, 1.05, -10.5);
							GreenArea();
							glPopMatrix();
						}
						else
						{
							if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1)
							{
								glPushMatrix();
								glTranslatef(2, 1.05, -4.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(2, 1.05, -6.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(2, 1.05, -8.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(2, 1.05, -10.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(2, 1.05, -12.5);
								GreenArea();
								glPopMatrix();
							}
							else
							{
								if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1)
								{
									glPushMatrix();
									glTranslatef(2, 1.05, -4.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -6.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -8.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -10.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -12.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -14.5);
									GreenArea();
									glPopMatrix();
								}
								else
								{
									if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1 && G1 != 1)
									{
										glPushMatrix();
										glTranslatef(2, 1.05, -4.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -6.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -8.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -10.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -12.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -14.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(4, 1.05, -2.5);
										GreenArea();
										glPopMatrix();
									}
									else
									{
										if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1 && G1 != 1)
										{
											glPushMatrix();
											glTranslatef(2, 1.05, -4.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -6.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -8.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -10.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -12.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -14.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(4, 1.05, -2.5);
											GreenArea();
											glPopMatrix();
										}
										else
										{
											if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1 && G1 != 1 && F1 != 1)
											{
												glPushMatrix();
												glTranslatef(2, 1.05, -4.5);
												GreenArea();
												glPopMatrix();
												glPushMatrix();
												glTranslatef(2, 1.05, -6.5);
												GreenArea();
												glPopMatrix();
												glPushMatrix();
												glTranslatef(2, 1.05, -8.5);
												GreenArea();
												glPopMatrix();
												glPushMatrix();
												glTranslatef(2, 1.05, -10.5);
												GreenArea();
												glPopMatrix();
												glPushMatrix();
												glTranslatef(2, 1.05, -12.5);
												GreenArea();
												glPopMatrix();
												glPushMatrix();
												glTranslatef(2, 1.05, -14.5);
												GreenArea();
												glPopMatrix();
												glPushMatrix();
												glTranslatef(4, 1.05, -2.5);
												GreenArea();
												glPopMatrix();
												glPushMatrix();
												glTranslatef(6, 1.05, -2.5);
												GreenArea();
												glPopMatrix();
											}
											else
											{
												if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1 && G1 != 1 && F1 != 1 && E1 != 1)
												{
													glPushMatrix();
													glTranslatef(2, 1.05, -4.5);
													GreenArea();
													glPopMatrix();
													glPushMatrix();
													glTranslatef(2, 1.05, -6.5);
													GreenArea();
													glPopMatrix();
													glPushMatrix();
													glTranslatef(2, 1.05, -8.5);
													GreenArea();
													glPopMatrix();
													glPushMatrix();
													glTranslatef(2, 1.05, -10.5);
													GreenArea();
													glPopMatrix();
													glPushMatrix();
													glTranslatef(2, 1.05, -12.5);
													GreenArea();
													glPopMatrix();
													glPushMatrix();
													glTranslatef(2, 1.05, -14.5);
													GreenArea();
													glPopMatrix();
													glPushMatrix();
													glTranslatef(4, 1.05, -2.5);
													GreenArea();
													glPopMatrix();
													glPushMatrix();
													glTranslatef(6, 1.05, -2.5);
													GreenArea();
													glPopMatrix();
													glPushMatrix();
													glTranslatef(8, 1.05, -2.5);
													GreenArea();
													glPopMatrix();
												}
												else
												{
													if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1 && G1 != 1 && F1 != 1 && E1 != 1 && D1 != 1)
													{
														glPushMatrix();
														glTranslatef(2, 1.05, -4.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(2, 1.05, -6.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(2, 1.05, -8.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(2, 1.05, -10.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(2, 1.05, -12.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(2, 1.05, -14.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(4, 1.05, -2.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(6, 1.05, -2.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(8, 1.05, -2.5);
														GreenArea();
														glPopMatrix();
														glPushMatrix();
														glTranslatef(10, 1.05, -2.5);
														GreenArea();
														glPopMatrix();
													}
													else
													{
														if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1 && G1 != 1 && F1 != 1 && E1 != 1 && D1 != 1 && C1 != 1)
														{
															glPushMatrix();
															glTranslatef(2, 1.05, -4.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(2, 1.05, -6.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(2, 1.05, -8.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(2, 1.05, -10.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(2, 1.05, -12.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(2, 1.05, -14.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(4, 1.05, -2.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(6, 1.05, -2.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(8, 1.05, -2.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(10, 1.05, -2.5);
															GreenArea();
															glPopMatrix();
															glPushMatrix();
															glTranslatef(12, 1.05, -2.5);
															GreenArea();
															glPopMatrix();
														}
														else
														{
															if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1 && G1 != 1 && F1 != 1 && E1 != 1 && D1 != 1 && C1 != 1 && B1 != 1)
															{
																glPushMatrix();
																glTranslatef(2, 1.05, -4.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(2, 1.05, -6.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(2, 1.05, -8.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(2, 1.05, -10.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(2, 1.05, -12.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(2, 1.05, -14.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(4, 1.05, -2.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(6, 1.05, -2.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(8, 1.05, -2.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(10, 1.05, -2.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(12, 1.05, -2.5);
																GreenArea();
																glPopMatrix();
																glPushMatrix();
																glTranslatef(14, 1.05, -2.5);
																GreenArea();
																glPopMatrix();
															}
															else
															{
																if (H2 != 1 && H3 != 1 && H4 != 1 && H6 != 1 && H7 != 1 && H8 != 1 && G1 != 1 && F1 != 1 && E1 != 1 && D1 != 1 && C1 != 1 && B1 != 1 && A1 != 1)
																{
																	glPushMatrix();
																	glTranslatef(2, 1.05, -4.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(2, 1.05, -6.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(2, 1.05, -8.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(2, 1.05, -10.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(2, 1.05, -12.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(2, 1.05, -14.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(4, 1.05, -2.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(6, 1.05, -2.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(8, 1.05, -2.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(10, 1.05, -2.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(12, 1.05, -2.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(14, 1.05, -2.5);
																	GreenArea();
																	glPopMatrix();
																	glPushMatrix();
																	glTranslatef(16, 1.05, -2.5);
																	GreenArea();
																	glPopMatrix();
																}
															}
														}
													}
												}
											}

										}
									}
								}
							}
						}
					}

				}
			}
		}
	}
	/* - 2 colum- */
	{
		if (aRr[9] == 1 && A2 == 1)
		{
			{
				glTranslatef(16, 1.05, -4.5);
				GreenArea();
			}
		}
		if (aRr[10] == 1 && B2 == 1)
		{
			
			{
				glTranslatef(14, 1.05, -4.5);
				GreenArea();
			}

		}
		if (aRr[11] == 1 && C2 == 1)
		{
			
			{
				glTranslatef(12, 1.05, -4.5);
				GreenArea();
			}

		}
		if (aRr[12] == 1 && D2 == 1)
		{
			//if (D2 == 1)
			{
				glTranslatef(10, 1.05, -4.5);
				GreenArea();
			}

		}
		if (aRr[13] == 1 && E2 == 1)
		{
			//if (E2 == 1)
			{
				glTranslatef(8, 1.05, -4.5);
				GreenArea();
			}

		}
		if (aRr[14] == 1 && F2 == 1)
		{
			//if (F2 == 1)
			{
				glTranslatef(6, 1.05, -4.5);
				GreenArea();
			}

		}
		if (aRr[15] == 1 && G2 == 1)
		{
			//if (G2 == 1)
			{
				glTranslatef(4, 1.05, -4.5);
				GreenArea();
			}

		}
		if (aRr[16] == 1 && H2 == 1)
		{
			//if (H2 == 1)
			{
				glTranslatef(2, 1.05, -4.5);
				GreenArea();
			}

		}
	}
	/* - 3 colum- */
	{
		if (aRr2[17] == 1 && A3 == 1)
		{		
			glPushMatrix();
			glPushMatrix();
				glTranslatef(16, 1.05, -6.5);
				GreenArea();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(16, 1.05, -8.5);
			GreenArea();
			glPopMatrix();
			select = 1;
			glPopMatrix();
		}

		if (aRr2[18] == 1 && B3 == 1)
		{
			
			glPushMatrix();
				glTranslatef(14, 1.05, -6.5);
				GreenArea();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(14, 1.05, -8.5);
			GreenArea();
			glPopMatrix();

		}
		if (aRr2[19] == 1 && C3 == 1)
		{
			 
			glPushMatrix();
				glTranslatef(12, 1.05, -6.5);
				GreenArea();
				glPopMatrix();
				glPushMatrix();
				glTranslatef(12, 1.05, -8.5);
				GreenArea();
				glPopMatrix();
		}
		if (aRr2[20] == 1 && D3 == 1)
		{
			
			glPushMatrix();
			glTranslatef(10, 1.05, -6.5);
			GreenArea();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(10, 1.05, -8.5);
			GreenArea();
			glPopMatrix();

		}
		if (aRr2[21] == 1 && E3 == 1)
		{
			
			glPushMatrix();
			glTranslatef(8, 1.05, -6.5);
			GreenArea();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(8, 1.05, -8.5);
			GreenArea();
			glPopMatrix();

		}
		if (aRr2[22] == 1 && F3 == 1)
		{
			
			glPushMatrix();
			glTranslatef(6, 1.05, -6.5);
			GreenArea();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(6, 1.05, -8.5);
			GreenArea();
			glPopMatrix();

		}
		if (aRr2[23] == 1 && G3 == 1)
		{
			
			glPushMatrix();
			glTranslatef(4, 1.05, -6.5);
			GreenArea();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(4, 1.05, -8.5);
			GreenArea();
			glPopMatrix();

		}
		if (aRr2[24] == 1 && H3 == 1)
		{
			
			glPushMatrix();
			glTranslatef(2, 1.05, -6.5);
			GreenArea();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(2, 1.05, -8.5);
			GreenArea();
			glPopMatrix();

		}
	}
	/* - 4 colum- */
	{
		if (aRr2[25] == 1 && A4 == 1)
		{

			{
				glTranslatef(16, 1.05, -8.5);
				GreenArea();
			}
		}
		if (aRr2[26] == 1 && B4 == 1)
		{

			{
				glTranslatef(14, 1.05, -8.5);
				GreenArea();
			}

		}
		if (aRr2[27] == 1 && C4 == 1)
		{

			{
				glTranslatef(12, 1.05, -8.5);
				GreenArea();
			}

		}
		if (aRr2[28] == 1 && D4 == 1)
		{

			{
				glTranslatef(10, 1.05, -8.5);
				GreenArea();
			}

		}
		if (aRr2[29] == 1 && E4 == 1)
		{

			{
				glTranslatef(8, 1.05, -8.5);
				GreenArea();
			}

		}
		if (aRr2[30] == 1 && F4 == 1)
		{

			{
				glTranslatef(6, 1.05, -8.5);
				GreenArea();
			}

		}
		if (aRr2[31] == 1 && G4 == 1)
		{

			{
				glTranslatef(4, 1.05, -8.5);
				GreenArea();
			}

		}
		if (aRr2[32] == 1 && H4 == 1)
		{

			{
				glTranslatef(2, 1.05, -8.5);
				GreenArea();
			}

		}
	}
	/* - 5 colum- */
	{
		if (aRr3[33] == 1 && A5 == 1)
		{
			
			{
				glTranslatef(16, 1.05, -10.5);
				GreenArea();
			}
		}
		if (aRr3[34] == 1 && B5 == 1)
		{
			
			{
				glTranslatef(14, 1.05, -10.5);
				GreenArea();
			}

		}
		if (aRr3[35] == 1 && C5 == 1)
		{
			
			{
				glTranslatef(12, 1.05, -10.5);
				GreenArea();
			}

		}
		if (aRr3[36] == 1 && D5 == 1)
		{
			
			{
				glTranslatef(10, 1.05, -10.5);
				GreenArea();
			}

		}
		if (aRr3[37] == 1 && E5 == 1)
		{
			
			{
				glTranslatef(8, 1.05, -10.5);
				GreenArea();
			}

		}
		if (aRr3[38] == 1 && F5 == 1)
		{
			
			{
				glTranslatef(6, 1.05, -10.5);
				GreenArea();
			}

		}
		if (aRr3[39] == 1 && G5 == 1)
		{
			
			{
				glTranslatef(4, 1.05, -10.5);
				GreenArea();
			}

		}
		if (aRr3[40] == 1 && H5 == 1)
		{
			
			{
				glTranslatef(2, 1.05, -10.5);
				GreenArea();
			}

		}
	}
	/* - 6 colum- */
	{
		if (aRr3[41] == 1 && A6 == 1)
		{
			glPushMatrix();
				glTranslatef(16, 1.05, -12.5);
				GreenArea();
				glPopMatrix();
				if (A5 != 1)
				{
					glPushMatrix();
					glTranslatef(16, 1.05, -10.5);
					GreenArea();
					glPopMatrix();
					
				}
			
		}
		if (aRr3[42] == 1 && B6 == 1)
		{
			glPushMatrix();
				glTranslatef(14, 1.05, -12.5);
				GreenArea();
				glPopMatrix();
				if (B5 != 1)
				{
					glPushMatrix();
					glTranslatef(14, 1.05, -10.5);
					GreenArea();
					glPopMatrix();

				}

		}
		if (aRr3[43] == 1 && C6 == 1)
		{
			glPushMatrix();
			glTranslatef(12, 1.05, -12.5);
			GreenArea();
			glPopMatrix();
			if (C5 != 1)
			{
				glPushMatrix();
				glTranslatef(12, 1.05, -10.5);
				GreenArea();
				glPopMatrix();

			}
		}
		if (aRr3[44] == 1 && D6 == 1)
		{
			glPushMatrix();
			glTranslatef(10, 1.05, -12.5);
			GreenArea();
			glPopMatrix();
			if (D5 != 1)
			{
				glPushMatrix();
				glTranslatef(10, 1.05, -10.5);
				GreenArea();
				glPopMatrix();

			}
		}
		if (aRr3[45] == 1 && E6 == 1)
		{
			glPushMatrix();
			glTranslatef(8, 1.05, -12.5);
			GreenArea();
			glPopMatrix();
			if (E5 != 1)
			{
				glPushMatrix();
				glTranslatef(8, 1.05, -10.5);
				GreenArea();
				glPopMatrix();

			}
		}
		if (aRr3[46] == 1 && F6 == 1)
		{
			glPushMatrix();
			glTranslatef(6, 1.05, -12.5);
			GreenArea();
			glPopMatrix();
			if (F5 != 1)
			{
				glPushMatrix();
				glTranslatef(6, 1.05, -10.5);
				GreenArea();
				glPopMatrix();

			}
		}
		if (aRr3[47] == 1 && G6 == 1)
		{
			glPushMatrix();
			glTranslatef(4, 1.05, -12.5);
			GreenArea();
			glPopMatrix();
			if (G5 != 1)
			{
				glPushMatrix();
				glTranslatef(4, 1.05, -10.5);
				GreenArea();
				glPopMatrix();

			}
		}
		if (aRr3[48] == 1 && H6 == 1)
		{
			glPushMatrix();
			glTranslatef(2, 1.05, -12.5);
			GreenArea();
			glPopMatrix();
			if (H5 != 1)
			{
				glPushMatrix();
				glTranslatef(2, 1.05, -10.5);
				GreenArea();
				glPopMatrix();

			}
		}
	}
	/* - 7 colum- */
	{
		if (aRr4[49] == 1 && A7 == 1)
		{
			
			{
				glTranslatef(16, 1.05, -14.5);
				GreenArea();
			}
		}
		if (aRr4[50] == 1 && B7 == 1)
		{
			
			{
				glTranslatef(14, 1.05, -14.5);
				GreenArea();
			}

		}
		if (aRr4[51] == 1 && C7 == 1)
		{
			
			{
				glTranslatef(12, 1.05, -14.5);
				GreenArea();
			}

		}
		if (aRr4[52] == 1 && D7 == 1)
		{
			
			{
				glTranslatef(10, 1.05, -14.5);
				GreenArea();
			}

		}
		if (aRr4[53] == 1 && E7 == 1)
		{
			
			{
				glTranslatef(8, 1.05, -14.5);
				GreenArea();
			}

		}
		if (aRr4[54] == 1 && F7 == 1)
		{
			
			{
				glTranslatef(6, 1.05, -14.5);
				GreenArea();
			}

		}
		if (aRr4[55] == 1 && G7 == 1)
		{
			
			{
				glTranslatef(4, 1.05, -14.5);
				GreenArea();
			}

		}
		if (aRr4[56] == 1 && H7 == 1)
		{
			
			{
				glTranslatef(2, 1.05, -14.5);
				GreenArea();
			}

		}
	}
	/* - 8 colum- */
	{
		if (aRr4[57] == 1 && A8 == 1)
		{
			glPushMatrix();
			glTranslatef(16, 1.05, -16.5);
			GreenArea();
			glPopMatrix();
			if (A7 != 1)
			{
				glPushMatrix();
				glTranslatef(16, 1.05, -14.5);
				GreenArea();
				glPopMatrix();
			}
			else
			{
				if (A7 != 1 && A6 != 1)
				{
					glPushMatrix();
					glTranslatef(16, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
					glPushMatrix();
					glTranslatef(16, 1.05, -12.5);
					GreenArea();
					glPopMatrix();
				}
				else
				{
					if (A7 != 1 && A6 != 1 && A5 != 1)
					{
						glPushMatrix();
						glTranslatef(16, 1.05, -14.5);
						GreenArea();
						glPopMatrix();
						glPushMatrix();
						glTranslatef(16, 1.05, -12.5);
						GreenArea();
						glPopMatrix();
						glPushMatrix();
						glTranslatef(16, 1.05, -10.5);
						GreenArea();
						glPopMatrix();
					}
					else
					{
						if (A7 != 1 && A6 != 1 && A5 != 1 && A4 != 1)
						{
							glPushMatrix();
							glTranslatef(16, 1.05, -14.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(16, 1.05, -12.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(16, 1.05, -10.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(16, 1.05, -8.5);
							GreenArea();
							glPopMatrix();
						}
						else
						{
							if (A7 != 1 && A6 != 1 && A5 != 1 && A4 != 1 && A3 != 1)
							{
								glPushMatrix();
								glTranslatef(16, 1.05, -14.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(16, 1.05, -12.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(16, 1.05, -10.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(16, 1.05, -8.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(16, 1.05, -6.5);
								GreenArea();
								glPopMatrix();
							}
							else
							{
								if (A7 != 1 && A6 != 1 && A5 != 1 && A4 != 1 && A3 != 1 && A1 == 1)
								{
									glPushMatrix();
									glTranslatef(16, 1.05, -14.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -12.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -10.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -8.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -6.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(16, 1.05, -4.5);
									GreenArea();
									glPopMatrix();
								}
							}
						}
					}
				}
			}
		}
		if (aRr4[58] == 1 && B8 == 1)
		{
			glPushMatrix();
				glTranslatef(14, 1.05, -16.5);
				GreenArea();
				glPopMatrix();
				if (A6 != 1)
				{
					glPushMatrix();
					glTranslatef(16, 1.05, -12.5);
					GreenArea();
					glPopMatrix();
				}
				if (C6 != 1)
				{
					glPushMatrix();
					glTranslatef(12, 1.05, -12.5);
					GreenArea();
					glPopMatrix();
				}
				if (D7 != 1)
				{
					glPushMatrix();
					glTranslatef(10, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
				}

		}
		if (aRr4[59] == 1 && C8 == 1)
		{
			glPushMatrix();
			glTranslatef(12, 1.05, -16.5);
			GreenArea();
			glPopMatrix();
			if (B7 != 1)
			{
				glPushMatrix();
				glTranslatef(14, 1.05, -14.5);
				GreenArea();
				glPopMatrix();
			}
			if (C7 != 1)
			{
				glPushMatrix();
				glTranslatef(12, 1.05, -14.5);
				GreenArea();
				glPopMatrix();
			}
			if (D7 != 1)
			{
				glPushMatrix();
				glTranslatef(10, 1.05, -14.5);
				GreenArea();
				glPopMatrix();
			}
		
		}
		if (aRr4[60] == 1 && D8 == 1)
		{
			glPushMatrix();
				glTranslatef(10, 1.05, -16.5);
				GreenArea();
				glPopMatrix();
				if (C7 != 1)
				{
					glPushMatrix();
					glTranslatef(12, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
				}
				if (E7 != 1)
				{
					glPushMatrix();
					glTranslatef(8, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
				}

		}
		if (aRr4[61] == 1 && E8 == 1)
		{
			glPushMatrix();
				glTranslatef(8, 1.05, -16.5);
				GreenArea();
				glPopMatrix();
				if (D8 != 1)
				{
					glPushMatrix();
					glTranslatef(10, 1.05, -16.5);
					GreenArea();
					glPopMatrix();
				}
				if (D7 != 1)
				{
					glPushMatrix();
					glTranslatef(10, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
				}
				if (E7 != 1)
				{
					glPushMatrix();
					glTranslatef(8, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
				}
				if (F7 != 1)
				{
					glPushMatrix();
					glTranslatef(6, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
				}
				if (F8 != 1)
				{
					glPushMatrix();
					glTranslatef(6, 1.05, -16.5);
					GreenArea();
					glPopMatrix();
				}

		}
		if (aRr4[62] == 1 && F8 == 1)
		{
			glPushMatrix();
			glTranslatef(6, 1.05, -16.5);
			GreenArea();
			glPopMatrix();
			if (E7 != 1)
			{
				glPushMatrix();
				glTranslatef(8, 1.05, -14.5);
				GreenArea();
				glPopMatrix();
			}
			if (F7 != 1)
			{
				glPushMatrix();
				glTranslatef(6, 1.05, -14.5);
				GreenArea();
				glPopMatrix();
			}
			if (G7 != 1)
			{
				glPushMatrix();
				glTranslatef(4, 1.05, -14.5);
				GreenArea();
				glPopMatrix();
			}

		}
		if (aRr4[63] == 1 && G8 == 1)
		{
			glPushMatrix();
				glTranslatef(4, 1.05, -16.5);
				GreenArea();
				glPopMatrix();
				if (E7 != 1)
				{
					glPushMatrix();
					glTranslatef(8, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
				}
				if (F6 != 1)
				{
					glPushMatrix();
					glTranslatef(6, 1.05, -12.5);
					GreenArea();
					glPopMatrix();
				}
				if (H6 != 1)
				{
					glPushMatrix();
					glTranslatef(2, 1.05, -12.5);
					GreenArea();
					glPopMatrix();
				}
		}
		if (aRr4[64] == 1 && H8 == 1)
		{
			glPushMatrix();
				glTranslatef(2, 1.05, -16.5);
				GreenArea();
				glPopMatrix();
				if (H7 != 1)
				{
					glPushMatrix();
					glTranslatef(2, 1.05, -14.5);
					GreenArea();
					glPopMatrix();
				}
				else
				{
					if (H7 != 1 && H6 != 1)
					{
						glPushMatrix();
						glTranslatef(2, 1.05, -14.5);
						GreenArea();
						glPopMatrix();
						glPushMatrix();
						glTranslatef(2, 1.05, -12.5);
						GreenArea();
						glPopMatrix();
					}
					else
					{
						if (H7 != 1 && H6 != 1 && H5 != 1)
						{
							glPushMatrix();
							glTranslatef(2, 1.05, -14.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(2, 1.05, -12.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(2, 1.05, -10.5);
							GreenArea();
							glPopMatrix();
						}
						else
						{
							if (H7 != 1 && H6 != 1 && H5 != 1 && H4 != 1)
							{
								glPushMatrix();
								glTranslatef(2, 1.05, -14.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(2, 1.05, -12.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(2, 1.05, -10.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(2, 1.05, -8.5);
								GreenArea();
								glPopMatrix();
							}
							else
							{
								if (H7 != 1 && H6 != 1 && H5 != 1 && H4 != 1 && H3 != 1)
								{
									glPushMatrix();
									glTranslatef(2, 1.05, -14.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -12.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -10.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -8.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(2, 1.05, -6.5);
									GreenArea();
									glPopMatrix();
								}
								else
								{
									if (H7 != 1 && H6 != 1 && H5 != 1 && H4 != 1 && H3 != 1 & H2 != 1)
									{
										glPushMatrix();
										glTranslatef(2, 1.05, -14.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -12.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -10.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -8.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -6.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(2, 1.05, -4.5);
										GreenArea();
										glPopMatrix();
									}
									else
									{
										if (H7 != 1 && H6 != 1 && H5 != 1 && H4 != 1 && H3 != 1 & H2 != 1 && H1 != 1)
										{
											glPushMatrix();
											glTranslatef(2, 1.05, -14.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -12.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -10.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -8.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -6.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -4.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(2, 1.05, -2.5);
											GreenArea();
											glPopMatrix();
										}
									}
								}
							}
						}
					}
				}
				if (G8 != 1)
				{
					glPushMatrix();
					glTranslatef(4, 1.05, -16.5);
					GreenArea();
					glPopMatrix();
				}
				else
				{
					if (G8 != 1 && F8 != 1)
					{
						glPushMatrix();
						glTranslatef(4, 1.05, -16.5);
						GreenArea();
						glPopMatrix();
						glPushMatrix();
						glTranslatef(6, 1.05, -16.5);
						GreenArea();
						glPopMatrix();
					}
					else
					{
						if (G8 != 1 && F8 != 1 && E8 != 1)
						{
							glPushMatrix();
							glTranslatef(4, 1.05, -16.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(6, 1.05, -16.5);
							GreenArea();
							glPopMatrix();
							glPushMatrix();
							glTranslatef(8, 1.05, -16.5);
							GreenArea();
							glPopMatrix();
						}
						else
						{
							if (G8 != 1 && F8 != 1 && E8 != 1 && D8 != 1)
							{
								glPushMatrix();
								glTranslatef(4, 1.05, -16.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(6, 1.05, -16.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(8, 1.05, -16.5);
								GreenArea();
								glPopMatrix();
								glPushMatrix();
								glTranslatef(10, 1.05, -16.5);
								GreenArea();
								glPopMatrix();
							}
							else
							{
								if (G8 != 1 && F8 != 1 && E8 != 1 && D8 != 1 && C8 != 1)
								{
									glPushMatrix();
									glTranslatef(4, 1.05, -16.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(6, 1.05, -16.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(8, 1.05, -16.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(10, 1.05, -16.5);
									GreenArea();
									glPopMatrix();
									glPushMatrix();
									glTranslatef(12, 1.05, -16.5);
									GreenArea();
									glPopMatrix();
								}
								else
								{
									if (G8 != 1 && F8 != 1 && E8 != 1 && D8 != 1 && C8 != 1 && B8 != 1)
									{
										glPushMatrix();
										glTranslatef(4, 1.05, -16.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(6, 1.05, -16.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(8, 1.05, -16.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(10, 1.05, -16.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(12, 1.05, -16.5);
										GreenArea();
										glPopMatrix();
										glPushMatrix();
										glTranslatef(14, 1.05, -16.5);
										GreenArea();
										glPopMatrix();
									}
									else
									{
										if (G8 != 1 && F8 != 1 && E8 != 1 && D8 != 1 && C8 != 1 && B8 != 1 && A8 != 1)
										{
											glPushMatrix();
											glTranslatef(4, 1.05, -16.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(6, 1.05, -16.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(8, 1.05, -16.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(10, 1.05, -16.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(12, 1.05, -16.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(14, 1.05, -16.5);
											GreenArea();
											glPopMatrix();
											glPushMatrix();
											glTranslatef(16, 1.05, -16.5);
											GreenArea();
											glPopMatrix();
										}
									}
								}
							}
						}
					}
				}
		}
	}

	/* - ShowBoard - */


	/* -MovePawn- */

	if (states == 13)
	{
		glPushMatrix();
		glPushMatrix();
		glTranslatef(16, 1.05, -6.5);
		GreenArea();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(16, 1.05, -8.5);
		GreenArea();
		glPopMatrix();
		select = 1;
		glPopMatrix();
	if (states == 13 && go == 14)
		{
		
		}
	}
	else
	{
		select = 0;
		go = 0;
	}
	


	//Drawn_Button();
	//glutSwapBuffers();

	glFlush(); // Process all OpenGL routines as quickly as possible.
	glMatrixMode(GL_PROJECTION);

}
void reshape(int w, int h) {
	float aspect = (float)w / h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (aspect >= 1.0) {
		glOrtho(left*aspect, right*aspect, bottom, top, znear, zfar);
	}
	else {
		glOrtho(left, right, bottom / aspect, top / aspect, znear, zfar);
	}
	glutPostRedisplay();
}

float r = 0;
void keyboard(unsigned char c, int w, int h) {
	switch (c) {
	
	case'.':
		xView = 1;
		yView = 0;
		zView = 0;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 0;
		break;
	case'0':
		xView = 0;
		yView = 0;
		zView = -1;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 0;
		break;
	case '1':
		xView = -2.5;
		yView = -2;
		zView = -3;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 0;
		break;
	case '2':
		xView = 0;
		yView = -5;
		zView = -4;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 1;
		break;
	case'3':
		xView = 2.5;
		yView = -2;
		zView = -3;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 0;
		break;
	case'4':
		xView = -3;
		yView = -2;
		zView = 0;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 0;
		break;
	case'6':
		xView = 3;
		yView = -2;
		zView = 0;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 0;
		break;
	case'7':
		xView = -3;
		yView = -2;
		zView = 3;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 0;
		break;
	case'8':
		xView = 0;
		yView = -5;
		zView = 4;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = -1;
		break;
	case'9':
		xView = 3;
		yView = -2;
		zView = 3;
		xLookAt = 0;
		yLookAt = 0;
		zLookAt = 0;
		break;

	}
	glutPostRedisplay();
}
void idle() {
	phi += deltaPhi;
	glutPostRedisplay();
}


void main(int argc, char** argv) {
	// initializing routine
	glutInit(&argc, argv); // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Set display mode.
	glutInitWindowPosition(win_position_x, win_position_y); //Set top-left display-window position.
	glutInitWindowSize(win_width, win_height); // Set display-window width and height.
	glutCreateWindow("My Chess"); // Create display window.


								  //user initialization routine
	init(); // user initializing routine
	glEnable(GL_DEPTH_TEST);

	//callback register function
	glutDisplayFunc(display); // Send graphics to display window.

							  //glutMotionFunc(motion); // callback for mouse motion
	glutReshapeFunc(reshape); // detect windows change
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(idle);
	glutMainLoop(); // Loop over registered function
					// Display everything and wait.
}

 
//ถามอ.เรื่องการเดิน
// แสดงหมดแล้ว ฝั่งแดง ทำให้เดิน