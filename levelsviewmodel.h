#ifndef LEVELSVIEWMODEL_H
#define LEVELSVIEWMODEL_H
#include <QWidget>

struct LevelsBoundaries{
    int color;
    double higher;
    double lower;
    LevelsBoundaries(int color,double higher,double lower){
        this->color=color;
        this->lower=lower;
        this->higher=higher;
    }
};

class LevelsViewModel
{
public:
    LevelsViewModel();
    LevelsViewModel(int,int,int,int,int,int,std:: vector <QColor*>);
    std::vector <double> val;
    std::vector <int> colInd;
    std::vector <LevelsBoundaries> divide;

    int a,b,c,d,m,n;
    std::vector <LevelsBoundaries> colorss;
    std::vector <LevelsBoundaries> divideColor;
    std:: vector <QColor*> colors;

    void start(int, int);
    double f(double, double);
    double aproximation(double, double, double);
};

#endif // LEVELSVIEWMODEL_H
