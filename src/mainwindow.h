#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>

#include "testdata.h"
#include "settings.h"
#include "loghistory.h"
#include "scores.h"

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
   void countDown();
   void session(int pace, int level, QMap<int, int>, QVector<double>);
   void simulateBreathPace(int pace);

   // void startSession():
    // random generator picks emotion:graph
   // breath pace
    // start timer
   // every 5
    // metric ->updateCoherence(
   // metric ->updateAchievement
   //when 100 secs is over or session is ended:
   // return metric
   // session(information:metric, date, length)
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
    settings setting;
    loghistory log;
    scores s;
//    testdata *data;
};
#endif // MAINWINDOW_H
