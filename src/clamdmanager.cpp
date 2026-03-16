#include "clamdmanager.h"
#define css_red "background-color:red;color:yellow"
#define css_green "background-color:green;color:yellow"
#define css_mono "background-color:#404040;color:white"

clamdManager::clamdManager(QWidget* parent, setupFileHandler* setupFile) : QWidget(parent), m_setupFile(setupFile)
{
    m_ui.setupUi(this);
    m_startup = true;
    m_monochrome = false;
    m_waitForFreshclam = true;
    m_clamdStartupCounter = 0;

    m_startDelayTimer = new QTimer(this);
    m_startDelayTimer->setSingleShot(true);
    connect(m_startDelayTimer, SIGNAL(timeout()), this, SLOT(slot_startDelayTimerExpired()));

    m_processWatcher = new QTimer(this);
    connect(m_processWatcher, SIGNAL(timeout()), this, SLOT(slot_processWatcherExpired()));
    m_processWatcher->start(30000);

    //initClamdSettings();

}

QString clamdManager::trimLocationOutput(QString value)
{
    QString rc = value;
    int start = rc.indexOf(" ") + 1;
    int ende = rc.indexOf(" ", start);

    ende = ende - start;
    rc = value.mid(start, ende);
    rc = rc.replace("\n", "");
    return rc;
}

void clamdManager::slot_initClamdSettings()
{
    m_initprocessrunning = true;
    // QStringList keywords;
    m_dirsUnderMonitoring = 0;
    m_logHighlighter = NULL;

    m_sudoGUI = m_setupFile->getSectionValue("Settings", "SudoGUI");

    QFile clamdConfFile(QDir::homePath() + "/.clamav-gui/clamd.conf");

    /*if (clamdConfFile.exists() == false) {
        m_clamdConf = new setupFileHandler(QDir::homePath() + "/.clamav-gui/clamd.conf", this);
        QString value = m_setupFile->getSectionValue("Directories", "LoadSupportedDBFiles");
        if (value.indexOf("checked|") == 0)
            m_clamdConf->addSingleLineValue("DatabaseDirectory", value.mid(value.indexOf("|") + 1));
        m_clamdConf->setSingleLineValue("LogSyslog", "no");
        m_clamdConf->setSingleLineValue("LogFacility", "LOG_LOCAL6");
        m_clamdConf->setSingleLineValue("PidFile", "/tmp/clamd.pid");
        m_clamdConf->setSingleLineValue("ExtendedDetectionInfo", "yes");
        m_clamdConf->setSingleLineValue("LocalSocket", QDir::homePath() + "/.clamav-gui/clamd-socket");
        m_clamdConf->setSingleLineValue("LogFile", QDir::homePath() + "/.clamav-gui/clamd.log");
        m_clamdConf->setSingleLineValue("LocalSocketGroup", "users");
        m_clamdConf->setSingleLineValue("TCPAddr", "127.0.0.1");
        m_clamdConf->setSingleLineValue("TCPAddr", "::1");
        m_clamdConf->setSingleLineValue("LogFileMaxSize", "1M");
        m_clamdConf->setSingleLineValue("LogTime", "yes");
        m_clamdConf->setSingleLineValue("LogRotate", "yes");
        m_clamdConf->setSingleLineValue("OnAccessMaxFileSize", "10M");
        m_clamdConf->setSingleLineValue("OnAccessMaxThreads", "10");
        m_clamdConf->setSingleLineValue("OnAccessPrevention", "yes");
        m_clamdConf->setSingleLineValue("OnAccessDenyOnError", "no");
        m_clamdConf->setSingleLineValue("OnAccessExtraScanning", "yes");
        m_clamdConf->setSingleLineValue("OnAccessRetryAttempts", "0");
        m_clamdConf->setSingleLineValue("OnAccessExcludeUname", "root");
        m_clamdConf->setSingleLineValue("OnAccessExcludeUID", "0");
    } else {*/
        m_clamdConf = new setupFileHandler(QDir::homePath() + "/.clamav-gui/clamd.conf", this);
    //}

    QStringList parameters;
    QStringList monitorings = m_setupFile->getKeywords("Clamonacc");
    m_dirsUnderMonitoring = monitorings.length();

    m_ui.monitoringComboBox->addItems(monitorings);

    m_clamdPidWatcher = new QFileSystemWatcher(this);
    connect(m_clamdPidWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slot_pidWatcherTriggered()));

    m_clamdLocationProcess = new QProcess(this);
    connect(m_clamdLocationProcess, SIGNAL(finished(int)), this, SLOT(slot_clamdLocationProcessFinished()));

    m_clamonaccLocationProcess = new QProcess(this);
    connect(m_clamonaccLocationProcess, SIGNAL(finished(int)), this, SLOT(slot_clamonaccLocationProcessFinished()));

    m_startClamdProcess = new QProcess(this);
    connect(m_startClamdProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slot_startClamdProcessFinished(int, QProcess::ExitStatus)));

    m_killProcess = new QProcess(this);
    connect(m_killProcess, SIGNAL(finished(int)), this, SLOT(slot_killClamdProcessFinished()));

    m_findclamonaccProcess = new QProcess(this);
    connect(m_findclamonaccProcess, SIGNAL(finished(int)), this, SLOT(slot_findclamonaccProcessFinished(int)));

    m_restartClamonaccProcess = new QProcess(this);
    connect(m_restartClamonaccProcess, SIGNAL(finished(int)), this, SLOT(slot_restartClamonaccProcessFinished()));

    if (checkClamdRunning() == true) {
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("green"));
        m_ui.startStopClamdPushButton->setText(tr("  Clamd running - Stop clamd"));
        m_ui.startStopClamdPushButton->setIcon(QIcon(":/icons/icons/stopclamd.png"));
        m_clamdPidWatcher->addPath("/tmp/clamd.pid");
    }
    else {
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("red"));
    }

    m_clamdRestartInProgress = false;

    m_ui.restartClamdPushButton->setVisible(false);
    slot_updateClamdConf();

    parameters << "clamd";
    m_clamdLocationProcess->start("whereis", parameters);

    parameters.clear();
    parameters << "clamonacc";
    m_clamonaccLocationProcess->start("whereis", parameters);

    m_initprocessrunning = false;

    getClamdConfElements();
}

