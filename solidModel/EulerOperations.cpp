//
//  EulerOperations.cpp
//  solidModel
//
//  Created by Lidemiao on 2023/10/17.
//

#include "EulerOperations.h"
#include "iostream"


int Loop::size() {
    if(loopHalfEdge== nullptr) return 0;
    int count=1;
    HalfEdge *startHfedge=loopHalfEdge;
    HalfEdge *tmphfedge=loopHalfEdge->nextHfEdge;
    while(tmphfedge!= nullptr&&tmphfedge!=startHfedge){
        count++; tmphfedge=tmphfedge->nextHfEdge;
    }
    return count;
}

Solid *mvfs(glm::vec3 position, Vertex *&vertex){
    Solid *newSolid=new Solid();
    Face *newFace=new Face();
    Loop *newLoop=new Loop();

    vertex=new Vertex(position);

    newSolid->solidFace=newFace;
    newFace->faceSolid=newSolid;

    newFace->faceLoop=newLoop;
    newLoop->loopFace=newFace;

    return newSolid;
}

HalfEdge *mev(Vertex *vertex, glm::vec3 position, Loop *loop){
    HalfEdge *hfedge1=new HalfEdge();
    HalfEdge *hfedge2=new HalfEdge();
    Edge *newedge=new Edge();

    newedge->firHfEdge=hfedge1; newedge->secHfEdge=hfedge2;
    hfedge1->edge=newedge; hfedge2->edge=newedge;
    hfedge1->adjacentHfEdge=hfedge2; hfedge2->adjacentHfEdge=hfedge1;

    Vertex *newvertex=new Vertex(position);

    hfedge1->startVertex=vertex; hfedge1->endVertex=newvertex;
    hfedge2->startVertex=newvertex; hfedge2->endVertex=vertex;

    hfedge1->hfEdgeLoop=loop; hfedge2->hfEdgeLoop=loop;
    hfedge1->nextHfEdge=hfedge2; hfedge2->prevHfEdge=hfedge1;

    if(loop->loopHalfEdge == nullptr){
        hfedge2->nextHfEdge=hfedge1; hfedge1->prevHfEdge=hfedge2;
        loop->loopHalfEdge=hfedge1;
    }else{
        HalfEdge *tmphf=loop->loopHalfEdge;
        while(tmphf->startVertex!=vertex) tmphf=tmphf->nextHfEdge;
        hfedge2->nextHfEdge=tmphf; hfedge1->prevHfEdge=tmphf->prevHfEdge;
        tmphf->prevHfEdge->nextHfEdge=hfedge1; tmphf->prevHfEdge=hfedge2;
    }

    Solid *thesolid=loop->loopFace->faceSolid;
    if(thesolid->solidEdges== nullptr) thesolid->solidEdges=newedge;
    else{
        Edge *e=thesolid->solidEdges;
        while(e->nextEdge != nullptr) e=e->nextEdge;
        e->nextEdge=newedge; newedge->prevEdge=e;
    }

    return hfedge1;
}

Loop *mef(Vertex *v1, Vertex *v2, Loop *&largeLoop){
    HalfEdge *hfedge1=new HalfEdge();
    HalfEdge *hfedge2=new HalfEdge();
    Edge *newedge=new Edge();

    newedge->firHfEdge=hfedge1; newedge->secHfEdge=hfedge2;
    hfedge1->edge=newedge; hfedge2->edge=newedge;
    hfedge1->adjacentHfEdge=hfedge2; hfedge2->adjacentHfEdge=hfedge1;

    hfedge1->startVertex=v1; hfedge1->endVertex=v2;
    hfedge2->startVertex=v2; hfedge2->endVertex=v1;

    bool thefirst=true; bool hasvertex=false;
    HalfEdge *firhfe; HalfEdge *sechfe;

    for(HalfEdge* hfe=largeLoop->loopHalfEdge;hfe!=largeLoop->loopHalfEdge||thefirst;hfe=hfe->nextHfEdge){
        thefirst=false;
        if(hfe->startVertex==v1){
            firhfe=hfe;
            hasvertex=true; break;
        }
    }
    if(!hasvertex){
        std::cout<<"do not fine vertex1: ("<<v1->position.x
                <<" "<<v1->position.y<<" "<<v1->position.z<<")"<<std::endl;
        return nullptr;
    }

    thefirst=true; hasvertex=false;
    for(HalfEdge* hfe=largeLoop->loopHalfEdge;hfe!=largeLoop->loopHalfEdge||thefirst;hfe=hfe->nextHfEdge){
        thefirst=false;
        if(hfe->startVertex==v2){
            sechfe=hfe;
            hasvertex=true; break;
        }
    }
    if(!hasvertex){
        std::cout<<"do not fine vertex1: ("<<v2->position.x
                 <<" "<<v2->position.y<<" "<<v2->position.z<<")"<<std::endl;
        return nullptr;
    }

    hfedge2->nextHfEdge=firhfe; hfedge2->prevHfEdge=sechfe->prevHfEdge;
    hfedge1->nextHfEdge=sechfe; hfedge1->prevHfEdge=firhfe->prevHfEdge;
    firhfe->prevHfEdge->nextHfEdge=hfedge1; firhfe->prevHfEdge=hfedge2;
    sechfe->prevHfEdge->nextHfEdge=hfedge2; sechfe->prevHfEdge=hfedge1;

    largeLoop->loopHalfEdge=hfedge1;
    Loop *newloop=new Loop();
    newloop->loopHalfEdge=hfedge2;

    Solid *thesolid=largeLoop->loopFace->faceSolid;

    Face *newface=new Face();
    newface->faceLoop=newloop;
    newface->faceSolid=thesolid;
    newloop->loopFace=newface;

    Face *tmpf=thesolid->solidFace;
    while(tmpf->nextFace!= nullptr) tmpf=tmpf->nextFace;
    tmpf->nextFace=newface; newface->prevFace=tmpf;

    Edge *e=thesolid->solidEdges;
    if(e== nullptr) thesolid->solidEdges=newedge;
    else{
        while (e->nextEdge!= nullptr) e=e->nextEdge;
        e->nextEdge=newedge;
        newedge->prevEdge=e;
    }

    if(newloop->size()>largeLoop->size()){
        Loop *tmpLoop=newloop;
        newloop=largeLoop;
        largeLoop=tmpLoop;
    }

    return newloop;

}


