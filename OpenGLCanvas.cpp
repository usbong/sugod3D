/*
 * Copyright 2020~2022 SYSON, MICHAEL B.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @company: USBONG
 * @author: SYSON, MICHAEL B. 
 * @date created: 20200926
 * @date updated: 20220628; from 20210422
 * @website address: http://www.usbong.ph  
 *
 * References:
 * 1) https://www.mathsisfun.com/sine-cosine-tangent.html;
 * last accessed: 20201026
 * 
 * 2) https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
 * last accessed: 20201026
 *
 * 3) https://github.com/opengl-tutorials/ogl/blob/master/tutorial08_basic_shading/tutorial08.cpp;
 * last accessed: 20210330
 * 
 * 4) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/;
 * last accessed: 20210330
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//TO-DO: -update: "Canvas" to "Engine"?
//TO-DO: -update: this
  
//#include <SDL.h>
//edited by Mike, 20200929

//added by Mike, 20201217
//Reference: https://stackoverflow.com/questions/34152424/autodetection-of-os-in-c-c;
//answer by: Jeegar Patel, 20151208T0940
//auto-identify if Windows Machine
#ifdef _WIN32
	#include <windows.h> //Windows Machine
#endif
/*
#ifdef linux
    printf("In Linux");
#endif
*/
/*	//removed by Mike, 20201121
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
*/

//added by Mike, 20201121
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#endif

#include <stdio.h>
//#include <math.h>

#include "OpenGLCanvas.h"

//added by Mike, 20201001
#include "RobotShip.h"

//added by Mike, 20201207
#include "Pilot.h"

//added by Mike, 20201010
#include "Font.h"

//added by Mike, 20201118
#include "Level.h"

//removed by Mike, 20200929
//TO-DO: -add: these 
/*
#include "PolygonUtils.h"
#include "RobotShip.h"
#include "Enemy.h"
#include "Beam.h"
#include "font.h"
#include "Asteroid.h"
*/

//added by Mike, 20201013
#include "Beam.h"
//added by Mike, 20201016
#include "Asteroid.h"

//added by Mike, 20201217
#include <algorithm>
#include <vector>

//#include "Sound.h"

//#include "DynamicObject.h"

//#include "glfont.h"

//removed by Mike, 20201014
//int i;

//TO-DO: -reverify: KEY_D!=OK; KEY_RIGHT=OK
//TO-DO: -reverify: KEY_W!=OK; KEY_UP=OK

//added by Mike, 20210321
#include <iostream> //we use with std::cout

//added by Mike, 20201001
enum Keys
{
/*	//edited by Mike, 20210128
	KEY_UP = 0,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_SPACE,
	//edited by Mike, 20201013
	KEY_ENTER,
	//TO-DO: -verify: gamepad
	KEY_A,
	KEY_D,
	KEY_W,
	KEY_S,
*/
	//TO-DO: -verify: gamepad
/*	//edited by Mike, 20210129
	KEY_A = 0,
	KEY_D,
	KEY_W,
	KEY_S,
*/
	KEY_W = 0,
	KEY_S,
	KEY_D,
	KEY_A,
/* //removed by Mike, 20210130
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_SPACE,
	KEY_ENTER,
*/
	KEY_J,
	KEY_L,
	KEY_I,
	KEY_K,
	KEY_H, //added by Mike, 20210111
	KEY_U, //added by Mike, 20210121

	//added by Mike, 20201201
	iNumOfKeyTypes
};

//added by Mike, 20210403
typedef struct
{
    GLubyte id_field_length;
    GLubyte color_map_type;
    GLubyte image_type_code;
    GLubyte ignore[9];
    GLushort width;
    GLushort height;
    GLubyte image_pixel_size;
    GLubyte image_descriptor;
} TARGA_HEADER;

//added by Mike, 20210403
GLboolean OpenGLCanvas::test_pow2(GLushort i)
{
    while (i % 2 == 0)
        i /= 2;
    if (i == 1)
        return GL_TRUE;
    else
        return GL_FALSE;
}

//added by Mike, 20201213
//Reference: https://stackoverflow.com/questions/10287924/fastest-way-to-sort-a-list-of-number-and-their-index;
//last accessed: 20201213
//answer by: Jerry Coffin, 20120423T2045
//edited by: 20131118T1435
//TO-DO: -add: in UsbongUtils
//descending
struct sortByZPosition { 
    //bool operator()(MyDynamicObject const &left, MyDynamicObject const &right) { 
    //bool operator()(MyDynamicObject &left, MyDynamicObject &right) { 
    bool operator()(MyDynamicObject *left, MyDynamicObject *right) { 
//        return left.getZ() > right.getZ();
        return left->getZ() > right->getZ();
    }
};

/*	//removed by Mike, 20200929
typedef struct
{
    GLubyte id_field_length;
    GLubyte color_map_type;
    GLubyte image_type_code;
    GLubyte ignore[9];
    GLushort width;
    GLushort height;
    GLubyte image_pixel_size;
    GLubyte image_descriptor;
} TARGA_HEADER;
*/

OpenGLCanvas::OpenGLCanvas()
{
  myRepaintCounter=0;
  myRepaintDelay=20;
}

OpenGLCanvas::~OpenGLCanvas()
{
}

bool OpenGLCanvas::init()
{	
	//TO-DO: -receive: values from main.cpp
	//edited by Mike, 20201115
	//noted by Mike, 20201202: smaller grid
/*    myWindowWidth=640;
    myWindowHeight=640;
*/
/*	//edited by Mike, 20210114
	myWindowWidth=2048;
    myWindowHeight=2048;
*/
/*	//edited by Mike, 20210116
	myWindowWidth=4096;
    myWindowHeight=4096;
*/
/*	//edited by Mike, 20210116; noticeable animation skipping problem
	myWindowWidth=8192;
    myWindowHeight=8192;
*/
/*	//edited by Mike, 20210320
	myWindowWidth=6144;
    myWindowHeight=6144;
*/
	
//added by Mike, 20210207
//TO-DO: -add: load level map as input.txt file
//TO-DO: -update: legs during diagonal firing of beams
/*	//30x30 grid OK
	myWindowWidth=8192;
    myWindowHeight=8192;imageSpriteExampleMike
*/

    //added by Mike, 20201023
    myCanvasPosX=-3.2f;//0.0f;
	myCanvasPosY=-1.0f;//0.0f;
	myCanvasPosZ=-3.2f;//0.0f;
    myCanvasEyePosX=0.0f;
	
	//added by Mike, 20201204
	//Linux Machine; Calibrate Canvas positions
/*    myCanvasPosX-=5.598498;
	myCanvasPosZ-=5.598498;
*/
/*
	myCanvasPosX=16.8f;
	myCanvasPosZ=16.8f;
*/	
    //edited by Mike, 20201025
	myCanvasStepX=0.3f;//0.32f;//0.3f;//0.1f;
	myCanvasStepY=0.3f;//0.32f;//0.3f;//0.1f;
	myCanvasStepZ=0.3f;//0.32f;//0.3f;//0.1f;
//	myCanvasEyeStepX=0.3f; //removed by Mike, 20201026
	
	//added by Mike, 20201025; edited by Mike, 20201026
	//add +0.5f to turn right without turning left first
	myCanvasLookAtAngle=-90.0f+0.5f;//-90.0f;
	
	//added by Mike, 20201024; removed by Mike, 20201025
	//myCanvasRotateAxisStepY=0.0f;

	//added by Mike, 20201025
    myCanvasEyePosX=0.0f;
	//edited by Mike, 20210117
//    myCanvasEyePosY=0.0f;
    myCanvasEyePosY=1.0f;

	//edited by Mike, 20210117
	//note: 3.0f OK if not rapid fire of beams as projectile
	//5.0f OK for rapid fire, but edge of 30x30 grid 
	//with window size 6144x6144 already visible
//    myCanvasEyePosZ=3.0f;//0.0f;//3.0f;
    myCanvasEyePosZ=5.0f;//0.0f;//3.0f;

    myCanvasCenterPosX=0.0f;
    myCanvasCenterPosY=0.0f;
    //edited by Mike, 20201026
    myCanvasCenterPosZ=1.0f;//1.0f;
/*
	//added by Mike, 20201026
    myCanvasLookAtAngleRad = (myCanvasLookAtAngle) * 3.141593f / 180.0f;
    zAccel = (cos(myCanvasLookAtAngleRad)*myCanvasStepZ);
    xAccel = -(sin(myCanvasLookAtAngleRad)*myCanvasStepX);
*/

/*
 	iRowCountMax=10;
 	iColumnCountMax=10;
*/
	
	//added by Mike, 20201113; edited by Mike, 20201115
/* 	iRowCountMax=10;
 	iColumnCountMax=10;
*/
/*	//edited by Mike, 20210114
 	iRowCountMax=20;
 	iColumnCountMax=20;
*/
	//note: noticeably delay in computer's auto-draw
	//myWindowWidth and myWindowHeight: 4096
	//iRowCountMax and iColumnCountMax: 40
	//Computer specifications:
	//Processor: Genuine Intel(R) CPU T2130 @1.86GHz
	//RAM: 3.00GB (2.87 GB usable)
	//System type: 32-bit Operating System
	//Windows 7 Ultimate (C) 2009 Service Pack 1
	//additional note: this is a stress test
	//for 3D grid using tiles as cube
	//Solution: in main.cpp
	//lower auto-draw sleep delay number to update OpenGLCanvas.cpp
	//TO-DO: -reverify: animation skipping problem 
/*	//edited by Mike, 20210116
 	iRowCountMax=40;
 	iColumnCountMax=40;
*/
/*	//edited by Mike, 20210116; noticeable animation skipping problem
 	iRowCountMax=80;
 	iColumnCountMax=80;
*/
	//note: reducing size of iRowCountMax and iColumnCountMax
	//to make cube smaller causes smoother animation
	//example: 30x30
	//TO-DO: -add: no need to draw all faces of each cube if not seen
	//edited by Mike, 20210117
/* 	iRowCountMax=60;
 	iColumnCountMax=60;
*/
	
/*	//edited by Mike, 20210321
	iRowCountMax=30;
 	iColumnCountMax=30;
	iHeightCountMax=30; //added by Mike, 20210208
*/
	//TO-DO: -reverify: auto-draw based on double array container 
	//for excess auto-drawing of objects even those already outside viewport,
	//e.g. over 3 rows or 3 columns excess
	//60*4=240; 240=maxViewPort
	//we use excess auto-draw outside camera viewport to eliminate object noticeably appearing
	//to be auto-drawn on screen while we move the camera viewport
	iRowCountMax=60;
 	iColumnCountMax=60;
	iHeightCountMax=60; //added by Mike, 20210208

/*	//edited by Mike, 20210320
	fGridSquareWidth = myWindowWidth/iColumnCountMax/100.0;
	fGridSquareHeight = myWindowHeight/iRowCountMax/100.0;
*/
	fGridSquareWidth = 4.0f;
	fGridSquareHeight = 4.0f;
	
	//added by Mike, 20210416
	fKahonRotation=0;
	
    keyPressCounter=0;
    
    //added by Mike, 20200930
	currentState = GAME_SCREEN; //TO-DO: -update: this

    //added by Mike, 20210211
    myLevel = new Level();    
    myLevel->setupLevel(LEVEL_TEXTURE); //FONT_TEXTURE);

    //added by Mike, 20210320; edited by Mike, 20210321
/*	
	myWindowWidth=myLevel->getMaxXAxisViewport()*fGridSquareWidth;
    myWindowHeight=myLevel->getMaxZAxisViewport()*fGridSquareHeight;
*/
	//getMaxXAxisViewport()... already the actual size
	myWindowWidth=myLevel->getMaxXAxisViewport();
    myWindowHeight=myLevel->getMaxZAxisViewport();
	

	//added by Mike, 20201001
	//edited by Mike, 20201115
	//myRobotShip = new RobotShip;
	//edited by Mike, 20210211
	//myRobotShip = new RobotShip(0.0f,0.0f,0.0f,myWindowWidth,myWindowHeight);
	
	//added by Mike, 20210321
	//TO-DO: -update: these due to getMaxXAxisViewport()... already the actual size
	
//	printf("%d",myLevel->getMaxXAxisViewport());
	myRobotShip = new RobotShip(0.0f,0.0f,0.0f,myLevel->getMaxXAxisViewport()*fGridSquareWidth,myLevel->getMaxZAxisViewport()*fGridSquareHeight);
	myRobotShip->setOpenGLCanvas(this);

//TO-DO: -update: myPilot instructions, e.g. movement
	//added by Mike, 20201207; edited by Mike, 20210219
//	myPilot = new Pilot(0.0f,0.0f,0.0f,myWindowWidth,myWindowHeight);
	myPilot = new Pilot(0.0f,0.0f,0.0f,myLevel->getMaxXAxisViewport()*fGridSquareWidth,myLevel->getMaxZAxisViewport()*fGridSquareHeight);
	myPilot->setOpenGLCanvas(this);

	//added by Mike, 20201013; edited by Mike, 20201014
//	for (i=0; i<MAX_BEAMS; i++) {
	for (int i=0; i<MAX_BEAMS; i++) {
		//edited by Mike, 2020116
//      myBeam[i] = new Beam;
		//edited by Mike, 20210219; edited by Mike, 20210321
		myBeam[i] = new Beam(0.0f,0.0f,0.0f,myWindowWidth,myWindowHeight);
//		myBeam[i] = new Beam(0.0f,0.0f,0.0f,myLevel->getMaxXAxisViewport()*fGridSquareWidth,myLevel->getMaxZAxisViewport()*fGridSquareHeight);
	}

	//added by Mike, 20201016
	//-------------------------------------------
	numOfAsteroidsLeft=MAX_ASTEROID;

    //init asteroids and set their positions to the four corners 
/*    myAsteroid[0] = new Asteroid(PARENT_STATUS,0.0f,1.0f);//,10,10); //TOP RIGHT
    myAsteroid[1] = new Asteroid(PARENT_STATUS,0.0f,0.0f);//,-10,10); //TOP LEFT
    myAsteroid[2] = new Asteroid(PARENT_STATUS,1.0f,0.0f);//,-10,-10); //BOTTOM LEFT
    myAsteroid[3] = new Asteroid(PARENT_STATUS,1.0f,1.0f);//,10,-10); //BOTTOM RIGHT
*/

/*	//edited by Mike, 20201017
    myAsteroid[0] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT
    myAsteroid[1] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,-10,10); //TOP LEFT
    myAsteroid[2] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,-10,-10); //BOTTOM LEFT
    myAsteroid[3] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,-10); //BOTTOM RIGHT
*/
	for (int i=0; i<4; i++) {
		//edited by Mike, 20201113
//    	myAsteroid[i] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT		
//    	myAsteroid[i] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20201115
//    	myAsteroid[i] = new Asteroid(PARENT_STATUS,fGridSquareWidth,0.0f,fGridSquareHeight);//,10,10); //TOP RIGHT
		//edited by Mike, 20210219
		//myAsteroid[i] = new Asteroid(PARENT_STATUS,fGridSquareWidth,0.0f,fGridSquareHeight,myWindowWidth,myWindowHeight);//TOP RIGHT
		myAsteroid[i] = new Asteroid(PARENT_STATUS,fGridSquareWidth,0.0f,fGridSquareHeight,myLevel->getMaxXAxisViewport()*fGridSquareWidth,myLevel->getMaxZAxisViewport()*fGridSquareHeight);		
	}

	for (int i=0; i<4; i++) {
		//edited by Mike, 20201113
//    	myAsteroid[i+4] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20201115
//    	myAsteroid[i+4] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20210219
    	//myAsteroid[i+4] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myWindowWidth,myWindowHeight); //TOP RIGHT		
		myAsteroid[i+4] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myLevel->getMaxXAxisViewport()*fGridSquareWidth,myLevel->getMaxZAxisViewport()*fGridSquareHeight);
	}

	for (int i=0; i<4; i++) {
		//edited by Mike, 20201113
//    	myAsteroid[i+8] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20201115
//    	myAsteroid[i+8] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20210219
		//myAsteroid[i+8] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myWindowWidth,myWindowHeight);//TOP RIGHT		
		myAsteroid[i+8] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myLevel->getMaxXAxisViewport()*fGridSquareWidth,myLevel->getMaxZAxisViewport()*fGridSquareHeight);
	}

	for (int i=0; i<4; i++) {
		//edited by Mike, 20201113
//    	myAsteroid[i+12] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20201115
//    	myAsteroid[i+12] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20210219
    	//myAsteroid[i+12] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myWindowWidth,myWindowHeight);//TOP RIGHT		
		myAsteroid[i+12] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myLevel->getMaxXAxisViewport()*fGridSquareWidth,myLevel->getMaxZAxisViewport()*fGridSquareHeight);
	}

