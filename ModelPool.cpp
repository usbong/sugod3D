/*
 * Copyright 2018~2022 SYSON, MICHAEL B.
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
 * @date created: 20070906
 * @date updated: 20220628; from 20210330
 * @website address: http://www.usbong.ph    
 *
 * Reference:
 * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/;
 * last accessed: 20210328
 * 
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 * 2) Marikina Orthopedic Specialty Clinic (MOSC)
 * 
 * 3) Sta. Lucia Health Care Center (SLHCC)
 *
 */
 
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <stdlib.h>

#include "ModelPool.h"
float matColors[4];

//added by Mike, 20210330
//halimbawa
void load_0() {
	//float matColors[4];
	glPushMatrix();
    	
    	glTranslated(1.390414, 1.494347, 4.961707);
    	glScaled(0.831364, 1.000000, 0.352202);
    	glBegin(GL_QUADS);
    		glNormal3f(-0.676504, 0.195807, -0.709891);
    		glTexCoord2f(0.409361, 0.374674);
    		glVertex3f(-4.646430, 3.052645, -2.675513);
    		glNormal3f(-0.471358, 0.717032, -0.513443);
    		glTexCoord2f(0.354573, 0.499786);
    		glVertex3f(-3.327921, 6.105289, -2.675513);
    		glNormal3f(0.000000, 0.707083, -0.707083);
    		glTexCoord2f(0.312527, 0.499913);
    		glVertex3f(-2.323215, 6.105289, -2.675513);
    		glNormal3f(0.000000, 0.000000, -1.000000);
    		glTexCoord2f(0.312135, 0.374966);
    		glVertex3f(-2.323215, 3.052645, -2.675513);
    	glEnd();

		//...

	glPopMatrix();
}
    
//added by Mike, 20210330
//halimbawa    
//object: Cube.011_1
//right arm
void load_1() {
	//float matColors[4];
	glPushMatrix();
    
    	glTranslated(2.212117, 1.613276, 3.332175);
		glRotated(-90.000035,0,1,0);
    	glScaled(1.000000, 1.000000, 1.000000);
    	glBegin(GL_QUADS);
    		glNormal3f(0.988281, -0.097537, 0.117222);
    		glTexCoord2f(0.131051, 0.551301);
    		glVertex3f(0.701391, -3.767079, 0.350657);
    		glNormal3f(0.704520, -0.085147, 0.704520);
    		glTexCoord2f(0.174192, 0.551163);
    		glVertex3f(0.701391, -3.767081, 0.701314);
    		glNormal3f(0.000000, -0.119968, 0.992767);
    		glTexCoord2f(0.174195, 0.552152);
    		glVertex3f(0.350734, -3.767078, 0.701314);
    		glNormal3f(0.362590, -0.328043, 0.872280);
    		glTexCoord2f(0.131602, 0.738321);
    		glVertex3f(0.350734, -5.222037, 0.350653);
    	glEnd();
		
		//...
		
    	glBegin(GL_TRIANGLES);
    		glNormal3f(-0.164647, -0.421125, -0.891903);
    		glTexCoord2f(0.500485, 0.580704);
    		glVertex3f(-0.526063, 3.182699, -0.701314);
    		glNormal3f(-0.776391, 0.226112, -0.588275);
    		glTexCoord2f(0.522617, 0.770870);
    		glVertex3f(-0.701391, 4.670173, -0.701314);
    		glNormal3f(-0.144688, 0.400128, -0.904935);
    		glTexCoord2f(0.479586, 0.808319);
    		glVertex3f(-0.350734, 4.961911, -0.701314);
    	glEnd();

	glPopMatrix();
}


//...

//added by Mike, 202103030
//halimbawa
void drawModelRobot() {
    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 1); //body
    	load_0();	//object: Cube.005
    	glBindTexture(GL_TEXTURE_2D, 2); //arm
    	load_1();	//object: Cube.011
    	glBindTexture(GL_TEXTURE_2D, 3); //arm
    	load_2();	//object: Cube.008
    	glBindTexture(GL_TEXTURE_2D, 4); //tail
    	load_3();	//object: Cube.001
    	glBindTexture(GL_TEXTURE_2D, 5); //cockpit
    	load_4();	//object: Cube.003
    	glBindTexture(GL_TEXTURE_2D, 6); //head
    	load_5();	//object: Cube.009
    	glBindTexture(GL_TEXTURE_2D, 7); //gun
    	load_6();	//object: Cube.006
    	glBindTexture(GL_TEXTURE_2D, 8); //wings
    	load_7();	//object: Cube.002
    	glBindTexture(GL_TEXTURE_2D, 9); //legs
    	load_8();	//object: Cube
    	
    	/* unselect and disable textures */
        glBindTexture(GL_TEXTURE_2D, 0);
    	glDisable(GL_TEXTURE_2D);
}
/*
void setTexturedObject(unsigned int argv[])
{
     int argLength = argv.length;
     int i;
     for (i=0; i<argLength; i++)
     {
         myTextureObject[i]=argv[i];
     }
} 
*/
//object: Asteroid_0
void drawAsteroid(unsigned int myTextureObject) {
	/* select and enable texture 1 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTextureObject);
         
	//float matColors[4];
	glPushMatrix();
	glTranslated(0.000000, 0.000000, 0.000000);
	glScaled(3.000000, 3.000000, 3.000000);
	matColors[0] = 0.950000;
	matColors[1] = 0.950000;
	matColors[2] = 0.950000;
	matColors[3] = 1.000000;
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,matColors);
	matColors[0] = 1.000000;
	matColors[1] = 1.000000;
	matColors[2] = 1.000000;
	matColors[3] = 1.000000;
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,matColors);
	glBegin(GL_QUADS);
		glNormal3f(-0.275216, 0.704856, 0.653737);
		glTexCoord2f(0.202899, 0.141599);
		glVertex3f(-0.675947, 0.950547, 0.722064);
		glNormal3f(-0.300119, 0.650258, 0.697897);
		glTexCoord2f(0.211815, 0.129973);
		glVertex3f(-0.729475, 0.867927, 0.784216);
		glNormal3f(-0.221625, 0.618427, 0.753899);
		glTexCoord2f(0.227757, 0.147176);
		glVertex3f(-0.583336, 0.836501, 0.858471);
		glNormal3f(-0.228339, 0.704947, 0.671468);
		glTexCoord2f(0.208460, 0.156364);
		glVertex3f(-0.566638, 0.970083, 0.743137);
	glEnd();
	
	//...
	
	glPopMatrix();
	
	/* unselect and disable texture 1 */
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawMyShip(unsigned int myTextureObject)
{
     /* select and enable texture 1 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTextureObject);
    glPushMatrix();
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glScalef(0.1f, 0.1f, 0.1f);
        //glColor3f(1.0f, 1.0f, 1.0f);//default: white
    	glBegin(GL_TRIANGLE_STRIP);
    	    //note: In "glTexCoord2f(1.0, 0.0);", if 1.0 is changed to 2.0, the plane is made up of 4 images instead of just 1 whole image 
    		glTexCoord2f(1.0, 0.0); glVertex3f(10.0, -10.0, -10.0);
    		glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, -10.0);
    		glTexCoord2f(1.0, 1.0);	glVertex3f(10.0, -10.0, 10.0);
    		glTexCoord2f(0.0, 1.0);	glVertex3f(-10.0, -10.0, 10.0);	
    	glEnd();
    glPopMatrix();
}

