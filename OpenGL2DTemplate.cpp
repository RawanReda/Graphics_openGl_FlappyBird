//  Includes
#include <stdlib.h>
#include <cmath>
#include <random>
#include <time.h>
#include <glut.h>
#include <string.h>
#include <algorithm>
#include <iostream> 
using namespace std;
#include <stdio.h>
#include <string.h>
#include <glut.h>
#include <iomanip>
#include <dos.h>
#include <windows.h>
#include <playsoundapi.h>
#include <mmsystem.h>
#include <tchar.h>

//  Methods Signatures
void drawRect(int x, int y, int w, int h);
void drawBird(int x, float r);
void drawBarrier(int x, int y, int w, int h);
void Key(unsigned char key, int x, int y);
void Timer(int value);
void collision();
void Display();
int getNewX(int val);


//  Global Variables
int index = 0;
int score = 0;
float bar = 0;
int upPlayer = 0;
float downPlayer = 0;
int movePlayer = 0;
int arr[3] = { 1,2,3};
int currentSet=-1;
int lives = 3;
bool poweron1 = false;
bool poweron2 = false;
bool endgame = false;
float r = 0.5;
float g = 0;
float b = 0.4;
bool win = false;
// Classes
class barrier {
public:
	int x;
	int y;
	int w;
	int h;
};
barrier bars_set1[6];
barrier bars_set2[6];
barrier bars_set3[6];

class powerup {
public:
	int x;
	int y;
	int w;
	int h;
};
powerup p_s1;
powerup p_s2;
//---------------------------------------------------------------------------------------

