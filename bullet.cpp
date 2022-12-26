#include "bullet.h"
#include "game.h"
#include <QTimer>


Bullet::Bullet(QGraphicsItem *parent, Player *pl):QGraphicsPixmapItem(parent)
{
    _player = pl;
    setPixmap(QString(":/picture/img/bullet.png"));
    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(move()));
    _timer->start(25);
}

Bullet::~Bullet()
{
    _player->_existence = false;
    delete _timer;
}

void Bullet::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        auto& r = *(colliding_items[i]);
        if ((typeid(r) == typeid(Enemy)))
        {
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
        }
    }
    setPos(x(), y() - 10);
    if (pos().y() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}