Loop *kemr(Vertex *v1,Vertex *v2, Loop *&largeloop){
    Loop *newloop=new Loop();
    HalfEdge *hf;
    for(hf=largeloop->loopHalfEdge;!(hf->startVertex==v1&&hf->endVertex==v2);hf=hf->nextHfEdge){}
    Edge *e=hf->edge;
    hf->nextHfEdge->prevHfEdge=hf->adjacentHfEdge->prevHfEdge;
    hf->adjacentHfEdge->prevHfEdge->nextHfEdge=hf->nextHfEdge;
    
    hf->prevHfEdge->nextHfEdge=hf->adjacentHfEdge->nextHfEdge;
    hf->adjacentHfEdge->nextHfEdge->prevHfEdge=hf->prevHfEdge;
    
    largeloop->loopHalfEdge=hf->prevHfEdge;
    newloop->loopHalfEdge=hf->nextHfEdge;
    
    Face *oldface=largeloop->loopFace;
    newloop->loopFace=oldface;
    
    Loop *lp;
    for(lp=oldface->faceLoop;lp->nextLoop!=nullptr;lp=lp->nextLoop){}
    lp->nextLoop=newloop; newloop->prevLoop=lp;
    
    Solid *oldsolid=largeloop->loopFace->faceSolid;
    e=oldsolid->solidEdges;
    if(e==hf->edge){
        oldsolid->solidEdges=e->nextEdge;
        oldsolid->solidEdges->prevEdge=e->prevEdge;
        if(e->prevEdge) e->prevEdge->nextEdge=oldsolid->solidEdges;
    }else{
        while (e->nextEdge!=hf->edge) {
            e=e->nextEdge;
        }
        e->nextEdge=hf->edge->nextEdge;
        e->nextEdge->prevEdge=e;
    }
    
    if(newloop->size()>largeloop->size()){
        Loop *tmpLoop=newloop;
        newloop=largeloop;
        largeloop=tmpLoop;
    }
    return newloop;
}

void kfmrh(Loop *outloop, Loop *inloop){
    Face *outface=outloop->loopFace;
    Face *inface=inloop->loopFace;
    
    Loop *lp;
    for(lp=outface->faceLoop;lp->nextLoop!=nullptr;lp=lp->nextLoop){}
    lp->nextLoop=inloop; inloop->prevLoop=lp;
    inloop->loopFace=outface;
    
    Solid *oldsolid=outface->faceSolid;
    Face *f=oldsolid->solidFace;
    if(f==inface){
        oldsolid->solidFace=f->nextFace;
        oldsolid->solidFace->prevFace=f->prevFace;
        if(f->prevFace) f->prevFace->nextFace=oldsolid->solidFace;
    }else{
        while (f->nextFace!=inface) {
            f=f->nextFace;
        }
        f->nextFace=inface->nextFace;
        f->nextFace->prevFace=f;
    }
    return;
}

Solid *sweep(Face *face, glm::vec3 direction, float distance){
    Solid *solid=face->faceSolid;
    Loop* lp; HalfEdge *hf;
    for(lp=face->faceLoop;lp!=nullptr;lp=lp->nextLoop){
        hf=lp->loopHalfEdge;
        Vertex *startV=hf->startVertex;
        glm::vec3 newPos=startV->position+distance*direction;
        HalfEdge *firstHf=mev(startV, newPos, lp);
        
        Vertex *preVertex=firstHf->endVertex;
        hf=hf->nextHfEdge;
        Vertex *v=hf->startVertex;
        
        while (v!=startV) {
            glm::vec3 newPosition=v->position+distance*direction;
            HalfEdge *conHf=mev(v, newPosition, lp);
            Vertex *nexVertex=conHf->endVertex;
            mef(preVertex, nexVertex, lp);
            preVertex=nexVertex;
            hf=hf->nextHfEdge;
            v=hf->startVertex;
        }
        
        mef(firstHf->endVertex, preVertex, lp);
        
    }
    
    return solid;
}





