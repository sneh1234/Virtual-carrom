#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <string.h>
#include <sys/time.h>
# include "globals.cpp"
using namespace std;

class coin{
    public:
        float x;
        float y;
        float vel_x;
        float vel_y;
        float mass;
        float rad;
        short int color;
        short int inhole;
        coin()
        {
            vel_x=0.0f;
            vel_y=0.0f;
            mass=1;
            rad=0.13f;
            x=0;
            y=0;
            inhole=0;
        }

        void checkhole()
        {
                if((2.3-abs(x))*(2.3-abs(x))+(2.3-abs(y))*(2.3-abs(y)) < (0.13*1.414+0.03)*(0.13*1.414+0.03))
                    {
                        x=-5.0f,y=0.0f,vel_x=0,vel_y=0,inhole++;
                        if(max_chance>0)
                        {
                            if(color==white && turn ==-1)
                                score2+=50,extrachance=1,max_chance=-1;
                            else if(color==white && turn==1)
                                score-=5;
                            else if(color==black && turn==1)
                                score+=50,extrachance=1,max_chance=-1;
                            else 
                                score2-=5;
                        }
                        else if(color== white && turn ==-1)
                            score2+=10,extrachance=1;
                        else if(color==white && turn == 1)
                            score-=5;
                        else if(color == black && turn ==-1)
                            score2-=5;
                        else  if(color==black && turn == 1)
                            score+=10,extrachance=1;
                        else  if(turn==-1)
                             max_chance=2,extrachance=1,queen_inside=-3;
                        else
                            max_chance=2,extrachance=1,queen_inside=-2; 
                    }
        }

        int applyfriction()
        {
           float  total=sqrt(vel_x*vel_x+vel_y*vel_y);
            if(total < 0.001f)
                {
                    vel_y=0,vel_x=0;
                    return 1;
                }
            else
            vel_x-=(vel_x*9.8*friction_coef)/total,vel_y-=9.8*friction_coef*vel_y/total;
        return 0;
        }
//        float color
};
coin coins[19];
class striker{
    public:
        float x;
        float y;
        float vel_x;
        float vel_y;
        float rad;
        float mass;
        float angle;
        striker()
        {
            rad=0.13*1.414f;
            mass=2;
            vel_x=0.00f;
            vel_y=0.0f;
            angle=90;
        }
        void moveStriker(float distance){
            int count=1;
        	if(distance>0  && x + distance < 1.38f)
        		x+=distance;
        	if(distance < 0 && x + distance > -1.38f)
       			x+=distance;
        	while(count)
        	{
            	count=0;
        		for(int i=0;i<19;i++)
        		{
            		if((coins[i].x-x)*(coins[i].x-x)+(coins[i].y-y)*(coins[i].y-y) < (coins[i].rad+rad)*(coins[i].rad+rad))
               		{
                    	if(distance >= 0)
                        x+=0.1;
                    else
                        x-=0.1;
                    count=1;
               		break;
                	}
        		}
        	}
        	if(x > 1.38)
        		moveStriker(-0.04);
       		if(x < -1.38)
        		moveStriker(0.04);
        }

        void changeAngle(float theta)
        {
            if(abs(angle+theta-90) < 90)
                angle+=theta;
        }

        void applyvelocity(float value)
        {
            vel_x=value*cos(DEG2RAD(-turn*angle));
            vel_y=value*sin(DEG2RAD(-turn*angle));
        }

        void checkhole()
        {
            if((2.3-abs(x))*(2.3-abs(x))+(2.3-abs(y))*(2.3-abs(y)) < (rad+0.03)*(rad+0.03))
            	{
                    y=-1.8,vel_y=0,vel_x=0;
                    score-=5;
                    for(int i=1;i<19;i++)
                    {
                        if(coins[i].inhole && ((coins[i].color==black && turn ==1 )||(coins[i].color==white && turn ==-1)))
                            {
                                coins[i].x=0,coins[i].y=0,coins[i].inhole=0;
                                break;
                            }
                    }
                }
        }

