#ifndef STRANGESHIP_H
#define STRANGESHIP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>

class Bullet;

class strangeShip:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    strangeShip(QGraphicsItem *parent = nullptr);
    ~strangeShip();
    enum Direction{Right = 0, Left = 1};

    friend class Game;
signals:
    void death();
    void block();
private slots:
    void move();
private:
    Direction dir;
    QTimer *timer;
};

#endif // STRANGESHIP_H
