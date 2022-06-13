#include "gamescene.h"
#include "ui_gamescene.h"
#include<QPainter>
#include<QDebug>
#include<QFont>
GameScene::GameScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameScene)
{
    ui->setupUi(this);
    setFixedSize(920,1200);

    QFont font;
    font.setFamily("Times New Roman");
    font.setPointSize(18);
    showPlayer=new QLabel(this);
    showPlayer->setFixedSize(150,50);
    showPlayer->setText("红方回合");
    showPlayer->setFont(font);
    showPlayer->move(385,20);

    //红棋先走
    player=true;
    //全局焦点设为0
    globalfocus=0;
    //创建棋盘按钮
    for(int j=0;j<10;j++)
    {
        for(int k=0;k<9;k++)
        {
            QPushButton*btn=new QPushButton(this);
            btn->setFixedSize(60,60);
            btn->move(70+k*90,110+j*90);
            connect(btn,&QPushButton::clicked,this,[=](){                  
                if(globalfocus!=0)
                {
                    if(!(isCanMove(temp->m_type,temp->pieces_x,temp->pieces_y,j,k,temp->m_type)))
                    {
                        return ;
                    }
                    else
                    {
                        movex=btn->x();
                        movey=btn->y();
                        temp->move(movex,movey);
                        emit temp->flickerEnd();
                        globalfocus=0;//全局焦点置为零
                        temp->pieces_x=j;//Pos矩阵对应值需要改变
                        temp->pieces_y=k;
                        Pos[nowx][nowy]=0;//原本对应的矩阵位置设为零
                        if(player==2)//上一步是黑方动棋
                        {
                            Pos[j][k]=2;
                            player=1;
                            showPlayer->setText("红方回合");
                        }
                        else if(player==1)
                        {
                            Pos[j][k]=1;
                            player=2;
                            showPlayer->setText("黑方回合");
                        }
                    }             
                }
            });
        }
    }
    int i=0;
    //创建红车
    while(i<2)
    {
    pieces *red_che =new pieces("://Chese/Che_red.png",0,0,0+i*8,1);
    red_che->setParent(this);
    red_che->move(70+i*720,110);
    Pos[red_che->pieces_x][red_che->pieces_y]=1;
    connect(red_che,&pieces::clicked,[=](){
        chesaction(red_che->RedorBlack,red_che,red_che->pieces_x,red_che->pieces_y);
    });
    i++;
    }
    //创建黑车
    i=0;
    while(i<2)
    {
        pieces *black_che =new pieces("://Chese/che_black.png",1,9,0+i*8,2);
        black_che->setParent(this);
        black_che->move(70+i*720,920);
        Pos[black_che->pieces_x][black_che->pieces_y]=2;
        connect(black_che,&pieces::clicked,[=](){
            chesaction(black_che->RedorBlack,black_che,black_che->pieces_x,black_che->pieces_y);
        });
        i++;
    }
    //创建红马
    i=0;
    while(i<2)
    {
    pieces *red_ma =new pieces("://Chese/ma_red.png",2,0,1+i*6,1);
    red_ma->setParent(this);
    red_ma->move(160+i*540,110);
    Pos[red_ma->pieces_x][red_ma->pieces_y]=1;
    connect(red_ma,&pieces::clicked,[=](){
        chesaction(red_ma->RedorBlack,red_ma,red_ma->pieces_x,red_ma->pieces_y);
    });
    i++;
    }
    //创建黑马
    i=0;
    while(i<2)
    {
    pieces *black_ma =new pieces("://Chese/ma_black.png",3,9,1+i*6,2);
    black_ma->setParent(this);
    black_ma->move(160+i*540,920);
    Pos[black_ma->pieces_x][black_ma->pieces_y]=2;
    connect(black_ma,&pieces::clicked,[=](){
        chesaction(black_ma->RedorBlack,black_ma,black_ma->pieces_x,black_ma->pieces_y);
    });
    i++;
    }
    //创建红象
    i=0;
    while(i<2)
    {
    pieces *red_xiang =new pieces("://Chese/xiang_red.png",4,0,2+i*4,1);
    red_xiang->setParent(this);
    red_xiang->move(250+i*360,110);
    Pos[red_xiang->pieces_x][red_xiang->pieces_y]=1;
    connect(red_xiang,&pieces::clicked,[=](){
        chesaction(red_xiang->RedorBlack,red_xiang,red_xiang->pieces_x,red_xiang->pieces_y);
    });
    i++;
    }
    //创建黑相
    i=0;
    while(i<2)
    {
    pieces *black_xiang =new pieces("://Chese/xiang_black.png",5,9,2+i*4,2);
    black_xiang->setParent(this);
    black_xiang->move(250+i*360,920);
    Pos[black_xiang->pieces_x][black_xiang->pieces_y]=2;
    connect(black_xiang,&pieces::clicked,[=](){
        chesaction(black_xiang->RedorBlack,black_xiang,black_xiang->pieces_x,black_xiang->pieces_y);
    });
    i++;
    }
    //创建红士
    i=0;
    while(i<2)
    {
    pieces *red_shi =new pieces("://Chese/shi_red.png",6,0,3+i*2,1);
    red_shi->setParent(this);
    red_shi->move(340+i*180,110);
    Pos[red_shi->pieces_x][red_shi->pieces_y]=1;
    connect(red_shi,&pieces::clicked,[=](){
        chesaction(red_shi->RedorBlack,red_shi,red_shi->pieces_x,red_shi->pieces_y);
    });
    i++;
    }
    //创建黑士
    i=0;
    while(i<2)
    {
    pieces *black_shi =new pieces("://Chese/shi_black.png",7,9,3+i*2,2);
    black_shi->setParent(this);
    black_shi->move(340+i*180,920);
    Pos[black_shi->pieces_x][black_shi->pieces_y]=2;
    connect(black_shi,&pieces::clicked,[=](){
        chesaction(black_shi->RedorBlack,black_shi,black_shi->pieces_x,black_shi->pieces_y);
    });
    i++;
    }
    //创建红炮
    i=0;
    while(i<2)
    {
    pieces *red_pao =new pieces("://Chese/pao_red.png",8,2,1+i*6,1);
    red_pao->setParent(this);
    red_pao->move(160+i*540,290);
    Pos[red_pao->pieces_x][red_pao->pieces_y]=1;
    connect(red_pao,&pieces::clicked,[=](){
        chesaction(red_pao->RedorBlack,red_pao,red_pao->pieces_x,red_pao->pieces_y);
    });
    i++;
    }
    //创建黑炮
    i=0;
    while(i<2)
    {
    pieces *black_pao =new pieces("://Chese/pao_black.png",9,7,1+i*6,2);
    black_pao->setParent(this);
    black_pao->move(160+i*540,740);
    Pos[black_pao->pieces_x][black_pao->pieces_y]=2;
    connect(black_pao,&pieces::clicked,[=](){
        chesaction(black_pao->RedorBlack,black_pao,black_pao->pieces_x,black_pao->pieces_y);
    });
    i++;
    }
    //创建红兵
    i=0;
    while(i<5)
    {
    pieces *bing =new pieces("://Chese/bing.png",10,3,0+i*2,1);
    bing->setParent(this);
    bing->move(70+i*180,380);
    Pos[bing->pieces_x][bing->pieces_y]=1;
    connect(bing,&pieces::clicked,[=](){
        chesaction(bing->RedorBlack,bing,bing->pieces_x,bing->pieces_y);
    });
    i++;
    }
    //创建黑卒
    i=0;
    while(i<5)
    {
    pieces *zu =new pieces("://Chese/zu.png",11,6,0+i*2,2);
    zu->setParent(this);
    zu->move(70+i*180,650);
    Pos[zu->pieces_x][zu->pieces_y]=2;
    connect(zu,&pieces::clicked,[=](){
        chesaction(zu->RedorBlack,zu,zu->pieces_x,zu->pieces_y);
    });
    i++;
    }
    //创建帅
    pieces *shuai =new pieces("://Chese/shuai.png",12,0,4,1);
    shuai->setParent(this);
    shuai->move(430,110);
    Pos[shuai->pieces_x][shuai->pieces_y]=1;
    connect(shuai,&pieces::clicked,[=](){
        chesaction(shuai->RedorBlack,shuai,shuai->pieces_x,shuai->pieces_y);
    });
    //创建将
    pieces *jiang =new pieces("://Chese/jiang.png",13,9,4,2);
    jiang->setParent(this);
    jiang->move(430,920);
    Pos[jiang->pieces_x][jiang->pieces_y]=2;
    connect(jiang,&pieces::clicked,[=](){
        chesaction(jiang->RedorBlack,jiang,jiang->pieces_x,jiang->pieces_y);
    });
}

