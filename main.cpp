#include <iostream>
#include <stdlib.h>
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <sys/time.h>

#include "painter.cpp"
#include "line.cpp"
#include "striker.cpp"
#include "coin.cpp"
#include "scoreboard.cpp"

#define PI 3.1417
#define DEG2RAD(deg) (deg * PI / 180)

using namespace std;

//Global variables
float len=5.0f;
float _angle = 0;
float originX = 0, originY = 0;
int flagStriker = 0;
int activeStriker = 1;
int coinActive = 0;
int i = 0, j = 0 ;
struct timeval tim;
double t1, t2;
int totalScore = 0;
float mouseX, mouseY;

Striker strik;
CarromCoin coinObject[19];
Scoreboard scoreObject;

void handleKeypress1(unsigned char key, int x, int y); 
void handleKeypress2(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void initRendering();
void handleResize(int w, int h);
void rotate();
void drawScene();
void update(int value);
void rotateBox(int value);
void arrangeCoin();
void checkRight();
void checkLeft();
void mouseDrag(int x, int y);
void pickStriker();

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	gettimeofday(&tim,NULL);
    t1 = tim.tv_sec+(tim.tv_usec/1000000.0);
	
	int windowWidth = glutGet(GLUT_SCREEN_WIDTH);
    int windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0,0);
	
	//Create the window
	glutCreateWindow("Carrom Extreme");
	initRendering();
	
	arrangeCoin();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
	glutReshapeFunc(handleResize);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseDrag);

	glutTimerFunc(1, update, 0); //Add a timer	
	glutMainLoop();
	return 0;
}

//Called when a key is pressed
void handleKeypress1(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;

		case 32: //SPACE key
			flagStriker = 1;
			activeStriker = 0;
			break;

		case 'a':
			if(activeStriker == 1)
				strik.dirLeft();
			break;

		case 'd':
			if(activeStriker == 1)
				strik.dirRight();
			break;

		case 'w':
			if(activeStriker == 1)
				strik.increaseVel();
			break;

		case 's':
			if(activeStriker == 1)
				strik.decreaseVel();
			break;				
	}
}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT && activeStriker == 1)
        strik.moveLeft();
    if (key == GLUT_KEY_RIGHT && activeStriker == 1) 
        strik.moveRight();
    if (key == GLUT_KEY_UP && activeStriker == 1)
        strik.moveUp();
    if (key == GLUT_KEY_DOWN && activeStriker == 1){
        strik.moveDown();
    }  
}

void mouse(int button, int state, int x, int y){
   
   // Wheel reports as button 3(scroll up) and button 4(scroll down)
   if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
   		flagStriker = 1;
   		activeStriker = 0;
   }

   if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
   		//flagStriker = 1;
   		//activeStriker = 0;
   		//strik.angle = atan((float)(mouseY - strik.posY)/(mouseX-strik.posX))*(180/PI);
   		//strik.setVel();
   		//strik.chooseDir();
   }

   if (button == 3 ){
   		if(activeStriker == 1)
				strik.increaseVel();
   }
   if(button == 4 ){
   		if(activeStriker == 1)
				strik.decreaseVel();
   }
}

//Initializes rendering
void initRendering() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	glEnable(GL_COLOR_MATERIAL); //Enable color
	glClearColor(0.0/248, 33.0/248, 0.0/248,0.0f); //Change the background to green
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

/*void rotate(){
	_angle += 2.0f;
		if (_angle > 360) {
			_angle -= 360;
	}
}*/

