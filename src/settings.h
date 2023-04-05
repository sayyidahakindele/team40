#ifndef SETTINGS_H
#define SETTINGS_H


class settings {
    public:
        //setters
        void setPace(int pace);
        void setLevel(int level);

        //getters
        int getPace();
        int getLevel();

        //functions
        void reset();

     private:
         int pace = 10;
         int level = 1;
};

#endif // SETTINGS_H
