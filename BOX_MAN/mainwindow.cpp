#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initmap();

    connect(this, SIGNAL(change()), this, SLOT(update()));
}

MainWindow::~MainWindow()
{
}
/*
 * 地图初始化函数
 * 设置地图大小和标题
 */
void MainWindow::initmap() {
    resize(SCREEN_WIDTH, SCREEN_HEIGHT); // 初始化屏幕高度宽度
    setWindowIconText(QString("推箱子"));
}
/*
 *  游戏控制函数
 *  输入参数：要前进的方向（UP， DOWN， LEFT， RIGHT）
 */
void MainWindow::gameControl(enum Direction direction) {
    if (direction == UP) { // 上方向
        if (map[man.x - 1][man.y] == FLOOR) { // 上方向为地板
            changeMap(man.x, man.y, FLOOR); // 原位置换为地板
            changeMap(man.x - 1, man.y, MAN); // 上方向位置换为人
        } else if (map[man.x - 1][man.y] == BOX && map[man.x - 2][man.y] == FLOOR) { // 上方向为箱子，箱子上方向为地板
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x - 1, man.y, MAN);
            changeMap(man.x - 2, man.y, BOX);
        } else if (map[man.x - 1][man.y] == BOX && map[man.x - 2][man.y] == DES) { // 上方向为箱子，箱子上方向为目的地
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x - 1, man.y, MAN);
            changeMap(man.x - 2, man.y, HIT);
        }
    } else if (direction == DOWN) {
        if (map[man.x + 1][man.y] == FLOOR) {
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x + 1, man.y, MAN);
        } else if (map[man.x + 1][man.y] == BOX && map[man.x + 2][man.y] == FLOOR) {
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x + 1, man.y, MAN);
            changeMap(man.x + 2, man.y, BOX);
        } else if (map[man.x + 1][man.y] == BOX && map[man.x + 2][man.y] == DES) {
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x + 1, man.y, MAN);
            changeMap(man.x + 2, man.y, HIT);
        }
    } else if (direction == LEFT) {
        if (map[man.x][man.y - 1] == FLOOR) {
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x, man.y - 1, MAN);
        } else if (map[man.x][man.y - 1] == BOX && map[man.x][man.y - 2] == FLOOR) {
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x, man.y - 1, MAN);
            changeMap(man.x, man.y - 2, BOX);
        } else if (map[man.x][man.y - 1] == BOX && map[man.x][man.y - 2] == DES) {
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x, man.y - 1, MAN);
            changeMap(man.x, man.y - 2, HIT);
        }
    } else if (direction == RIGHT) {
        if (map[man.x][man.y + 1] == FLOOR) {
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x, man.y + 1, MAN);
        } else if (map[man.x][man.y + 1] == BOX && map[man.x][man.y + 2] == FLOOR){
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x, man.y + 1, MAN);
            changeMap(man.x, man.y + 2, BOX);
        } else if (map[man.x][man.y + 1] == BOX && map[man.x][man.y + 2] == DES) {
            changeMap(man.x, man.y, FLOOR);
            changeMap(man.x, man.y + 1, MAN);
            changeMap(man.x, man.y + 2, HIT);
        }
    }
}
/*
 * 判断游戏是否结束函数
 * 当地图中所有DES被替换为HIT代表游戏结束
 * 返回值：true为结束， false反之
 */
bool MainWindow::isOver() {
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (map[i][j] == DES) return false;
        }
    }
    return true;
}
/*
 * 改变地图参数函数
 * 改变参数同时发出change()信号， 关联update()函数对图进行渲染
 * 输入：改变的行，列，变成的属性（墙，箱子，人等）
 */
void MainWindow::changeMap(int line, int column, enum Map m) {
    map[line][column] = m;
    emit change();
}
// 重写绘图事件
void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, QPixmap(BLACKGROUND_PATH)); // 绘制背景
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            switch (map[i][j]) {
            case WALL: {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(WALL_PATH)); // 绘制墙
                break;
            }
            case FLOOR: {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(FLOOR_PATH)); // 绘制空地
                break;
            }
            case DES: {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(DES_PATH)); // 绘制目的地
                break;
            }
            case MAN: {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(MAN_PATH)); // 绘制人
                man.x = i; // 记录小人位置
                man.y = j;
                break;
            }
            case BOX: {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(BOX_PATH)); // 绘制箱子
                break;
            }
            case HIT: {
                painter.drawPixmap(X_SHIFT + SIZE * j, Y_SHIFT + SIZE * i, SIZE, SIZE, QPixmap(BOX_1_PATH));
                break;
            }
            default:
                break;
            }
        }
    }
    if (isOver()) {
        QFont font("方正舒体", 30, QFont::ExtraLight, false);
        QPen pen;
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.setFont(font);
        painter.drawText((this->width()/2) - 40, this->height()/2, QString("游戏结束！"));
    }
}
// 重写键盘事件
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) {
        gameControl(UP);
    } else if (event->key() == Qt::Key_A) {
        gameControl(LEFT);
    } else if (event->key() == Qt::Key_D) {
        gameControl(RIGHT);
    } else if (event->key() == Qt::Key_S) {
        gameControl(DOWN);
    } else if (event->key() == Qt::Key_Enter) {

    } else {

    }
}
