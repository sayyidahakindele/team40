#include "settings.h"

void settings::setPace(int bpace) {
    pace = bpace;
}

void settings::setLevel(int clevel) {
    level = clevel;
}

int settings::getPace() {
    return pace;
}

int settings::getLevel() {
    return level;
}

void settings::reset() {
    pace = 1;
    level = 10;
}
