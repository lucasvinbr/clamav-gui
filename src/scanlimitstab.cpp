#include "scanlimitstab.h"
#include "sharedvars.cpp"
#define css "background-color:#404040;color:white"

scanLimitsTab::scanLimitsTab(QWidget* parent, setupFileHandler* setupFile) : QWidget(parent), m_setupFile(setupFile)
{
    m_ui.setupUi(this);

    if (m_setupFile->sectionExists("ScanLimitations") == true)
        updateLimits();
    else
        writeLimits();
}

void scanLimitsTab::writeLimits()
{
    QString keyword;
    QString value;
    QString checked;

    if (update == false)
    {
        for (int i = 0; i < scanLimitKeywords.length(); i++)
        {
            keyword = scanLimitKeywords.at(i);
            switch (i)
            {//TODO: use switch with enum class but not integer - done!
                case FilesLargerThanThis:
                    value = QString::number(m_ui.filesLargerThanThisSpinBox->value()) + m_ui.filesLargerThanThisComboBox->currentText();
                    m_ui.filesLargerThanThisCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxAmountOfData:
                    value = QString::number(m_ui.maxAmountForContainerSpinBox->value()) + m_ui.maxAmountForContainerComboBox->currentText();
                    m_ui.maxAmountForContainerCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MinNumberOfFiles:
                    value = QString::number(m_ui.maxNumberForContainerSpinBox->value());
                    m_ui.maxNumberForContainerCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxArchiveRecursion:
                    value = QString::number(m_ui.maxArchiveRecursionForContainerSpinBox->value());
                    m_ui.maxArchiveRecursionForContainerCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxDirectoryRecursion:
                    value = QString::number(m_ui.maxDirRecursionLevelSpinBox->value());
                    m_ui.maxDirRecursionLevelCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxSizeFilePE:
                    value = QString::number(m_ui.maxSizeFileForPESpinBox->value()) + m_ui.maxSizeFileForPEComboBox->currentText();
                    m_ui.maxSizeFileForPECheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxSizeHTMLNormalize:
                    value = QString::number(m_ui.maxSizeHTMLFileToNormalizeSpinBox->value()) + m_ui.maxSizeHTMLFileToNormalizeComboBox->currentText();
                    m_ui.maxSizeHTMLFileToNormalizeCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxSizeNormalizedHTML:
                    value =
                        QString::number(m_ui.maxSizeOfNormalizedHTMLFileSpinBox->value()) + m_ui.maxSizeOfNormalizedHTMLFileComboBox->currentText();
                    m_ui.maxSizeOfNormalizedHTMLFileCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxSizeScriptFileNormalize:
                    value = QString::number(m_ui.maxSizeOfScriptFileToNormalizeSpinBox->value()) +
                            m_ui.maxSizeOfScriptFileToNormalizeComboBox->currentText();
                    m_ui.maxSizeOfScriptFileToNormalizeCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxSizeZIPReanalyze:
                    value = QString::number(m_ui.maxSizeZipToTypeReanalzeSpinBox->value()) + m_ui.maxSizeZipToTypeReanalzeComboBox->currentText();
                    m_ui.maxSizeZipToTypeReanalzeCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxNumberPartitions:
                    value = QString::number(m_ui.maxNumberOfPartitionsInDiskImageSpinBox->value());
                    m_ui.maxNumberOfPartitionsInDiskImageCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxNumberIconsPE:
                    value = QString::number(m_ui.maxNumberOfIconsInPEFileSpinBox->value());
                    m_ui.maxNumberOfIconsInPEFileCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case NumberSecondsStatsTimeout:
                    value = QString::number(m_ui.numberOfSecondsToWaitForResponseSpinBox->value());
                    m_ui.numberOfSecondsToWaitForResponseCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case BytecodeTimeout:
                    value = QString::number(m_ui.numberOfSecondsToWaitForByteCodeSpinBox->value());
                    m_ui.numberOfSecondsToWaitForByteCodeCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case CollectAndPrint:
                    value = QString::number(m_ui.collectAndPrintExecutionStatisticsComboBox->currentIndex());
                    m_ui.collectAndPrintExecutionStatisticsCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case StructSSNFormat:
                    value = QString::number(m_ui.structuredSSNFormatComboBox->currentIndex());
                    m_ui.structuredSSNFormatCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case StructSSNCount:
                    value = QString::number(m_ui.structuredSSNCountSpinBox->value());
                    m_ui.structuredSSNCountCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case StructCCCount:
                    value = QString::number(m_ui.structuredCCCountSpinBox->value());
                    m_ui.structuredCCCountCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case StructCCMode:
                    value = QString::number(m_ui.structuredCCModeComboBox->currentIndex());
                    m_ui.structuredCCModeCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxScanTime:
                    value = QString::number(m_ui.maxScanTimeSpinBox->value());
                    m_ui.maxScanTimeCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxRecursionHWP3:
                    value = QString::number(m_ui.maxRecursionHWP3SpinBox->value());
                    m_ui.maxRecursionHWP3CheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxCallsPCRE:
                    value = QString::number(m_ui.maxPCREMatchSpinBox->value());
                    m_ui.maxPCREMatchCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxRecursionCallsPCRE:
                    value = QString::number(m_ui.maxRecursionPCREMatchSpinBox->value());
                    m_ui.maxRecursionPCREMatchCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case MaxPCREFileSize:
                    value = QString::number(m_ui.maxPCREFileSizeSpinBox->value()) + m_ui.maxPCREFileSizeComboBox->currentText();
                    m_ui.maxPCREFileSizeCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
                case DatabaseOutdated:
                    value = QString::number(m_ui.databaseOutdatedSpinBox->value());
                    m_ui.databaseOutdatedCheckBox->isChecked() == true ? checked = "checked" : checked = "not checked";
                    break;
            }
            m_setupFile->setSectionValue("ScanLimitations", keyword, checked + "|" + value);
        }

        emit updateClamdConf();

        updateLimits();
    }
}

