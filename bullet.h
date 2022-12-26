#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "strangeship.h"

class Player;

class Bullet:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent = nullptr, Player *pl = nullptr);
    ~Bullet();
private slots:
    void move();
private:
    Player *_player;
    QTimer *_timer;
};

#endif // BULLET_H
