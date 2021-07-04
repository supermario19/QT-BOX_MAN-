#ifndef PERSON_H
#define PERSON_H


struct Person {
    int x; // 人所在行
    int y; // 人所在列
};

enum Direction { //人的方向
    UP,
    DOWN,
    LEFT,
    RIGHT
};

#endif // PERSON_H
