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
 * @date created: 20200930
 * @date updated: 20220628; from 20201226
 * @website address: http://www.usbong.ph  
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
//TO-DO: -update: this

#include "MyDynamicObject.h"
#include <stdlib.h>

//#include "Beam.h"

#include <string.h>

//edited by Mike, 20201226
//#include <windows.h> //Windows Machine
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


#include <stdio.h>

//added by Mike, 20201213
void MyDynamicObject::draw() {
}

void MyDynamicObject::hitBy(MyDynamicObject* mdo){
}

bool MyDynamicObject::checkIsCollidable() {
     return isCollidable;
}
void MyDynamicObject::setCollidable(bool c) {
     isCollidable=c;
}

void MyDynamicObject::initializeCollisionSpheres(int ms) {
  csSize=0;
  maxSize = ms;
  collisionSpheres = (float**)malloc(maxSize*sizeof(float*));
  for(i=0; i<maxSize; i++)
    collisionSpheres[i] = (float*)malloc(4*sizeof(float)); //why 4? x y z, and radius
}

void MyDynamicObject::addSphere(float dx, float dy, float dz, float r)
{
	if(csSize!=maxSize)
	{
		collisionSpheres[csSize][0]=dx;
		collisionSpheres[csSize][1]=dy;
		collisionSpheres[csSize][2]=dz;
		collisionSpheres[csSize][3]=r;
		csSize++;
	}
	//else csSize has reached the maxSize
}

float** MyDynamicObject::getCollisionSpheres()
{
   return collisionSpheres;
}

int MyDynamicObject::getNumSpheres()
{
   return csSize;
}

float MyDynamicObject::getX()
{
   return myXPos;
}
float MyDynamicObject::getY()
{
   return myYPos;
}
float MyDynamicObject::getZ()
{
   return myZPos;
}

float MyDynamicObject::getWidth()
{
   return myWidth;
}
float MyDynamicObject::getHeight()
{
   return myHeight;
}

float MyDynamicObject::getDistance(float x1, float y1, float z1, float x2, float y2, float z2)
{
/*
    float dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
    char str[700];
    sprintf(str,"here: %f",dist);
    MessageBox(NULL, str, "Welcome!", MB_OK);
*/
   return /*dist;*/(float)sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

bool MyDynamicObject::checkCollision(MyDynamicObject* mdo1, MyDynamicObject* mdo2)
{
    int s1 = mdo1->getNumSpheres();
	int s2 = mdo2->getNumSpheres();
    if(s1==0||s2==0)
    {
    	return false;
    }

    float** cs1 = mdo1->getCollisionSpheres();
    float** cs2 = mdo2->getCollisionSpheres();
    for(int i = 0; i < s1; i++)
    {
    	for(int j = 0; j < s2; j++)
    	{
    		if(getDistance(cs1[i][0] + mdo1->getX(),
						   cs1[i][1] + mdo1->getY(),
						   cs1[i][2] + mdo1->getZ(),
						   cs2[j][0] + mdo2->getX(),
						   cs2[j][1] + mdo2->getY(),
						   cs2[j][2] + mdo2->getZ())
    					<=(cs1[i][3]+cs2[j][3]))
    		{
    			return true;
    	    }
        }
    }        
    return false;
}

bool MyDynamicObject::isIntersectingRect(MyDynamicObject* mdo1, MyDynamicObject* mdo2)
{     
/*
    char str[700];
    sprintf(str,"here: %f",mdo1->getY());//myZPos
    MessageBox(NULL, str, "Welcome!", MB_OK);
*/
/*	//edited by Mike, 20201117
    if (mdo2->getY()+mdo2->getHeight() < mdo1->getY() || //is the bottom of mdo2 above the top of mdo1?
        mdo2->getY() > mdo1->getY()+mdo1->getHeight() || //is the top of mdo2 below bottom of mdo1?
        mdo2->getX()+mdo2->getWidth() < mdo1->getX()  || //is the right of mdo2 to the left of mdo1?
        mdo2->getX() > mdo1->getX()+mdo1->getWidth()) //is the left of mdo2 to the right of mdo1?
        return false;
*/
	//note: computer computation correct, albeit human person may think 
	//based on observation in 3D (3-Dimensions) that beam should hit asteroid
	//alternative collision detection technique 
	//for computer to verify if not intersecting
	//Reference: Jongko, J. et al (2004)
/* //edited by Mike, 20210219	
    if (mdo2->getZ()+mdo2->getHeight() < mdo1->getZ() || //is the bottom of mdo2 above the top of mdo1?
        mdo2->getZ() > mdo1->getZ()+mdo1->getHeight() || //is the top of mdo2 below bottom of mdo1?
        mdo2->getX()+mdo2->getWidth() < mdo1->getX()  || //is the right of mdo2 to the left of mdo1?
        mdo2->getX() > mdo1->getX()+mdo1->getWidth()) //is the left of mdo2 to the right of mdo1?
        return false;
*/
	//TO-DO: -update: to use keyword for object size in z-axis, etc
    if (mdo2->getZ()+mdo2->getWidth() < mdo1->getZ() || //is the bottom of mdo2 above the top of mdo1?
        mdo2->getZ() > mdo1->getZ()+mdo1->getWidth() || //is the top of mdo2 below bottom of mdo1?
        mdo2->getX()+mdo2->getWidth() < mdo1->getX()  || //is the right of mdo2 to the left of mdo1?
        mdo2->getX() > mdo1->getX()+mdo1->getWidth()) {//is the left of mdo2 to the right of mdo1?
        return false;
	}
	
    return true;
}

void MyDynamicObject::collideWith(MyDynamicObject* mdo)
{
/*     
    if (this==we)
	{
		return;
	}
*/
    if ((!checkIsCollidable())||(!mdo->checkIsCollidable()))    
    {
        return;
    }
       
//    if (checkCollision(this, mdo))
    if (isIntersectingRect(this, mdo))
    {
        this->hitBy(mdo);
        mdo->hitBy(this);
    }
}

//added by Mike, 20201016
void MyDynamicObject::destroy()
{
/*	
	for(int i = 0; i < MAX_EXPLOSION_PARTICLES; ++i) {
	    delete [] explosionParticle[i];
	}
	delete [] explosionParticle;
*/
}
