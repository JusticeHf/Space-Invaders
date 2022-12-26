#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <vector>
#include <QGraphicsPixmapItem>
#include "block.h"
#include "player.h"
#include "enemy.h"
#include <QLabel>
#include "strangeship.h"

#define widthMob 6
#define heightMob 5


class Game:public QGraphicsScene
{
    Q_OBJECT
public:
    Game(QGraphicsScene * parent = nullptr);
    ~Game();
    enum Status {Playing, Lose};
    void start();
    int get_score() const;
    int get_health() const;

    Player *player;
    Status status;

private slots:
    void changeDir();
    void increaseScore(int i, int j, int score);
    void increaseScore();
    void decreaseHealth();
    void spawnShip();
    void removeShip();
    void stopGame();
    void update();

private:
    int _score = 0;
    int _health = 3;
    int _count = heightMob * widthMob;
    int _acceleration = 0;
    bool _existence = false;

    strangeShip *ship;
    QGraphicsPixmapItem *line;
    QTimer *moveTimer;
    QTimer *spawnTimer;
    QTimer *updateTimer;
    std::vector<std::vector<Enemy*>> enemys;
    std::vector<std::vector<block*>> bunker;
    QGraphicsTextItem *health_title, *score_title;
    QGraphicsTextItem *health, *score;

    void spawn();
    void spawnBunker();
    void moveEnemys();
    void initLabels();
};

#endif // GAME_H
