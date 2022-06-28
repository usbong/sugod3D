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
 * @date updated: 20220628; from 20210130
 * @website address: http://www.usbong.ph
 *
 * References:
 * 1) Dev-C++ 5.11 auto-generated OpenGL example project
 *
 * 2) https://www.libsdl.org/download-2.0.php;
 * last accessed: 20200423
 *
 * 3) https://docs.microsoft.com/en-us/windows/win32/inputdev/user-input3
 * last accessed: 20200424
 *
 * 4) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL Game Programming". USA: Premier Press.
 *
 * 5) https://en.wikibooks.org/wiki/OpenGL_Programming/Basics/Structure
 * last accessed: 20200926
 *
 * 6) https://dos.gamebub.com/cpp.php
 * last accessed: 20200921
 *
 * 7) https://chortle.ccsu.edu/Bloodshed/howToGL.html
 * last accessed: 20200927
 * --> instructions to add GLUT library in Dev-C++ Editor 5.11
 *
 * 8) https://stackoverflow.com/questions/5289284/compiling-and-runnin-opengl-glut-program-in-ubuntu-10-10
 * --> last accessed: 20200928
 *
 * 9) https://askubuntu.com/questions/96087/how-to-install-opengl-glut-libraries
 * --> last accessed: 20200928
 *
 * 10) https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html
 * --> last accessed: 20200928
 * 
 * 11) https://stackoverflow.com/questions/2571402/how-to-use-glortho-in-opengl/36046924#36046924;
 * --> last accessed: 20200928
 * --> answers by: Mikepote, 20100408T1912
 * --> answers by: Santilli, Ciro, 20160316T2106
 *
 * 
 * Notes:
 * 1) We can use this software tool to extract the compressed (zipped) folder.
 *   https://www.7-zip.org/download.html; last accessed: 20200423
 *
 * 2) OpenGL (Open Graphics Library) Utility Toolkit Library
 *
 * 3) Linux Machine
 * 3.1) Compile Command
 *   g++ main.cpp -o mainOutput -lGL -lGLU -lglut
 *
 * 3.2) Execute Command
 *   ./mainOutput
 *
 * 3.3) Install OpenGL Libraries
 *   sudo apt-get install mesa-utils
 *
 * 3.4) Install GLUT Library
 *   sudo apt-get install freeglut3-dev
 */


/**************************
 * Includes
 *
 **************************/

/* //edited by Mike, 20201210
//#include <windows.h> //removed by Mike, 20200928 due to Linux Machine
#include <GL/gl.h>
#include <GL/glut.h> //added by Mike, 20200927
#include <GL/glu.h> //added by Mike, 20200926
*/
	
//added by Mike, 20201209
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

//added by Mike, 20201209
#if defined(__APPLE__)
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #include <GLUT/glut.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glut.h>
#endif

//added by Mike, 20200930
#include "OpenGLCanvas.h"

//added by Mike, 20201210
#include <time.h>
#include <unistd.h>

//added by Mike, 20201002
#include <iostream>

/**************************
 * Function Declarations
 *
 **************************/
/*
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);
*/

/* //removed by Mike, 20210130
//added by Mike, 20201002
#define VK_UP 101
#define VK_DOWN 103
#define VK_LEFT 100
#define VK_RIGHT 102
*/
	
//note: "static" in C/C++ = "final" in java
/*	//edited by Mike, 20201202
static int myWindowWidth=1024;//640; //320
static int myWindowHeight=1024;//640; //320
*/
static int myWindowWidth=640; //2048;//320
static int myWindowHeight=640; //2048;//320

//added by Mike, 20201001
OpenGLCanvas *myOpenGLCanvas = NULL;

//added by Mike, 20201121
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
	//added by Mike, 20210123
	KEY_H,
	KEY_U,

	iNumOfKeyTypes	
};

//added by Mike, 20201001; edited by Mike, 20201210
bool bMyPause;

