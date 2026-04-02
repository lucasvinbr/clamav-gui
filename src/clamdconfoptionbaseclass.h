#ifndef CLAMDCONFOPTIONBASECLASS_H
#define CLAMDCONFOPTIONBASECLASS_H

#include <QWidget>

class ClamdConfOptionBaseClass : public QWidget
{
    Q_OBJECT
   public:
    explicit ClamdConfOptionBaseClass(QWidget* parent = nullptr);
    virtual QString getKeyword();
    virtual QString getLabel();
    virtual void setValue(QString);
    virtual QString getValue();
    virtual void setChecked(bool);
    virtual bool isChecked();
   signals:
};

#endif  // CLAMDCONFOPTIONBASECLASS_H
