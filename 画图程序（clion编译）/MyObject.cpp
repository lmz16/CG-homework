//
// Created by li on 18-6-2.
//

#include "MyObject.h"
#include <cmath>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;

using namespace cv;
void MyPoint::Assignment(MyPoint const &mp) {
    x = mp.x;
    y	= mp.y;
    z = mp.z;
    h = mp.h;
    next = mp.next;
}

bool MyPoint::Equal(float x1, float y1, float z1, float h1) {
    return ((x==x1)&&(y==y1)&&(z==z1)&&(h==h1));
}

MyPoint::MyPoint(float x1, float y1, float z1) {
    x=x1;y=y1;z=z1;h=1;next=0;
}

MyPoint::~MyPoint() {
    MyPoint *mp=this;
    MyPoint *tempm;
    while(mp->next)
    {
        tempm=mp;
        mp=mp->next;
        delete tempm;
    }
}

PointInfo::PointInfo() {
    Distance=10000000000000000;
    Color=3;
}

MyLine::MyLine(MyPoint *mp1, MyPoint *mp2) {
    Start=mp1;
    End=mp2;
}

MyPlane::MyPlane(MyPoint *mp1, MyPoint *mp2, MyPoint *mp3) {
    Vertex1=mp1;
    Vertex2=mp2;
    Vertex3=mp3;
}

void MyPoint::CalcDistance(float cx, float cy, float cz, float ch) {
    Distance=(x-cx)*(x-cx)+(y-cy)*(y-cy)+(z-cz)*(z-cz);
}

void MyLine::BuildLine() {
    MyPoint *temp=new MyPoint(-1,-1,-1);
    PointOnLine=temp;
    float pace=0.001;
    for(float t=0;t<=1;t+=pace)
    {
        float temp_x, temp_y, temp_z;
        temp_x=(1-t)*(Start->x)+t*(End->x);
        temp_y=(1-t)*(Start->y)+t*(End->y);
        temp_z=(1-t)*(Start->z)+t*(End->z);
        if(!temp->Equal(temp_x,temp_y,temp_z,1))
        {
            MyPoint *NewPoint=new MyPoint(temp_x,temp_y,temp_z);
            temp->next=NewPoint;
            temp=temp->next;
        }
    }
}

bool MyPlane::IsExisted(float x1, float y1, float z1) {
    MyPoint *p=PointOnPlane;
    bool flag=false;
    while(p->next)
    {
        p=p->next;
        if(p->Equal(x1,y1,z1,1))
        {
            flag=true;
            break;
        }
    }
    return flag;
}

void MyPlane::BuildPlane() {
    MyPoint *temp=new MyPoint(-1,-1,-1);
    PointOnPlane=temp;
    float pace = 0.008;
    float t, p;
    for(t = 0; t<=1; t+=pace)
    {
        float temp_x, temp_y, temp_z;
        temp_x=(1-t)*(Vertex1->x)+t*(Vertex2->x);
        temp_y=(1-t)*(Vertex1->y)+t*(Vertex2->y);
        temp_z=(1-t)*(Vertex1->z)+t*(Vertex2->z);
        for(p=0; p<=1;p+=pace)
        {
            float temp_x1, temp_y1, temp_z1;
            temp_x1=(1-p)*temp_x+p*(Vertex3->x);
            temp_y1=(1-p)*temp_y+p*(Vertex3->y);
            temp_z1=(1-p)*temp_z+p*(Vertex3->z);
            if(!temp->Equal(temp_x1,temp_y1,temp_z1,1))
            {
                if(!IsExisted(temp_x1,temp_y1,temp_z1))
                {
                    MyPoint *NewPoint = new MyPoint(temp_x1, temp_y1, temp_z1);
                    temp->next=NewPoint;
                    temp=temp->next;
                }
            }
        }
    }
}

MyObject::MyObject() {
    NumberOfLine=0;
    NumberOfPlane=0;
    NumberOfVertex=0;
    VertexOfObject=new MyPoint;
    LineOfObject=new MyLine;
    PlaneOfObject=new MyPlane;
}

void MyObject::AddVertex(MyPoint *mp) {
    MyPoint *p=VertexOfObject;
    while(p->next)p=p->next;
    p->next=mp;
    NumberOfVertex++;
}

void MyObject::AddLine(MyPoint *mp1, MyPoint *mp2) {
    MyLine *p=LineOfObject;
    while(p->next)p=p->next;
    MyLine *NewLine=new MyLine(mp1,mp2);
    NewLine->BuildLine();
    p->next=NewLine;
    NumberOfLine++;
}

