#include "levels.h"
#include <fstream>
#include <QLabel>

Levels::Levels(QWidget *parent) : QWidget(parent)
{
    readInput();
    start();
    QList <QLabel *> lstLbl;
    QLabel *lbl;
    lbl = new QLabel(QString::number((int)viewModel->colorss.at(0).lower),this);
    lbl->show();
    for(int i =0;i<viewModel->colorss.size();i++){
        lbl = new QLabel(QString::number((int)viewModel->colorss.at(i).higher),this);
        int nnv = 881/viewModel->colorss.size();
        lbl->move((i+1)*(nnv+13),0);
        lbl->show();
    }
}



void Levels::start(){
    viewModel->start(width(),height());
}


void Levels::readInput()
{
    std::ifstream file;
    file.open("/Users/savely/Downloads/Lab3/input.txt");
    if(!file.is_open()){
        exit(1);
    }
    int a,b,c,d,m,n;
    std::vector <QColor*> colors;
    file>>a>>b>>c>>d>>m>>n;
    while(!file.eof()){
        int r,g,b;
        file>>r>>g>>b;
        colors.push_back(new QColor(r,g,b));
    }
    this->viewModel = new LevelsViewModel(a,b,c,d,m,n,colors);
    file.close();
}
