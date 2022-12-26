#include "player.h"


Player::Player(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/picture/img/gun.png"));
}

void Player::move_left()
{
    if (pos().x() > 0)
    {
        setPos(x() - 10, y());
    }
}

void Player::move_right()
{
    if (pos().x() + 55 < 800)
    {
        setPos(x() + 10, y());
    }
}

void Player::shoot()
{
    if (_existence == true)
    {
        return;
    }
    Bullet *bullet = new Bullet(nullptr, this);
    bullet->setPos(x() + 25, y());
    scene()->addItem(bullet);
    _existence = true;
}


