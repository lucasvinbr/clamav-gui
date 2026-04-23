#ifndef SCANOPTIONBASECLASS_H
#define SCANOPTIONBASECLASS_H

#include <QWidget>

namespace Ui
{
class scanOptionBaseClass;
}

class scanOptionBaseClass : public QWidget
{
    Q_OBJECT

   public:
    explicit scanOptionBaseClass(QWidget* parent = nullptr);
    ~scanOptionBaseClass();
    virtual QString getOption();
    virtual QString getComment();
    virtual bool isChecked();

   private:
    Ui::scanOptionBaseClass* ui;
};

#endif  // SCANOPTIONBASECLASS_H
