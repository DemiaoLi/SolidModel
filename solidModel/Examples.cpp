//
//  Examples.cpp
//  solidModel
//
//  Created by Lidemiao on 2023/10/19.
//

#include "Examples.h"
#include <iostream>


Solid *createZero(){
    Solid *newSolid;
    Vertex *topUpperRight;
    newSolid = mvfs(glm::vec3 (-1.0, 1, 2.0), topUpperRight);
    Loop *topLoop = newSolid->solidFace->faceLoop;
    HalfEdge *topUpperHalfEdge = mev(topUpperRight, glm::vec3 (1.0, 1, 2.0), topLoop);
    Vertex *topUpperLeft = topUpperHalfEdge->endVertex;
    HalfEdge *topLeftHalfEdge = mev(topUpperRight, glm::vec3 (-1.0, 1, -2.0), topLoop);
    Vertex *topBottomRight = topLeftHalfEdge->endVertex;
    HalfEdge *topRightHalfEdge = mev(topUpperLeft, glm::vec3 (1.0, 1, -2.0), topLoop);
    Vertex *topBottomLeft = topRightHalfEdge->endVertex;
    Loop *downLoop = mef(topBottomLeft, topBottomRight, topLoop);

    HalfEdge *upperLeftHalfEdge = mev(topUpperLeft, glm::vec3(1.0, -1, 2.0), downLoop);
    Vertex *downUpperLeft = upperLeftHalfEdge->endVertex;
    HalfEdge *upperRightHalfEdge = mev(topUpperRight, glm::vec3(-1.0, -1, 2.0), downLoop);
    Vertex *downUpperRight = upperRightHalfEdge->endVertex;
    HalfEdge *bottomLeftHalfEdge = mev(topBottomLeft, glm::vec3(1.0, -1, -2.0), downLoop);
    Vertex *downBottomLeft = bottomLeftHalfEdge->endVertex;
    HalfEdge *bottomRightHalfEdge = mev(topBottomRight, glm::vec3(-1.0, -1, -2.0), downLoop);
    Vertex *downBottomRight = bottomRightHalfEdge->endVertex;

    Loop *upperLoop = mef(downUpperRight, downUpperLeft, downLoop);
    Loop *rightLoop = mef(downBottomRight, downUpperRight, downLoop);
    Loop *bottomLoop = mef(downBottomLeft, downBottomRight, downLoop);
    Loop *leftLoop = mef(downUpperLeft, downBottomLeft, downLoop);
    
    
    
    HalfEdge *topBridge = mev(topUpperRight, glm::vec3(-0.5, 1, 1.5), topLoop);
    Vertex *topInnerUpperRight = topBridge->endVertex;

    HalfEdge *topInnerUpperHalfEdge = mev(topInnerUpperRight, glm::vec3(0.5, 1, 1.5), topLoop);
    Vertex *topInnerUpperLeft = topInnerUpperHalfEdge->endVertex;
    HalfEdge *topInnerRightHalfEdge = mev(topInnerUpperRight, glm::vec3(-0.5, 1, -1.5), topLoop);
    Vertex *topInnerBottomRight = topInnerRightHalfEdge->endVertex;
    HalfEdge *topInnerLeftHalfEdge = mev(topInnerUpperLeft, glm::vec3(0.5, 1, -1.5), topLoop);
    Vertex *topInnerBottomLeft = topInnerLeftHalfEdge->endVertex;
    
    Loop *topInnerLoop = kemr(topUpperRight, topInnerUpperRight, topLoop);
    Loop *downInnerLoop = mef(topInnerBottomRight, topInnerBottomLeft, topLoop);

    
    HalfEdge *upperLeftInnerHalfEdge = mev(topInnerUpperLeft, glm::vec3(0.5, -1, 1.5), downInnerLoop);
    Vertex *downInnerUpperLeft = upperLeftInnerHalfEdge->endVertex;
    HalfEdge *upperRightInnerHalfEdge = mev(topInnerUpperRight, glm::vec3(-0.5, -1, 1.5), downInnerLoop);
    Vertex *downInnerUpperRight = upperRightInnerHalfEdge->endVertex;
    HalfEdge *bottomLeftInnerHalfEdge = mev(topInnerBottomLeft, glm::vec3(0.5, -1, -1.5), downInnerLoop);
    Vertex *downInnerBottomLeft = bottomLeftInnerHalfEdge->endVertex;
    HalfEdge *bottomRightInnerHalfEdge = mev(topInnerBottomRight, glm::vec3(-0.5, -1, -1.5), downInnerLoop);
    Vertex *downInnerBottomRight = bottomRightInnerHalfEdge->endVertex;

    Loop *upperInnerLoop = mef(downInnerUpperRight, downInnerUpperLeft, downInnerLoop);
    Loop *rightInnerLoop = mef(downInnerBottomRight, downInnerUpperRight, downInnerLoop);
    Loop *bottomInnerLoop = mef(downInnerBottomLeft, downInnerBottomRight, downInnerLoop);
    Loop *leftInnerLoop = mef(downInnerUpperLeft, downInnerBottomLeft, downInnerLoop);

    kfmrh(leftLoop, downInnerLoop);
    
    return newSolid;
}

