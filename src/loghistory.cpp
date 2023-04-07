#include "loghistory.h"

loghistory::loghistory()
{

}

double loghistory::getAchievement(double coherence){
    achieveScore +=  coherence;
    return achieveScore;
}
