#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <iostream>
#include <QKeyEvent>
#define TIMEOUT 30
#define RED 0
#define GRE 1



namespace Ui {
class Widget;
class MyItem;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    friend Ui::MyItem;
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void game_timer_countdown();

    void on_pushButton_4_released();

    void on_pushButton_5_released();

    void Rf_Score();

    void gen_drum();
protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::Widget *ui;
    QTimer *timer;
    QTimer *refresh_t;
    QTimer *trigger;
    int counter_30;

    QString score_line;
    QGraphicsScene *scene;




};

class MyItem : public QGraphicsItem
{
public:
    bool RG;
    friend Ui::Widget;
        bool valid;
    MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int phase);
    //void keyPressEvent(QKeyEvent *event);

private:
    qreal angle, speed;
    void doCollision();

};

#endif // WIDGET_H