GameScene::~GameScene()
{
    delete ui;
}

void GameScene::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    //棋盘绘制
    int i=0;
    while(i++<10)
    paint.drawLine(100,50+i*90,820,50+i*90);
    i=0;
    while(i++<9)
    {
    paint.drawLine(10+i*90,140,10+i*90,500);
    }
    i=0;
    while(i++<9)
    {
     paint.drawLine(10+i*90,590,10+i*90,950);
    }
    paint.drawLine(370,140,550,320);
    paint.drawLine(550,140,370,320);
    paint.drawLine(370,770,550,950);
    paint.drawLine(550,770,370,950);

    paint.drawLine(50,545,870,545);
    paint.drawLine(50,500,50,590);
    paint.drawLine(870,500,870,590);
}

void GameScene::chesaction(int playerchoose, pieces *intemp,int innowx, int innowy)
{
    if(player==playerchoose)
    {
        if(globalfocus==1)
        {
            emit temp->flickerEnd();
        }
        globalfocus=1;
        temp=intemp;
        nowx=innowx;
        nowy=innowy;
        emit temp->flickerStart();
    }
    else//此时是另一方点击了棋子
    {
        if(globalfocus==1)//有全局焦点，这是待被吃的棋子
        {
            emit temp->flickerEnd();
            if(isCanMove(temp->m_type,temp->pieces_x,temp->pieces_y,intemp->pieces_x,intemp->pieces_y,intemp->m_type))
            {
                if(intemp->m_type==12)//被吃的是帅，黑方赢了
                {
                    showPlayer->setText("黑方获胜");
                    player=4;//对局结束
                    emit winnerappear();
                }
                if(intemp->m_type==13)//被吃的是将，红方赢了
                {
                    showPlayer->setText("红方获胜");
                    player=4;//对局结束
                    emit winnerappear();
                }
                intemp->setVisible(false);
                temp->move(intemp->x(),intemp->y());
                Pos[nowx][nowy]=0;
                temp->pieces_x=intemp->pieces_x;
                temp->pieces_y=intemp->pieces_y;
                if(player==2)
                {
                    Pos[temp->pieces_x][temp->pieces_y]=2;
                    player=1;
                    showPlayer->setText("红方回合");
                }
                else if(player==1)
                {
                    Pos[temp->pieces_x][temp->pieces_y]=1;
                    player=2;
                    showPlayer->setText("黑方回合");
                }
                temp->setVisible(true);
            }
        }
        globalfocus=0;

    }
}

