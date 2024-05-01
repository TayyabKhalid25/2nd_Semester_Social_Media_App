#ifndef USER_H
#define USER_H

#include <QString>
#include "page.h"

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
