#ifndef SCORES_H
#define SCORES_H


class scores {
    public:
        //functions
        //set score to 0 for each new session
        double setAchievement();
        double getAchievement(double coherence, double& sum);
        double getChallenge(double coherence);
        int getColor(int level, double coherence);

     private:
        double achieveScore;
};

#endif // SCORES_H
