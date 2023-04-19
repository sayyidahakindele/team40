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

    //default settings
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
    ui ->rechargeButton ->setVisible(false);

    returnToMain();
}

/*  ~MainWindow()
    -----------------------------
    functionality: destroys ui
*/
MainWindow::~MainWindow() {
    delete ui;
}

/*  drainBattery()
    -----------------------------
    functionality: simulates the draining of the battery as it is in use until it gets depleted
*/
void MainWindow::drainBattery() {
    int currentPercentage = ui->battery->value();
    ui->battery->setValue(currentPercentage - 1);

    if (ui->battery->value() == 0) {                                // powers down the device even in session
        batteryTimer->stop();
        qDebug() << "Battery died: Please recharge.";
        if (ui->views->currentIndex() == 1 && contact == true) {
            ui->contactButton->click();
        }
        power = false;
        ui ->rechargeButton ->setVisible(true);
        changePowerStatus(power);
        clear_graph();
    }
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
        ui ->rechargeButton ->setVisible(true);
        ui ->mainOptions ->clear();
    } else {
        power = true;
        ui ->menuButton ->click();
        ui ->rechargeButton ->setVisible(false);
        batteryTimer = new QTimer(this);
        connect(batteryTimer, &QTimer::timeout, this, &MainWindow::drainBattery);
        batteryTimer->start(10000); //decreases battery every 10 seconds
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
    // resets all session graphics
    if (ui ->views ->currentIndex() == 1) {
        contact = false;
        ui ->contactButton ->setStyleSheet("QPushButton {image: url(:/buttons/disabled.png);background-color: rgb(108, 147, 136); border-radius: 5px;}");
        ui ->timer ->display(100);
        ui ->coherence ->display(0);
        ui ->achievement ->display(0);
        ui ->breathing ->setValue(0);
        ui ->coherenceLevel ->setStyleSheet("background-color: rrgb(239, 41, 41);");
        clear_graph();
    }

    // enables all controls
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
        qDebug() << "Device now in contact with skin.";
        ui ->saveButton ->setVisible(true);
        startSession(timer, countdown);

    } else {
        contact=false;
        ui ->contactButton ->setStyleSheet("QPushButton {image: url(:/buttons/disabled.png);background-color: rgb(108, 147, 136); border-radius: 5px;}");
        ui ->saveButton ->setVisible(false);
        qDebug() << "Device no longer in contact with skin";
        endSession(timer, countdown);
    }
}

/*  on_saveButton_clicked()
    -----------------------------
    functionality: saves session and takes you the summary of the session
*/
void MainWindow::on_saveButton_clicked() {
    qDebug() << "Session saved";

    // getting summary details
    int sessionLength = 100 - ui ->timer ->value();
    QString id = QString::number(log.logs.count() + 1);
    QString challengeLevel;
    if (setting.getLevel() == 1) {
      challengeLevel = "BEGINNER";
    } else if (setting.getLevel() == 2) {
        challengeLevel = "INTERMEDIATE";
    } else if (setting.getLevel() == 3) {
        challengeLevel = "HARD";
    } else {
        challengeLevel = "ADVANCED";
    }
    QString averageCoherence = QString::number(ui ->coherence ->value()/sessionLength);
    QString coherenceLevelPercentages;
    int sessionCoherence = qrand() % 3;
    if (sessionCoherence == 0) {
        coherenceLevelPercentages = "              low - 78%\n              medium - 16%\n              high - 6%";
    } else if (sessionCoherence == 1) {
        coherenceLevelPercentages = "              low - 23%\n              medium - 68%\n              high - 9%";
    } else if (sessionCoherence == 2) {
        coherenceLevelPercentages = "              low - 2%\n               medium - 23%\n              high - 75%";
    }

    // creates summary
    QString summary = "SESSION: " + id
                      + "\n     Session Length: " + QString::number(sessionLength) + " seconds"
                      + "\n     Challenge Level: " + challengeLevel
                      + "\n     Achievement Score: " + QString::number(ui ->achievement ->value())
                      + "\n     Average Coherence: " + averageCoherence
                      + "\n     Coherence Level Percentages: \n" + coherenceLevelPercentages;
    log.logs.append(summary);

    // takes user to summary and resets all controls
    contact = false;
    ui ->contactButton ->setStyleSheet("QPushButton {image: url(:/buttons/disabled.png);background-color: rgb(108, 147, 136); border-radius: 5px;}");
    ui ->timer ->display(100);
    ui ->coherence ->display(0);
    ui ->achievement ->display(0);
    ui ->breathing ->setValue(0);
    ui ->coherenceLevel ->setStyleSheet("background-color: rrgb(239, 41, 41);");
    clear_graph();
    ui ->contactButton ->setStyleSheet("QPushButton {image: url(:/buttons/disabled.png);background-color: rgb(108, 147, 136); border-radius: 5px;}");
    ui ->views ->setCurrentIndex(0);
    ui ->mainOptions ->clear();
    ui ->heading ->setText("ALL SESSIONS");
    foreach(QString summary, log.logs) {
        ui ->mainOptions ->addItem(summary);
    }
    ui ->mainOptions ->setCurrentRow(log.logs.count() - 1);
    changePowerStatus(true);
}