        int applyfriction()
        {
           float total=sqrt(vel_x*vel_x+vel_y*vel_y);
            if(total < 0.001f)
                {
                    vel_y=0,vel_x=0;
                    return 1;
                }
            else
            	vel_x-=(vel_x*9.8*friction_coef)/total,vel_y-=9.8*friction_coef*vel_y/total;
        	return 0;
        }

};
striker s;
void handle_angle(int , int );

void generateStriker()
{
    s.x=0.0f;
    s.y=-1.8f;
}

void handle_angle(int x, int y)
{
    x=-(float)((x-655)*(0.26*sqrt(3))/51)*turn;
    y=(float)(y-370)*(-0.26/30);

}

void generateCoin(int i)
{
	coins[0].x=0;
   	coins[0].y=0;
   	coins[0].color=red;
    for(int j=-90;j<270;j+=60)
    {   
    	if(((j+90)/60)%2==0)   
   			coins[(j+90)/60+1].color=white;
    	else
     		coins[(j+90)/60+1].color=black;
    	coins[(j+90)/60+1].x=2*coins[0].rad*cos(DEG2RAD(j));
    	coins[(j+90)/60+1].y=2*coins[0].rad*sin(DEG2RAD(j));
    }

    for(int j=-90;j<270;j+=60)
    {
        coins[((j+90)/60)+7].color=white;
        coins[(j+90)/60+7].x=4*coins[0].rad*cos(DEG2RAD(j));
    	coins[(j+90)/60+7].y=4*coins[0].rad*sin(DEG2RAD(j));
    }

    for(i=-60;i<360;i+=60)
    {
        coins[((i+60)/60)+13].color=black;
        coins[(i+60 )/60+13].x=2*sqrt(3)*coins[0].rad*cos(DEG2RAD(i));
    	coins[(i+60)/60+13].y=2*sqrt(3)*coins[0].rad*sin(DEG2RAD(i));
    }
}

int main(int argc, char **argv) {
    // Initialize GLUT
    gettimeofday(&tim, NULL); 
    t1=tim.tv_sec+(tim.tv_usec/1000000.0);  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w ;
    int windowHeight = h;
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
    glutCreateWindow("Carrom");  // Setup the window
    initRendering();
   	generateCoin(1);
    generateStriker();
    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMotionFunc(handleMouseclick1);
    glutMouseFunc(handleMouseclick);
    glutKeyboardUpFunc(keyUp); 
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}

