#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>
#ifdef TARGET_OS_MAC
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <pic.h>
#include <ctime> 

#include "scene.h"

using namespace std;

//size of the display window
int WIDTH = 640;
int HEIGHT = 480;

scene* myScene;

//this is the image onto which we are going to be drawing
unsigned char image[640 * 480 * 3];

void initGL();
void display();
void saveJPG(char* fileName);
void drawScene(int display);
void plotPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

int main(int argc, char **argv)
{
	char* filename = argv[1];
	myScene = new scene(filename);

	initGL();

	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Programming Assignment 3: Ray Tracer");
    glutDisplayFunc(display);

	glutTimerFunc(10, drawScene, 1);

	glutMainLoop();
}

//generates the rays and asks the scene to trace them,
//then draws the resulting RGB values to the image buffer
void drawScene(int d)
{
	//get camera parameters from scene
	Vec3f eye = myScene->getEye();
	Vec3f lookAt = myScene->getLookAt();
	Vec3f up = myScene->getUp();
	float fovy = myScene->getFovy();

	fovy = fovy * 3.1416/180;

	//get the direction we are looking
	Vec3f dir = lookAt-eye;
	dir.Normalize();
	//cross up and dir to get a vector to our left
	Vec3f left;
	Vec3f::Cross3(left,up,dir);
	left.Normalize();

	Vec3f currentColor;

	for (int x=0; x<WIDTH; x++)
	{
		for (int y=0; y<HEIGHT; y++)
		{
			//some code that just makes a green/red pattern
			currentColor.Set(x%255/255.0,y%255/255.0,0);

			//you will have to write this function in the scene class, using
			//recursive raytracing to determine color
			//currentColor = myScene->rayTrace(eye,currentDir,0);

			//put the color into our image buffer (making sure value is within range)
			plotPixel(x,y,((int)(min(max(currentColor.x(),0),1)*255))%256,
				((int)(min(max(currentColor.y(),0),1)*255))%256,
				((int)(min(max(currentColor.z(),0),1)*255))%256);

			//refresh display every 10 completed columns of pixels
			if (y==0 && x%10==0)
				display();
		}
	}
	//done, so redisplay and save result
	glutPostRedisplay();
	char* fileName="out.jpg";
	saveJPG(fileName);
}

//write out pixels to image buffer
//x,y is 0,0 in the upper left corner
void plotPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	image[(HEIGHT-y-1) * 3 * WIDTH + x*3] = r;
	image[(HEIGHT-y-1) * 3 * WIDTH + x*3 + 1] = g;
	image[(HEIGHT-y-1) * 3 * WIDTH + x*3 + 2] = b;
}

/* OpenGL view initialization */
void initGL()
{
  /* We wont be using much of OpenGL */
  /* Just set a frontal orthographic projection */

  glMatrixMode(GL_PROJECTION);
  glOrtho(0, WIDTH, 0, HEIGHT, 1, -1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
}

void display()
{
	//send the buffer to the output window
	glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,image);
	glutSwapBuffers();
}

/* Write jpeg buffer to file */
void saveJPG(char* fileName)
{
  Pic *in = NULL;
  in = pic_alloc(WIDTH, HEIGHT, 3, NULL);

  cout<<"Saving JPEG file: "<<fileName<<endl;
  /* copy image buffer into pic buffer taking into account that the y coordinates
     are different */
  for (int i=0; i<HEIGHT; i++)
    /* copy one row */
	memcpy(in->pix+i*WIDTH*3, image+(HEIGHT-i+1)*WIDTH*3, 3 * WIDTH);
  
  if (jpeg_write(fileName, in))
    cout<<"File saved successfully!"<<endl;
  else
    cout<<"Error in saving"<<endl;

  pic_free(in);
}