#include "enemy.h"
#include "enemybullet.h"
#include <QTimer>
#include <stdlib.h>


Enemy::Enemy(QGraphicsItem *parent, int i, int j, int type):
    QGraphicsPixmapItem(parent)
{
    if (type == 0)
    {
        setPixmap(QString(":/picture/img/enemy31.png"));
        _anim[0] = QPixmap(":/picture/img/enemy31.png");
        _anim[1] = QPixmap(":/picture/img/enemy32.png");
        _score = 40;
    }
    else if (type == 1)
    {
        setPixmap(QString(":/picture/img/enemy1.png"));
        _anim[0] = QPixmap(":/picture/img/enemy1.png");
        _anim[1] = QPixmap(":/picture/img/enemy2.png");
        _score = 20;
    }
    else
    {
        setPixmap(QString(":/picture/img/enemy21.png"));
        _anim[0] = QPixmap(":/picture/img/enemy21.png");
        _anim[1] = QPixmap(":/picture/img/enemy22.png");
        _score = 10;
    }
    pos_i = i;
    pos_j = j;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(shoot()));
    timer->start(1000);
}

Enemy::~Enemy()
{
    emit increase(pos_i, pos_j, _score);
    delete timer;
}


void Enemy::move()
{

    if (pos().y() > 450)
    {
        emit stop();
    }
    if (dir == Left)
    {
        _moveleft();
    }
    else
    {
        _moveright();
    }
    if (pos().x() + 75 >= 800 || pos().x() <= 0)
    {
        emit block();
    }
}

void Enemy::_moveleft()
{
    anim_index++;
    if (anim_index == 2)
    {
        anim_index = 0;
    }
    setPixmap(_anim[anim_index]);
    setPos(x() - 5, y());
}

void Enemy::_moveright()
{
    anim_index++;
    if (anim_index == 2)
    {
        anim_index = 0;
    }
    setPixmap(_anim[anim_index]);
    setPos(x() + 5, y());
}

void Enemy::_movedown()
{
    setPos(x(), y() + 15);
}

void Enemy::shoot()
{
    int random = rand() % 100;
    if (random < 6)
    {
        enemyBullet *bullet = new enemyBullet();
        connect(bullet, SIGNAL(hit()), this, SLOT(decrease()));
        bullet->setPos(x() + 25, y());
        scene()->addItem(bullet);
    }
}

void Enemy::decrease()
{
    emit decreaseHealth();
}