void printNumber(int sc)
{
    glColor3f(0,0,0);
    if(sc==0)
        return;
    printNumber(sc/10);
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, '0'+sc%10);
}
// Function to draw objects on the screen
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBox(box_len);   
 	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(3.5,-2.5,0);
    glVertex3f( 4.5,-2.5,0);
   	glVertex3f(3.5,2,0);
   	glVertex3f(3.5,-2.5,0);
   	glVertex3f(4.5,2,0);
   	glVertex3f(4.5,-2.5,0);
   	glVertex3f(3.5,2,0);
   	glVertex3f(4.5,2,0); 
   	glEnd();
	float k=speed/10;
	if(!speed)
		k=50*sqrt(s.vel_x*s.vel_x+s.vel_y*s.vel_y);
	if(k>9)
		k=9;
	for(float i=0;i<k;i++)
	{   
    	glBegin(GL_QUADS);
    	glColor3f(i/9,1-i/9,0.0);
    	glVertex3f(3.5,-2.5+(i+1)*0.5,0);
    	glVertex3f(4.5,-2.5+(i+1)*0.5,0);
    	glVertex3f(4.5,-2.5+(i)*0.5,0);
    	glVertex3f(3.5,-2.5+(i)*0.5,0);
    	glEnd();
	}

	displayInholeCoin();
	glPushMatrix();
    if((Carrom_angle >30 && turn ==1) || ( Carrom_angle < 150 && turn == -1))
    	glRotatef(Carrom_angle,0,0,1);
	Carrom_angle+=3*turn;
	if(Carrom_angle<0)
    	Carrom_angle=0;
	if(Carrom_angle>180)
    	Carrom_angle=180;
	if(canMove)
	{
    	glLineWidth(1.2);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(s.x,  s.y, 0.0f);
		glVertex3f(s.x +0.5*cos(DEG2RAD(-s.angle*turn)), s.y + 0.5*sin(DEG2RAD(-s.angle*turn)), 0);
		glEnd();
		glPushMatrix();
		glTranslatef(s.x+0.5*cos(DEG2RAD(-s.angle*turn)),s.y+0.5*sin(DEG2RAD(-s.angle*turn)),0);
		glRotatef(45-turn*s.angle,0.0,0.0,1.0);
    	drawTriangle();
    	glPopMatrix();
	}

	for(float i=0;i<360;i+=45)  
 	{ 
    	if((int)(i/45)%2==0)
    		glColor3f(0.6875f, 0.144f, 0.152f);
    	else
    		glColor3f(0.0f,0.0f,0.0f);    
  		glPushMatrix();
  		glRotatef(i,0.0f,0.0f,1.0f);
  		drawInnerPattern();
  		glPopMatrix();
	}

	glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
	drawBorder(0.65f);
	glPopMatrix();
	glPushMatrix();
    glColor3f(0.6875f, 0.144f, 0.152f);
	drawBall(0.14f);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	drawBorder(0.19f);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	drawBorder(0.15f);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(2.3f, -2.3f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawBall(s.rad+0.03f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(hole_x-0.4f, hole_y-4.2f, 0);
    drawTriangleAndOther();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(hole_x-4.2f, hole_y-0.4f, 0);
    glRotatef(180.0, 0.0f, 0.0f, 1.0f);
    drawTriangleAndOther();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(hole_x-0.4f, hole_y-0.4f, 0);
    glRotatef(90.0, 0.0f, 0.0f, 1.0f);
    drawTriangleAndOther();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(hole_x-4.2f, hole_y-4.2f, 0);
    glRotatef(270.0, 0.0f, 0.0f, 1.0f);
    drawTriangleAndOther();
    glPopMatrix();
    displayCoin();
	glPopMatrix();
	glColor3f(1.0,1.0,1.0);
	glLineWidth(1.9);
	glBegin(GL_LINES);
	glVertex3f(-4.3f, -2.2, 0.0f);
	glVertex3f(-4.3f, 2.5f, 0);
	glVertex3f(-3.0f, -2.2, 0.0f);
	glVertex3f(-3.0f, 2.5f, 0);
	glVertex3f(-5.5f, -2.2, 0.0f);
	glVertex3f(-5.5f, 2.5f, 0);
	glVertex3f(-3.0f, 2.5, 0.0f);
	glVertex3f(-5.5f, 2.5f, 0);
	glVertex3f(-3.0f, -2.2, 0.0f);
	glVertex3f(-5.5f, -2.2f, 0);
	glVertex3f(-3.0f, 1.8, 0.0f);
	glVertex3f(-5.5f, 1.8f, 0);
	glEnd();
  	gettimeofday(&tim, NULL);  
    double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
	char string[100];
	strcpy(string,"Player 1: ");
    if(turn==-1)
        t2=score2+t1-t2-time1+1;//-(t2-t1);
    else
      	t2=score2-time1;//+t1-t2;
   	glColor3f(1.0,1.0,1.0);
	glRasterPos3f(-5.4,2,0);
    for(int j=0;j<10;j++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[j]);
    if(t2<0)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'-'),t2=-t2;
    if((int)(t2))
    	printNumber((int)(t2));
    else glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'0');
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' '), glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' '), glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
   	strcpy(string,"Player 2: ");
   	for(int j=0;j<10;j++)
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[j]);
    t2=tim.tv_sec+(tim.tv_usec/1000000.0);
    if(turn==1)
        t2=score-time2+t1-t2+1;//-time2;//-(t2-t1);
    else
        t2=score-time2;
    if(t2 <0)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'-'),t2=-t2;
    if((int)t2)
        printNumber((int)t2);
 	if(speed && canMove && speed < 90)
        speed++;
    glPopMatrix();
    glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void displayInholeCoin()
{
	int count=0,count2=0;
    for(int i=0;i<19;i++)
    {
    	if(coins[i].inhole)
        {
            if(coins[i].color==black || (queen_inside==-2 && i==0))
                coins[i].x=-3.6,coins[i].y=1.6-(float)count/2.5,count++;
            else if(coins[i].color==white || (queen_inside==-3 && i==0))
                coins[i].x=-4.9,coins[i].y=1.6-(float)count2/2.5,count2++;
        	glPushMatrix();
        	glTranslatef(coins[i].x,coins[i].y,0.0f);
        	if(coins[i].color==red)
            	glColor3f(1.0f,0.0f,0.0f);
        	else if(coins[i].color==black)
            	glColor3f(0.2f,0.2f,0.2f);
        	else
            	glColor3f(1.0,1.0,1.0);
        	drawBall(coins[i].rad);
        	drawBorder(coins[i].rad);
        	glPopMatrix();
    	}
    }

	glBegin(GL_QUADS);
    glColor3f(0.117f,0.562f,1.0f);
    glVertex2f(-2.0 , -2.9);
    glVertex2f( -2.0, -3.9);
    glVertex2f(2, -3.9);
    glVertex2f(2, -2.9);
    glEnd();
    glColor3f(1.0,1.0,1.0);
   	glRasterPos3f(-1,-3.1,0);

    char string[100];
    if(turn==-1)
		strcpy(string,"Player 1: Turn");
	else
		strcpy(string,"Player 2: Turn");
	if(count==10 || count2==10)
	{
    	if(score>score2)
   			strcpy(string,"Player 2: Won");
        else
   			strcpy(string,"Player 1: Won");

	}

  for(int j=0;j<17;j++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[j]);

}
void displayCoin()
{
    for(int i=0;i<19;i++)
    {
        if(!coins[i].inhole)
        {
        	glPushMatrix();
        	glTranslatef(coins[i].x,coins[i].y,0.0f);
        	if(coins[i].color==red)
            	glColor3f(0.8f,0.0f,0.0f);
        	else if(coins[i].color==black)
            	glColor3f(0.2f,0.2f,0.2f);
       		else
            	glColor3f(1.0,1.0,1.0);
        	drawBall(coins[i].rad);
        	drawBorder(coins[i].rad);
        	glPopMatrix();
    	}
	}
    glPushMatrix();
    glTranslatef(s.x,s.y,0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    drawBall(s.rad);

   	for(int i=0;i<720;i++)
	{	
		glPointSize(2.5f);
    	glLineWidth(0.1);
   		glColor3f(0.996f,0.341f,0.067f);
		glBegin(GL_POINTS);
		glVertex3f(s.rad*0.85*cos(DEG2RAD((float)i/2)),  s.rad*0.85*sin(DEG2RAD((float)i/2)), 0.0);
		glEnd();
	}

  	for(int i=0;i<720;i++)
	{	
		glPointSize(2.5f);
    	glLineWidth(0.1);
		glColor3f(0.996f,0.341f,0.067f);
		glBegin(GL_POINTS);
		glVertex3f(s.rad*0.65*cos(DEG2RAD((float)i/2)),  s.rad*0.65*sin(DEG2RAD((float)(i/2))), 0.0);
		glEnd();
	}

 	for(int i=0;i<360;i++)
	{
		glPointSize(6.0f);
    	glLineWidth(0.1);
		glColor3f(0.996f,0.341f,0.067f);
		glBegin(GL_POINTS);
		glVertex3f(s.rad*0.3*cos(DEG2RAD(i)),  s.rad*0.3*sin(DEG2RAD(i)), 0.0);
		glEnd();
	}

	glPopMatrix();
}

void drawInnerPattern()
{
    glLineWidth(2.1);
	for(int i=0;i>-45;i--)
	{  
		glBegin(GL_LINES);
		glVertex3f(0.19*cos(DEG2RAD(i)), 0.19f*sin(DEG2RAD(i)), 0.0f);
		glVertex3f(0.65f, 0.0f, 0);
		glEnd();
    }

	glColor3f(0.99,0.96,0.558);
	for(int i=0;i>-45;i--)
	{  
		glBegin(GL_LINES);
		glVertex3f(0.19*cos(DEG2RAD(i)), 0.19*sin(DEG2RAD(i)), 0.0f);
		glVertex3f(0.65/1.414f, -0.65/1.414f, 0);
		glEnd();
    }

    glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0.19*cos(DEG2RAD(-45)), 0.19*sin(DEG2RAD(-45)), 0.0f);
	glVertex3f(0.65/1.414f, -0.65/1.414f, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.19*cos(DEG2RAD(-45)), 0.19*sin(DEG2RAD(-45)), 0.0f);
	glVertex3f(0.65f, 0.0f, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.19f,0.0f,0.0f);
	glVertex3f(0.65*cos(DEG2RAD(45)), -0.65*cos(DEG2RAD(45)), 0);
	glEnd();
}