/*	//removed by Mike, 20201016
    for (int i=4; i<12; i++)   
    {
        myAsteroid[i] = new Asteroid(CHILD_STATUS,0,0);
    }
    //group them into 3's
    myAsteroid[0]->attachChild(myAsteroid[4],myAsteroid[5]);
    myAsteroid[1]->attachChild(myAsteroid[6],myAsteroid[7]);
    myAsteroid[2]->attachChild(myAsteroid[8],myAsteroid[9]);
    myAsteroid[3]->attachChild(myAsteroid[10],myAsteroid[11]);
    for (int i=12; i<MAX_ASTEROID; i++)   
    {
        myAsteroid[i] = new Asteroid(GRANDCHILD_STATUS,0,0);
    }
    myAsteroid[4]->attachChild(myAsteroid[12],myAsteroid[13]);
    myAsteroid[5]->attachChild(myAsteroid[14],myAsteroid[15]);
    myAsteroid[6]->attachChild(myAsteroid[16],myAsteroid[17]);
    myAsteroid[7]->attachChild(myAsteroid[18],myAsteroid[19]);
    myAsteroid[8]->attachChild(myAsteroid[20],myAsteroid[21]);
    myAsteroid[9]->attachChild(myAsteroid[22],myAsteroid[23]);
    myAsteroid[10]->attachChild(myAsteroid[24],myAsteroid[25]);
    myAsteroid[11]->attachChild(myAsteroid[26],myAsteroid[27]);
*/
    
/* //removed by Mike, 20201213    
    for (int i=0; i<MAX_ASTEROID; i++)   
    {
//      myAsteroid[i] = new Asteroid;
	//removed by Mike, 20201016
//        myAsteroid[i]->setOpenGLCanvas(this);
    }
*/

	//added by Mike, 20201213
	//std::vector<MyDynamicObject*> v;	
	vMyDynamicObjectContainer.push_back(myPilot);
	vMyDynamicObjectContainer.push_back(myRobotShip);

/*	//removed by Mike, 20210120
	for (int i=0; i<MAX_BEAMS; i++) { //32
		vMyDynamicObjectContainer.push_back(myBeam[i]);
	}
*/

	for (int i=0; i<MAX_ASTEROID; i++) { //16			
		vMyDynamicObjectContainer.push_back(myAsteroid[i]);
	}	
	
/*
	myDynamicObjectContainer[0]=myPilot;
	myDynamicObjectContainer[1]=myRobotShip;
	for (int i=0; i<MAX_BEAMS; i++) { //32
		myDynamicObjectContainer[i+2]=myBeam[i];
	}
	for (int i=0; i<MAX_ASTEROID; i++) { //16			
		myDynamicObjectContainer[i+2+MAX_BEAMS]=myAsteroid[i];
	}
*/
	
	//-------------------------------------------
    //added by Mike, 20201011
    setupFont(FONT_TEXTURE);

/* //removed by Mike, 20210211	
    //added by Mike, 20201118
    myLevel = new Level();    
    myLevel->setupLevel(LEVEL_TEXTURE); //FONT_TEXTURE);
*/
	
	//added by Mike, 20210403; edited by Mike, 20210418
//	setupKahonTexture(KAHON_TEXTURE);
	setupKahonTexture(BAHAY_TEXTURE);

	//added by Mike, 20210420
	//TO-DO: -update: this
	setupTaoTexture();
	
	return true;
}


bool OpenGLCanvas::shutdown()
{
/*	//removed by Mike, 20200929
    sound->unload_sound_clip(thrust);
	sound->unload_sound_clip(rotate);
    sound->unload_sound_clip(beam);
    sound->unload_sound_clip(explosion);
	sound->unload_sound_clip(zing);
	sound->unload_sound_clip(title);
	sound->unload_sound_clip(bonus);
	
    sound->sound_stop();
	
    glDeleteTextures(1, &currTextureBackground);
    glDeleteTextures(1, &myTextureObjectFont);
    glDeleteTextures(1, &titleBackground);
    glDeleteTextures(1, &gameBackground);
	//myBackground->Release();
	//delete myBackground;
	
	//releaseFont(myFontListBase);
*/		

	//added by Mike, 20201016
	for (int i=0; i<MAX_ASTEROID; i++)   
    {
        myAsteroid[i]->destroy();
    }
	
	return true;
}

/*	//removed by Mike, 20200929
GLboolean OpenGLCanvas::test_pow2(GLushort i)
{
    while (i % 2 == 0)
        i /= 2;
    if (i == 1)
        return GL_TRUE;
    else
        return GL_FALSE;
}
*/

/* //removed by Mike, 20200929
//added by Mike, 20200928"RobotShip.h"
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;
   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }
   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount"RobotShip.h", 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}
//Reference: "Beginning OpenGL Game Programming", Chapter 7
//Astle and Kevin Hawkins
//edited by Mike, 2007
void OpenGLCanvas::load_tga(char *filename)
{
    TARGA_HEADER targa;
    FILE *file;
//added by Mike, 20200928
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;
   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }
   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount, 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}
    GLubyte *data;
    GLuint i;
    file = fopen(filename, "rb");
    if (file == NULL)
        return;
    // test validity of targa file
    if (fread(&targa, 1, sizeof(targa), file) != sizeof(targa) ||
        targa.id_field_length != 0 || targa.color_map_type != 0 ||
        targa.image_type_code !=
//added by Mike, 20200928
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
//added by Mike, 20200928
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;
   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }
   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount, 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;
   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }
   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount, 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
} 2 || ! test_pow2(targa.width) ||
        ! test_pow2(targa.height) || targa.image_pixel_size != 32 ||
        targa.image_descriptor != 8)
    {
        fclose(file);
        free(data);
        return;
    }
    // read targa file into memory
    data = (GLubyte *) malloc(targa.width * targa.height * 4);
    if (fread(data, targa.width * targa.height * 4, 1, file) != 1)
    {
        fclose(file);
        return;
    }
    // swap texture bytes so that BGRA becomes RGBA
    for (i = 0; i < targa.width * targa.height * 4; i += 4)
    {
        GLbyte swap = data[i];
        data[i] = data[i + 2];
        data[i + 2] = swap;
    }
    // build OpenGL texture
    fclose(file);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, targa.width, targa.height,
                      GL_RGBA, GL_UNSIGNED_BYTE, data);
    free(data);
}
*/

/* //removed by Mike, 20200929https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
bool OpenGLCanvas::loadBackground()
{
    // retrieve "unused" texture object
	glGenTextures(1, &titleBackground);
    // select texture 1
    glBindTexture(GL_TEXTURE_2D, titleBackground);//1);
    // create OpenGL texture out of targa file
    //removed by Mike, 20200929
    //TO-DO: -update: this
    //load_tga("textures/title.tga");//background.
    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// retrieve "unused" texture object
	glGenTextures(1, &gameBackground);
    // select texture 1
    glBindTexture(GL_TEXTURE_2D, gameBackground);//1);
    // create OpenGL texture out of targa file
    //removed by Mike, 20200929
    //TO-DO: -update: this
//    load_tga("textures/background.tga");//background.
    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // unselect texture 1
    glBindTexture(GL_TEXTURE_2D, 0);
    currTextureBackground=titleBackground;
}
*/

bool OpenGLCanvas::setupProjection()
{
	/*	//removed by Mike, 20200929
    glViewport(0, 0, myWindowWidth, myWindowHeight); // reset the viewport to new dimensions
	*/
	return true;
}

/*	//removed by Mike, 20200929
void OpenGLCanvas::drawPlane()
{
    //glColor3f(1.0f, 1.0f, 1.0f);//default: white
	glBegin(GL_TRIANGLE_STRIP);
	    //note: In "glTexCoord2f(1.0, 0.0);", if 1.0 is changed to 2.0, the plane is made up of 4 images instead of just 1 whole image 
		glTexCoord2f(1.0, 0.0); glVertex3f(10.0, -10.0, -10.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, -10.0);
		glTexCoord2f(1.0, 1.0);	glVertex3f(10.0, -10.0, 10.0);
		glTexCoord2f(0.0, 1.0);	glVertex3f(-10.0, -10.0, 10.0);	
	glEnd();
}
*/

void OpenGLCanvas::keyDown(int keyCode)
{
	myKeysDown[keyCode] = TRUE;	
	
	//added by Mike, 20201226
	myRobotShip->keyDown(keyCode);
}
void OpenGLCanvas::keyUp(int keyCode)
{
	myKeysDown[keyCode] = FALSE;	

	//added by Mike, 20201226
	myRobotShip->keyUp(keyCode);
}



//added by Mike, 20210403
//TO-DO: -update: this
void OpenGLCanvas::load_tga(char *filename)
//void load_tga(std::string filename)
{
    TARGA_HEADER targa;
    FILE *file;
    GLubyte *data;
    GLuint i;

    file = fopen(filename, "rb");
    if (file == NULL)
        return;

    /* test validity of targa file */
    if (fread(&targa, 1, sizeof(targa), file) != sizeof(targa) ||
        targa.id_field_length != 0 || targa.color_map_type != 0 ||
        targa.image_type_code != 2 || ! test_pow2(targa.width) ||
        ! test_pow2(targa.height) || targa.image_pixel_size != 32 ||
        targa.image_descriptor != 8)
    {
        fclose(file);
        return;
    }

    /* read targa file into memory */
    data = (GLubyte *) malloc(targa.width * targa.height * 4);
    if (fread(data, targa.width * targa.height * 4, 1, file) != 1)
    {
        fclose(file);
        free(data);
        return;
    }

    /* swap texture bytes so that BGRA becomes RGBA */
    for (i = 0; i < targa.width * targa.height * 4; i += 4)
    {
        GLbyte swap = data[i];
        data[i] = data[i + 2];
        data[i + 2] = swap;
    }

    /* build OpenGL texture */
    fclose(file);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, targa.width, targa.height,
                      GL_RGBA, GL_UNSIGNED_BYTE, data);
    free(data);
    
/*   char str[700];                                       
   sprintf(str,"dito: %f",0.0f);
*/
//   std::cout << "keydown " << "\n";
	//printf("dito");
}


//added by Mike, 20210402
//TO-DO: -update: this
void OpenGLCanvas::setupKahonTexture(int myKahonTextureObject)
{
	//removed by Mike, 20201010
	//due to blank output
    //glEnable(GL_DEPTH_TEST);

    /* select texture 1 */
	glBindTexture(GL_TEXTURE_2D, myKahonTextureObject);
	
    /* create OpenGL texture out of targa file */
//    load_tga("textures/font.tga");
//    load_tga("textures/concrete.tga");

	//edited by Mike, 20210409
//    load_tga("textures/armor.tga");	
//    load_tga("textures/imageSpriteExampleMike.tga");	
	//edited by Mike, 20210416
//    load_tga("textures/imageSpriteExampleMikeWithoutBG.tga");	
//edited by Mike, 20210418	
//    load_tga("textures/armor.tga");	

	if (myKahonTextureObject==KAHON_TEXTURE) {
    	load_tga("textures/imageSpriteExampleMikeWithoutBG.tga");	
	}
	else if (myKahonTextureObject==ARMOR_TEXTURE) {
    	load_tga("textures/armor.tga");	
	}
	else {  //BAHAY_TEXTURE
    	load_tga("textures/bahay.tga");	
	}	
	
	//    load_tga("textures/uvtemplate.tga");
//    load_tga("textures/uvHalimbawa.tga");
    
	/* set texture parameters */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* unselect texture myFontTextureObject */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* setup alpha blending */
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

/* //removed by Mike, 20210403	
    // set background color to bluish
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // unselect texture myFontTextureObject
    glBindTexture(GL_TEXTURE_2D, 0);

    // setup alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
*/
	//removed by Mike, 20201012
    /* set background color to bluish to demonstrate font transparency */
//    glClearColor(0.0f, 0.0f, 0.25f, 1.0f); /* to demonstrate font transparency */

}

