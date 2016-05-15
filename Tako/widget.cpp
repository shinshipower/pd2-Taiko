#include "widget.h"
#include "ui_widget.h"
int game_score;
MyItem* Act;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    timer=new QTimer(this);
    refresh_t=new QTimer(this);
    trigger = new QTimer(this);
    scene = new QGraphicsScene(this);
    Act=NULL;
    ui->Runline->setScene(scene);
    scene->setSceneRect(0,0,512,70);
    ui->Runline->setBackgroundBrush(QBrush(Qt::gray,Qt::SolidPattern));

    connect(trigger,SIGNAL(timeout()),this,SLOT(gen_drum()));
    connect(timer,SIGNAL(timeout()),this,SLOT(game_timer_countdown()));
    connect(refresh_t,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(refresh_t,SIGNAL(timeout()),SLOT(Rf_Score()));
        refresh_t->start(3);

    counter_30=TIMEOUT;
    game_score=0;

    ui->Counter->display(counter_30);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_released()
{
    close();
}

void Widget::on_pushButton_2_released()//start
{
    ui->stackedWidget->setCurrentIndex(1);

    QLineF topLine(scene->sceneRect().topLeft(),
                       scene->sceneRect().topRight());
        QLineF leftLine(scene->sceneRect().topLeft(),
                       scene->sceneRect().bottomLeft());
        QLineF rightLine(scene->sceneRect().topRight(),
                       scene->sceneRect().bottomRight());
        QLineF bottomLine(scene->sceneRect().bottomLeft(),
                       scene->sceneRect().bottomRight());

        QPen myPen = QPen(Qt::red);

        //scene->addLine(topLine, myPen);
        //scene->addLine(leftLine, myPen);
        //scene->addLine(rightLine, myPen);
        //scene->addLine(bottomLine, myPen);
            scene->addEllipse(scene->sceneRect().topLeft().x()+25,scene->sceneRect().topLeft().y()+10,50,50);
        // adding items to the scene

            MyItem *item = new MyItem();
            scene->addItem(item);


    timer->start(1000);
    trigger->start(300);

    ui->Counter->display(counter_30);

}

void Widget::on_pushButton_3_released()//back to main menu
{
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();
    counter_30=TIMEOUT;
    game_score = 0;

}

void Widget::game_timer_countdown()
{
    if(counter_30>0)
    {
        counter_30--;
        ui->Counter->display(counter_30);
    }
    else
    {
        timer->stop();
        counter_30=TIMEOUT;
        ui->stackedWidget->setCurrentIndex(2);
        score_line=score_line.number(game_score);
        ui->Score->setText(score_line);
    }
}

void Widget::Rf_Score(){

    score_line=score_line.number(game_score);
    ui->Score_2->setText(score_line);
}

void Widget::on_pushButton_4_released()
{
    close();
}

void Widget::on_pushButton_5_released()
{
    game_score=0;
    counter_30=TIMEOUT;
    ui->stackedWidget->setCurrentIndex(0);
}


MyItem::MyItem()
{
    // random start rotation


    // set the speed
    RG = rand()%2;
    speed = 1;  // 5 pixels
    valid = 0;
    // random start position
    int startX = 512;
    int startY = 10;



    setPos(mapToParent(startX,startY));
}

QRectF MyItem::boundingRect() const
{
    return QRect(0,0,50,50);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    // basic collision detection
        if(RG){
        QPen    pen(Qt::green);
        QBrush brush(Qt::green);
        painter->setPen(pen);
        painter->setBrush(brush);
        }else{
            QPen    pen(Qt::red);
            QBrush brush(Qt::red);
            painter->setPen(pen);
            painter->setBrush(brush);
        }

    painter->drawEllipse(rect);
}

void MyItem::advance(int phase)
{
    if(!phase) return;

    QPointF location = this->pos();
    double X=this->pos().x();
    double Y=this->pos().y();
    if(!valid){if(X<75) {valid = 1;Act = this; std::cout<<"  valid "<<endl;}}
    if(X<-75){Act=NULL;delete this;}else{
    X = X - speed;
    std::cout<<X<<endl<<"  ";

    setPos(X,Y);}
}

void MyItem::doCollision()
{
    // get a new position

    // change the angle with randomness
    if(qrand() % 1)
    {
        setRotation(rotation() + (180 + (qrand() % 10)));
    }
    else
    {
        setRotation(rotation() + (180 + (qrand() % -10)));
    }

    // check if the new position is in bounds
    QPointF newPoint = mapToParent(-(boundingRect().width()), -(boundingRect().width() + 2));

    if(!scene()->sceneRect().contains((newPoint)))
    {
        // move back in bounds
        newPoint = mapToParent(0,0);
    }
    else
    {
        // set the new position
        setPos(newPoint);
    }
}

void Widget::keyPressEvent(QKeyEvent *e){

    switch(e->key()){
        case Qt::Key_J:
            if(Act!=NULL){
            if(Act->RG == RED){
            if(Act->valid){
                delete Act;
                Act=NULL;
                std::cout<<"  J  "<<endl;game_score++;std::cout<<" score = "<<game_score<<endl;}}}
        break;
        case Qt::Key_K:
            if(Act!=NULL){
            if(Act->RG == GRE){
            if(Act->valid){
                delete Act;
            Act=NULL;
            std::cout<<"  K  "<<endl;game_score++;std::cout<<" score = "<<game_score<<endl;}}}
        break;
        default:
            break;
    }



}


void Widget::gen_drum(){

    trigger->stop();
    MyItem *item = new MyItem();
    scene->addItem(item);
    trigger->start((rand()%10)*200);




}

/*
void MyItem::keyPressEvent(QKeyEvent *event){

    switch(event->key()){
        case Qt::Key_J:
            if(valid){std::cout<<"  J  "<<endl;game_score++;std::cout<<" score = "<<game_score<<endl; valid == 0;delete this;}
        default:
            break;
    }




}*/