void scanLimitsTab::updateLimits()
{
    QString value;
    QString checked;
    QString keyword;
    bool flag;

    update = true;

    for (int i = 0; i < scanLimitKeywords.length(); i++)
    {
        keyword = scanLimitKeywords.at(i);
        value = m_setupFile->getSectionValue("ScanLimitations", keyword);
        checked = value.left(value.indexOf("|"));
        value = value.mid(value.indexOf("|") + 1);
        checked == "checked" ? flag = true : flag = false;

        switch (i)
        {
            case FilesLargerThanThis:
                if (value.right(1) != "")
                {
                    if ((value.indexOf("K") != -1) || (value.indexOf("M") != -1))
                    {
                        m_ui.filesLargerThanThisComboBox->setCurrentIndex(m_ui.filesLargerThanThisComboBox->findText(value.right(1)));
                        value = value.left(value.length() - 1);
                    }
                }
                m_ui.filesLargerThanThisComboBox->setEnabled(flag);
                m_ui.filesLargerThanThisCheckBox->setChecked(flag);
                if (value != "")
                    m_ui.filesLargerThanThisSpinBox->setValue(value.toInt());
                m_ui.filesLargerThanThisSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame01->setStyleSheet(css) : m_ui.frame01->setStyleSheet("");
                m_ui.frame01->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));

                break;
            case MaxAmountOfData:
                if (value.right(1) != "")
                {
                    if ((value.indexOf("K") != -1) || (value.indexOf("M") != -1))
                    {
                        m_ui.maxAmountForContainerComboBox->setCurrentIndex(m_ui.maxAmountForContainerComboBox->findText(value.right(1)));
                        value = value.left(value.length() - 1);
                    }
                }
                m_ui.maxAmountForContainerComboBox->setEnabled(flag);
                m_ui.maxAmountForContainerCheckBox->setChecked(flag);
                if (value != "")
                    m_ui.maxAmountForContainerSpinBox->setValue(value.toInt());
                m_ui.maxAmountForContainerSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame02->setStyleSheet(css) : m_ui.frame02->setStyleSheet("");
                m_ui.frame02->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));

                break;
            case MinNumberOfFiles:
                m_ui.maxNumberForContainerCheckBox->setChecked(flag);
                m_ui.maxNumberForContainerSpinBox->setValue(value.toInt());
                m_ui.maxNumberForContainerSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame03->setStyleSheet(css) : m_ui.frame03->setStyleSheet("");
                m_ui.frame03->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxArchiveRecursion:
                m_ui.maxArchiveRecursionForContainerCheckBox->setChecked(flag);
                m_ui.maxArchiveRecursionForContainerSpinBox->setValue(value.toInt());
                m_ui.maxArchiveRecursionForContainerSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame04->setStyleSheet(css) : m_ui.frame04->setStyleSheet("");
                m_ui.frame04->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxDirectoryRecursion:
                m_ui.maxDirRecursionLevelCheckBox->setChecked(flag);
                m_ui.maxDirRecursionLevelSpinBox->setValue(value.toInt());
                m_ui.maxDirRecursionLevelSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame05->setStyleSheet(css) : m_ui.frame05->setStyleSheet("");
                m_ui.frame05->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxSizeFilePE:
                if (value.right(1) != "")
                {
                    if ((value.indexOf("K") != -1) || (value.indexOf("M") != -1))
                    {
                        m_ui.maxSizeFileForPEComboBox->setCurrentIndex(m_ui.maxSizeFileForPEComboBox->findText(value.right(1)));
                        value = value.left(value.length() - 1);
                    }
                }
                m_ui.maxSizeFileForPEComboBox->setEnabled(flag);
                m_ui.maxSizeFileForPECheckBox->setChecked(flag);
                if (value != "")
                    m_ui.maxSizeFileForPESpinBox->setValue(value.toInt());
                m_ui.maxSizeFileForPESpinBox->setEnabled(flag);
                flag == true ? m_ui.frame06->setStyleSheet(css) : m_ui.frame06->setStyleSheet("");
                m_ui.frame06->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxSizeHTMLNormalize:
                if (value.right(1) != "")
                {
                    if ((value.indexOf("K") != -1) || (value.indexOf("M") != -1))
                    {
                        m_ui.maxSizeHTMLFileToNormalizeComboBox->setCurrentIndex(m_ui.maxSizeHTMLFileToNormalizeComboBox->findText(value.right(1)));
                        value = value.left(value.length() - 1);
                    }
                }
                m_ui.maxSizeHTMLFileToNormalizeComboBox->setEnabled(flag);
                m_ui.maxSizeHTMLFileToNormalizeCheckBox->setChecked(flag);
                if (value != "")
                    m_ui.maxSizeHTMLFileToNormalizeSpinBox->setValue(value.toInt());
                m_ui.maxSizeHTMLFileToNormalizeSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame07->setStyleSheet(css) : m_ui.frame07->setStyleSheet("");
                m_ui.frame07->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxSizeNormalizedHTML:
                if (value.right(1) != "")
                {
                    if ((value.indexOf("K") != -1) || (value.indexOf("M") != -1))
                    {
                        m_ui.maxSizeOfNormalizedHTMLFileComboBox->setCurrentIndex(m_ui.maxSizeOfNormalizedHTMLFileComboBox->findText(value.right(1)));
                        value = value.left(value.length() - 1);
                    }
                }
                m_ui.maxSizeOfNormalizedHTMLFileComboBox->setEnabled(flag);
                m_ui.maxSizeOfNormalizedHTMLFileCheckBox->setChecked(flag);
                if (value != "")
                    m_ui.maxSizeOfNormalizedHTMLFileSpinBox->setValue(value.toInt());
                m_ui.maxSizeOfNormalizedHTMLFileSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame08->setStyleSheet(css) : m_ui.frame08->setStyleSheet("");
                m_ui.frame08->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxSizeScriptFileNormalize:
                if (value.right(1) != "")
                {
                    if ((value.indexOf("K") != -1) || (value.indexOf("M") != -1))
                    {
                        m_ui.maxSizeOfScriptFileToNormalizeComboBox->setCurrentIndex(
                            m_ui.maxSizeOfScriptFileToNormalizeComboBox->findText(value.right(1)));
                        value = value.left(value.length() - 1);
                    }
                }
                m_ui.maxSizeOfScriptFileToNormalizeComboBox->setEnabled(flag);
                m_ui.maxSizeOfScriptFileToNormalizeCheckBox->setChecked(flag);
                if (value != "")
                    m_ui.maxSizeOfScriptFileToNormalizeSpinBox->setValue(value.toInt());
                m_ui.maxSizeOfScriptFileToNormalizeSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame09->setStyleSheet(css) : m_ui.frame09->setStyleSheet("");
                m_ui.frame09->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxSizeZIPReanalyze:
                if (value.right(1) != "")
                {
                    if ((value.indexOf("K") != -1) || (value.indexOf("M") != -1))
                    {
                        m_ui.maxSizeZipToTypeReanalzeComboBox->setCurrentIndex(m_ui.maxSizeZipToTypeReanalzeComboBox->findText(value.right(1)));
                        value = value.left(value.length() - 1);
                    }
                }
                m_ui.maxSizeZipToTypeReanalzeComboBox->setEnabled(flag);
                m_ui.maxSizeZipToTypeReanalzeCheckBox->setChecked(flag);
                if (value != "")
                    m_ui.maxSizeZipToTypeReanalzeSpinBox->setValue(value.toInt());
                m_ui.maxSizeZipToTypeReanalzeSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame10->setStyleSheet(css) : m_ui.frame10->setStyleSheet("");
                m_ui.frame10->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxNumberPartitions:
                m_ui.maxNumberOfPartitionsInDiskImageCheckBox->setChecked(flag);
                m_ui.maxNumberOfPartitionsInDiskImageSpinBox->setValue(value.toInt());
                m_ui.maxNumberOfPartitionsInDiskImageSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame11->setStyleSheet(css) : m_ui.frame11->setStyleSheet("");
                m_ui.frame11->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxNumberIconsPE:
                m_ui.maxNumberOfIconsInPEFileCheckBox->setChecked(flag);
                m_ui.maxNumberOfIconsInPEFileSpinBox->setValue(value.toInt());
                m_ui.maxNumberOfIconsInPEFileSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame12->setStyleSheet(css) : m_ui.frame12->setStyleSheet("");
                m_ui.frame12->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case NumberSecondsStatsTimeout:
                m_ui.numberOfSecondsToWaitForResponseCheckBox->setChecked(flag);
                m_ui.numberOfSecondsToWaitForResponseSpinBox->setValue(value.toInt());
                m_ui.numberOfSecondsToWaitForResponseSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame13->setStyleSheet(css) : m_ui.frame13->setStyleSheet("");
                m_ui.frame13->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case BytecodeTimeout:
                m_ui.numberOfSecondsToWaitForByteCodeCheckBox->setChecked(flag);
                m_ui.numberOfSecondsToWaitForByteCodeSpinBox->setValue(value.toInt());
                m_ui.numberOfSecondsToWaitForByteCodeSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame14->setStyleSheet(css) : m_ui.frame14->setStyleSheet("");
                m_ui.frame14->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case CollectAndPrint:
                m_ui.collectAndPrintExecutionStatisticsCheckBox->setChecked(flag);
                m_ui.collectAndPrintExecutionStatisticsComboBox->setCurrentIndex(value.toInt());
                m_ui.collectAndPrintExecutionStatisticsComboBox->setEnabled(flag);
                flag == true ? m_ui.frame15->setStyleSheet(css) : m_ui.frame15->setStyleSheet("");
                m_ui.frame15->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case StructSSNFormat:
                m_ui.structuredSSNFormatCheckBox->setChecked(flag);
                m_ui.structuredSSNFormatComboBox->setCurrentIndex(value.toInt());
                m_ui.structuredSSNFormatComboBox->setEnabled(flag);
                flag == true ? m_ui.frame16->setStyleSheet(css) : m_ui.frame16->setStyleSheet("");
                m_ui.frame16->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case StructSSNCount:
                m_ui.structuredSSNCountCheckBox->setChecked(flag);
                m_ui.structuredSSNCountSpinBox->setValue(value.toInt());
                m_ui.structuredSSNCountSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame17->setStyleSheet(css) : m_ui.frame17->setStyleSheet("");
                m_ui.frame17->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case StructCCCount:
                m_ui.structuredCCCountCheckBox->setChecked(flag);
                m_ui.structuredCCCountSpinBox->setValue(value.toInt());
                m_ui.structuredCCCountSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame18->setStyleSheet(css) : m_ui.frame18->setStyleSheet("");
                m_ui.frame18->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case StructCCMode:
                m_ui.structuredCCModeCheckBox->setChecked(flag);
                m_ui.structuredCCModeComboBox->setCurrentIndex(value.toInt());
                m_ui.structuredCCModeComboBox->setEnabled(flag);
                flag == true ? m_ui.frame19->setStyleSheet(css) : m_ui.frame19->setStyleSheet("");
                m_ui.frame19->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxScanTime:
                m_ui.maxScanTimeCheckBox->setChecked(flag);
                m_ui.maxScanTimeSpinBox->setValue(value.toInt());
                m_ui.maxScanTimeSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame20->setStyleSheet(css) : m_ui.frame20->setStyleSheet("");
                m_ui.frame20->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxRecursionHWP3:
                m_ui.maxRecursionHWP3CheckBox->setChecked(flag);
                m_ui.maxRecursionHWP3SpinBox->setValue(value.toInt());
                m_ui.maxRecursionHWP3SpinBox->setEnabled(flag);
                flag == true ? m_ui.frame21->setStyleSheet(css) : m_ui.frame21->setStyleSheet("");
                m_ui.frame21->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxCallsPCRE:
                m_ui.maxPCREMatchCheckBox->setChecked(flag);
                m_ui.maxPCREMatchSpinBox->setValue(value.toInt());
                m_ui.maxPCREMatchSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame22->setStyleSheet(css) : m_ui.frame22->setStyleSheet("");
                m_ui.frame22->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxRecursionCallsPCRE:
                m_ui.maxRecursionPCREMatchCheckBox->setChecked(flag);
                m_ui.maxRecursionPCREMatchSpinBox->setValue(value.toInt());
                m_ui.maxRecursionPCREMatchSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame23->setStyleSheet(css) : m_ui.frame23->setStyleSheet("");
                m_ui.frame23->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case MaxPCREFileSize:
                if (value.right(1) != "")
                {
                    if ((value.indexOf("K") != -1) || (value.indexOf("M") != -1))
                    {
                        m_ui.maxPCREFileSizeComboBox->setCurrentIndex(m_ui.maxPCREFileSizeComboBox->findText(value.right(1)));
                        value = value.left(value.length() - 1);
                    }
                }
                m_ui.maxPCREFileSizeComboBox->setEnabled(flag);
                m_ui.maxPCREFileSizeCheckBox->setChecked(flag);
                if (value != "")
                    m_ui.maxPCREFileSizeSpinBox->setValue(value.toInt());
                m_ui.maxPCREFileSizeSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame24->setStyleSheet(css) : m_ui.frame24->setStyleSheet("");
                m_ui.frame24->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
            case DatabaseOutdated:
                m_ui.databaseOutdatedCheckBox->setChecked(flag);
                m_ui.databaseOutdatedSpinBox->setValue(value.toInt());
                m_ui.databaseOutdatedSpinBox->setEnabled(flag);
                flag == true ? m_ui.frame25->setStyleSheet(css) : m_ui.frame25->setStyleSheet("");
                m_ui.frame25->setVisible(m_setupFile->keywordExists("OtherKeywords", scanLimitSwitches.at(i)));
                break;
        }
    }
    update = false;
}
