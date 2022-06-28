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
 * @date updated: 20220628; from 20210324
 * @website address: http://www.usbong.ph
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

//TO-DO: -update: this

#include "PolygonUtils.h"
#include <math.h>

//#include <SDL.h>

//edited by Mike, 20201019
#include <GL/gl.h>
#include <GL/glut.h> 
#include <GL/glu.h>

//added by Mike, 20201114; removed by Mike, 20201114
// disable implicit float-double casting
//#pragma warning(disable:4305)

/*
#include <stdio.h>
#include <stdlib.h>
*/

/*	//removed by Mike, 20201019
void drawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glBegin(GL_POLYGON);
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// bottom face
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// back face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
		glEnd();
	glPopMatrix();
}
*/

void drawTriangle(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
        //front
		glBegin(GL_TRIANGLES);
            //glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.5f, 0.0f);
            //glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.5f, 0.0f, 0.0f);
            //glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f, 0.0f, 0.0f);
		glEnd();
		//back
		glBegin(GL_TRIANGLES);
            glVertex3f(0.5f, 0.0f, 0.0f);
            glVertex3f(-0.5f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.5f, 0.0f);
		glEnd();

	glPopMatrix();     	
}

//added by Mike, 20201019
//void drawSquare(float xPos, float yPos, float zPos) {
void drawSquare() {
	//to make anchor/origin/reference point start at top-left
    glTranslatef(0.0f, 0.1f, 0.0f);   
	
	//Reference: https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html;
	//last accessed: 20200928 
   //note: 0.5f = half of the window width or height
   // Draw a Red 1x1 Square centered at origin
   //TO-DO: -update: this due to output is 1 x 2 box, width x height
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
/*    //edited by Mike, 20201001  
	  glVertex2f(-0.1f, -0.1f);    // x, y
      glVertex2f( 0.1f, -0.1f);
      glVertex2f( 0.1f,  0.1f);
      glVertex2f(-0.1f,  0.1f);
*/      
	  //1x1 square
	  glVertex2f(0.0f, 0.0f);    // x, y
      glVertex2f( 0.0f, -0.1f);
      glVertex2f( 0.1f,  -0.1f);
      glVertex2f(0.1f,  0.0f);
   glEnd();    
}


//Reference: Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
//void CGfxOpenGL::DrawCube(float xPos, float yPos, float zPos)
//void drawCube()
void drawCube(float fSideLength)
{
	glPushMatrix();
	//to make anchor/origin/reference point start at top-left
//		glTranslatef(xPos, yPos, zPos);
		//note: we add 0.2f in x-axis due to vertex locations 
		//of cube's square face not equal with that of drawSquare()
//	    glTranslatef(0.0f, 0.1f, 0.0f);

		//TO-DO: -reverify: this if necessary
		//edited by Mike, 20201116
//	    glTranslatef(0.2f, 0.1f, 0.0f);   
	    glTranslatef(0.0f, fSideLength, 0.0f);   //0.0f, 1.0f, 0.0f
		
		//TO-DO: -update: vertex locations
		
		//added by Mike, 20201114
//		glDepthFunc(GL_ALWAYS);
//		glEnable(GL_DEPTH_TEST);	
		//removed by Mike, 20201114		
/*
		// Draw lines antialiased
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/
		//removed by Mike, 20201114		
		// Draw black wireframe version of geometry
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

/*		//removed by Mike, 20201114
		//added by Mike, 20201114
		glDepthFunc(GL_LEQUAL);

		glLineWidth(2.0f);

		glEnable( GL_POLYGON_OFFSET_FILL );
        glPolygonOffset( 1.0, 1.0 ); //3.0, 1.0 );	
*/		

		glLineWidth(2.0f);
		
		glBegin(GL_QUADS);
/*		
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);	// bottom face
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);	// back face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
*/
/*			//edited by Mike, 20201023
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -0.1f);
			glVertex3f(-0.1f, 0.0f, -0.1f);
			glVertex3f(-0.1f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-0.1f, 0.0f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(0.0f, -0.1f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -0.1f, 0.0f);
			glVertex3f(0.0f, -0.1f, -0.1f);
			glVertex3f(0.0f, 0.0f, -0.1f);
			glVertex3f(-0.1f, 0.0f, 0.0f);	// left face
			glVertex3f(-0.1f, 0.0f, -0.1f);
			glVertex3f(-0.1f, -0.1f, -0.1f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(0.0f, -0.1f, 0.0f);	// bottom face
			glVertex3f(0.0f, -0.1f, -0.1f);
			glVertex3f(-0.1f, -0.1f, -0.1f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(0.0f, 0.0f, -0.1f);	// back face
			glVertex3f(-0.1f, 0.0f, -0.1f);
			glVertex3f(-0.1f, -0.1f, -0.1f);
			glVertex3f(0.0f, -0.1f, -0.1f);
*/
			//note: add vertex counter-clockwise
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-fSideLength, 0.0f, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, 0.0f);

			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(0.0f, 0.0f, -fSideLength);
			//edited by Mike, 2020114
			//vertices drawn clock-wise
			
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

