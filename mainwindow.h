#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionSettings_triggered();

    void on_actionSmooth_shading_triggered();

    void on_actionGrid_triggered();

    void on_actionIsolines_triggered();

private:
    Ui::MainWindow *ui;
    Settings* settings;


};

#endif // MAINWINDOW_H
