#include "socialmediaapp.h"
#include "ui_socialmediaapp.h"



SocialMediaApp::SocialMediaApp(QWidget *parent) : QMainWindow(parent), ui(new Ui::SocialMediaApp)
{
    ui->setupUi(this);
    currentUser = 0;
    totalUsers = totalPages = totalPosts = 0;
    users = 0;
    pages = 0;
    posts = 0;

    // Attempt Loading Data.
    loadData();

    // UI Initialization.
    ui->tabWidget->setTabText(0, "Home");
    ui->tabWidget->setTabText(1, "Timeline");
    ui->tabWidget->setTabText(2, "Friend List");

    // Connect UI signals of buttons to functions.
    connect(ui->actionSet_User, &QAction::triggered, this, &SocialMediaApp::setCurrentUser);
    connect(ui->actionLike_Post, &QAction::triggered, this, &SocialMediaApp::likePost);
    connect(ui->actionComment, &QAction::triggered, this, &SocialMediaApp::commentOnPost);
    connect(ui->actionShare_Memory, &QAction::triggered, this, &SocialMediaApp::shareMemory);
    connect(ui->actionView_Post, &QAction::triggered, this, &SocialMediaApp::viewPost);
    connect(ui->actionView_Timeline, &QAction::triggered, this, &SocialMediaApp::viewUserTimeline);
    connect(ui->actionView_Friend_List, &QAction::triggered, this, &SocialMediaApp::viewFriendList);
    connect(ui->actionView_Page, &QAction::triggered, this, &SocialMediaApp::viewPage);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &SocialMediaApp::closeTab);

}

SocialMediaApp::~SocialMediaApp()
{
    saveData();

    for (int i = 0; i < totalUsers; i++){
        delete users[i];
    }
    delete[] users;
    for (int i = 0; i < totalPosts; i++){
        delete posts[i];
    }
    delete[] posts;
    for (int i = 0; i < totalPages; i++){
        delete pages[i];
    }
    delete[] pages;

    delete ui;
}

void SocialMediaApp::loadData()
{
    QFile database("Database.txt");
    if (database.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream fin(&database);
        fin >> totalUsers >> totalPages >> totalPosts;
        if (totalUsers)
            users = new User*[totalUsers] {0};
        if (totalPages)
            pages = new Page*[totalPages] {0};
        if (totalPosts)
            posts = new Post*[totalPosts] {0};
        QList<QList<int>> friendids;
        QList<QList<int>> likedpageids;

        for (int i = 0; i < totalUsers; i++) {  // Reading User Data.
            fin.skipWhiteSpace();
            QString name = fin.readLine();
            int friends, likedPages;
            fin >> friends >> likedPages;
            QList<int> row;
            users[i] = new User(i + 1, name, friends, likedPages);
            for (int j = 0; j < friends; j++) {
                int friendID;
                fin >> friendID;
                row.append(friendID);
            }
            friendids.append(row);
            row.clear();
            for (int j = 0; j < likedPages; j++) {
                int pageID;
                fin >> pageID;
                row.append(pageID);
            }
            likedpageids.append(row);
        }

        for (int i = 0; i < totalPages; i++) {
            QString title;
            fin.skipWhiteSpace();
            title = fin.readLine();
            int userID, totPosts, totLikes;
            fin >> userID >> totPosts >> totLikes;
            pages[i] = new Page(i+1, users[userID - 1], title, totPosts, totLikes);
        }

        for (int i = 0; i < totalPosts; i++) {
            int userID, isActivity, day, month, year, type, likes, comments;
            fin >> userID >> isActivity >> day >> month >> year;
            QString description, value;
            fin.skipWhiteSpace();
            description = fin.readLine();
            type = 0;
            value = "";
            if (isActivity) {
                fin >> type;
                fin.skipWhiteSpace();
                value = fin.readLine();
            }
            fin >> likes >> comments;
            posts[i] = new Post(i+1, users[userID - 1], description, Activity(type, value), likes, comments, QDate(year, month, day));
            for (int j = 0; j < likes; j++) {
                int ID;
                fin >> ID;
                posts[i]->getLikedBy()[j] = users[ID - 1];
            }
            for (int j = 0; j < comments; j++) {
                int ID;
                QString text;
                fin >> ID;
                fin.skipWhiteSpace();
                text = fin.readLine();
                Comment* comment = new Comment(users[ID - 1], text);
                posts[i]->getComments()[j] = comment;
            }
        }
        // Assign pointers to arrays.
        for (int i = 0; i < totalUsers; i++) {
            for (int j = 0; j < users[i]->getTotalFriends(); j++)
                users[i]->getFriends()[j] = users[friendids[i][j] - 1];
            for (int j = 0; j < users[i]->getTotalLikedPages(); j++)
                users[i]->getLikedPages()[j] = pages[likedpageids[i][j] - 1];
        }
        database.close();
    }
}