/*
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
*/
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

			//edited by Mike, 20201114
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/
			//TO-DO: -reverify: disable BackFaceCulling 
			//+updated: to draw vertices clockwise due to back face not drawn
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/
			//draw vertices clockwise
			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

		glEnd();
		
/*		//removed by Mike, 20201114		
		//added by Mike, 20201114
		glDisable( GL_POLYGON_OFFSET_FILL );
*/

		//added by Mike, 20201114; removed by Mike, 2020114
//		glDepthFunc(GL_LESS);

	glPopMatrix();
}

//added by Mike, 20201120
//note: Z-ordering/depth test: what is drawn last is drawn top
//References:
//1) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
//2) https://stackoverflow.com/questions/42695183/qt-opengl-textures-transparency-issues;
//last accessed: 20201123
//answer by: Swift - Friday Pie, 20170309T1432
void drawCubeWithBlockTextureTopQuadFaceOnly(float fSideLength, GLfloat tx, GLfloat ty, GLfloat tz, float x, float y, float z)
{
	glPushMatrix();
/*
glEnable(GL_ALPHA_TEST);
glEnable( GL_BLEND );
glBlendFunc(GL_SRC_ALPHA, GL_ONE);
glEnable(GL_DEPTH_TEST);
glClearDepth(1.0); 
*/
//glDisable(GL_ALPHA_TEST);
//glDisable( GL_BLEND );
//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//glDisable(GL_DEPTH_TEST);
//glClearDepth(1.0); 
/*
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
*/

	//to make anchor/origin/reference point start at top-left
//		glTranslatef(xPos, yPos, zPos);
		//note: we add 0.2f in x-axis due to vertex locations 
		//of cube's square face not equal with that of drawSquare()
//	    glTranslatef(0.0f, 0.1f, 0.0f);

		//TO-DO: -reverify: cause of excess cube translation when moving camera	
//		glLineWidth(2.0f);
	    glTranslatef(x, y, z);

		//TO-DO: -reverify: this if necessary
   		glTranslatef(0.0f, 0.0f, -fSideLength);

		//due to top face not drawn
		//TO-DO: -reverify: if we do not add top face 
		//added due to inverted z-axis based on position of vertices 
		glRotatef(180, 0.0f, 0.0f, 1.0f);
		//added by Mike, 20201122
		//added due to inverted x-axis based on position of vertices 
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		
//		glScalef(0.99f, 0.99f, 0.99f);

		//TO-DO: -update: vertex locations
		
		//added by Mike, 20201114
//		glDepthFunc(GL_ALWAYS);
//		glEnable(GL_DEPTH_TEST);	
		//removed by Mike, 20201114		
/*
		// Draw lines antialiased
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/
		//removed by Mike, 20201114		
		// Draw black wireframe version of geometry
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


//	glEnable(GL_BLEND);

		//TO-DO: -reverify: this due to wireframe still drawn with cube
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


//		glDepthFunc(GL_LESS);
//		glDepthFunc(GL_LEQUAL);

/*		//removed by Mike, 20201114
		//added by Mike, 20201114
		glDepthFunc(GL_LEQUAL);

		glLineWidth(2.0f);

		glEnable( GL_POLYGON_OFFSET_FILL );
        glPolygonOffset( 1.0, 1.0 ); //3.0, 1.0 );	
*/		

		//removed by Mike, 20201123
//		glLineWidth(2.0f);
//		glLineWidth(1.0f);
//		glLineWidth(0.01f);
//		glDisable(GL_LINE_WIDTH);
//		glLineWidth(0.0f);

//glPointSize(0.01f);

		//edited by Mike, 20201123
//		glColor3f(0.0f,1.0f,0.0f);
//		glColor4f(0.0f,0.0f,0.0f,0.5f);

//glDisable(GL_LIGHTING);
//glDisable(GL_TEXTURE_2D);

//glDisable(GL_TEXTURE_2D);
//glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
/*			//edited by Mike, 20201122
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/
/*
			//counter clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/

/*
			//TO-DO: -reverify due to not drawn
			//clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/

			//edited by Mike, 20201123
			//note: y-axis inverted
			// bottom face becomes top face 		
			//set y to be at origin, i.e. 0.0f
/*			//edited by Mike, 20201124
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f, -fSideLength);
*/
			//removed by Mike, 20201124
//			glColor3f(0.14f,0.68f,0.06f);


//			float fBorderWidth = 0.1f;
			float fBorderWidth = 0.05f;
//			float fBorderWidth = 0.0f;

	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+fBorderWidth, 0.0f, 0.0f+fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength-fBorderWidth, 0.0f, 0.0f+fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength-fBorderWidth, 0.0f, -fSideLength-fBorderWidth);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f+fBorderWidth, 0.0f, -fSideLength-fBorderWidth);

