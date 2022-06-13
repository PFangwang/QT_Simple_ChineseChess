#ifndef PIECES_H
#define PIECES_H

#include <QPushButton>

class pieces : public QPushButton
{
    Q_OBJECT
public:
    explicit pieces(QWidget *parent = nullptr);
    pieces(QString str,int type,int x,int y,int redorblack);
    int RedorBlack;//真为红方
    //0为红车，1为黑车，2为红马，3为黑马，4为红象，5为黑相，6为红士，7为黑士，
    //8为红炮，9为黑炮，10为红兵，11为黑卒，12为帅，13为将
    int m_type;
    //位置信息
    int pieces_x;
    int pieces_y;
    int i=0;
    QString iconStr;
signals:
    void flickerStart();
    void flickerEnd();
public slots:
};

#endif // PIECES_H
