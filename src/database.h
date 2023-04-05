#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>

extern QMap<int, int> frustration;
extern QMap<int, int> anxiety;
extern QMap<int, int> worry;
extern QMap<int, int> irritation;
extern QMap<int, int> happiness;
extern QMap<int, int> appreciation;
extern QMap<int, int> love;
extern QMap<int, int> care;

class database
{
    public:
        database(int number);
        void frustration();
        void anxiety();
        void worry();
        void irritation();
        void happiness();
        void appreciation();
        void love();
        void care();

     private:
        QMap<int, int> graph;
};

#endif // DATABASE_H
