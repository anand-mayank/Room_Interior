#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void initialize();
void displayGraphics();
void reshapeWindowChange(int width, int height);
void cuboid(double width, double thickness, double height, double xpos, double ypos, double zpos);
void keyboardEvents(unsigned char key, int xpos, int ypos);
void drawGraphics();
void specialKeyEvents(int key, int xpos, int ypos);
void rotateFan();
void menuDefinition(int id);

int widthWindow=900, heightWindow=700;
double multiple = 4;
static GLfloat theta[] = {0,45,0};
static GLint axis = 2;
static GLdouble viewer[] = {2.3,1.38,2.0};
float xTranslate=1,yTranslate=-2,zTranslate=-15;
float fanRotation = 0, rate = 0;
int fanSwitch = 1;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(widthWindow, heightWindow);
	glutInitWindowPosition(400,100);
	glutCreateWindow("Room Interior");
	glutDisplayFunc(displayGraphics);
	glutReshapeFunc(reshapeWindowChange);
	glutKeyboardFunc(keyboardEvents);
	glutSpecialFunc(specialKeyEvents);
	glutIdleFunc(rotateFan);
	glutCreateMenu(menuDefinition);
	glutAddMenuEntry ("Fan On", 1);
  glutAddMenuEntry ("Fan Off", 2);
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	initialize();
	glutMainLoop();
	return 1;
}

void reshapeWindowChange(int width, int height){
	if(height == 0)
		height = 1;
	float ratio = 10.0 * width / height;
	widthWindow = width;
	heightWindow = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,width, height);
	gluPerspective(45,ratio, .1, 100);
}

void initialize(){
	glClearColor(0.2,0.2,0.4,1);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
}

void cuboid(double width, double thickness, double height, double xpos, double ypos, double zpos)    // function to create the cuboids with given thickness
{
    glPushMatrix();
    glTranslated(xpos, ypos, zpos);
    glScaled(width,thickness,height);
    glutSolidCube(1.0);
    glPopMatrix();
}

