#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    mainMenu = new Menu("MAIN MENU", {"PROGRAMS","FREQUENCY","HISTORY"}, nullptr);

    // power button toggle
    ui ->views ->setVisible(false);
    ui ->battery ->setVisible(false);
    ui ->upButton ->setEnabled(false);
    ui ->downButton ->setEnabled(false);
    ui ->leftButton ->setEnabled(false);
    ui ->rightButton ->setEnabled(false);
    ui ->menuButton ->setEnabled(false);
    ui ->okButton ->setEnabled(false);
    ui ->backButton ->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

// on-click function: power button toggle
void MainWindow::on_powerButton_clicked() {
    if (power == true) {
        power = false;
    } else {
        power = true;
    }
    changePowerStatus(power);
}

void MainWindow::changePowerStatus(bool status) {
    ui ->views ->setVisible(status);
    ui ->battery ->setVisible(status);
    ui ->upButton ->setEnabled(status);
    ui ->downButton ->setEnabled(status);
    ui ->leftButton ->setEnabled(status);
    ui ->rightButton ->setEnabled(status);
    ui ->menuButton ->setEnabled(status);
    ui ->okButton ->setEnabled(status);
    ui ->backButton ->setEnabled(status);
}