void SocialMediaApp::saveData()
{
    QFile database("Database.txt");
    if (database.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream fout(&database);

        fout << totalUsers << "\t" << totalPages << "\t" << totalPosts << "\n";

        for (int i = 0; i < totalUsers; i++) {
            fout << users[i]->getName() << "\n";
            fout << users[i]->getTotalFriends() << "\t" << users[i]->getTotalLikedPages() << "\n";

            for (int j = 0; j < users[i]->getTotalFriends(); j++) {
                fout << users[i]->getFriends()[j]->getUserID() << "\t";
            }
            fout << "\n";

            for (int j = 0; j < users[i]->getTotalLikedPages(); j++) {
                fout << users[i]->getLikedPages()[j]->getPageID() << "\t";
            }
            fout << "\n";
        }

        for (int i = 0; i < totalPages; i++) {
            fout << pages[i]->getTitle() << "\n";
            fout << pages[i]->getOwner()->getUserID() << "\t" << pages[i]->getTotalPosts() << "\t" << pages[i]->getTotalLikes() << "\n";
        }

        for (int i = 0; i < totalPosts; i++) {
            fout << posts[i]->getOwner()->getUserID() << "\t" << (posts[i]->getActivity().getType() ? 1 : 0) << "\n";
            fout << posts[i]->getSharedDate().day() << "\t" << posts[i]->getSharedDate().month() << "\t" << posts[i]->getSharedDate().year() << "\n";
            fout << posts[i]->getDescription() << "\n";

            if (posts[i]->getActivity().getType()) {
                fout << posts[i]->getActivity().getType() << "\n";
                fout << posts[i]->getActivity().getValue() << "\n";
            }

            fout << posts[i]->getTotalLikes() << "\t" << posts[i]->getTotalComments() << "\n";

            for (int j = 0; j < posts[i]->getTotalLikes(); j++) {
                fout << posts[i]->getLikedBy()[j]->getUserID() << "\t";
            }
            fout << "\n";

            for (int j = 0; j < posts[i]->getTotalComments(); j++) {
                fout << posts[i]->getComments()[j]->getAuthor()->getUserID() << "\t";
                fout << posts[i]->getComments()[j]->getContent() << "\n";
            }
        }
        database.close();
    }
}

void SocialMediaApp::closeTab(int index)
{
    if (index > 2)
        ui->tabWidget->removeTab(index);
}

void SocialMediaApp::setCurrentUser(int userID = 0)  // Load User and view user's home, timeline, friends.
{
    if (userID) {
        currentUser = users[userID - 1];
        viewHome();
        viewUserTimeline(userID);
        viewFriendList(userID);
    } else {
        bool ok;
        userID = QInputDialog::getInt(this, "Enter UserID ", "Number:", 0, 1, totalUsers + 1, 1, &ok);
        if (ok) {
            currentUser = users[userID - 1];
            viewHome();
            viewUserTimeline(userID);
            viewFriendList(userID);
        }
    }
}

