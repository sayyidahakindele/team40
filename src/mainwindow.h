#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QVector>
#include <QLCDNumber>
#include <QSlider>
#include <QMessageBox>

#include "loghistory.h"
#include "scores.h"
#include "settings.h"
#include "testdata.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // constructor
    MainWindow(QWidget *parent = nullptr);

   void startSession(QTimer& timer, QTimer& countdown);
   void changePowerStatus(bool status);
   void updateMenu(QString option);
   void printHistories();
   void printHistory(int id);
   void session(int pace, int level, QMap<int, int>, QVector<double>);
   void beep();
   void endSession(QTimer& timer, QTimer& countdown);
   void startTimer(QTimer& timer, QTimer& countdown, QLCDNumber& tracker,QSlider& breathPacer, int& countTime, int& getPace);

   // session graphics
   void updateDisplay(QTimer& timer, QLCDNumber& coh, QLCDNumber& ach, QVector<double>& arrScores, int& i, double& achieveSum, int& countTime);
   void simulateGraph();
   void updateLights(int color);
   void simulateBreathPace(QTimer& timer, int pace, QSlider& slide);
   void drainBattery();
   void returnToMain();
   QTimer *batteryTimer;

    // destructor
    ~MainWindow();


private slots:
    // on-click functions
    void on_powerButton_clicked();
    void on_upButton_clicked();
    void on_downButton_clicked();
    void on_okButton_clicked();
    void on_menuButton_clicked();
    void on_backButton_clicked();
    void on_contactButton_clicked();
    void on_saveButton_clicked();
    void update_graph();

private:
    Ui::MainWindow *ui;
    bool power;
    bool contact;
    settings setting;
    loghistory log;
    scores s;
    testdata *data;
    int runTime = 0;
    double PI = 3.14;
};
#endif // MAINWINDOW_H

