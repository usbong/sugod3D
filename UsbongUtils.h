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
 * @date created: 20201210
 * @date updated: 20220628; from 20210208
 * @website address: http://www.usbong.ph
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//TO-DO: -update: this

/* //removed by Mike, 20201210
//added by Mike, 20201130 
#include "CTargaImage.h"
#include "OpenGLCanvas.h"
#include "MyDynamicObject.h"
//added by Mike, 20201019
#include "PolygonUtils.h"
*/
	
class UsbongUtils
{
private:		
public:
	~UsbongUtils(); //note: add "~" for constructor without any input parameter
/*
	Pilot(float xPos, float yPos, float zPos,int windowWidth,int windowHeight);
	~Pilot();
*/	
	//edited by Mike, 20210208
    void read(char *filename);
//    FILE read(char *filename);
// char* read(char *filename);
//char read(char *filename);
// char[] read(char *filename);

};