//added by Mike, 20210420
//TO-DO: -update: this
void OpenGLCanvas::setupTaoTexture()
{
	//removed by Mike, 20201010
	//due to blank output
    //glEnable(GL_DEPTH_TEST);

    // select texture 1
	glBindTexture(GL_TEXTURE_2D, MIKE_TEXTURE_A);
	
    /* create OpenGL texture out of targa file */
	//edited by Mike, 20210420
//    load_tga("textures/armor.tga");	
    load_tga("textures/imageSpriteExampleMikeWithoutBG.tga");	
	
	// set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

/*
    // select texture 1
	glBindTexture(GL_TEXTURE_2D, MIKE_TEXTURE_B);
	
    // create OpenGL texture out of targa file
    load_tga("textures/armor.tga");	
	
	// set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
    // select texture 1
	glBindTexture(GL_TEXTURE_2D, MIKE_TEXTURE_C);
	
    // create OpenGL texture out of targa file
    load_tga("textures/armor.tga");	
	
	// set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
*/
	
    /* unselect texture myFontTextureObject */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* setup alpha blending */
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void OpenGLCanvas::render()
{     
	//added by Mike, 20201023
	//note: this is to be print-ready in newsletter
	//we use recycled paper
	//edited by Mike, 2020116
	//edited by Mike, 20201122
//   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
//   glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Set background color to white and not opaque
	//removed by Mike, 20201122
	//sky blue
//   glClearColor(0.69f, 0.84f, 1.0f, 0.0f); // Set background color to white and not opaque
	//edited by Mike, 20201122
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Set background color to white and not opaque

	//added by Mike, 20201012
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    //removed by Mike, 20201015
//    glViewport(0, 0, myWindowWidth, myWindowHeight);		// reset the viewport to new 

	//added by Mike, 20201207
	//Reference: https://www.khronos.org/opengl/wiki/Depth_Test;
	//last accessed: 20201206
	//TO-DO: -verify: this
	//TO-DO: -add: Z-sort, i.e. sort objects by Z-axis when computer auto-draws
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	//Reference: https://community.khronos.org/t/gradient-background/54348/2;
	//last accessed: 20201122
	//answer by: NiCo1, 2008-03
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		/* //horizontal
		glBegin(GL_QUADS);
			//red color
			glColor3f(1.0,0.0,0.0);
			glVertex2f(-1.0, 1.0);
			glVertex2f(-1.0,-1.0);
			//blue color
			glColor3f(0.0,0.0,1.0);
			glVertex2f(1.0,-1.0);
			glVertex2f(1.0, 1.0);
			glEnd();
		*/
	
		glBegin(GL_QUADS);
		//	glColor3f(0.0f,0.0f,0.0f); //black
		//	glColor3f(1.0f,1.0f,1.0f); //white
		
			//TOP
			//sky blue color; darker
		//	glColor3f(0.51f, 0.73f, 0.98f);
		//	glColor3f(0.08f, 0.51f, 1.00f);
		//	glColor3f(0.0f, 0.32f, 0.67f);
			glColor3f(0.0f, 0.44f, 0.67f);
			glVertex2f(1.0, 1.0);
			glVertex2f(-1.0, 1.0);
		
			//BOTTOM
			//sky blue color; brighter
			glColor3f(0.69f, 0.84f, 1.0f);
			glVertex2f(-1.0,-1.0);
			glVertex2f(1.0,-1.0);
		glEnd();


    //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//TOP-LEFT origin
	glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maximum
      	);

/*	//removed by Mike, 20201117
    //font 
    // select and enable texture FONT_TEXTURE
	//edited by Mike, 20201012
    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
    glEnable(GL_TEXTURE_2D);
*/		
    if (currentState==TITLE_SCREEN) {                                    
    }
    else if (currentState==CONTROLS_SCREEN) {
    }
    else if (currentState==GAMEOVER_SCREEN) {
    }
    else if (currentState==HIGHSCORE_SCREEN) {
    }
    else if (currentState==GAME_SCREEN) {
/* //removed by Mike, 20201117
//TO-DO: -update: this
		sprintf(tempText,"USBONG");
		//TO-DO: -update: this to not add 0.1 in y-axis
//	    draw_string(0, 0, tempText);    	
		//edited by Mike, 2020117
//	    draw_string(0, 0.1, tempText);    	
	    draw_string(0, 0.1, tempText);    	
	    glDisable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, 0);
*/

  	//added by Mike, 20201117
    //font 
    /* select and enable texture FONT_TEXTURE */
	//edited by Mike, 20201012
    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
    glEnable(GL_TEXTURE_2D);

  	//TO-DO: -update: this
	sprintf(tempText,"USBONG");
	//TO-DO: -update: this to not add 0.1 in y-axis
//	    draw_string(0, 0, tempText);    	
	//edited by Mike, 2020117
//	    draw_string(0, 0.1, tempText);    
	//edited by Mike, 20210416	
//    draw_string(0.0f, 0.1f, 0.0f, tempText);    	
    draw_string(0.0f, 0.12f, 0.0f, tempText);    	

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);


	//added by Mike, 20201020
	//note: we add these to enable complete drawing of 3D shape with z-axis
	//--------------------------------------------------------
	//removed by Mike, 20201118; added by Mike, 20210416
	//solves problem with quad face image texture merging
    glEnable(GL_CULL_FACE);
//https://www.khronos.org/opengl/wiki/Face_Culling; last accessed: 20201122
//    glCullFace(GL_BACK);

	//removed by Mike, 20201010
	//TO-DO: -reverify: this
	//due to blank output in Font texture
//    glEnable(GL_DEPTH_TEST);
	
	//removed by Mike, 2020117
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//added by Mike, 20201114
//	glDepthFunc(GL_ALWAYS);


	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	//TO-DO: -reverify: these
	// calculate aspect ratio of window
	//gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);	
/*    //edited by Mike, 20201022
    gluPerspective(90.0, // field-of-view angle
                   4.0 / 3.0, // aspect ratio
                   1.0, // near plane
                   100); // far plane
*/

/*	//edited by Mike, 20201114
    gluPerspective(90.0, // field-of-view angle
                   4.0 / 4.0, // aspect ratio
                   0.1, // near plane
                   100); // far plane
*/
/* //edited by Mike, 20210416		
    gluPerspective(90.0, // field-of-view angle
                   4.0 / 3.0, // aspect ratio
                   0.1, // near plane
                   100); // far plane
*/
    gluPerspective(90.0, // field-of-view angle
                   4.0 / 4.0, // aspect ratio
                   0.1, // near plane
                   100); // far plane
		
/* //removed by Mike, 20201118
	//TO-DO: -reverify: these
	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix
*/

/*
    gluLookAt(0.0, 1.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 0.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/
/*
    gluLookAt(0.0, 1.0, 3.0, // eye position 0.0, 0.0, 3.0
              1.0, 0.0, 0.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/
/*	UFO Catcher View; Z as up
    gluLookAt(0.0, 1.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 0.0, 1.0); // up-direction
*/
/*	UFO Catcher View; Y as up
	//reverify: robotship cube
    gluLookAt(0.0, -1.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/

	//edited by Mike, 20201023
/*
    gluLookAt(0.0, 1.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/

/*	//edited by Mike, 20201025
    gluLookAt(myCanvasEyePosX, 0.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
//              1.0, 1.0, 0.0); // up-direction //floor head down
*/
/*	//edited by Mike, 20201115
    gluLookAt(myCanvasEyePosX, myCanvasEyePosY, myCanvasEyePosZ, // eye position 0.0, 0.0, 3.0
              myCanvasCenterPosX, myCanvasCenterPosY, myCanvasCenterPosZ, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/
    gluLookAt(myCanvasEyePosX, myCanvasEyePosY, myCanvasEyePosZ, // eye position 0.0, 0.0, 3.0
              myCanvasCenterPosX, myCanvasCenterPosY, myCanvasCenterPosZ, // look-at point
              0.0, 1.0, 0.0); // up-direction
/*	//edited by Mike, 20210311
    gluLookAt(myCanvasEyePosX, myCanvasEyePosY, myCanvasEyePosZ*2, // eye position 0.0, 0.0, 3.0
              myCanvasCenterPosX, myCanvasCenterPosY, myCanvasCenterPosZ, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/		
		
/*
    gluLookAt(0.0, 0.5, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/
	//--------------------------------------------------------

	//note: reference point/origin at center; not top-left

	//added by Mike, 20210220
	//ISOMETRIC VIEW					  	
	//-----
	//added by Mike, 20201115
/*		
	glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
////    glScalef(0.2f, 0.2f, 0.2f);
	//-----
*/

	//added by Mike, 20210220
	//3rd-person view
	//without additional rotate and scale
	//TO-DO: -reverify: robot's draw sequence

	//added by Mike, 20210323
	//Tron Bonne Mini Game: Cannonballs
	//https://www.youtube.com/watch?v=P1S3Mt49qyg;
	//last accessed: 20210323
	glRotatef(30, 1.0f, 0.0f, 0.0f);
		
	//added by Mike, 20210220; edited by Mike, 20210220
	//2D horizontal-scrolling, vertical-scrolling view
	//note: Zelda Link's Awakening DX; Gameboy Color
	//-----
//	glRotatef(30, 0.0f, 1.0f, 0.0f);
/*    glScalef(0.2f, 0.2f, 0.2f);
*/
	//-----
		
/*	//removed by Mike, 20210323
//added by Mike, 20210311
	//TOP-VIEW
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
*/
		
//    glTranslatef(-1.0f, -1.0f, 0.0f);

	//added by Mike, 20210320
 	//set to TOP-LEFT
//	glTranslatef(-myWindowWidth/100/2, 0.0f, -myWindowHeight/100/2);

		
	//edited by Mike, 2021022
//    glTranslatef(-1.0f, -1.0f, 0.0f);
//    glTranslatef(-3.0f, -1.0f, 0.0f);
//    glTranslatef(-3.2f, 0.0f, 0.0f);
	//edited by Mike, 20201023
//    glTranslatef(-3.2f, 0.0f, -3.2f);
    glTranslatef(myCanvasPosX, myCanvasPosY, myCanvasPosZ);
  
    //added by Mike, 2020116; edited by Mike, 20201116
   	//wrap the world 
/*
//           		if (myXPos <= 0.0f) myXPos = 20-myWidth/8; //if left side
	if (myCanvasPosX <= 0.0f) myCanvasPosX = myWindowWidth/100;//-myWidth/8; //if left side
	else if (myCanvasPosX >= myWindowWidth/100) myCanvasPosX = 0.0f;//+myWidth/8; //if right side
	if (myCanvasPosZ >= myWindowHeight/100) myCanvasPosZ = 0.0f;//+myHeight/8; //if bottom side
	//edited by Mike, 20201116
//           		else if (myZPos <= 0.0f) myZPos = 20-myHeight/8; //if top side
	else if (myCanvasPosZ <= 0.0f) myCanvasPosZ = myWindowHeight/100;//-myHeight/8; //if top side
*/
	//edited by Mike, 20201202
/* //Windows Machine
	//note: negative value
	if (myRobotShip->getX() <= 0.0f) myCanvasPosX = 0.0f-myWindowWidth/100+myRobotShip->getWidth()/8;//-myWidth/8; //if left side
	//edited by Mike, 20201202		
	else if (myRobotShip->getX() >= myWindowWidth/100) myCanvasPosX = 0.0f+myRobotShip->getWidth()/8;//+myWidth/8; //if right side
//	else if (myRobotShip->getX() >= 10) myCanvasPosX = 0.0f+myRobotShip->getWidth()/8;//+myWidth/8; //if right side
	if (myRobotShip->getZ() >= myWindowHeight/100) myCanvasPosZ = 0.0f+myRobotShip->getHeight()/8; //if bottom side
	//note: negative value
	else if (myRobotShip->getZ() <= 0.0f) myCanvasPosZ = 0.0f-myWindowHeight/100+myRobotShip->getHeight()/8;//-myHeight/8; //if top side
*/
	//TO-DO: -reverify: with Windows Machine
	//Linux Machine
/*	printf("CanvasPosX: %f\n", myCanvasPosX);
	printf("robotShipX: %f\n", myRobotShip->getX());
	printf("CanvasPosZ: %f\n", myCanvasPosZ);
	printf("robotShipZ: %f\n", myRobotShip->getZ());
*/
/*	//edited by Mike, 20201204		
	//TO-DO: -fix: wrapping bottom and top sides
	if (myCanvasPosX >= 0.0f) myCanvasPosX = 0.0f-20.0f+myRobotShip->getWidth()/8;//myWindowWidth;//-myWidth/8; //if left side
	else if (myCanvasPosX-myRobotShip->getWidth()/8 <= -20.0f) myCanvasPosX = 0.0f+myRobotShip->getWidth()/8;//+myWidth/8; //if right side
		
	if (myCanvasPosZ-myRobotShip->getWidth()/8 <= -20.f) myCanvasPosZ = 0.0f+myRobotShip->getWidth()/8; //if bottom side
	else if (myCanvasPosZ >= 0.0f) myCanvasPosZ = 0.0f-20.0f+myRobotShip->getWidth()/8;//-myHeight/8; //if top side
*/
	//set canvas camera position relative to MyRobotShip position 
/* //edited by Mike, 20210320		
	myCanvasPosX = -myRobotShip->getX()+1.0f; //-3.2 : 4.2; CanvasPosX : robotShipX
	myCanvasPosZ = -myRobotShip->getZ()+1.0f; //-3.2 : 4.2; CanvasPosZ : robotShipZ
*/
 	//set to TOP-LEFT
 	//inverted controller movement
/*	myCanvasPosX = myRobotShip->getX()-myWindowWidth/100/2; //-3.2 : 4.2; CanvasPosX : robotShipX
	myCanvasPosZ = myRobotShip->getZ()-myWindowHeight/100/2; //-3.2 : 4.2; CanvasPosZ : robotShipZ
*/		
	myCanvasPosX = -myRobotShip->getX(); //-3.2 : 4.2; CanvasPosX : robotShipX
	myCanvasPosZ = -myRobotShip->getZ(); //-3.2 : 4.2; CanvasPosZ : robotShipZ
		
/*		
			//note: position calibrate; robotShipX : CanvasPosX
	//note: negative value; linux machine positive 20.0f, not 0.0f		
	printf("myWindowWidth/100: %f\n", myWindowWidth/100.0f);
	if (myRobotShip->getX() <= 0.0f) myCanvasPosX = 0.0f-myWindowWidth/100.0f+myRobotShip->getWidth()/8;//-myWidth/8; //if left side
	else if (myRobotShip->getX() >= myWindowWidth/100.0f) myCanvasPosX = 0.0f+myRobotShip->getWidth()/8;//+myWidth/8; //if right side
	if (myRobotShip->getZ() >= myWindowHeight/100.0f) myCanvasPosZ = 0.0f+myRobotShip->getHeight()/8; //if bottom side
	//note: negative value
	else if (myRobotShip->getZ() <= 0.0f) myCanvasPosZ = 0.0f-myWindowHeight/100+myRobotShip->getHeight()/8;//-myHeight/8; //if top side
		*/
		
		
    //added by Mike, 20201024
//    glTranslatef(3.2f, 1.0f, 3.2f);    
//    glTranslatef(0.0f, 0.0f, 3.2f);
//    glTranslatef(3.2f, 0.0f, 6.4f);
	//removed by Mike, 20201025
//	glRotatef(myCanvasRotateAxisStepY, 0.0f, 1.0f, 0.0f);
	//added by Mike, 20201026; removed by Mike, 20201026
//	glRotatef(myCanvasLookAtAngle, 0.0f, 1.0f, 0.0f);
    

/*
    	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
    	glLoadIdentity();						// reset projection matrix
    	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
    	// load the identity matrix (clear to default position and orientation)
    	glLoadIdentity();  
*/
		
		//added by Mike, 20201207
		//TO-DO: -add: z-sort, i.e. auto-draw objects based on z position;
		//objects with higher z positions are auto-drawn first;
		//these are objects at the back of those that have lower z positions

    	//added by Mike, 20200930
    	drawGridWithZAxis();

/*	//edited by Mike, 20201213
		//added by Mike, 20201001
    	glPushMatrix();		
    		//added by Mike, 202013; edited by Mike, 20201014
//            for(i=0; i<MAX_BEAMS; i++) {
            for(int i=0; i<MAX_BEAMS; i++) {
              if (myBeam[i]->isActive()) {
                myBeam[i]->draw();
			  }
            }
        glPopMatrix();       
		
		//edited by Mike, 20201016
    	glPushMatrix();
            myRobotShip->drawRobotShip();			
        glPopMatrix();       
		//added by Mike, 20201207
    	glPushMatrix();		        
            myPilot->drawPilot();			
        glPopMatrix();       
		//edited by Mike, 20201016
    	glPushMatrix();		                
			//added by Mike, 20201016
            for(int i=0; i<MAX_ASTEROID; i++) {
              //if (myBeam[i]->isActive())
                myAsteroid[i]->draw();
            }
    	glPopMatrix();		
*/

		//added by Mike, 20210120
		//note: draw beam first to be below the rest during auto-draw
    	glPushMatrix();		
            for(int i=0; i<MAX_BEAMS; i++) {
              if (myBeam[i]->isActive()) {
                myBeam[i]->draw();
			  }
            }
        glPopMatrix();       

		//added by Mike, 20201213
		//TO-DO: -reverify: this
		
		//z-sort, i.e. auto-draw objects based on z position;
		//objects with higher z positions are auto-drawn first;
		//these are objects at the back of those that have lower z positions
		//MyDynamicObject *myDynamicObjectContainerSorted[MAX_DYNAMIC_OBJECT];		
		//std::vector<MyDynamicObject*> v;
		std::sort(vMyDynamicObjectContainer.begin(), vMyDynamicObjectContainer.end(), sortByZPosition());
		
		for (int i=0; i<MAX_DYNAMIC_OBJECT; i++) {			
    		glPushMatrix();
				vMyDynamicObjectContainer[i]->draw();
    		glPopMatrix();
		}
		
//vMyDynamicObjectContainer[0]->draw();
//vMyDynamicObjectContainer[1]->draw();
/*
    for (int i=0; i<MAX_ASTEROID; i++)   
    {
		vMyDynamicObjectContainer[1]->draw();
    }
		
	myDynamicObjectContainer[0]=myPilot;
	myDynamicObjectContainer[1]=myRobotShip;
	for (int i=0; i<MAX_BEAMS; i++) { //32
		myDynamicObjectContainer[i+2]=myBeam[i];
	}
*/
/*
	for (int i=0; i<MAX_BEAMS; i++) { //32
		vMyDynamicObjectContainer[i+2]->draw();
	}
	for (int i=0; i<MAX_ASTEROID; i++) { //16			
		vMyDynamicObjectContainer[i+2+MAX_BEAMS]->draw();
	}
*/	
		
		//added by Mike, 20201011; removed by Mike, 20201207
		//TO-DO: -update: this
/*
        currTextureBackground=gameBackground;
        sprintf(tempText,"1P \n       %d", score);
        draw_string(-200, 130, tempText);
    
    	sprintf(tempText,"HIGH-SCORE\n  %d",highScore);
        draw_string(90, 130, tempText);
    
    	sprintf(tempText,"REST %d", rest);
        draw_string(100, -150, tempText);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        //for the rest of the objects in the world
    	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
    	glLoadIdentity();						// reset projection matrix
        gluPerspective(90.0, // field-of-view angle
                       4.0 / 3.0, // aspect ratio
                       1.0, // near plane
                       myWindowWidth); //or myWindowHeight will do, since they are equal
                       //100); // far plane
    
    	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
    	// load the identity matrix (clear to default position and orientation)
    	glLoadIdentity();  
        //note: this is assuming that myWindowWidth and myWindowHeight are equal
        gluLookAt(0.0, 5.0, myWindowWidth/2, // eye position 0.0, 0.0, 3.0
                  0.0, 0.0, 0.0, // look-at point
                  0.0, 1.0, 0.0); // up-direction
*/

	}
}

