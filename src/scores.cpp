#include "scores.h"

double scores::setAchievement(){
    achieveScore=0;
}

double scores::getAchievement(double coherence, double& sum){
    sum +=  coherence;
    return sum;
}

