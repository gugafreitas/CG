#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float posx = 0, posz = 0, posy = 0, angle = 0, scalex = 0, scaley = 0, scalez = 0;
int radius = 1, height = 1, slices = 100, stacks = 10;

/*typedef struct polar {
	double radius;
	double alpha;
	double beta;
}Polar;

double polarX(Polar polar) { 
	return polar.radius * cos(polar.beta) * sin(polar.alpha); 
	}
double polarY(Polar polar) { 
	return polar.radius * sin(polar.beta); 
	}
double polarZ(Polar polar) { 
	return polar.radius * cos(polar.beta) * cos(polar.alpha); 
}*/


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawCone(int radius, int height, int slices, int stacks){
	//glutWireCone((GLint)radius,(GLint)height,(GLdouble)slices,(GLdouble)stacks);
	GLint numberOfVertices = slices + 2;
	GLfloat doublePi = 2.0f * M_PI;
	GLfloat circleVerticesX[numberOfVertices];
	GLfloat circleVerticesZ[numberOfVertices];
	GLfloat circleVerticesY[numberOfVertices];

	circleVerticesX[0] = posx;
	circleVerticesZ[0] = posz;
	circleVerticesY[0] = posy;

	for(int i=1; i<numberOfVertices;i++){
		circleVerticesX[i] = posx + (radius * cos(i * doublePi / slices));
		circleVerticesY[i] = posy + (radius * sin(i * doublePi / slices));
		circleVerticesZ[i] = posz;
	}

	GLfloat allCircleVertices[numberOfVertices * 3];

	for(int i=0; i<numberOfVertices; i++){
		allCircleVertices[i*3] = circleVerticesX[i];
		allCircleVertices[(i*3) + 1] = circleVerticesY[i];
		allCircleVertices[(i*3) + 2] = circleVerticesZ[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	// put the geometric transformations here
	glTranslatef(posx,posy,posz);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glScalef(scalex,scaley,scalez);

	// put cone drawing instructions here
	glColor3ub(255,0,0);
	drawCone(radius, height, slices, stacks);

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void keyboardFunc(unsigned char key, int x, int y) {
	switch(key) {
		case 'a':
			posx -= 0.1;
			break;
		case 'd':
			posx += 0.1;
			break;
		case 's':
			posz += 0.1;
			break;
		case 'w':
			posz -= 0.1;
			break;
		case 't':
			posy += 0.1;
			break;
		case 'g':
			posy -= 0.1;
			break;
		case 'q':
			angle -= 1;
			break;
		case 'e':
			angle += 1;
			break;
		case 'z':
			scalex += 0.1;
			scaley += 0.1;
			scalez += 0.1;
			break;
		case 'x':
			scalex -= 0.1;
			scaley -= 0.1;
			scalez -= 0.1;
			break;
	}
	glutPostRedisplay();
}





int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboardFunc);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
