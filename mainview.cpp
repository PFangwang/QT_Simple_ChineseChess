#include "mainview.h"
#include "ui_mainview.h"
#include<Qlabel>
#include<QPushButton>
MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    //设置欢迎场景，为以后设置登陆场景做准备
    setFixedSize(600,400);
    setWindowTitle("象棋游戏");
    QLabel*lbl=new QLabel("让我们开始游戏吧！",this);
    lbl->move(200,100);
    QPushButton*btn_start=new QPushButton("确定",this);
    btn_start->move(180,250);
    btn_start->setFixedSize(80,60);
    QPushButton*btn_quit=new QPushButton("退出",this);
    btn_quit->move(300,250);
    btn_quit->setFixedSize(80,60);
    connect(btn_quit,&QPushButton::clicked,this,&MainView::close);

    connect(btn_start,&QPushButton::clicked,this,[=](){
       GameView=new GameScene;
       confirm = new QPushButton("再来一局",GameView);
       cancel = new QPushButton("返回主界面",GameView);
       confirm->setFixedSize(100,50);
       cancel->setFixedSize(100,50);
       confirm->move(600,1000);
       cancel->move(200,1000);
       confirm->setVisible(false);
       cancel->setVisible(false);
       GameView->show();
       this->close();
       connect(GameView,&GameScene::winnerappear,[=](){
           confirm->setVisible(true);
           cancel->setVisible(true);
       });
       connect(cancel,&QPushButton::clicked,[=](){
          GameView->close();
          this->show();
          GameView->destroyed();
       });
       connect(confirm,&QPushButton::clicked,[=](){
           GameView->close();
           GameView->destroyed();
           emit btn_start->click();
       });
    });
}

MainView::~MainView()
{
    delete ui;
}
