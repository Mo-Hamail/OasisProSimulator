#ifndef CONNECTION_H
#define CONNECTION_H


class Connection
{
private:
    bool status;
public:
    Connection();
    void setStatus(bool);
    bool testConnection();
};

#endif // CONNECTION_H
