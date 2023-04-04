#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // default settings
    // hides tabs and disables buttons
    ui ->views ->setCurrentIndex(0);
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
    //toggles between disabled menu and main menu
    if (power == true) {
        power = false;
        ui ->mainOptions ->clear();
    } else {
        power = true;
        QListWidgetItem *session = new QListWidgetItem("CREATE NEW SESSION");
        QListWidgetItem *settings = new QListWidgetItem("SETTINGS");
        QListWidgetItem *history = new QListWidgetItem("HISTORY");
        QListWidgetItem *reset = new QListWidgetItem("RESET");
        ui ->mainOptions ->addItem(session);
        ui ->mainOptions ->addItem(settings);
        ui ->mainOptions ->addItem(history);
        ui ->mainOptions ->addItem(reset);
        ui ->mainOptions ->setCurrentRow(0);
        ui ->views ->setCurrentIndex(0);
        ui ->heading ->setText("MAIN MENU");
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

// on-click function: up button clicked
void MainWindow::on_upButton_clicked() {
    int current = ui ->mainOptions ->currentRow();
    if (current > 0) {
        ui ->mainOptions ->setCurrentRow(current - 1);
    } else {
        ui ->mainOptions ->setCurrentRow(ui ->mainOptions ->count() - 1);
    }
}

// on-click function: down button clicked
void MainWindow::on_downButton_clicked() {
    int current = ui ->mainOptions ->currentRow();
    if (current < ui ->mainOptions ->count() - 1) {
        ui ->mainOptions ->setCurrentRow(current + 1);
    } else {
        ui ->mainOptions ->setCurrentRow(0);
    }
}

// on-click function: ok button clicked
void MainWindow::on_okButton_clicked() {
    QString selectedItem = ui ->mainOptions ->currentItem() ->text();
    // updateMenu only called when a new submenu is created or a being difrected to a different menu
    if (selectedItem == "CREATE NEW SESSION" | selectedItem == "SETTINGS" | selectedItem == "HISTORY" | selectedItem == "CHANGE CHALLENGE LEVEL" | selectedItem == "CHANGE BREATH PACE" | selectedItem == "HISTORY" | selectedItem == "RESET" | selectedItem == "YES" | selectedItem == "NO") {
        updateMenu(selectedItem);
    } else { // this covers breath and challenge. Should call a function in each one that updates the respective quality
        // set selected option for metric
        QString currentTab = ui ->mainOptions ->item(0) ->text();
        if (currentTab == "1 - BEGINNER") {
            qDebug() << (ui ->mainOptions ->currentRow() + 1); // just for debug purposes. replace with function
        } else if (currentTab == "1") {
            qDebug() << (ui ->mainOptions ->currentRow() + 1); // just for debug purposes. replace with function
        }
    }

}

void MainWindow::updateMenu(QString option) {
    if (option == "CREATE NEW SESSION") {   // takes you to the session view tab
        ui ->views ->setCurrentIndex(1);
        //startSession
    } else if (option == "SETTINGS") {      // creates sub menu by clearing current items and replacing it with submenu items. sets the current row to the first one and changes the heading
        ui ->mainOptions ->clear();
        ui ->heading ->setText("SETTINGS");
        QListWidgetItem *challengeLevel = new QListWidgetItem("CHANGE CHALLENGE LEVEL");
        QListWidgetItem *breathPace = new QListWidgetItem("CHANGE BREATH PACE");
        ui ->mainOptions ->addItem(challengeLevel);
        ui ->mainOptions ->addItem(breathPace);
        ui ->mainOptions ->setCurrentRow(0);
    } else if (option == "HISTORY") {       // creates sub menu by clearing current items and replacing it with submenu items. sets the current row to the first one and changes the heading
        ui ->mainOptions ->clear();
        ui ->heading ->setText("HISTORY");
        ui ->mainOptions ->addItem("VIEW");
        ui ->mainOptions ->addItem("CLEAR");
        ui ->mainOptions ->setCurrentRow(0);
    } else if (option == "CHANGE CHALLENGE LEVEL") {    // creates sub menu by clearing current items and replacing it with submenu items. sets the current row to the first one and changes the heading
        ui ->mainOptions ->clear();
        ui ->heading ->setText("SETTINGS");
        QListWidgetItem *beginner = new QListWidgetItem("1 - BEGINNER");
        QListWidgetItem *intermediate = new QListWidgetItem("2 - INTERMEDIATE");
        QListWidgetItem *hard = new QListWidgetItem("3 - HARD");
        QListWidgetItem *advanced = new QListWidgetItem("4 - ADVANCED");
        ui ->mainOptions ->addItem(beginner);
        ui ->mainOptions ->addItem(intermediate);
        ui ->mainOptions ->addItem(hard);
        ui ->mainOptions ->addItem(advanced);
        ui ->mainOptions ->setCurrentRow(0);
    } else if (option == "CHANGE BREATH PACE") {        // creates sub menu by clearing current items and replacing it with submenu items. sets the current row to the first one and changes the heading
        ui ->mainOptions ->clear();
        ui ->heading ->setText("SETTINGS");
        ui ->mainOptions ->addItem("1");
        ui ->mainOptions ->addItem("2");
        ui ->mainOptions ->addItem("3");
        ui ->mainOptions ->addItem("4");
        ui ->mainOptions ->addItem("5");
        ui ->mainOptions ->addItem("6");
        ui ->mainOptions ->addItem("7");
        ui ->mainOptions ->addItem("8");
        ui ->mainOptions ->addItem("9");
        ui ->mainOptions ->addItem("10");
        ui ->mainOptions ->addItem("11");
        ui ->mainOptions ->addItem("12");
        ui ->mainOptions ->addItem("13");
        ui ->mainOptions ->addItem("14");
        ui ->mainOptions ->addItem("15");
        ui ->mainOptions ->addItem("16");
        ui ->mainOptions ->addItem("17");
        ui ->mainOptions ->addItem("18");
        ui ->mainOptions ->addItem("19");
        ui ->mainOptions ->addItem("20");
        ui ->mainOptions ->addItem("21");
        ui ->mainOptions ->addItem("22");
        ui ->mainOptions ->addItem("23");
        ui ->mainOptions ->addItem("24");
        ui ->mainOptions ->addItem("25");
        ui ->mainOptions ->addItem("26");
        ui ->mainOptions ->addItem("27");
        ui ->mainOptions ->addItem("28");
        ui ->mainOptions ->addItem("29");
        ui ->mainOptions ->addItem("30");
        ui ->mainOptions ->setCurrentRow(9);
    } else if (option == "RESET") {         // creates sub menu by clearing current items and replacing it with submenu items. sets the current row to the first one and changes the heading
        ui ->mainOptions ->clear();
        ui ->heading ->setText("ARE YOU SURE YOU WANT TO RESET?");
        ui ->mainOptions ->addItem("YES");
        ui ->mainOptions ->addItem("NO");
        ui ->mainOptions ->setCurrentRow(0);
    } else if (option == "YES") {       // resets challenge and breath // returns back to main menu. sets the current row to the first one and changes the heading
        ui ->mainOptions ->clear();
        QListWidgetItem *session = new QListWidgetItem("CREATE NEW SESSION");
        QListWidgetItem *settings = new QListWidgetItem("SETTINGS");
        QListWidgetItem *history = new QListWidgetItem("HISTORY");
        QListWidgetItem *reset = new QListWidgetItem("RESET");
        ui ->mainOptions ->addItem(session);
        ui ->mainOptions ->addItem(settings);
        ui ->mainOptions ->addItem(history);
        ui ->mainOptions ->addItem(reset);
        ui ->mainOptions ->setCurrentRow(0);
        ui ->views ->setCurrentIndex(0);
        ui ->heading ->setText("MAIN MENU");
    } else if (option == "NO") {    // returns back to main menu. sets the current row to the first one and changes the heading
        ui ->mainOptions ->clear();
        QListWidgetItem *session = new QListWidgetItem("CREATE NEW SESSION");
        QListWidgetItem *settings = new QListWidgetItem("SETTINGS");
        QListWidgetItem *history = new QListWidgetItem("HISTORY");
        QListWidgetItem *reset = new QListWidgetItem("RESET");
        ui ->mainOptions ->addItem(session);
        ui ->mainOptions ->addItem(settings);
        ui ->mainOptions ->addItem(history);
        ui ->mainOptions ->addItem(reset);
        ui ->mainOptions ->setCurrentRow(0);
        ui ->views ->setCurrentIndex(0);
        ui ->heading ->setText("MAIN MENU");
    }
}

// on-click function: menu button clicked
void MainWindow::on_menuButton_clicked() {          // rests to main menu
    ui ->views ->setCurrentIndex(0);
    ui ->mainOptions ->clear();
    QListWidgetItem *session = new QListWidgetItem("CREATE NEW SESSION");
    QListWidgetItem *settings = new QListWidgetItem("SETTINGS");
    QListWidgetItem *history = new QListWidgetItem("HISTORY");
    QListWidgetItem *reset = new QListWidgetItem("RESET");
    ui ->mainOptions ->addItem(session);
    ui ->mainOptions ->addItem(settings);
    ui ->mainOptions ->addItem(history);
    ui ->mainOptions ->addItem(reset);
    ui ->mainOptions ->setCurrentRow(0);
    ui ->heading ->setText("MAIN MENU");
}

// on-click function: back button clicked
void MainWindow::on_backButton_clicked() {          // figures out what parent it should return to by checking the first item and replacing current menu with parent menu
    QString currentTab = ui ->mainOptions ->item(0) ->text();
    if (currentTab == "1 - BEGINNER" | currentTab == "1") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("SETTINGS");
        QListWidgetItem *challengeLevel = new QListWidgetItem("CHANGE CHALLENGE LEVEL");
        QListWidgetItem *breathPace = new QListWidgetItem("CHANGE BREATH PACE");
        ui ->mainOptions ->addItem(challengeLevel);
        ui ->mainOptions ->addItem(breathPace);
        ui ->mainOptions ->setCurrentRow(0);
    } else if (currentTab == "CHANGE CHALLENGE LEVEL" | currentTab == "VIEW") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("MAIN MENU");
        QListWidgetItem *session = new QListWidgetItem("CREATE NEW SESSION");
        QListWidgetItem *settings = new QListWidgetItem("SETTINGS");
        QListWidgetItem *history = new QListWidgetItem("HISTORY");
        QListWidgetItem *reset = new QListWidgetItem("RESET");
        ui ->mainOptions ->addItem(session);
        ui ->mainOptions ->addItem(settings);
        ui ->mainOptions ->addItem(history);
        ui ->mainOptions ->addItem(reset);
        ui ->mainOptions ->setCurrentRow(0);
    } else if (currentTab == "YES") {
        ui ->mainOptions ->clear();
        QListWidgetItem *session = new QListWidgetItem("CREATE NEW SESSION");
        QListWidgetItem *settings = new QListWidgetItem("SETTINGS");
        QListWidgetItem *history = new QListWidgetItem("HISTORY");
        QListWidgetItem *reset = new QListWidgetItem("RESET");
        ui ->mainOptions ->addItem(session);
        ui ->mainOptions ->addItem(settings);
        ui ->mainOptions ->addItem(history);
        ui ->mainOptions ->addItem(reset);
        ui ->mainOptions ->setCurrentRow(0);
        ui ->views ->setCurrentIndex(0);
        ui ->heading ->setText("MAIN MENU");
    }
}