void print(int x, int y, char* string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void main(int argc, char** argr) {

	glutInit(&argc, argr);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Flappy Bird Replica");

	glutDisplayFunc(Display);
	glutKeyboardFunc(Key);
	glutTimerFunc(0, Timer, 0); // sets the Timer handler function; which runs every `Threshold` milliseconds (1st argument)
	glutIdleFunc(collision);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.8f, 1.0f, 1.0f, 0.0f);
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
	srand(time(0));
	std::random_shuffle(&arr[0], &arr[3]);
	glutMainLoop();
	
}
void drawBird1(int x, int y, float r) {
	glPushMatrix();
	glColor3b(0, 0, 1);
	glTranslatef(x, y, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}
void collision() {

	if (movePlayer >= 400 - 20 || movePlayer <= 20) {
		movePlayer = 200;
		upPlayer = 0;
		downPlayer = 0;
		endgame = true;
	}

	else if (currentSet == 1 && !poweron1) {

		if (p_s1.x <= 50 && p_s1.x >= 0 && movePlayer + 20 >= 160 && movePlayer + 20 <= 180) {
			PlaySound(TEXT("sound/jumpSound.wav"), NULL, SND_ASYNC | SND_FILENAME );

			poweron1 = true;
		}
		for (int i = 0; i < 6; i++) {
			if (bars_set1[i].h > 0) {

				if(((bars_set1[i].x) <= 50 && (bars_set1[i].x) >= -20 && (movePlayer - 20 <= bars_set1[i].h)) || ((bars_set1[i].x) == 50 && (movePlayer <= bars_set1[i].h))){
					lives--;
					PlaySound(TEXT("sound/jumpSound.wav"), NULL, SND_ASYNC| SND_FILENAME );

					//PlaySoundA((LPCSTR)"sound/jumpSound.wav", NULL, SND_FILENAME | SND_ASYNC);
						upPlayer = 0;
						downPlayer = 0;
						movePlayer = 200;
						break;
				}
			}
			else {
				
				if (((bars_set1[i].x) <= 50 && (bars_set1[i].x) >= -20 && (movePlayer + 50 >= 400+bars_set1[i].h)) || ((bars_set1[i].x) == 50 && (movePlayer >= 400+bars_set1[i].h))) {
					//PlaySoundA((LPCSTR)"sound/jumpSound.wav", NULL, SND_FILENAME | SND_ASYNC);
					PlaySound(TEXT("sound/jumpSound.wav"), NULL, SND_ASYNC| SND_FILENAME );

						lives--;
						upPlayer = 0;
						downPlayer = 0;
						movePlayer = 200;
						break;
				}
			}
		}
}
	else if (currentSet == 2 && !poweron2) {
		if (p_s2.x <= 50 && p_s2.x >= 0 && movePlayer + 20 >= 160 && movePlayer + 20 <= 180) {
			PlaySound(TEXT("sound/PowerUp3.wav"), NULL, SND_ASYNC | SND_FILENAME );
			poweron2 = true;
		}
		for (int i = 0; i < 6; i++) {
			if (bars_set2[i].h > 0) {
				if (((bars_set2[i].x) <= 50 && (bars_set2[i].x) >= -20 && (movePlayer - 20 <= bars_set2[i].h)) || ((bars_set2[i].x) == 50 && (movePlayer <= bars_set2[i].h))) {
					lives--;
					PlaySound(TEXT("sound/jumpSound.wav"), NULL, SND_ASYNC| SND_FILENAME  );
					//PlaySoundA((LPCSTR)"sound/jumpSound.wav", NULL, SND_FILENAME | SND_ASYNC);

					upPlayer = 0;
					downPlayer = 0;
					movePlayer = 200;
					break;
				}
			}
			else {
				if (((bars_set2[i].x) <= 50 && (bars_set2[i].x) >= -20 && (movePlayer + 50 >= 400 + bars_set2[i].h)) || ((bars_set2[i].x) == 50 && (movePlayer >= 400 + bars_set2[i].h))) {
					lives--;
					PlaySound(TEXT("sound/jumpSound.wav"), NULL, SND_ASYNC| SND_FILENAME );

					//PlaySoundA((LPCSTR)"sound/jumpSound.wav", NULL, SND_FILENAME | SND_ASYNC);

					upPlayer = 0;
					downPlayer = 0;
					movePlayer = 200;
					break;
				}
			}
		}
	}
	else if (currentSet == 3) {
		for (int i = 0; i < 6; i++) {
			if (bars_set3[i].h > 0) {
				if (((bars_set3[i].x) <= 50 && (bars_set3[i].x) >= -20 && (movePlayer - 20 <= bars_set3[i].h)) || ((bars_set3[i].x) == 50 && (movePlayer <= bars_set3[i].h))) {
					lives--;
					//PlaySoundA((LPCSTR)"sound/jumpSound.wav", NULL, SND_FILENAME | SND_ASYNC);
					PlaySound(TEXT("sound/jumpSound.wav"), NULL, SND_ASYNC| SND_FILENAME );

					upPlayer = 0;
					downPlayer = 0;
					movePlayer = 200;
					break;
				}
			}
			else {

				if (((bars_set3[i].x) <= 50 && (bars_set3[i].x) >= -20 && (movePlayer + 50 >= 400 + bars_set3[i].h)) || ((bars_set3[i].x) == 50 && (movePlayer >= 400 + bars_set3[i].h))) {

					lives--;
					//PlaySoundA((LPCSTR)"sound/jumpSound.wav", NULL, SND_FILENAME | SND_ASYNC);
					PlaySound(TEXT("sound/jumpSound.wav"), NULL, SND_ASYNC| SND_FILENAME );

					upPlayer = 0;
					downPlayer = 0;
					movePlayer = 200;
					break;
				}
			}
		}
	}
	glutPostRedisplay();
}

void Key(unsigned char key, int x, int y) {
	if (key == 'a') {
		upPlayer += 20;
	}
	glutPostRedisplay();
}


// draws rectangles using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawRect(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}

void drawRectTop(int x, int y, int w, int h) {
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}
void drawPowerUp(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
	w -= 10;
	h -= 10;
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3b(1, 0, 1);
	glVertex2f(x + 5, y + 5);
	glVertex2f(x + w + 5, y + 5);
	glVertex2f(x + w + 5, y + h + 5);
	glVertex2f(x + 5, y + h + 5);
	glEnd();
	glPopMatrix();
}
void create_set1(int x) {

	int index = 0;
	bars_set1[index].x = 60 + x - bar;
	bars_set1[index].y = 0;
	bars_set1[index].w = 60;
	bars_set1[index].h = 150;
	drawBarrier(bars_set1[index].x, bars_set1[index].y, bars_set1[index].w, bars_set1[index].h);

	index++;
	bars_set1[index].x = 60 + x - bar;
	bars_set1[index].y = 400;
	bars_set1[index].w = 60;
	bars_set1[index].h = -100;
	drawBarrier(bars_set1[index].x, bars_set1[index].y, bars_set1[index].w, bars_set1[index].h);

	index++;
	bars_set1[index].x = 200 + x - bar;
	bars_set1[index].y = 0;
	bars_set1[index].w = 60;
	bars_set1[index].h = 130;
	drawBarrier(bars_set1[index].x, bars_set1[index].y, bars_set1[index].w, bars_set1[index].h);

	index++;
	bars_set1[index].x = 200 + x - bar;
	bars_set1[index].y = 400;
	bars_set1[index].w = 60;
	bars_set1[index].h = -140;
	drawBarrier(bars_set1[index].x, bars_set1[index].y, bars_set1[index].w, bars_set1[index].h);

	index++;
	bars_set1[index].x = 340 + x - bar;
	bars_set1[index].y = 0;
	bars_set1[index].w = 60;
	bars_set1[index].h = 30;
	drawBarrier(bars_set1[index].x, bars_set1[index].y, bars_set1[index].w, bars_set1[index].h);

	index++;
	bars_set1[index].x = 340 + x - bar;
	bars_set1[index].y = 400;
	bars_set1[index].w = 60;
	bars_set1[index].h = -100;
	drawBarrier(bars_set1[index].x, bars_set1[index].y, bars_set1[index].w, bars_set1[index].h);


	p_s1.x = 340 + x - bar;
	p_s1.y = 160;
	p_s1.w = 20;
	p_s1.h = 20;
	if (!poweron1)
		drawPowerUp(340 + x - bar, 160, 20, 20);

}
void create_set2(int x) {

	int index = 0;
	bars_set2[index].x = 60 + x - bar;
	bars_set2[index].y = 0;
	bars_set2[index].w = 60;
	bars_set2[index].h = 100;
	drawBarrier(bars_set2[index].x, bars_set2[index].y, bars_set2[index].w, bars_set2[index].h);

	index++;
	bars_set2[index].x = 60 + x - bar;
	bars_set2[index].y = 400;
	bars_set2[index].w = 60;
	bars_set2[index].h = -100;
	drawBarrier(bars_set2[index].x, bars_set2[index].y, bars_set2[index].w, bars_set2[index].h);

	index++;
	bars_set2[index].x = 200 + x - bar;
	bars_set2[index].y = 0;
	bars_set2[index].w = 60;
	bars_set2[index].h = 60;
	drawBarrier(bars_set2[index].x, bars_set2[index].y, bars_set2[index].w, bars_set2[index].h);
	p_s2.x = 200 + x - bar;
	p_s2.y = 160;
	p_s2.w = 20;
	p_s2.h = 20;

	index++;
	bars_set2[index].x = 200 + x - bar;
	bars_set2[index].y = 400;
	bars_set2[index].w = 60;
	bars_set2[index].h = -140;
	drawBarrier(bars_set2[index].x, bars_set2[index].y, bars_set2[index].w, bars_set2[index].h);

	index++;
	bars_set2[index].x = 340 + x - bar;
	bars_set2[index].y = 400;
	bars_set2[index].w = 60;
	bars_set2[index].h = -30;
	drawBarrier(bars_set2[index].x, bars_set2[index].y, bars_set2[index].w, bars_set2[index].h);

	index++;
	bars_set2[index].x = 340 + x - bar;
	bars_set2[index].y = 0;
	bars_set2[index].w = 60;
	bars_set2[index].h = 100;
	drawBarrier(bars_set2[index].x, bars_set2[index].y, bars_set2[index].w, bars_set2[index].h);

	if (!poweron2)
		drawPowerUp(200 + x - bar, 160, 20, 20);
}

void create_set3(int x) {

	int index = 0;
	bars_set3[index].x = 60 + x - bar;
	bars_set3[index].y = 0;
	bars_set3[index].w = 60;
	bars_set3[index].h = 40;
	drawBarrier(bars_set3[index].x, bars_set3[index].y, bars_set3[index].w, bars_set3[index].h);


	index++;
	bars_set3[index].x = 60 + x - bar;
	bars_set3[index].y = 400;
	bars_set3[index].w = 60;
	bars_set3[index].h = -50;
	drawBarrier(bars_set3[index].x, bars_set3[index].y, bars_set3[index].w, bars_set3[index].h);

	index++;
	bars_set3[index].x = 200 + x - bar;
	bars_set3[index].y = 0;
	bars_set3[index].w = 60;
	bars_set3[index].h = 150;
	drawBarrier(bars_set3[index].x, bars_set3[index].y, bars_set3[index].w, bars_set3[index].h);

	index++;
	bars_set3[index].x = 200 + x - bar;
	bars_set3[index].y = 400;
	bars_set3[index].w = 60;
	bars_set3[index].h = -60;
	drawBarrier(bars_set3[index].x, bars_set3[index].y, bars_set3[index].w, bars_set3[index].h);

	index++;
	bars_set3[index].x = 340 + x - bar;
	bars_set3[index].y = 400;
	bars_set3[index].w = 60;
	bars_set3[index].h = -120;
	drawBarrier(bars_set3[index].x, bars_set3[index].y, bars_set3[index].w, bars_set3[index].h);

	index++;
	bars_set3[index].x = 340 + x - bar;
	bars_set3[index].y = 0;
	bars_set3[index].w = 60;
	bars_set3[index].h = 100;
	drawBarrier(bars_set3[index].x, bars_set3[index].y, bars_set3[index].w, bars_set3[index].h);

}


void Timer(int value) {

	score++;

	movePlayer = 200 + upPlayer - downPlayer;
	downPlayer += 1;
	bar += 0.5f;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 0);
}
void drawTriangle(int x, int y, int w, int h) {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(1 , 0.8 ,1); 
	glVertex2f(x + 20, y);
	glVertex2f(x + 30,y + (h+20));
	glVertex2f(x + 40, y );
	glEnd();
	glPopMatrix();
}
void drawTriangleUp(int x, int y, int w, int h) {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.8, 1);
	glVertex2f(x + 20, y );
	glVertex2f(x + 30, y +(h-20));
	glVertex2f(x + 40, y );
	glEnd();
	glPopMatrix();
}
void drawBarrier(int x, int y, int w, int h) {
	
	//glColor3f(0, 1, 1);
	glPushMatrix();
	glColor3f(r, g, b);
	drawRect(x, y, w , h - 30);
	glPopMatrix();
	glPushMatrix();
	glColor3f(r ,g , b);
	drawRectTop(x, y + (h - 30), w, 30);
	glPopMatrix();

	glPushMatrix();
	//glColor3d(1, 0, 0);
	drawTriangle(x, 0, 5, 5);
	drawTriangleUp(x, 400, -5, -5);
	glPopMatrix();
	

	

}


