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
 * @date updated: 20220628; from 20210219
 * @website address: http://www.usbong.ph       
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

#include <stdio.h>
#include <math.h>

//added by Mike, 20210107
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#endif

#include "Asteroid.h"

/*	//removed by Mike, 20201016
#include "PolygonUtils.h"
#include "ModelPool.h"
*/

//#include "OpenGLCanvas.h"

//edited by Mike, 20201016
//#include <string.h>
#include <string>

//added by Mike, 20210107
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

//#include "MyDynamicObject.h"

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

GLboolean Asteroid::test_pow2(GLushort i)
{
    while (i % 2 == 0)
        i /= 2;
    if (i == 1)
        return GL_TRUE;
    else
        return GL_FALSE;
}

void Asteroid::load_tga(char *filename)
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
        free(data);
        return;
    }

    /* read targa file into memory */
    data = (GLubyte *) malloc(targa.width * targa.height * 4);
    if (fread(data, targa.width * targa.height * 4, 1, file) != 1)
    {
        fclose(file);
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
}

void Asteroid::setup()
{
    GLuint i, j;
	
    glEnable(GL_DEPTH_TEST);

    // retrieve "unused" texture object
	glGenTextures(1, &myTextureObject);

    /* select texture 1 */
    glBindTexture(GL_TEXTURE_2D, myTextureObject);//1);

    /* create OpenGL texture out of targa file */
    load_tga("textures/asteroid.tga");

    /* set texture parameters */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* unselect texture 1 */
    glBindTexture(GL_TEXTURE_2D, 0);
	
	/* setup alpha blending */
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	//sound->sound_start();
	//explosion = sound->load_sound_clip(EXPLOSIONSOUND);
	
	//sound->sound_start();
	//

}


//Asteroid::Asteroid(): MyDynamicObject(10,10,300)
//edited by Mike, 20201016
//Asteroid::Asteroid(int status, float xPos, float yPos): MyDynamicObject(xPos,yPos,300)
//edited by Mike, 20201113
//Asteroid::Asteroid(int status, float xPos, float yPos): MyDynamicObject(xPos,yPos,0.0f)
//edited by Mike, 20201115
//Asteroid::Asteroid(int status, float xPos, float yPos, float zPos): MyDynamicObject(xPos,yPos,0.0f)
//edited by Mike, 2020117
//Asteroid::Asteroid(int status, float xPos, float yPos, float zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,0.0f, windowWidth, windowHeight)
Asteroid::Asteroid(int status, float xPos, float yPos, float zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,zPos, windowWidth, windowHeight)
{ 
    invincibleCounter=0;
    
    if (status==PARENT_STATUS) { 
        currentState=MOVING_STATE;
        currentStatus=status;

        /*	//edited by Mike, 20201016
		myWidth=4.0;
        myHeight=4.0;
        */

/*       ///edited by Mike, 2020116
		myWidth=0.15f; //note: 0.1f size of robotship
        myHeight=0.15f; //note: 0.1f size of robotship
*/
		myWidth=1.5f; //note: 1.0f size of robotship
        myHeight=1.5f; //note: 1.0f size of robotship
		
		//added by Mike, 20201016
    	myXPos=xPos;
		myYPos=yPos;
		//edited by Mike, 20201113
		myZPos=zPos;

		//added by Mike, 20210219
		stepX=2.00; //0.1
		stepY=2.00;
		stepZ=2.00;

		//added by Mike, 20201115
		myWindowWidth=windowWidth;
		myWindowHeight=windowHeight;
				
		//added by Mike, 20201016
    	myStartXPos=xPos;
		myStartYPos=yPos;
		//edited by Mike, 20201113
		myStartZPos=zPos;
        
        myScoreValue=200;
    
        rotationAngle=(float)(rand()%360);//10.0f;//360.0f;//90.0;
		//edited by Mike, 20201016
//        rotationStep=10.0;//1.0f;    
        rotationStep=1.0f;    

		//edited by Mike, 20201016
//        thrust=0.2f;
		//edited by Mike, 20201117
        //thrust=0.02f;
        thrust=0.06f;
        
//        thrust=0.002f; //explosion animation?
        
        xVel;
        yVel;
				
		//added by Mike, 20201016
    	explosionParticle = new float*[MAX_EXPLOSION_PARTICLES];
		for(int i=0; i<MAX_EXPLOSION_PARTICLES; i++) {
			//edited by Mike, 20201117
//		    explosionParticle [i] = new float[3];
		    explosionParticle [i] = new float[4];
		}		
    
        //child1=new Asteroid(CHILD_STATUS,0,0);
        //child2=new Asteroid(CHILD_STATUS,0,0);
        
        //initializeCollisionSpheres(1);
        //addSphere(0.0f, 0.0f, 0.0f, 2.0f);
        setCollidable(true);
    }    
/* //removed by Mike, 20201016    
    //TO-DO: -update: this
    else if (status==CHILD_STATUS) { 
        currentState=DEATH_STATE;
        currentStatus=status;
		//edited by Mike, 20201016
////        myWidth=2.0;
////        myHeight=2.0;
        
        myWidth=0.05;
        myHeight=0.05;

        myScoreValue=300;
    
        rotationAngle=(float)(rand()%360);//10.0f;//360.0f;//90.0;

		//edited by Mike, 20201016
        //rotationStep=15.0;//1.0f;    
        rotationStep=1.0;//1.0f;    

        thrust=0.4f;
        xVel;
        yVel;
        setCollidable(false);         
    }
    else if (status==GRANDCHILD_STATUS) { 
        currentState=DEATH_STATE;
        currentStatus=status;

		//edited by Mike, 20201016
////        myWidth=1.0;
////        myHeight=1.0;
      
        myWidth=0.025;
        myHeight=0.025;

        myScoreValue=400;
        
        rotationAngle=(float)(rand()%360);//10.0f;//360.0f;//90.0;
		//edited by Mike, 20201016
        //rotationStep=20.0;//1.0f;    
        rotationStep=1.0;

        thrust=0.6f;
        xVel;
        yVel;
        setCollidable(false);         
    }
*/    
	//removed by Mike, 20201016
//	setup();
}

