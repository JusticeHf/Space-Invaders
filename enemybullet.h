#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "player.h"
#include "game.h"

class enemyBullet:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemyBullet(QGraphicsItem * parent = nullptr);
    ~enemyBullet();
private slots:
    void move();
signals:
    void hit();
private:
    QTimer *timer;
};

#endif // ENEMYBULLET_H