void drawBird(int x, float r) {
	glPushMatrix();
	glColor3f(0.9 , 1 ,0.3); // red
	glTranslatef(x, movePlayer, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f(0 ,0.4 , 0.3); // red
	glVertex2f(x + 10, movePlayer - 5);
	glVertex2f(x + 30, movePlayer + 5);
	glVertex2f(x + 20, movePlayer + 10);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0); // red
	glVertex2f(x + 3, movePlayer + 8);
	glVertex2f(x + 7, movePlayer + 8);
	glVertex2f(x + 7, movePlayer + 3);
	glVertex2f(x + 3, movePlayer + 3);

	glEnd();

	glPushMatrix();

}

int getNewX(int pos) {
	int shiftedX = 0;
	if (pos == 0)
		shiftedX = 0;
	else if (pos == 1)
		shiftedX = 400;
	else
		shiftedX = 800;

	return shiftedX;
}

void drawGameOverScreen() {
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(400, 0);
	glVertex2f(400, 400);
	glVertex2f(0, 400);
	glEnd();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);


	glPushMatrix();
	drawBird(30, 20);
	glPopMatrix();


	glPushMatrix();
	currentSet = arr[index];
	int newx = getNewX(index);

			switch (currentSet) {
			case 1:
				if (poweron1) {
					r = 1;
					g = 0;
					b = 0;
				}
				else {
					r = 0.5;
					g = 0;
					b = 0.4;
				}
				create_set1(newx);
				if (bars_set1[5].x == -50) {
					index++;
					currentSet = arr[index];			
			    }
				break;
			case 2:
				if (poweron2) {
					r = 1;
					g = 0;
					b = 0;
				}
				else {
					r = 0.4;
					g = 1;
					b = 0;
					
				}
				create_set2(newx);
				if (bars_set2[5].x == -50) {
					index++;
					currentSet = arr[index];
				}
				break;
			case 3:
				r = 0.9;
				g = 0.6;
				b = 0;
				create_set3(newx);
				if (bars_set3[5].x == -50) {
					index++;
					currentSet = arr[index];
				}
				break;
			}
			
	glPopMatrix();

	if (!win) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		char* p0s[40];
		sprintf((char*)p0s, "Lives: %d, Score %d", lives, score);
		print(100, 350, (char*)p0s);
		glPopMatrix();
	}
	if (currentSet > 100) {
		win = true;
		char* p0s[40];
		glColor3f(1, 0, 0);
		sprintf((char*)p0s, "Great Job! You made it!!", lives, score);
		print(100, 200, (char*)p0s);
	}
	else if (lives < 1 || endgame) {
		glColor3b(1, 1, 1);
		drawGameOverScreen();
		char* p0s[40];
		glColor3f(1, 0, 0);
		sprintf((char*)p0s, "Hard Luck!", lives, score);
		print(130, 200, (char*)p0s);
	}

	

	glFlush();
}