Asteroid::~Asteroid()
{
}


//added by Mike, 20201016
void Asteroid::drawAsteroid() {	
	//added by Mike, 20201002; edited by Mike, 202010015
	//to make anchor/origin/reference point start at top-left
	//removed by Mike, 20201117
//    glTranslatef(0.0f, 0.1f, 0.0f);   

/* //removed by Mike, 20201113
   //TO-DO: -update: this due to output is 1 x 2 box, width x height
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		//removed by Mike, 20201016
//      glColor3f(0.0f, 0.0f, 1.0f); // blue
	  //1x1 square
	  glVertex2f(0.0f, 0.0f);    // x, y
      glVertex2f( 0.0f, -myHeight);
      glVertex2f(myWidth,  -myHeight);
      glVertex2f(myWidth,  0.0f);

   glEnd();    
*/   
   
	//added by Mike, 20201113
	//set square face with no color fill 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	drawCube();
		drawCube(myWidth); //myWidth = myHeight

	//set square face with color fill 	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);   
}

void Asteroid::drawExplosion() {
	//added by Mike, 20201002; edited by Mike, 202010015
	//to make anchor/origin/reference point start at top-left
	//edited by Mike, 20201016
//   glTranslatef(0.0f, 0.1f, 0.0f);   
	//edited by Mike, 20201017
/*   glTranslatef(0.0f, myHeight/4, 0.0f);   
*/
	//edited by Mike, 2020117
	//TO-DO: -add: this
//   glTranslatef(0.0f, myHeight/8, 0.0f);   
//   glTranslatef(0.0f, 0.0f, myHeight/8);   //removed by Mike, 20201117
	
   //TO-DO: update: this
//   for(int i=0; i<MAX_EXPLOSION_PARTICLES; i++) {
	   //added by Mike, 20201016
//       glTranslatef(myXPos+explosionParticle[i][X_POS_INDEX], myYPos+explosionParticle[i][Y_POS_INDEX], 0); //myZPos);    

//       glTranslatef(explosionParticle[i][X_POS_INDEX], explosionParticle[i][Y_POS_INDEX], 0); //myZPos);

	//edited by Mike, 2020117
/*
	   //TO-DO: -update: this due to output is 1 x 2 box, width x height
	   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			//edited by Mike, 20201017
	      //glColor3f(1.0f, 0.0f, 0.0f); // red
	      glColor3f(0.0f, 1.0f, 1.0f); // blue and green
		  
		  //edited by Mike, 20201017
		  //1x1 square
		  glVertex2f(0.0f, 0.0f);    // x, y
	      glVertex2f( 0.0f, -myHeight/8);
	      glVertex2f(myWidth/8,  -myHeight/8);
	      glVertex2f(myWidth/8,  0.0f);
	   glEnd();   	
*/
	    glColor3f(0.0f, 1.0f, 1.0f); // blue and green
		drawCube(myWidth/8); //myWidth=myHeight; myWidth/8 of Asteroid's width
//   }   
}

