#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>

class block:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    block(QGraphicsItem *parent = nullptr);
    ~block();
    friend class Game;
private slots:
    void lifetime();
private:
    QTimer *timer;
    int _health = 3;
};

#endif // BLOCK_H