bool GameScene::isCanMove(int type, int cheseX, int cheseY,int waitX,int waitY,int Now_type)
{
    bool moveCondition=false;
    int Shi_Red_Black=0;
    switch (type) {
    case 0:
    case 1:
        //车的逻辑 只能横走或者竖走
        if((cheseX!=waitX)&&(cheseY!=waitY))
        {
            return false;
        }
        //竖着走
        else if((cheseY==waitY)&&(cheseX!=waitX))
        {
            if(cheseX<waitX)
            {
            for(int i=cheseX+1;i<waitX;i++)//检测竖向是否有其他棋子
            {
                if((Pos[i][cheseY]==1)||(Pos[i][cheseY]==2)) //中途有棋子
                {
                    return false;
                }
            }
                return true;//可以走
            }
            else
            {
                for(int i=waitX+1;i<cheseX;i++)//检测竖向是否有其他棋子
                {
                    if((Pos[i][cheseY]==1)||(Pos[i][cheseY]==2)) //中途有棋子
                    {
                        return false;
                    }
                }
                    return true;//可以走
            }
        }
        //横着走
        else if((cheseX==waitX)&&(cheseY!=waitY))
        {
            if(cheseY<waitY)
            {
            for(int i=cheseY+1;i<waitY;i++)//检测横向是否有其他棋子
            {
                if((Pos[cheseX][i]==1)||(Pos[cheseX][i]==2)) //中途有棋子
                {
                    return false;
                }
            }
                return true;//可以走
            }
            else
            {
                for(int i=waitY+1;i<cheseY;i++)//检测横向是否有其他棋子
                {
                    if((Pos[cheseX][i]==1)||(Pos[cheseX][i]==2)) //中途有棋子
                    {
                    return false;
                    }
                }
                return true;//可以走
            }
        }
        break;
    case 2:
    case 3:
        //马的逻辑 走日且不能有马腿
        if(((waitX-cheseX)==2)&&((waitY-cheseY)==1)&&Pos[cheseX+1][cheseY]==0) return true;//右下方竖日
        if(((waitX-cheseX)==1)&&((waitY-cheseY)==2)&&Pos[cheseX][cheseY+1]==0) return true;//右下方横日
        if(((waitX-cheseX)==-2)&&((waitY-cheseY)==1)&&Pos[cheseX-1][cheseY]==0) return true;//右上方竖日
        if(((waitX-cheseX)==-1)&&((waitY-cheseY)==2)&&Pos[cheseX][cheseY+1]==0) return true;//右上方横日
        if(((waitX-cheseX)==-2)&&((waitY-cheseY)==-1)&&Pos[cheseX-1][cheseY]==0) return true;//左上方竖日
        if(((waitX-cheseX)==-1)&&((waitY-cheseY)==-2)&&Pos[cheseX][cheseY-1]==0) return true;//左上方横日
        if(((waitX-cheseX)==2)&&((waitY-cheseY)==-1)&&Pos[cheseX+1][cheseY]==0) return true;//左下方竖日
        if(((waitX-cheseX)==1)&&((waitY-cheseY)==-2)&&Pos[cheseX][cheseY-1]==0) return true;//左下方横日
        return false;
        break;
    case 4:
    case 5:
        //象的逻辑 走田，不能有象腿且不能过河
        if(((waitX-cheseX)==2)&&((waitY-cheseY)==2)&&Pos[cheseX+1][cheseY+1]==0) moveCondition=true;//右下方田
        if(((waitX-cheseX)==-2)&&((waitY-cheseY)==2)&&Pos[cheseX-1][cheseY+1]==0) moveCondition=true;//右上方田
        if(((waitX-cheseX)==2)&&((waitY-cheseY)==-2)&&Pos[cheseX+1][cheseY-1]==0) moveCondition=true;//左下方田
        if(((waitX-cheseX)==-2)&&((waitY-cheseY)==-2)&&Pos[cheseX-1][cheseY-1]==0) moveCondition=true;//左上方田
        if(type==4)//红象
        {
            if((moveCondition)&&waitX<=4) //不能过河
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if(type==5)//黑相
        {
            if((moveCondition)&&waitX>4) //不能过河
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        break;
    case 6:
    case 7:
        //士的逻辑 走九宫格内斜线
        if(type==6) Shi_Red_Black=1;
        if(type==7) Shi_Red_Black=8;
        if((cheseX!=Shi_Red_Black))//士不在九宫格第二行下一步就只能去第二行中点
        {
            if((waitX==Shi_Red_Black)&&(waitY==4)) return true;
            else return false;
        }
        else//在第二行下一步也只能去四个点
        {
            if(abs(waitX-cheseX)==1&&abs(waitY-cheseY)==1)
            {
                return true;
            }
            return false;
        }
        break;
    case 8:
    case 9:
        //炮的逻辑 横走或者竖走 吃子中间要有一个棋子
        if(type==Now_type)//说明是要移动该棋子 使用车的逻辑即可
        {
            if((cheseX!=waitX)&&(cheseY!=waitY))
            {
                return false;
            }
            //竖着走
            else if((cheseY==waitY)&&(cheseX!=waitX))
            {
                if(cheseX<waitX)
                {
                for(int i=cheseX+1;i<waitX;i++)//检测竖向是否有其他棋子
                {
                    if((Pos[i][cheseY]==1)||(Pos[i][cheseY]==2)) //中途有棋子
                    {
                        return false;
                    }
                }
                    return true;//可以走
                }
                else
                {
                    for(int i=waitX+1;i<cheseX;i++)//检测竖向是否有其他棋子
                    {
                        if((Pos[i][cheseY]==1)||(Pos[i][cheseY]==2)) //中途有棋子
                        {
                            return false;
                        }
                    }
                        return true;//可以走
                }
            }
            //横着走
            else if((cheseX==waitX)&&(cheseY!=waitY))
            {
                if(cheseY<waitY)
                {
                for(int i=cheseY+1;i<waitY;i++)//检测横向是否有其他棋子
                {
                    if((Pos[cheseX][i]==1)||(Pos[cheseX][i]==2)) //中途有棋子
                    {
                        return false;
                    }
                }
                    return true;//可以走
                }
                else
                {
                    for(int i=waitY+1;i<cheseY;i++)//检测横向是否有其他棋子
                    {
                        if((Pos[cheseX][i]==1)||(Pos[cheseX][i]==2)) //中途有棋子
                        {
                        return false;
                        }
                    }
                    return true;//可以走
                }
            }
        }
        else//要吃子
        {
            int chese_Num=0;//跨距中的棋子数
            if((cheseX!=waitX)&&(cheseY!=waitY)) return false;
            //竖着走
            else if((cheseY==waitY)&&(cheseX!=waitX))
            {
                if(cheseX<waitX)
                {
                for(int i=cheseX+1;i<waitX;i++)//检测竖向是否有其他棋子
                {
                    if((Pos[i][cheseY]==1)||(Pos[i][cheseY]==2)) //中途有棋子
                    {
                        chese_Num++;
                    }
                }
                if(chese_Num==1) return true;
                return false;
                }
                else
                {
                    for(int i=waitX+1;i<cheseX;i++)//检测竖向是否有其他棋子
                    {
                        if((Pos[i][cheseY]==1)||(Pos[i][cheseY]==2)) //中途有棋子
                        {
                            chese_Num++;
                        }
                    }
                    if(chese_Num==1) return true;
                    return false;
                }
            }
            //横着走
            else if((cheseX==waitX)&&(cheseY!=waitY))
            {
                if(cheseY<waitY)
                {
                for(int i=cheseY+1;i<waitY;i++)//检测竖向是否有其他棋子
                {
                    if((Pos[cheseX][i]==1)||(Pos[cheseX][i]==2)) //中途有棋子
                    {
                        chese_Num++;
                    }
                }
                if(chese_Num==1) return true;
                return false;
                }
                else
                {
                    for(int i=waitY+1;i<cheseY;i++)//检测竖向是否有其他棋子
                    {
                        if((Pos[cheseX][i]==1)||(Pos[cheseX][i]==2)) //中途有棋子
                        {
                        chese_Num++;
                        }
                    }
                    if(chese_Num==1) return true;
                    return false;
                }
            }
        }
        break;
    case 10:
        //兵的逻辑 一次走一步，不能向后走，未过河前只能向前，过河后能跑左右
        if(waitX<=4)//过河前
        {
            if(((waitX-cheseX)==1)&&(waitY==cheseY))
            {
                return true;
            }
            return false;
        }
        else//过河后
        {
            if(((waitX-cheseX)==1)&&(waitY==cheseY)) return true;
            if(((waitY-cheseY)==1)&&(waitX==cheseX)) return true;
            if(((waitY-cheseY)==-1)&&(waitX==cheseX)) return true;
            return false;
        }
        break;
    case 11:
        //卒的逻辑 一次走一步，不能向后走，未过河前只能向前，过河后能跑左右
        if(waitX>4)//过河前
        {
            if(((waitX-cheseX)==-1)&&(waitY==cheseY))
            {
                return true;
            }
            return false;
        }
        else//过河后
        {
            if(((waitX-cheseX)==-1)&&(waitY==cheseY)) return true;
            if(((waitY-cheseY)==1)&&(waitX==cheseX)) return true;
            if(((waitY-cheseY)==-1)&&(waitX==cheseX)) return true;
            return false;
        }
        break;
    case 12:
        //补充逻辑 将帅不相见 否则可以吃
        if(Now_type==13)
        {
            if(cheseY==waitY)
            {
                for(int i=cheseX+1;i<waitX;i++)
                {
                    if(Pos[i][cheseY]!=0)
                    {
                        return false;
                    }
                }
                return true;
            }
        }
        //帅的逻辑 九宫格内一次一步走
        if((waitX<3)&&waitY>=3&&waitY<=5)
        {
            if(waitX==cheseX)
            {
                if(abs(waitY-cheseY)==1)
                {
                    return true;
                }
                return false;
            }
            if(waitY==cheseY)
            {
                if(abs(waitX-cheseX)==1)
                {
                    return true;
                }
                return false;
            }
            return false;
        }
        return false;
        break;
    case 13:
        //补充逻辑 将帅不相见 否则可以吃
        if(Now_type==12)
        {
            if(cheseY==waitY)
            {
                for(int i=cheseX-1;i>waitX;i--)
                {
                    if(Pos[i][cheseY]!=0)
                    {
                        return false;
                    }
                }
                return true;
            }
        }
        //将的逻辑 九宫格内一次一步走
        if((waitX>6)&&waitY>=3&&waitY<=5)
        {
            if(waitX==cheseX)
            {
                if(abs(waitY-cheseY)==1)
                {
                    return true;
                }
                return false;
            }
            if(waitY==cheseY)
            {
                if(abs(waitX-cheseX)==1)
                {
                    return true;
                }
                return false;
            }
            return false;
        }
        return false;
        break;
    default:
        return false;
        break;
    }
    return true;
}





