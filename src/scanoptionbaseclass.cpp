#include "scanoptionbaseclass.h"
#include "ui_scanoptionbaseclass.h"

scanOptionBaseClass::scanOptionBaseClass(QWidget* parent) : QWidget(parent), ui(new Ui::scanOptionBaseClass)
{
    ui->setupUi(this);
}

scanOptionBaseClass::~scanOptionBaseClass()
{
    delete ui;
}

QString scanOptionBaseClass::getOption()
{
    return "";
}

QString scanOptionBaseClass::getComment()
{
    return "";
}

bool scanOptionBaseClass::isChecked()
{
    return false;
}
