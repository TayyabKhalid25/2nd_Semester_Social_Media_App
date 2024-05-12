#include "post.h"



Post::Post(int p = 0, User* o = 0, QString d = "", Activity a = Activity(0, QString("")), int tl = 0, int tc = 0, QDate sd = QDate::currentDate())
    : postID(p), owner(o), description(d), activity(a), totalLikes(tl), totalComments(tc), sharedDate(sd)
{
    likedBy = new User*[10] {0};  // Post can only have 10 likes or comments.
    comments = new Comment*[10] {0};
}

Post::~Post()
{
    for (int i = 0; i < totalComments; i++) {  // Since Comments are responsibility of Post(Composition), delete them here.
        delete comments[i];
    }
    delete[] comments;
    delete[] likedBy;
}

int& Post::getPostID() { return postID; }

User*& Post::getOwner() { return owner; }

QString& Post::getDescription() { return description; }

Activity& Post::getActivity() { return activity; }

int& Post::getTotalLikes() { return totalLikes; }

User**& Post::getLikedBy() { return likedBy; }

QDate& Post::getSharedDate() { return sharedDate; }

int& Post::getTotalComments() { return totalComments; }

Comment**& Post::getComments() { return comments; }

void Post::postToString(Post* post, QString& str)  // Convert Post into a displayable Text.
{
    str.append(QString("Post ID: %1\nAuthor: %2\nDescription: %3\nLikes: %4\nDate: %5\n").arg(post->getPostID()).arg(post->getOwner()->getName()).arg(post->getDescription())
                   .arg(post->getTotalLikes()).arg(post->getSharedDate().toString()));
    if (post->getLikedBy()) {  // If people have liked post, display them.
        str.append("Liked By:\n");
        for (int i = 0; i < post->getTotalLikes(); i++ ) {
            str.append(QString("\t%1\n").arg(post->getLikedBy()[i]->getName()));
        }
    }
    if (post->getComments()) {  // If people have commented on post, display them.
        str.append("Comments:\n");
        for (int i = 0; i < post->getTotalComments(); i++ ) {
            str.append(QString("\t%1:\n\t\t%2\n").arg(post->getComments()[i]->getAuthor()->getName()).arg(post->getComments()[i]->getContent()));
        }
    }
    str.append("\n");
}