/*  startSession()
    -----------------------------
    functionality: simulates the start of a session
*/
void MainWindow::startSession(QTimer& timer, QTimer& countdown){
    qDebug() << "Session started";
    int i= 0;
    int j=0;
    double achieveSum=0;
    int getPace = setting.getPace();        //value sldier moves every sec  eg. 15 every second
    int interval= 60/setting.getPace();     //interval it should take to reach in 60 eg 15 the take 4 times to reach full
    data = new testdata(rand() % 3);

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
    
        //updating the graph using the 1-second timer
        QObject:: connect(&countdown, SIGNAL(timeout()), this, SLOT(update_graph()));
        ui->graph_2->addGraph();


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
    ui ->saveButton ->setVisible(false);
    ui ->contactButton ->setVisible(false);
}

/*  updateMenu(QString)
    -----------------------------
    functionality: figures out what submenu to open and updates the menu view
*/
void MainWindow::updateMenu(QString option) {
    if (option == "CREATE NEW SESSION") {
        ui ->contactButton ->setVisible(true);
        ui ->views ->setCurrentIndex(1);
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
        for(int i = 0; i < 30; i++){
            ui ->mainOptions ->addItem(QString::number(i+1));
        }
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
    } else if (option == "YES" && ui ->heading->text() == "ARE YOU SURE YOU WANT TO CLEAR ALL?") {
        log.logs.clear();
        returnToMain();
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
        ui ->mainOptions ->setCurrentRow(0);
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
            breathPacer.setValue(value);
            if(value > 60){
                value=0;
                 breathPacer.setValue(value);
            }
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

/*updateGraph()
  --------------------------------
  functionality: uses the generated graph values and updates the graph throughout the session
*/
void MainWindow::update_graph()
{
    runTime++;
    //used to store the x and y values of the graph
    QVector<double> x(101), y(101);

    //getting the data generated for the graph
    int* graphData = data ->getGraph();

    //storing the x and y values in the vector
    double xVal = 0;
    for(int i = 0; i < runTime; i++)
    {
       if(i == 0)
            x[i] = 0;
       else
         x[i] = xVal+= PI/4;

       y[i] = graphData[i];

    }

    ui->graph_2->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->graph_2->xAxis->setLabel("time/seconds");
    ui->graph_2->yAxis->setLabel("heart rate");
    // set axes ranges, so we see all data:
    ui->graph_2->xAxis->setRange(0, runTime); //sets the range of the x axis--doesn't draw the line
    ui->graph_2->yAxis->setRange(0, 100);
    ui->graph_2->replot();

}

/*returnToMain()
  --------------------------------
  functionality: resets the main menu of the application, preparing it for user interaction.
*/
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


/*on_rechargeButton()
  --------------------------------
  functionality: recharges the battery and resets it to back to full battery 100%
*/
void MainWindow::on_rechargeButton_clicked() {
    qDebug() << "Charging";
    ui->battery->setValue(100);
    qDebug() << "Charged";
    ui ->powerButton ->setEnabled(true);
}


/*clear_graph()
 * --------------------------------
 * functionality: clears the already plotted graph and resets it for the next use
*/
void MainWindow::clear_graph()
{
    //resetting values
    runTime = 0;
    QVector<double> x(101), y(101);
    ui->graph_2->graph(0)->setData(x, y);

    // set axes ranges, so we see all data:
    ui->graph_2->xAxis->setRange(0, runTime);
    ui->graph_2->yAxis->setRange(0, 100);
    ui->graph_2->replot();
}
