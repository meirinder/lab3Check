#ifndef WORKSPACEVIEWMODEL_H
#define WORKSPACEVIEWMODEL_H
#include <QWidget>
#include <cmath>


struct WorkCoordinates{
    int x;
    int y;
    WorkCoordinates(int x,int y){
        this->x=x;
        this->y=y;
    }
};

struct WorkBoundaries{
    int color;
    double higher;
    double lower;
    WorkBoundaries(int color,double higher,double lower){
        this->color=color;
        this->lower=lower;
        this->higher=higher;
    }
};

struct NewColor{
    int place;
    int r;
    int g;
    int b;
    NewColor(int place,int r,int g,int b){
        this->r=r;
        this->g=g;
        this->b=b;
        this->place=place;
    }
};


class WorkspaceViewModel
{
public:
    WorkspaceViewModel();
    WorkspaceViewModel(int,int,int,int,int,int,std:: vector <QColor*>);

    std::vector <double> val;
    std::vector <int> colInd;
    std::vector <WorkBoundaries> divide;
    int a,b,c,d,m,n;
    bool isSmoothed;
    bool isIsolined;
    std::vector <WorkBoundaries> divideColor;
    bool isGrided;
    std:: vector <QColor*> colors;

    void start(int, int);
    double aproximation(double, double,double);
    double f(double, double);

};

#endif // WORKSPACEVIEWMODEL_H
