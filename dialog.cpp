#include "dialog.h"
#include "ui_dialog.h"
#include <box2d/box2d.h>
#include <iostream>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    size = 1200;
    resize(size,size);
    image = QImage(size,size,QImage::Format_RGB32);
    image.fill(Qt::white);

    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(updateState()));

    initWorld();

    timer->start(16);
}

void Dialog::initWorld()
{
    world = new World();
    dt = 0.2;
    world->dt = dt;

    Body* b;

    b = world->CreateBody(50,1.0);
    b->position.Set(200,500);
    b->velocity.Set(5,5);
    b->force.SetZero();

    for(int i=0;i<4;i++){
        b = world->CreateBody(10,1.0);
        b->position.Set(qrand()%size,qrand()%size);
        b->velocity.Set(3,3);
        b->force.SetZero();
    }

}

void Dialog::paintEvent(QPaintEvent *)
{
    if(image.isNull()) return;
    QPainter painter(this);
    painter.drawImage(0,0,image);
}

void Dialog::updateState(){
    image.fill(Qt::white);
    QPainter pp(&image);
    QPen pen;
    pen.setColor(Qt::gray);
    QBrush brush(Qt::gray);
    pp.setPen(pen);
    pp.setBrush(brush);

    QColor colors[4] = {Qt::gray, Qt::blue, Qt::yellow, Qt::red};

    float interval = 1.6;
    int cnt = interval/dt;


    while (cnt--) {
        world->Step();
    }

    for(int i=0;i<(int)world->bodyList.size();i++){
        pen.setColor(colors[i%4]);
        brush.setColor(colors[i%4]);
        pp.setPen(pen);
        pp.setBrush(brush);
        Body* b= world->bodyList[i];
        float r = b->radius;
        int s = 2;
        pp.drawEllipse(b->position.x, b->position.y, r*s, r*s);
    }

    update();
}

Dialog::~Dialog()
{
    delete ui;
}

