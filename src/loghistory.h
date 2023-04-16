#ifndef LOGHISTORY_H
#define LOGHISTORY_H


class loghistory {
    public:
        loghistory();
        QList<QString> logs;
        // printSummary(int): call getters from session
        // delete
        // delete all
        double getAchievement(double coherence);
    private:
        double achieveScore;
};

#endif // LOGHISTORY_H