//Reference: https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html;
//last accessed: 20200928
void displayExample() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.5f, -0.5f);    // x, y
      glVertex2f( 0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f(-0.5f,  0.5f);
   glEnd();
 
   glFlush();  // Render now
}

//added by Mike, 20200928; edited by Mike, 20201202
void display() { //Linux Machine
//void display(HDC hDC) { //Windows Machine
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
   
   //edited by Mike, 20201202
   //glFlush();  // Render now
   glutSwapBuffers();
}

//added by Mike, 20200930
void displayOpenGLCanvas() {
	 //removed by Mike, 20200930	 
	 //Linux Machine
/*    myOpenGLCanvas = new OpenGLCanvas;
    myOpenGLCanvas->init();
*/

	//added by Mike, 20201001
    //init stuff for delay
    int skip=0, currSysTime=0,
        timeElapsed,
		//edited by Mike, 20201205
		//TO-DO: -update: this
        idealFrameTime=33;//60;//33;
	//edited by Mike, 20201210
    //pause=false;//0;
	bMyPause=false;	 
	
//		if (!pause) {
		if (!bMyPause) {
			//TO-DO: -add: this
					//removed by Mike, 20201002					
          //currSysTime=GetTickCount(); //Windows Machine

/* //edited by Mike, 20201210			
		  //added by Mike, 20201210
		  //time_t now = time(0); //Get the system time
		  //printf("time now: %d",(int)now);
		  currSysTime = (int) time(0); //Linux Machine
*/
	
          /* OpenGL animation code goes here */
          myOpenGLCanvas->update();
		  
/*		  //edited by Mike, 20201210
          if (skip > 0)
              skip = skip-1;
          else {
*/          
                //do rendering here 
                myOpenGLCanvas->render();
                //removed by Mike, 20201002
                //SwapBuffers (hDC); //Windows Machine
				//edited by Mike, 20201205
//   							glFlush();  // Render now //Linux Machine
			   glutSwapBuffers();
			   
			    //edited by Mike, 20201210
/*
			  	//TO-DO: -add: auto-identify if Windows Machine
                //timeElapsed=GetTickCount()-currSysTime;
			    timeElapsed=(int)time(0)-currSysTime; //Linux Machine
			
			  
                if (timeElapsed>idealFrameTime) {
                  skip = (timeElapsed/idealFrameTime) - 1;
				}
                else {
                  sleep(idealFrameTime - timeElapsed);
                  //pause(idealFrameTime - timeElapsed);
				}			  
          }
*/                  
		  //added by Mike, 20201002
//			glutPostRedisplay();
			
			//reference: https://stackoverflow.com/questions/35563360/looping-in-opengl-with-gluttimerfunc;
			//answer by: spookyPuppy, 20160223T0445
			//edited by: datenwolf, 20160223T0631			
			//note: void glutTimerFunc(unsigned int numMilliseconds, functionCallback, value);
			//glutTimerFunc(1000 / SCREEN_FPS, Loop, 0);
//			glutTimerFunc(1000, NULL, 0);

		}	 
}

