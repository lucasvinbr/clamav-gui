#include "scanoption.h"
#define css "background-color:#404040;color:white"

scanoption::scanoption(QWidget *parent, QString setupFileName, QString section, bool checked, QString label, QString comment)
: QWidget(parent)
{
    m_ui.setupUi(this);
    m_setupFile = new setupFileHandler(setupFileName,this);

    m_setupFileSection = section;
    m_option = label;

    m_com = QCoreApplication::translate("ClamAV", comment.toUtf8().constData());

// -------------------------------------------------------------------------
// For DEBUG reasons only.
/*    QFile file(QDir::homePath() + "/clamav-xx_XX.ts");
    if (file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)) {
        QTextStream stream(&file);
        stream << "    <message>\n        <source>" << comment << "</source>\n        <translation>TRANS</translation>\n    </message>\n";
        file.close();
    }*/
// -------------------------------------------------------------------------

    m_ui.checkBox->setChecked(checked);

    if (checked == true) {
        this->setStyleSheet(css);
        m_setupFile->setSectionValue(m_setupFileSection,m_option,m_com);
    }

    m_ui.checkBox->setText(translator::beautifyString(m_com));
    m_ui.checkBox->setToolTip(m_option);
}


void scanoption::slot_checkboxClicked(){
    if (m_ui.checkBox->isChecked() == false) {
        m_setupFile->removeKeyword(m_setupFileSection,m_option);
        this->setStyleSheet("");
    } else {
        m_setupFile->setSectionValue(m_setupFileSection,m_option,m_com);
        this->setStyleSheet(css);
    }

    emit valuechanged();
}
