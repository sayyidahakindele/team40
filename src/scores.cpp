#include "scores.h"

double scores::setAchievement(){
    achieveScore=0;
}

double scores::getAchievement(double coherence, double& sum){
    sum +=  coherence;
    return sum;
}

int scores::getColor(int level, double coherence) {
    double low;
    double high;

    if (level == 1) {
        low = 0.5;
        high = 0.9;
    } else if (level == 2) {
        low = 0.6;
        high = 2.1;
    } else if (level == 3) {
        low = 1.8;
        high = 4.0;
    } else {
        low = 4.0;
        high = 6.0;
    }

    if (coherence < low) {
        return 1;
    } else if (coherence > high) {
        return 3;
    } else {
        return 2;
    }
}

