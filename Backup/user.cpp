#include "user.h"
#include "page.h"

User::User(int id, QString Name, int friendNum, int pages) : userID(id), name(Name), totalFriends(friendNum), totalLikedPages(pages)
{
    friends = 0;
    likedPages = 0;
}

int& User::getUserID() { return userID; }

QString& User::getName() { return name; }

int& User::getTotalFriends() { return totalFriends; }

User**& User::getFriends() { return friends; }

int& User::getTotalLikedPages() { return totalLikedPages; }

Page**& User::getLikedPages() { return likedPages; }