//added by Mike, 20200930
void update(int i) {
	 //removed by Mike, 20200930	 
	 //Linux Machine
/*    myOpenGLCanvas = new OpenGLCanvas;
    myOpenGLCanvas->init();
*/

	//added by Mike, 20201001
    //init stuff for delay
    int skip=0, currSysTime=0,
        timeElapsed,
        idealFrameTime=60;//33;
	//edited by Mike, 20201210
//    pause=false;//0;
    bMyPause=false;//0;
	
	
		//edited by Mike, 20201210	 
//		if (!pause) {
		if (!bMyPause) {			
					//removed by Mike, 20201002					
          //currSysTime=GetTickCount(); //Linux Machine

          /* OpenGL animation code goes here */
          myOpenGLCanvas->update();
/*				//removed by Mike, 20201002, Linux Machine
          if (skip > 0)
              skip = skip-1;
          else {
*/          

/*							//removed by Mike, 20201002, Linux Machine                
                timeElapsed=GetTickCount()-currSysTime;
                if (timeElapsed>idealFrameTime)
                  skip = (timeElapsed/idealFrameTime) - 1;
                else 
                  Sleep(idealFrameTime - timeElapsed);
          }
*/                  
		  //added by Mike, 20201002
			glutPostRedisplay();
			
			//TO-DO: -add: auto-identify if Windows Machine
			//reference: https://stackoverflow.com/questions/35563360/looping-in-opengl-with-gluttimerfunc;
			//answer by: spookyPuppy, 20160223T0445
			//edited by: datenwolf, 20160223T0631			
			//note: void glutTimerFunc(unsigned int numMilliseconds, functionCallback, value);
			//glutTimerFunc(1000 / SCREEN_FPS, Loop, 0);
			//edited by Mike, 20201202
//			glutTimerFunc(50, update, 0);
			//edited by Mike, 20201210
//			glutTimerFunc(70, update, 0);
//			glutTimerFunc(80, update, 0);
			//edited by Mike, 20210115
			//TO-DO: -reverify: add RobotShip movement animation delay
			//using lower canvas auto-draw update delay
			//glutTimerFunc(40, update, 0);
			glutTimerFunc(50, update, 0);

		}	 
}