void clamdManager::slot_dbPathChanged(QString dbPath)
{
    m_clamdConf->setSingleLineValue("DatabaseDirectory", dbPath);
    slot_clamdSettingsChanged();
}

void clamdManager::slot_updateClamdConf()
{
    QStringList path;
    QString logPath = QDir::homePath() + "/.clamav-gui/clamd.log";
    QFile checkFile(logPath);

    if (checkFile.exists() == false) {
        if (checkFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            checkFile.close();
        }
    }
    else {
        slot_logFileContentChanged();
    }

    path << logPath;

    m_clamdLogWatcher = new QFileSystemWatcher(path, this);
    connect(m_clamdLogWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slot_logFileContentChanged()));

    m_freshclamConf = new setupFileHandler(QDir::homePath() + "/.clamav-gui/freshclam.conf", this);

    QStringList watchList = m_setupFile->getKeywords("Clamonacc");
    foreach (QString entry, watchList) {
        m_clamdConf->addSingleLineValue("OnAccessIncludePath", entry);
    }

    if ((m_setupFile->sectionExists("REGEXP_and_IncludeExclude")) &&
        (m_setupFile->getSectionValue("REGEXP_and_IncludeExclude", "DontScanDiretoriesMatchingRegExp").indexOf("checked|") == 0))
        m_clamdConf->addSingleLineValue("ExcludePath",
                                        m_setupFile->getSectionValue("REGEXP_and_IncludeExclude", "DontScanDiretoriesMatchingRegExp").mid(8));
    if ((m_setupFile->sectionExists("REGEXP_and_IncludeExclude")) &&
        (m_setupFile->getSectionValue("REGEXP_and_IncludeExclude", "DontScanFileNamesMatchingRegExp").indexOf("checked|") == 0))
        m_clamdConf->addSingleLineValue("ExcludePath",
                                        m_setupFile->getSectionValue("REGEXP_and_IncludeExclude", "DontScanDiretoriesMatchingRegExp").mid(8));
    if (m_setupFile->getSectionBoolValue("REGEXP_and_IncludeExclude", "EnablePUAOptions") == true) {
        QStringList PUAKeywords;
        PUAKeywords << "LoadPUAPacked" << "LoadPUAPWTool" << "LoadPUANetTool" << "LoadPUAP2P" << "LoadPUAIRC" << "LoadPUARAT" << "LoadPUANetToolSpy"
                    << "LoadPUAServer";
        PUAKeywords << "LoadPUAScript" << "LoadPUAAndr" << "LoadPUAJava" << "LoadPUAOsx" << "LoadPUATool" << "LoadPUAUnix" << "LoadPUAWin";

        QStringList PUASwitches;
        PUASwitches << "Packed" << "PWTool" << "NetTool" << "P2P" << "IRC" << "RAT" << "NetToolSpy" << "Server" << "Script" << "Andr" << "Java"
                    << "Osx" << "Tool" << "Unix" << "Win";

        for (int i = 0; i < PUAKeywords.length(); i++) {
            if (m_setupFile->getSectionBoolValue("REGEXP_and_IncludeExclude", PUAKeywords.at(i)) == true)
                m_clamdConf->addSingleLineValue("IncludePUA", PUASwitches.at(i));
        }
    }
}

void clamdManager::slot_logFileContentChanged()
{
    QFile file(QDir::homePath() + "/.clamav-gui/clamd.log");
    QString content;
    QString checkString;

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        content = stream.readAll();
        file.close();
    }

    QStringList lines = content.split("\n");
    foreach (QString line, lines) {
        if ((line.indexOf("/") == 0) && (line.indexOf("FOUND") == line.length() - 5))
            checkString = line;
    }

    if ((checkString != m_lastFound) && (checkString != "")) {
        m_lastFound = checkString;
        emit setBallonMessage(2, tr("WARNING"), m_lastFound);
    }

    m_ui.clamdLogPlainTextEdit->clear();
    m_ui.clamdLogPlainTextEdit->insertPlainText(content);
    m_ui.clamdLogPlainTextEdit->ensureCursorVisible();
}

