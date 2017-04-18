#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qstring.h>
#include <QMainWindow>
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QMap>
#include <iostream>
#include <stdio.h>
#include <cmath>
//#include <cstring>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton *btn;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn_W;
    QPushButton *btn_B;
    QPushButton *pan_btn[19][19];
    QPushButton *hard[5];
    QPushButton *help;


    QMap<int, QMap<int, int> > location;
    QMap<int, QMap<int, int> > pan;
    //int pan[19][19];
    int score[3];
    int stone_count = 0;
    int stone, p1_s, p2_s, pc_s;
    int play = 0;
    bool playing = true;
    int depth_main;
    int MAX_x, MAX_y;
    int stop = 1;
    int MAX_length;
    int MAX_count;

    int pc_do_count[3][50];

    int MAX_x_PC[10][100];
    int MAX_y_PC[10][100];
    int prev_score1; //최고점수 확인 후 점수 복귀를 위한 변수
    int prev_score2;
    int MAX_x_PLAYER[10][10];
    int MAX_y_PLAYER[10][10];
    int SCORE_PC[10];
    int SCORE_PLAYER[10];
    int first;
    QLabel *l2;
    QLabel *l1;
    QString str1;
    QString buf;
    QLabel *IbView;
    QLabel *label;

    int PC_DO_CHECK(int stone, int num);
    int PC_DO_CHECK_SCORE(int stone);

    void Think_Depth(int depth, int pc);
    int PC_DO(int stone, int depth);
    int CHECK_SCORE(int stone);

    int Think_do_somewhere(int stone, int num, int start, int end);
    int Think_do_somewhere_left(int stone, int num, int start, int end);
    int Think_do_somewhere_right(int stone, int num, int start, int end);

    int Think_do_somewhere_for_five(int stone, int num, int start, int end);


    int Think_do(int stone, int num, int start, int end);
    int Think_do_not(int stone, int not_stone, int num, int start, int end);

    void Game_end();

private slots:
    void btn_c();
    void PLAY_start();
    //void PLAY_WITH_PC_start();
    void pan_c();
    void Choice_stone();
    void Choice_hard();
    void Help();

};

#endif // MAINWINDOW_H