//note: special functions, e.g. character keys
//added by Mike, 20201002
void keyDown (unsigned char key, int x, int y)
{
	//note: space bar and escape keys detected, albeit blank output 
//    std::cout << "keydown " << key << "\n";

	//added by Mike, 20201121
	switch (key)
    {
/*			   //removed by Mike, 20201121
			   //TO-DO: -add: identify VK_SPACE in Linux Machine
			case VK_SPACE:
                myOpenGLCanvas->keyDown(KEY_SPACE);
                return;
*/				
			
           //added by Mike, 20201013
           //reference: 
           //https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
           //last accessed: 20201013
			//TO-DO: -add: auto-identify if Linux Machine
			//edited by Mike, 20201121
//   	       case 0x41: //A key //Windows Machine
   	       case (int) 'a': //A key //Linux Machine
				myOpenGLCanvas->keyDown(KEY_A);
                return;     
			//edited by Mike, 20201121			
//   	       case 0x44: //D key //Windows Machine
   	       case (int) 'd': //d key //Linux Machine
				//edited by Mike, 20210128
		        myOpenGLCanvas->keyDown(KEY_D);
//		        myOpenGLCanvas->keyDown(KEY_RIGHT);
                return;
			//edited by Mike, 20201121
//		   case 0x57: //W key //Windows Machine
   	       case (int) 'w': //w key //Linux Machine			
//   	       case 0x41: //W key
//			case VK_UP:
				//edited by Mike, 20210128
//		        myOpenGLCanvas->keyDown(KEY_UP);//KEY_W);
		        myOpenGLCanvas->keyDown(KEY_W);
                return;
			//edited by Mike, 20201121
//		   case 0x53: //S key //Windows Machine
   	       case (int) 's': //s key //Linux Machine			
				myOpenGLCanvas->keyDown(KEY_S);
//		        myOpenGLCanvas->keyDown(KEY_DOWN);
                return;     
			//edited by Mike, 20201121
//			case 0x4A: //J key //Windows Machine
   	       case (int) 'j': //j key //Linux Machine			
				myOpenGLCanvas->keyDown(KEY_J);
                return;     
			//edited by Mike, 20201121
//		   case 0x4C: //L key //Windows Machine
   	       case (int) 'l': //l key //Linux Machine			
				myOpenGLCanvas->keyDown(KEY_L);
                return;     
			//edited by Mike, 20201121
//			case 0x49: //I key //Windows Machine
   	       case (int) 'i': //i key //Linux Machine			
				myOpenGLCanvas->keyDown(KEY_I);
                return;     
			//edited by Mike, 20201121
//			case 0x4B: //K key //Windows Machine
   	       case (int) 'k': //k key //Linux Machine			
				myOpenGLCanvas->keyDown(KEY_K);
                return;     
		   //added by Mike, 20210123
   	       case (int) 'h': //h key //Linux Machine
		        myOpenGLCanvas->keyDown(KEY_H);
                return;
  	       case (int) 'u': //u key //Linux Machine
		        myOpenGLCanvas->keyDown(KEY_U);
                return;

			//removed by Mike, 20201001 
/*			               
   	       case 13: //ENTER
                myOpenGLCanvas->keyDown(KEY_ENTER);
                return 0;     
   	       case 80: //P
   	            if (myOpenGLCanvas->currentState!=TITLE_SCREEN) {
			        if (pause==0) //false
			          pause=1; //make it true
                    else pause=0;
                }
                return 0;     	        
*/         						
	}
}
//added by Mike, 20201002
void keyUp (unsigned char key, int x, int y)
{
//    std::cout << "keyup " << key << "\n";
	
	//added by Mike, 20201121
	switch (key)
    {
/*			   //removed by Mike, 20201121
			   //TO-DO: -add: identify VK_SPACE in Linux Machine
       	       case VK_SPACE:
			        myOpenGLCanvas->keyUp(KEY_SPACE);
                    return;     
*/					
	           //added by Mike, 20201013
	           //reference: 
	           //https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	           //last accessed: 20201013
				//edited by Mike, 20201121			
//			   case 0x41: //A key //Windows Machine
			   case (int) 'a': //d key //Linux Machine
				    myOpenGLCanvas->keyUp(KEY_A);
                    return;
				//edited by Mike, 20201121			
	   	       //case 0x44: //D key //Windows Machine
			   case (int) 'd': //d key //Linux Machine			
					//edited by Mike, 20210128
			        myOpenGLCanvas->keyUp(KEY_D);
//			        myOpenGLCanvas->keyUp(KEY_RIGHT);
	                return;     
				//edited by Mike, 20201121
//	   	       case 0x57: //W key //Windows Machine
			   case (int) 'w': //w key //Linux Machine			
					//edited by Mike, 20210128
//			        myOpenGLCanvas->keyUp(KEY_UP);
			        myOpenGLCanvas->keyUp(KEY_W);
					return;     
				//edited by Mike, 20201121
//	   	       case 0x53: //S key //Windows Machine
			   case (int) 's': //s key //Linux Machine
					myOpenGLCanvas->keyUp(KEY_S);
//			        myOpenGLCanvas->keyUp(KEY_DOWN);
	                return;     	
				//edited by Mike, 20201121
//			   case 0x4A: //J key //Windows Machine
			   case (int) 'j': //j key //Linux Machine			
					myOpenGLCanvas->keyUp(KEY_J);
	                return;     
				//edited by Mike, 20201121
//				case 0x4C: //L key //Windows Machine
			   case (int) 'l': //l key //Linux Machine			
					myOpenGLCanvas->keyUp(KEY_L);
	                return;     
				//edited by Mike, 20201121
//			case 0x49: //I key //Windows Machine
			   case (int) 'i': //i key //Linux Machine			
			        myOpenGLCanvas->keyUp(KEY_I);
	                return;     
			//edited by Mike, 20201121
//			case 0x4B: //K key //Windows Machine
   	       case (int) 'k': //k key //Linux Machine			
					myOpenGLCanvas->keyUp(KEY_K);
	                return;     
		   //added by Mike, 20210123
   	       case (int) 'h': //h key //Linux Machine
		        myOpenGLCanvas->keyUp(KEY_H);
                return;
  	       case (int) 'u': //u key //Linux Machine
		        myOpenGLCanvas->keyUp(KEY_U);
                return;
/*	//removed by Mike, 20210130
       	       case 13: //ENTER
                    myOpenGLCanvas->keyUp(KEY_ENTER);
                    return;			
*/					
        }
        return;    			
}