Solid *createEight(){
    Solid *newSolid;
    Vertex *topUpperRight;
    newSolid = mvfs(glm::vec3 (-1.0, 1, 2.0), topUpperRight);
    Loop *topLoop = newSolid->solidFace->faceLoop;
    HalfEdge *topUpperHalfEdge = mev(topUpperRight, glm::vec3 (1.0, 1, 2.0), topLoop);
    Vertex *topUpperLeft = topUpperHalfEdge->endVertex;
    HalfEdge *topLeftHalfEdge = mev(topUpperRight, glm::vec3 (-1.0, 1, -2.0), topLoop);
    Vertex *topBottomRight = topLeftHalfEdge->endVertex;
    HalfEdge *topRightHalfEdge = mev(topUpperLeft, glm::vec3 (1.0, 1, -2.0), topLoop);
    Vertex *topBottomLeft = topRightHalfEdge->endVertex;
    Loop *downLoop = mef(topBottomLeft, topBottomRight, topLoop);

    HalfEdge *upperLeftHalfEdge = mev(topUpperLeft, glm::vec3(1.0, -1, 2.0), downLoop);
    Vertex *downUpperLeft = upperLeftHalfEdge->endVertex;
    HalfEdge *upperRightHalfEdge = mev(topUpperRight, glm::vec3(-1.0, -1, 2.0), downLoop);
    Vertex *downUpperRight = upperRightHalfEdge->endVertex;
    HalfEdge *bottomLeftHalfEdge = mev(topBottomLeft, glm::vec3(1.0, -1, -2.0), downLoop);
    Vertex *downBottomLeft = bottomLeftHalfEdge->endVertex;
    HalfEdge *bottomRightHalfEdge = mev(topBottomRight, glm::vec3(-1.0, -1, -2.0), downLoop);
    Vertex *downBottomRight = bottomRightHalfEdge->endVertex;

    Loop *upperLoop = mef(downUpperRight, downUpperLeft, downLoop);
    Loop *rightLoop = mef(downBottomRight, downUpperRight, downLoop);
    Loop *bottomLoop = mef(downBottomLeft, downBottomRight, downLoop);
    Loop *leftLoop = mef(downUpperLeft, downBottomLeft, downLoop);
    
    
    
    HalfEdge *topBridge = mev(topUpperRight, glm::vec3(-0.5, 1, -0.15), topLoop);
    Vertex *topInnerUpperRight = topBridge->endVertex;

    HalfEdge *topInnerUpperHalfEdge = mev(topInnerUpperRight, glm::vec3(0.5, 1, -0.15), topLoop);
    Vertex *topInnerUpperLeft = topInnerUpperHalfEdge->endVertex;
    HalfEdge *topInnerRightHalfEdge = mev(topInnerUpperRight, glm::vec3(-0.5, 1, -1.5), topLoop);
    Vertex *topInnerBottomRight = topInnerRightHalfEdge->endVertex;
    HalfEdge *topInnerLeftHalfEdge = mev(topInnerUpperLeft, glm::vec3(0.5, 1, -1.5), topLoop);
    Vertex *topInnerBottomLeft = topInnerLeftHalfEdge->endVertex;
    
    std::cout<<"11111"<<std::endl;
    Loop *topInnerLoop = kemr(topUpperRight, topInnerUpperRight, topLoop);
    Loop *downInnerLoop = mef(topInnerBottomRight, topInnerBottomLeft, topLoop);
    std::cout<<"11111"<<std::endl;
    
    HalfEdge *upperLeftInnerHalfEdge = mev(topInnerUpperLeft, glm::vec3(0.5, -1, -0.15), downInnerLoop);
    Vertex *downInnerUpperLeft = upperLeftInnerHalfEdge->endVertex;
    HalfEdge *upperRightInnerHalfEdge = mev(topInnerUpperRight, glm::vec3(-0.5, -1, -0.15), downInnerLoop);
    Vertex *downInnerUpperRight = upperRightInnerHalfEdge->endVertex;
    HalfEdge *bottomLeftInnerHalfEdge = mev(topInnerBottomLeft, glm::vec3(0.5, -1, -1.5), downInnerLoop);
    Vertex *downInnerBottomLeft = bottomLeftInnerHalfEdge->endVertex;
    HalfEdge *bottomRightInnerHalfEdge = mev(topInnerBottomRight, glm::vec3(-0.5, -1, -1.5), downInnerLoop);
    Vertex *downInnerBottomRight = bottomRightInnerHalfEdge->endVertex;

    Loop *upperInnerLoop = mef(downInnerUpperRight, downInnerUpperLeft, downInnerLoop);
    Loop *rightInnerLoop = mef(downInnerBottomRight, downInnerUpperRight, downInnerLoop);
    Loop *bottomInnerLoop = mef(downInnerBottomLeft, downInnerBottomRight, downInnerLoop);
    Loop *leftInnerLoop = mef(downInnerUpperLeft, downInnerBottomLeft, downInnerLoop);

    kfmrh(leftLoop, downInnerLoop);
    
    
    
    
    
    HalfEdge *topBridge1 = mev(topUpperRight, glm::vec3(-0.5, 1, 1.5), topInnerLoop);
    Vertex *topInnerUpperRight1 = topBridge1->endVertex;

    HalfEdge *topInnerUpperHalfEdge1 = mev(topInnerUpperRight1, glm::vec3(0.5, 1, 1.5), topInnerLoop);
    Vertex *topInnerUpperLeft1 = topInnerUpperHalfEdge1->endVertex;
    HalfEdge *topInnerRightHalfEdge1 = mev(topInnerUpperRight1, glm::vec3(-0.5, 1, 0.15), topInnerLoop);
    Vertex *topInnerBottomRight1 = topInnerRightHalfEdge1->endVertex;
    HalfEdge *topInnerLeftHalfEdge1 = mev(topInnerUpperLeft1, glm::vec3(0.5, 1, 0.15), topInnerLoop);
    Vertex *topInnerBottomLeft1 = topInnerLeftHalfEdge1->endVertex;
    

    Loop *topInnerLoop1 = kemr(topUpperRight, topInnerUpperRight1, topInnerLoop);
    Loop *downInnerLoop1 = mef(topInnerBottomRight1, topInnerBottomLeft1, topInnerLoop);
    
    HalfEdge *upperLeftInnerHalfEdge1 = mev(topInnerUpperLeft1, glm::vec3(0.5, -1, 1.5), downInnerLoop1);
    Vertex *downInnerUpperLeft1 = upperLeftInnerHalfEdge1->endVertex;
    HalfEdge *upperRightInnerHalfEdge1 = mev(topInnerUpperRight1, glm::vec3(-0.5, -1, 1.5), downInnerLoop1);
    Vertex *downInnerUpperRight1 = upperRightInnerHalfEdge1->endVertex;
    HalfEdge *bottomLeftInnerHalfEdge1 = mev(topInnerBottomLeft1, glm::vec3(0.5, -1, 0.15), downInnerLoop1);
    Vertex *downInnerBottomLeft1 = bottomLeftInnerHalfEdge1->endVertex;
    HalfEdge *bottomRightInnerHalfEdge1 = mev(topInnerBottomRight1, glm::vec3(-0.5, -1, 0.15), downInnerLoop1);
    Vertex *downInnerBottomRight1 = bottomRightInnerHalfEdge1->endVertex;

    Loop *upperInnerLoop1 = mef(downInnerUpperRight1, downInnerUpperLeft1, downInnerLoop1);
    Loop *rightInnerLoop1 = mef(downInnerBottomRight1, downInnerUpperRight1, downInnerLoop1);
    Loop *bottomInnerLoop1 = mef(downInnerBottomLeft1, downInnerBottomRight1, downInnerLoop1);
    Loop *leftInnerLoop1 = mef(downInnerUpperLeft1, downInnerBottomLeft1, downInnerLoop1);

    kfmrh(leftLoop, downInnerLoop1);
    
    return newSolid;
}


