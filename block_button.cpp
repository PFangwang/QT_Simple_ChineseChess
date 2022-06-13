#include "block_button.h"

block_button::block_button(QWidget *parent) : QPushButton(parent)
{
    isClicked=false;
    isEmpty=false;
    this->setFixedSize(90,90);
}