/* 			//note: use technique +0.5f to create effect, e.g. disheveled leaves of tree
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+0.5f, 0.0f, 0.0f+0.5f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength+0.5f, 0.0f, 0.0f+0.5f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength+0.5f, 0.0f, -fSideLength+0.5f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f+0.5f, 0.0f, -fSideLength+0.5f);
*/

		glEnd();
		
/*		//removed by Mike, 20201114		
		//added by Mike, 20201114
		glDisable( GL_POLYGON_OFFSET_FILL );
*/

		//added by Mike, 20201114; removed by Mike, 2020114
//		glDepthFunc(GL_LESS);

//glEnable(GL_LIGHTING);
//glEnable(GL_TEXTURE_2D);
//glColor3f(1.0f, 1.0f, 1.0f);

	glPopMatrix();
}

//added by Mike, 20210323
//note: Z-ordering/depth test: what is drawn last is drawn top
//References:
//1) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
//2) https://stackoverflow.com/questions/42695183/qt-opengl-textures-transparency-issues;
//last accessed: 20201123
//answer by: Swift - Friday Pie, 20170309T1432
void drawCubeWithBlockTextureQuadFacingCameraOnly(float fSideLength, GLfloat tx, GLfloat ty, GLfloat tz, float x, float y, float z)
{
	glPushMatrix();
/*
glEnable(GL_ALPHA_TEST);
glEnable( GL_BLEND );
glBlendFunc(GL_SRC_ALPHA, GL_ONE);
glEnable(GL_DEPTH_TEST);
glClearDepth(1.0); 
*/
//glDisable(GL_ALPHA_TEST);
//glDisable( GL_BLEND );
//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//glDisable(GL_DEPTH_TEST);
//glClearDepth(1.0); 
/*
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
*/

	//to make anchor/origin/reference point start at top-left
//		glTranslatef(xPos, yPos, zPos);
		//note: we add 0.2f in x-axis due to vertex locations 
		//of cube's square face not equal with that of drawSquare()
//	    glTranslatef(0.0f, 0.1f, 0.0f);

		//TO-DO: -reverify: cause of excess cube translation when moving camera	
//		glLineWidth(2.0f);
	    glTranslatef(x, y, z);

		//TO-DO: -reverify: this if necessary
   		glTranslatef(0.0f, 0.0f, -fSideLength);

		//due to top face not drawn
		//TO-DO: -reverify: if we do not add top face 
		//added due to inverted z-axis based on position of vertices 
		glRotatef(180, 0.0f, 0.0f, 1.0f);

		//removed by Mike, 20210323
		//facing the camera
		//added by Mike, 20201122
		//added due to inverted x-axis based on position of vertices 
//		glRotatef(180, 1.0f, 0.0f, 0.0f);

		//added by Mike, 20210324
		glRotatef(-90, 1.0f, 0.0f, 0.0f);

		
//		glScalef(0.99f, 0.99f, 0.99f);

		//TO-DO: -update: vertex locations
		
		//added by Mike, 20201114
//		glDepthFunc(GL_ALWAYS);
//		glEnable(GL_DEPTH_TEST);	
		//removed by Mike, 20201114		
/*
		// Draw lines antialiased
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/
		//removed by Mike, 20201114		
		// Draw black wireframe version of geometry
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


//	glEnable(GL_BLEND);

		//TO-DO: -reverify: this due to wireframe still drawn with cube
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


//		glDepthFunc(GL_LESS);
//		glDepthFunc(GL_LEQUAL);

/*		//removed by Mike, 20201114
		//added by Mike, 20201114
		glDepthFunc(GL_LEQUAL);

		glLineWidth(2.0f);

		glEnable( GL_POLYGON_OFFSET_FILL );
        glPolygonOffset( 1.0, 1.0 ); //3.0, 1.0 );	
*/		

		//removed by Mike, 20201123
//		glLineWidth(2.0f);
//		glLineWidth(1.0f);
//		glLineWidth(0.01f);
//		glDisable(GL_LINE_WIDTH);
//		glLineWidth(0.0f);

//glPointSize(0.01f);

		//edited by Mike, 20201123
//		glColor3f(0.0f,1.0f,0.0f);
//		glColor4f(0.0f,0.0f,0.0f,0.5f);

//glDisable(GL_LIGHTING);
//glDisable(GL_TEXTURE_2D);

//glDisable(GL_TEXTURE_2D);
//glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
/*			//edited by Mike, 20201122
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/
/*
			//counter clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/

/*
			//TO-DO: -reverify due to not drawn
			//clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/

			//edited by Mike, 20201123
			//note: y-axis inverted
			// bottom face becomes top face 		
			//set y to be at origin, i.e. 0.0f
/*			//edited by Mike, 20201124
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f, -fSideLength);
*/
			//removed by Mike, 20201124
//			glColor3f(0.14f,0.68f,0.06f);


//			float fBorderWidth = 0.1f;
			float fBorderWidth = 0.05f;
//			float fBorderWidth = 0.0f;

	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+fBorderWidth, 0.0f, 0.0f+fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength-fBorderWidth, 0.0f, 0.0f+fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength-fBorderWidth, 0.0f, -fSideLength-fBorderWidth);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f+fBorderWidth, 0.0f, -fSideLength-fBorderWidth);

