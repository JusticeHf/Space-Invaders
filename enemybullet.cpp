#include "enemybullet.h"
#include <QTimer>

enemyBullet::enemyBullet(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QString(":/picture/img/enemy_bullet.png"));
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(25);
}

enemyBullet::~enemyBullet()
{
    delete timer;
}

void enemyBullet::move()
{
    setPos(x(), y() + 10);
    if (pos().y() > 600)
    {
        scene()->removeItem(this);
        delete this;
        return;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        auto& r = *(colliding_items[i]);
        if (typeid(r) == typeid(Player))
        {
            scene()->removeItem(this);

            emit hit();
            delete this;
        }
    }
}