void update(int value) {
    int i,j;
    float energy=0.0f;
 	float cosa,sina;
 	int count=0;
    // Handle ball collisions with box
    for(i=0;i<19;i++)
   	{
    	for(j=i+1;j<19;j++)
    	{
	    	if( ((coins[i].x-coins[j].x)*(coins[i].x-coins[j].x) + (coins[i].y-coins[j].y)*(coins[i].y-coins[j].y) < coins[i].rad*coins[i].rad*4) && ((coins[i].x-coins[j].x)*(coins[i].vel_x-coins[j].vel_x) + (coins[i].y-coins[j].y)*(coins[i].vel_y-coins[j].vel_y) < 0))
	    	{
	     		sina=(coins[j].y-coins[i].y)/(sqrt((coins[j].y-coins[i].y)*(coins[j].y-coins[i].y)+(coins[j].x-coins[i].x)*(coins[j].x-coins[i].x)));
	     		cosa=(coins[j].x-coins[i].x)/(sqrt((coins[j].y-coins[i].y)*(coins[j].y-coins[i].y)+(coins[j].x-coins[i].x)*(coins[j].x-coins[i].x)));
	    		float temp1,temp2,temp3,temp4;
	    		temp1=coins[j].vel_x*cosa   +coins[j].vel_y*sina;
	    		temp2=coins[i].vel_x*sina - coins[i].vel_y*cosa;
	    		temp3=coins[i].vel_x*cosa+coins[i].vel_y*sina;
	    		temp4=coins[j].vel_x*sina - coins[j].vel_y*cosa;
	    		coins[i].vel_x=temp1*cosa+temp2*sina;
	    		coins[i].vel_y=temp1*sina-temp2*cosa;
	        	coins[j].vel_x=temp3*cosa+temp4*sina;
	        	coins[j].vel_y=temp3*sina-temp4*cosa;
	    	}
    	}

    	count+=coins[i].applyfriction();
   		if((coins[i].x + coins[i].rad > box_len/2 && coins[i].vel_x>0) || (coins[i].x - coins[i].rad < -box_len/2 && coins[i].vel_x < 0))
        	coins[i].vel_x *= -1;
    	if((coins[i].y + coins[i].rad > box_len/2 && coins[i].vel_y > 0) || (coins[i].y - coins[i].rad < -box_len/2 && coins[i].vel_y < 0))
        	coins[i].vel_y*=-1;
   		if( ((coins[i].x-s.x)*(coins[i].x-s.x)+(coins[i].y-s.y)*(coins[i].y-s.y) < (coins[i].rad+s.rad)*(coins[i].rad+s.rad) )&& ((coins[i].x-s.x)*(coins[i].vel_x-s.vel_x) + (coins[i].y-s.y)*(coins[i].vel_y-s.vel_y) < 0))
   		{
    		float cosa,sina;
     		sina=(coins[i].y-s.y)/(sqrt((coins[i].y-s.y)*(coins[i].y-s.y)+(coins[i].x-s.x)*(coins[i].x-s.x)));
     		cosa=(coins[i].x-s.x)/(sqrt((coins[i].y-s.y)*(coins[i].y-s.y)+(coins[i].x-s.x)*(coins[i].x-s.x)));
		    float vPer1,vPer2,vLOC1,vLOC2,vfinalLOC1,vfinalLOC2;
		    vPer1=-coins[i].vel_x*sina+coins[i].vel_y*cosa;
		    vPer2=-s.vel_x*sina+s.vel_y*cosa;
		    vLOC1=coins[i].vel_x*cosa+coins[i].vel_y*sina;
		    vLOC2=s.vel_x*cosa+s.vel_y*sina;
		    vfinalLOC1=((coins[i].mass-s.mass)*(vLOC1)+2*s.mass*vLOC2)/(coins[i].mass+s.mass);
		    vfinalLOC2= (2*coins[i].mass*vLOC1+(s.mass-coins[i].mass)*vLOC2)/(coins[i].mass+s.mass);
		    coins[i].vel_x=vfinalLOC1*cosa-vPer1*sina;
		    coins[i].vel_y=vfinalLOC1*sina+vPer1*cosa;
		    s.vel_x=vfinalLOC2*cosa-vPer2*sina;
		    s.vel_y=vfinalLOC2*sina+vPer2*cosa;
   		}

	 	if((s.x + s.rad > box_len/2 && s.vel_x>0) || (s.x - s.rad < -box_len/2 && s.vel_x < 0))
        	s.vel_x *= -1;
    	if((s.y + s.rad > box_len/2 && s.vel_y > 0) || (s.y - s.rad < -box_len/2 && s.vel_y < 0))
        	s.vel_y*=-1;
            
        // Update position of ball
    	coins[i].x += coins[i].vel_x;
        coins[i].y+= coins[i].vel_y;
   		coins[i].checkhole(); 
		energy+=coins[i].vel_y*coins[i].vel_y+coins[i].vel_x*coins[i].vel_x;

    }

	count+=s.applyfriction();
  	s.x+=s.vel_x;
    s.y+=s.vel_y;

    if(count==20)
  	{
    	if(!newchance)
       	{
        	double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
         	newchance=1,s.y=-turn*1.73,turn=-turn;
         	if(turn==1)
            	time1+=t2-t1;
        	else
            	time2+=t2-t1;
            	gettimeofday(&tim, NULL); 
    		t1=tim.tv_sec+(tim.tv_usec/1000000.0);
    		max_chance-=1;  
    	}

    if(extrachance)
        s.y=-turn*1.73,turn=-turn,extrachance=0;
    if(max_chance==0)
        coins[0].x=0,coins[0].y=0,max_chance=-1,coins[0].inhole=0;
     	canMove=1;
     	s.moveStriker(0.0f);
 	}

 	else newchance=0;
 	s.checkhole();
    glutTimerFunc(10, update, 0);
}