//Draws the carrom board
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	void initiate();

	Draw drawObject;

    glTranslatef(originX+1, originY, -8.0f);

    if(activeStriker==1){
	    
	    glPushMatrix();
	    strik.chooseDir();
	    glPopMatrix();

	    glPushMatrix();
	    strik.getVel();
	    glPopMatrix();
		}

		strik.x1 = -len/2 + 0.5;
		strik.y1 = -len/2 + 0.5;
		strik.x2 = +len/2 - 0.5;
		strik.y2 = -len/2 + 0.65;
			
	glPushMatrix();
	glTranslatef(strik.posX, strik.posY , 0);
	strik.drawStriker();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(coinObject[0].posX, coinObject[0].posY,0);
    coinObject[0].drawCoin(5);
    glPopMatrix();

    //show coins
    int color;
    for (int i = 1; i < 7; ++i)
    {
    	if( i % 2 == 0)
    		color = 1;
    	else
    		color = 0;
    	glPushMatrix();
		glTranslatef(coinObject[i].posX, coinObject[i].posY ,0);
		coinObject[i].drawCoin(color);
		glPopMatrix();
    }

    for (int i = 7; i < 19; ++i)
    {
    	if( i % 2 == 0)
    		color = 1;
    	else
    		color = 0;
    	glPushMatrix();
		glTranslatef(coinObject[i].posX ,  coinObject[i].posY, 0);
		coinObject[i].drawCoin(color);
		glPopMatrix();
    }

    glPushMatrix();
    drawObject.drawPocket(0.2f, len, -len/2 + 0.2,-len/2 + 0.2, 0);
    glPopMatrix();
	
    glPushMatrix();
    drawObject.drawPocket(0.2f, len, -len/2 + 0.2,+len/2 - 0.2, 0);
    glPopMatrix();

    glPushMatrix();
    drawObject.drawPocket(0.2f, len, +len/2 - 0.2,-len/2 + 0.2, 0);
    glPopMatrix();

    glPushMatrix();
    drawObject.drawPocket(0.2f, len, +len/2 - 0.2,+len/2 - 0.2, 0);
    glPopMatrix();

    glPushMatrix();
    drawObject.drawCenter(0.6f);
    glPopMatrix();

	StartLine lineObject;
    for(int z=0;z<4;z++){

	    glPushMatrix();
	    glRotatef(z*90,0,0,1);
	    glTranslatef(+0.3,-0.3,0);
	    lineObject.drawArrow();
	    glPopMatrix();
	    
	    glPushMatrix();
	    glRotatef(z*90,0,0,1);
	    lineObject.x1=-len/2+0.5;
	    lineObject.y1=-len/2+0.5;
	    lineObject.x2=+len/2-0.5;
	    lineObject.y2=-len/2+0.5;
	    lineObject.drawLine();
	    glPopMatrix();
	}

    for(int z=0;z<19;z++){
    	totalScore = totalScore + coinObject[z].score;
    }
    
    //check for 1 second 
    int time_;
	gettimeofday(&tim,NULL);
	double t2 = tim.tv_sec+(tim.tv_usec/1000000.0);
	time_ = int(t2 -t1);
	totalScore = totalScore - time_;

	if(totalScore < -99)
		totalScore = -99;

    glPushMatrix();
    scoreObject.getScore(totalScore);
    scoreObject.drawCover();
    glPopMatrix();
    totalScore = 100;

    glPushMatrix();
    drawObject.drawBox(len);
    glPopMatrix();
    
	glutSwapBuffers();
}

