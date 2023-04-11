#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // default settings
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

// power button toggle
void MainWindow::on_powerButton_clicked() {
    //toggles between disabled menu and main menu
    if (ui ->views ->currentIndex() == 1) {
        endSession();
    }
    if (power == true) {
        power = false;
        if (ui ->views ->currentIndex() == 1) {
            qDebug() << "session view";
        }
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

// up button clicked
void MainWindow::on_upButton_clicked() {
    int current = ui ->mainOptions ->currentRow();
    if (current > 0) {
        ui ->mainOptions ->setCurrentRow(current - 1);
    } else {
        ui ->mainOptions ->setCurrentRow(ui ->mainOptions ->count() - 1);
    }
}

// down button clicked
void MainWindow::on_downButton_clicked() { 
    int current = ui ->mainOptions ->currentRow();
    if (current < ui ->mainOptions ->count() - 1) {
        ui ->mainOptions ->setCurrentRow(current + 1);
    } else {
        ui ->mainOptions ->setCurrentRow(0);
    }
}

// ok button clicked
void MainWindow::on_okButton_clicked() {
    if (ui ->views ->currentIndex() == 0) {
        QString selectedItem = ui ->mainOptions ->currentItem() ->text();
        // updateMenu only called when a new submenu is created or a being difrected to a different menu
        if (selectedItem == "CREATE NEW SESSION" | selectedItem == "SETTINGS" | selectedItem == "HISTORY" | selectedItem == "CHANGE CHALLENGE LEVEL" | selectedItem == "CHANGE BREATH PACE" | selectedItem == "HISTORY" | selectedItem == "RESET" | selectedItem == "CLEAR"| selectedItem == "YES" | selectedItem == "NO" | selectedItem == "VIEW") {
            updateMenu(selectedItem);
        } else { // this covers breath and challenge. Should call a function in each one that updates the respective quality
            QString currentTab = ui ->mainOptions ->item(0) ->text();
            if (currentTab == "1 - BEGINNER") {
                setting.setLevel(ui ->mainOptions ->currentRow() + 1);
            } else if (currentTab == "1") {
                setting.setPace(ui ->mainOptions ->currentRow() + 1);
            }
        }
    } else {
        endSession();
    }
}

// menu button clicked
void MainWindow::on_menuButton_clicked() {
    if (ui ->views ->currentIndex() == 1) {
       endSession();
    }
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

// back button clicked
void MainWindow::on_backButton_clicked() {
    if (ui ->views ->currentIndex() == 1) {
        endSession();
    }
    QString currentTab = ui ->mainOptions ->item(0) ->text();
    if (currentTab == "1 - BEGINNER" | currentTab == "1") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("SETTINGS");
        QListWidgetItem *challengeLevel = new QListWidgetItem("CHANGE CHALLENGE LEVEL");
        QListWidgetItem *breathPace = new QListWidgetItem("CHANGE BREATH PACE");
        ui ->mainOptions ->addItem(challengeLevel);
        ui ->mainOptions ->addItem(breathPace);
        ui ->mainOptions ->setCurrentRow(0);
    } else if (currentTab == "CHANGE CHALLENGE LEVEL" | currentTab == "VIEW" | currentTab == "YES" | currentTab == "NO") {
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
    } else {
        ui ->mainOptions ->clear();
        QListWidgetItem *view = new QListWidgetItem("VIEW");
        QListWidgetItem *clear = new QListWidgetItem("CLEAR");
        ui ->mainOptions ->addItem(view);
        ui ->mainOptions ->addItem(clear);
        ui ->mainOptions ->setCurrentRow(0);
    }
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

void MainWindow::updateMenu(QString option) {
    if (option == "CREATE NEW SESSION") {   // takes you to the session view tab
        int i= 0;
        double achieveSum=0;
        int currentPace = setting.getPace();
        testdata *data = new testdata(qrand()%3);

        //Timer
        QTimer timer;
        QTimer countdown;
        int countTime= 10; //change to 100
        QTimer paceTime;

        //set timer display
        QLCDNumber *coh = ui->coherence;
        QLCDNumber *ach = ui->achievement;
        QLCDNumber *tracker = ui->timer;
        QSlider *breathPace = ui ->breathing;

        s.setAchievement();
        ui ->views ->setCurrentIndex(1);
        //QMap<int, int> graph = data ->getGraph();
        int* graph = data ->getGraph();
        for (int var = 0; var < 100; ++var) {
            qDebug() << graph[var];
        }
        QVector<double> arrScores = data ->getScores();

        startTimer(timer, countdown, paceTime, *tracker, countTime);

        coh->display(0);
        ach->display(0);
        QObject::connect(&timer, &QTimer::timeout, [&](){
            updateDisplay(timer, *coh, *ach, arrScores, i, achieveSum);
//            simulateBreathPace(paceTime, currentPace, *breathPace);

        });

        QEventLoop l;
        QTimer::singleShot(100000,&l,&QEventLoop::quit);
        l.exec();
        qDebug() << "Session finished";
    } else if (option == "SETTINGS") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("SETTINGS");
        QListWidgetItem *challengeLevel = new QListWidgetItem("CHANGE CHALLENGE LEVEL");
        QListWidgetItem *breathPace = new QListWidgetItem("CHANGE BREATH PACE");
        ui ->mainOptions ->addItem(challengeLevel);
        ui ->mainOptions ->addItem(breathPace);
        ui ->mainOptions ->setCurrentRow(0);
    } else if (option == "HISTORY") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("HISTORY");
        ui ->mainOptions ->addItem("VIEW");
        ui ->mainOptions ->addItem("CLEAR");
        ui ->mainOptions ->setCurrentRow(0);
    } else if (option == "CHANGE CHALLENGE LEVEL") {
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
        ui ->mainOptions ->setCurrentRow(setting.getLevel() - 1);
    } else if (option == "CHANGE BREATH PACE") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("SETTINGS");
        ui ->mainOptions ->addItem("1");
        ui ->mainOptions ->addItem("2");
        ui ->mainOptions ->addItem("3");
        ui ->mainOptions ->addItem("4");
        ui ->mainOptions ->addItem("5");
        ui ->mainOptions ->addItem("6");
        ui ->mainOptions ->addItem("10");
        ui ->mainOptions ->addItem("12");
        ui ->mainOptions ->addItem("15");
        ui ->mainOptions ->addItem("20");
        ui ->mainOptions ->addItem("30");
        ui ->mainOptions ->setCurrentRow(setting.getPace() - 1);
    } else if (option == "RESET") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("ARE YOU SURE YOU WANT TO RESET?");
        ui ->mainOptions ->addItem("YES");
        ui ->mainOptions ->addItem("NO");
        ui ->mainOptions ->setCurrentRow(0);
    } else if (option == "CLEAR") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("ARE YOU SURE YOU WANT TO CLEAR ALL?");
        ui ->mainOptions ->addItem("YES");
        ui ->mainOptions ->addItem("NO");
        ui ->mainOptions ->setCurrentRow(0);
    } else if (option == "YES") {
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
    } else if (option == "NO") {
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
    } else if (option == "VIEW") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("ALL SESSIONS");
        // if (log is empty)
        ui ->mainOptions ->addItem("EMPTY");
    }
}

