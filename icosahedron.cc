// Draw an Icosahedron
// ECE4893/8893 Project 4
// Bi Ge

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#define NFACE 20
#define NVERTEX 12

#define X .525731112119133606 
#define Z .850650808352039932

#define updateRate 10
#define _WIDTH 2.0
// These are the 12 vertices for the icosahedron
static GLfloat vdata[NVERTEX][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};

// These are the 20 faces.  Each of the three entries for each 
// vertex gives the 3 vertices that make the face.
static GLint tindices[NFACE][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

int testNumber; // Global variable indicating which test number is desired
int depth;

void Normalize(GLfloat* v)
{
  GLfloat length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  v[0] /= length;
  v[1] /= length;
  v[2] /= length;
  return;
}

// depth means how many left
void DrawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3, int depth)
{
  GLfloat v12[3];
  GLfloat v13[3];
  GLfloat v23[3];
  if (depth == 0){
    // simply draw triangl
    //glBegin(GL_TRIANGLES);
    GLfloat rgb[3];
    rgb[0] = v1[0] + v2[0] + v3[0];
    rgb[1] = v1[1] + v2[1] + v3[1];
    rgb[2] = v1[2] + v2[2] + v3[2];
    Normalize(rgb);
    //cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << endl;
    //glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 1);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glEnd();
    glBegin(GL_LINES);
    glLineWidth(_WIDTH);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glVertex3f(v2[0], v2[1], v2[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glEnd();
    glLineWidth(1.0f);
  }
  else {
    for (int i = 0; i < 3; i++){
      v12[i] = v1[i] + v2[i];
      v13[i] = v1[i] + v3[i];
      v23[i] = v2[i] + v3[i];
    }
    Normalize(v12);
    Normalize(v13);
    Normalize(v23);
    DrawTriangle(v1, v12, v13, depth-1);
    DrawTriangle(v2, v12, v23, depth-1);
    DrawTriangle(v3, v13, v23, depth-1);
    DrawTriangle(v12, v13, v23, depth-1);
  }
}

// Test cases.  Fill in your code for each test case
void Test1()
{
  const int recurDepth = 0; 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // clear matrix
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(250, 250, 0);
  glScalef(100.0, 100.0, 0.0);
  // j is the current face
  for (int j = 0; j < NFACE; j++){
    GLint* face = tindices[j];
    GLfloat* t1 = vdata[face[0]];
    GLfloat* t2 = vdata[face[1]];
    GLfloat* t3 = vdata[face[2]];
    DrawTriangle(t1, t2, t3, recurDepth);
  }
  glutSwapBuffers();
}

void Test2()
{
  const int recurDepth = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(0, 0, -150);
  glScalef(150, 150, 150);
  static float xr = 0.0;
  static float yr = 30.0;
  glRotatef(xr, 1, 0, 0);
  glRotatef(yr, 0, 1, 0);
  xr += 1;
  yr += 1;

  // j is the current face
  for (int j = 0; j < NFACE; j++){
    GLint* face = tindices[j];
    GLfloat* t1 = vdata[face[0]];
    GLfloat* t2 = vdata[face[1]];
    GLfloat* t3 = vdata[face[2]];
    DrawTriangle(t1, t2, t3, recurDepth);
  }
  glFlush();
  glutSwapBuffers();
  // cin.ignore();
}

void Test3()
{
  const int recurDepth = 1; 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // clear matrix
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(250, 250, 0);
  glScalef(100.0, 100.0, 0.0);
  // j is the current face
  for (int j = 0; j < NFACE; j++){
    GLint* face = tindices[j];
    GLfloat* t1 = vdata[face[0]];
    GLfloat* t2 = vdata[face[1]];
    GLfloat* t3 = vdata[face[2]];
    DrawTriangle(t1, t2, t3, recurDepth);
  }
  glutSwapBuffers();
}

void Test4()
{
}

void Test5(int depth)
{
}

void Test6(int depth)
{
}

void reshape(int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-(GLdouble)w, (GLdouble)w, -(GLdouble)h, (GLdouble)h,
  	  -(GLdouble)1000.0, (GLdouble)100000000.0);

  glViewport(0, 0, (GLsizei)w, (GLsizei) h);
  glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
}

void timer(int)
{
  glutPostRedisplay();
  glutTimerFunc(1000.0 / updateRate, timer, 0);
}

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cout << "Usage: icosahedron testnumber" << endl;
      exit(1);
    }
  // Set the global test number
  testNumber = atol(argv[1]);
  if (5 == testNumber){
    depth = atol(argv[2]);
  }

  // Initialize glut  and create your window here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Icosahedron");
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);


  // Set your glut callbacks here
  if (1 == testNumber){
    glutDisplayFunc(Test1);
  }
  else if (2 == testNumber){
    glutDisplayFunc(Test2);
  }
  else if (3 == testNumber){
    glutDisplayFunc(Test3);
  }
  glutReshapeFunc(reshape);
  glutTimerFunc(1000.0 / updateRate, timer, 0);
  // Enter the glut main loop here
  glutMainLoop();
  return 0;
}

