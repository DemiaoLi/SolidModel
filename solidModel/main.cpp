//
//  main.cpp
//  solidModel
//
//  Created by Lidemiao on 2023/10/17.
//



#include "draw.h"
#include "Examples.h"
//#include "EulerOperations.h"


int main(int argc, char **argv)
{
    
    Solid *zero=createZero();
    Solid *eight=createEight();
    Solid *one=createOne();
    Solid *five=createFive();
    
    int fcnt=1; int lcnt=1;
    for(Face* f=zero->solidFace;f;f=f->nextFace){
        cout<<"the "<<fcnt<<"th face:"<<endl;
        for(Loop* l=f->faceLoop;l;l=l->nextLoop){
            cout<<"   the "<<lcnt<<"th loop:"<<endl;
            Vertex *sv=l->loopHalfEdge->startVertex;
            cout<<"      Vertex:("<<sv->position.x<<" "<<sv->position.y<<" "<<sv->position.z<<") -> ";
            for(HalfEdge* hf=l->loopHalfEdge;hf->endVertex!=sv;hf=hf->nextHfEdge){
                cout<<"      Vertex:("<<hf->endVertex->position.x<<" "<<hf->endVertex->position.y<<" "<<hf->endVertex->position.z<<") -> ";
            }
            lcnt++;
        }
        cout<<endl;
        fcnt++;
    }
    
    drawSolidModel(argc, argv,five,eight,one);
    
    return 0;
}


