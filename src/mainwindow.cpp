#include "mainwindow.h"
#include "ui_mainwindow.h"

/*  mainWindow(QWidget *parent)
    -----------------------------
    functionality: sets all buttons and variables to their default
                  displays UI
*/

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    power = false;
    contact = false;
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
    ui ->contactButton ->setVisible(false);
    ui ->saveButton ->setVisible(false);
}

/*  ~MainWindow()
    -----------------------------
    functionality: destroys ui
*/
MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::drainBattery() {

    int currentPercentage = ui->battery->value();
    ui->battery->setValue(currentPercentage - 20);
    qDebug() << "Should be draining battery";

    // it shoud power down the device instead of just stopping the session
    if (ui->battery->value() == 0) {
        batteryTimer->stop();
        qDebug() << "Battery Died. Session ending.";

        if (ui->views->currentIndex() == 1 && contact == true) {
            ui->contactButton->click();
            //remove hr, save,
            //show recharge button
        }

        power = false;
        changePowerStatus(power);
    }
}

void MainWindow::returnToMain() {
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

/*  on_menuButton_clicked()
    -----------------------------
    functionality: shows/hides ui and enables/disables buttons
    extension: if in session view, stops timer and enables all buttons
*/
void MainWindow::on_powerButton_clicked() {
    if (power == true) {
        power = false;

        ui ->contactButton ->setVisible(false);
        ui ->mainOptions ->clear();
    } else {
        power = true;
        returnToMain();

        batteryTimer = new QTimer(this);
        connect(batteryTimer, &QTimer::timeout, this, &MainWindow::drainBattery);
        batteryTimer->start(10000); //decrements battery every 10 seconds
    }
    changePowerStatus(power);

}

/*  on_upButton_clicked()
    -----------------------------
    functionality: navigates up the menu
*/
void MainWindow::on_upButton_clicked() {
    int current = ui ->mainOptions ->currentRow();
    if (current > 0) {
        ui ->mainOptions ->setCurrentRow(current - 1);
    } else {
        ui ->mainOptions ->setCurrentRow(ui ->mainOptions ->count() - 1);
    }
}

/*  on_downButton_clicked()
    -----------------------------
    functionality: navigates down menu
*/
void MainWindow::on_downButton_clicked() { 
    int current = ui ->mainOptions ->currentRow();
    if (current < ui ->mainOptions ->count() - 1) {
        ui ->mainOptions ->setCurrentRow(current + 1);
    } else {
        ui ->mainOptions ->setCurrentRow(0);
    }
}

/*  on_okButton_clicked()
    -----------------------------
    functionality: opens submenus
    extensions: if on challenge level or breath pace submenu, save selected value
*/
void MainWindow::on_okButton_clicked() {
    QString selectedItem = ui ->mainOptions ->currentItem() ->text();
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
}

/*  on_menuButton_clicked()
    -----------------------------
    functionality: takes you to the main menu
    extension: if in session view, stops timer and enables all buttons
*/
void MainWindow::on_menuButton_clicked() {
    if (ui ->views ->currentIndex() == 1) {
        contact = false;
        ui ->contactButton ->setStyleSheet("QPushButton {image: url(:/buttons/disabled.png);background-color: rgb(108, 147, 136); border-radius: 5px;}");
        ui ->timer ->display(100);
        ui ->coherence ->display(0);
        ui ->achievement ->display(0);
        ui ->breathing ->setValue(0);
        ui ->coherenceLevel ->setStyleSheet("background-color: rrgb(239, 41, 41);");
        // rest graph
    }
    ui ->views ->setCurrentIndex(0);
    ui ->contactButton ->setVisible(false);
    ui ->saveButton ->setVisible(false);
    ui ->views ->setVisible(true);
    ui ->battery ->setVisible(true);
    ui ->upButton ->setEnabled(true);
    ui ->downButton ->setEnabled(true);
    ui ->leftButton ->setEnabled(true);
    ui ->rightButton ->setEnabled(true);
    ui ->powerButton ->setEnabled(true);
    ui ->okButton ->setEnabled(true);
    ui ->backButton ->setEnabled(true);

    returnToMain();
}

/*  on_backButton_clicked()
    -----------------------------
    functionality: takes you to the previous menu page
*/
void MainWindow::on_backButton_clicked() {
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
        returnToMain();
    } else {
        ui ->mainOptions ->clear();
        QListWidgetItem *view = new QListWidgetItem("VIEW");
        QListWidgetItem *clear = new QListWidgetItem("CLEAR");
        ui ->mainOptions ->addItem(view);
        ui ->mainOptions ->addItem(clear);
        ui ->mainOptions ->setCurrentRow(0);
    }
}

