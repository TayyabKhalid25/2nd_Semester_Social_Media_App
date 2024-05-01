#include "post.h"

int& Post::getPostID()
{
    return &postID;
}

User*& Post::getOwner()
{
    return &owner;
}

QString& Post::getDescription()
{
    return &description;
}

Activity& Post::getActivity()
{
    return &activity;
}

int& Post::getTotalLikes()
{
    return &totalLikes;
}

User**& Post::getLikedBy()
{
    return &likedBy;
}

QDateTime& Post::getSharedDate()
{
    return &sharedDate;
}

int& Post::getTotalComments()
{
    return &totalComments;
}

Comment**& Post::getComments()
{
    return &comments;
}

Post::Post()
{

}