/* 			//note: use technique +0.5f to create effect, e.g. disheveled leaves of tree
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+0.5f, 0.0f, 0.0f+0.5f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength+0.5f, 0.0f, 0.0f+0.5f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength+0.5f, 0.0f, -fSideLength+0.5f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f+0.5f, 0.0f, -fSideLength+0.5f);
*/

		glEnd();
		
/*		//removed by Mike, 20201114		
		//added by Mike, 20201114
		glDisable( GL_POLYGON_OFFSET_FILL );
*/

		//added by Mike, 20201114; removed by Mike, 2020114
//		glDepthFunc(GL_LESS);

//glEnable(GL_LIGHTING);
//glEnable(GL_TEXTURE_2D);
//glColor3f(1.0f, 1.0f, 1.0f);

	glPopMatrix();
}



//PrevV20201124
//edited by Mike, 20201129
//+added: fBorderWidth to eliminate excess space between cubes
void drawCubeWithBlockTexture(float fSideLength, GLfloat tx, GLfloat ty, GLfloat tz, float x, float y, float z)
{
//	float fBorderWidth = 0.05f;
//edited by Mike, 20210311
	float fBorderWidth = 0.0125f;
//	float fBorderWidth = fSideLength;
	
//	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
/*
glEnable(GL_ALPHA_TEST);
glEnable( GL_BLEND );
glBlendFunc(GL_SRC_ALPHA, GL_ONE);
glEnable(GL_DEPTH_TEST);
glClearDepth(1.0); 
*/
//glDisable(GL_ALPHA_TEST);
//glDisable( GL_BLEND );
//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//glDisable(GL_DEPTH_TEST);
//glClearDepth(1.0); 
/*
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
*/

	//to make anchor/origin/reference point start at top-left
//		glTranslatef(xPos, yPos, zPos);
		//note: we add 0.2f in x-axis due to vertex locations 
		//of cube's square face not equal with that of drawSquare()
//	    glTranslatef(0.0f, 0.1f, 0.0f);

		//TO-DO: -reverify: cause of excess cube translation when moving camera	
//		glLineWidth(2.0f);
	    glTranslatef(x, y, z);

		//TO-DO: -reverify: this if necessary
   		glTranslatef(0.0f, 0.0f, -fSideLength);

		//due to top face not drawn
		//TO-DO: -reverify: if we do not add top face 
		//added due to inverted z-axis based on position of vertices 
		glRotatef(180, 0.0f, 0.0f, 1.0f);
		//added by Mike, 20201122
		//added due to inverted x-axis based on position of vertices 
		glRotatef(180, 1.0f, 0.0f, 0.0f);
		
//		glScalef(0.99f, 0.99f, 0.99f);

		//TO-DO: -update: vertex locations
		
		//added by Mike, 20201114
//		glDepthFunc(GL_ALWAYS);
//		glEnable(GL_DEPTH_TEST);	
		//removed by Mike, 20201114		
/*
		// Draw lines antialiased
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/
		//removed by Mike, 20201114		
		// Draw black wireframe version of geometry
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glEnable(GL_BLEND);

		//TO-DO: -reverify: this due to wireframe still drawn with cube
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


//		glDepthFunc(GL_LESS);
//		glDepthFunc(GL_LEQUAL);

/*		//removed by Mike, 20201114
		//added by Mike, 20201114
		glDepthFunc(GL_LEQUAL);

		glLineWidth(2.0f);

		glEnable( GL_POLYGON_OFFSET_FILL );
        glPolygonOffset( 1.0, 1.0 ); //3.0, 1.0 );	
*/		

		//removed by Mike, 20201123
//		glLineWidth(2.0f);
//		glLineWidth(1.0f);
//		glLineWidth(0.01f);
//		glDisable(GL_LINE_WIDTH);
//		glLineWidth(0.0f);

//glPointSize(0.01f);

		//edited by Mike, 20201123
//		glColor3f(0.0f,1.0f,0.0f);
//		glColor4f(0.0f,0.0f,0.0f,0.5f);

//glDisable(GL_LIGHTING);
//glDisable(GL_TEXTURE_2D);

//glDisable(GL_TEXTURE_2D);
//glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
			//note: inverted y-axis; top face becomes bottom face
			//counter clockwise
			// top face		
/*			//edited by Mike, 20201129
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, 0.0f, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);
*/
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+fBorderWidth, 0.0f, 0.0f+fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f+fBorderWidth, 0.0f, -fSideLength-fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength-fBorderWidth, 0.0f, -fSideLength-fBorderWidth);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength-fBorderWidth, 0.0f, 0.0f+fBorderWidth);


			//TO-DO: -update: this
