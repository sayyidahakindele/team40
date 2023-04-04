#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "defs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   void changePowerStatus(bool status);
   void updateMenu(QString option);

   // void startSession():
    // random generator picks emotion
    // start timer
    // for loop
    //


   // updateGraph


private slots:

    void on_powerButton_clicked();
    void on_upButton_clicked();
    void on_downButton_clicked();
    void on_okButton_clicked();
    void on_menuButton_clicked();
    void on_backButton_clicked();

private:
    Ui::MainWindow *ui;
    bool power;

};
#endif // MAINWINDOW_H
