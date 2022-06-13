#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include"pieces.h"
#include<QLabel>
namespace Ui {
class GameScene;
}

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(QWidget *parent = 0);
    ~GameScene();
    void paintEvent(QPaintEvent*);
    int Pos[10][9]={{0},{0}};//棋盘对应的位置有无棋子，0无1红2黑
    int globalfocus;//全局焦点 0代表无 1代表红选中了红 2代表黑选中了黑
    int player;//1为红方 2为黑方 其他代表对局中止或结束
    pieces *temp;
    int movex;
    int movey;
    int nowx;
    int nowy;
    //棋子相应动作 棋手选择 自己值 移动到的地点x y 现在的地点 x y
    void chesaction(int playerchoose,pieces*intemp,int innowx,int innowy);
    //是棋子能否移动的关键规则 棋子种类 棋子x坐标 棋子Y坐标 给定移动坐标X 给定移动坐标Y 缺省值，为有两种行动模式的炮|将|帅所设
    bool isCanMove(int type,int cheseX,int cheseY,int waitX,int waitY,int Now_type=0);

    QLabel *showPlayer=NULL;
signals:
    void moveChese();
    void winnerappear();

private:
    Ui::GameScene *ui;
};

#endif // GAMESCENE_H
