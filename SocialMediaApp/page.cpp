#include "page.h"

Page::Page(int ID = 0, User* o = 0, QString t = "" , int tP = 0, int tL = 0) : pageID(ID), owner(o), title(t), totalPosts(tP),
    totalLikes(tL)
{
    if (tP > 0) {
        posts = new Post*[tP] {0};
    }else
        posts = 0;
}

Page::~Page()
{
    delete[] posts;
}

int& Page::getPageID() { return pageID; }

User*& Page::getOwner() { return owner; }

QString& Page::getTitle() { return title; }

int& Page::getTotalPosts() { return totalPosts; }

Post**& Page::getPosts() { return posts; }

int& Page::getTotalLikes() { return totalLikes; }
