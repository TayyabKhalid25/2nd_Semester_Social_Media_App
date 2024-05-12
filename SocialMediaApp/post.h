#ifndef POST_H
#define POST_H

#include <QString>
#include <QDate>
#include "user.h"
#include "activity.h"
#include "comment.h"

class Post
{
protected:
    int postID, totalLikes, totalComments;
    User* owner;
    QString description;
    Activity activity;
    User** likedBy;
    QDate sharedDate;
    Comment** comments;

public:
    Post(int, User*, QString, Activity, int, int, QDate);
    virtual ~Post();

    int& getPostID();
    User*& getOwner();
    QString& getDescription();
    Activity& getActivity();
    int& getTotalLikes();
    User**& getLikedBy();
    QDate& getSharedDate();
    int& getTotalComments();
    Comment**& getComments();

    static void postToString(Post *post, QString &str);

};

#endif // POST_H
