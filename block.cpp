#include "block.h"
#include "enemybullet.h"

block::block(QGraphicsItem *parent)
{
    setPixmap(QString(":/picture/img/block1.png"));
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(lifetime()));
    timer->start(10);
}

block::~block()
{
    delete timer;
}

void block::lifetime()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        auto& r = *(colliding_items[i]);
        if ((typeid(r) == typeid(Bullet)) || (typeid(r) == typeid(enemyBullet)))
        {
            _health--;
            if (_health == 2)
            {
                setPixmap(QString(":/picture/img/block2.png"));
            }
            else if (_health == 1)
            {
                setPixmap(QString(":/picture/img/block3.png"));
            }
            else
            {
                scene()->removeItem(this);
                delete this;
            }
            delete colliding_items[i];
        }
    }
}
