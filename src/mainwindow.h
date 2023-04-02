#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "menu.h"

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

private slots:

    void on_powerButton_clicked();

    void on_mainOptions_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    Menu *mainMenu;
    bool power;

};
#endif // MAINWINDOW_H
