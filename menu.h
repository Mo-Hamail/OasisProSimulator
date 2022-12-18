#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>
#include <QVector>

class menu
{
public:
    menu(QString n, QStringList list, menu* p);
    ~menu();
    QString getName();
    QStringList getMenuItems();
    menu* getParent();
    int getPos();
    menu* get(int);
    void addChildMenu(menu*);

private:
    QString name;
    QStringList menuItems;
    int position;
    QVector<menu*> subMenus;
    menu* parent;
};

#endif // MENU_H
