#ifndef WORKSPACE_H
#define WORKSPACE_H
#include <QWidget>
#include <fstream>
#include <vector>
#include "workspaceviewmodel.h"



class WorkSpace: public QWidget {
    Q_OBJECT
public:
    explicit WorkSpace(QWidget *parent = nullptr);
    QImage *image;
    uchar *bits;
    WorkspaceViewModel *viewModel;

    void paintEvent(QPaintEvent *);
    void readInput();
    void smoothShading(std::vector <WorkBoundaries>, std::vector <double>, std::vector <int>);

    void make(int, int);
    void setPixel(int, int, QColor);
    void drawLine(int, int, int, int);
    void isolines(std::vector <double>, std::vector <int>, std::vector <WorkBoundaries>);
    void paintGdrid();

public slots:
    void recieveData(int, int, int, int, int, int);

};

#endif // WORKSPACE_H
