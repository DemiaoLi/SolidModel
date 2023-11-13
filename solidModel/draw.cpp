//
//  draw.cpp
//  solidModel
//
//  Created by Lidemiao on 2023/10/17.
//

#include "draw.h"

// global variables ///////////////////////////////////////////////////////////
void *font = GLUT_BITMAP_8_BY_13;
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;
int drawMode = 0;
GLuint listId1, listId2, listId3;       // IDs of display lists
GLdouble vertices[64][6];               // arrary to store newly created vertices (x,y,z,r,g,b) by combine callback
int vertexIndex = 0;                    // array index for above array incremented inside combine callback

// DEBUG //
stringstream ss;

///////////////////////////////////////////////////////////////////////////////
// create a tessellation object and compile a quad into a display list
///////////////////////////////////////////////////////////////////////////////
GLuint tessellate1_tmp()
{
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;  // failed to create tessellation object, return 0

    // define concave quad data (vertices only)
    //  0    2
    //  \ \/ /
    //   \3 /
    //    \/
    //    1
    GLdouble quad1[4][3] = { {-1,3,0}, {0,0,0}, {1,3,0}, {0,2,0} };

    // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);

    // tessellate and compile a concave quad into display list
    // gluTessVertex() takes 3 params: tess object, pointer to vertex coords,
    // and pointer to vertex data to be passed to vertex callback.
    // The second param is used only to perform tessellation, and the third
    // param is the actual vertex data to draw. It is usually same as the second
    // param, but It can be more than vertex coord, for example, color, normal
    // and UV coords which are needed for actual drawing.
    // Here, we are looking at only vertex coods, so the 2nd and 3rd params are
    // pointing same address.
    glNewList(id, GL_COMPILE);
    glColor3f(1,1,1);
    gluTessBeginPolygon(tess, 0);                   // with NULL data
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[0], quad1[0]);
            gluTessVertex(tess, quad1[1], quad1[1]);
            gluTessVertex(tess, quad1[2], quad1[2]);
            gluTessVertex(tess, quad1[3], quad1[3]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    glEndList();

    gluDeleteTess(tess);        // delete after tessellation

    // DEBUG //
    // print out actual GL calls that are performed
    cout << endl;
    cout << "1. Concave Quad\n";
    cout << "===============\n";
    cout << ss.str().c_str() << endl;
    ss.str("");                     // clear string buffer

    return id;      // return handle ID of a display list
}


///////////////////////////////////////////////////////////////////////////////
// create a tessellation object and compile a quad into a display list
///////////////////////////////////////////////////////////////////////////////
GLuint tessellate1()
{
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;  // failed to create tessellation object, return 0

    // define concave quad data (vertices only)
    //  0    2
    //  \ \/ /
    //   \3 /
    //    \/
    //    1
    GLdouble quad1[24][3] = {
        //{-1.0, 0.5, 2.0}, {1.0, 0.5, 2.0}, {-1,-0.5,2.0}, {1,-0.5,2.0}
        {-1,1,2}, {-1,-1,2}, {1,-1,2}, { 1,1,2},
        {-1,1,-2}, {1,1,-2}, {1,-1,-2}, { -1,-1,-2},
        
        {-1,1,-2}, {-1,1,2}, {1,1,2}, { 1,1,-2},
        {-1,-1,-2}, {1,-1,-2}, {1,-1,2}, { -1,-1,2},
        
        {1,1,-2}, {1,1,2}, {1,-1,2}, { 1,-1,-2},
        {-1,-1,-2}, {-1,-1,2}, {-1,1,2}, { -1,1,-2}
    };

    // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);

    // tessellate and compile a concave quad into display list
    // gluTessVertex() takes 3 params: tess object, pointer to vertex coords,
    // and pointer to vertex data to be passed to vertex callback.
    // The second param is used only to perform tessellation, and the third
    // param is the actual vertex data to draw. It is usually same as the second
    // param, but It can be more than vertex coord, for example, color, normal
    // and UV coords which are needed for actual drawing.
    // Here, we are looking at only vertex coods, so the 2nd and 3rd params are
    // pointing same address.
    glNewList(id, GL_COMPILE);
    glColor3f(1,1,1);
    
    gluTessBeginPolygon(tess, 0);                   // with NULL data
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[0], quad1[0]);
            gluTessVertex(tess, quad1[1], quad1[1]);
            gluTessVertex(tess, quad1[2], quad1[2]);
            gluTessVertex(tess, quad1[3], quad1[3]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[4], quad1[4]);
            gluTessVertex(tess, quad1[5], quad1[5]);
            gluTessVertex(tess, quad1[6], quad1[6]);
            gluTessVertex(tess, quad1[7], quad1[7]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    glColor3f(0,1,1);
    gluTessBeginPolygon(tess, 0);                   // with NULL data
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[8], quad1[8]);
            gluTessVertex(tess, quad1[9], quad1[9]);
            gluTessVertex(tess, quad1[10], quad1[10]);
            gluTessVertex(tess, quad1[11], quad1[11]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[12], quad1[12]);
            gluTessVertex(tess, quad1[13], quad1[13]);
            gluTessVertex(tess, quad1[14], quad1[14]);
            gluTessVertex(tess, quad1[15], quad1[15]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    glColor3f(1,0,1);
    gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[16], quad1[16]);
            gluTessVertex(tess, quad1[17], quad1[17]);
            gluTessVertex(tess, quad1[18], quad1[18]);
            gluTessVertex(tess, quad1[19], quad1[19]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[20], quad1[20]);
            gluTessVertex(tess, quad1[21], quad1[21]);
            gluTessVertex(tess, quad1[22], quad1[22]);
            gluTessVertex(tess, quad1[23], quad1[23]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    glEndList();
    gluDeleteTess(tess);        // delete after tessellation

    // DEBUG //
    // print out actual GL calls that are performed
    cout << endl;
    cout << "1. Concave Quad\n";
    cout << "===============\n";
    cout << ss.str().c_str() << endl;
    ss.str("");                     // clear string buffer

    return id;      // return handle ID of a display list
}



