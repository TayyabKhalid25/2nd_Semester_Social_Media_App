#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>

class Activity final
{
private:
    int type;
    QString value;

public:
    Activity(int, QString);
    Activity(const Activity &rhs);
    int& getType();
    QString& getValue();
    QString toString();

};

#endif // ACTIVITY_H