//edited by Mike, 20201022
/* //previous drawGridWithZAxis()
//added by Mike, 20201020
void OpenGLCanvas::drawGridWithZAxis() {
//	//removed by Mike, 20201020
//     //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
//	 glMatrixMode(GL_PROJECTION);
//	 glLoadIdentity();
	 //TO-DO: -add: Z plane grid
	
	 //draw grid
	 //edited by Mike, 20201015 	 
 	 //TO-DO: -update: iRowCountMax
// 	 int iRowCountMax=10;
 	 int iRowCountMax=20;
 	 //TO-DO: -update: iColumnCountMax
// 	 int iColumnCountMax=10;
 	 int iColumnCountMax=20;
   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
   	//edited by Mike, 20201002
 	 for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
			//edited by Mike, 20201022
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//edited by Mike, 20201015
//      		glVertex2f(1.0f, 0.1f*iRowCount);
      		glVertex2f(0.1f*iRowCountMax, 0.1f*iRowCount);
      		
   		glEnd();   		   	  
	 }
   //columns
   	//edited by Mike, 20201015   	
 	 for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//edited by Mike, 20201015
//      		glVertex2f(0.1f*iColumnCount, 1.0f);
      		glVertex2f(0.1f*iColumnCount, 0.1f*iColumnCountMax);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}
*/
//added by Mike, 20201020
void OpenGLCanvas::drawGridWithZAxis() {
/*	//removed by Mike, 20201020
     //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
*/
	
	 //draw grid
	 //edited by Mike, 20201015 	 
 	 //TO-DO: -update: iRowCountMax
 	 //edited by Mike, 20201022
 	 //removed by Mike, 20201113
// 	 int iRowCountMax=10;
// 	 int iRowCountMax=20;

 	 //TO-DO: -update: iColumnCountMax
 	 //edited by Mike, 20201022
 	 //removed by Mike, 20201113
// 	 int iColumnCountMax=10;
// 	 int iColumnCountMax=20;

	//added by Mike, 20201022
	//example: 640/10 = 64; 64/100 = .64
	//half the window
	//example: 640/2 = 320; 320/10 = 32; 32/100 = .32
/*
	float fColumnSquareWidth = myWindowWidth/2/iRowCountMax/100.0;
	float fRowSquareHeight = myWindowHeight/2/iColumnCountMax/100.0;
*/
	//edited by Mike, 20201022
/*	//half window width and height
	float fSquareWidth = myWindowWidth/2/iColumnCountMax/100.0;
	float fGridSquareHeight = myWindowHeight/2/iRowCountMax/100.0;
*/

	//removed by Mike, 20201113
//	float fSquareWidth = myWindowWidth/iColumnCountMax/100.0;
//	float fGridSquareHeight = myWindowHeight/iRow3CountMax/100.0;


	//removed by Mike, 20201123
/*
	//TO-DO: -add: grid after drawing level 
	//due to glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
	//edited by Mike, 20201120
   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
   	//edited by Mike, 20201002
 	 for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
			//added by Mike, 20201023
			//floor face
			//with Z-axis
      		glVertex3f(0.0f, 0.0f, fGridSquareHeight*iRowCount);    // x, z
      		glVertex3f(fGridSquareWidth*iRowCountMax, 0.0f, fGridSquareHeight*iRowCount);      		
   		glEnd();   		   	  
	 }
   //columns
   	//edited by Mike, 20201015   	
 	 for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
			//added by Mike, 20201022			
			//with Z-axis
      		glVertex3f(fGridSquareWidth*iColumnCount, 0.0f, 0.0f);    // y, z
      		glVertex3f(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iColumnCountMax);
   		glEnd();   		   	  
	 }
*/

  	//added by Mike, 20201118
  	//LEVEL TEXTURE
	//added by Mike, 20201121
	//previous color of grid: green
    glColor3f(1.0f, 1.0f, 1.0f); // set back to default
	//removed by Mike, 20201122
	//due to font and level textures cleared
/*	
//   glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set background color to black and opaque
//   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
*/
    /* select and enable texture LEVEL_TEXTURE */
	//edited by Mike, 20201122
//    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, LEVEL_TEXTURE);
    glEnable(GL_TEXTURE_2D);

	//TO-DO: -fix: column's right border 
	//column : z-axis
	//TO-DO: -fix: row's bottom border 
	//column : x-axis
	
	//note: add: randomly tile with texture

	//TO-DO: -use: light effect
	//TO-DO: -update: robotship
	//TO-DO: -update: textures	
	//TO-DO: -add: collision detection with tile blocks
	

/* //removed by Mike, 20210208	
	//added by Mike, 20201122
    //Grass
	sprintf(tempText,"G");
	//added by Mike, 20201124
    glColor3f(0.14f, 0.68f, 0.06f); // Green
 	for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {	
	 	for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {		
			//added by Mike, 20201124
			//execute this when using solid colors
			//for computer to not draw borders
			glBindTexture( GL_TEXTURE_2D, 0 );
			myLevel->draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);
		}
	}
*/
	//added by Mike, 20210320
 	//set to TOP-LEFT
//	glTranslatef(-myWindowWidth/100/2, 0.0f, -myWindowHeight/100/2);
//	glTranslatef(-myWindowWidth/2, 0.0f, -myWindowHeight/2);
	//TO-DO: -reverify: cause for use of 8	
	//removed by Mike, 20210321
//	glTranslatef(-myWindowWidth/8, 0.0f, -myWindowHeight/8);
	//updated: viewport to be 240, from 60
//	glTranslatef(-myWindowWidth/6, 0.0f, -myWindowHeight/6);
	glTranslatef(-30, 0.0f, -30);

	//myWindowWidth = 240
	//myWindowWidth/8 = 240/8 = 30
	//left-most : -74
//	glTranslatef(-20, 0.0f, -20);
//	glTranslatef(10, 0.0f, 10);

//	std::cout << "myWindowWidth: " << myWindowWidth << "\n";

	//edited by Mike, 20210305
//	myLevel->drawLevelMapInViewPort(0,0,0,fGridSquareWidth*iRowCountMax,fGridSquareWidth*iColumnCountMax,fGridSquareWidth*iHeightCountMax);
	myLevel->drawLevelMapInViewPort(myCanvasPosX,myCanvasPosY,myCanvasPosZ,fGridSquareWidth*iRowCountMax,fGridSquareWidth*iColumnCountMax,fGridSquareWidth*iHeightCountMax);

//added by Mike, 20210311
//note: computer does not draw this
	sprintf(tempText,"G");

	//added by Mike, 20201124
	glColor3f(0.14f, 0.68f, 0.06f); // Green

	//added by Mike, 20201124
	//execute this when using solid colors
	//for computer to not draw borders
	glBindTexture( GL_TEXTURE_2D, 0 );

	myLevel->draw_level(5.0f, 0.0f, -420.0f, tempText);    	

	
/* //removed by Mike, 20210309	
	//added by Mike, 20201124
    glColor3f(1.0f, 1.0f, 1.0f); // white
	glBindTexture( GL_TEXTURE_2D, LEVEL_TEXTURE );
	
	//added by Mike, 20201207
	//TO-DO: -put: all cube tiles in an array container
	
  	//edited by Mike, 20201119
	//TO-DO: -update: this
	//note: D = "Door"
//	sprintf(tempText,"D");
	//TO-DO: -update: level texture 
	sprintf(tempText,"E");
	myLevel->draw_level(0.0f, 0.0f, 0.0f, tempText);    	
	//added by Mike, 20201122
	sprintf(tempText,"E");
	myLevel->draw_level(1.0f, 0.0f, 0.0f, tempText);    	
	sprintf(tempText,"E");
	myLevel->draw_level(0.0f, 1.0f, 0.0f, tempText);    	
	//Tree
	sprintf(tempText,"F");
	myLevel->draw_level(6.0f, 0.0f, 6.0f, tempText);    	
	myLevel->draw_level(6.0f, 1.0f, 6.0f, tempText);    	
	myLevel->draw_level(6.0f, 2.0f, 6.0f, tempText);
	sprintf(tempText,"E");
	myLevel->draw_level(6.0f, 3.0f, 6.0f, tempText);    	
	myLevel->draw_level(5.0f, 3.0f, 6.0f, tempText);    	
	myLevel->draw_level(7.0f, 3.0f, 6.0f, tempText);    	
	myLevel->draw_level(6.0f, 3.0f, 7.0f, tempText);    	
	myLevel->draw_level(6.0f, 3.0f, 5.0f, tempText);    	
	myLevel->draw_level(6.0f, 3.0f, 6.0f, tempText);    	
*/

	//added by Mike, 20210323
	//TO-DO: -reverify: cause of square cube to be rectangular
	//TO-DO: -reverify: texture rotation
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glBindTexture( GL_TEXTURE_2D, LEVEL_TEXTURE );
	sprintf(tempText,"M");	
	myLevel->draw_level(fGridSquareWidth*1.0f, 0.0f, fGridSquareWidth*1.0f, tempText);    	


	//added by Mike, 20210325
	//TO-DO: -add: identification for object to draw by Level.cpp	
	//edited by Mike, 20210325	
//    glColor3f(1.0f, 1.0f, 1.0f); // white
/*	//edited by Mike, 20210330
	if ((iCountLevelM%2)==0) {
    	glColor3f(1.0f, 0.0f, 0.0f); // red
	}
	else {
    	glColor3f(1.0f, 1.0f, 1.0f); // white
	}
	iCountLevelM=iCountLevelM+1;	
*/
	iCountLevelM=(iCountLevelM+1)%2;
	if (iCountLevelM==0) {
    	glColor3f(1.0f, 0.0f, 0.0f); // red
	}
	else {
    	glColor3f(1.0f, 1.0f, 1.0f); // white
	}
	printf("iCountLevelM: %i\n",iCountLevelM);
	
	glBindTexture( GL_TEXTURE_2D, LEVEL_TEXTURE );
	sprintf(tempText,"M");	
	myLevel->draw_level(fGridSquareWidth*3.0f, 0.0f, fGridSquareWidth*3.0f, tempText);    	

	//removed by Mike, 20210402	
//    glColor3f(0.325f, 0.325f, 0.325f); // gray
	
/*
 	//columns
   	//edited by Mike, 20201015   	
    //rows   
	sprintf(tempText,"D");
 	for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {	
	 	for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {		
//			//edited by Mike, 20201120
//	    	myLevel->draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);
			//TO-DO: -update: this
			//added by Mike, 20201120	    	
//	    	if ((iColumnCount%3==0) && (iRowCount%7==0)) {
	    	if ((iColumnCount%9==0) && (iRowCount%7==0)) {
				sprintf(tempText,"E");
				myLevel->draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);	    		
			}
			else {
				sprintf(tempText,"D");
	    		myLevel->draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);
			}
		}
	}
*/

/*	
	//added by Mike, 20201120
	sprintf(tempText,"E");
	myLevel->draw_level(fGridSquareWidth*6,0.0f, fGridSquareHeight*6, tempText);
*/
	//removed by Mike, 20210210	
//	exit(0);
	
	
	//removed by Mike, 20201122
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
	
//added by Mike, 20210422	
glPushMatrix();
	
	//added by Mike, 20210420
    glColor3f(1.0f, 1.0f, 1.0f); // white
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, MIKE_TEXTURE_A);		

	glTranslatef(30.0f, 0.0f, 25.0f);
	glRotatef(180, 1.0f, 0.0f, 0.0f);

	//added by Mike, 20210422
    glScalef(1.5f, 1.5f, 1.0f);	
	
	//edited by Mike, 20210420
	//note: 3 animation frames; .tga image file has 4 frames @128x256, i.e. width x height
