#include "menu.h"

menu::menu(QString n, QStringList list, menu* p) {
    name = n;
    menuItems = list;
    parent = p;
}


menu::~menu() {
    for(int x = 0; x < subMenus.length(); x++) {
        delete subMenus[x];
    }
}


void menu::addChildMenu(menu* m) {
    subMenus.push_back(m);
}


// getters
QString menu::getName() { return name; }
QStringList menu::getMenuItems() { return menuItems; }
menu* menu::getParent() { return parent; }
int menu::getPos() { return position; }
menu* menu::get(int i) { return subMenus[i]; }