/*  on_contactButton_clicked()
    -----------------------------
    functionality: simulates connecting/disconnecting measuring gadgets
*/
void MainWindow::on_contactButton_clicked() {

    //Timer
    QTimer timer; //timer for collecting coherence score every 5 secs
    QTimer countdown; //timer shown in the session that countdown
    QPushButton *hr = ui->contactButton;

    if (contact == false) {
        contact = true;
        ui ->contactButton ->setStyleSheet("QPushButton {image: url(:/buttons/enabled.png);background-color: rgb(108, 147, 136); border-radius: 5px;}");
        qDebug() << "Device is now in contact with skin.";
        ui ->saveButton ->setVisible(true);
        startSession(timer, countdown);

    } else {
        contact=false;
        ui ->contactButton ->setStyleSheet("QPushButton {image: url(:/buttons/disabled.png);background-color: rgb(108, 147, 136); border-radius: 5px;}");
        ui ->saveButton ->setVisible(false);
        qDebug() << "Device is no longer in contact with skin";
        //disconnect(ui->contactButton, &QPushButton::clicked, nullptr, nullptr);
        endSession(timer, countdown);
    }
}

/*  on_saveButton_clicked()
    -----------------------------
    functionality: saves session and takes you the summary of the session
*/
void MainWindow::on_saveButton_clicked() {
    qDebug() << "Session saved - WEIRD FUNC";

    int sessionLength = 100 - ui->timer->intValue();
    int achievementScore = ui->achievement->intValue();

    QString challengeLevel = QString::number(setting.getLevel());
    QString averageCoherence = QString::number(achievementScore/(sessionLength/5));
    QString coherenceLevelPercentages = "";

    QMessageBox msgBox;
    QString summary = "Session Length: " + QString::number(sessionLength) + " seconds"
                      + "\nChallenge Level: " + challengeLevel
                      + "\nAchievement Score: " + QString::number(achievementScore)
                      + "\nAverage Coherence: " + averageCoherence
                      + "\nCoherence Level Percentages: " + coherenceLevelPercentages;
    log.logs.append(summary);

    msgBox.setText(summary );
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setWindowModality(Qt::ApplicationModal);

    QString styleSheet = "QMessageBox { background-color: black; border: 2px solid white; color: white; }";

    msgBox.setStyleSheet(styleSheet);
    msgBox.exec();
}

/*  startSession()
    -----------------------------
    functionality: simulates the start of a session
*/
void MainWindow::startSession(QTimer& timer, QTimer& countdown){
    int i= 0;
        int j=0;
        double achieveSum=0;
        int getPace = setting.getPace();//value sldier moves every sec  eg. 15 every second
        int interval= 60/setting.getPace(); //interval it should take to reach in 60 eg 15 the take 4 times to reach full
        testdata *data = new testdata(qrand()%3);

        int countTime= 100; //change to 100

        //set session displays
        QLCDNumber *coh = ui->coherence;
        QLCDNumber *ach = ui->achievement;
        QLCDNumber *tracker = ui->timer;
        QSlider *breathPacer = ui ->breathing; //creates a slider

        breathPacer->setRange(0,60);//set the min and max vals
        breathPacer->setValue(0);


        s.setAchievement();

        int* graph = data ->getGraph();
        QVector<double> arrScores = data ->getScores();

        startTimer(timer, countdown, *tracker, *breathPacer, countTime, getPace);

        coh->display(0);
        ach->display(0);
        QObject::connect(&timer, &QTimer::timeout, [&](){
            updateDisplay(timer, *coh, *ach, arrScores, i, achieveSum, countTime);
        });

        QObject::connect(&timer, &QTimer::timeout, [&](){
            updateDisplay(timer, *coh, *ach, arrScores, i, achieveSum, countTime);
        });

        QObject::connect(ui->contactButton, &QPushButton::clicked, this, [&](){
            endSession(timer, countdown);
        });

        QObject::connect(ui->menuButton, &QPushButton::clicked, this, [&](){
            endSession(timer, countdown);
        });

        QObject::connect(ui->saveButton, &QPushButton::clicked, this, [&](){
            endSession(timer, countdown);
            //add summary function stuff here to create summary for session
        });


        QEventLoop l;
        QTimer::singleShot(100000,&l,&QEventLoop::quit);
        l.exec();
        qDebug() << "Session finished";
        contact =false;
}