void clamdManager::slot_clamdStartStopButtonClicked()
{
    QStringList monitorings = m_setupFile->getKeywords("Clamonacc");

    QStringList parameters;
    QFile pidFile("/tmp/clamd.pid");
    QString clamonaccOptions;

    if (m_setupFile->getSectionValue("Directories", "MoveInfectedFiles").indexOf("checked") == 0) {
        QString path = m_setupFile->getSectionValue("Directories", "MoveInfectedFiles");
        path = path.mid(path.indexOf("|") + 1);
        clamonaccOptions = " --move=" + path;
    }

    if (m_setupFile->getSectionValue("Directories", "CopyInfectedFiles").indexOf("checked") == 0) {
        QString path = m_setupFile->getSectionValue("Directories", "CopyInfectedFiles");
        path = path.mid(path.indexOf("|") + 1);
        clamonaccOptions = clamonaccOptions + " --copy=" + path;
    }

    if (m_setupFile->getSectionValue("Directories", "ScanReportToFile").indexOf("checked") == 0) {
        QString path = m_setupFile->getSectionValue("Directories", "ScanReportToFile");
        path = path.mid(path.indexOf("|") + 1);
        clamonaccOptions = clamonaccOptions + " --log=" + path;
    }

    if (m_setupFile->keywordExists("Directories", "--verbose") == true)
        clamonaccOptions += " --verbose";
    if (m_setupFile->keywordExists("SelectedOptions", "--remove<equal>yes") == true)
        clamonaccOptions += "--remove";
    if (m_setupFile->keywordExists("SelectedOptions", "--allmatch<equal>yes") == true)
        clamonaccOptions += "--allmatch";

    if (checkClamdRunning() == false) {
        slot_updateClamdConf();

        m_ui.clamdIconLabel->setMovie(new QMovie(":/icons/icons/gifs/spinning_segments_small.gif"));
        m_ui.clamdIconLabel->movie()->start();

        m_clamdLogWatcher->removePath(QDir::homePath() + "/.clamav-gui/clamd.log");
        QFile logFile(QDir::homePath() + "/.clamav-gui/clamd.log");
        if (logFile.exists() == true)
            logFile.remove();
        if (logFile.open(QIODevice::ReadWrite)) {
            QTextStream stream(&logFile);
            stream << "";
            logFile.close();
        }
        m_clamdLogWatcher->addPath(QDir::homePath() + "/.clamav-gui/clamd.log");

        m_ui.clamdLogPlainTextEdit->clear();
        m_ui.startStopClamdPushButton->setText(tr("  Clamd starting. Please wait!"));

        QFile startclamdFile(QDir::homePath() + "/.clamav-gui/startclamd.sh");
        if (startclamdFile.exists() == true)
            startclamdFile.remove();
        if (startclamdFile.open(QIODevice::Text | QIODevice::ReadWrite)) {
            QString logFile = m_clamdConf->getSingleLineValue("LogFile");
            QTextStream stream(&startclamdFile);
            if (monitorings.length() > 0) {
                stream << "#!/bin/bash\n"
                       << m_clamdLocation + " 2> " + logFile + " -c " + QDir::homePath() + "/.clamav-gui/clamd.conf && " + m_clamonaccLocation +
                              " -c " + QDir::homePath() + "/.clamav-gui/clamd.conf -l " + QDir::homePath() + "/.clamav-gui/clamd.log" +
                              clamonaccOptions;
            }
            else {
                stream << "#!/bin/bash\n" << m_clamdLocation + " 2> " + logFile + " -c " + QDir::homePath() + "/.clamav-gui/clamd.conf";
                m_setupFile->setSectionValue("Clamd", "Status2", "n/a");
            }
            startclamdFile.close();
            startclamdFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner | QFileDevice::ReadGroup |
                                          QFileDevice::WriteGroup | QFileDevice::ExeGroup);
        }
        parameters << QDir::homePath() + "/.clamav-gui/startclamd.sh";
        if (m_sudoGUI == "")
            m_sudoGUI = m_setupFile->getSectionValue("Settings", "SudoGUI");
        m_startClamdProcess->start(m_sudoGUI, parameters);
        m_setupFile->setSectionValue("Clamd", "Status", "starting up ...");
        if (m_dirsUnderMonitoring > 0)
            m_setupFile->setSectionValue("Clamd", "Status2", "starting up ...");
        emit systemStatusChanged();
    }
    else {
        m_setupFile->setSectionValue("Clamd", "Status", "shutting down ...");
        emit systemStatusChanged();
        QString pid = "";
        if (pidFile.open(QIODevice::ReadOnly)) {
            QTextStream stream(&pidFile);
            pid = stream.readLine();
            pidFile.close();
        }
        m_ui.startStopClamdPushButton->setText(tr("  Stopping Clamd. Please wait!"));
        QFile stopclamdFile(QDir::homePath() + "/.clamav-gui/stopclamd.sh");
        if (stopclamdFile.exists() == true)
            stopclamdFile.remove();
        if (stopclamdFile.open(QIODevice::Text | QIODevice::ReadWrite)) {
            QTextStream stream(&stopclamdFile);
            if (m_clamonaccPid != "n/a") {
                stream << "#!/bin/bash\n/bin/kill -sigterm " + pid + " && kill -9 " + m_clamonaccPid;
            }
            else {
                stream << "#!/bin/bash\n/bin/kill -sigterm " + pid;
            }
            stopclamdFile.close();
            stopclamdFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner | QFileDevice::ReadGroup |
                                         QFileDevice::WriteGroup | QFileDevice::ExeGroup);
        }
        parameters << QDir::homePath() + "/.clamav-gui/stopclamd.sh";
        if (m_sudoGUI == "")
            m_sudoGUI = m_setupFile->getSectionValue("Settings", "SudoGUI");
        m_killProcess->start(m_sudoGUI, parameters);
    }
    m_ui.startStopClamdPushButton->setEnabled(false);
    m_ui.monitoringAddButton->setEnabled(false);
    m_ui.monitoringDelButton->setEnabled(false);
}