void MyObject::AddPlane(MyPoint *mp1, MyPoint *mp2, MyPoint *mp3) {
    MyPlane *p=PlaneOfObject;
    while(p->next)p=p->next;
    MyPlane *NewPlane=new MyPlane(mp1,mp2,mp3);
    NewPlane->BuildPlane();
    p->next=NewPlane;
    NumberOfPlane++;
}

MyGraph::MyGraph() {
    ObjectOfWorld=new MyObject;
//    FinalPoint=new ChainOfPoint;
}

void MyGraph::AddObject(MyObject *mo) {
    MyObject *p=ObjectOfWorld;
    while(p->next)p=p->next;
    p->next=mo;
}

void PointInfo::Fresh() {Distance=10000000000000000;Color=3;}

ChainOfPoint::~ChainOfPoint() {
    ChainOfPoint *cp=this;
    ChainOfPoint *tempc;
    while(cp->next)
    {
        tempc=cp;
        cp=cp->next;
        MyPoint *mp=tempc->Chain;
        MyPoint *tempm;
        while(mp->next)
        {
            tempm=mp;
            mp=mp->next;
            delete tempm;
        }
        delete tempc;
    }
    cout<<"chain delete\n";
}

void ProjectionTransform(MyPoint *myp,float a,float b,float c)
{
    MyPoint* curr = myp;
    float dist = 500;
    float u = sqrt(a*a+b*b+c*c);
    float v = sqrt(a*a+b*b);
    while(curr -> next)
    {
        curr = curr -> next;

            float temp_x, temp_y, temp_z;
            temp_x = -curr->x * b / v + curr->y * a / v;
            temp_y = -curr->x * a * c / u / v - curr->y * b * c / u / v + curr->z * v / u;
            temp_z = -curr->x * a / u - curr->y * b / u - curr->z * c / u + u;

            temp_x = dist * temp_x / temp_z;
            temp_y = dist * temp_y / temp_z;
            temp_z = dist;

            curr->x = temp_x;
            curr->y = temp_y;
            curr->z = temp_z;

    }
}

MyPoint* Displacement(MyPoint *myp, float dx, float dy, float dz)
{
    MyPoint* curr_prev = myp;
    MyPoint* post_trans = new MyPoint(-1,-1,-1);
    MyPoint* curr_post = post_trans;
    while(curr_prev -> next)
    {
        curr_prev = curr_prev -> next;
        float temp_x, temp_y, temp_z;
        temp_x = curr_prev -> x + dx;
        temp_y = curr_prev -> y + dy;
        temp_z = curr_prev -> z + dz;
        curr_post -> next = new MyPoint(temp_x, temp_y, temp_z);
        curr_post = curr_post -> next;
    }
    return post_trans;
}

void Rotation(MyPoint *myp, float theta, float persx, float persy)
{
    MyPoint* curr_prev = myp;
    while(curr_prev -> next)
    {
        curr_prev = curr_prev -> next;
        float temp_x, temp_y;
        float vec_x, vec_y;
        vec_x = curr_prev -> x - persx;
        vec_y = curr_prev -> y - persy;

        temp_x = cos(theta)*vec_x - sin(theta)*vec_y;
        temp_y = sin(theta)*vec_x + cos(theta)*vec_y;
        temp_x += persx;
        temp_y += persy;

        curr_prev->x=temp_x;
        curr_prev->y=temp_y;
    }
}

bool Compare(float a[8], float b[8])
{
    bool flag=1;
    for(int i=0;i<8;i++)
    {
        if(a[i]!=b[i])
        {
            flag=false;
            break;
        }
    }
    return flag;
}

