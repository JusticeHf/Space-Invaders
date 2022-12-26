#include "game.h"
#include <QTimer>
//#include <QDebug>
//#include <iostream>

Game::Game(QGraphicsScene *parent)
{
    status = Playing;
    setSceneRect(0, 0, 800, 600);
    player = new Player();
    player->setPos(400, 550);
    addItem(player);
    QImage image(QString(":/picture/img/line.png"));
    line = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    addItem(line);
    line->setPos(3, 599);
}

Game::~Game()
{
    delete moveTimer;
    delete spawnTimer;
    delete player;
    delete line;
    delete updateTimer;
}

void Game::start()
{
    spawn();
    moveEnemys();
    spawnBunker();
    initLabels();
    spawnTimer = new QTimer();
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnShip()));
    spawnTimer->start(10000);
    updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(25);
}

int Game::get_score() const
{
    return _score;
}

int Game::get_health() const
{
    return _health;
}

void Game::spawn()
{
    for (size_t i = 0; i < heightMob; i++)
    {
        std::vector<Enemy*> tmp;
        for (size_t j = 0; j < widthMob; j++)
        {
            int type;
            if (i == heightMob - 3 || i == heightMob - 4)
            {
                type = 1;
            }
            else if (i == heightMob - 1 || i == heightMob - 2)
            {
                type = 2;
            }
            else
            {
                type = 0;
            }
            Enemy *enemy =new Enemy(nullptr, i, j, type);
            tmp.push_back(enemy);
            enemy->setPos(200 + 70 * j, 100 + 50 * i);
            addItem(enemy);
            connect(enemy, SIGNAL(block()), this, SLOT(changeDir()));
            connect(enemy, SIGNAL(increase(int, int, int)), this, SLOT(increaseScore(int, int, int)));
            connect(enemy, SIGNAL(decreaseHealth()), this, SLOT(decreaseHealth()));
            connect(enemy, SIGNAL(stop()), this, SLOT(stopGame()));
        }
        enemys.push_back(tmp);
    }
}

void Game::spawnBunker()
{
    for (size_t count = 0; count < 4; count++)
    {
        for (size_t i = 0; i < 3; i++)
        {
            std::vector<block*> tmp;
            for (size_t j = 0; j < 4; j++)
            {
                block *brick = new block();
                tmp.push_back(brick);
                brick->setPos(115 + count * 175 + j * 22, 455 + i * 22);
                addItem(brick);
                if ((i == 2 || i == 1) & (j == 1 || j == 2))
                {
                    removeItem(brick);
                    delete brick;
                    tmp[j] = nullptr;
                }
            }
            bunker.push_back(tmp);
        }
    }
}

void Game::moveEnemys()
{
    moveTimer = new QTimer();
    for (auto& vec : enemys)
    {
        for (auto& enemy : vec)
        {
            connect(moveTimer, SIGNAL(timeout()), enemy, SLOT(move()));
        }
    }
    moveTimer->start(500);
}

void Game::initLabels()
{
    QFont f("Arial", 15, QFont::Bold);
    health_title = new QGraphicsTextItem();
    health_title->setDefaultTextColor(Qt::white);
    health_title->setPlainText(QString("Lives :"));
    health_title->setFont(f);
    health_title->setPos(610, 10);
    addItem(health_title);

    score_title = new QGraphicsTextItem();
    score_title->setDefaultTextColor(Qt::white);
    score_title->setPlainText(QString("Score : "));
    score_title->setFont(f);
    score_title->setPos(10, 10);
    addItem(score_title);

    score = new QGraphicsTextItem();
    score->setDefaultTextColor(Qt::green);
    score->setPlainText("0");
    score->setFont(f);
    score->setPos(100, 10);
    addItem(score);

    health = new QGraphicsTextItem();
    health->setDefaultTextColor(Qt::green);
    health->setPlainText("3");
    health->setFont(f);
    health->setPos(700, 10);
    addItem(health);
}

void Game::increaseScore(int i, int j, int score)
{
    _score += score;
    enemys[i][j] = nullptr;
    _count--;
    if ( _count == 0)
    {
        delete moveTimer;
        enemys.clear();
        _count = heightMob * widthMob;
        if (_health < 4)
        {
            _health++;
        }
        spawn();
        _acceleration = 0;
        moveEnemys();
    }
}

void Game::increaseScore()
{
    int random = rand() % 6 + 1;
    _score += random * 50;
    removeItem(ship);
    delete ship;
    _existence = false;
}

void Game::decreaseHealth()
{
    _health--;
    if (_health == 0)
    {
        stopGame();
    }
}

void Game::spawnShip()
{
    int random  = rand() % 2;
    if (random == 0 && _existence == false)
    {
        ship = new strangeShip();
        _existence = true;
        connect(ship, SIGNAL(block()), this, SLOT(removeShip()));
        connect(ship, SIGNAL(death()), this, SLOT(increaseScore()));
        if (ship->dir == strangeShip::Left)
        {
            ship->setPos(750, 50);
        }
        else
        {
            ship->setPos(5, 50);
        }
        addItem(ship);
    }
}

void Game::removeShip()
{
    removeItem(ship);
    delete ship;
    _existence = false;
}

void Game::stopGame()
{
    moveTimer->stop();
    spawnTimer->stop();
    updateTimer->stop();
    for (auto& vec : enemys)
    {
        for (auto& enemy : vec)
        {
            if (enemy == nullptr)
            {
                continue;
            }
            enemy->timer->stop();
            enemy->hide();
        }
    }
    status = Lose;
}

void Game::update()
{
    score->setPlainText(QString::number(_score));
    health->setPlainText(QString::number(_health));
}

void Game::changeDir()
{
    for (auto& vec : enemys)
    {
        for (auto& enemy : vec)
        {
            if (enemy == nullptr)
            {
                continue;
            }
            enemy->_movedown();
            if (enemy->dir == Enemy::Right)
            {
                enemy->dir = Enemy::Left;
            }
            else
            {
                enemy->dir = Enemy::Right;
            }
        }
    }
    _acceleration += 20;
    moveTimer->setInterval(500 - _acceleration);
}