void clamdManager::slot_startClamdProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if ((exitCode != 0) || (exitStatus == QProcess::CrashExit))
        m_clamdStartupCounter = 0;
    m_ui.clamdIconLabel->clear();
    m_ui.clamdIconLabel->setPixmap(QPixmap(":/icons/icons/onaccess.png"));
    m_ui.clamdIconLabel_2->clear();
    ;
    m_ui.clamdIconLabel_2->setPixmap(QPixmap(":/icons/icons/options.png"));

    if (checkClamdRunning() == false) {
        m_clamdPidWatcher->removePath("/tmp/clamd.pid");
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("red"));
        m_ui.startStopClamdPushButton->setText(tr("  Clamd not running - Start Clamd"));
        m_ui.startStopClamdPushButton->setIcon(QIcon(":/icons/icons/startclamd.png"));

        m_setupFile->setSectionValue("Clamd", "ClamdPid", "n/a");
        m_setupFile->setSectionValue("Clamd", "ClamonaccPid", "n/a");
        m_setupFile->setSectionValue("Clamd", "Status", "not running");

        emit systemStatusChanged();

        if (m_clamdStartupCounter > 0) {
            if (m_waitForFreshclam == false)
                m_clamdStartupCounter--;
            m_startDelayTimer->start(2500);
        }
    }
    else {
        m_clamdStartupCounter = 0;

        m_clamdPidWatcher->addPath("/tmp/clamd.pid");

        QFile pidFile("/tmp/clamd.pid");
        if (pidFile.open(QIODevice::ReadOnly)) {
            QTextStream stream(&pidFile);
            QString pid = stream.readLine();
            pid = pid.replace("\n", "");

            m_setupFile->setSectionValue("Clamd", "ClamdPid", pid);
            m_setupFile->setSectionValue("Clamd", "Status", "is running");

            pidFile.close();
        }

        emit systemStatusChanged();
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("green"));
        m_ui.startStopClamdPushButton->setText(tr("  Clamd running - Stop Clamd"));
        m_ui.startStopClamdPushButton->setIcon(QIcon(":/icons/icons/stopclamd.png"));

        slot_logFileContentChanged();

        QStringList parameters;
        parameters << "-s" << "clamonacc";
        m_findclamonaccProcess->start("pidof", parameters);
    }

    m_clamdRestartInProgress = false;

    m_ui.startStopClamdPushButton->setEnabled(true);
    m_ui.monitoringAddButton->setEnabled(true);
    m_ui.monitoringDelButton->setEnabled(true);
    m_ui.restartClamdPushButton->setVisible(false);
}

void clamdManager::slot_killClamdProcessFinished()
{
    m_ui.clamdIconLabel->clear();
    m_ui.clamdIconLabel->setPixmap(QPixmap(":/icons/icons/onaccess.png"));
    m_ui.clamdIconLabel_2->clear();
    ;
    m_ui.clamdIconLabel_2->setPixmap(QPixmap(":/icons/icons/options.png"));

    if (checkClamdRunning() == false) {
        m_clamdPidWatcher->removePath("/tmp/clamd.pid");
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("red"));
        m_ui.startStopClamdPushButton->setText(tr("  Clamd not running - Start Clamd"));
        m_ui.startStopClamdPushButton->setIcon(QIcon(":/icons/icons/startclamd.png"));

        m_setupFile->setSectionValue("Clamd", "ClamdPid", "n/a");
        m_setupFile->setSectionValue("Clamd", "ClamonaccPid", "n/a");
        m_setupFile->setSectionValue("Clamd", "Status", "shut down");
        if (m_dirsUnderMonitoring > 0)
            m_setupFile->setSectionValue("Clamd", "Status2", "shut down");

        emit systemStatusChanged();
    }
    else {
        m_clamdPidWatcher->addPath("/tmp/clamd.pid");
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("green"));
        m_ui.startStopClamdPushButton->setText(tr("  Clamd running - Stop Clamd"));
        m_ui.startStopClamdPushButton->setIcon(QIcon(":/icons/icons/stopclamd.png"));
    }

    m_ui.startStopClamdPushButton->setEnabled(true);
    m_ui.monitoringAddButton->setEnabled(true);
    m_ui.monitoringDelButton->setEnabled(true);
}

void clamdManager::slot_findclamonaccProcessFinished(int rc)
{
    if (rc == 0) {
        m_clamonaccPid = m_findclamonaccProcess->readAllStandardOutput();
        m_clamonaccPid = m_clamonaccPid.replace("\n", "");
        m_setupFile->setSectionValue("Clamd", "ClamonaccPid", m_clamonaccPid);
        emit systemStatusChanged();
    }
    else {
        m_clamonaccPid = "";
        m_setupFile->setSectionValue("Clamd", "ClamonaccPid", "n/a");
        emit systemStatusChanged();
    }

    if ((m_setupFile->keywordExists("Clamd", "StartClamdOnStartup") == true) &&
        (m_setupFile->getSectionBoolValue("Clamd", "StartClamdOnStartup") == true)) {
        m_ui.startClamdOnStartupCheckBox->setChecked(m_setupFile->getSectionBoolValue("Clamd", "StartClamdOnStartup"));
    }
}

void clamdManager::slot_startDelayTimerExpired()
{
    if (checkClamdRunning() == false) {
        emit setActiveTab();
        slot_clamdStartStopButtonClicked();
    }
}

void clamdManager::slot_waitForFreshclamStarted()
{
    m_waitForFreshclam = false;

    if ((m_startup == true) && (m_setupFile->keywordExists("Clamd", "StartClamdOnStartup") == true) &&
        (m_setupFile->getSectionBoolValue("Clamd", "StartClamdOnStartup") == true)) {
        m_ui.startClamdOnStartupCheckBox->setChecked(m_setupFile->getSectionBoolValue("Clamd", "StartClamdOnStartup"));

        m_clamdStartupCounter = 5;
        if (m_startup == true)
            m_startDelayTimer->start(2500);
        m_startup = false;
    }
}