///////////////////////////////////////////////////////////////////////////////
// tessellate a polygon with a hole and compile it into a display list
///////////////////////////////////////////////////////////////////////////////
GLuint tessellate2()
{
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;         // failed to create tessellation object, return 0

    // define concave quad with a hole
    //  0--------3
    //  | 4----7 |
    //  | |    | |
    //  | 5----6 |
    //  1--------2
    GLdouble quad2[8][3] = { {-2,3,0}, {-2,0,0}, {2,0,0}, { 2,3,0},
                             {-1,2,0}, {-1,1,0}, {1,1,0}, { 1,2,0} };

    // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (__stdcall*)(void))tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (__stdcall*)())tessVertexCB);

    // tessellate and compile a concave quad into display list
    glNewList(id, GL_COMPILE);
    glColor3f(1,1,1);
    gluTessBeginPolygon(tess, 0);                       // with NULL data
        gluTessBeginContour(tess);                      // outer quad
            gluTessVertex(tess, quad2[0], quad2[0]);
            gluTessVertex(tess, quad2[1], quad2[1]);
            gluTessVertex(tess, quad2[2], quad2[2]);
            gluTessVertex(tess, quad2[3], quad2[3]);
        gluTessEndContour(tess);
        gluTessBeginContour(tess);                      // inner quad (hole)
            gluTessVertex(tess, quad2[4], quad2[4]);
            gluTessVertex(tess, quad2[5], quad2[5]);
            gluTessVertex(tess, quad2[6], quad2[6]);
            gluTessVertex(tess, quad2[7], quad2[7]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    glEndList();

    gluDeleteTess(tess);        // delete after tessellation

    // DEBUG //
    // print out actual GL calls that are performed
    cout << endl;
    cout << "2. Quad with a Hole\n";
    cout << "===================\n";
    cout << ss.str().c_str() << endl;
    ss.str("");                     // clear string buffer

    return id;      // return handle ID of a display list
}



///////////////////////////////////////////////////////////////////////////////
// tessellate a self-intersecting polygon and compile it into a display list
// Note that tessellator will find out the self-intersecting vertex where
// two edge lines are met, and pass it to your combine callback function.
// The combine callback must store the vertex coords into local memory in
// your application and also handle other vertex data, such as color, UVs.
///////////////////////////////////////////////////////////////////////////////
GLuint tessellate3()
{
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;  // failed to create tessellation object, return 0

    // define self-intersecting star shape (with color)
    //      0
    //     / \
    //3---+---+---2
    //  \ |   | /
    //   \|   |/
    //    +   +
    //    |\ /|
    //    | + |
    //    |/ \|
    //    1   4
    GLdouble star[5][6] = { { 0.0, 3.0, 0,  1, 0, 0},       // 0: x,y,z,r,g,b
                            {-1.0, 0.0, 0,  0, 1, 0},       // 1:
                            { 1.6, 1.9, 0,  1, 0, 1},       // 2:
                            {-1.6, 1.9, 0,  1, 1, 0},       // 3:
                            { 1.0, 0.0, 0,  0, 0, 1} };     // 4:

    // register callback functions
    // This polygon is self-intersecting, so GLU_TESS_COMBINE callback function
    // must be registered. The combine callback will process the intersecting vertices.
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (__stdcall*)(void))tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (__stdcall*)(void))tessVertexCB2);
    gluTessCallback(tess, GLU_TESS_COMBINE, (void (__stdcall*)(void))tessCombineCB);

    // tessellate and compile a concave quad into display list
    // Pay attention to winding rules if multiple contours are overlapped.
    // The winding rules determine which parts of polygon will be filled(interior)
    // or not filled(exterior). For each enclosed region partitioned by multiple
    // contours, tessellator assigns a winding number to the region by using
    // given winding rule. The default winding rule is GLU_TESS_WINDING_ODD,
    // but, here we are using non-zero winding rule to fill the middle area.
    // BTW, the middle region will not be filled with the odd winding rule.
    gluTessProperty(tess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO);
    glNewList(id, GL_COMPILE);
    gluTessBeginPolygon(tess, 0);                   // with NULL data
        gluTessBeginContour(tess);
            gluTessVertex(tess, star[0], star[0]);
            gluTessVertex(tess, star[1], star[1]);
            gluTessVertex(tess, star[2], star[2]);
            gluTessVertex(tess, star[3], star[3]);
            gluTessVertex(tess, star[4], star[4]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    glEndList();

    gluDeleteTess(tess);        // safe to delete after tessellation

    // DEBUG //
    // print out actual GL calls that are performed
    cout << endl;
    cout << "3. Self-Intersect Star";
    cout << "======================\n";
    cout << ss.str().c_str() << endl;
    cout << "Tessellator creates " << vertexIndex << " new intersecting vertices\n";
    ss.str("");                     // clear string buffer

    return id;      // return handle ID of a display list
}