//	iCountTaoAnimationFrame=(iCountTaoAnimationFrame)%2;
	iCountTaoAnimationFrame=(iCountTaoAnimationFrame)%3;
	
/*
	iTaoAnimationFrameOffset=256*iCountTaoAnimationFrame;	
	int iTaoAnimationFrameWidthMax=256;
	iTaoAnimationFrameOffset=iTaoAnimationFrameOffset/iTaoAnimationFrameWidthMax;
*/
//	fTaoAnimationFrameOffset=iCountTaoAnimationFrame*0.5;
	fTaoAnimationFrameOffset=iCountTaoAnimationFrame*0.25;
	
	printf("iCountTaoAnimationFrame: %i",iCountTaoAnimationFrame);

	iCountTaoAnimationFrame=iCountTaoAnimationFrame+1;
		
	//printf("iTaoAnimationFrameOffset: %i",iTaoAnimationFrameOffset);
	
/*	
	if (iCountTaoAnimationFrame==0) {
    	glColor3f(1.0f, 0.0f, 0.0f); // red
	}
	else {
    	glColor3f(1.0f, 1.0f, 1.0f); // white
	}
*/
		
//-----	
glBegin(GL_TRIANGLES);	
	//triangle#6 //back face left part
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.0+fTaoAnimationFrameOffset,0.0);	
	glVertex3f(-1.000000,1.000000,-1.000000); //A1

	glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210420
//	glTexCoord2f(1.0+iTaoAnimationFrameOffset,1.0);
//	glTexCoord2f(0.5+fTaoAnimationFrameOffset,1.0);
	glTexCoord2f(0.25+fTaoAnimationFrameOffset,1.0);
	glVertex3f(1.000000,-1.000000,-1.000000); //B1

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.0+fTaoAnimationFrameOffset,1.0);	
	glVertex3f(-1.000000,-1.000000,-1.000000); //C1	
	

	//triangle#12 //back face right part		
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.0+fTaoAnimationFrameOffset,0.0);	
	glVertex3f(-1.000000,1.000000,-1.000000); //A2

	glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210420	
//	glTexCoord2f(1.0+iTaoAnimationFrameOffset,0.0);
//	glTexCoord2f(0.5+fTaoAnimationFrameOffset,0.0);
	glTexCoord2f(0.25+fTaoAnimationFrameOffset,0.0);
	glVertex3f(1.000000,1.000000,-1.000000); //B2

	glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210420	
//	glTexCoord2f(1.0+iTaoAnimationFrameOffset,1.0);
//	glTexCoord2f(0.5+fTaoAnimationFrameOffset,1.0);
	glTexCoord2f(0.25+fTaoAnimationFrameOffset,1.0);	
	glVertex3f(1.000000,-1.000000,-1.000000); //C2	
glEnd();
	
//-----		
/*	
//-----	
glBegin(GL_TRIANGLES);	
	//triangle#6 //back face left part
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.0,0.0);	
	glVertex3f(-1.000000,1.000000,-1.000000); //A1

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.000000,-1.000000,-1.000000); //B1

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.0,1.0);	
	glVertex3f(-1.000000,-1.000000,-1.000000); //C1	
	

	//triangle#12 //back face right part		
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.0,0.0);	
	glVertex3f(-1.000000,1.000000,-1.000000); //A2

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.000000,1.000000,-1.000000); //B2

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.000000,-1.000000,-1.000000); //C2	
glEnd();
//-----	
*/
	//added by Mike, 20210422
	glScalef(1.0f, 1.0f, 1.0f);	

	glRotatef(-180, 1.0f, 0.0f, 0.0f);
	glTranslatef(-30.0f, 0.0f, -25.0f);		

/*	//removed by Mike, 20210422
	//added by Mike, 20210422
    glScaled(1.000000, 1.000000, 1.000000);	
*/
	
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
glPopMatrix(); //added by Mike, 20210422
	
	


	
//added by Mike, 20210422
glPushMatrix();
		
	//added by Mike, 20210416
	glTranslatef(15.0f, 0.0f, 30.0f);		
	
//added by Mike, 20210418
/*    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
*/
    glColor3f(1.0f, 1.0f, 1.0f); // white
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BAHAY_TEXTURE);

	//added by Mike, 20210422
    glScalef(4.0f, 4.0f, 4.0f);	
		
//removed by Mike, 20210422
//glRotatef(fKahonRotation, 0.0f, 1.0f, 0.0f);

//added by Mike, 20210418
//TO-DO: -reverify house roof bottom quad to use only half triangle has texture, et cetera 
glBegin(GL_TRIANGLES);
	//Triangle#1-----
	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(1.004574,0.504320);
	glVertex3f(-1.000000,0.720536,-1.000000);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.498614,0.005673);
	glVertex3f(1.000000,0.720536,1.000000);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.512700,0.507912);
	glVertex3f(1.000000,0.720536,-1.000000);

	//Triangle#2-----
	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.984378,0.997785);
	glVertex3f(1.000000,0.720536,1.000000);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.502366,0.503219);
	glVertex3f(-1.000000,-0.435089,1.000000);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.502366,0.997785);
	glVertex3f(1.000000,-0.435089,1.000000);

	//Triangle#3-----
	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.984378,0.512192);
	glVertex3f(-1.000000,0.720536,1.000000);

	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.502366,0.993388);
	glVertex3f(-1.000000,-0.435089,-1.000000);

	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.502366,0.512192);
	glVertex3f(-1.000000,-0.435089,1.000000);

	//Triangle#4-----
	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.502366,0.513781);
	glVertex3f(1.000000,-0.435089,-1.000000);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.991541,0.997785);
	glVertex3f(-1.000000,-0.435089,1.000000);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.991541,0.514565);
	glVertex3f(-1.000000,-0.435089,-1.000000);

	//Triangle#5-----
	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.984378,0.513781);
	glVertex3f(1.000000,0.720536,-1.000000);

	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.502366,0.997785);
	glVertex3f(1.000000,-0.435089,1.000000);

	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.502366,0.513781);
	glVertex3f(1.000000,-0.435089,-1.000000);

	//Triangle#6-----
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.984378,0.993388);
	glVertex3f(-1.000000,0.720536,-1.000000);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.502366,0.513781);
	glVertex3f(1.000000,-0.435089,-1.000000);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.502366,0.993388);
	glVertex3f(-1.000000,-0.435089,-1.000000);

	//Triangle#7-----
	glNormal3f(0.5816,-0.8135,0.0000);
	glTexCoord2f(0.997927,0.003095);
	glVertex3f(-0.117531,1.359641,-0.985252);

	glNormal3f(0.5816,-0.8135,0.0000);
	glTexCoord2f(0.509877,0.508364);
	glVertex3f(-1.000000,0.728727,0.985252);

	glNormal3f(0.5816,-0.8135,0.0000);
	glTexCoord2f(0.498014,0.004966);
	glVertex3f(-1.000000,0.728727,-0.985252);

	//Triangle#8-----
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(1.003196,0.499632);
	glVertex3f(-0.117531,1.359641,0.985252);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.497201,0.004564);
	glVertex3f(1.000000,0.728727,0.985252);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.502513,0.499632);
	glVertex3f(-1.000000,0.728727,0.985252);

	//Triangle#9-----
	glNormal3f(-0.5816,-0.8135,0.0000);
	glTexCoord2f(0.998154,0.002951);
	glVertex3f(0.117531,1.359641,0.985252);

	glNormal3f(-0.5816,-0.8135,0.0000);
	glTexCoord2f(0.502513,0.498142);
	glVertex3f(1.000000,0.728727,-0.985252);

	glNormal3f(-0.5816,-0.8135,0.0000);
	glTexCoord2f(0.499093,0.005490);
	glVertex3f(1.000000,0.728727,0.985252);

	//Triangle#10-----
	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.501949,0.498142);
	glVertex3f(0.117531,1.359641,-0.985252);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(1.002241,0.004722);
	glVertex3f(-1.000000,0.728727,-0.985252);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(1.002241,0.498142);
	glVertex3f(1.000000,0.728727,-0.985252);

	//Triangle#11-----
	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(1.002241,0.003645);
	glVertex3f(1.000000,0.728727,0.985252);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.997816,0.498142);
	glVertex3f(-1.000000,0.728727,-0.985252);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.997816,0.003645);
	glVertex3f(-1.000000,0.728727,0.985252);

	//Triangle#12-----
	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.496913,-0.007592);
	glVertex3f(-0.117531,1.359641,0.985252);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.994448,0.501058);
	glVertex3f(0.117531,1.359641,-0.985252);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.992693,0.001452);
	glVertex3f(0.117531,1.359641,0.985252);

	//Triangle#13-----
	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(1.004574,0.504320);
	glVertex3f(-1.000000,0.720536,-1.000000);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.997203,0.001555);
	glVertex3f(-1.000000,0.720536,1.000000);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.498614,0.005673);
	glVertex3f(1.000000,0.720536,1.000000);

	//Triangle#14-----
	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.984378,0.997785);
	glVertex3f(1.000000,0.720536,1.000000);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.984378,0.503219);
	glVertex3f(-1.000000,0.720536,1.000000);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.502366,0.503219);
	glVertex3f(-1.000000,-0.435089,1.000000);

	//Triangle#15-----
	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.984378,0.512192);
	glVertex3f(-1.000000,0.720536,1.000000);

	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.984378,0.993388);
	glVertex3f(-1.000000,0.720536,-1.000000);

	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.502366,0.993388);
	glVertex3f(-1.000000,-0.435089,-1.000000);

	//Triangle#16-----
	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.502366,0.513781);
	glVertex3f(1.000000,-0.435089,-1.000000);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.502366,0.997785);
	glVertex3f(1.000000,-0.435089,1.000000);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.991541,0.997785);
	glVertex3f(-1.000000,-0.435089,1.000000);

	//Triangle#17-----
	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.984378,0.513781);
	glVertex3f(1.000000,0.720536,-1.000000);

	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.984378,0.997785);
	glVertex3f(1.000000,0.720536,1.000000);

	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.502366,0.997785);
	glVertex3f(1.000000,-0.435089,1.000000);

	//Triangle#18-----
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.984378,0.993388);
	glVertex3f(-1.000000,0.720536,-1.000000);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.984378,0.513781);
	glVertex3f(1.000000,0.720536,-1.000000);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.502366,0.513781);
	glVertex3f(1.000000,-0.435089,-1.000000);

	//Triangle#19-----
	glNormal3f(0.5816,-0.8135,0.0000);
	glTexCoord2f(0.997927,0.003095);
	glVertex3f(-0.117531,1.359641,-0.985252);

	glNormal3f(0.5816,-0.8135,0.0000);
	glTexCoord2f(0.995182,0.508364);
	glVertex3f(-0.117531,1.359641,0.985252);

	glNormal3f(0.5816,-0.8135,0.0000);
	glTexCoord2f(0.509877,0.508364);
	glVertex3f(-1.000000,0.728727,0.985252);

	//Triangle#20-----
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(1.003196,0.499632);
	glVertex3f(-0.117531,1.359641,0.985252);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.997958,0.001452);
	glVertex3f(0.117531,1.359641,0.985252);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.497201,0.004564);
	glVertex3f(1.000000,0.728727,0.985252);

	//Triangle#21-----
	glNormal3f(-0.5816,-0.8135,0.0000);
	glTexCoord2f(0.998154,0.002951);
	glVertex3f(0.117531,1.359641,0.985252);

	glNormal3f(-0.5816,-0.8135,0.0000);
	glTexCoord2f(1.003196,0.498142);
	glVertex3f(0.117531,1.359641,-0.985252);

	glNormal3f(-0.5816,-0.8135,0.0000);
	glTexCoord2f(0.502513,0.498142);
	glVertex3f(1.000000,0.728727,-0.985252);

	//Triangle#22-----
	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.501949,0.498142);
	glVertex3f(0.117531,1.359641,-0.985252);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.497606,0.005179);
	glVertex3f(-0.117531,1.359641,-0.985252);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(1.002241,0.004722);
	glVertex3f(-1.000000,0.728727,-0.985252);

	//Triangle#23-----
	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(1.002241,0.003645);
	glVertex3f(1.000000,0.728727,0.985252);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(1.002241,0.498142);
	glVertex3f(1.000000,0.728727,-0.985252);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.997816,0.498142);
	glVertex3f(-1.000000,0.728727,-0.985252);

	//Triangle#24-----
	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.496913,-0.007592);
	glVertex3f(-0.117531,1.359641,0.985252);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.497547,0.501058);
	glVertex3f(-0.117531,1.359641,-0.985252);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(0.994448,0.501058);
	glVertex3f(0.117531,1.359641,-0.985252);
