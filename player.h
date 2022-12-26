#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "bullet.h"

class Player:public QGraphicsPixmapItem
{
public:
    Player(QGraphicsItem * parent = nullptr);

    friend class MainWindow;
    friend class Game;
    friend class Bullet;
private:
    void move_left();
    void move_right();
    void shoot();
    bool _existence = false;
};

#endif // PLAYER_H
