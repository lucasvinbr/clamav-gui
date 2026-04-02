#include "clamdconfspinboxoption.h"
#define css_mono "background-color:#404040;color:white"

clamdconfspinboxoption::clamdconfspinboxoption(QWidget* parent, QString keyword, bool checked, QString label, QString options,
                                               setupFileHandler* setupFile)
    : ClamdConfOptionBaseClass(parent), m_optionKeyword(keyword), m_setupFile(setupFile)
{
    m_ui.setupUi(this);
    m_ui.checkBox->setChecked(checked);

    QStringList values = options.split(",");
    QString StringSpinMin = values.at(0);
    QString StringSpinMax = values.at(1);
    QString StringSpinValue = values.at(2);
    int spinvalue;
    int spinmin;
    int spinmax;
    if (StringSpinMax.indexOf("M") != -1) {
        m_ui.label->setText("MB");
        StringSpinValue = StringSpinValue.replace("M","");
        StringSpinMax = StringSpinMax.replace("M","");
        StringSpinMin = StringSpinMin.replace("M","");
    }
    spinmin = StringSpinMin.toInt();
    spinmax = StringSpinMax.toInt();
    spinvalue = StringSpinValue.toInt();

    m_ui.spinBox->setMinimum(spinmin);
    m_ui.spinBox->setMaximum(spinmax);
    connect(m_ui.checkBox, SIGNAL(clicked(bool)), this, SLOT(slot_checkboxClicked()));

    if (m_setupFile->singleLineExists(m_optionKeyword) == true) {
        m_ui.checkBox->setChecked(true);
        QString valueHelper = m_setupFile->getSingleLineValue(m_optionKeyword);
        if (valueHelper.indexOf("M") != -1) {
            m_ui.label->setText("MB");
            valueHelper = valueHelper.replace("M", "");
        }
        m_ui.spinBox->setValue(valueHelper.toInt());
    }
    else {
        m_ui.spinBox->setValue(spinvalue);
    }

// -------------------------------------------------------------------------
// For DEBUG reasons only.
/*    QFile file(QDir::homePath() + "/clamav-xx_XX.ts");
    if (file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)) {
        QTextStream stream(&file);
        stream << "    <message>\n        <source>" << label << "</source>\n        <translation>TRANS</translation>\n    </message>\n";
        file.close();
    }*/
// -------------------------------------------------------------------------

    label = QCoreApplication::translate("ClamAV", label.toUtf8().constData());
    m_ui.checkBox->setText(translator::beautifyString(label, 120));
    m_ui.checkBox->setToolTip(keyword);
    m_startup = false;

    slot_checkboxClicked();
}

QString clamdconfspinboxoption::getKeyword()
{
    return m_optionKeyword;
}

QString clamdconfspinboxoption::getLabel()
{
    return  m_ui.checkBox->text();
}

void clamdconfspinboxoption::setValue(QString value)
{
    m_ui.spinBox->setValue(value.toInt());
}

QString clamdconfspinboxoption::getValue()
{
    return QString::number(m_ui.spinBox->value());
}

void clamdconfspinboxoption::setChecked(bool checked)
{
    m_ui.checkBox->setChecked(checked);
}

bool clamdconfspinboxoption::isChecked()
{
    return m_ui.checkBox->isChecked();
}

void clamdconfspinboxoption::slot_checkboxClicked()
{
    if (m_startup == false) {
        bool state = m_ui.checkBox->isChecked();
        m_ui.spinBox->setEnabled(state);
        m_ui.label->setEnabled(state);
        (state == true) ? m_ui.frame->setStyleSheet(css_mono) : m_ui.frame->setStyleSheet("");
        if (state == true) {
            if (m_ui.label->text() == "MB") {
                m_setupFile->setSingleLineValue(m_optionKeyword, QString::number(m_ui.spinBox->value()) + "M");
            }
            else {
                m_setupFile->setSingleLineValue(m_optionKeyword, QString::number(m_ui.spinBox->value()));
            }
        }
        else {
            QString value = m_setupFile->getSingleLineValue(m_optionKeyword);
            m_setupFile->removeSingleLine(m_optionKeyword, value);
        }
        emit settingChanged();
    }
}

void clamdconfspinboxoption::slot_spinboxChanged()
{
    if (m_startup == false) {
        bool state = m_ui.checkBox->isChecked();
        if (state == true) {
            QString value = m_setupFile->getSingleLineValue(m_optionKeyword);
            m_setupFile->removeSingleLine(m_optionKeyword, value);
            if (m_ui.label->text() == "MB") {
                m_setupFile->setSingleLineValue(m_optionKeyword, QString::number(m_ui.spinBox->value()) + "M");
            }
            else {
                m_setupFile->setSingleLineValue(m_optionKeyword, QString::number(m_ui.spinBox->value()));
            }
            emit settingChanged();
        }
    }
}
