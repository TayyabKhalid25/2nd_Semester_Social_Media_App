#include "page.h"


Page::Page(int ID = 0, QString t = "" , int tP = 0, int tL = 0  ) : pageID(ID), title(t), totalPosts(tP), totalLikes(tL)
{

}

int& Page::getPageID() { return pageID; }

User*& Page::getOwner() { return owner; }

QString& Page::getTitle() { return title; }

int& Page::getTotalPosts() { return totalPosts; }

Post**& Page::getPosts() { return posts; }

int& Page::getTotalLikes() { return totalLikes; }
