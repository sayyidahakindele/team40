#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>
#include <QVector>

class Menu {

    public:
        Menu(QString choice, QStringList items, Menu *parent);

    private:
        QString choice;
        QStringList items;
        Menu *parent;
        int position;
        QVector<Menu*> submenu;
};

#endif // MENU_H