//note: special functions, e.g. shift, control, arrow keys
//UP: 101
//DOWN: 103
//LEFT: 100
//RIGHT: 102    
//added by Mike, 20201002
void specialKeyDown (int specialKey, int x, int y)
{
	//noted by Mike, 20201121
	//Note: space bar and escape key not detected
//    std::cout << "keydown " << specialKey << "\n";  
  
    switch (specialKey)
    {
/* //edited by Mike, 20201121
			//added by Mike, 20201001
   	       case VK_LEFT:
		        		myOpenGLCanvas->keyDown(KEY_LEFT);
                return;
   	       case VK_RIGHT:
		        		myOpenGLCanvas->keyDown(KEY_RIGHT);
                return;
   	       case VK_UP:
		        		myOpenGLCanvas->keyDown(KEY_UP);
                return;
   	       case VK_DOWN:
		        		myOpenGLCanvas->keyDown(KEY_DOWN);
                return; 
				 //removed by Mike, 20201002                    
//   	       case VK_SPACE:
//                myOpenGLCanvas->keyDown(KEY_SPACE);
//                return;
*/
			//TO-DO: -add: this
			//removed by Mike, 20201121
/*
		   case VK_ESCAPE:
	            PostQuitMessage(0);
	            return;// 0;
*/
			//removed by Mike, 20210130
/*			
		   //added by Mike, 20201001
   	       case VK_LEFT:
		        myOpenGLCanvas->keyDown(KEY_LEFT);
                return;// 0;
   	       case VK_RIGHT:
		        myOpenGLCanvas->keyDown(KEY_RIGHT);
                return;
   	       case VK_UP:
		        myOpenGLCanvas->keyDown(KEY_UP);
                return;                
   	       case VK_DOWN:
		        myOpenGLCanvas->keyDown(KEY_DOWN);
                return;     
*/				
		}
        return;

}
//added by Mike, 20201002
void specialKeyUp (int specialKey, int x, int y)
{
//    std::cout << "keyup " << specialKey << "\n";
    
	switch (specialKey)
    {
//removed by Mike, 20201121			
/*
			case VK_LEFT:
		        		myOpenGLCanvas->keyUp(KEY_LEFT);
                return;
   	       case VK_RIGHT:
		        		myOpenGLCanvas->keyUp(KEY_RIGHT);
                return;
   	       case VK_UP:
		        		myOpenGLCanvas->keyUp(KEY_UP);
                return;
   	       case VK_DOWN:
		        		myOpenGLCanvas->keyUp(KEY_DOWN);
                return;
         //removed by Mike, 20201002
//   	       case VK_SPACE:
//                myOpenGLCanvas->keyUp(KEY_SPACE);
//                return;
*/
	//removed by Mike,  20210130			
/*			
       	       case VK_LEFT:
			        myOpenGLCanvas->keyUp(KEY_LEFT);
                    return;// 0;
       	       case VK_RIGHT:
			        myOpenGLCanvas->keyUp(KEY_RIGHT);
                    return;
       	       case VK_UP:
			        myOpenGLCanvas->keyUp(KEY_UP);
                    return;
       	       case VK_DOWN:
			        myOpenGLCanvas->keyUp(KEY_DOWN);
                    return;         	
*/					
        }
        return;    
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // InglutReshapeWindowitialize GLUT
//   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); //addded by Mike, 20201202
   glutInitWindowSize(myWindowWidth, myWindowHeight);   // Set the window's initial width & height
//   glutInitWindowSize(2048,2048);   // Set the window's initial width & height

	//edited by Mike, 20201202
//   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutInitWindowPosition(0, 0); // Position the window's initial top-left corner

   //edited by Mike, 20201202
   //note: put this command after all the glutInit Window commands
   glutCreateWindow("Usbong OpenGL Automotive"); // Create a window with the given title

	  //added by Mike, 20201002
	  //Linux Machine
	  //note: to receive key presses
    myOpenGLCanvas = new OpenGLCanvas;
    myOpenGLCanvas->init();

	 	//edited by Mike, 20200930
   	//glutDisplayFunc(display); // Register display callback handler for window re-paint	

   	//edited by Mike, 20201002
//	 	glutDisplayFunc(displayOpenGLCanvas); // Register display callback handler for window re-paint
	 	glutDisplayFunc(displayOpenGLCanvas); // Register display callback handler for window re-paint
	 	//displayOpenGLCanvas(); //output of this = glutDisplayFunc(displayOpenGLCanvas);
	 		
	 	update(0);
	 		
	 	//added by Mike, 20201002
	 	glutKeyboardFunc(keyDown);
   		glutKeyboardUpFunc(keyUp);
/*	//removed by Mike, 20210130	
	 	glutSpecialFunc(specialKeyDown);
	 	glutSpecialUpFunc(specialKeyUp);
*/	
		//added by Mike, 20210128
		glutIgnoreKeyRepeat(1);
    		
   	glutMainLoop();           // Enter the infinitely event-processing loop
   	

   return 0;
}


