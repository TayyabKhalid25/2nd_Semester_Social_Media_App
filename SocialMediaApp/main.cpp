#include "socialmediaapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SocialMediaApp w;
    w.show();
    return a.exec();
}
