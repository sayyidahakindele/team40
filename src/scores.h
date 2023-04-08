#ifndef SCORES_H
#define SCORES_H


class scores
{
public:
    //scores();
    // metic function that takes in challenge level
    // getChallengeLevel(int level)

    //set score to 0 for each new session
    double setAchievement();

    double getAchievement(double coherence, double& sum);

    // int colorUpdate(coherence ...)
    // return 1 if 0 red , if blue, if green
 private:
    double achieveScore;
};

#endif // SCORES_H
