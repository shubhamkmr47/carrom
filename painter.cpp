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

class Draw{
	public:
		void drawBox(float len){

			glBegin(GL_QUADS);
		    	glColor3f(232.0/248, 170.0/248, 84.0/248);
			    glVertex3f(-len / 2, -len / 2, 0);
			    glVertex3f(len / 2, -len / 2, 0);
			    glVertex3f(len / 2, len / 2, 0);
			    glVertex3f(-len / 2, len / 2, 0);
	    	glEnd();

		    len=len+0.6f;
		    glBegin(GL_QUADS);
			    glColor3f(0/248, 0/248, 0/248);
			    glVertex3f(-len / 2, -len / 2, 0);
			    glVertex3f(len / 2, -len / 2, 0);
			    glColor3f(43.0/248, 29.0/248, 17.0/248);
			    glVertex3f(len / 2, len / 2, 0);
			    glVertex3f(-len / 2, len / 2, 0);

		    glEnd();
		}

		void drawPocket(float rad, float len, float x, float y, float z ) {
		   glTranslatef(x, y, z);	
		   glColor4f(0.0/248, 33.0/248, 0.0/248 , 0.9);
		   glBegin(GL_TRIANGLE_FAN);
		   for(float i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   }
		   glEnd();
		}

		void drawCenter(float rad){
		   glPointSize(2);
		   glColor3f(31.0/244,31.0/244,31.0/244);
		   glBegin(GL_POINTS);
		   for(float i=0 ; i<360 ; i=i+0.1) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   }
		   glEnd();



		   rad = 0.1;
		   glColor3f(232.0/248, 170.0/248, 84.0/248);
		   glBegin(GL_TRIANGLE_FAN);
		   for(float i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   }
		   glEnd();

		   glPointSize(5);
		   glColor3f(0.0/248, 0.0/248, 0.0/248);
		   glBegin(GL_POINTS);
		   for(float i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   }
		   glEnd();
		   glPointSize(1.8);


		    int angle=0,i,j;
		    float centre_rad = 0.68,centre_centre_rad = 0.1;
			float radius=centre_rad-0.08f;
			float small=centre_centre_rad +0.02f;

			for(j=0;j<3;j++)
			
				for(angle=0,i=0;i<8;i++,angle+=45){
					if(j==0 || j==2){
						glPushMatrix();
							glRotatef(angle,0.0f,0.0f,0.1f);
						if(i%2==0)
							glColor3f(184.0/244,13.0/244,13.0/244);
						else
							glColor3f(0.0,0.0,0.0);
						if(j==0)
							drawTriangle(0.0f,radius*cos(DEG2RAD(0)),
								small*cos(DEG2RAD(-90)),0.0f,
								radius*sin(DEG2RAD(0)),small*sin(DEG2RAD(-90)));
					else
						drawTriangleOutline(0.0f,radius*cos(DEG2RAD(0)),
							small*cos(DEG2RAD(-90)),0.0f,
							radius*sin(DEG2RAD(0)),small*sin(DEG2RAD(-90)));
					glPopMatrix();
					}
					if(j==1 || j==2){
						glPushMatrix();
							glRotatef(angle,0.0f,0.0f,0.1f);
							glColor3f(232.0/248, 170.0/248, 84.0/248);
							if(j==1)
								drawTriangle(0.0f,radius*cos(DEG2RAD(-45)),
									small*cos(DEG2RAD(90-45)),0.0f,
									radius*sin(DEG2RAD(0-45)),
									small*sin(DEG2RAD(+90-45)));
							else
								drawTriangleOutline(0.0f,radius*cos(DEG2RAD(0-45)),
									small*cos(DEG2RAD(90-45)),0.0f
									,radius*sin(DEG2RAD(0-45))
									,small*sin(DEG2RAD(+90-45)));

						glPopMatrix();
					}
				}
			}

		void drawTriangle(float x1,float x2,float x3,float y1,float y2,float y3) {
		glBegin(GL_TRIANGLES);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x3, y3, 0.0f);
		glEnd();
		}

		void drawTriangleOutline(float x1,float x2,float x3,float y1,float y2,float y3) {
		glBegin(GL_LINE_LOOP);
		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x3, y3, 0.0f);
		glEnd();
		}
};