glEnd();
	
	
/* //bahay v0	
glBegin(GL_TRIANGLES);
	//Triangle#1-----
	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.993468,-0.002000);
	glVertex3f(-1.000000,1.000000,-1.000000);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.493875,0.998368);
	glVertex3f(1.000000,1.000000,1.000000);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.493875,-0.002000);
	glVertex3f(1.000000,1.000000,-1.000000);

	//Triangle#2-----
	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.493875,0.998368);
	glVertex3f(1.000000,1.000000,1.000000);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(-0.005718,1.998735);
	glVertex3f(-1.000000,-1.000000,1.000000);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(-0.005718,0.998368);
	glVertex3f(1.000000,-1.000000,1.000000);

	//Triangle#3-----
	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.493875,-2.002735);
	glVertex3f(-1.000000,1.000000,1.000000);

	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(-0.005718,-1.002367);
	glVertex3f(-1.000000,-1.000000,-1.000000);

	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(-0.005718,-2.002735);
	glVertex3f(-1.000000,-1.000000,1.000000);

	//Triangle#4-----
	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(-0.005718,-0.002000);
	glVertex3f(1.000000,-1.000000,-1.000000);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(-0.505311,0.998368);
	glVertex3f(-1.000000,-1.000000,1.000000);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(-0.505311,-0.002000);
	glVertex3f(-1.000000,-1.000000,-1.000000);

	//Triangle#5-----
	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.493875,-0.002000);
	glVertex3f(1.000000,1.000000,-1.000000);

	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(-0.005718,0.998368);
	glVertex3f(1.000000,-1.000000,1.000000);

	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(-0.005718,-0.002000);
	glVertex3f(1.000000,-1.000000,-1.000000);

	//Triangle#6-----
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.493875,-1.002367);
	glVertex3f(-1.000000,1.000000,-1.000000);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(-0.005718,-0.002000);
	glVertex3f(1.000000,-1.000000,-1.000000);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(-0.005718,-1.002367);
	glVertex3f(-1.000000,-1.000000,-1.000000);

	//Triangle#7-----
	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.993468,-0.002000);
	glVertex3f(-1.000000,1.000000,-1.000000);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.993468,0.998368);
	glVertex3f(-1.000000,1.000000,1.000000);

	glNormal3f(0.0000,1.0000,0.0000);
	glTexCoord2f(0.493875,0.998368);
	glVertex3f(1.000000,1.000000,1.000000);

	//Triangle#8-----
	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.493875,0.998368);
	glVertex3f(1.000000,1.000000,1.000000);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(0.493875,1.998735);
	glVertex3f(-1.000000,1.000000,1.000000);

	glNormal3f(0.0000,0.0000,1.0000);
	glTexCoord2f(-0.005718,1.998735);
	glVertex3f(-1.000000,-1.000000,1.000000);

	//Triangle#9-----
	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.493875,-2.002735);
	glVertex3f(-1.000000,1.000000,1.000000);

	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(0.493875,-1.002367);
	glVertex3f(-1.000000,1.000000,-1.000000);

	glNormal3f(-1.0000,0.0000,0.0000);
	glTexCoord2f(-0.005718,-1.002367);
	glVertex3f(-1.000000,-1.000000,-1.000000);

	//Triangle#10-----
	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(-0.005718,-0.002000);
	glVertex3f(1.000000,-1.000000,-1.000000);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(-0.005718,0.998368);
	glVertex3f(1.000000,-1.000000,1.000000);

	glNormal3f(0.0000,-1.0000,0.0000);
	glTexCoord2f(-0.505311,0.998368);
	glVertex3f(-1.000000,-1.000000,1.000000);

	//Triangle#11-----
	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.493875,-0.002000);
	glVertex3f(1.000000,1.000000,-1.000000);

	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(0.493875,0.998368);
	glVertex3f(1.000000,1.000000,1.000000);

	glNormal3f(1.0000,0.0000,0.0000);
	glTexCoord2f(-0.005718,0.998368);
	glVertex3f(1.000000,-1.000000,1.000000);

	//Triangle#12-----
	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.493875,-1.002367);
	glVertex3f(-1.000000,1.000000,-1.000000);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(0.493875,-0.002000);
	glVertex3f(1.000000,1.000000,-1.000000);

	glNormal3f(0.0000,0.0000,-1.0000);
	glTexCoord2f(-0.005718,-0.002000);
	glVertex3f(1.000000,-1.000000,-1.000000);
glEnd();
*/

	
	glBindTexture(GL_TEXTURE_2D, 0);
glDisable(GL_TEXTURE_2D);	
	
//removed by Mike, 20210422	
//glRotatef(-fKahonRotation, 0.0f, 1.0f, 0.0f);
		
	//added by Mike, 20210422
    glScalef(1.0f, 1.0f, 1.0f);	
	
	glTranslatef(-15.0f, 0.0f, -30.0f);		

//edited by Mike, 20210416	
//fKahonRotation+=10;

	fKahonRotation+=10;
	if (fKahonRotation>=360) { //note: % operation uses integer, i.e. whole number
		fKahonRotation=0;
	}

//added by Mike, 20210422	
glPopMatrix();       	
//------	
	
	//added by Mike, 20210329
	glTranslatef(30.0f, 0.0f, 30.0f);		

	//added by Mike, 20210330
	//BASIC SHADING
	//TO-DO: -add: https://github.com/opengl-tutorials/ogl/blob/master/tutorial08_basic_shading/tutorial08.cpp;
	//last accessed: 20210330
/*	
	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("halimbawaMellow.obj", vertices, uvs, normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	//...

// 3rd attribute buffer : normals
 glEnableVertexAttribArray(2);
 glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
 glVertexAttribPointer(
     2,                                // attribute
     3,                                // size
     GL_FLOAT,                         // type
     GL_FALSE,                         // normalized?
     0,                                // stride
     (void*)0                          // array buffer offset
 );	
 

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//...
*/	

/* //removed by Mike, 20210402	
//mellow
*/
	//added by Mike, 20210402
	//kahon with texture
	
/*	//removed by Mike, 20210409	
    	glEnable(GL_TEXTURE_2D);
	//edited by Mike, 20210403
//        glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE); //concrete
        glBindTexture(GL_TEXTURE_2D, KAHON_TEXTURE); //concrete
*/
		

//added by Mike, 20210405
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
//removed by Mike, 20210422	
//	std::cout << "myWindowWidth: " << myWindowWidth;

   //removed by Mike, 20201203 to remove flicker
   //glFlush();  // Render now
}

//added by Mike, 20200930
void OpenGLCanvas::drawGrid() {
	//removed by Mike, 20201012
/*   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
*/
 
     //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();

	 //TOP-LEFT origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maximum
      	);

	//edited by Mike, 20201016
	//added by Mike, 20201002

/*	//note: set these to be isometric view
    glRotatef(40, 0.0f, 0.0f, 0.2f);
//    glTranslatef(0.45f, -0.15f, 0.0f); //10x10 grid
    glTranslatef(0.45f, -0.20f, 0.0f); //20x20 grid
//    glScalef(0.5f, 0.5f, 0.5f); //10x10 grid
    glScalef(0.3f, 0.3f, 0.3f); //20x20 grid
*/

/*
	//edited by Mike, 20201018
	//+increased: size of grid from 10x10 to 20x20
	//non-isometric view
	//edited by Mike, 20201018
//    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(0.2f, 0.2f, 0.0f); //20x20 grid
    glScalef(0.3f, 0.3f, 0.3f);
*/

/*
	//added by Mike, 20201018
	//TO-DO: -update: this
	//first-person view
    glRotatef(90.0f, 1.0f, 0.0f, 0.1f); //roll clock-wise
	//added by Mike, 20201019
	//note decrease, i.e. increase negatively, z value, to move forward
    glTranslatef(0.0f, -1.0f, -0.8f); //20x20 grid
*/

/*
	//note: set these to be isometric view
//    glRotatef(30, 0.0f, 0.0f, 0.2f);
//    glRotatef(30, 0.0f, 0.0f, 1.0f);
    glRotatef(60, 1.0f, 0.0f, 0.0f);
//    glTranslatef(0.45f, -0.15f, 0.0f); //10x10 grid
    glTranslatef(0.45f, -0.20f, 0.0f); //20x20 grid
//    glScalef(0.5f, 0.5f, 0.5f); //10x10 grid
    glScalef(0.3f, 0.3f, 0.3f); //20x20 grid
*/

//    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
//	glRotatef(15.0, 1.0, 0.0, 0.0);

//	glRotatef(60.0f, 0.0, 0.0, 1.0);
//	glRotatef(30.0f, 1.0, 0.0, 0.0);
  	glRotatef(60.0f, 1.0, 0.0, 0.0);

    glTranslatef(0.2f, 0.0f, 0.0f); //20x20 grid
      
//    glTranslatef(0.2f, 0.2f, 0.0f); //20x20 grid
//    glScalef(0.3f, 0.3f, 0.3f);


//    glTranslatef(0.0f, 0.0f, 1.0f); //20x20 grid

	//edited by Mike, 20201019
//    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//    glTranslatef(0.2f, -0.5f, -0.5f); //20x20 grid
//    glScalef(0.3f, 0.3f, 0.3f);


/*
//    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
//    glTranslatef(0.2f, -0.5f, -0.5f); //20x20 grid
//    glTranslatef(0.0f, -0.5f, -0.9f); //20x20 grid
//    glTranslatef(0.0f, -0.7f, -0.9f); //20x20 grid
//    glTranslatef(0.0f, -1.0f, -0.5f); //20x20 grid
    glTranslatef(0.0f, -1.0f, -0.8f); //20x20 grid
*/

//    glScalef(0.3f, 0.3f, 0.3f);


/*
	//use these to verify grid
    glTranslatef(0.1f, 0.1f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);
*/	
	 //draw grid
	 //edited by Mike, 20201015 	 
 	 //TO-DO: -update: iRowCountMax
// 	 int iRowCountMax=10;
 	 int iRowCountMax=20;
 	 //TO-DO: -update: iColumnCountMax
// 	 int iColumnCountMax=10;
 	 int iColumnCountMax=20;

   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
   	//edited by Mike, 20201002
 	 for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//edited by Mike, 20201015
//      		glVertex2f(1.0f, 0.1f*iRowCount);
      		glVertex2f(0.1f*iRowCountMax, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }

   //columns
   	//edited by Mike, 20201015   	
 	 for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//edited by Mike, 20201015
//      		glVertex2f(0.1f*iColumnCount, 1.0f);
      		glVertex2f(0.1f*iColumnCount, 0.1f*iColumnCountMax);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}

