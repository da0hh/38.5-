
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>
#include <QPainter>

QImage blurImage(QImage source, int blurRadius)
{
    if(source.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));

    auto *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurRadius);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage res(source.size(), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter painter(&res);
    scene.render(&painter, QRectF(),
                QRectF(0, 0, source.width(), source.height()));

    return res;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->usersPicture->setFixedSize(400, 300);

    connect(ui->slider, &QSlider::valueChanged, this, &MainWindow::on_slider_valueChanged) ;
    ui->slider->setRange(0, 10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Image", "", "Images (*.png *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        sourceImage.load(fileName);

        int currentBlurValue = ui->slider->value();
        QImage blurred = blurImage(sourceImage, currentBlurValue);
        ui->usersPicture->setPixmap(QPixmap::fromImage(blurred.scaled(
                                                                   ui->usersPicture->width(),
                                                                   ui->usersPicture->height(),
                                                                   Qt::KeepAspectRatio,
                                                                   Qt::SmoothTransformation)));
    }
}

void MainWindow::on_slider_valueChanged(int value)
{
    if(!sourceImage.isNull())
    {
        qDebug() << "Blur value changed to: " << value;

        QImage blurred = blurImage(sourceImage, value);

        ui->usersPicture->setPixmap(QPixmap::fromImage(blurred.scaled(
                                                           ui->usersPicture->width(),
                                                           ui->usersPicture->height(),
                                                           Qt::KeepAspectRatio,
                                                           Qt::SmoothTransformation
                                                           )));
    }
}
