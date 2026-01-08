#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>
#include <QMediaContent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QMediaPlayer* player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("click.mp3"));;
    player->play();
}