void clamdManager::slot_processWatcherExpired()
{
    QString clamdPid = m_setupFile->getSectionValue("Clamd", "ClamdPid");
    QString clamonaccPid = m_setupFile->getSectionValue("Clamd", "ClamonaccPid");

    QDir checkDir;
    if (clamdPid != "n/a") {
        if (checkDir.exists("/proc/" + clamdPid) == false) {
            m_setupFile->setSectionValue("Clamd", "ClamdPid", "n/a");

            emit systemStatusChanged();

            slot_killClamdProcessFinished();
        }
    }

    if (clamonaccPid != "n/a") {
        if (checkDir.exists("/proc/" + clamonaccPid) == false) {
            m_setupFile->setSectionValue("Clamd", "ClamonaccPid", "n/a");
            emit systemStatusChanged();
        }
    }
}

void clamdManager::slot_add_remove_highlighter(bool state)
{
    if (state == true) {
        if (m_logHighlighter != NULL) {
            delete m_logHighlighter;
            m_logHighlighter = NULL;
        }
        m_monochrome = true;
        m_ui.clamonaccLabel->setStyleSheet("padding:3px");
        m_ui.clamdLabel_3->setStyleSheet("padding:3px");
    }
    else {
        if (m_logHighlighter == NULL) {
            m_logHighlighter = new highlighter(m_ui.clamdLogPlainTextEdit->document());
        }
        else {
            delete m_logHighlighter;
            m_logHighlighter = new highlighter(m_ui.clamdLogPlainTextEdit->document());
        }
        m_monochrome = false;
        m_ui.clamonaccLabel->setStyleSheet("background-color:#c0c0c0;color:black;padding:3px");
        m_ui.clamdLabel_3->setStyleSheet("background-color:#c0c0c0;color:black;padding:3px");
    }
    checkClamdRunning();
}

void clamdManager::slot_pidWatcherTriggered()
{
    QFile pidFile("/tmp/clamd.pid");
    if ((pidFile.exists() == false) && (m_clamdRestartInProgress == false)) {
        m_clamdPidWatcher->removePath("/tmp/clamd.pid");
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("red"));
        m_ui.startStopClamdPushButton->setText(tr("  Clamd not running - Start Clamd"));
        m_ui.startStopClamdPushButton->setIcon(QIcon(":/icons/icons/startclamd.png"));
        m_ui.startStopClamdPushButton->setEnabled(true);
        m_ui.monitoringAddButton->setEnabled(true);
        m_ui.monitoringDelButton->setEnabled(true);

        m_setupFile->setSectionValue("Clamd", "ClamdPid", "n/a");
        m_setupFile->setSectionValue("Clamd", "ClamonaccPid", "n/a");
        if (m_dirsUnderMonitoring > 0)
            m_setupFile->setSectionValue("Clamd", "Status2", "not Running");
        m_setupFile->setSectionValue("Clamd", "Status", "not running");

        emit systemStatusChanged();
    }
}

void clamdManager::slot_clamdLocationProcessFinished()
{
    QString searchstring = "clamd:";
    QString output = m_clamdLocationProcess->readAll();
    if (output == searchstring + "\n") {
        m_ui.startStopClamdPushButton->setEnabled(false);
        m_ui.monitoringAddButton->setEnabled(false);
        m_ui.monitoringDelButton->setEnabled(false);

        m_setupFile->setSectionValue("Clamd", "ClamdLocation", "n/a");

        emit systemStatusChanged();
    }
    else {
        m_clamdLocation = trimLocationOutput(output);

        m_setupFile->setSectionValue("Clamd", "ClamdLocation", m_clamdLocation);

        emit systemStatusChanged();
    }
}

void clamdManager::slot_clamonaccLocationProcessFinished()
{
    QString searchstring = "clamonacc:";
    QString output = m_clamonaccLocationProcess->readAll();
    if (output == searchstring + "\n") {
        m_ui.startStopClamdPushButton->setEnabled(false);
        m_ui.monitoringAddButton->setEnabled(false);
        m_ui.monitoringDelButton->setEnabled(false);

        m_setupFile->setSectionValue("Clamd", "ClamonaccLocation", "n/a");

        emit systemStatusChanged();
    }
    else {
        m_clamonaccLocation = trimLocationOutput(output);
        m_setupFile->setSectionValue("Clamd", "ClamonaccLocation", m_clamonaccLocation);

        emit systemStatusChanged();

        QStringList parameters;
        parameters << "-s" << "clamonacc";
        m_findclamonaccProcess->start("pidof", parameters);
    }
}

void clamdManager::slot_startClamdOnStartupCheckBoxClicked()
{
    m_setupFile->setSectionValue("Clamd", "StartClamdOnStartup", m_ui.startClamdOnStartupCheckBox->isChecked());
}

void clamdManager::slot_monitoringAddButtonClicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Directory to monitor"), QDir::homePath());
    if (path != "") {
        if (m_ui.monitoringComboBox->findText(path) == -1) {
            m_ui.monitoringComboBox->addItem(path);
            m_setupFile->setSectionValue("Clamonacc", path, "under monitoring");
            m_clamdConf->addSingleLineValue("OnAccessIncludePath", path);
            m_dirsUnderMonitoring++;
            if (checkClamdRunning() == true)
                restartClamonacc();
        }
        else {
            QMessageBox::warning(this, tr("WARNING"), tr("Path already under monitoring"));
        }
    }
}

