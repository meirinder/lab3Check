#ifndef LEVELS_H
#define LEVELS_H

#include <QWidget>
#include "levelsviewmodel.h"



class Levels : public QWidget
{
    Q_OBJECT
public:
    LevelsViewModel *viewModel;
    void readInput();
    void start();

    explicit Levels(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // LEVELS_H