void MainWindow::countDown() {
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    ui ->countdown ->setText("3");
    ui ->countdown ->setText("2");
    ui ->countdown ->setText("1");
    ui ->countdown ->setText("START!!!");
    ui ->countdown ->setVisible(false);
}
//starts the timer and updates its display in session
void MainWindow::startTimer(QTimer& timer, QTimer& countdown, QTimer& bpace, QLCDNumber& tracker, int& countTime) // add timers for graph, breath pace
{
    timer.setInterval(5000);
    timer.setSingleShot(false);

    countdown.setInterval(1000);
    tracker.display(countTime);

    bpace.setInterval(setting.getPace());

    QObject::connect(&countdown, &QTimer::timeout, [&](){
        if(countTime > 0){
            countTime--;
            tracker.display(countTime);
        }
        else{
            countdown.stop();
            timer.stop();
            qDebug() << "Timer Up!";
        }
    });

    countdown.start();
    timer.start();
}

//gets coherence and achievement score and updates the values in the session display
void MainWindow::updateDisplay(QTimer& timer, QLCDNumber& coh, QLCDNumber& ach, QVector<double>& arrScores, int& i, double& achieveSum)
{
    if(i< arrScores.size()){
        double score= arrScores[i];
        achieveSum= s.getAchievement(score, achieveSum); //setting.getLevel

        coh.display(score);
        ach.display(achieveSum);
        i++;
    }
    else{
        timer.stop();
        qDebug() << "Achievement Sum:" << achieveSum;
        qDebug() << "Timer Up!";
    }

}


void MainWindow::endSession() {
    // call session ->session();
    qDebug() << "session saved!";
    ui ->views ->setCurrentIndex(0);
    ui ->mainOptions ->clear();
    ui ->heading ->setText("SESSIONS");
    // if (log is empty)
    ui ->mainOptions ->addItem("EMPTY");
}

void simulateBreathPace(QTimer& timer, int pace, QSlider& slide) {
    qDebug() << "hi";
}
