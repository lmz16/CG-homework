//
// Created by li on 18-6-2.
//

#ifndef CGFINAL_MYOBJECT_H
#define CGFINAL_MYOBJECT_H

struct MyPoint
{
    float x;
    float y;
    float z;
    float h;
    MyPoint *next;
    float Distance;
    MyPoint(){h=1;}
    MyPoint(float x1,float y1,float z1);
    void Assignment (MyPoint const& mp);
    bool Equal(float x1,float y1,float z1,float h1);
    void CalcDistance(float cx,float cy,float cz,float ch);
    ~MyPoint();
};

struct PointInfo
{
    float Distance;
    int Color;// =3:null =0:vertex =1:line =2:plane =4:axis
    PointInfo();
    void Fresh();
};

struct MyLine
{
    MyPoint *Start,*End;
    MyPoint *PointOnLine;
    MyLine *next;
    MyLine(){}
    MyLine(MyPoint *mp1,MyPoint *mp2);
    void BuildLine();
};

struct MyPlane
{
    MyPoint *Vertex1,*Vertex2,*Vertex3;
    MyPoint *PointOnPlane;
    MyPlane *next;
    MyPlane(){}
    MyPlane(MyPoint *mp1,MyPoint *mp2,MyPoint *mp3);
    void BuildPlane();
    bool IsExisted(float x1,float y1,float z1);
};

struct MyObject
{
    int NumberOfVertex;
    int NumberOfLine;
    int NumberOfPlane;
    MyPoint *VertexOfObject;
    MyLine *LineOfObject;
    MyPlane *PlaneOfObject;
    MyObject *next;
    int Color[4];
    MyObject();
    void AddVertex(MyPoint *mp);
    void AddLine(MyPoint *mp1,MyPoint *mp2);
    void AddPlane(MyPoint *mp1,MyPoint *mp2,MyPoint *mp3);
};

struct ChainOfPoint
{
    MyPoint *Chain;
    int type;//type =0:vertex =1:line =2:plane =3:null
    ChainOfPoint *next;
    MyObject *WhichObject;
    ChainOfPoint(){type=3;}
    ~ChainOfPoint();
};

struct MyGraph
{
    MyObject* ObjectOfWorld;
    //ChainOfPoint *FinalPoint;
    PointInfo MyView[256][512];
    float Camera_x,Camera_y,Camera_z;
    float delta_x,delta_y,delta_z;
    float rotationangle;
    MyGraph();
    void AddObject(MyObject *mo);
    void Trans_Dispaly_ConvertJPG();
};

void ProjectionTransform(MyPoint *myp,float a,float b,float c);
MyPoint *Displacement(MyPoint *myp,float dx,float dy,float dz);
void Rotation(MyPoint *myp,float theta, float persx,float persy);
bool Compare(float a[8], float b[8]);
#endif //CGFINAL_MYOBJECT_H
