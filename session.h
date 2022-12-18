
// Session class that conatins all session information

#ifndef SESSION_H
#define SESSION_H

#include<frequency.h>

class Session
{
private:
    int sTime; // session alloted time
    Frequency sFrequency; // session frequency

public:
    Session();
    Session(int t, Frequency f);
    int getSTime() const;
    void setSTime(int value);
    Frequency getSFrequency() const;
    void setSFrequency(const Frequency &value);
};

#endif // SESSION_H