///////////////////////////////////////////////////////////////////////////////
// convert enum of OpenGL primitive type to a string(char*)
// OpenGL supports only 10 primitive types.
///////////////////////////////////////////////////////////////////////////////
const char* getPrimitiveType(GLenum type)
{
    switch(type)
    {
    case 0x0000:
        return "GL_POINTS";
        break;
    case 0x0001:
        return "GL_LINES";
        break;
    case 0x0002:
        return "GL_LINE_LOOP";
        break;
    case 0x0003:
        return "GL_LINE_STRIP";
        break;
    case 0x0004:
        return "GL_TRIANGLES";
        break;
    case 0x0005:
        return "GL_TRIANGLE_STRIP";
        break;
    case 0x0006:
        return "GL_TRIANGLE_FAN";
        break;
    case 0x0007:
        return "GL_QUADS";
        break;
    case 0x0008:
        return "GL_QUAD_STRIP";
        break;
    case 0x0009:
        return "GL_POLYGON";
        break;
    }
    return "";
}



///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char **argv)
{
    // GLUT stuff for windowing
    // initialization openGL window.
    // it is called before any other GLUT routine
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(1200, 800);               // window size

    glutInitWindowPosition(100, 100);           // window location

    // finally, create a window with openGL context
    // Window will not displayed until glutMainLoop() is called
    // it returns a unique ID
    int handle = glutCreateWindow(argv[0]);     // param is the title of window

    // register GLUT callback functions
    glutDisplayFunc(displayCB);
    glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
    //glutIdleFunc(idleCB);                       // redraw only every given millisec
    glutReshapeFunc(reshapeCB);
    glutKeyboardFunc(keyboardCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);

    return handle;
}



///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    initLights();
    setCamera(6, 4, 6, 0, 0, 0);
}