/*  endSession()
    -----------------------------
    functionality: stops the active session and ongoing timers
*/
void MainWindow::endSession(QTimer& timer, QTimer& countdown) {
    // should only be called to end timer. If saved, done in another button
    qDebug() << "session ended";
    timer.stop();
    countdown.stop();
}

/*  changePowerStatus(bool)
    -----------------------------
    functionality: disables/enables buttons
*/
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

/*  updateMenu(QString)
    -----------------------------
    functionality: figures out what submenu to open and updates the menu view
*/
void MainWindow::updateMenu(QString option) {
    if (option == "CREATE NEW SESSION") {
        ui ->contactButton ->setVisible(true);
        ui ->views ->setCurrentIndex(1);
        ui ->battery ->setVisible(false);
        ui ->upButton ->setEnabled(false);
        ui ->downButton ->setEnabled(false);
        ui ->leftButton ->setEnabled(false);
        ui ->rightButton ->setEnabled(false);
        ui ->okButton ->setEnabled(false);
        ui ->backButton ->setEnabled(false);
        ui ->powerButton ->setEnabled(false);
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
        for(int i = 0; i <= 30; i++){
            ui ->mainOptions ->addItem(QString::number(i));
        }
        ui ->mainOptions ->setCurrentRow(setting.getPace() - 1);
        qDebug() << setting.getPace();
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
    } else if (option == "YES" && ui ->heading->text() == "ARE YOU SURE YOU WANT TO CLEAR ALL?") {
        log.logs.clear();
        returnToMain();
        qDebug() << log.logs;
    }
    else if(option == "YES" && ui ->heading->text() == "ARE YOU SURE YOU WANT TO RESET?"){
        log.logs.clear();
        setting.reset();
        returnToMain();
    } else if (option == "NO") {
        returnToMain();
    } else if (option == "VIEW") {
        ui ->mainOptions ->clear();
        ui ->heading ->setText("ALL SESSIONS");

        if (log.logs.isEmpty()){
            ui ->mainOptions ->addItem("EMPTY");
        } else {
            foreach(QString summary, log.logs) {
                ui ->mainOptions ->addItem(summary);
            }
        }

    }
}

/*  startTimer
    -----------------------------
    functionality: starts the timers and updates its display in session. Also updates the breath pacer every sec.
*/
void MainWindow::startTimer(QTimer& timer, QTimer& countdown, QLCDNumber& tracker,QSlider& breathPacer, int& countTime, int& getPace) // add timers for graph, breath pace
{
    int value= breathPacer.value();
    timer.setInterval(5000);//5sec interval
    timer.setSingleShot(false);

    countdown.setInterval(1000);//1 sec interval
    tracker.display(countTime);

    QObject::connect(&countdown, &QTimer::timeout, [&](){
        if(countTime > 0){
            countTime--;
            tracker.display(countTime);
            value+= getPace;
            qDebug() << value;
            breathPacer.setValue(value);
            if(value > 60){
                value=0;
                 breathPacer.setValue(value);
            }
            qDebug() << value;
        }
        else{
            countdown.stop();
            timer.stop();
            //paceTimer.stop();
            qDebug() << "Timer Up!";
        }
    });

    countdown.start();
    timer.start();
}

/*  updateDisplay()
    -----------------------------
    functionality: updates the various metrics in the session display(coherence, achievement score)
*/
void MainWindow::updateDisplay(QTimer& timer, QLCDNumber& coh, QLCDNumber& ach, QVector<double>& arrScores, int& i, double& achieveSum, int& countTime)
{
    if(i< arrScores.size()){
        double score= arrScores[i];
        achieveSum= s.getAchievement(score, achieveSum);
        coh.display(score);
        ach.display(achieveSum);
        updateLights(s.getColor(setting.getLevel(), score));
        i++;
    }
    else{
        timer.stop();
        qDebug() << "Achievement Sum:" << achieveSum;
        qDebug() << "Timer Up!";
    }
}

/*  updateLights()
    -----------------------------
    functionality: changes color of label depending on coherence
*/
void MainWindow::updateLights(int color) {
    if (color == 1) {
        ui ->coherenceLevel ->setStyleSheet("QLabel { color: red; background-color: red;}");
    } else if (color == 2) {
        ui ->coherenceLevel ->setStyleSheet("QLabel { color: blue; background-color: blue;}");
    } else if (color == 3) {
        ui ->coherenceLevel ->setStyleSheet("QLabel { color: green; background-color: green}");
    }
}