/*
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-fSideLength, 0.0f, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, 0.0f);
*/
			//edited by Mike, 20201129
/*
			//counter clockwise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, -fSideLength, 0.0f);
*/
			//counter clockwise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+fBorderWidth, 0.0f+fBorderWidth, 0.0f);	// front face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength-fBorderWidth, 0.0f+fBorderWidth, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength-fBorderWidth, -fSideLength-fBorderWidth, 0.0f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f+fBorderWidth, -fSideLength-fBorderWidth, 0.0f);


/*			//edited by Mike, 20201122
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(0.0f, 0.0f, -fSideLength);
*/			

/*			//edited by Mike, 20201129
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(0.0f, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f, -fSideLength);
*/	
/*			//edited by Mike, 20201129
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(0.0f, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f, -fSideLength);
*/
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f+fBorderWidth, 0.0f+fBorderWidth);	// right face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength-fBorderWidth, 0.0f+fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(0.0f, -fSideLength-fBorderWidth, -fSideLength-fBorderWidth);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f+fBorderWidth, -fSideLength-fBorderWidth);
			
			//edited by Mike, 2020114
			//vertices drawn clock-wise

/*			//edited by Mike, 20201122
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/
	        glTexCoord2f(tx, ty);
			glVertex3f(-fSideLength, 0.0f+fBorderWidth, 0.0f+fBorderWidth);	// left face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f+fBorderWidth, -fSideLength-fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength-fBorderWidth, -fSideLength-fBorderWidth);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, -fSideLength-fBorderWidth, 0.0f+fBorderWidth);

/*
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
*/
/*			//edited by Mike, 20201122
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/
/*
			//counter clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/

/*
			//TO-DO: -reverify due to not drawn
			//clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/

			//edited by Mike, 20201129			
			//note: y-axis inverted
			// bottom face becomes top face 		
			//set y to be at origin, i.e. 0.0f
/*			//removed by Mike, 20201129
//			float fBorderWidth = 0.05f;
			float fBorderWidth = 0.0125f;
*/
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+fBorderWidth, 0.0f, 0.0f+fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength-fBorderWidth, 0.0f, 0.0f+fBorderWidth);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength-fBorderWidth, 0.0f, -fSideLength-fBorderWidth);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f+fBorderWidth, 0.0f, -fSideLength-fBorderWidth);
			
			
/* 			//note: use technique +0.5f to create effect, e.g. disheveled leaves of tree
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+0.5f, 0.0f, 0.0f+0.5f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength+0.5f, 0.0f, 0.0f+0.5f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength+0.5f, 0.0f, -fSideLength+0.5f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f+0.5f, 0.0f, -fSideLength+0.5f);
*/
/*
			//TO-DO: -reverify: due to computer still draws borders
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f-0.03f, 0.0f, 0.0f-0.03f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength-0.03f, 0.0f, 0.0f-0.03f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength-0.03f, 0.0f, -fSideLength+0.03f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f-0.03f, 0.0f, -fSideLength+0.03f);
*/
			//edited by Mike, 20201114
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/
			//TO-DO: -reverify: disable BackFaceCulling 
			//+updated: to draw vertices clockwise due to back face not drawn
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/

