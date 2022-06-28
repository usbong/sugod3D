/*
 * Copyright 2021~2022 SYSON, MICHAEL B.
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
 * @date created: 20210330
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

/*
void load_0();
void load_1();
void load_2();
void load_3();
void load_4();
void load_5();
void load_6();
void load_7();
void load_8();
*/

void load_tga(char *filename);
void drawModelRobot();
void drawAsteroid(unsigned int myTextureObject);
void drawMyShip(unsigned int myTextureObject);

