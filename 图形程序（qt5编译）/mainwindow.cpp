#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDataStream>
#include "stdlib.h"
#include <stdio.h>
#include <unistd.h>
#include <QProcess>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui -> height -> setMinimum(-4000);
    ui -> height -> setMaximum(4000);
    ui -> height -> setSingleStep(100);

    ui -> rotation -> setMinimum(-150);
    ui -> rotation -> setMaximum(150);
    ui -> rotation -> setSingleStep(10);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(endprocess()));
    connect(ui->forward,SIGNAL(clicked()),this,SLOT(move_forward()));
    connect(ui->backward,SIGNAL(clicked()),this,SLOT(move_backward()));
    connect(ui->left,SIGNAL(clicked()),this,SLOT(move_left()));
    connect(ui->right,SIGNAL(clicked()),this,SLOT(move_right()));
    connect(ui->height,SIGNAL(sliderReleased()),this,SLOT(move_vertically()));
    connect(ui->rotation,SIGNAL(sliderReleased()),this,SLOT(rotate()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(startprocess()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startprocess()
{
    float output[8];
    output[0]=4000;
    output[1]=4000;
    output[2]=-500;
    output[3]=x;
    output[4]=y;
    output[5]=z;
    output[6]=theta;
    output[7]=0;
    FILE *fp=fopen("/home/li/cghm/binary.dat","wb");
    fwrite(output,sizeof(float),8,fp);
    fclose(fp);
    program=new QProcess();
    program->start("bash /home/li/cghm/run.sh");
}

void MainWindow::endprocess()
{
    float output[8];
    output[0]=4000;
    output[1]=4000;
    output[2]=-500;
    output[3]=x;
    output[4]=y;
    output[5]=z;
    output[6]=theta;
    output[7]=1;
    FILE *fp=fopen("/home/li/cghm/binary.dat","wb");
    fwrite(output,sizeof(float),8,fp);
    fclose(fp);
    program->close();
    this->close();
    exit(0);
}

void MainWindow::move_forward()
{
    //x = x + pace_len;
    y = y + pace_len;
    float output[8];
    output[0]=4000;
    output[1]=4000;
    output[2]=-500;
    output[3]=x;
    output[4]=y;
    output[5]=z;
    output[6]=theta;
    output[7]=0;
    FILE *fp=fopen("/home/li/cghm/binary.dat","wb");
    fwrite(output,sizeof(float),8,fp);
    fclose(fp);
}

void MainWindow::move_backward()
{
    //x = x - pace_len;
    y = y - pace_len;
    float output[8];
    output[0]=4000;
    output[1]=4000;
    output[2]=-500;
    output[3]=x;
    output[4]=y;
    output[5]=z;
    output[6]=theta;
    output[7]=0;
    FILE *fp=fopen("/home/li/cghm/binary.dat","wb");
    fwrite(output,sizeof(float),8,fp);
    fclose(fp);
}

void MainWindow::move_left()
{
    x = x - pace_len;
    //y = y + pace_len;
    float output[8];
    output[0]=4000;
    output[1]=4000;
    output[2]=-500;
    output[3]=x;
    output[4]=y;
    output[5]=z;
    output[6]=theta;
    output[7]=0;
    FILE *fp=fopen("/home/li/cghm/binary.dat","wb");
    fwrite(output,sizeof(float),8,fp);
    fclose(fp);
}

void MainWindow::move_right()
{
    x = x + pace_len;
    //y = y - pace_len;
    float output[8];
    output[0]=4000;
    output[1]=4000;
    output[2]=-500;
    output[3]=x;
    output[4]=y;
    output[5]=z;
    output[6]=theta;
    output[7]=0;
    FILE *fp=fopen("/home/li/cghm/binary.dat","wb");
    fwrite(output,sizeof(float),8,fp);
    fclose(fp);
}

void MainWindow::move_vertically()
{
    z = ui -> height -> value();
    float output[8];
    output[0]=4000;
    output[1]=4000;
    output[2]=-500;
    output[3]=x;
    output[4]=y;
    output[5]=z;
    output[6]=theta;
    output[7]=0;
    FILE *fp=fopen("/home/li/cghm/binary.dat","wb");
    fwrite(output,sizeof(float),8,fp);
    fclose(fp);
}

void MainWindow::rotate()
{
    theta = ui -> rotation -> value()/(-100.00);
    float output[8];
    output[0]=4000;
    output[1]=4000;
    output[2]=-500;
    output[3]=x;
    output[4]=y;
    output[5]=z;
    output[6]=theta;
    output[7]=0;
    FILE *fp=fopen("/home/li/cghm/binary.dat","wb");
    fwrite(output,sizeof(float),8,fp);
    fclose(fp);
}
