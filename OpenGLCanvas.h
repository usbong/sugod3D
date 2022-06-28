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
 * @date created: 20200929
 * @date updated: 20220628; from 20210418
 * @website address: http://www.usbong.ph  
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//TO-DO: -update: "Canvas" to "Engine"?
//TO-DO: -update: this

#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

//added by Mike, 20201207
//auto-identify if Windows Machine
#ifdef _WIN32
	#include <windows.h> //Windows Machine
#endif
/*
#ifdef linux
    printf("In Linux");
#endif
*/


//#include "CTargaImage.h"

/* //removed by Mike, 20200929
#include "MyDynamicObject.h"

#include "Sound.h"
*/

#include <stdio.h>
//added by Mike, 20201213
#include <vector>

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0
#define TRUE 1
#define FALSE 0

#define FONT_TEXTURE 2
#define LEVEL_TEXTURE 3 //added by Mike, 20201122

//TO-DO: -update: this
#define KAHON_TEXTURE 4 //added by Mike, 20210402
#define ARMOR_TEXTURE 5 //added by Mike, 20210412
#define BAHAY_TEXTURE 6 //added by Mike, 20210418

//added by Mike, 20210420
//TO-DO: -update: this
#define MIKE_TEXTURE_A 7 
#define MIKE_TEXTURE_B 8 
#define MIKE_TEXTURE_C 9 

#define MAX_ENEMY 2

//edited by Mike, 20201013
//#define MAX_BEAMS 5
//added by Mike, 20201214
//TO-DO: -update: this
#define MAX_BEAMS 32

//edited by Mike, 20201016
//#define MAX_ASTEROID 28 //groups of 3, therefore 4 groups, plus inner groupings
//edited by Mike, 20201017
//#define MAX_ASTEROID 4
#define MAX_ASTEROID 16

#define MAX_LIFE 3
#define REQUIRED_POINTS_FOR_BONUS 30000 //5000

//added by Mike, 20201213
//includes: pilot, robotship, beams, asteroid, 
//edited by Mike, 20210120
//#define MAX_DYNAMIC_OBJECT 50 //TO-DO: -update: this

//edited by Mike, 20210206
#define MAX_DYNAMIC_OBJECT 18 //remove beams x32
//#define MAX_DYNAMIC_OBJECT 17 //remove beams x32

#define MAX 1026 //buffer

#define TITLE_SCREEN 0
#define CONTROLS_SCREEN 1
#define GAME_SCREEN 2
#define GAMEOVER_SCREEN 3
#define HIGHSCORE_SCREEN 4

#define ROBOTSHIP_INITIALIZING_STATE 0

//added by Mike, 20201123
#define GL_CLAMP_TO_EDGE 0x812F

//added by Mike, 20210207
#define FACING_UP 0
#define FACING_DOWN 1
#define FACING_LEFT 2
#define FACING_RIGHT 3
//diagonal
#define FACING_LEFT_AND_UP 4
#define FACING_RIGHT_AND_UP 5
#define FACING_LEFT_AND_DOWN 6
#define FACING_RIGHT_AND_DOWN 7


class MyDynamicObject; //added by Mike, 20201213

class RobotShip;
//added by Mike, 20201207
class Pilot;

//class Enemy; //removed by Mike, 20201013
class Beam;
class Asteroid;

class Level; //added by Mike, 20201118

class OpenGLCanvas
{
    private:
    	RobotShip *myRobotShip,
    	          *myRobotShipPlayer2;
		
		//added by Mike, 20201207
    	Pilot *myPilot;
		
		//added by Mike, 20201118
    	Level *myLevel;

        //Enemy *myEnemy[MAX_ENEMY];
        //removed by Mike, 20201013
//        Enemy *myEnemy;

        Beam *myBeam[MAX_BEAMS];

        //added by Mike, 20201014
        Asteroid *myAsteroid[MAX_ASTEROID];
//        Asteroid *myAsteroid;

		//added by Mike, 20201213
		//TO-DO: -add: level tile boxes, e.g. parts of tree
		//TO-DO: -update: MAX_DYNAMIC_OBJECT value
		//MyDynamicObject *myDynamicObjectContainer[MAX_DYNAMIC_OBJECT];
		//std::vector<MyDynamicObject> items;
		std::vector<MyDynamicObject*> vMyDynamicObjectContainer;
		
       	char *infile;//= "Patches1.txt";		
        char *outfile;
       	FILE *in;
        FILE *out;
        char buffer[MAX];

