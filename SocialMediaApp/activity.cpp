#include "activity.h"

Activity::Activity(int t = 0, QString v = "") : type(t), value(v) {}

Activity::Activity(const Activity& rhs) : type(rhs.type), value(rhs.value) {}

int& Activity::getType() { return type; }

QString& Activity::getValue() { return value; }

QString Activity::toString()  // Returns predetermined string against type with value.
{
    QString str;
    switch (type) {
    case 1:
        str = "feeling " + value;
        break;
    case 2:
        str = "thinking about " + value;
        break;
    case 3:
        str = "making " + value;
        break;
    case 4:
        str = "celebrating " + value;
        break;
    default:
        str = "Invalid type of Activity..";
        break;
    }
    return str;
}
