#ifndef PIECE_CHE_H
#define PIECE_CHE_H

#include <QPushButton>

class Piece_che : public QPushButton
{
    Q_OBJECT
public:
    explicit Piece_che(QWidget *parent = nullptr);
    Piece_che(bool color);
    //判断属于哪一方 真为红 假为黑
    bool Color;
    //判断是否被点击了
    bool isClick;


signals:

public slots:
};

#endif // PIECE_CHE_H
