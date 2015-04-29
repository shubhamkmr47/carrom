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

//Digital display of score
//lowest score is -99
class Scoreboard{

	public:

		float x, y, flag;

		Scoreboard(){
			this->x=-3.5;
			this->y=0;
			this->flag=0;
		}

		void getScore(int value){

			if(value==0)
				draw(0);
			if(value<-99)
				value = -99;
			if(value<0){
				flag=1;
				value *= -1;
			}

			while (value!=0){
				draw(value%10);
				value = value/10;
				x=x-0.7;
				y=0;
			}
			if(flag==1){
				draw(-1);
			}	

			x=-3.5;
			y=0;
		}

		void draw(int digit){

			if(digit==-1){
				print(6);
			}

			if(digit==0){
				print(1);
				print(2);
				print(3);
				print(4);
				print(5);
				print(7);
			}

			if(digit==1){
				print(1);
				print(2);
			}

			if(digit==2){
				print(5);
				print(1);
				print(6);
				print(4);
				print(7);
			}

			if(digit==3){
				print(5);
				print(1);
				print(6);
				print(2);
				print(7);
			}

			if(digit==4){
				print(3);
				print(1);
				print(6);
				print(2);
			}

			if(digit==5){
				print(3);
				print(5);
				print(6);
				print(2);
				print(7);
			}

			if(digit==6){
				print(3);
				print(5);
				print(6);
				print(2);
				print(7);
				print(4);
			}

			if(digit==7){
				print(1);
				print(5);
				print(2);
			}

			if(digit==8){
				print(3);
				print(5);
				print(6);
				print(2);
				print(7);
				print(1);
				print(4);
			}
			if(digit==9){
				print(3);
				print(5);
				print(6);
				print(2);
				print(7);
				print(1);
			}
		}

		void print(int i){

			if(i==1)
				line(x,y+0.5,x,y);
			if(i==2)
				line(x,y,x,y-0.5);
			if(i==3)
				line(x-0.5,y+0.5,x-0.5,y);
			if(i==4)
				line(x-0.5,y,x-0.5,y-0.5);
			if(i==5)
				line(x,y+0.5,x-0.5,y+0.5);
			if(i==6)
				line(x,y,x-0.5,y);
			if(i==7)
				line(x,y-0.5,x-0.5,y-0.5);
		}

		void line(float x1, float y1, 
			float x2, float y2){

			glColor3f(1,1,1);
			glLineWidth(10);
			glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
			glEnd();
			glLineWidth(2);
		}

		void drawCover(){
			glBegin(GL_QUADS);
				glColor3f(2.0/244,28.0/244,2.0/244);
				glVertex2f(-3,1);
				glVertex2f(-3,-1);
				glVertex2f(x-2,-1);
				glVertex2f(x-2,1);
			glEnd();
		}	
};