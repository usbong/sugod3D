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
 * @date created: 20201016
 * @date updated: 20220628; from 20201213
 * @website address: http://www.usbong.ph      
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

//#include "CTargaImage.h"
#include "MyDynamicObject.h"

#include "OpenGLCanvas.h"

//added by Mike, 20201113
#include "PolygonUtils.h"

#define INITIALIZING_STATE 3
#define MOVING_STATE 0
#define DEATH_STATE 1
#define HIDDEN_STATE 2 //added by Mike, 20201016

#define PARENT_STATUS 0
#define CHILD_STATUS 1
#define GRANDCHILD_STATUS 2

#define MAX_EXPLOSION_PARTICLES 16
#define X_POS_INDEX 0
#define Y_POS_INDEX 1
#define Z_POS_INDEX 2 //added by Mike, 20201117
#define ROTATION_ANGLE_INDEX 3 //edited by Mike, 20201117

//class OpenGLCanvas;

class Asteroid: public MyDynamicObject
{
private:	
	int currentState,
	    currentStatus,//parent or child
        myScoreValue; 
        
/*	//removed by Mike, 20201016
	Sound *sound;
	SoundClip *explosion;
*/
	Asteroid* child1;
    Asteroid* child2;
    
    //edited by Mike, 20201016
//    float explosionParticle[MAX_EXPLOSION_PARTICLES][3]; //4: particles; 3: x, y, rotation angle
    float** explosionParticle;
    
    float stepX;
    float stepY;
    float stepZ;
	
	//added by Mike, 20201016
	float myStartXPos;
	float myStartYPos;
	//added by Mike, 20201113
	float myStartZPos;
        
    //float boundary;

    float rotationAngle;
    float rotationAngleRad;
    float rotationStep;
    
    float thrust;
    //float thrustMax;
    float xAccel;
    float yAccel;
	float zAccel; //added by Mike, 20201113

    float xVel;
    float yVel;
    float zVel; //added by Mike, 20201113
    
    //float maxXVel;
    //float maxYVel;    
    
    //int previousFacingState;
    //int currentFacingState;    
    
    OpenGLCanvas *myOpenGLCanvas;
/*
    CTargaImage *myBodyTexture;
   	unsigned int myBodyTextureObject;

    CTargaImage *myHeadTexture;
   	unsigned int myHeadTextureObject;
*/
    GLint tricount;
    GLint isMovingForward;

    GLboolean test_pow2(GLushort i);
    void load_tga(char *filename);

    unsigned int myTextureObject;
    int invincibleCounter;

	//added by Mike, 20201016
	int iDeathAnimationCounter;

    //draw texture
    //bool loadTexture(CTargaImage *myTexture, const char *filename, unsigned int *myTextureObject);
    void setup();
    void initChildren();
	// draws a unit cube
	//void drawCube(float xPos, float yPos, float zPos);

    // draw a unit triangle, Mike Dec. 19, 2006
    //void drawTriangle(float xPos, float yPos, float zPos);
    //void drawTriangledCube(float xPos, float yPos, float zPos);

	//added by Mike, 20201016
	void drawAsteroid();
	void drawExplosion();

public:
//	Asteroid();
	//edited by Mike, 20201113
//    Asteroid(int status, float xPos, float yPos); 
	//edited by Mike, 20201115
//    Asteroid(int status, float xPos, float yPos, float zPos); 
    Asteroid(int status, float xPos, float yPos, float zPos,int windowWidth,int windowHeight);

	~Asteroid();
	//virtual ~Robot();

    virtual float getX()
    {
       return myXPos;
    }
    virtual float getY()
    {
       return myYPos;
    }
    virtual float getZ()
    {
       return myZPos;
    }
    virtual float getWidth()
    {
       return myWidth;
    }
    virtual float getHeight()
    {
       return myHeight;
    }

    void setOpenGLCanvas(OpenGLCanvas* c);
    
    //int STANDING_STATE;
    //int WALKING_STATE;
    
	// draws the entire robot
	//void drawRobot(float xPos, float yPos, float zPos);
    //void drawRobotShip();
    //void drawValkyrie();
    //edited by Mike, 20201213
    //void draw();
    virtual void draw();
    
	// updates the robot data
	void update(float dt);
	
	void changeState(int s);	//moving or death
	void changeStatus(int s);	//parent or child

	int getState();

	//edited by Mike, 20201113
//	void reset(float xPos, float yPos, float ra);
//	void reset(float xPos, float yPos);
//	void reset(float xPos, float yPos, float zPos, float ra);
	void reset(float xPos, float yPos, float zPos);
     
	void move(int key);	
	
    virtual void hitBy(MyDynamicObject* mdo);
    void attachChild(Asteroid* child1, Asteroid* child2);
	
	//added by Mike, 20201016
    virtual void destroy();

};