void SocialMediaApp::viewHome()
{
    QList<Post*> postList;
    // Get posts of Friends.
    for (int i = 0; i < totalPosts; i++) {
        for (int j = 0; j < currentUser->getTotalFriends(); j++) {
            if (posts[i]->getOwner() == currentUser->getFriends()[j]) {  // If owner of post is a friend of current user, get post.
                postList.append(posts[i]);
                break;
            }
        }
    }
    // Get posts of Liked Pages.
    for (int i = 0; i < currentUser->getTotalLikedPages(); i++) {  // Get posts from likedPages.
        for (int j = 0; j < currentUser->getLikedPages()[i]->getTotalPosts(); j++) {
            postList.append(currentUser->getLikedPages()[i]->getPosts()[j]);
        }
    }

    // Display posts in the UI
    if (!postList.isEmpty()){
        QString text;
        for (Post* post : postList) {
            Post::postToString(post, text);
        }
        ui->HomeText->setPlainText(text);
    }
}

void SocialMediaApp::viewPost(int postID = 0)
{
    Post* post = 0;
    if ((postID < totalPosts + 1) && (postID > 0)) {  // Check if valid ID
        post = posts[postID - 1];  // i+1 is the postID of ith post in array, so inverse is also true.
    } else {
        postID = QInputDialog::getInt(this, "Enter PostID", "Number:", 0, 1, totalPosts + 1, 1);
        post = posts[postID - 1];  // i+1 is the postID of ith post in array, so inverse is also true.
    }

    if (post) {  // Display Post in UI.
        QString text;
        Post::postToString(post, text);

        QTextBrowser* PostText = new QTextBrowser(this);  // By passing *this* as a param, Qt MainWindow will handle it's deletion on its own.
        PostText->setPlainText(text);
        QStringList namePart(post->getOwner()->getName().split(QString(" ")));
        ui->tabWidget->addTab(PostText, QString("Post (%1)").arg(namePart.constFirst()));
    }
}

void SocialMediaApp::viewUserTimeline(int userID = 0)
{
    User* user = 0;
    if (!((userID < totalUsers + 1) && (userID > 0))) {  // Check if valid ID, else prompt id.
        userID = QInputDialog::getInt(this, "Enter UserID", "Number:", 0, 1, totalUsers + 1, 1);
    }

    // Find the posts of user with the given ID
    QList<Post*> postList;
    for (int i = 0; i < totalPosts; i++) {
        if (posts[i]->getOwner()->getUserID() == userID) {
            postList.append(posts[i]);
        }
    }

    // Display posts in the UI
    if (!postList.isEmpty()){
        QString text;
        for (Post* post : postList) {
            Post::postToString(post, text);
        }
        if (userID == currentUser->getUserID()) {  // Update set tab of user's own timeline
            ui->TimelineText->setPlainText(text);
        }
        else {  // Make new tab and update that.
            QTextBrowser* PostText = new QTextBrowser(this);
            PostText->setPlainText(text);
            QStringList namePart(postList.constFirst()->getOwner()->getName().split(QString(" ")));
            ui->tabWidget->addTab(PostText, QString("Timeline (%1)").arg(namePart.constFirst()));
        }
    }
}

void SocialMediaApp::viewFriendList(int userID = 0)
{
    User* user = 0;
    if ((userID < totalUsers + 1) && (userID > 0) ) {  // Check if valid ID
        user = users[userID - 1];  // i+1 is userID of ith user in array, so the inverse is also true.
    } else {
        userID = QInputDialog::getInt(this, "Enter UserID", "Number:", 0, 1, totalUsers + 1, 1);
        user = users[userID - 1];  // i+1 is userID of ith user in array, so the inverse is also true.
    }

    // Display friend list in the UI
    if (user){
        QString text;
        text.append("Friend List: \n");
        for (int i = 0; i < user->getTotalFriends(); i++) {
            text.append(QString("\t%1: %2\n").arg(QString::number(i+1)).arg(user->getFriends()[i]->getName()));
        }
        if (userID == currentUser->getUserID()) {  // Update set tab of user's own friend list.
            ui->FriendListText->setPlainText(text);
        }
        else {  // Make new tab and update that.
            QTextBrowser* friendListText = new QTextBrowser(this);
            friendListText->setPlainText(text);
            QStringList namePart(user->getName().split(QString(" ")));
            ui->tabWidget->addTab(friendListText, QString("Friend List (%1)").arg(namePart.constFirst()));
        }
    }
}

