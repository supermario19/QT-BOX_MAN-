#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"
#include "person.h"
#include "postion.h"
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QFont>
#include <QPen>

#define SCREEN_WIDTH 960 // 屏幕宽度
#define SCREEN_HEIGHT 768 // 屏幕高度
#define LINE 9 // 地图行数
#define COLUMN 12 // 地图列数
#define LEVEL 1 // 关卡
#define SIZE 61 // 格子（地图上墙，箱子...）尺寸
#define X_SHIFT 110 // x偏移量
#define Y_SHIFT 130 // y偏移量
#define BLACKGROUND_PATH ":/images/blackground" // 背景图片
#define WALL_PATH ":/images/wall" // 墙图片
#define FLOOR_PATH ":/images/floor" // 空地图片
#define DES_PATH ":/images/des" // 目的图片
#define MAN_PATH ":/images/man" // 人图片
#define BOX_PATH ":/images/box" // 箱子图片
#define BOX_1_PATH ":/images/box_1" // 箱子推到指定位置图片
#define MAX_STEP 65 // 最大步数限制

extern int map[LINE][COLUMN];

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    struct Person man; // 人的位置
    struct Postion pre_pos; // 之前的位置
    int step;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initmap();
    void gameControl(enum Direction);
    void changeMap(int line, int column, enum Map);
    bool isOver();
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
public slots:
    void gameOverControl();
    void gameSuccessControl();
signals:
    void change();
    void gameover();
    void gamesuccess();
};
#endif // MAINWINDOW_H
