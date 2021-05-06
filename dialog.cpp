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

    int w = 50;
    b = world->CreateBody(w,1.0);
    b2Vec2 pos(200,450);
    b->initRect(pos,w,w);
    b->velocity.Set(5,0);
    b->force.SetZero();

//    w = 1;
    for(int i=0;i<40;i++){
        b = world->CreateBody(w,1.0);
        pos.Set(qrand()%size,qrand()%size);
//        pos.Set(500,500);
        b->initRect(pos,qrand()%10 + w, qrand()%10 +w);
        b->velocity.Set(2,2);
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
        float w = b->w;
        float h = b->h;
        int s = 2;
//        pp.drawEllipse(b->position.x, b->position.y, r*s, r*s);
        pp.drawRect(b->position.x, b->position.y, w*s, h*s);

    }

    update();
}

Dialog::~Dialog()
{
    delete ui;
}

