#include "connection.h"

//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */

Connection::Connection()
{
    status = false;
}
void Connection::setStatus(bool newStatus)
{
    status = newStatus;
}
bool Connection::testConnection()
{
    // in case team decides to use random number idea...
    //srand (time(NULL));
    //status = (rand() % 100 + 1)%2; //to get a 0 (false) or 1 (true) as a connection status
    //******************************************************
    return status;
}
