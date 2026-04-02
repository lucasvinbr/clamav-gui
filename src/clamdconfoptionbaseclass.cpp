#include "clamdconfoptionbaseclass.h"

ClamdConfOptionBaseClass::ClamdConfOptionBaseClass(QWidget* parent) : QWidget{parent} {}

QString ClamdConfOptionBaseClass::getKeyword()
{
    return "";
}

QString ClamdConfOptionBaseClass::getLabel()
{
    return "";
}

void ClamdConfOptionBaseClass::setValue(QString value)
{
    Q_UNUSED(value);
}

QString ClamdConfOptionBaseClass::getValue()
{
    return "";
}

void ClamdConfOptionBaseClass::setChecked(bool checked)
{
    Q_UNUSED(checked);
}

bool ClamdConfOptionBaseClass::isChecked()
{
    return false;
}
