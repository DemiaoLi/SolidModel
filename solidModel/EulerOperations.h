//
//  EulerOperations.h
//  solidModel
//
//  Created by Lidemiao on 2023/10/17.
//

#ifndef EulerOperations_h
#define EulerOperations_h

#include "/Users/lidemiao/cadcg/solidModel/glm/glm.hpp"
#include "/Users/lidemiao/cadcg/solidModel/glm/gtc/matrix_transform.hpp"
#include "/Users/lidemiao/cadcg/solidModel/glm/gtc/type_ptr.hpp"

class Solid;
class Face;
class Loop;
class HalfEdge;
class Edge;
class Vertex;

class SolidModel{
    Solid *solidList;
};

class Solid{
public:
    int solidID;
    Solid *prevSolid, *nextSolid;
    Face *solidFace;
    Edge *solidEdges;

    Solid(): solidID(-1), prevSolid(nullptr), nextSolid(nullptr), solidFace(nullptr), solidEdges(nullptr) {}
};

class Face{
public:
    int faceID;
    Solid *faceSolid;
    Face *prevFace, *nextFace;
    Loop *faceLoop;

    Face(): faceID(-1), faceSolid(nullptr), prevFace(nullptr), nextFace(nullptr), faceLoop(nullptr) {}
};

class Loop{
public:
    Face *loopFace;
    Loop *prevLoop, *nextLoop;
    HalfEdge *loopHalfEdge;
    int size();

    Loop(): loopFace(nullptr), prevLoop(nullptr), nextLoop(nullptr), loopHalfEdge(nullptr) {}
};

class HalfEdge{
public:
    Loop *hfEdgeLoop;
    HalfEdge *prevHfEdge, *nextHfEdge, *adjacentHfEdge;
    Edge *edge;
    Vertex *startVertex, *endVertex;

    HalfEdge(): hfEdgeLoop(nullptr), prevHfEdge(nullptr), nextHfEdge(nullptr),
        adjacentHfEdge(nullptr), edge(nullptr), startVertex(nullptr), endVertex(nullptr) {}

};

class Edge{
public:
    Edge *prevEdge, *nextEdge;
    HalfEdge *firHfEdge, *secHfEdge;

    Edge(): prevEdge(nullptr), nextEdge(nullptr), firHfEdge(nullptr), secHfEdge(nullptr) {}
};

class Vertex{
public:
    Vertex *prevVertex, *nextVertex;
    glm::vec3 position;

    Vertex(): prevVertex(nullptr), nextVertex(nullptr), position(0,0,0) {}
    Vertex(double x,double y,double z): prevVertex(nullptr), nextVertex(nullptr), position(x,y,z) {}
    Vertex(glm::vec3 pos): prevVertex(nullptr), nextVertex(nullptr), position(pos) {}
};



Solid *mvfs(glm::vec3 position, Vertex *&vertex);
HalfEdge *mev(Vertex *vertex, glm::vec3 position, Loop *loop);
Loop *mef(Vertex *v1, Vertex *v2, Loop *&largeLoop);
void kfmrh(Loop *outloop, Loop *inloop);
Loop *kemr(Vertex *v1,Vertex *v2, Loop *&largeloop);
Solid *sweep(Face *face, glm::vec3 direction, float distance);


#endif /* EulerOperations_h */
