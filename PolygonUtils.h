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
 * @date created: 20201019
 * @date updated: 20220628; from 20210323
 * @website address: http://www.usbong.ph 
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

//added by Mike, 20201120
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#endif

//added by Mike, 20201123
#define GL_CLAMP_TO_EDGE 0x812F

//void load_tga(char *filename);
//GLboolean test_pow2(GLushort i);
//bool test_pow2(GLushort i);

/*	//removed by Mike, 20201020
//TO-DO: -add: these
void generatePoint(float latitude, float longitude);
void drawSphere();    
*/

void drawTriangle(float xPos, float yPos, float zPos);

//added by Mike, 20201019
void drawSquare();

//edited by Mike, 20201019
//void drawCube(float xPos, float yPos, float zPos);
//edited by Mike, 20201023
//void drawCube();
void drawCube(float fSideLength);

//added by Mike, 20201120
void drawCubeWithBlockTexture(float fSideLength, GLfloat tx, GLfloat ty, GLfloat tz, float x, float y, float z);

//added by Mike, 20210323
void drawCubeWithBlockTextureQuadFacingCameraOnly(float fSideLength, GLfloat tx, GLfloat ty, GLfloat tz, float x, float y, float z);