///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void drawString3D(const char *str, float pos[3], float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glColor4fv(color);          // set text color
    glRasterPos3fv(pos);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
    mouseLeftDown = mouseRightDown = false;
    return true;
}



///////////////////////////////////////////////////////////////////////////////
// clean up shared memory
///////////////////////////////////////////////////////////////////////////////
void clearSharedMem()
{
}



///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void initLights()
{
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}



///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}



///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void showInfo()
{
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);     // switch to projection matrix
    glPushMatrix();                  // save current projection matrix
    glLoadIdentity();                // reset projection matrix
    gluOrtho2D(0, 400, 0, 200);  // set to orthogonal projection

    float color[4] = {1, 1, 1, 1};

    stringstream ss;
    ss << std::fixed << std::setprecision(3);

    if(drawMode == 0)
        ss << "Draw Mode: Fill" << ends;
    else if(drawMode == 1)
        ss << "Draw Mode: Wireframe" << ends;
    else
        ss << "Draw Mode: Points" << ends;
    drawString(ss.str().c_str(), 1, 186, color, font);
    ss.str("");

    ss << "Press 'D' to switch drawing mode." << ends;
    drawString(ss.str().c_str(), 1, 2, color, font);
    ss.str("");

    // unset floating format
    ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}



//=============================================================================
// CALLBACKS
//=============================================================================

void displayCB()
{
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // save the initial ModelView matrix before modifying ModelView matrix
    glPushMatrix();

    // tramsform camera
    glTranslatef(0, 0, cameraDistance);
    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
    glRotatef(cameraAngleY, 0, 1, 0);   // heading

    // draw meshes
    glTranslatef(-4, -1.5f,0);
    glCallList(listId1);

    glTranslatef(4,0,0);
    glCallList(listId2);

    glTranslatef(4,0,0);
    glCallList(listId3);

    // draw info messages
    showInfo();

    glPopMatrix();

    glutSwapBuffers();
}


void reshapeCB(int w, int h)
{
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // set perspective viewing frustum
    float aspectRatio = (float)w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-aspectRatio, aspectRatio, -1, 1, 1, 100);
    gluPerspective(60.0f, (float)(w)/h, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
}


void timerCB(int millisec)
{
    glutTimerFunc(millisec, timerCB, millisec);
    glutPostRedisplay();
}


void idleCB()
{
    glutPostRedisplay();
}


void keyboardCB(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27: // ESCAPE
        clearSharedMem();
        exit(0);
        break;

    case ' ':
        break;

    case 'd': // switch rendering modes (fill -> wire -> point)
    case 'D':
        drawMode = ++drawMode % 3;
        if(drawMode == 0)        // fill mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
        }
        else if(drawMode == 1)  // wireframe mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        else                    // point mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        break;

    default:
        ;
    }

    glutPostRedisplay();
}


void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}


void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    //glutPostRedisplay();
}



///////////////////////////////////////////////////////////////////////////////
// GLU_TESS CALLBACKS
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessBeginCB(GLenum which)
{
    glBegin(which);

    // DEBUG //
    ss << "glBegin(" << getPrimitiveType(which) << ");\n";
}



void CALLBACK tessEndCB()
{
    glEnd();

    // DEBUG //
    ss << "glEnd();\n";
}



void CALLBACK tessVertexCB(const GLvoid *data)
{
    // cast back to double type
    const GLdouble *ptr = (const GLdouble*)data;

    glVertex3dv(ptr);

    // DEBUG //
    ss << "  glVertex3d(" << *ptr << ", " << *(ptr+1) << ", " << *(ptr+2) << ");\n";
}



///////////////////////////////////////////////////////////////////////////////
// draw a vertex with color
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessVertexCB2(const GLvoid *data)
{
    // cast back to double type
    const GLdouble *ptr = (const GLdouble*)data;

    glColor3dv(ptr+3);
    glVertex3dv(ptr);

    // DEBUG //
    ss << "  glColor3d(" << *(ptr+3) << ", " << *(ptr+4) << ", " << *(ptr+5) << ");\n";
    ss << "  glVertex3d(" << *ptr << ", " << *(ptr+1) << ", " << *(ptr+2) << ");\n";
}



