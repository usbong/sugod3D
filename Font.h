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
 * @date updated: 20220628; from 20201117
 * @website address: http://www.usbong.ph       
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
#include <stdlib.h> 

//edited by Mike, 20201011
//#include <string.h>
#include <string>
 
void setupFont(int myFontTextureObject);
//edited by Mike, 20201017
//void draw_string(GLfloat x, GLfloat y, char *string);
//void draw_char(GLfloat x, GLfloat y, char c);
void draw_string(GLfloat x, GLfloat y, GLfloat z, char *string);
void draw_char(GLfloat x, GLfloat y, GLfloat z, char c);

//void draw_string(GLfloat x, GLfloat y, std::string string);