    	float rotationAngle;

/*    	//removed by Mike, 20201015
    	int myWindowWidth;
    	int myWindowHeight;
*/

/*
    	//added by Mike, 20201015
    	int iRowCountMax;
 	 	int iColumnCountMax;
*/    	  		
		//edited by Mike, 20201015 	
		//TO-DO: -reverify: this; malloc?
//   		int myKeysDown[14];	
		//added by Mike, 20201226
		//TO-DO: -update: this to include diagonal directional movement
		//edited by Mike, 20210130
//   		int myKeysDown[4];
   		int myKeysDown[10];
		   	
   		float rotationSpeed;
    
        int myRepaintCounter;
        int myRepaintDelay;
       	
   	    char tempText[50];
        int score,
            rest,
            restPlayer2,
            missiles,
            highScore,
            numOfAsteroidsLeft,
            currFrame,
            keyPressCounter,
            scoreBeforeBonus;
        bool isTwoPlayers;
        
        //added by Mike, 20201023; edited by Mike, 20201025
        //TO-DO: -update: container names in RobotShip.cpp, etc
        float myCanvasPosX,
    		  myCanvasPosY,
    		  myCanvasPosZ;
		
		float myCanvasStepX,
		      myCanvasStepY,
		      myCanvasStepZ,
			  myCanvasEyeStepX,
			  myCanvasRotateAxisStepY, //added by Mike, 20201024		       
			  //added by Mike, 20201025
			  myCanvasLookAtAngle,
    		  myCanvasEyePosX,
    		  myCanvasEyePosY,
    		  myCanvasEyePosZ,
    		  myCanvasCenterPosX,
    		  myCanvasCenterPosY,
    		  myCanvasCenterPosZ,
			  //added by Mike, 20201026
			  myCanvasLookAtAngleRad,
			  xAccel,
			  yAccel,
			  zAccel;

		//grid
	 	int iRowCountMax,
	 		iColumnCountMax, 
			iHeightCountMax; //added by Mike, 20210208
		
		//TO-DO: -update: this to use "x", "y", "z" keywords
		float fGridSquareWidth,
			  fGridSquareHeight;

		bool hasTurnedNinetyDegCounterClockWise,		       
			 hasTurnedNinetyDegClockWise;
			 
		//added by Mike, 20210416
		float fKahonRotation;

		//added by Mike, 20210325
		//TO-DO: -update: this
		int iCountLevelM;

		//added by Mike, 20210420
		//TO-DO: -update: this
		int iCountTaoAnimationFrame;
//		int iTaoAnimationFrameOffset;
		float fTaoAnimationFrameOffset;

       	//unsigned int myFontTextureObject;
               
        unsigned int myFontListBase;	    

//removed by Mike, 20200930, due to Linux Machine
//        HDC hDC;

        //CTargaImage *myBackground,
        //            *myFont;
       	unsigned int currTextureBackground,
       	             myTextureObjectFont,
       	             titleBackground,
       	             gameBackground;
    	bool loadBackground();
    	bool setupProjection();
    	//removed by Mike, 20200930
    	//void drawPlane();
    	void drawGrid();
		
		//added by Mike, 20201020
    	void drawGridWithZAxis();

    	void gameReset();
    	void resetDynamicObjects();
    	
        GLboolean test_pow2(GLushort i);
        void load_tga(char *filename);
		
		//added by Mike, 20210402
		void setupKahonTexture(int myKahonTextureObject);
		
		//added by Mike, 20210420
		//TO-DO: -update: this
		void setupTaoTexture();

		//added by Mike, 20210412
		void drawKahonWithTextureForVerification();

/*
        //methods to generate bitmap texts
        unsigned int createBitmapFont(char *fontName, int fontSize);
        void renderFont(int xPos, int yPos, unsigned int base, char *str);
	    void releaseFont(unsigned int base);
*/        
    public:
    	OpenGLCanvas();
    	~OpenGLCanvas();
    	//virtual ~CGfxOpenGL();
    	
/*		//removed by Mike, 20200929
        Sound *sound;
        SoundClip *beam, *valkyrie, *explosion, *zing, *thrust, *rotate, *bonus, *title;
*/        
		//added by Mike, 20201015
    	int myWindowWidth;
    	int myWindowHeight;

        int currentState;

    	bool init();
    	bool shutdown();

   		void keyDown(int keyCode);
	    void keyUp(int keyCode);
		
    	//void Prepare(float dt);
    	void render();
    	void update();
    	
    	void addScore(int s);
    	void loseLife();
    	void changeState(int s);
};

#endif
