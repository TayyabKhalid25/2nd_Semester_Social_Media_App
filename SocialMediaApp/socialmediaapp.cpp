#include "socialmediaapp.h"
#include "ui_socialmediaapp.h"

SocialMediaApp::SocialMediaApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialMediaApp)
{
    ui->setupUi(this);
}

SocialMediaApp::~SocialMediaApp()
{
    delete ui;
}