void SocialMediaApp::viewPage()
{
    bool ok;
    int pageID = QInputDialog::getInt(this, "Enter PageID", "Number:", 0, 1, totalPages + 1, 1, &ok);
    if (ok) {
        Page* page = pages[pageID - 1];  // i+1 represents the ith page, so the inverse is also true.
        // Display the page's posts in the UI
        if (page) {
            QString text;
            for (int i = 0; i < page->getTotalPosts(); i++) {
                Post::postToString(page->getPosts()[i], text);
            }
            // Make new tab and update that.
            QTextBrowser* PageText = new QTextBrowser(this);
            PageText->setPlainText(text);
            ui->tabWidget->addTab(PageText, QString("Page (%1)").arg(page->getTitle()));
        }
    }

}

void SocialMediaApp::likePost()
{
    if (currentUser) {
        bool ok;
        int postID = QInputDialog::getInt(this, "Enter PostID ", "Number:", 0, 1, totalPosts + 1, 1, &ok);
        if (ok) {
            if (postID < totalPosts + 1 && posts[postID - 1]->getTotalLikes() < 10) {  // Post can only have 10 likes, check for valid ID.
                Post* post = posts[postID - 1];
                bool exists = false;
                for (int i = 0; i < post->getTotalLikes(); i++) {  // Check likedBy for currentUser.
                    if (post->getLikedBy()[i]->getUserID() == currentUser->getUserID()) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {  // Add the current user to likedBy if not already liked.
                    post->getLikedBy()[post->getTotalLikes()] = currentUser;
                    post->getTotalLikes()++;
                }
            }
            setCurrentUser(currentUser->getUserID());  // Refresh Perma Tabs
        }
    }
    else
        QMessageBox::information(this, "Error", "User Not Set!!!");
}


void SocialMediaApp::commentOnPost()
{
    if (currentUser) {
        bool ok;
        int postID = QInputDialog::getInt(this, "Enter PostID ", "Number:", 0, 1, totalPosts + 1, 1, &ok);
        if (ok) {
            if (postID < totalPosts + 1 && posts[postID - 1]->getTotalComments() < 10) {  // Post can only have 10 comments, check for valid ID.
                Post* post = posts[postID - 1];
                bool ok;
                QString text = QInputDialog::getText(this, "Enter Text", "Text:", QLineEdit::Normal, "", &ok);
                if (ok && !text.isEmpty()) {
                    // Generate new Comment object and update array.
                    Comment* comment = new Comment(currentUser, text);
                    post->getComments()[post->getTotalComments()++] = comment;
                }
            }
            setCurrentUser(currentUser->getUserID());  // Refresh Perma Tabs
        }
    }
    else
        QMessageBox::information(this, "Error", "User Not Set!!!");
}

void SocialMediaApp::shareMemory()
{
    if (currentUser) {
        bool ok;
        int postID = QInputDialog::getInt(this, "Enter PostID ", "Number:", 0, 1, totalPosts + 1, 1, &ok);
        if (ok) {
            if (postID < totalPosts + 1) {  // Check for valid ID.
                Post* post = posts[postID - 1];
                bool ok;
                QString text = QInputDialog::getText(this, "Enter Text", "Text:", QLineEdit::Normal, "", &ok);
                if (ok && !text.isEmpty()) {
                    // Create new Memory object and update array.
                    Memory* memory = new Memory(post, totalPosts + 1, currentUser, text, Activity(0, QString("")), 0, 0, QDate::currentDate());
                    posts[totalPosts++] = memory;
                }
            }
            setCurrentUser(currentUser->getUserID());  // Refresh Perma Tabs
        }
    }
    else
        QMessageBox::information(this, "Error", "User Not Set!!!");
}