void Asteroid::draw()
{
    glPushMatrix();  
    //removed by Mike, 20201016
//    glTranslatef(myXPos, myYPos, myZPos);    

    switch (currentState)
    {
            case INITIALIZING_STATE:
            case MOVING_STATE:
               //added by Mike, 20201016
			   glTranslatef(myXPos, myYPos, myZPos);    

            	//removd by Mike, 20201016
//               glColor3f(1.0f, 1.0f, 1.0f); //white
               glColor3f(0.0f, 0.0f, 1.0f); //blue
           	   glPushMatrix();	
/*					//removed by Mike, 20201016
           	       //this handles rotation of the asteroid, not the direction where it goes
                   if (rotationStep>360)
                     rotationStep-=360;
                   else if (rotationStep<-360)
                     rotationStep+=360;
*/

/*					//removed by Mike, 20201016
                   glRotatef(rotationStep, 0.0f, 0.0f, 1.0f);
                   //this is so that the asteroids don't look the same
                   glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
                   //since the model ship is too big, do this...
                   if (currentStatus==CHILD_STATUS)                   
                     glScalef(0.5f, 0.5f, 0.5f);
                   else if (currentStatus==GRANDCHILD_STATUS)
                     glScalef(0.25f, 0.25f, 0.25f);
                   //glBindTexture(GL_TEXTURE_2D, myTextureObject);
                   //glEnable(GL_TEXTURE_2D); //added by Mike, Dec.21,2006
*/
					
				   //edited by Mike, 20201016
                   /* //note: use ModelPool.cpp
					drawAsteroid(myTextureObject);
                   */
                   drawAsteroid();
                   
           	   glPopMatrix();	// pop back to original coordinate system
               break;
        	case DEATH_STATE:
     			for(int i=0; i<MAX_EXPLOSION_PARTICLES; i++) {
	           	   glPushMatrix();	
	           	   		//edited by Mike, 2020117
//       					glTranslatef(explosionParticle[i][X_POS_INDEX], explosionParticle[i][Y_POS_INDEX], 0); //myZPos);
       					glTranslatef(explosionParticle[i][X_POS_INDEX], 0, explosionParticle[i][Z_POS_INDEX]);
						drawExplosion();
	           	   glPopMatrix();	// pop back to original coordinate system
	           }
        	   break;
    }    
    glPopMatrix();	// pop back to original coordinate system
    
    //glDisable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void Asteroid::update(float dt)
{
    switch (currentState)
    {
           case INITIALIZING_STATE:
                if (invincibleCounter==6) {
                  changeState(MOVING_STATE);
                  setCollidable(true);
                }
                else invincibleCounter++;
           case MOVING_STATE:      
					//removed by Mike, 20201016                  
//                  rotationStep+=10.0f;
					
					//added by Mike, 20201016
					//rotationAngle=0;

                  //thrust+=0.01f;
//                if (isMovingForward)
//                { 
                    /* rotationAngle in degrees, convert to radians */
                    //im not yet sure why, but i have to deduct 90 to rotationAngle
                    rotationAngleRad = (rotationAngle) * 3.141593f / 180.0f;
                    
					
					//edited by Mike, 20201113
                    //yAccel = (cos(rotationAngleRad)*thrust);
                    zAccel = (cos(rotationAngleRad)*thrust);

                    xAccel = -(sin(rotationAngleRad)*thrust);
/*
                   rotationAngle+=1;
                   char str[700];                                       
                   sprintf(str,"xAccel: %f",xAccel);
                   MessageBox(NULL, str, "Welcome!", MB_OK);
*/                   
                    xVel=xAccel;
					//edited by Mike, 20201113
                    //yVel=yAccel;
                    zVel=zAccel;
                    
/*                    
                    if (xVel > maxXVel) xVel = maxXVel;
                    else if (xVel < -maxXVel) xVel = -maxXVel;
                    if (yVel > maxYVel) yVel = maxYVel;
                    else if (yVel < -maxYVel) yVel = -maxYVel;
*/                  

                    myXPos+=xVel;
					//edited by Mike, 2020113
                    //myYPos+=yVel;
                    myZPos+=zVel;

/*                    
                    if (thrust>0)
                      thrust-=0.01f;
                    else thrust=0;
*/

/*				//edited by Mike, 20201016
           		//wrap the world 
           		if (myXPos <= -25.0f) myXPos = 25.0f;
           		else if (myXPos > 25.0f) myXPos = -25.0f; 
           		if (myYPos <= -17.0f) myYPos = 19.0f;
           		else if (myYPos > 19.0f) myYPos = -17.0f;
*/
				//removed by Mike, 20201113
				//TO-DO: -use: size of grid           		
/*
				//TO-DO: -add: 0.1f*iColumnCountMax
           		if (myXPos <= 0.0f) myXPos = 0.1f*20-myWidth/8; //if left side
           		else if (myXPos >= 0.1f*20) myXPos = 0.0f+myWidth/8; //if right side
*/
				//added by Mike, 20201115
/*
           		if (myXPos <= 0.0f) myXPos = myWindowWidth-myWidth/8; //if left side
           		else if (myXPos >= myWindowWidth) myXPos = 0.0f+myWidth/8; //if right side
*/
           		//edited by Mike, 20201116; edited again by Mike, 20210219
/*			
           		if (myXPos <= 0.0f) myXPos = myWindowWidth/100-myWidth/8; //if left side
           		else if (myXPos >= myWindowWidth/100) myXPos = 0.0f+myWidth/8; //if right side
           		if (myZPos >= myWindowHeight/100) myZPos = 0.0f+myHeight/8; //if bottom side
           		else if (myZPos <= 0.0f) myZPos = myWindowHeight/100-myHeight/8; //if top side
*/           		           		
           		if (myXPos <= 0.0f) myXPos = myWindowWidth-myWidth/8; //if left side
           		else if (myXPos >= myWindowWidth) myXPos = 0.0f+myWidth/8; //if right side
           		if (myZPos >= myWindowHeight) myZPos = 0.0f+myHeight/8; //if bottom side
           		else if (myZPos <= 0.0f) myZPos = myWindowHeight-myHeight/8; //if top side

				break;
           case DEATH_STATE:
/*			//added by Mike, 20201016
                if (invincibleCounter==10) {
                  changeState(MOVING_STATE);
                  setCollidable(true);
                }
                else invincibleCounter++;
*/              
				//edited by Mike, 20201016; edited again by Mike, 20210219
//                if (iDeathAnimationCounter==20) {//40) { //10
                if (iDeathAnimationCounter==40) {//40) { //10
				  //edited by Mike, 20201113
                  //reset(myStartXPos,myStartYPos);
                  reset(myStartXPos,myStartYPos,myStartZPos);

					//edited by Mike, 20201016
  //                changeState(MOVING_STATE);
                  setCollidable(true);
                }
                else {
                	for(int i=0; i<MAX_EXPLOSION_PARTICLES; i++) {
	                    /* rotationAngle in degrees, convert to radians */
	                    //im not yet sure why, but i have to deduct 90 to rotationAngle
						//edited by Mike, 20201016
//	                    rotationAngleRad = (rotationAngle) * 3.141593f / 180.0f;
	                    rotationAngleRad = (explosionParticle[i][ROTATION_ANGLE_INDEX]) * 3.141593f / 180.0f;
						
						//edited by Mike, 20201117	                    
/*
//	                    yAccel = (cos(rotationAngleRad)*thrust);
	                    zAccel = (cos(rotationAngleRad)*thrust);
	                    xAccel = -(sin(rotationAngleRad)*thrust);

*/
						//note: remove divide by 3; add shake via translate during impact?
//	                    yAccel = (cos(rotationAngleRad)*thrust/3);
	                    zAccel = (cos(rotationAngleRad)*thrust/3);
	                    xAccel = -(sin(rotationAngleRad)*thrust/3);



	/*
	                   rotationAngle+=1;
	                   char str[700];                                       
	                   sprintf(str,"xAccel: %f",xAccel);
	                   MessageBox(NULL, str, "Welcome!", MB_OK);
	*/                   
	
/*						//edited by Mike, 20201016
	                    xVel=xAccel;
	                    yVel=yAccel;
*/
	                    //edited by Mike, 2020117
						//xVel=xAccel;
						//edited by Mike, 20210116
//						xVel=xAccel*30.0;
						//edited by Mike, 20210219
						//xVel=xAccel*0.1;
						xVel=xAccel*stepX;
	                    
						//edited by Mike, 20201117	                    
	                    //yVel=yAccel;
	                    yVel=0;//yAccel;
						
//	                    zVel=zAccel;
						//edited by Mike, 20210116
//	                    zVel=zAccel*30.0;
						//edited by Mike, 20210219
	                    //zVel=zAccel*0.1;
	                    zVel=zAccel*stepZ;

						
/*						//edited by Mike, 20201016
	                    myXPos+=xVel;
	                    myYPos+=yVel;
*/	


						//TO-DO: -update: this
						explosionParticle[i][X_POS_INDEX]+=xVel;
						//edited by Mike, 20201117	                    
						explosionParticle[i][Y_POS_INDEX]+=yVel; //note: set to 0
						explosionParticle[i][Z_POS_INDEX]+=zVel;

/*
						explosionParticle[i][X_POS_INDEX]=getX();
						explosionParticle[i][Z_POS_INDEX]=getZ();
*/

/*
						//TO-DO: -add: 0.1f*iColumnCountMax
		           		if (explosionParticle[i][X_POS_INDEX] <= 0.0f) changeState(HIDDEN_STATE); //if left side
		           		else if (explosionParticle[i][X_POS_INDEX] >= 0.1f*20) changeState(HIDDEN_STATE); //if right side
		
						//TO-DO: -add: 0.1f*iRowCountMax
		           		if (explosionParticle[i][Y_POS_INDEX] >= 0.1f*20) changeState(HIDDEN_STATE); //if bottom side
		           		else if (explosionParticle[i][Y_POS_INDEX] <= 0.0f) changeState(HIDDEN_STATE); //if top side
*/
/*						//edited by Mike, 20201016
						//TO-DO: -add: 0.1f*iColumnCountMax
		           		if (myXPos <= 0.0f) myXPos = 0.1f*20-myWidth/8; //if left side
		           		else if (myXPos >= 0.1f*20) myXPos = 0.0f+myWidth/8; //if right side
		
						//TO-DO: -add: 0.1f*iRowCountMax
		           		if (myYPos >= 0.1f*20) myYPos = 0.0f+myHeight/8; //if bottom side
		           		else if (myYPos <= 0.0f) myYPos = 0.1f*20-myHeight/8; //if top side
*/
/*
						//edited by Mike, 20201117
						//TO-DO: -update: this
		           		if (explosionParticle[i][X_POS_INDEX] <= 0.0f) explosionParticle[i][X_POS_INDEX] = 0.1f*20-myWidth/8; //if left side
		           		else if (explosionParticle[i][X_POS_INDEX] >= 0.1f*20) explosionParticle[i][X_POS_INDEX] = 0.0f+myWidth/8; //if right side
		
						//TO-DO: -add: 0.1f*iRowCountMax
		           		if (explosionParticle[i][Y_POS_INDEX] >= 0.1f*20) explosionParticle[i][Y_POS_INDEX] = 0.0f+myHeight/8; //if bottom side
		           		else if (explosionParticle[i][Y_POS_INDEX] <= 0.0f) explosionParticle[i][Y_POS_INDEX] = 0.1f*20-myHeight/8; //if top side
*/
/*						//removed by Mike, 2020117
						//note: explosion wrap OK
						//edited by Mike, 20201117
		           		if (explosionParticle[i][X_POS_INDEX] <= 0.0f) explosionParticle[i][X_POS_INDEX] = myWindowWidth/100-myWidth/8; //if left side
		           		else if (explosionParticle[i][X_POS_INDEX] >= myWindowWidth/100) explosionParticle[i][X_POS_INDEX] = 0.0f+myWidth/8; //if right side
		
		           		if (explosionParticle[i][Z_POS_INDEX] >= myWindowHeight/100) explosionParticle[i][Z_POS_INDEX] = 0.0f+myHeight/8; //if bottom side
		           		else if (explosionParticle[i][Z_POS_INDEX] <= 0.0f) explosionParticle[i][Z_POS_INDEX] = myWindowHeight/100-myHeight/8; //if top side
*/ 
 
					}
	
                	iDeathAnimationCounter++;
				}
			  break;
/*          //removed by Mike, 20201016  
			case HIDDEN_STATE:
			  break;
*/			  
            default: //STANDING STATE
              break;//do nothing    
    }
}

void Asteroid::changeStatus(int s)
{
  currentStatus=s;                  
}
void Asteroid::changeState(int s)
{
  currentState=s;                  
}
int Asteroid::getState()
{
    return currentState;
}

void Asteroid::attachChild(Asteroid* c1, Asteroid* c2)
{
  child1=c1;
  child2=c2;
}

/* //removed by Mike, 20201113
void Asteroid::reset(float xPos, float yPos,float ra)
{
    rotationAngle=ra;//(float)(rand()%360);//10.0f;//360.0f;//90.0;

    myXPos=xPos;
    myYPos=yPos;  
    //myXPos=(float)(rand()%640); //640 is the max width of the screen
    //myYPos=(float)(rand()%640); //640 is the max height of the screen
    
    changeState(INITIALIZING_STATE);
    setCollidable(false);
	
	//edited by Mike, 20201016
    //invincibleCounter=0;
    iDeathAnimationCounter=0;

//	//TO-DO: -set: 4 to a defined constant container
//	for(int i=0; i<4; i++) {
//		explosionParticle[4][3]
//	}	
	
}
*/

//edited by Mike, 20201113
//void Asteroid::reset(float xPos, float yPos)
void Asteroid::reset(float xPos, float yPos, float zPos)
{
    rotationAngle=(float)(rand()%360);

    myXPos=xPos;
    myYPos=yPos;  
	//added by Mike, 20201113
    myZPos=zPos;  

    //myXPos=(float)(rand()%640); //640 is the max width of the screen
    //myYPos=(float)(rand()%640); //640 is the max height of the screen

	//TO-DO: -remove: this?
	//added by Mike, 20201016
	for(int i=0; i<MAX_EXPLOSION_PARTICLES; i++) {		
		//edited by Mike, 2020117
		explosionParticle[i][X_POS_INDEX]=getX();//myXPos;
		explosionParticle[i][Y_POS_INDEX]=getY();myYPos;	
		//added by Mike, 20201117
		explosionParticle[i][Z_POS_INDEX]=getZ();myZPos;	

		explosionParticle[i][ROTATION_ANGLE_INDEX]=rotationAngle;
	}
    
    changeState(INITIALIZING_STATE);
    setCollidable(false);

	//edited by Mike, 20201016
    //invincibleCounter=0;
    iDeathAnimationCounter=0;

}

/*
void Asteroid::move(int key)
{
   switch (key)
   {
     case KEY_UP:
          //isMovingForward=1;
          //myZPos-=1.0f;
          thrust+=0.1f;
          break;      
     case KEY_DOWN:
          break;      
     case KEY_LEFT:
          rotationAngle+=rotationStep;

          break;      
     case KEY_RIGHT:
          rotationAngle-=rotationStep;
          return;
   }
}
*/

void Asteroid::hitBy(MyDynamicObject* mdo)
{
/*	//removed by Mike, 20201016
	explosion = sound->load_sound_clip(EXPLOSIONSOUND);
	sound->play_sound_clip(explosion);
*/
    setCollidable(false);
    myOpenGLCanvas->addScore(myScoreValue);      
	
	//added by Mike, 20201016
	for(int i=0; i<MAX_EXPLOSION_PARTICLES; i++) {
		//edited by Mike, 2020117
		explosionParticle[i][X_POS_INDEX]=getX();//myXPos;
		explosionParticle[i][Y_POS_INDEX]=getY();//myYPos;	
		explosionParticle[i][Z_POS_INDEX]=getZ();//myZPos; //added by Mike, 20201117

		explosionParticle[i][ROTATION_ANGLE_INDEX]=rotationAngle;
		rotationAngle+=30;
	}

    changeState(DEATH_STATE);

/*	//edited by Mike, 20201016
	//TO-DO: -add: this
    if ((currentStatus==PARENT_STATUS) || (currentStatus==CHILD_STATUS))
      initChildren();    
*/      

/*	//removed by Mike, 20201016
	reset(myStartXPos,myStartYPos);
*/
}

void Asteroid::initChildren()
{
/*	//removed by Mike, 20201016	
     //child1->changeState(MOVING_STATE);
     child1->reset(getX(),getY(), rotationAngle-10);
     //child1->setCollidable(true);

     //child2->changeState(MOVING_STATE);
     child2->reset(getX(),getY(), rotationAngle+10);     
     //child2->setCollidable(true);
*/     
}

void Asteroid::setOpenGLCanvas(OpenGLCanvas* c)
{
     myOpenGLCanvas = c;
}

//added by Mike, 20201016
void Asteroid::destroy()
{
	for(int i = 0; i < MAX_EXPLOSION_PARTICLES; ++i) {
	    delete [] explosionParticle[i];
	}
	delete [] explosionParticle;
}


