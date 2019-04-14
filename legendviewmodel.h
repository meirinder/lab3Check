#ifndef LEGENDVIEWMODEL_H
#define LEGENDVIEWMODEL_H
#include <QWidget>

struct LegendBoundaries{
    int color;
    double higher;
    double lower;
    LegendBoundaries(int color,double higher,double lower){
        this->color=color;
        this->lower=lower;
        this->higher=higher;
    }
};

struct LegendNewColor{
    int place;
    int r;
    int g;
    int b;
    LegendNewColor(int place,int r,int g,int b){
        this->r=r;
        this->g=g;
        this->b=b;
        this->place=place;
    }
};

class LegendViewModel
{
public:
    LegendViewModel();

    LegendViewModel(int,int,int,int,int,int,std:: vector <QColor*>);
    int a,b,c,d,m,n;

    bool isSmoothed;
    std:: vector <QColor*> colors;
    std::vector <double> val;
    std::vector <int> colInd;
    std::vector <LegendBoundaries> divide;

    void start(int,int);
    double approximation(double, double, double);
    double f(double, double);
};

#endif // LEGENDVIEWMODEL_H