void clamdManager::slot_monitoringDelButtonClicked()
{
    QString entry = m_ui.monitoringComboBox->currentText();
    if (entry != "") {
        if (QMessageBox::information(this, tr("Remove Folder from monitoring"),
                                     tr("Path: ") + entry + "\n" + tr("Do you want to remove the folder from the monitoring list?"), QMessageBox::Yes,
                                     QMessageBox::No) == QMessageBox::Yes) {
            m_setupFile->removeKeyword("Clamonacc", entry);
            m_ui.monitoringComboBox->removeItem(m_ui.monitoringComboBox->currentIndex());
            m_clamdConf->removeSingleLine("OnAccessIncludePath", entry);
            m_dirsUnderMonitoring--;
            if (checkClamdRunning() == true)
                restartClamonacc();
        }
    }
}

void clamdManager::slot_restartClamonaccProcessFinished()
{
    QStringList parameters;
    parameters << "-s" << "clamonacc";
    m_findclamonaccProcess->start("pidof", parameters);
}

void clamdManager::slot_restartClamdButtonClicked()
{
    QString pid = "";
    QFile pidFile("/tmp/clamd.pid");
    if (pidFile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&pidFile);
        pid = stream.readLine();
        pidFile.close();
    }

    m_setupFile->setSectionValue("Clamd", "ClamdPid", pid);

    QString clamonaccOptions;
    clamonaccOptions = " --copy=" + QDir::homePath() + "/.clamav-gui/quarantine";

    m_clamdRestartInProgress = true;

    m_ui.startStopClamdPushButton->setEnabled(false);
    m_ui.monitoringAddButton->setEnabled(false);
    m_ui.monitoringDelButton->setEnabled(false);
    m_ui.startStopClamdPushButton->setText(tr("  Clamd restarting. Please wait!"));
    m_ui.clamdIconLabel_2->setMovie(new QMovie(":/icons/icons/gifs/spinning_segments_small.gif"));
    m_ui.clamdIconLabel_2->movie()->start();

    QStringList parameters;

    QFile startclamdFile(QDir::homePath() + "/.clamav-gui/startclamd.sh");
    startclamdFile.remove();
    if (startclamdFile.open(QIODevice::Text | QIODevice::ReadWrite)) {
        QTextStream stream(&startclamdFile);
        if (m_dirsUnderMonitoring > 0) {
            stream << "#!/bin/bash\n"
                   << "kill -sigterm " + pid + " && kill -9 " + m_clamonaccPid + " && sleep 20 && " + m_clamdLocation + " -c " + QDir::homePath() +
                          "/.clamav-gui/clamd.conf && " + m_clamonaccLocation + " -c " + QDir::homePath() + "/.clamav-gui/clamd.conf -l " +
                          QDir::homePath() + "/.clamav-gui/clamd.log" + clamonaccOptions;
        }
        else {
            stream << "#!/bin/bash\n"
                   << "kill -sigterm " + pid + " && sleep 20 && " + m_clamdLocation + " -c " + QDir::homePath() + "/.clamav-gui/clamd.conf";
        }
        startclamdFile.close();
        startclamdFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner | QFileDevice::ReadGroup |
                                      QFileDevice::WriteGroup | QFileDevice::ExeGroup);
    }
    parameters << QDir::homePath() + "/.clamav-gui/startclamd.sh";

    if (m_sudoGUI == "")
        m_sudoGUI = m_setupFile->getSectionValue("Settings", "SudoGUI");

    m_startClamdProcess->start(m_sudoGUI, parameters);

    m_setupFile->setSectionValue("Clamd", "Status", "starting up ...");
    if (m_dirsUnderMonitoring > 0)
        m_setupFile->setSectionValue("Clamd", "Status2", "starting up ...");
    m_setupFile->setSectionValue("Clamd", "ClamdPid", "n/a");
    m_setupFile->setSectionValue("Clamd", "ClamonaccPid", "n/a");

    emit systemStatusChanged();
}

void clamdManager::slot_clamdSettingsChanged()
{
    if (m_initprocessrunning == false) {
        if (checkClamdRunning() == true) {
            m_ui.restartClamdPushButton->setVisible(true);
            m_ui.restartClamdPushButton->setStyleSheet(selectColor("green"));
        }
    }
}

void clamdManager::restartClamonacc()
{
    QStringList parameters;

    QFile restartclamdFile(QDir::homePath() + "/.clamav-gui/restartclamd.sh");
    restartclamdFile.remove();

    if (restartclamdFile.open(QIODevice::Text | QIODevice::ReadWrite)) {
        QTextStream stream(&restartclamdFile);
        if (m_clamonaccPid != "") {
            if (m_dirsUnderMonitoring > 0) {
                stream << "#!/bin/bash\n/bin/kill -9 " + m_clamonaccPid + " && " + m_clamonaccLocation + " -c " + QDir::homePath() +
                              "/.clamav-gui/clamd.conf -l " + QDir::homePath() + "/.clamav-gui/clamd.log";
            }
            else {
                stream << "#!/bin/bash\n/bin/kill -9 " + m_clamonaccPid;
            }
        }
        else {
            if (m_dirsUnderMonitoring > 0) {
                stream << "#!/bin/bash\n" + m_clamonaccLocation + " -c " + QDir::homePath() + "/.clamav-gui/clamd.conf -l " + QDir::homePath() +
                              "/.clamav-gui/clamd.log";
            }
        }
        restartclamdFile.close();
        restartclamdFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner | QFileDevice::ReadGroup |
                                        QFileDevice::WriteGroup | QFileDevice::ExeGroup);
    }

    parameters << QDir::homePath() + "/.clamav-gui/restartclamd.sh";

    if (m_sudoGUI == "")
        m_sudoGUI = m_setupFile->getSectionValue("Settings", "SudoGUI");

    m_startClamdProcess->start(m_sudoGUI, parameters);

    m_setupFile->setSectionValue("Clamd", "Status", "shutting down ...");

    emit systemStatusChanged();
}

