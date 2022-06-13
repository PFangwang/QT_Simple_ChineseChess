#include "piece_che.h"

Piece_che::Piece_che(QWidget *parent) : QPushButton(parent)
{

}

Piece_che::Piece_che(bool color)
{
this->Color=color;
    if(this->Color)
    {
        this->setIcon(QIcon("://Chese/Che_red.png"));
    }
    else
    {
        this->setIcon(QIcon("://Chese/che_black.png"));
    }
    this->setFixedSize(60,60);
    this->isClick=false;
}
