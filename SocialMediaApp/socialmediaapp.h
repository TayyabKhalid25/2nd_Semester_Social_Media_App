#ifndef SOCIALMEDIAAPP_H
#define SOCIALMEDIAAPP_H

#include "ui_socialmediaapp.h"

#include <QMainWindow>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include "user.h"
#include "post.h"
#include "page.h"
#include "memory.h"
#include "comment.h"
#include "activity.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class SocialMediaApp;
}
QT_END_NAMESPACE

class SocialMediaApp final : public QMainWindow
{
    Q_OBJECT

private:
    Ui::SocialMediaApp *ui;
    User* currentUser;
    int totalUsers, totalPages, totalPosts;
    User** users;
    Page** pages;
    Post** posts;

public:
    SocialMediaApp(QWidget *parent = nullptr);
    ~SocialMediaApp();
    void loadData();  // filehandling to read
    void saveData();  // ... to write data
    void closeTab(int index);
    void setCurrentUser(int userID);
    void viewHome();
    void likePost();
    // void viewPostLikers(int postID);  // Incorporated into every display of post.
    void commentOnPost();
    void viewPost(int postID);
    void shareMemory();
    void viewUserTimeline(int userID);
    void viewFriendList(int userID);
    void viewPage();

};
#endif // SOCIALMEDIAAPP_H
