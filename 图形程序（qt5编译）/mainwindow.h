#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    float x=0,y=0,z=0,theta=0;
    float pace_len = 400;
    //float pace_ang = 0.1;
public slots:
    void move_forward();
    void move_backward();
    void move_left();
    void move_right();
    void move_vertically();
    void rotate();
    void endprocess();
    void startprocess();
private:
    Ui::MainWindow *ui;
    QProcess *program;
};

#endif // MAINWINDOW_H
