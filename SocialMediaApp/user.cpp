#include "user.h"
#include "page.h"

User::User(int id = 0, QString Name = "", int friendNum = 0, int pages = 0) : userID(id), name(Name), totalFriends(friendNum), totalLikedPages(pages)
{
    friends = new User*[friendNum];
    likedPages = new Page*[pages];
}
User::~User()
{
    delete[] friends;
    delete[] likedPages;
}

int& User::getUserID() { return userID; }

QString& User::getName() { return name; }

int& User::getTotalFriends() { return totalFriends; }

User**& User::getFriends() { return friends; }

int& User::getTotalLikedPages() { return totalLikedPages; }

Page**& User::getLikedPages() { return likedPages; }
