#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsView>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Space Invaders");
    setFixedSize(825, 660);
    ui->graphicsView->setStyleSheet("QGraphicsView {border : none;}");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);

    game = new Game();
    ui->graphicsView->setScene(game);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_score()));
    timer->start(25);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
    delete timer;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        game->player->move_left();
        break;
    case Qt::Key_Left:
        game->player->move_left();
        break;
    case Qt::Key_D:
        game->player->move_right();
        break;
    case Qt::Key_Right:
        game->player->move_right();
        break;
    case Qt::Key_Space:
        game->player->shoot();
        break;
    default:
        break;
    }
}

void MainWindow::update_score()
{
    if (game->status == Game::Lose)
    {
        timer->stop();
        ui->stackedWidget->setCurrentIndex(2);
    }
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    game->start();
}

