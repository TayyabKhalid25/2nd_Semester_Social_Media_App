#ifndef USER_H
#define USER_H

#include <QString>
//#include "page.h"
class Page;  // Circular Dependency (Composition, Aggregation, etc.) causes a problem and we cant directly include header file of other classes.
// To avoid this, Forward Declaration is required like above, but include header file wherever members need to be accessed, e.g in user.cpp


class User
{
private:
    int userID;
    QString name;
    int totalFriends;
    User** friends;
    int totalLikedPages;
    Page** likedPages;

public:
    User(int, QString, int, int);
    int& getUserID();
    QString& getName();
    int& getTotalFriends();
    User**& getFriends();
    int& getTotalLikedPages();
    Page**& getLikedPages();
};

#endif // USER_H
