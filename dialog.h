#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPainter>
#include "world.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    void initWorld();
    void paintEvent(QPaintEvent *);
    ~Dialog();
private slots:
    void updateState();
private:
    Ui::Dialog *ui;
    QTimer *timer;
    QImage image;
    int size;

    World* world;
    float dt;
};
#endif // DIALOG_H
