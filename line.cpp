#include <iostream>
#include <stdlib.h>
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#define PI 3.1417
#define DEG2RAD(deg) (deg * PI / 180)

using namespace std;

//design board and set constraint 
class StartLine{
	public:
		float x1,y1,x2,y2;

		void drawLine(){
			glColor3f(0,0,0);
			glBegin(GL_LINES);
				glVertex3f(x1, y1, 0);
				glVertex3f(x2, y2, 0);
			glEnd();

			float a1=(x1>0) ? x1-0.15 : x1 + 0.15;
			float b1=(y1>0) ? y1-0.15 : y1 + 0.15;
			float a2=(x2>0) ? x2-0.15 : x2 + 0.15;
			float b2=(y2>0) ? y2-0.15 : y2 + 0.15;

			glBegin(GL_LINES);
				glVertex3f(a1, b1, 0);
				glVertex3f(a2, b2, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(a1, b1, 0);
				glVertex3f(x1, y1, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(a2, b2, 0);
				glVertex3f(x2, y2, 0);
			glEnd();
		}

		void drawCircle(float a, float b, float rad){

			glTranslatef(a,b,0);
			glColor3f(244.0/244, 0.0/244, 0.0/244);
		   	glBegin(GL_TRIANGLE_FAN);
		   	for(float i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   	}
		   	glEnd();
		}

		void drawArrow()
		{    
		    //line
		    glLineWidth(2);
			    glBegin(GL_LINES);
			    glVertex3f(1.8,-1.8,0.0);
			    glVertex3f(0.6,-0.6,0);
		    glEnd();
		    
		    //arc
		    glPushMatrix();
		    glTranslatef(0.8, -0.8, 0.0f);
			    glBegin(GL_POINTS);
				    for(int i=0;i<270;++i)
				      {
				      glVertex3f(0.3*cos(3.14159*i/180),0.3*sin(3.14159*i/180),0);
				      }
			    glEnd();
		    glPopMatrix();

		    //triangles
		    glPushMatrix();
			    glTranslatef(0.78,-1.1, 0.0);
			    glRotatef(15, 0.0f, 0.0f, 1.0f);
			    glScalef(0.05f, 0.05f, 0.05f);
			    drawTriangle();
		    glPopMatrix();
		    glPushMatrix();
			    glTranslatef(1.08,-0.8, 0.0);
			    glRotatef(45, 0.0f, 0.0f, 1.0f);
			    glScalef(0.05f, 0.05f, 0.05f);
			    drawTriangle();
		    glPopMatrix();
		    glPushMatrix();
			    glTranslatef(1.82,-1.8, 0.0);
			    glRotatef(-15, 0.0f, 0.0f, 1.0f);
			    glScalef(0.05f, 0.05f, 0.05f);
			    drawTriangle();
		    glPopMatrix();

		}

		void drawBall(float rad) {
		    
		   glBegin(GL_TRIANGLE_FAN);
		   for(int i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   }
		   glEnd();
		}

		void drawTriangle() {
		    glBegin(GL_TRIANGLES);
		    glColor3f(0,0,0);
		    glVertex3f(0.0f, 1.0f, 0.0f);
		    glColor3f(0,0,0);
		    glVertex3f(-1.0f, -1.0f, 0.0f);
		    glColor3f(0,0,0);
		    glVertex3f(1.0f, -1.0f, 0.0f);
		    glEnd();
		}
};