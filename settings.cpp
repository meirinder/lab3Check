#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->Apply, SIGNAL(clicked()), this, SLOT(onButtonSend()));

}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_Cancel_clicked()
{
    this->close();
}



void Settings::onButtonSend(){
    emit sendData(atoi(ui->lineEditA->text().toStdString().c_str()),atoi(ui->lineEditB->text().toStdString().c_str()),atoi(ui->lineEditC->text().toStdString().c_str()),
                  atoi(ui->lineEditD->text().toStdString().c_str()),atoi(ui->lineEditM->text().toStdString().c_str()),atoi(ui->lineEditN->text().toStdString().c_str()));
    this->close();
}

