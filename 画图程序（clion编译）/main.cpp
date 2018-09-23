#include <iostream>
#include "MyObject.h"
#include "time.h"
#include "stdlib.h"
#include <stdio.h>
//#include <fstream>
#include <cstring>
#include <unistd.h>
using namespace std;

int main(int argc, char** argv) {
    clock_t start,finish;
    double Total_time;
    MyPoint *p1=new MyPoint(-1,-1,-1);p1->x=0;p1->y=0;p1->z=0;
    MyPoint *p2=new MyPoint(-1,-1,-1);p2->x=1000;p2->y=0;p2->z=0;
    MyPoint *p3=new MyPoint(-1,-1,-1);p3->x=0;p3->y=1000;p3->z=0;
    MyPoint *p4=new MyPoint(-1,-1,-1);p4->x=1000;p4->y=1000;p4->z=0;
    MyPoint *p5=new MyPoint(-1,-1,-1);p5->x=0;p5->y=0;p5->z=1000;
    MyPoint *p6=new MyPoint(-1,-1,-1);p6->x=1000;p6->y=0;p6->z=1000;
    MyPoint *p7=new MyPoint(-1,-1,-1);p7->x=0;p7->y=1000;p7->z=1000;
    MyPoint *p8=new MyPoint(-1,-1,-1);p8->x=1000;p8->y=1000;p8->z=1000;
    MyObject *Cubic=new MyObject;
    Cubic->AddVertex(p1);Cubic->AddVertex(p2);
    Cubic->AddVertex(p3);Cubic->AddVertex(p4);
    Cubic->AddVertex(p5);Cubic->AddVertex(p6);
    Cubic->AddVertex(p7);Cubic->AddVertex(p8);
    Cubic->AddLine(p1,p2);Cubic->AddLine(p4,p2);
    Cubic->AddLine(p1,p3);Cubic->AddLine(p4,p3);
    Cubic->AddLine(p1,p5);Cubic->AddLine(p4,p8);
    Cubic->AddLine(p6,p2);Cubic->AddLine(p7,p3);
    Cubic->AddLine(p6,p5);Cubic->AddLine(p7,p5);
    Cubic->AddLine(p6,p8);Cubic->AddLine(p7,p8);
    Cubic->AddPlane(p1,p2,p3);Cubic->AddPlane(p4,p2,p3);
    Cubic->AddPlane(p1,p2,p5);Cubic->AddPlane(p5,p2,p6);
    Cubic->AddPlane(p1,p5,p3);Cubic->AddPlane(p5,p3,p7);
    Cubic->AddPlane(p5,p6,p7);Cubic->AddPlane(p8,p6,p7);
    Cubic->AddPlane(p4,p8,p3);Cubic->AddPlane(p7,p8,p3);
    Cubic->AddPlane(p5,p2,p6);Cubic->AddPlane(p5,p6,p8);
    Cubic->Color[0]=0;Cubic->Color[1]=2;Cubic->Color[2]=1;Cubic->Color[3]=3;

    MyPoint *p11=new MyPoint(-1,-1,-1);p11->x=2100;p11->y=800;p11->z=-500;
    MyPoint *p12=new MyPoint(-1,-1,-1);p12->x=2600;p12->y=800;p12->z=-500;
    MyPoint *p13=new MyPoint(-1,-1,-1);p13->x=2100;p13->y=1300;p13->z=-500;
    MyPoint *p14=new MyPoint(-1,-1,-1);p14->x=2600;p14->y=1300;p14->z=-500;
    MyPoint *p15=new MyPoint(-1,-1,-1);p15->x=2100;p15->y=800;p15->z=1000;
    MyPoint *p16=new MyPoint(-1,-1,-1);p16->x=2600;p16->y=800;p16->z=1000;
    MyPoint *p17=new MyPoint(-1,-1,-1);p17->x=2100;p17->y=1300;p17->z=1000;
    MyPoint *p18=new MyPoint(-1,-1,-1);p18->x=2600;p18->y=1300;p18->z=1000;
    MyObject *Cuboid=new MyObject;
    Cuboid->AddVertex(p11);Cuboid->AddVertex(p12);
    Cuboid->AddVertex(p13);Cuboid->AddVertex(p14);
    Cuboid->AddVertex(p15);Cuboid->AddVertex(p16);
    Cuboid->AddVertex(p17);Cuboid->AddVertex(p18);
    Cuboid->AddLine(p11,p12);Cuboid->AddLine(p14,p12);
    Cuboid->AddLine(p11,p13);Cuboid->AddLine(p14,p13);
    Cuboid->AddLine(p11,p15);Cuboid->AddLine(p14,p18);
    Cuboid->AddLine(p16,p12);Cuboid->AddLine(p17,p13);
    Cuboid->AddLine(p16,p15);Cuboid->AddLine(p17,p15);
    Cuboid->AddLine(p16,p18);Cuboid->AddLine(p17,p18);
    Cuboid->AddPlane(p11,p12,p13);Cuboid->AddPlane(p14,p12,p13);
    Cuboid->AddPlane(p11,p12,p15);Cuboid->AddPlane(p15,p12,p16);
    Cuboid->AddPlane(p11,p15,p13);Cuboid->AddPlane(p15,p13,p17);
    Cuboid->AddPlane(p15,p16,p17);Cuboid->AddPlane(p18,p16,p17);
    Cuboid->AddPlane(p14,p18,p13);Cuboid->AddPlane(p17,p18,p13);
    Cuboid->AddPlane(p15,p12,p16);Cuboid->AddPlane(p15,p16,p18);
    Cuboid->Color[0]=5;Cuboid->Color[1]=6;Cuboid->Color[2]=7;Cuboid->Color[3]=8;

    MyPoint *a1=new MyPoint(-1,-1,-1);a1->x=0;a1->y=0;a1->z=1000;
    MyPoint *a2=new MyPoint(-1,-1,-1);a2->x=10000;a2->y=0;a2->z=1000;
    MyPoint *a3=new MyPoint(-1,-1,-1);a3->x=0;a3->y=10000;a3->z=1000;
    MyPoint *a4=new MyPoint(-1,-1,-1);a4->x=0;a4->y=0;a4->z=-10000;
    MyObject *Axis=new MyObject;
    Axis->AddVertex(a1);Axis->AddVertex(a2);Axis->AddVertex(a3);Axis->AddVertex(a4);
    Axis->AddLine(a1,a2);Axis->AddLine(a1,a3);Axis->AddLine(a1,a4);
    Axis->Color[0]=4;Axis->Color[1]=4;Axis->Color[2]=4;Axis->Color[3]=4;

    MyPoint *c1=new MyPoint(-1,-1,-1);c1->x=500;c1->y=3000;c1->z=1000;
    MyPoint *c2=new MyPoint(-1,-1,-1);c2->x=3000;c2->y=4000;c2->z=1000;
    MyPoint *c3=new MyPoint(-1,-1,-1);c3->x=1800;c3->y=4500;c3->z=1000;
    MyPoint *c4=new MyPoint(-1,-1,-1);c4->x=1500;c4->y=3600;c4->z=-500;
    MyObject *Centrum=new MyObject;
    Centrum->AddVertex(c1);Centrum->AddVertex(c2);Centrum->AddVertex(c3);Centrum->AddVertex(c4);
    Centrum->AddLine(c1,c2);Centrum->AddLine(c3,c2);Centrum->AddLine(c1,c3);
    Centrum->AddLine(c1,c4);Centrum->AddLine(c4,c2);Centrum->AddLine(c4,c3);
    Centrum->AddPlane(c1,c2,c3);Centrum->AddPlane(c4,c2,c3);
    Centrum->AddPlane(c1,c4,c3);Centrum->AddPlane(c1,c2,c4);
    Centrum->Color[0]=9;Centrum->Color[1]=5;Centrum->Color[2]=9;Centrum->Color[3]=9;

    MyGraph *graph = new MyGraph;
    graph->AddObject(Cubic);
    graph->AddObject(Axis);
    graph->AddObject(Cuboid);
    graph->AddObject(Centrum);

    float input[8];
    input[7]=0;
    while(!input[7]) {
        FILE *fp=fopen("/home/li/cghm/binary.dat","rb");
        float readdata[8];
        fread(readdata,sizeof(float),8,fp);
        if(!Compare(readdata,input)) {
            start = clock();
            //ChainOfPoint *FinalPoint=new ChainOfPoint;
            for(int i=0;i<8;i++)input[i]=readdata[i];
            //cin>>input[0];cin>>input[1];cin>>input[2];cin>>input[3];cin>>input[4];
            //cin>>input[5];cin>>input[6];cin>>input[7];
            graph->Camera_x = input[0];
            graph->Camera_y = input[1];
            graph->Camera_z = input[2];
            graph->delta_x = input[3];
            graph->delta_z = input[5];
            graph->delta_y = input[4];
            graph->rotationangle = input[6];
            //graph->Trans(FinalPoint);
            //graph->Display(FinalPoint);
            //ConvertJPG(graph);
            graph->Trans_Dispaly_ConvertJPG();
            printf("OK!\n");
            fclose(fp);
            finish = clock();
            Total_time = (double) (finish - start) / CLOCKS_PER_SEC;
            printf("%f seconds\n", Total_time);
        }
        else{usleep(200000);}
        }
//    MyPoint *p9;
//    MyPoint *p10;
//    MyPoint *p11;
//    MyPoint *p12;
//    MyPoint *p13;
    return 0;
}