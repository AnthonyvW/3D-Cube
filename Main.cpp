#include "gl/glut.h"

#define GL_GLEXT_PROTOTYPES

// Rotation of the cube
GLfloat rotation = 0;
GLfloat rotationSpeed = 0.5;

void RectFace(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) {
	// Draws a Rectangle
	glBegin(GL_POLYGON);
	glVertex3fv(A);
	glVertex3fv(B);
	glVertex3fv(C);
	glVertex3fv(D);
	glEnd();
}
void TriangleFace(GLfloat A[], GLfloat B[], GLfloat C0, GLfloat C1, GLfloat C2) {
	// Draws a triangle
	glBegin(GL_POLYGON);
	glVertex3fv(A);
	glVertex3fv(B);
	glVertex3f(C0, C1, C2);
	glEnd();
}

void DrawCube(GLfloat v[][3]) {
	// Set Color to Blue
	glColor3f(0, 0, 1);
	// Front Face
	TriangleFace(v[2], v[1], 0, 0.5, 0.5);
	TriangleFace(v[3], v[0], 0, 0.5, 0.5);
	// Back Face
	TriangleFace(v[6], v[5], 0, 0.5, -0.5);
	TriangleFace(v[4], v[7], 0, 0.5, -0.5);
	// Left Face
	TriangleFace(v[7], v[4], -0.5, 0.5, 0);
	TriangleFace(v[0], v[3], -0.5, 0.5, 0);
	// Right Face
	TriangleFace(v[6], v[5], 0.5, 0.5, 0);
	TriangleFace(v[1], v[2], 0.5, 0.5, 0); 
	// Top Face
	RectFace(v[0], v[1], v[5], v[4]);

	// Set Color to Yellow
	glColor3f(1, 1, 0);
	// Bottom Face
	RectFace(v[3], v[2], v[6], v[7]);
	// Yellow Triangles
	TriangleFace(v[2], v[3], 0, 0.5, 0.5); // Front Triangle
	TriangleFace(v[6], v[7], 0, 0.5, -0.5);// Back Triangle
	TriangleFace(v[7], v[3], -0.5, 0.5, 0);// Left Triangle
	TriangleFace(v[6], v[2], 0.5, 0.5, 0); // Right Triangle
	
	// Draw Wireframe Cube
	// Switch to a mode that draws lines instead of faces
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Offset Depth buffer to prevent lines from flickering
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(0, -10);
	// Set Wireframe to Black
	glColor3f(0, 0, 0);
	// Render Wireframe Cube Faces
	RectFace(v[0], v[1], v[2], v[3]); // Front
	RectFace(v[4], v[5], v[6], v[7]); // Back
	RectFace(v[0], v[3], v[7], v[4]); // Left
	RectFace(v[1], v[2], v[6], v[5]); // Right
	RectFace(v[0], v[1], v[5], v[4]); // Top
	RectFace(v[3], v[2], v[6], v[7]); // Bottom
	// Disable Wireframe
	glDisable(GL_POLYGON_OFFSET_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Draw() {
	// Creates the Cube
	GLfloat vertices[8][3] = {
		{-0.5, 0.5, 0.5},
		{ 0.5, 0.5, 0.5},
		{ 0.5,-0.5, 0.5},
		{-0.5,-0.5, 0.5},

		{-0.5, 0.5,-0.5},
		{ 0.5, 0.5,-0.5},
		{ 0.5,-0.5,-0.5},
		{-0.5,-0.5,-0.5}
	};
	// Clears the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Resets vertices to default state.
	glLoadIdentity();
	// Rotates vertices
	glRotatef(rotation, 1.0, 1.0, 0);

	// Draws the Cube
	DrawCube(vertices);

	// Swaps the current screen with the buffer
	glutSwapBuffers();
}
void Spin() {
	// Rotate Cube
	rotation += rotationSpeed;
	if (rotation > 360) {
		rotation = 0;
	}
	// Refresh Display
	glutPostRedisplay();
}

int main(int C, char* V[]) {
	glutInit(&C, V);
	// Create Window
	glutInitWindowPosition(1200, 0);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Open GL: Rotating Cube");
	// Initialize Buffer
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	// sets the display function and Draws the cube
	glutDisplayFunc(Draw);
	// Sets the idle function and Rotates the cube
	glutIdleFunc(Spin);
	// Tells glut to enter the main loop
	glutMainLoop();

	// Exits the program
	return 0;
}