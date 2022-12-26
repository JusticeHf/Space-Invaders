#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
//#include <QVector>


class Enemy:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QGraphicsItem *parent = nullptr, int i = 0, int j = 0, int type = 0);
    ~Enemy();
    enum Direction{Left, Right};

    friend class Game;
private slots:
    void move();
    void shoot();
    void decrease();
signals:
    void block();
    void increase(int pos_i, int pos_j, int score);
    void decreaseHealth();
    void stop();
private:
    void _moveleft();
    void _moveright();
    void _movedown();
    Direction dir = Right;
    int pos_i;
    int pos_j;
    int _score;
    QPixmap _anim[2];
    int anim_index = 0;
    QTimer *timer;
};

#endif // ENEMY_H
