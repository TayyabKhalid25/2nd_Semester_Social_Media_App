#ifndef SOCIALMEDIAAPP_H
#define SOCIALMEDIAAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialMediaApp;
}
QT_END_NAMESPACE

class SocialMediaApp : public QMainWindow
{
    Q_OBJECT

public:
    SocialMediaApp(QWidget *parent = nullptr);
    ~SocialMediaApp();

private:
    Ui::SocialMediaApp *ui;
};
#endif // SOCIALMEDIAAPP_H