bool clamdManager::checkClamdRunning()
{
    bool rc = false;
    QProcess checkPIDProcess;
    QStringList parameters;

    parameters << "clamd";

    int pid = checkPIDProcess.execute("pidof", parameters);

    if (pid == 0) {
        rc = true;
        QFile pidFile("/tmp/clamd.pid");
        if (pidFile.open(QIODevice::ReadOnly)) {
            QTextStream stream(&pidFile);
            QString pidString = stream.readLine();
            pidString = pidString.replace("\n", "");
            m_setupFile->setSectionValue("Clamd", "ClamdPid", pidString);
            m_setupFile->setSectionValue("Clamd", "Status", "is running");
            m_ui.startStopClamdPushButton->setStyleSheet(selectColor("green"));
            pidFile.close();
        }

        emit systemStatusChanged();
    }
    else {
        m_setupFile->setSectionValue("Clamd", "ClamdPid", "n/a");
        m_setupFile->setSectionValue("Clamd", "Status", "not running");
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("red"));
        emit systemStatusChanged();
    }

    return rc;
}

QString clamdManager::selectColor(QString color)
{
    QString rc = "";

    if (m_monochrome == true) {
        rc = css_mono;
    }
    else {
        if (color == "mono")
            rc = css_mono;
        if (color == "red")
            rc = css_red;
        if (color == "green")
            rc = css_green;
    }

    return rc;
}

