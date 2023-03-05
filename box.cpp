#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

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

void drawBox(GLfloat centerPosX, GLfloat centerPosy, GLfloat centerPosZ, GLfloat length, GLfloat divs){
	GLfloat halfSideLength = length * 0.5;

	glBegin(GL_TRIANGLE_FAN);

	// Set the color to blue
    glColor3f(0.0f, 0.0f, 1.0f);
	// front face
	glVertex3f(centerPosX - halfSideLength,centerPosy + halfSideLength,centerPosZ + halfSideLength); //top left
	glVertex3f(centerPosX + halfSideLength,centerPosy + halfSideLength,centerPosZ + halfSideLength); //top right
	glVertex3f(centerPosX + halfSideLength,centerPosy - halfSideLength,centerPosZ + halfSideLength); //bottom right
	glVertex3f(centerPosX - halfSideLength,centerPosy - halfSideLength,centerPosZ + halfSideLength); //bottom left

	//Set the color to red
	glColor3f(1.0f, 0.0f, 0.0f);
	//back face
	glVertex3f(centerPosX - halfSideLength,centerPosy + halfSideLength,centerPosZ - halfSideLength); //top left
	glVertex3f(centerPosX + halfSideLength,centerPosy + halfSideLength,centerPosZ - halfSideLength); //top right
	glVertex3f(centerPosX + halfSideLength,centerPosy - halfSideLength,centerPosZ - halfSideLength); //bottom right
	glVertex3f(centerPosX - halfSideLength,centerPosy - halfSideLength,centerPosZ - halfSideLength); //bottom left

	//Set the color to green
	glColor3f(1.0f, 0.0f, 0.0f);
	//left face
	glVertex3f(centerPosX - halfSideLength,centerPosy + halfSideLength,centerPosZ + halfSideLength); //top left
	glVertex3f(centerPosX - halfSideLength,centerPosy + halfSideLength,centerPosZ - halfSideLength); //top right
	glVertex3f(centerPosX - halfSideLength,centerPosy - halfSideLength,centerPosZ - halfSideLength); //bottom right
	glVertex3f(centerPosX - halfSideLength,centerPosy - halfSideLength,centerPosZ + halfSideLength); //bottom left

	//Set the color to yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	//right face
	glVertex3f(centerPosX + halfSideLength,centerPosy + halfSideLength,centerPosZ + halfSideLength); //top left
	glVertex3f(centerPosX + halfSideLength,centerPosy + halfSideLength,centerPosZ - halfSideLength); //top right
	glVertex3f(centerPosX + halfSideLength,centerPosy - halfSideLength,centerPosZ - halfSideLength); //bottom right
	glVertex3f(centerPosX + halfSideLength,centerPosy - halfSideLength,centerPosZ + halfSideLength); //bottom left

	//Set the color to purple
	glColor3f(1.0f, 0.5f, 1.0f);
	//top face
	glVertex3f(centerPosX - halfSideLength,centerPosy + halfSideLength,centerPosZ + halfSideLength); //top left
	glVertex3f(centerPosX - halfSideLength,centerPosy + halfSideLength,centerPosZ - halfSideLength); //top right
	glVertex3f(centerPosX + halfSideLength,centerPosy + halfSideLength,centerPosZ - halfSideLength); //bottom right
	glVertex3f(centerPosX + halfSideLength,centerPosy + halfSideLength,centerPosZ + halfSideLength); //bottom left

	//Set the color to orange
	glColor3f(1.0f, 0.5f, 0.0f);
	//bottom face
	glVertex3f(centerPosX - halfSideLength,centerPosy - halfSideLength,centerPosZ + halfSideLength); //top left
	glVertex3f(centerPosX - halfSideLength,centerPosy - halfSideLength,centerPosZ - halfSideLength); //top right
	glVertex3f(centerPosX + halfSideLength,centerPosy - halfSideLength,centerPosZ - halfSideLength); //bottom right
	glVertex3f(centerPosX + halfSideLength,centerPosy - halfSideLength,centerPosZ + halfSideLength); //bottom left

	glEnd();



}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	// put axis drawing in here
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();


	// put the geometric transformations here


	// put box drawing instructions here
	//drawBox(0.0f,0.0f,0.0f,);


	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events






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



//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