void MyGraph::Trans_Dispaly_ConvertJPG() {
    MyObject *op=ObjectOfWorld;
    ChainOfPoint *FinalPoint=new ChainOfPoint;
    ChainOfPoint *cp=FinalPoint;
    while(op->next)
    {
        op=op->next;
        MyPoint* temp=Displacement(op->VertexOfObject,delta_x,delta_y,delta_z);
        Rotation(temp,rotationangle,Camera_x,Camera_y);
        MyPoint *ptemp=temp;
        while(ptemp->next)
        {
            ptemp=ptemp->next;
            ptemp->CalcDistance(Camera_x,Camera_y,Camera_z,1);
        }
        ProjectionTransform(temp,Camera_x,Camera_y,Camera_z);
        ChainOfPoint *temp1=new ChainOfPoint;
        temp1->Chain=temp;temp1->type=0;
        cp->next=temp1;cp=cp->next;
        cp->WhichObject=op;
        temp1=0;temp=0;ptemp=0;
        MyLine *lp=op->LineOfObject;
        while(lp->next)
        {
            lp=lp->next;
            MyPoint* templ=Displacement(lp->PointOnLine,delta_x,delta_y,delta_z);
            Rotation(templ,rotationangle,Camera_x,Camera_y);
            MyPoint *ptempl=templ;
            while(ptempl->next)
            {
                ptempl=ptempl->next;
                ptempl->CalcDistance(Camera_x,Camera_y,Camera_z,1);
            }
            ProjectionTransform(templ,Camera_x,Camera_y,Camera_z);
            ChainOfPoint *temp2=new ChainOfPoint;
            temp2->Chain=templ;temp2->type=1;
            cp->next=temp2;cp=cp->next;
            cp->WhichObject=op;
            temp2=0;templ=0;ptempl=0;
        }
        MyPlane *pp=op->PlaneOfObject;
        while(pp->next)
        {
            pp=pp->next;
            MyPoint* tempp=Displacement(pp->PointOnPlane,delta_x,delta_y,delta_z);
            Rotation(tempp,rotationangle,Camera_x,Camera_y);
            MyPoint *ptempp=tempp;
            while(ptempp->next)
            {
                ptempp=ptempp->next;
                ptempp->CalcDistance(Camera_x,Camera_y,Camera_z,1);
            }
            ProjectionTransform(tempp,Camera_x,Camera_y,Camera_z);
            ChainOfPoint *temp3=new ChainOfPoint;
            temp3->Chain=tempp;temp3->type=2;
            cp->next=temp3;cp=cp->next;
            cp->WhichObject=op;
            temp3=0;tempp=0;ptempp=0;
        }
    }
    cp=0;

    ChainOfPoint *temp=FinalPoint;
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<512;j++)
            MyView[i][j].Fresh();
    }
    while(temp->next)
    {
        temp=temp->next;
        MyPoint *temp_point=temp->Chain;
        while(temp_point->next)
        {
            temp_point=temp_point->next;
            if((temp_point->y<128)&&(temp_point->x<256)&&(temp_point->x>=-256)&&(temp_point->y>=-128)){
                if(temp_point->Distance<MyView[int(temp_point->y)+128][int(temp_point->x)+256].Distance)
                {
                    MyView[int(temp_point->y)+128][int(temp_point->x)+256].Distance = temp_point->Distance;
                    MyView[int(temp_point->y)+128][int(temp_point->x)+256].Color =temp->WhichObject->Color[temp->type];
                }
                else if((temp_point->Distance==MyView[int(temp_point->y)+128][int(temp_point->x)+256].Distance)&&(MyView[int(temp_point->y)+128][int(temp_point->x)+256].Color >temp->type))
                {
                    MyView[int(temp_point->y)+128][int(temp_point->x)+256].Color =temp->WhichObject->Color[temp->type];
                }}
        }
        temp_point=0;
    }
    temp=0;

    int row = 256, col = 512;
    Mat outMat(row, col, CV_8UC3);
    uchar* pixel = outMat.ptr<uchar>(0);
    for(int i = 0; i < row; i++)
    {
        pixel = outMat.ptr<uchar>(i);
        for(int j = 0; j < col; j++)
        {
            int selectChannel = this -> MyView[i][j].Color;
            switch(selectChannel) {
                case 0: {
                    pixel[j * 3] = 255;
                    pixel[j * 3 + 1] = pixel[j * 3 + 2] = 0;
                    break;
                }
                case 1:{
                    pixel[j * 3+1] = 255;
                    pixel[j * 3] = pixel[j * 3 + 2] = 0;
                    break;
                }
                case 2:{
                    pixel[j * 3+2] = 255;
                    pixel[j * 3 + 1] = pixel[j * 3] = 0;
                    break;
                }
                case 3:{
                    pixel[j * 3] = pixel[j * 3 + 1] = pixel[j * 3 + 2] =255;
                    break;
                }
                case 4:{
                    pixel[j * 3] = pixel[j * 3 + 1] = pixel[j * 3 + 2] =0;
                    break;
                }
                case 5:{
                    pixel[j * 3] =0 ;
                    pixel[j * 3 + 1] =0 ;
                    pixel[j * 3 + 2] =0;
                    break;
                }
                case 6:{
                    pixel[j * 3] =137 ;
                    pixel[j * 3 + 1] =137 ;
                    pixel[j * 3 + 2] =137;
                    break;
                }
                case 7:{
                    pixel[j * 3] =0 ;
                    pixel[j * 3 + 1] =255 ;
                    pixel[j * 3 + 2] =255;
                    break;
                }
                case 8:{
                    pixel[j * 3] =0 ;
                    pixel[j * 3 + 1] =0 ;
                    pixel[j * 3 + 2] =0;
                    break;
                }
                case 9:{
                    pixel[j * 3] =0 ;
                    pixel[j * 3 + 1] =0 ;
                    pixel[j * 3 + 2] =255;
                }
            }

        }
    }
    imwrite("test.jpg", outMat);
    //delete FinalPoint;
    FinalPoint=0;
}