void displayGraphics(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    GLfloat mat_ambient[]={1,1,1,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    GLfloat light_Intensity[]={1,1,1,.5};
    GLfloat light_Position[]={2.0f,6.0f,3.0f,0.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,light_Position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_Intensity);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,widthWindow, heightWindow);
    gluPerspective(45,(float)widthWindow/heightWindow, .1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(viewer[0],viewer[1],viewer[2],0.0,0.25,0.0,0.0,1.0,0.0);
    glRotatef(theta[0],1,0,0);
    glRotatef(theta[1],0,1,0);
    glRotatef(theta[2],0,0,1);

    drawGraphics();

}



void keyboardEvents(unsigned char key, int xpos, int ypos){
	if(key=='a' || key=='A')
		xTranslate+=0.1;
		yTranslate+=0;
		zTranslate+=0;
	if(key=='d' || key=='D')
		xTranslate-=0.1;
		yTranslate-=0;
		zTranslate-=0;
	if(key=='w' || key=='W'){
		xTranslate+=0;
		yTranslate+=0;
		zTranslate+=0.1;
	}
	if(key=='s' || key=='S') {
		xTranslate-=0;
		yTranslate-=0;
		zTranslate-=0.1;
	}
	glutPostRedisplay();
}

void specialKeyEvents(int key, int xpos, int ypos){
	if(key==GLUT_KEY_DOWN){
		xTranslate+=0;
		yTranslate+=0.1;
		zTranslate+=0;
	}
	if(key==GLUT_KEY_UP){
		xTranslate-=0;
		yTranslate-=0.1;
		zTranslate-=0;
	}
	glutPostRedisplay();
}

void drawGraphics(){
	GLfloat defaultColor[] = {0,0,0,0.1f};
	GLfloat roofColor[] = {0,0,0,1.0f};
	GLfloat floorColor[] = {.4,.5,.9,.5};
	GLfloat wallColor[] = {0.76, 0.45, 0.47, 0.1};
	GLfloat wall2Color[] = {0.62f,.02f,0.23f,1.0f};
	GLfloat tableColor[] = {0.82f, 0.5f, 0.24f, 0.94f};
	GLfloat mattressColor1[] = {0.9f, 0.2f, 0.0f, 1.0f};
	GLfloat mattressColor2[] = {0.3f, 0.3f, 0.9f, 1.0f};
	GLfloat mattressColor3[] = {0,0,1,1};
	glTranslatef(xTranslate,yTranslate,zTranslate);
  glPushMatrix();
		//Floor
	  glMaterialfv(GL_FRONT,GL_AMBIENT,floorColor);
	  cuboid(multiple*2, 0.02, multiple*2, multiple*-.5, multiple*-0.5, multiple*-.5);
	  glPushMatrix();
			//Front Wall
		  glRotated(-90.0,1.0,0.0,0.0);
		  glMaterialfv(GL_FRONT,GL_AMBIENT,wall2Color);
		  cuboid(multiple*2, 0.02, multiple*1, multiple*-0.5, multiple*1.5, multiple*0);
	  glPopMatrix();
	  glPushMatrix();
			//Left Wall
		  glRotated(90.0,0.0,0.0,180.0);
		  glMaterialfv(GL_FRONT,GL_AMBIENT,wallColor);
		  cuboid(multiple*1, 0.02, multiple*2, multiple*0, multiple*-0.5, multiple*-0.5);
	  glPopMatrix();
	  glPushMatrix();
			//Right Wall
		  glRotated(-90.0,0.0,0.0,180.0);
		  glMaterialfv(GL_FRONT,GL_AMBIENT,wallColor);
		  cuboid(multiple*1, 0.02, multiple*2, multiple*0, multiple*-1.5, multiple*-0.5);
	  glPopMatrix();
	  glPushMatrix();
			//Roof
		  glRotated(180.0,1.0,0.0,0.0);
		  glMaterialfv(GL_FRONT,GL_AMBIENT,roofColor);
		  cuboid(multiple*2, 0.02, multiple*2, multiple*-.5, multiple*-.5, multiple*.5);

			glPushMatrix();
				//Fan
				glMaterialfv(GL_FRONT,GL_AMBIENT,tableColor);
				glTranslatef(-1.6,-1.6,1.5);
				glRotatef(fanRotation,0,1,0);
				cuboid(multiple*.08, 0.06, multiple*.08, multiple*0, multiple*0, multiple*0);
				//Wings
				cuboid(multiple*.04, 0.02, multiple*.5, multiple*0, multiple*0, multiple*0);
				cuboid(multiple*.5, 0.02, multiple*.04, multiple*0, multiple*0, multiple*0);
				//FixedRod
				cuboid(multiple*.01, 0.4, multiple*.01, multiple*0, multiple*-.05, multiple*0);
			glPopMatrix();

	  glPopMatrix();
		glPushMatrix();


			//Table
			glMaterialfv(GL_FRONT,GL_AMBIENT,tableColor);

			glTranslatef( multiple * .25, multiple * -0.03, multiple * -1.0);
			cuboid(multiple * .5, 0.01, multiple * .5, multiple * 0, multiple * -.25, multiple * 0);

			glPushMatrix();

				cuboid(multiple * .02, 1.0, multiple * .02, multiple * -.22, multiple * -0.38, multiple * -.22);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .02, 1.0, multiple * .02, multiple * -.22, multiple * -0.38, multiple * .22);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .02, 1.0, multiple * .02, multiple * .22, multiple * -0.38, multiple * .22);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .02, 1.0, multiple * .02, multiple * .22, multiple * -0.38, multiple * -.22);

			glPopMatrix();

		glPopMatrix();
		glPushMatrix();

		

			//Bed

			glTranslatef( multiple * -1.2, multiple * -0.03, multiple * -0.7);
			cuboid(multiple * .5, 0.03, multiple * 1.0, multiple * 0, multiple * -.295, multiple * 0);

			glPushMatrix();

				cuboid(multiple * .02, .7, multiple * .02, multiple * -.22, multiple * -0.38, multiple * -.47);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .02, .7, multiple * .02, multiple * -.22, multiple * -0.38, multiple * .47);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .02, .7, multiple * .02, multiple * .22, multiple * -0.38, multiple * .47);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .02, .7, multiple * .02, multiple * .22, multiple * -0.38, multiple * -.47);

			glPopMatrix();

		glPopMatrix();
		glPushMatrix();
		
		//Chair
			glTranslatef( multiple * -0.1, multiple * -.03, multiple * -0.9);
			cuboid(multiple * .15, 0.03, multiple * .15, multiple * 0, multiple * -.320, multiple * 0);

			glPushMatrix();

				cuboid(multiple * .01, .5, multiple * .01, multiple * -.070, multiple * -0.38, multiple * -.070);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .01, .5, multiple * .01, multiple * -.070, multiple * -0.38, multiple * .070);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .01, .5, multiple * .01, multiple * .070, multiple * -0.38, multiple * .070);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .01, .5, multiple * .01, multiple * .070, multiple * -0.38, multiple * -.070);

			glPopMatrix();
		glPopMatrix();

	glPopMatrix();

  
			//Mattress

			glTranslatef( multiple * 0, multiple * 0.005, multiple * 0);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mattressColor1);
			cuboid(multiple * 1, 0.01, multiple * .7, multiple * -0.2, multiple * -.5, multiple * 0);
			glTranslatef( multiple * 0, multiple * 0.005, multiple * 0);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mattressColor2);
			cuboid(multiple * .7, 0.01, multiple * .4, multiple * -0.2, multiple * -.5, multiple * 0);
			glTranslatef( multiple * 0, multiple * 0.005, multiple * 0);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mattressColor3);
			cuboid(multiple * .25, 0.01, multiple * .175, multiple * -0.2, multiple * -.5, multiple * 0);

		glPopMatrix();
		glPushMatrix();
			//Chair
			glTranslatef( multiple * -0.1, multiple * -.03, multiple * -0.9);
			cuboid(multiple * .15, 0.03, multiple * .15, multiple * 0, multiple * -.320, multiple * 0);

			glPushMatrix();

				cuboid(multiple * .01, .5, multiple * .01, multiple * -.070, multiple * -0.38, multiple * -.070);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .01, .5, multiple * .01, multiple * -.070, multiple * -0.38, multiple * .070);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .01, .5, multiple * .01, multiple * .070, multiple * -0.38, multiple * .070);

			glPopMatrix();
			glPushMatrix();

				cuboid(multiple * .01, .5, multiple * .01, multiple * .070, multiple * -0.38, multiple * -.070);

			glPopMatrix();
		glPopMatrix();

	glPopMatrix();

  glFlush();
  glutSwapBuffers();
}

void rotateFan(){
	if(fanSwitch == 0){
		if(rate<3)
			rate += .001;
		fanRotation += rate;
		if(fanRotation>360)
			fanRotation -= 360;
		glutPostRedisplay();
	}
	else if(fanSwitch == 1) {
		if(rate>0)
			rate -= .001;
		else
			rate = 0;
		fanRotation += rate;
		if(fanRotation>360)
			fanRotation -= 360;
		glutPostRedisplay();
	}
}


void menuDefinition(int id) {
	switch (id)
    {
    case 1 :
        fanSwitch = 0;
        break;
    case 2 :
        fanSwitch = 1;
        break;
    default :
        break;
    }
}