void OpenGLCanvas::update()
{           
    if (currentState==GAME_SCREEN) {
/*		//removed by Mike, 20201016
    	//added by Mike, 20201016
        if(numOfAsteroidsLeft<=0) {
            resetDynamicObjects();
        }
*/

    	//added by Mike, 20210206
    	myPilot->update(1); //dt
    	
    	//added by Mike, 20201001
    	myRobotShip->update(1); //dt

		//added by Mike, 20210207
		//TO-DO: -add: myRobotShip collide with Asteroid
		//TO-DO: -add: myRobotShip's punch collide with Asteroid		
		//TO-DO: -add: myRobotShip's shield collide with Asteroid		
/*        for(int a=0; a<MAX_ASTEROID; a++) {
          myBeam[i]->collideWith(myAsteroid[a]);
		}              
*/
		
		//added by Mike, 20201013
/*    	int a;
*/
		//edited by Mike, 20201014
//        for(i=0; i<MAX_BEAMS; i++) {
        for(int i=0; i<MAX_BEAMS; i++) {
          if ( (myRobotShip->getState()!=ROBOTSHIP_INITIALIZING_STATE) &&
               (myBeam[i]->isActive()) ){
			//edited by Mike, 20210322
//            myBeam[i]->update(1);
			//TO-DO: reverify: cause of myCanvasPosX, etc does not move
//            myBeam[i]->update(myCanvasPosX,myCanvasPosY,myCanvasPosZ);
            myBeam[i]->update(myRobotShip->getX(),myRobotShip->getY(),myRobotShip->getZ());

            //check collisions
            //myBeam[i]->collideWith(myEnemy);
			
			//added by Mike, 20201016
            for(int a=0; a<MAX_ASTEROID; a++) {
              myBeam[i]->collideWith(myAsteroid[a]);
			}   			  			
		  }
		}

		//added by Mike, 20201016
        for(int i=0; i<MAX_ASTEROID; i++) {
          //if (myBeam[i]->isActive())
            myAsteroid[i]->update(1);
            //removed by Mike, 20201016
//            myAsteroid[i]->collideWith(myRobotShip);       
			
			//added by Mike, 20210219  
          	if (myRobotShip->getIsExecutingPunch()) {
              myAsteroid[i]->collideWith(myRobotShip);			  
            }			
        }

       	//process input
       	//TO-DO: -update: this
       	//TO-DO: -verify: gamepad
		
		//added by Mike, 20201202
       	//verify if no keys are pressed down
       	int iKeyCount;
       	for (iKeyCount=0; iKeyCount<iNumOfKeyTypes; iKeyCount++) {
			if (myKeysDown[iKeyCount]==TRUE) {
				break;				
			}
		}

		if (iKeyCount==iNumOfKeyTypes) {
			//TO-DO: -update: this
          	myRobotShip->move(-1); //IDLE_MOVING_STATE			
		}		

       	//added by Mike, 20210111; edited by Mike, 20210121
       	//robotship; defend command
    	if(myKeysDown[KEY_H] == TRUE)
    	{
          	myRobotShip->move(KEY_H);
		}

       	//added by Mike, 20210121
       	//robotship; punch command
    	if(myKeysDown[KEY_U] == TRUE)
    	{
          	myRobotShip->move(KEY_U);
		}
		
       	//edited by Mike, 20201013; edited again by Mike, 20210128
       	//edited by Mike, 20210130
//    	if ((myKeysDown[KEY_UP] == TRUE) || (myKeysDown[KEY_W] == TRUE)) 
    	if (myKeysDown[KEY_W] == TRUE)
    	{
    		//added by Mike, 20201001
          	//myRobotShip->move(KEY_UP);

          	//edited by Mike, 20201115
          	myRobotShip->move(KEY_W);
			//removed by Mike, 20201026
/*			  myCanvasPosZ+=myCanvasStepZ;
*/

			//move forward
			//Reference: https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
			//last accessed: 20201026
			//answer by: Bob, 200002
			myCanvasPosZ-=sin(myCanvasLookAtAngle)*myCanvasStepZ;
			myCanvasPosX-=cos(myCanvasLookAtAngle)*myCanvasStepX;


			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}
       	//edited by Mike, 20201013
    	//else if(myKeysDown[KEY_DOWN] == TRUE)
    	//edited by Mike, 20201014
    	if(myKeysDown[KEY_S] == TRUE)
//    	else if(myKeysDown[KEY_S] == TRUE)
    	{
    		//edited by Mike, 20201115; edited again by Mike, 20210128
            //myRobotShip->move(KEY_DOWN);
            myRobotShip->move(KEY_S);
			
/*			//removed by Mike, 20201026
			myCanvasPosZ-=myCanvasStepZ;
*/
			//move backward
			//Reference: https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
			//last accessed: 20201026
			//answer by: Bob, 200002
			myCanvasPosZ+=sin(myCanvasLookAtAngle)*myCanvasStepZ;
			myCanvasPosX+=cos(myCanvasLookAtAngle)*myCanvasStepX;

    	}
       	//edited by Mike, 20201013
    	//else if(myKeysDown[KEY_RIGHT] == TRUE)
    	//edited by Mike, 20201014
    	//else if(myKeysDown[KEY_D] == TRUE)
//    	if(myKeysDown[KEY_D] == TRUE)
		//edited by Mike, 20210128
//    	if(myKeysDown[KEY_RIGHT] == TRUE)
		//edited by Mike, 20210129
//    	if ((myKeysDown[KEY_RIGHT] == TRUE) || (myKeysDown[KEY_D] == TRUE)) 
    	if (myKeysDown[KEY_D] == TRUE)
		{
    		//added by Mike, 20201001
    		//edited by Mike, 20201115; edited again by Mike, 20210128
//            myRobotShip->move(KEY_RIGHT);
            myRobotShip->move(KEY_D);
			
/*			//removed by Mike, 20201026
			myCanvasPosX+=-myCanvasStepX;
*/

			//move right
			//Reference: https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
			//last accessed: 20201026
			//answer by: Bob, 200002
			myCanvasPosZ-=cos(myCanvasLookAtAngle)*myCanvasStepZ;
			myCanvasPosX+=sin(myCanvasLookAtAngle)*myCanvasStepX;

			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}

//added by Mike, 20210130
//note: +reverified due to sequence if-then instructions causes RobotShip to not execute rapid fire down with move up-left, etc
//using Windows Machine
//verified: problem does not occur using Linux Machine (with external USB keyboard)
//added by Mike, 20210131
//note: add use of external USB keyboard solves the problem		  

       	//edited by Mike, 20201013
    	//else if(myKeysDown[KEY_LEFT] == TRUE)
    	//edited by Mike, 20201014
    	//else if(myKeysDown[KEY_A] == TRUE)
    	if(myKeysDown[KEY_A] == TRUE)
    	{
    		//added by Mike, 20201001
    		//edited by Mike, 20201115
    		//edited by Mike, 20210129
//            myRobotShip->move(KEY_LEFT);
            myRobotShip->move(KEY_A);

			//removed by Mike, 20201026
/////			myCanvasPosX+=myCanvasStepX;
			
			//move left
			//Reference: https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
			//last accessed: 20201026
			//answer by: Bob, 200002
			myCanvasPosZ+=cos(myCanvasLookAtAngle)*myCanvasStepZ;
			myCanvasPosX-=sin(myCanvasLookAtAngle)*myCanvasStepX;

			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}    	
    	
    	//TO-DO: -update: to execute diagonal beams
		//TO-DO: -reverify: rotation angle

		//TO-DO: -reverify beam start position during firing

		//added by Mike, 20210207
//note: add this diagonal set of instructions first
		//diagonal weapon attack
		if ((myKeysDown[KEY_I]==TRUE) && (myKeysDown[KEY_L]))
    	{
			//edited by Mike, 20201013
			static int i = 0;

			//added by Mike, 20210112
			if (!myRobotShip->getIsExecuteWithWeaponReady()) {
				return;
			}
			
			//edited by Mike, 20201218
            //myRobotShip->move(KEY_LEFT);
            myRobotShip->move(KEY_I);

    		//edited by Mike, 20210207
			//myRobotShip->setCurrentFacingState(FACING_UP);
			myRobotShip->setCurrentFacingState(FACING_RIGHT_AND_UP);
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				//UP
//				rotationAngle=180;
				//RIGHT AND UP
//				rotationAngle=135; //LEFT AND UP
				rotationAngle=225;

				//added by Mike, 20210112
				float *beamPosXyz = {myRobotShip->getXYZPos()};
//				float *beamPosXyz[3] = {myRobotShip->getXYZPos()};
//edited by Mike, 20210207	
//				beamPosXyz[0]+=2.0f; //center
//				beamPosXyz[0]+=0.0f; //left arm 
				beamPosXyz[0]+=4.0f; //right arm 

				if (i%2==0) {
                	myBeam[i]->move(rotationAngle+4, beamPosXyz);
				}
				else {
                	myBeam[i]->move(rotationAngle, beamPosXyz);					
				}

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}
		
		//added by Mike, 20210207
		//LEFT AND UP keys
		if ((myKeysDown[KEY_I]==TRUE) && (myKeysDown[KEY_J]))
    	{
			//edited by Mike, 20201013
			static int i = 0;

			//added by Mike, 20210112
			if (!myRobotShip->getIsExecuteWithWeaponReady()) {
				return;
			}
			
			//edited by Mike, 20201218
            //myRobotShip->move(KEY_LEFT);
            myRobotShip->move(KEY_I);

    		//edited by Mike, 20210207
			//myRobotShip->setCurrentFacingState(FACING_UP);
			myRobotShip->setCurrentFacingState(FACING_LEFT_AND_UP);
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				//UP
//				rotationAngle=180;
				//RIGHT AND UP
				rotationAngle=135; //LEFT AND UP
//				rotationAngle=225; //RIGHT AND UP

				//added by Mike, 20210112
				float *beamPosXyz = {myRobotShip->getXYZPos()};
//				float *beamPosXyz[3] = {myRobotShip->getXYZPos()};
//edited by Mike, 20210207	
//				beamPosXyz[0]+=2.0f; //center
//				beamPosXyz[0]+=0.0f; //left arm 
//				beamPosXyz[0]+=4.0f; //right arm 
				beamPosXyz[0]+=1.0f; //right arm 

				if (i%2==0) {
                	myBeam[i]->move(rotationAngle+4, beamPosXyz);
				}
				else {
                	myBeam[i]->move(rotationAngle, beamPosXyz);					
				}

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}

		//added by Mike, 20210207
		//LEFT AND DOWN keys
		if ((myKeysDown[KEY_J]) && (myKeysDown[KEY_K]==TRUE))
    	{
			//edited by Mike, 20201013
			static int i = 0;

			//added by Mike, 20210112
			if (!myRobotShip->getIsExecuteWithWeaponReady()) {
				return;
			}
			
			//edited by Mike, 20201218
            //myRobotShip->move(KEY_LEFT);
            myRobotShip->move(KEY_I);

    		//edited by Mike, 20210207
			//myRobotShip->setCurrentFacingState(FACING_UP);
			myRobotShip->setCurrentFacingState(FACING_LEFT_AND_DOWN);
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				//UP
//				rotationAngle=180;
				//RIGHT AND UP
//				rotationAngle=135; //LEFT AND UP
//				rotationAngle=225; //RIGHT AND UP
				rotationAngle=45; //LEFT AND DOWN


				//added by Mike, 20210112
				float *beamPosXyz = {myRobotShip->getXYZPos()};
//				float *beamPosXyz[3] = {myRobotShip->getXYZPos()};
//edited by Mike, 20210207	
//				beamPosXyz[0]+=2.0f; //center
//				beamPosXyz[0]+=0.0f; //left arm 
//				beamPosXyz[0]+=4.0f; //right arm 
//removed by Mike, 20210207
//				beamPosXyz[0]+=1.0f; //right arm 

				if (i%2==0) {
                	myBeam[i]->move(rotationAngle+4, beamPosXyz);
				}
				else {
                	myBeam[i]->move(rotationAngle, beamPosXyz);					
				}

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}

		//added by Mike, 20210207
		//RIGHT AND DOWN keys
		if ((myKeysDown[KEY_L]) && (myKeysDown[KEY_K]==TRUE))
    	{
			//edited by Mike, 20201013
			static int i = 0;

			//added by Mike, 20210112
			if (!myRobotShip->getIsExecuteWithWeaponReady()) {
				return;
			}
			
			//edited by Mike, 20201218
            //myRobotShip->move(KEY_LEFT);
            myRobotShip->move(KEY_I);

    		//edited by Mike, 20210207
			//myRobotShip->setCurrentFacingState(FACING_UP);
			myRobotShip->setCurrentFacingState(FACING_RIGHT_AND_DOWN);
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				//UP
//				rotationAngle=180;
				//RIGHT AND UP
//				rotationAngle=135; //LEFT AND UP
//				rotationAngle=225; //RIGHT AND UP
//				rotationAngle=45; //LEFT AND DOWN
				rotationAngle=-45; //RIGHT AND DOWN

				//added by Mike, 20210112
				float *beamPosXyz = {myRobotShip->getXYZPos()};
//				float *beamPosXyz[3] = {myRobotShip->getXYZPos()};
//edited by Mike, 20210207	
//				beamPosXyz[0]+=2.0f; //center
//				beamPosXyz[0]+=0.0f; //left arm 
//				beamPosXyz[0]+=4.0f; //right arm 
//				beamPosXyz[0]-=1.0f; //right arm 
				beamPosXyz[2]+=2.0f; //right arm 

				if (i%2==0) {
                	myBeam[i]->move(rotationAngle+4, beamPosXyz);
				}
				else {
                	myBeam[i]->move(rotationAngle, beamPosXyz);					
				}

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}

    	
		//edited by Mike, 20210102
    	if(myKeysDown[KEY_J] == TRUE)
    	{
			//edited by Mike, 20201013
			static int i = 0;
			
			
			//added by Mike, 20210112
			if (!myRobotShip->getIsExecuteWithWeaponReady()) {
				return;
			}
			
			//edited by Mike, 20201218
            //myRobotShip->move(KEY_LEFT);
            //TO-DO: -update: this; we use KEY_I for now
            //myRobotShip->move(KEY_J);
            myRobotShip->move(KEY_I);
    		myRobotShip->setCurrentFacingState(FACING_LEFT); //added by Mike, 20210102
						
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				//LEFT
				rotationAngle=90;

				//added by Mike, 20210112
				float *beamPosXyz = {myRobotShip->getXYZPos()};
//				float beamPosXyz[3] = myRobotShip->getXYZPos();

				//edited by Mike, 20201225
//              myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());
				//note: when held, beam particles move in waves
				//note: move beams based on direction where robot faces 
				if (i%2==0) {
//                	myBeam[i]->move(rotationAngle+4, myRobotShip->getXYZPos());
                	myBeam[i]->move(rotationAngle+4, beamPosXyz);
				}
				else {
//                	myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());					
                	myBeam[i]->move(rotationAngle, beamPosXyz);					
				}

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
		}

    	//edited by Mike, 20201015
//    	else if(myKeysDown[KEY_L] == TRUE)
		//edited by Mike, 20210102
    	if(myKeysDown[KEY_L] == TRUE)
    	{
			//edited by Mike, 20201013
			static int i = 0;

			//added by Mike, 20210112
			if (!myRobotShip->getIsExecuteWithWeaponReady()) {
				return;
			}
			
			//edited by Mike, 20201218
            //myRobotShip->move(KEY_LEFT);
            //TO-DO: -update: this; we use KEY_I for now
            //myRobotShip->move(KEY_J);
            myRobotShip->move(KEY_I);
    		myRobotShip->setCurrentFacingState(FACING_RIGHT);  //added by Mike, 20210102
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {

				//RIGHT
				rotationAngle=-90;
				
				//added by Mike, 20210112
				float *beamPosXyz = {myRobotShip->getXYZPos()};
//				float *beamPosXyz[3] = {myRobotShip->getXYZPos()};
				//edited by Mike, 20210118
//				beamPosXyz[2]+=2.0f;
				beamPosXyz[2]+=1.5f;

				if (i%2==0) {
                	myBeam[i]->move(rotationAngle+4, beamPosXyz);
				}
				else {
                	myBeam[i]->move(rotationAngle, beamPosXyz);					
				}

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
		}

		//edited by Mike, 20201015
//    	else if(myKeysDown[KEY_I] == TRUE)
    	if(myKeysDown[KEY_I] == TRUE)
    	{
			//edited by Mike, 20201013
			static int i = 0;

			//added by Mike, 20210112
			if (!myRobotShip->getIsExecuteWithWeaponReady()) {
				return;
			}
			
			//edited by Mike, 20201218
            //myRobotShip->move(KEY_LEFT);
            myRobotShip->move(KEY_I);
    		myRobotShip->setCurrentFacingState(FACING_UP);
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				//UP
				rotationAngle=180;

				//added by Mike, 20210112
				float *beamPosXyz = {myRobotShip->getXYZPos()};
//				float *beamPosXyz[3] = {myRobotShip->getXYZPos()};
				beamPosXyz[0]+=2.0f;

				//edited by Mike, 20201225
//              myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());
				//note: when held, beam particles move in waves
				//note: move beams based on direction where robot faces 
				if (i%2==0) {
//                	myBeam[i]->move(rotationAngle+4, myRobotShip->getXYZPos());
                	myBeam[i]->move(rotationAngle+4, beamPosXyz);
				}
				else {
//                	myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());					
                	myBeam[i]->move(rotationAngle, beamPosXyz);					
				}

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}

		//edited by Mike, 20201015
//    	else if(myKeysDown[KEY_K] == TRUE)
		//edited by Mike, 20210102
    	if(myKeysDown[KEY_K] == TRUE)
    	{
			//edited by Mike, 20201013
			static int i = 0;

			//added by Mike, 20210112
			if (!myRobotShip->getIsExecuteWithWeaponReady()) {
				return;
			}
			
			//edited by Mike, 20201218
            //myRobotShip->move(KEY_LEFT);
            myRobotShip->move(KEY_I);
    		myRobotShip->setCurrentFacingState(FACING_DOWN);
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				  //edited by Mike, 20201013
//                myBeam[i]->move(myRobotShip->getRotationAngle(), myRobotShip->getXYZPos());
				
				//TO-DO: -update: to immediately move a beam if only single press, i.e. not held
				//TO-DO: -update: to move beam in curve

				//DOWN
				rotationAngle=0;

				//added by Mike, 20210112
				//TO-DO: -reverify: if causes memory leak problem
				float *beamPosXyz = {myRobotShip->getXYZPos()};
//				float *beamPosXyz[3] = {myRobotShip->getXYZPos()};

				//edited by Mike, 20201225
//              myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());
				//note: when held, beam particles move in waves
				//note: move beams based on direction where robot faces 
				if (i%2==0) {
//                	myBeam[i]->move(rotationAngle+4, myRobotShip->getXYZPos());
                	myBeam[i]->move(rotationAngle+4, beamPosXyz);
				}
				else {
//                	myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());					
                	myBeam[i]->move(rotationAngle, beamPosXyz);					
				}

//		        sound->play_sound_clip(beam);
                return;
              }
            }
    	}



     }
     else if (currentState==TITLE_SCREEN)
     {
     }
     else if (currentState==CONTROLS_SCREEN)
     {
     }
     else if (currentState==HIGHSCORE_SCREEN)
     {
     }
     else if (currentState==GAMEOVER_SCREEN)
     {
/*		//removed by Mike, 20200929		 
		if(myKeysDown[KEY_SPACE] == TRUE)
		{
		  gameReset();
		}
*/		
     }
}