/*			//edited by Mike, 20201122
			//draw vertices clockwise
			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
*/

			//note: inverted z-axis; back face becomes front face
/*			//edited by Mike, 20201129
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
*/
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+fBorderWidth, 0.0f+fBorderWidth, -fSideLength);	// back face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f+fBorderWidth, -fSideLength-fBorderWidth, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength-fBorderWidth, -fSideLength-fBorderWidth, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength-fBorderWidth, 0.0f+fBorderWidth, -fSideLength);

		glEnd();
		
/*		//removed by Mike, 20201114		
		//added by Mike, 20201114
		glDisable( GL_POLYGON_OFFSET_FILL );
*/

		//added by Mike, 20201114; removed by Mike, 2020114
//		glDepthFunc(GL_LESS);

//glEnable(GL_LIGHTING);
//glEnable(GL_TEXTURE_2D);
//glColor3f(1.0f, 1.0f, 1.0f);

	glPopMatrix();
}

//added by Mike, 20201120
//note: Z-ordering/depth test: what is drawn last is drawn top
//References:
//1) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
//2) https://stackoverflow.com/questions/42695183/qt-opengl-textures-transparency-issues;
//last accessed: 20201123
//answer by: Swift - Friday Pie, 20170309T1432
void drawCubeWithBlockTexturePrev(float fSideLength, GLfloat tx, GLfloat ty, GLfloat tz, float x, float y, float z)
{
	glPushMatrix();
	//to make anchor/origin/reference point start at top-left
//		glTranslatef(xPos, yPos, zPos);
		//note: we add 0.2f in x-axis due to vertex locations 
		//of cube's square face not equal with that of drawSquare()
//	    glTranslatef(0.0f, 0.1f, 0.0f);

		//TO-DO: -reverify: cause of excess cube translation when moving camera	
//		glLineWidth(2.0f);
	    glTranslatef(x, y, z);

		//TO-DO: -reverify: this if necessary
   		glTranslatef(0.0f, 0.0f, -fSideLength);

		//due to top face not drawn
		//TO-DO: -reverify: if we do not add top face 
		//added due to inverted z-axis based on position of vertices 
		glRotatef(180, 0.0f, 0.0f, 1.0f);
		//added by Mike, 20201122
		//added due to inverted x-axis based on position of vertices 
		glRotatef(180, 1.0f, 0.0f, 0.0f);

		
		//TO-DO: -update: vertex locations
		
		//added by Mike, 20201114
//		glDepthFunc(GL_ALWAYS);
//		glEnable(GL_DEPTH_TEST);	
		//removed by Mike, 20201114		
/*
		// Draw lines antialiased
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/
		//removed by Mike, 20201114		
		// Draw black wireframe version of geometry
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glEnable(GL_BLEND);

		//TO-DO: -reverify: this due to wireframe still drawn with cube
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

/*		//removed by Mike, 20201114
		//added by Mike, 20201114
		glDepthFunc(GL_LEQUAL);

		glLineWidth(2.0f);

		glEnable( GL_POLYGON_OFFSET_FILL );
        glPolygonOffset( 1.0, 1.0 ); //3.0, 1.0 );	
*/		

		//removed by Mike, 20201123
//		glLineWidth(2.0f);
//		glLineWidth(1.0f);
//		glDisable(GL_LINE_WIDTH);
//		glLineWidth(0.0f);
		
		//edited by Mike, 20201123		
//		glColor3f(0.0f,1.0f,0.0f);

		glBegin(GL_QUADS);
			//note: inverted y-axis; top face becomes bottom face
			//counter clockwise
			// top face		
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, 0.0f, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);

			//TO-DO: -update: this
