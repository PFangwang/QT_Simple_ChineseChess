#ifndef BLOCK_BUTTON_H
#define BLOCK_BUTTON_H

#include <QPushButton>

class block_button : public QPushButton
{
    Q_OBJECT
public:
    explicit block_button(QWidget *parent = nullptr);
    bool isEmpty;
    bool isClicked;
signals:

public slots:
};

#endif // BLOCK_BUTTON_H
