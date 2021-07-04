#ifndef MAP_H
#define MAP_H

#define LINE 9 // 地图行数
#define COLUMN 12 // 地图列数

enum Map { // 地图属性
    WALL, // 墙
    FLOOR, // 空地
    DES, // 目的地
    MAN, // 人
    BOX, // 箱子
    HIT // 箱子到达目的地
};

#endif // MAP_H
