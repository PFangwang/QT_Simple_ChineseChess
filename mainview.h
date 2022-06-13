#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include"gamescene.h"
namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();
    GameScene *GameView=NULL;

    QPushButton *confirm=NULL;
    QPushButton *cancel=NULL;
private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
