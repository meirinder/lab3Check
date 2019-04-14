#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    settings = new Settings();
    QObject::connect(settings, &Settings::sendData, ui->widget, &WorkSpace::recieveData);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSettings_triggered()
{
    settings->exec();
}

void MainWindow::on_actionSmooth_shading_triggered()
{
    if(ui->actionSmooth_shading->isChecked()){
        ui->widget->viewModel->isSmoothed=true;
        ui->widget_2->viewModel->isSmoothed=true;
    }else {
        ui->widget->viewModel->isSmoothed=false;
        ui->widget_2->viewModel->isSmoothed=false;
    }
    repaint();
}

void MainWindow::on_actionGrid_triggered()
{
    if(ui->actionGrid->isChecked()){
        ui->widget->viewModel->isGrided=true;
    }else {
        ui->widget->viewModel->isGrided=false;
    }
    repaint();
}


void MainWindow::on_actionIsolines_triggered()
{
    if(ui->actionIsolines->isChecked()){
        ui->widget->viewModel->isIsolined=true;
    }else {
        ui->widget->viewModel->isIsolined=false;
    }
    repaint();
}