///////////////////////////////////////////////////////////////////////////////
// Combine callback is used to create a new vertex where edges intersect.
// In this function, copy the vertex data into local array and compute the
// color of the vertex. And send it back to tessellator, so tessellator pass it
// to vertex callback function.
//
// newVertex: the intersect point which tessellator creates for us
// neighborVertex[4]: 4 neighbor vertices to cause intersection (given from 3rd param of gluTessVertex()
// neighborWeight[4]: 4 interpolation weights of 4 neighbor vertices
// outData: the vertex data to return to tessellator
///////////////////////////////////////////////////////////////////////////////
void CALLBACK tessCombineCB(const GLdouble newVertex[3], const GLdouble *neighborVertex[4],
                            const GLfloat neighborWeight[4], GLdouble **outData)
{
    // copy new intersect vertex to local array
    // Because newVertex is temporal and cannot be hold by tessellator until next
    // vertex callback called, it must be copied to the safe place in the app.
    // Once gluTessEndPolygon() called, then you can safly deallocate the array.
    vertices[vertexIndex][0] = newVertex[0];
    vertices[vertexIndex][1] = newVertex[1];
    vertices[vertexIndex][2] = newVertex[2];

    // compute vertex color with given weights and colors of 4 neighbors
    // the neighborVertex[4] must hold required info, in this case, color.
    // neighborVertex was actually the third param of gluTessVertex() and is
    // passed into here to compute the color of the intersect vertex.
    vertices[vertexIndex][3] = neighborWeight[0] * neighborVertex[0][3] +   // red
                               neighborWeight[1] * neighborVertex[1][3] +
                               neighborWeight[2] * neighborVertex[2][3] +
                               neighborWeight[3] * neighborVertex[3][3];
    vertices[vertexIndex][4] = neighborWeight[0] * neighborVertex[0][4] +   // green
                               neighborWeight[1] * neighborVertex[1][4] +
                               neighborWeight[2] * neighborVertex[2][4] +
                               neighborWeight[3] * neighborVertex[3][4];
    vertices[vertexIndex][5] = neighborWeight[0] * neighborVertex[0][5] +   // blue
                               neighborWeight[1] * neighborVertex[1][5] +
                               neighborWeight[2] * neighborVertex[2][5] +
                               neighborWeight[3] * neighborVertex[3][5];


    // return output data (vertex coords and others)
    *outData = vertices[vertexIndex];   // assign the address of new intersect vertex

    ++vertexIndex;  // increase index for next vertex
}



void CALLBACK tessErrorCB(GLenum errorCode)
{
    const GLubyte *errorStr;

    errorStr = gluErrorString(errorCode);
    cerr << "[ERROR]: " << errorStr << endl;
}