void drawBorder(float len)
{
	for(int i=0;i<360;i++)
	{
		glPointSize(2.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex3f(len*cos(DEG2RAD(i)),  len*sin(DEG2RAD(i)), 0.0);
		glEnd();
	}
}

void drawBox(float len)
{
	glColor3f(1,0.8,0.2);
	glBegin(GL_QUADS);
    glVertex2f(-GLUT_SCREEN_WIDTH / 2, -GLUT_SCREEN_HEIGHT / 2);
    glVertex2f( GLUT_SCREEN_WIDTH/ 2, -GLUT_SCREEN_HEIGHT / 2);
    glVertex2f(GLUT_SCREEN_WIDTH/ 2, GLUT_SCREEN_HEIGHT / 2);
    glVertex2f(-GLUT_SCREEN_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2);
    glEnd();
	glColor3f(0.117f,0.562f,1.0f);
    glBegin(GL_QUADS);
	glVertex2f(-3.0,1.8);
	glVertex2f(-5.5,1.8);
	glVertex2f(-5.5,2.5);
	glVertex2f(-3.0,2.5);
	glEnd();
    glBegin(GL_QUADS);
    glBegin(GL_QUADS);
    glColor3f(0.625f,0.32f,0.074f);
    len+=0.7f;
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    len-=0.7f;
    glBegin(GL_QUADS);
	glColor3f(0.99,0.96,0.558);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
}

void drawBall(float rad) {
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.07f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.07f, 0.0f);
    glEnd();
}