/**************************
 * WinMain
 *
 **************************/
/*
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    // register window class
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    // create main window    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
	//added by Mike, 20200926
    int myWindowWidth=640;
    int myWindowHeight=640;


    hWnd = CreateWindow (
      "GLSample", "Usbong OpenGL Halimbawa", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, myWindowWidth, myWindowHeight,
      NULL, NULL, hInstance, NULL);

    // enable OpenGL for the window
    EnableOpenGL (hWnd, &hDC, &hRC);

    // program main loop
    while (!bQuit)
    {
        // check for messages
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            // handle or dispatch messages
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            // OpenGL animation code goes here

            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);


			//added by Mike, 20200926
		    // setup OpenGL initial state
		    glEnable(GL_CULL_FACE);   // cull back faces
		    glEnable(GL_DEPTH_TEST);  // enable Z-buffer
		    //glEnable(GL_LIGHTING);    // enable lighting
		    glEnable(GL_NORMALIZE);   // renormalize all vertex normals
		
		    // enable Gouraud shading
		    // (this is default--code appears here only for emphasis)
		    glShadeModel(GL_SMOOTH);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
//    		glViewport(0-myWindowWidth/2, 0-myWindowHeight/2, myWindowWidth, myWindowHeight);		// reset the viewport to new dimensions

			//TO-DO: -update: this
			//Reference: https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Introduction.html;
			//last accessed: 20200927
			// Set to 2D orthographic projection with the specified clipping area
			glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
			glLoadIdentity();                 // Reset Projection matrix
			gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set clipping area's left, right, bottom, top

    		glViewport(0, 0, myWindowWidth, myWindowHeight);		// reset the viewport to new dimensions

			// Draws two horizontal lines
            glPushMatrix ();			
			glBegin(GL_LINES);
              glColor3f (0.0f, 1.0f, 0.0f);
              //TO-DO: -add: grid
              //note: one (1) line, two (2) vertices
			  //X,Y coordinate position from center as reference point
			  //TO-DO: -update: this
			  //X,Y coordinate position from top-left as reference point
//			  glVertex2f(0.0f, 0.9f);
//			  glVertex2f(0.9f, 0.9f); 

			  glVertex2f(0.0f, 0.5f);
			  glVertex2f(0.5f, 0.5f); 

			glEnd();            
            glPopMatrix ();
            SwapBuffers (hDC);    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
            
            //TO-DO: -add: read input file with vertices
            //refer: https://all-things-andy-gavin.com/2020/02/27/war-stories-crash-bandicoot/
            //last accessed: 20200926
        }
    }

    // shutdown OpenGL
    DisableOpenGL (hWnd, hDC, hRC);

    // destroy the window explicitly
    DestroyWindow (hWnd);

    return msg.wParam;
}
*/

/********************
 * Window Procedure
 *
 ********************/
/*
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}
*/

/*******************
 * Enable OpenGL
 *
 *******************/
/*
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // get the device context (DC)
    *hDC = GetDC (hWnd);

    // set the pixel format for the DC 
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    // create and enable the render context (RC) 
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}
*/

/******************
 * Disable OpenGL
 *
 ******************/
/*
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
*/
