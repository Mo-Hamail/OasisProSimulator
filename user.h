#ifndef USER_H
#define USER_H


class user
{
public:
    user(int, double, int);
    int getId();
    //double getBLvl();
    int getPLvl();
    //void setBLvl(double);
    void setPLvl(int);

private:
    int id;
    //double batteryLvl;
    int powerLvl;

};

#endif // USER_H