///////////////////////////////////////////////////////////////////////////////
// create a tessellation object and compile a quad into a display list
///////////////////////////////////////////////////////////////////////////////
GLuint tessellate11(Solid* smodel)
{
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;  // failed to create tessellation object, return 0

    // define concave quad data (vertices only)
    //  0    2
    //  \ \/ /
    //   \3 /
    //    \/
    //    1
    GLdouble quad1[24][3] = {
        //{-1.0, 0.5, 2.0}, {1.0, 0.5, 2.0}, {-1,-0.5,2.0}, {1,-0.5,2.0}
        {-1,1,2}, {-1,-1,2}, {1,-1,2}, { 1,1,2},
        {-1,1,-2}, {1,1,-2}, {1,-1,-2}, { -1,-1,-2},
        
        {-1,1,-2}, {-1,1,2}, {1,1,2}, { 1,1,-2},
        {-1,-1,-2}, {1,-1,-2}, {1,-1,2}, { -1,-1,2},
        
        {1,1,-2}, {1,1,2}, {1,-1,2}, { 1,-1,-2},
        {-1,-1,-2}, {-1,-1,2}, {-1,1,2}, { -1,1,-2}
    };

    // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (CALLBACK *)())tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (CALLBACK *)())tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (CALLBACK *)())tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (CALLBACK *)())tessVertexCB);

    // tessellate and compile a concave quad into display list
    // gluTessVertex() takes 3 params: tess object, pointer to vertex coords,
    // and pointer to vertex data to be passed to vertex callback.
    // The second param is used only to perform tessellation, and the third
    // param is the actual vertex data to draw. It is usually same as the second
    // param, but It can be more than vertex coord, for example, color, normal
    // and UV coords which are needed for actual drawing.
    // Here, we are looking at only vertex coods, so the 2nd and 3rd params are
    // pointing same address.
    
    srand(time(nullptr));//设置随机数种子，使每次产生的随机序列不同
    
    GLdouble* pos;
    
    glNewList(id, GL_COMPILE);
    
    
    for(Face* f=smodel->solidFace;f;f=f->nextFace){
        double R = rand() % (101) / double(100);
        double G = rand() % (101) / double(100);
        double B = rand() % (101) / double(100);
        glColor3f(1-R,1-G,1-B);
        gluTessBeginPolygon(tess, 0);
        for(Loop* l=f->faceLoop;l;l=l->nextLoop){
            gluTessBeginContour(tess);
            Vertex *sv=l->loopHalfEdge->startVertex;
            pos = new GLdouble[3]{ sv->position.x, sv->position.y, sv->position.z };
            gluTessVertex(tess, pos, pos);
            for(HalfEdge* hf=l->loopHalfEdge;hf->endVertex!=sv;hf=hf->nextHfEdge){
                pos = new GLdouble[3]{ hf->endVertex->position.x, hf->endVertex->position.y, hf->endVertex->position.z };
                gluTessVertex(tess, pos, pos);
            }
            gluTessEndContour(tess);
        }
        gluTessEndPolygon(tess);
    }
    glEndList();
    gluDeleteTess(tess);
    
    /*
    glNewList(id, GL_COMPILE);
    glColor3f(1,1,1);
    
    gluTessBeginPolygon(tess, 0);                   // with NULL data
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[0], quad1[0]);
            gluTessVertex(tess, quad1[1], quad1[1]);
            gluTessVertex(tess, quad1[2], quad1[2]);
            gluTessVertex(tess, quad1[3], quad1[3]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[4], quad1[4]);
            gluTessVertex(tess, quad1[5], quad1[5]);
            gluTessVertex(tess, quad1[6], quad1[6]);
            gluTessVertex(tess, quad1[7], quad1[7]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    glColor3f(0,1,1);
    gluTessBeginPolygon(tess, 0);                   // with NULL data
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[8], quad1[8]);
            gluTessVertex(tess, quad1[9], quad1[9]);
            gluTessVertex(tess, quad1[10], quad1[10]);
            gluTessVertex(tess, quad1[11], quad1[11]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[12], quad1[12]);
            gluTessVertex(tess, quad1[13], quad1[13]);
            gluTessVertex(tess, quad1[14], quad1[14]);
            gluTessVertex(tess, quad1[15], quad1[15]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    glColor3f(1,0,1);
    gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[16], quad1[16]);
            gluTessVertex(tess, quad1[17], quad1[17]);
            gluTessVertex(tess, quad1[18], quad1[18]);
            gluTessVertex(tess, quad1[19], quad1[19]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    gluTessBeginPolygon(tess, 0);
        gluTessBeginContour(tess);
            gluTessVertex(tess, quad1[20], quad1[20]);
            gluTessVertex(tess, quad1[21], quad1[21]);
            gluTessVertex(tess, quad1[22], quad1[22]);
            gluTessVertex(tess, quad1[23], quad1[23]);
        gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    
    glEndList();
    gluDeleteTess(tess);        // delete after tessellation
     */

    // DEBUG //
    // print out actual GL calls that are performed
    cout << endl;
    cout << "1. Concave Quad\n";
    cout << "===============\n";
    cout << ss.str().c_str() << endl;
    ss.str("");                     // clear string buffer

    return id;      // return handle ID of a display list
}


void drawSolidModel(int argc, char **argv, Solid* smodel, Solid *smodel1,Solid *smodel2){
    initSharedMem();

    // init GLUT and GL
    initGLUT(argc, argv);
    initGL();

    // perform tessellation and compile into display lists
    listId1 = tessellate11(smodel);    // a concave quad
    if(smodel1) listId2 = tessellate11(smodel1);    // a quad with a hole in it
    if(smodel2) listId3 = tessellate11(smodel2);    // a self-intersecting star


    // the last GLUT call (LOOP)
    // window will be shown and display callback is triggered by events
    // NOTE: this call never return main().
    glutMainLoop(); /* Start GLUT event-processing loop */
}