Solid *createOne(){
    Solid *newSolid;
    Vertex *topUpperRight;
    newSolid = mvfs(glm::vec3 (-1.0/2, -1, 2.0), topUpperRight);
    Loop *topLoop = newSolid->solidFace->faceLoop;
    HalfEdge *topUpperHalfEdge = mev(topUpperRight, glm::vec3 (1.0/2, -1, 2.0), topLoop);
    Vertex *topUpperLeft = topUpperHalfEdge->endVertex;
    HalfEdge *topLeftHalfEdge = mev(topUpperRight, glm::vec3 (-1.0/2, -1, -2.0), topLoop);
    Vertex *topBottomRight = topLeftHalfEdge->endVertex;
    HalfEdge *topRightHalfEdge = mev(topUpperLeft, glm::vec3 (1.0/2, -1, -2.0), topLoop);
    Vertex *topBottomLeft = topRightHalfEdge->endVertex;
    Loop *downLoop = mef(topBottomLeft, topBottomRight, topLoop);

    return sweep(newSolid->solidFace,glm::vec3(0.0,1.0,0.0),2.0);

    
    //return newSolid;
}


Solid *createFive(){
        Solid *newSolid;
        Vertex *P0;
        newSolid = mvfs(glm::vec3(-1.0, -1, 2.0), P0);
        Loop *topLoop = newSolid->solidFace->faceLoop;

        HalfEdge *H1 = mev(P0, glm::vec3(1.0, -1, 2.0), topLoop);
        Vertex *P1 = H1->endVertex;

        HalfEdge *H2 = mev(P1, glm::vec3(1.0, -1, -0.5), topLoop);
        Vertex *P2 = H2->endVertex;
        HalfEdge *H3 = mev(P2, glm::vec3(-0.5, -1, -0.5), topLoop);
        Vertex *P3 = H3->endVertex;
        HalfEdge *H4 = mev(P3, glm::vec3(-0.5, -1, -1.5), topLoop);
        Vertex *P4 = H4->endVertex;
        HalfEdge *H5 = mev(P4, glm::vec3(1.0, -1, -1.5), topLoop);
        Vertex *P5 = H5->endVertex;
        HalfEdge *H6 = mev(P5, glm::vec3(1.0, -1, -2.0), topLoop);
        Vertex *P6 = H6->endVertex;
        HalfEdge *H7 = mev(P6, glm::vec3(-1.0, -1, -2.0), topLoop);
        Vertex *P7 = H7->endVertex;
        HalfEdge *H8 = mev(P7, glm::vec3(-1.0, -1, 0.5), topLoop);
        Vertex *P8 = H8->endVertex;
        HalfEdge *H9 = mev(P8, glm::vec3(0.5, -1, 0.5), topLoop);
        Vertex *P9 = H9->endVertex;
        HalfEdge *H10 = mev(P9, glm::vec3(0.5, -1, 1.5), topLoop);
        Vertex *P10 = H10->endVertex;
        HalfEdge *H11 = mev(P10, glm::vec3(-1.0, -1, 1.5), topLoop);
        Vertex *P11 = H11->endVertex;

        Loop *downLoop = mef(P0, P11, topLoop);
    
    return sweep(downLoop->loopFace,glm::vec3(0.0,1.0,0.0),2.0);
}
