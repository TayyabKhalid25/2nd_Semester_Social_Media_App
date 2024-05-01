#ifndef POST_H
#define POST_H

#include <QString>
#include <QDateTime>
#include "user.h"
#include "activity.h"
#include "comment.h"

class Post
{
private:
    int postID;
    User* owner;
    QString description;
    Activity activity;
    int totalLikes;
    User** likedBy;
    QDateTime sharedDate;
    int totalComments;
    Comment** comments;

public:
    Post();
    int& getPostID();
    User*& getOwner();
    QString& getDescription();
    Activity& getActivity();
    int& getTotalLikes();
    User**& getLikedBy();
    QDateTime& getSharedDate();
    int& getTotalComments();
    Comment**& getComments();
};

#endif // POST_H