void drawTriangleAndOther(){
    float line_x=-0.28f,distance=0.12f;
    drawTriangle();
    for(int i=0;i<270;i++)
	{
		glPointSize(2.0f);
    	glLineWidth(0.1);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex3f(0.3f*cos(DEG2RAD(i))-0.9f,  0.3f*sin(DEG2RAD(i))+0.9f, 0.0);
		glEnd();
	}   
    glPushMatrix();
   	glTranslatef(-0.6f, 0.86f, 0);
    glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
    drawTriangle();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.86f, 0.6f, 0);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    drawTriangle();
    glPopMatrix();
 	glPushMatrix();
    glTranslatef(-0.34f, 0.34f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
   	for(int i=127 ; i<310; i++) {
       glVertex2f(0.1f * cos(DEG2RAD(i)), 0.1f * sin(DEG2RAD(i)));
   }
   	glEnd();
    glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.34f, 0.34f, 0.0f);
	drawBorder(0.1f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.485f, -line_x - distance ,0.0f);
	drawBorder(distance);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(-0.485f,-line_x-distance, 0.0f);
    glColor3f(0.6875f, 0.144f, 0.152f);
    drawBall(0.7633*distance);
    glPopMatrix();
	glPushMatrix();
	glTranslatef(line_x+distance, 0.485f,0.0f);
	drawBorder(distance);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(line_x+distance,0.485f, 0.0f);
    glColor3f(0.6875f, 0.144f, 0.152f);
    drawBall(0.7633*distance);
    glPopMatrix();
	glLineWidth(2.1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,  0.0f, 0.0f);
	glVertex3f(-1.1f, 1.1f, 0);
	glEnd();
    glPushMatrix();
    glTranslatef(0.4f, -0.4f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawBall(s.rad+0.03f);
    for(int i=0;i<92;i++)
    {  
    	glBegin(GL_LINES);
    	glColor3f(0.625f,0.32f,0.074f);
	    glVertex3f(0.2f, -0.2f, 0.0f);
	    glVertex3f((s.rad+0.03)*cos(DEG2RAD(i)), -(s.rad+0.03)*sin(DEG2RAD(i)), 0);
	    glColor3f(1.0,0.8,0.2);
	    glVertex3f(0.35+s.rad+0.03,-0.35-s.rad-0.03,0.0f);
	    glVertex3f((s.rad+0.03)*cos(DEG2RAD(i))+0.36,-(s.rad+0.03)*sin(DEG2RAD(i))-0.36,0);
	    glEnd();
    }

    glPopMatrix();
	glColor3f(0.0,0.0,0.0);
 	glBegin(GL_LINES);
	glVertex3f(line_x+2*distance, 0.485f,0.0);
	glVertex3f(line_x+2*distance , 3.288f,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(line_x, 0.485f,0.0);
	glVertex3f(line_x , 3.288f,0);
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {
    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}
// Function called when the window is resized
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void handleKeypress1(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    if(key==32 && canMove)
		glutIgnoreKeyRepeat(1),speed=1;
}
void handleKeypress2(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT && canMove)
       s.moveStriker(0.04f*turn);  
    if (key == GLUT_KEY_RIGHT && canMove)
        s.moveStriker(-0.04f*turn);
    if (key == GLUT_KEY_UP)
        s.changeAngle(1*-turn);
    if (key == GLUT_KEY_DOWN)
        s.changeAngle(turn);
}

void keyUp (unsigned char key, int x, int y) { 
    if(key==32 && speed) 
    s.applyvelocity(speed/500),speed=0,canMove=0 ,glutIgnoreKeyRepeat(0);
}

void handleMouseclick(int button, int state, int x, int y) 
{
	if(button==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)
	{
	 	float x1=-(float)((x-655)*(0.26*sqrt(3))/51)*turn;
	   	float y1=(float)(y-370)*(-0.26/30);
		speed++;
		s.angle=(atan((y1+turn*s.y)/(s.x-x1))*180/3.14);
	 	if(s.angle<0)
	    	s.angle=180+s.angle;
	    if(turn==-1)
	        s.angle=180-s.angle;
	 	if(turn==1)
	 		s.angle=-s.angle+180;
	}
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	s.applyvelocity(speed/500),speed=0,canMove=0;
}

void handleMouseclick1(int x, int y)
{
    s.x=-((x-655)*(0.26*sqrt(3))/51)*turn;
}

