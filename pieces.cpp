#include "pieces.h"
#include<QTimer>
pieces::pieces(QWidget *parent) : QPushButton(parent)
{

}

pieces::pieces(QString str,int type,int x,int y,int redorblack)
{
    this->setIcon(QIcon(str));
    this->setIconSize(QSize(60,60));
    this->setFixedSize(60,60);
    this->m_type=type;
    this->pieces_x=x;
    this->pieces_y=y;
    this->RedorBlack=redorblack;
    this->iconStr=str;
    QTimer *timer=new QTimer(this);

    connect(this,&pieces::flickerStart,this,[=](){
        timer->start(300);
    });
    connect(this,&pieces::flickerEnd,this,[=](){
        timer->stop();
        this->setVisible(true);
    });
    connect(timer,&QTimer::timeout,this,[=](){
        i++;
        if(i%2==1)
        {
            this->hide();
        }
        else
        {
            this->setVisible(true);
        }
    });
}