void OpenGLCanvas::gameReset(){
/*	//removed by Mike, 20200929
    score=0;
    scoreBeforeBonus=0;
    myRobotShip->reset();
    rest=MAX_LIFE;
    resetDynamicObjects();
    changeState(GAME_SCREEN);
*/	
}

void OpenGLCanvas::resetDynamicObjects(){
/*	//removed by Mike, 20200929
    myAsteroid[0]->reset(15,15); //TOP RIGHT
    myAsteroid[1]->reset(-15,15); //TOP LEFT
    myAsteroid[2]->reset(-15,-15); //BOTTOM LEFT
    myAsteroid[3]->reset(15,-15); //BOTTOM RIGHT
    for (i=4; i<12; i++) {   
      myAsteroid[i]->changeState(CHILD_STATUS);
      myAsteroid[i]->setCollidable(false);
    }
    for (i=12; i<MAX_ASTEROID; i++) {   
      myAsteroid[i]->changeState(GRANDCHILD_STATUS);
      myAsteroid[i]->setCollidable(false);
    }
    //for (i=0; i<MAX_ASTEROID; i++)   
    numOfAsteroidsLeft=MAX_ASTEROID;
    
    for (i=0; i<MAX_BEAMS; i++)
      myBeam[i]->changeState(HIDDEN_STATE);
*/  
}

void OpenGLCanvas::addScore(int s)
{
/*	//removed by Mike, 20200929
     score+=s;
     scoreBeforeBonus+=s;
     if (scoreBeforeBonus>=REQUIRED_POINTS_FOR_BONUS) {
       sound->play_sound_clip(bonus);
       rest++;
       scoreBeforeBonus-=REQUIRED_POINTS_FOR_BONUS;
     }
     numOfAsteroidsLeft--;
*/	 
}
void OpenGLCanvas::loseLife()
{
/*	//removed by Mike, 20200929
     rest-=1;
     if (rest==0) {
        if(score>highScore)
        {
          //save score in a text file
          highScore=score;
       	  out = fopen(outfile, "w");
          fprintf(out,"%d",highScore);
          fclose(out);
          changeState(HIGHSCORE_SCREEN);
          sound->play_sound_clip(title);
        }     
        else changeState(GAMEOVER_SCREEN);
     }
*/
}
void OpenGLCanvas::changeState(int s)
{
  currentState=s;                  
}

//added by Mike, 20210412
void OpenGLCanvas::drawKahonWithTextureForVerification() {	
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, KAHON_TEXTURE);

	
	//added by Mike, 20210408
	//TO-DO: -reverify: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-9-vbo-indexing/
	//displayed output using 3D object from Blender3D (version 2.82)
	//set with 2 triangles to create quad not yet identified 
	
	//output from Blender3D  2.82

	//added by Mike, 20210408
	//note: if we use GL_QUADS, computer draws only 1 triangle, instead of 2 for a set of quad
	//TO-DO: -reverify: texture coordinates for a set with 2 triangles

	//added by Mike, 20210409
	//note: texture coordinates anchor bottom-left
	//ship controls to fire beams, inverted x and z-axes 

	//added by Mike, 20210410
	//cube's bottom face; image texture, i.e. imageSpriteExampleMikeWithoutBG.tga
	//facing to the right, i.e. rotated +90degrees

	//glBegin(GL_QUADS);
	glBegin(GL_TRIANGLES);
	/*
	//triangle#1 //top face right part
		glNormal3f(0.0000,1.0000,0.0000);
		glTexCoord2f(0.875000,0.500000);
		glVertex3f(-1.000000,1.000000,-1.000000);

		glNormal3f(0.0000,1.0000,0.0000);
		glTexCoord2f(0.625000,0.750000);
		glVertex3f(1.000000,1.000000,1.000000);

		glNormal3f(0.0000,1.0000,0.0000);
		glTexCoord2f(0.625000,0.500000);
		glVertex3f(1.000000,1.000000,-1.000000);

	//triangle#2 //front face right part
		glNormal3f(0.0000,0.0000,1.0000);
		glTexCoord2f(0.625000,0.750000);
		glVertex3f(1.000000,1.000000,1.000000);

		glNormal3f(0.0000,0.0000,1.0000);
		glTexCoord2f(0.375000,1.000000);
		glVertex3f(-1.000000,-1.000000,1.000000);

		glNormal3f(0.0000,0.0000,1.0000);
		glTexCoord2f(0.375000,0.750000);
		glVertex3f(1.000000,-1.000000,1.000000);

	//triangle#3 //left face bottom part
		glNormal3f(-1.0000,0.0000,0.0000);
		glTexCoord2f(0.625000,0.000000);
		glVertex3f(-1.000000,1.000000,1.000000);

		glNormal3f(-1.0000,0.0000,0.0000);
		glTexCoord2f(0.375000,0.250000);
		glVertex3f(-1.000000,-1.000000,-1.000000);

		glNormal3f(-1.0000,0.0000,0.0000);
		glTexCoord2f(0.375000,0.000000);
		glVertex3f(-1.000000,-1.000000,1.000000);
	*/
	//triangle#4 //bottom face left part	
		glNormal3f(0.0000,-1.0000,0.0000);
		//edited by Mike, 20210410
	//	glTexCoord2f(0.375000,0.500000);
		glTexCoord2f(0.0,0.0);		
		glVertex3f(1.000000,-1.000000,-1.000000);

		glNormal3f(0.0000,-1.0000,0.0000);
		//edited by Mike, 20210410	
	//	glTexCoord2f(0.125000,0.750000);
		glTexCoord2f(1.0,1.0);	
		glVertex3f(-1.000000,-1.000000,1.000000);

		glNormal3f(0.0000,-1.0000,0.0000);
		//edited by Mike, 20210410	
	//	glTexCoord2f(0.125000,0.500000);
		glTexCoord2f(0.0,1.0);	
		glVertex3f(-1.000000,-1.000000,-1.000000);
	/*
	//triangle#5 //right face bottom part
		glNormal3f(1.0000,0.0000,0.0000);
		glTexCoord2f(0.625000,0.500000);
		glVertex3f(1.000000,1.000000,-1.000000);

		glNormal3f(1.0000,0.0000,0.0000);
		glTexCoord2f(0.375000,0.750000);
		glVertex3f(1.000000,-1.000000,1.000000);

		glNormal3f(1.0000,0.0000,0.0000);
		glTexCoord2f(0.375000,0.500000);
		glVertex3f(1.000000,-1.000000,-1.000000);

	//triangle#6 //back face left part
	//blender output texture coordinates; origin/anchor bottom-left; counter-clockwise
		//note: glRotatef(180, 1.0f, 0.0f, 0.0f);
		//now anchor top-left
		//clockwise

		glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210409	
	//	glTexCoord2f(0.625000,0.250000);
		glTexCoord2f(0.0,0.0);	
		glVertex3f(-1.000000,1.000000,-1.000000); //A1

		glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210409	
	//	glTexCoord2f(0.375000,0.500000);
		glTexCoord2f(1.0,1.0);
		glVertex3f(1.000000,-1.000000,-1.000000); //B1

		glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210409	
	//	glTexCoord2f(0.375000,0.250000);
		glTexCoord2f(0.0,1.0);	
		glVertex3f(-1.000000,-1.000000,-1.000000); //C1


	//triangle#7 //top face left part
		glNormal3f(0.0000,1.0000,0.0000);
		glTexCoord2f(0.875000,0.500000);
		glVertex3f(-1.000000,1.000000,-1.000000);

		glNormal3f(0.0000,1.0000,0.0000);
		glTexCoord2f(0.875000,0.750000);
		glVertex3f(-1.000000,1.000000,1.000000);

		glNormal3f(0.0000,1.0000,0.0000);
		glTexCoord2f(0.625000,0.750000);
		glVertex3f(1.000000,1.000000,1.000000);

	//triangle#8 //front face left part
		glNormal3f(0.0000,0.0000,1.0000);
		glTexCoord2f(0.625000,0.750000);
		glVertex3f(1.000000,1.000000,1.000000);

		glNormal3f(0.0000,0.0000,1.0000);
		glTexCoord2f(0.625000,1.000000);
		glVertex3f(-1.000000,1.000000,1.000000);

		glNormal3f(0.0000,0.0000,1.0000);
		glTexCoord2f(0.375000,1.000000);
		glVertex3f(-1.000000,-1.000000,1.000000);

	//triangle#9 //left face top part
		glNormal3f(-1.0000,0.0000,0.0000);
		glTexCoord2f(0.625000,0.000000);
		glVertex3f(-1.000000,1.000000,1.000000);

		glNormal3f(-1.0000,0.0000,0.0000);
		glTexCoord2f(0.625000,0.250000);
		glVertex3f(-1.000000,1.000000,-1.000000);

		glNormal3f(-1.0000,0.0000,0.0000);
		glTexCoord2f(0.375000,0.250000);
		glVertex3f(-1.000000,-1.000000,-1.000000);
	*/		
	//triangle#10 //bottom face right part
		glNormal3f(0.0000,-1.0000,0.0000);
		//edited by Mike, 20210410		
	//	glTexCoord2f(0.375000,0.500000);
		glTexCoord2f(0.0,0.0);		
		glVertex3f(1.000000,-1.000000,-1.000000);

		glNormal3f(0.0000,-1.0000,0.0000);
		//edited by Mike, 20210410		
	//	glTexCoord2f(0.375000,0.750000);
		glTexCoord2f(1.0,0.0);	
		glVertex3f(1.000000,-1.000000,1.000000);

		glNormal3f(0.0000,-1.0000,0.0000);
		//edited by Mike, 20210410		
	//	glTexCoord2f(0.125000,0.750000);
		glTexCoord2f(1.0,1.0);	
		glVertex3f(-1.000000,-1.000000,1.000000);

	/*
	//triangle#11 //right face top part
		glNormal3f(1.0000,0.0000,0.0000);
		glTexCoord2f(0.625000,0.500000);
		glVertex3f(1.000000,1.000000,-1.000000);

		glNormal3f(1.0000,0.0000,0.0000);
		glTexCoord2f(0.625000,0.750000);
		glVertex3f(1.000000,1.000000,1.000000);

		glNormal3f(1.0000,0.0000,0.0000);
		glTexCoord2f(0.375000,0.750000);
		glVertex3f(1.000000,-1.000000,1.000000);
	*/
	/*	
	//triangle#12 //back face right part	
	//blender output texture coordinates; origin/anchor bottom-left; counter-clockwise
		//note: glRotatef(180, 1.0f, 0.0f, 0.0f);
		//now anchor top-left
		//clockwise

		glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210409		
	//	glTexCoord2f(0.625000,0.250000);
		glTexCoord2f(0.0,0.0);	
		glVertex3f(-1.000000,1.000000,-1.000000); //A2

		glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210409		
	//	glTexCoord2f(0.625000,0.500000);
		glTexCoord2f(1.0,0.0);
	//	glTexCoord2f(1.0,1.0);
		glVertex3f(1.000000,1.000000,-1.000000); //B2

		glNormal3f(0.0000,0.0000,-1.0000);
	//edited by Mike, 20210409		
	//	glTexCoord2f(0.375000,0.500000);
		glTexCoord2f(1.0,1.0);
	//	glTexCoord2f(1.0,0.0);	
		glVertex3f(1.000000,-1.000000,-1.000000); //C2
	*/

	glEnd();
	
}
