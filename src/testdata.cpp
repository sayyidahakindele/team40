#include "testdata.h"

testdata::testdata(int number) {
    switch(number) {
        case 0:
            low();
            lowCoherence();
            break;
        case 1:
            medium();
            mediumCoherence();
            break;
        case 2:
            high();
            highCoherence();
            break;
    }
}

void testdata::low() {
    for (int i = 0; i < 100; ++i) {
        if (i%2 == 0) {
            graph[i] = rand() % 30 + 1;
        } else {
            graph[i] = rand() % 100 + 1; // 0 - 100
        }
    }
}

void testdata::medium() {
    for (int i = 0; i < 100; ++i) {
        if (i%2 == 0) {
            graph[i] = rand() % 50;
        } else {
            graph[i] = rand() % 11 + 90; // 90 - 100
        }
    }
}

void testdata::high() {
    for (int i = 0; i < 100; ++i) {
        if (i%2 == 0) {
            graph[i] = rand() % 20;
        } else {
            graph[i] = rand() % 11 + 90; // 90 - 100
        }
    }
}

/*  lowCoherence()
    -----------------------------
    functionality: an array of low coherence scores
*/

void testdata::lowCoherence() {
    scores.append(0.21);
    scores.append(0.42);
    scores.append(0.63);
    scores.append(0.84);
    scores.append(1.03);
    scores.append(1.37);
    scores.append(1.76);
    scores.append(2.22);
    scores.append(2.08);
    scores.append(1.60);
    scores.append(1.42);
    scores.append(1.26);
    scores.append(0.12);
    scores.append(0.43);
    scores.append(0.39);
    scores.append(0.30);
    scores.append(0.28);
    scores.append(0.20);
    scores.append(0.17);
    scores.append(0.23);
}

/*  mediumCoherence()
    -----------------------------
    functionality: an array of medium coherence scores
*/
void testdata::mediumCoherence() {
    scores.append(1.34);
    scores.append(1.75);
    scores.append(1.93);
    scores.append(2.23);
    scores.append(2.55);
    scores.append(2.89);
    scores.append(3.06);
    scores.append(2.70);
    scores.append(2.42);
    scores.append(2.19);
    scores.append(1.98);
    scores.append(1.67);
    scores.append(1.35);
    scores.append(1.14);
    scores.append(1.17);
    scores.append(0.83);
    scores.append(0.63);
    scores.append(0.70);
    scores.append(1.26);
    scores.append(2.57);
}

/*  highCoherence()
    -----------------------------
    functionality: an array of high coherence scores
*/
void testdata::highCoherence() {
    scores.append(3.65);
    scores.append(4.20);
    scores.append(4.55);
    scores.append(5.20);
    scores.append(6.48);
    scores.append(6.56);
    scores.append(7.08);
    scores.append(7.57);
    scores.append(8.41);
    scores.append(8.54);
    scores.append(9.03);
    scores.append(9.55);
    scores.append(10.34);
    scores.append(10.40);
    scores.append(11.49);
    scores.append(11.50);
    scores.append(13.04);
    scores.append(12.78);
    scores.append(13.92);
    scores.append(14.23);
}

/*  getGraph()
    -----------------------------
    functionality: gets the graph
*/
int* testdata::getGraph() {
    return graph;
}

/*  getSCores()
    -----------------------------
    functionality: gets the coherence scores
*/
QVector<double> testdata::getScores() {
    return scores;
}
