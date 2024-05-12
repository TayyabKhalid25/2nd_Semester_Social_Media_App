#ifndef MEMORY_H
#define MEMORY_H

#include "post.h"

class Memory final : public Post
{
private:
    Post* originalPost;

public:

    Memory(Post*, int, User*, QString, Activity, int, int, QDate);
    ~Memory();
    Post*& getOriginalPost();

};

#endif // MEMORY_H