/*
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-fSideLength, 0.0f, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, 0.0f);
*/

			//counter clockwise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, -fSideLength, 0.0f);


/*			//edited by Mike, 20201122
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(0.0f, 0.0f, -fSideLength);
*/			

	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(0.0f, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f, -fSideLength);
			
			//edited by Mike, 2020114
			//vertices drawn clock-wise

/*			//edited by Mike, 20201122
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/
	        glTexCoord2f(tx, ty);
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

/*
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
*/
/*			//edited by Mike, 20201122
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/
/*
			//counter clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
*/

/*
			//TO-DO: -reverify due to not drawn
			//clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/

/*			//edited by Mike, 20201123
			//note: y-axis inverted
			// bottom face becomes top face 		
			//set y to be at origin, i.e. 0.0f
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f, -fSideLength);
*/

/* 			//note: use technique +0.5f to create effect, e.g. dishevelled leaves of tree
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f+0.5f, 0.0f, 0.0f+0.5f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength+0.5f, 0.0f, 0.0f+0.5f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength+0.5f, 0.0f, -fSideLength+0.5f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f+0.5f, 0.0f, -fSideLength+0.5f);
*/

			//edited by Mike, 20201114
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/
			//TO-DO: -reverify: disable BackFaceCulling 
			//+updated: to draw vertices clockwise due to back face not drawn
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/

/*			//edited by Mike, 20201122
			//draw vertices clockwise
			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
*/

			//note: inverted z-axis; back face becomes front face
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(0.0f, -fSideLength, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

		glEnd();
		
/*		//removed by Mike, 20201114		
		//added by Mike, 20201114
		glDisable( GL_POLYGON_OFFSET_FILL );
*/

		//added by Mike, 20201114; removed by Mike, 2020114
//		glDepthFunc(GL_LESS);

	glPopMatrix();
}

