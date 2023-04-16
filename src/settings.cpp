#include "settings.h"

/*  setPace()
    -----------------------------
    functionality: sets the breathing pace
*/
void settings::setPace(int bpace) {
    pace = bpace;
}

/*  setLevel()
    -----------------------------
    functionality: sets the challenge level
*/
void settings::setLevel(int clevel) {
    level = clevel;
}

/*  getPace()
    -----------------------------
    functionality: gets the selected breathing pace of the user
*/
int settings::getPace() {
    return pace;
}

/*  getLevel()
    -----------------------------
    functionality: gets the selected challenge level of the user
*/
int settings::getLevel() {
    return level;
}

/*  reset()
    -----------------------------
    functionality: resets the breathing pace and challenge level to default of 1 and 10 respectively
*/
void settings::reset() {
    pace = 1;
    level = 10;
}
