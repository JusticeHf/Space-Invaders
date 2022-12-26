#include "strangeship.h"
#include "bullet.h"
#include <stdlib.h>
#include "game.h"

strangeShip::strangeShip(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QString(":/picture/img/ship.png"));
    int random = rand() % 2;
    dir = Direction(random);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(8);
}

strangeShip::~strangeShip()
{
    delete timer;
}

void strangeShip::move()
{
    if (dir == Left)
    {
        setPos(x() - 1, y());
    }
    else
    {
        setPos(x() + 1, y());
    }
    if (pos().x() >= 800 || pos().x() <= 0)
    {
        emit block();
    }
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        auto& r = *(colliding_items[i]);
        if ((typeid(r) == typeid(Bullet)))
        {
            emit death();
            delete colliding_items[i];
        }
    }
}

