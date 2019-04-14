#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT
public:
    int* a,b,c,d,m,n;
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:

    void on_Cancel_clicked();

private:
    Ui::Settings *ui;
signals:
    void sendData(int, int, int, int, int, int);
private slots:
    void onButtonSend();
};

#endif // SETTINGS_H
