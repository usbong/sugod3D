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
 * @date created: 20201010
 * @date updated: 20220628; from 20210402
 * @website address: http://www.usbong.ph      
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
/*
 * This program demonstrates how to render
 * a simple heads-up display.  It uses a
 * font texture to display the text.
 *
 * Eric Vidal
 */

//#include <SDL.h>

//added by Mike, 20201010
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
#include <stdlib.h>

//edited by Mike, 20201011
//#include <string.h>
#include <string>

//added by Mike, 20201011
#include <iostream>

/*****************************************************************************/

/* texture loading */

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

GLboolean test_pow2(GLushort i)
{
    while (i % 2 == 0)
        i /= 2;
    if (i == 1)
        return GL_TRUE;
    else
        return GL_FALSE;
}

//edited by Mike, 20201010
void load_tga(char *filename)
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

/*****************************************************************************/

/* text drawing */

//edited by Mike, 2020117
//void draw_char(GLfloat x, GLfloat y, char c)
void draw_char(GLfloat x, GLfloat y, GLfloat z, char c)
{
	//edited by Mike, 20201117
//    GLfloat tx, ty;
    GLfloat tx, ty, tz;

    /* check if the character is valid */
    if (c < ' ' || c > '~')
        return;

    /* subtract 32, since the first character in the font texture
     * is the space (ascii value 32) */
    c = c - 32;

    /* determine texture coordinates; this assumes that each character
     * in the font texture has a width-height ratio of 10:16 (see the
     * font.tga file to understand what I mean) */
    tx = c % 12 * 0.078125f;
    ty = 0.875f - (c / 12 * 0.125f);
    //added by Mike, 20201117
//    tz = 0.875f - (c / 12 * 0.125f);

	//edited by Mike, 20201012
	//to make anchor/origin/reference point start at top-left
/*//removed by Mike, 20210402
	glTranslatef(0.0f, 0.1f, 0.0f);   
*/	
	glColor3f(1.0f, 1.0f, 1.0f); //set to default, i.e. white
    //glColor3f(0.0f, 0.0f, 0.0f); //set to default, i.e. black
	
	//edited by Mike, 20201012
/*
	  //1x1 box
	  glVertex2f(0.0f, 0.0f);    // x, y
      glVertex2f( 0.0f, -0.1f);
      glVertex2f( 0.1f,  -0.1f);
      glVertex2f(0.1f,  0.0f);
*/
	//edited by Mike, 20201117; added by Mike, 20210402

	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glTexCoord2f(tx, ty);
        glVertex3f(x, y, 0.0f);
        glTexCoord2f(tx + 0.078125f, ty);
//        glVertex3f(x + 10.0f, y, 0.0f);
      	glVertex3f(x+0.1f, y, 0.0f);      
        glTexCoord2f(tx + 0.078125f, ty + 0.125f);
        //glVertex3f(x + 10.0f, y + 16.0f, 0.0f);
      	//glVertex3f(x+0.1f, y+0.16f, 0.0f);              
      	//glVertex3f(x+0.1f, y+0.16f, 0.0f);              
      	glVertex3f(x+0.1f, y-0.16f, 0.0f);              
//      	glVertex3f(x, y+0.16f, 0.0f);      
		glTexCoord2f(tx, ty + 0.125f);
        //glVertex3f(x, y + 16.0f, 0.0f);
      	//glVertex3f(x, y+0.16f, 0.0f);      
      	glVertex3f(x, y-0.16f, 0.0f);      
//      	glVertex3f(x+0.1f, y+0.16f, 0.0f);              
   glEnd();        
/*   //removed by Mike, 20210402
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glTexCoord2f(tx, ty);
        glVertex3f(x, y, 0.0f);
        glTexCoord2f(tx + 0.078125f, ty);
      	glVertex3f(x+0.1f, y, 0.0f);      
        glTexCoord2f(tx + 0.078125f, ty + 0.125f);
      	glVertex3f(x+0.1f, y-0.16f, 0.0f);              
		glTexCoord2f(tx, ty + 0.125f);
      	glVertex3f(x, y-0.16f, 0.0f);      
   glEnd();        
*/
}

//edited by Mike, 2020117
//void draw_string(GLfloat x, GLfloat y, char *string)
void draw_string(GLfloat x, GLfloat y, GLfloat z, char *string)
{

    GLfloat origX=x;
    while (string[0] != 0)
    {

		//TO-DO: -update: this
        //added by Mike, Feb14,2007
		if (string[0]=='\n') {
			y -= 0.1f;//15.0f;
			x=origX-0.1f;//-10.0f;			
    	}
        

        glPushMatrix();
        	//removed by Mike, 20201010
            //make font larger, added by Mike, Feb28,2007
//            glScalef(2.0f, 2.0f, 2.0f);//1.5f, 1.5f, 1.5f);

//            glScalef(0.5f, 0.5f, 0.5f);
				//edited by Mike, 2020117
//            draw_char(x, y, string[0]);
            draw_char(x, y, z, string[0]);
    	glPopMatrix();

        
        /* advance 10 pixels after each character */
//TO-DO: -update: this
//        x += 10.0f;
        x += 0.1f;

        /* go to the next character in the string */
        string++;
    }
}

void setupFont(int myFontTextureObject)
{
	//removed by Mike, 20201010
	//due to blank output
    //glEnable(GL_DEPTH_TEST);

    /* select texture 1 */
    glBindTexture(GL_TEXTURE_2D, myFontTextureObject);

    /* create OpenGL texture out of targa file */
	//edited by Mike, 20210420
    load_tga("textures/font.tga");
//    load_tga("textures/concrete.tga");
    
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

    /* set background color to bluish /* set texture parameters */
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

	//removed by Mike, 20201012
    /* set background color to bluish to demonstrate font transparency */
//    glClearColor(0.0f, 0.0f, 0.25f, 1.0f); /* to demonstrate font transparency */

}
