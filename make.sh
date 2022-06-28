#!/bin/bash

# Copyright 2020~2022 SYSON, MICHAEL B.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
#
#
# Usbong SUGOD 3D: Auto-guided CAMERA movement
# C++ Computer Language and OpenGL
#
# Compile and Link Multiple Source Files
#
# @company: USBONG
# @author: SYSON, MICHAEL B.
# @date created: 20200930
# @last updated: 20220628; from 20210220
#
# References:
# 1) https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html;
# last accessed: 20200930
#
# 2) Usbong Automotive: Image Processing Automation

cp -r ./textures ./output/
cp -r ./input ./output/

#rm *.o

g++ -c mainLinux.cpp
g++ -c OpenGLCanvas.cpp
g++ -c MyDynamicObject.cpp
g++ -c RobotShip.cpp
g++ -c Font.cpp
g++ -c Beam.cpp
g++ -c Asteroid.cpp
g++ -c Level.cpp
g++ -c PolygonUtils.cpp
g++ -c CTargaImage.cpp
g++ -c Pilot.cpp
g++ -c UsbongUtils.cpp

#g++ -o mainOutput main.o OpenGLCanvas.o -lGL -lGLU -lglut
# edited by Mike, 20210126
# g++ -o ./output/mainOutputLinux mainLinux.o OpenGLCanvas.o MyDynamicObject.o RobotShip.o Font.o Beam.o Asteroid.o Level.o PolygonUtils.o CTargaImage.o Pilot.o UsbongUtils.o -lGL -lGLU -lglut
g++ -o ./output/UsbongSugod3DLinux mainLinux.o OpenGLCanvas.o MyDynamicObject.o RobotShip.o Font.o Beam.o Asteroid.o Level.o PolygonUtils.o CTargaImage.o Pilot.o UsbongUtils.o -lGL -lGLU -lglut

#added by Mike, 20210220
cp -r ./*.o ./objectFilesLinux/
