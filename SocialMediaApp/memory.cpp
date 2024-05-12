#include "memory.h"

Memory::Memory(Post* op = 0 ,int p = 0, User* o = 0, QString d = "", Activity a = Activity(0, QString("")), int tl = 0, int tc = 0, QDate sd = QDate::currentDate())
    : Post(p, o, d, a, tl, tc, sd), originalPost(op) {}

Memory::~Memory()
{
    for (int i = 0; i < totalComments; i++){
        delete comments[i];
    }
    delete[] comments;
    delete[] likedBy;
}

Post*& Memory::getOriginalPost(){ return originalPost; }