void clamdManager::getClamdConfElements()
{
    QString possibleValues;
    QString keyword;
    QString content;
    QStringList splitter;
    QString valuetype;
    QString skipvalues = "|Example|OnAccessIncludePath|LogFile|PidFile|LocalSocketMode|";
    int poscounter = 0;
    bool skip = false;
    QStringList clamdConfElement;

    if (m_setupFile->getSectionBoolValue("Setup", "DisableLogHighlighter") == false) {
        m_logHighlighter = new highlighter(m_ui.clamdLogPlainTextEdit->document());
        m_monochrome = false;
        if (checkClamdRunning() == true) {
            m_ui.startStopClamdPushButton->setStyleSheet(selectColor("green"));
        }
        else {
            m_ui.startStopClamdPushButton->setStyleSheet(selectColor("red"));
        }
        m_ui.clamonaccLabel->setStyleSheet("background-color:#c0c0c0;color:black;padding:3px");
        m_ui.clamdLabel_3->setStyleSheet("background-color:#c0c0c0;color:black;padding:3px");
    }
    else {
        m_monochrome = true;
        m_ui.startStopClamdPushButton->setStyleSheet(selectColor("mono"));
        m_ui.clamonaccLabel->setStyleSheet("padding:3px");
        m_ui.clamdLabel_3->setStyleSheet("padding:3px");
    }

    QFile file(QDir::homePath() + "/.clamav-gui/clamd.conf.man");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        content = stream.readAll();
        file.close();

        content = content.mid(content.indexOf("Example"));
        content = content.left(content.indexOf("NOTES"));
        content = content.trimmed();
        QStringList lines = content.split("\n");
        content = "";

        foreach(QString line, lines){
            if (line != "") {
                if (line.mid(0,14) != "              ") {
                    skip = false;
                    line = line.trimmed();
                    poscounter = 0;
                    splitter = line.split(" ");
                    keyword = splitter[0];
                    if (splitter.length() == 2) valuetype = splitter[1]; else valuetype = "VALUETYPE";
                    if (skipvalues.indexOf("|" + keyword + "|") != -1) skip = true; else content = content + "\n";
                }
                if (skip == false) {
                    if (poscounter == 0) {
                        line = line.trimmed();
                        if ((line.indexOf("ExcludePath") == 0) || (line.indexOf("OnAccess") == 0)) line = "2" + line; else line = "1" + line;
                        if (valuetype == "VALUETYPE") {
                            content = content + line + " VALUETYPE|";
                        } else {
                            content = content + line + "|";
                        }
                    } else {
                        if (line.left(18) == "                  ") {
                            QString helperstring = line.mid(18);
                            if (helperstring.indexOf(" - ") != -1) {
                                QString newValue = helperstring.left(helperstring.indexOf(" - "));
                                possibleValues == ""?possibleValues = possibleValues + newValue:possibleValues = possibleValues + "," + newValue;
                            }
                        }
                        line = line.trimmed();
                        content.right(1) == "|"?content = content + line:content = content + " " + line;
                        if (line.indexOf("Default:") != -1) {
                            QString defaultvalue = line.mid(line.indexOf("Default:") + 9);
                            if (valuetype == "VALUETYPE") {
                                if ((defaultvalue.indexOf("yes") != -1) || (defaultvalue.indexOf("no") != -1)) {
                                    valuetype = "BOOL";
                                } else {
                                    valuetype = "NUMBER";
                                }
                                content = content.replace("VALUETYPE",valuetype);
                            }
                            //if (valuetype == "SIZE") qDebug() << "Keyword: " << keyword << " Value: " << valuetype << " Default: " << defaultvalue;
                            if (valuetype == "BOOL") {
                                defaultvalue = defaultvalue.left(3);
                                defaultvalue = defaultvalue.trimmed();
                                content = content + "|yes,no," + defaultvalue;
                            }
                            if ((valuetype == "STRING") || (valuetype == "CATEGORY") || (valuetype == "COMMAND") || (valuetype == "REGEX")) {
                                if (defaultvalue == "LOG_LOCAL6") possibleValues = "LOG_LOCAL6,LOG_MAIL";
                                possibleValues != ""?content = content + "|" + possibleValues + "," + defaultvalue:content = content + "|" + defaultvalue;
                            }
                            if (valuetype == "NUMBER") {
                                if ((defaultvalue == "disabled") && (keyword.indexOf("Socket") != -1)) {
                                    content = content + "|0,4096,0";
                                } else {
                                    if (keyword.indexOf("Port") != -1) {
                                        content = content + "|0,65536," + defaultvalue;
                                    } else {
                                        int defaultIntValue = defaultvalue.toInt();
                                        if (defaultIntValue < 0) content = content + "|-1,30,-1";
                                        if ((defaultIntValue >= 0) && (defaultIntValue < 1000)) content = content + "|0," + QString::number(defaultIntValue * 3) + "," + defaultvalue;
                                        if ((defaultIntValue >= 1000) && (defaultIntValue < 10000)) content = content + "|0," + QString::number(defaultIntValue * 2) + "," + defaultvalue;
                                        if (defaultIntValue >= 10000) content = content + "|0," + QString::number(defaultIntValue * 10) + "," + defaultvalue;
                                    }

                                }
                            }
                            if (valuetype == "SIZE") {
                                int maxIntValue = 0;
                                bool mega = false;
                                if (defaultvalue.indexOf("M") != -1) {
                                    defaultvalue = defaultvalue.replace("M","");
                                    mega = true;
                                }
                                maxIntValue = defaultvalue.toInt() * 2;
                                if (mega == true) {
                                    content = content + "|0," + QString::number(maxIntValue) + "M," + defaultvalue + "M";
                                } else {
                                    content = content + "|0," + QString::number(maxIntValue) + "," + defaultvalue;
                                }
                            }
                            possibleValues = "";
                        }
                    }
                    poscounter++;
                }
            }
        }
        content = content.trimmed();
    }

    while (content.indexOf("  ") != -1) content = content.replace("  "," ");
    clamdConfElement = content.split("\n");

    // STRING, CATEGORY, COMMAND, REGEX ----> checkbox + lineedit
    // NUMBER, SIZE ----> checkbox + spinbox
    // BOOL ----> checkbox + combobox [yes,no,....] "scanoption"

    QString keywordHelper;
    QString label;
    QString optionValues;
    QString element;
    QString group;
    QString container;

    bool checked = false;
    clamdConfStringOption* stringOption;
    clamdconfspinboxoption* spinboxOption;
    clamdconfcomboboxoption* comboboxOption;
    clamdconfmultioption * comboboxmultioption;
    QString language = setupFileHandler::getSectionValue(QDir::homePath() + "/.clamav-gui/settings.ini","Setup","language");
    if (language == "") language = "[en_GB]";
    for (int i = 0; i < clamdConfElement.length()-1; i++) {
        element = clamdConfElement.at(i);

        QStringList values = element.split("|");
        keywordHelper = values.at(0);
        label = values.at(1);

        optionValues = values.at(2);

        QStringList splitter = keywordHelper.split(" ");
        keyword = splitter.at(0);
        container = keyword.left(1);
        keyword = keyword.mid(1);
        group = splitter.at(1);

        if (optionValues == "disabled")
            optionValues = "";
        if ((group == "STRING") || (group == "CATEGORY") || (group == "COMMAND") || (group == "REGEX")) {
            if (optionValues.indexOf(",") == -1) {
                if ((label.indexOf("multiple times") != -1) || (label.indexOf("mul‐ tiple times") != -1)) {
                    QStringList tempParams = m_clamdConf->getSingleLineValues(keyword);
                    comboboxmultioption = new clamdconfmultioption(this, keyword, checked, label, tempParams, m_clamdConf,m_setupFile);
                    connect(comboboxmultioption,SIGNAL(settingChanged()),this,SLOT(slot_clamdSettingsChanged()));
                    container != "2" ? m_ui.layout1->addWidget(comboboxmultioption) : m_ui.layout2->addWidget(comboboxmultioption);
                } else {
                    stringOption = new clamdConfStringOption(this, keyword, checked, label, optionValues, m_clamdConf);
                    connect(stringOption, SIGNAL(settingChanged()), this, SLOT(slot_clamdSettingsChanged()));
                    container != "2" ? m_ui.layout1->addWidget(stringOption) : m_ui.layout2->addWidget(stringOption);
                }
            }
            else {
                comboboxOption = new clamdconfcomboboxoption(this, keyword, checked, label, optionValues, m_clamdConf);
                connect(comboboxOption, SIGNAL(settingChanged()), this, SLOT(slot_clamdSettingsChanged()));
                container != "2" ? m_ui.layout1->addWidget(comboboxOption) : m_ui.layout2->addWidget(comboboxOption);
            }
        }

        if ((group == "NUMBER") || (group == "SIZE")) {
            //if (group == "SIZE") qDebug() << keyword << optionValues;
            spinboxOption = new clamdconfspinboxoption(this, keyword, checked, label, optionValues, m_clamdConf);
            connect(spinboxOption, SIGNAL(settingChanged()), this, SLOT(slot_clamdSettingsChanged()));
            container != "2" ? m_ui.layout1->addWidget(spinboxOption) : m_ui.layout2->addWidget(spinboxOption);
        }

        if (group == "BOOL") {
            comboboxOption = new clamdconfcomboboxoption(this, keyword, checked, label, optionValues, m_clamdConf);
            connect(comboboxOption, SIGNAL(settingChanged()), this, SLOT(slot_clamdSettingsChanged()));
            container != "2" ? m_ui.layout1->addWidget(comboboxOption) : m_ui.layout2->addWidget(comboboxOption);
        }
    }
}
