#ifndef LEGEND_H
#define LEGEND_H

#include <QWidget>
#include "legendviewmodel.h"



class Legend : public QWidget
{
    Q_OBJECT
public:
    explicit Legend(QWidget *parent = nullptr);
    QImage *image;
    uchar *bits;
    LegendViewModel *viewModel;

    void readInput();
    void paintEvent(QPaintEvent *);
    void smoothShading(std::vector <LegendBoundaries>, std::vector <double>, std::vector <int>);
    void start();
};

#endif // LEGEND_H