void update(int value) {

	//collsion with coins
	for(i=0 ; i < 19; i++){
		for(j = i+1; j<19 ; j++){
			if((sqrt(pow(coinObject[i].posX-coinObject[j].posX, 2)+pow(coinObject[i].posY-coinObject[j].posY, 2)) <= coinObject[i].rad + coinObject[j].rad) 
				&& coinObject[i].game ==1 && coinObject[j].game ==1 ){

				if((coinObject[i].posX - coinObject[j].posX)*(coinObject[i].velX - coinObject[j].velX) +
				 (coinObject[i].posY - coinObject[j].posY)*(coinObject[i].velY - coinObject[j].velY) < 0){
					float z1,z2,q1,q2,q11,q22,z;

					z1=coinObject[j].posX - coinObject[i].posX;
					z2=coinObject[j].posY - coinObject[i].posY;

					z=sqrt(z1*z1+z2*z2); // |z|

					q1=(z1*coinObject[i].velX + z2*coinObject[i].velY)/z;
					q2=(z1*coinObject[j].velX + z2*coinObject[j].velY)/z;

					// q1 = projection of v1 along z = v1.z/|z| = component of v1 along the direction of z
					// q2 = projection of v2 along z = v2.z/|z| = component of v2 along the direction of z

					float temp;
					temp =q1;
					q1 = q2;
					q2 = temp;

					// Interchange the velocities along the line fo collision

					q11=(z2*coinObject[i].velX - z1*coinObject[i].velY)/z;
					q22=(z2*coinObject[j].velX - z1*coinObject[j].velY)/z;

					coinObject[i].velX=((q1*z1+q11*z2)/z);
					coinObject[i].velY=((q1*z2-q11*z1)/z);
					coinObject[j].velX=((q2*z1+q22*z2)/z);
					coinObject[j].velY=((q2*z2-q22*z1)/z);
				}
			}

			if((sqrt(pow(coinObject[i].posX-coinObject[j].posX, 2)) + sqrt(pow(coinObject[i].posY-coinObject[j].posY, 2)) > coinObject[i].rad + coinObject[j].rad)){

        		coinObject[i].check();
        		coinObject[j].check();	
        	}		
		}
	}

	//striker collision with coins
	for(j=0; j < 19 ; j++)
	{

        if(sqrt(pow(strik.posX-coinObject[j].posX, 2)+pow(strik.posY-coinObject[j].posY, 2)) <= strik.rad + coinObject[j].rad 
        	&& coinObject[j].game == 1 && strik.game == 1){

				if((strik.posX - coinObject[j].posX)*(strik.velX - coinObject[j].velX) +
				 (strik.posY - coinObject[j].posY)*(strik.velY - coinObject[j].velY) < 0 && flagStriker==1){
					
					float z1,z2,q1,q2,q11,q22,z;

					z1=coinObject[j].posX - strik.posX;
					z2=coinObject[j].posY - strik.posY;

					z=sqrt(z1*z1+z2*z2); // |z|

					q1=(z1*strik.velX + z2*strik.velY)/z;
					q2=(z1*coinObject[j].velX + z2*coinObject[j].velY)/z;

					// q1 = projection of v1 along z = v1.z/|z| = component of v1 along the direction of z
					// q2 = projection of v2 along z = v2.z/|z| = component of v2 along the direction of z

					float temp;
					temp =q1;
					q1 = q2;
					q2 = temp;

					// Interchange the velocities along the line fo collision

					q11=(z2*strik.velX - z1*strik.velY)/z;
					q22=(z2*coinObject[j].velX - z1*coinObject[j].velY)/z;

					strik.velX=((q1*z1+q11*z2)/z);
					strik.velY=((q1*z2-q11*z1)/z);
					coinObject[j].velX=((q2*z1+q22*z2)/z);
					coinObject[j].velY=((q2*z2-q22*z1)/z);
				}
		}

		if(sqrt(pow(strik.posX-coinObject[j].posX, 2)) + pow(strik.posY-coinObject[j].posY, 2) > strik.rad + coinObject[j].rad){

        		strik.check();
        		coinObject[j].check();	
        }
		coinObject[j].strike();
		coinObject[j].deaccelerate();
	}

	//check for coins in motion
	for (i = 0; i < 19; i++)
	{
		if(coinObject[i].velX != 0 && coinObject[i].velY !=0){
			coinActive = 1;
			break; 
		}
		coinActive = 0;
	}		
	
	//hit stirker	
	if(flagStriker == 1)
		strik.strike();

	//striker apply friction
	if(flagStriker == 1)
		strik.deaccelerate();

	if(strik.velX == 0  && strik.velY==0  && activeStriker == 0 && coinActive == 0){
		strik.reset();
		flagStriker = 0;
		activeStriker = 1;
		strik.drawStriker();
	}

	glutPostRedisplay();
	glutTimerFunc(1, update, 0);
}

/*void rotateBox(int value) {

	if(_angle==90){
		_angle=0;
		return ;
	}
	_angle += 2.0f;
		if (_angle > 90) {
			_angle -= 90;
	}
	glutPostRedisplay();
	glutTimerFunc(10, rotateBox, 0);
}*/

void arrangeCoin(){
  	coinObject[0].posX = 0;
  	coinObject[0].posY = 0;
    for ( i = 1; i < 7; i++){
    	coinObject[i].posX = 0.235 * cos(DEG2RAD(i*60));
    	coinObject[i].posY = 0.235 * sin(DEG2RAD(i*60));		
    }
    for ( i = 7; i < 19; i++){
    	coinObject[i].posX = 0.46 * cos(DEG2RAD((i-7)*30));
    	coinObject[i].posY = 0.46 * sin(DEG2RAD((i-7)*30));
    }
}

//mouse drag event
void mouseDrag(int x, int y){

	mouseX = (0.005)*x -3.835 ;
	mouseY = -(0.005)*y + 1.86;
	if(mouseX > strik.x1 + 0.29 && mouseX < strik.x2 - 0.29 && activeStriker==1)
		strik.posX = mouseX;
}
