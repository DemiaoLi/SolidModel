//
//  draw.h
//  solidModel
//
//  Created by Lidemiao on 2023/10/17.
//


#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef _WIN32
#define __stdcall
#endif

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "EulerOperations.h"

using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;
using std::ends;

#ifndef CALLBACK
#define CALLBACK
#endif



// CALLBACK functions for GLU_TESS ////////////////////////////////////////////
// NOTE: must be declared with CALLBACK directive
void CALLBACK tessBeginCB(GLenum which);
void CALLBACK tessEndCB();
void CALLBACK tessErrorCB(GLenum errorCode);
void CALLBACK tessVertexCB(const GLvoid *data);
void CALLBACK tessVertexCB2(const GLvoid *data);
void CALLBACK tessCombineCB(const GLdouble newVertex[3], const GLdouble *neighborVertex[4],
                            const GLfloat neighborWeight[4], GLdouble **outData);



// GLUT CALLBACK functions ////////////////////////////////////////////////////
void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);
void idleCB();
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);



// function declarations //////////////////////////////////////////////////////
void initGL();
int  initGLUT(int argc, char **argv);
bool initSharedMem();
void clearSharedMem();
void initLights();
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void drawString(const char *str, int x, int y, float color[4], void *font);
void drawString3D(const char *str, float pos[3], float color[4], void *font);
void showInfo();
const char* getPrimitiveType(GLenum type);
GLuint tessellate1();
GLuint tessellate1_tmp();
GLuint tessellate2();
GLuint tessellate3();
GLuint tessellate11(Solid* smodel);

void drawSolidModel(int argc, char **argv, Solid* smodel, Solid *smodel1,Solid *smodel2);

/*
#ifndef draw_h
#define draw_h

#pragma once
#include "EulerOperations.h"
#define CALLBACK    __stdcall

void InitEnvironment();

//键盘操作，wasd改变视角
void KeyBoards(unsigned char key, int x, int y);

//滚轮操作，zoom in/out
void MouseWheel(int button, int dir, int x, int y);

void Display();
void Draw(int argc, char** argv, Solid* firstSolid);


#endif
*/
