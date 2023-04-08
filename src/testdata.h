#ifndef TESTDATA_H
#define TESTDATA_H

#include <QMap>
#include <QVector>
#include <QPair>

class testdata
{
    public:
        testdata(int number);
        void low();
        void medium();
        void high();
        void lowCoherence();
        void mediumCoherence();
        void highCoherence();

        QMap<int, int> getGraph();
        QVector<double> getScores();


     private:
        QMap<int, int> graph;
        QVector<double> scores;
};

#endif // TESTDATA_H
