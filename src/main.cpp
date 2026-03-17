#include "clamav_gui.h"
#include <QTranslator>
#include <QApplication>
#include <QtNetwork/QTcpServer>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include "schedulescanobject.h"
#include "setupfilehandler.h"

#define PORT_NUM 55000

int main(int argc, char *argv[])
{
    QTranslator translator1(0);
    QTranslator translator2(0);
    QTcpServer server;
    QStringList parameters;
    QString lang;
    QString setLang;
    QString rc;
    bool translatorLoaded = false;

    QApplication a(argc, argv);
    lang = QLocale::system().name();

    if (argc > 1) rc=(QString)argv[1];
    if (argc > 2) setLang = (QString) argv[2];

    if (rc == "--language"){
        printf("\nDesktop Language Settings: %s\n",lang.toStdString().c_str());
    }

    QFile file;
    if (file.exists(QDir::homePath() + "/.clamav-gui/settings.ini") == true) {
        setupFileHandler setupFile(QDir::homePath() + "/.clamav-gui/settings.ini");
        if (setupFile.keywordExists("Setup","language") == true) {
            lang = setupFile.getSectionValue("Setup","language").mid(1,5);
        } else {
            lang = "en_GB";
        }
    }

    if (rc == "--setlang") {
        lang = setLang;
    }

    if (rc == "--scan") {
        if (file.exists(QDir::homePath() + "/.clamav-gui/settings.ini") == true) {
            setupFileHandler setupFile(QDir::homePath() + "/.clamav-gui/settings.ini");
            QStringList selectedOptions = setupFile.getKeywords("SelectedOptions");
            QStringList directoryOptions = setupFile.getKeywords("Directories");
            QStringList scanLimitations = setupFile.getKeywords("ScanLimitations");
            QString option;
            QString checked;
            QString value;

            for (int i = 0; i < selectedOptions.count(); i++){
                parameters << selectedOptions.at(i).left(selectedOptions.indexOf("|")).replace("<equal>","=");
            }

            // Directory Options
            for (int i = 0; i < directoryOptions.count(); i++){
                option = directoryOptions.at(i);
                value = setupFile.getSectionValue("Directories",option);
                checked = value.left(value.indexOf("|"));
                value = value.mid(value.indexOf("|") + 1);
                if ((checked == "checked") && (value != "")) {
                    if (option == "LoadSupportedDBFiles") parameters << "--database=" + value;
                    if (option == "ScanReportToFile") {
                        parameters << "--log=" + value;
                        QFile file(value);
                        if (file.open(QIODevice::ReadWrite|QIODevice::Append|QIODevice::Text)){
                            QTextStream stream(&file);
                            stream << "\n<Scanning startet> " << QDateTime::currentDateTime().toString("yyyy/M/d - hh:mm");
                            file.close();
                        }
                    }
                    if (option == "TmpFile") parameters << "--tempdir=" + value;
                    if (option == "MoveInfectedFiles") parameters << "--move=" + value;
                    if (option == "CopyInfectedFiles") parameters << "--copy=" + value;
                    if (option == "SCanFileFromFiles") parameters << "--file-list=" + value;
                    if (option == "FollowDirectorySymLinks") parameters << "--follow-dir-symlinks=" + value;
                    if (option == "FollowFileSymLinks") parameters << "--follow-file-symlinks=" + value;
                }
            }

            // Scan Limitations
            QStringList SLKeywords;
            QStringList SLSwitches;
            SLKeywords << "Files larger than this will be skipped and assumed clean" << "The maximum amount of data to scan for each container file";
            SLKeywords << "The maximum number of files to scan for each container file" << "Maximum archive recursion level for container file";
            SLKeywords << "Maximum directory recursion level" << "Maximum size file to check for embedded PE" << "Maximum size of HTML file to normalize";
            SLKeywords << "Maximum size of normalized HTML file to scan" << "Maximum size of script file to normalize" << "Maximum size zip to type reanalyze";
            SLKeywords << "Maximum number of partitions in disk image to be scanned" << "Maximum number of icons in PE file to be scanned";
            SLKeywords << "Number of seconds to wait for waiting a response back from the stats server" << "Bytecode timeout in milliseconds";
            SLKeywords << "Collect and print execution statistics" << "Structured SSN Format" << "Structured SSN Count" << "Structured CC Count" << "Structured CC Mode";
            SLKeywords << "Max Scan-Time" << "Max recursion to HWP3 parsing function" << "Max calls to PCRE match function" << "Max recursion calls to the PCRE match function";
            SLKeywords << "Max PCRE file size" << "Database outdated if older than x days";
            SLSwitches << "--max-filesize=" << "--max-scansize=" << "--max-files=" << "--max-recursion=" << "--max-dir-recursion=";
            SLSwitches << "--max-embeddedpe=" << "--max-htmlnormalize=" << "--max-htmlnotags=" << "--max-scriptnormalize=" << "--max-ziptypercg=";
            SLSwitches << "--max-partitions=" << "--max-iconspe=" << "--stats-timeout=" << "--bytecode-timeout=" << "--statistics=";
            SLSwitches << "--structured-ssn-format=" << "--structured-ssn-count=" << "--structured-cc-count=" << "--structured-cc-mode=" << "--max-scantime=";
            SLSwitches << "--max-rechwp3=" << "--pcre-match-limit=" << "--pcre-recmatch-limit=" << "--pcre-max-filesize=" << "--fail-if-cvd-older-than=";

            for (int i = 0; i < scanLimitations.count(); i++){
                option = scanLimitations.at(i);
                value = setupFile.getSectionValue("ScanLimitations",option);
                checked = value.left(value.indexOf("|"));
                value = value.mid(value.indexOf("|") + 1);
                if (checked == "checked"){
                    for (int i = 0; i < SLKeywords.length(); i++) {
                        if (option == SLKeywords.at(i)){
                            parameters << SLSwitches.at(i) + value;
                        }
                    }
                }
            }

            // REGEXP and Include Exclude Options
            value = setupFile.getSectionValue("REGEXP_and_IncludeExclude","DontScanFileNamesMatchingRegExp");
            checked = value.left(value.indexOf("|"));
            value = value.mid(value.indexOf("|") + 1);
            if (checked == "checked") parameters << "--exclude=" + value;

            value = setupFile.getSectionValue("REGEXP_and_IncludeExclude","DontScanDirectoriesMatchingRegExp");
            checked = value.left(value.indexOf("|"));
            value = value.mid(value.indexOf("|") + 1);
            if (checked == "checked") parameters << "--exclude-dir=" + value;

            value = setupFile.getSectionValue("REGEXP_and_IncludeExclude","OnlyScanFileNamesMatchingRegExp");
            checked = value.left(value.indexOf("|"));
            value = value.mid(value.indexOf("|") + 1);
            if (checked == "checked") parameters << "--include=" + value;

            value = setupFile.getSectionValue("REGEXP_and_IncludeExclude","OnlyScanDirectoriesMatchingRegExp");
            checked = value.left(value.indexOf("|"));
            value = value.mid(value.indexOf("|") + 1);
            if (checked == "checked") parameters << "--include-dir=" + value;

            if (setupFile.getSectionBoolValue("REGEXP_and_IncludeExclude","EnablePUAOptions") == true){
                QStringList keywords;
                QStringList switches;
                keywords << "LoadPUAPacked" << "LoadPUAPWTool" << "LoadPUANetTool" << "LoadPUAP2P" << "LoadPUAIRC" << "LoadPUARAT" << "LoadPUANetToolSpy";
                keywords << "LoadPUAServer" << "LoadPUAScript" << "LoadPUAAndr" << "LoadPUAJava" << "LoadPUAOsx" << "LoadPUATool" << "LoadPUAUnix" << "LoadPUAWin";
                switches << "--include-pua=Packed" << "--include-pua=PWTool" << "--include-pua=NetTool" << "--include-pua=P2P" << "--include-pua=IRC" << "--include-pua=RAT";
                switches << "--include-pua=NetToolSpy" << "--include-pua=Server" << "--include-pua=Script" << "--include-pua=Andr" << "--include-pua=Java";
                switches << "--include-pua=Osx" << "--include-pua=Tool" << "--include-pua=Unix" << "--include-pua=Win";
                for (int i = 0; i < keywords.length(); i++) {
                    if (setupFile.getSectionBoolValue("REGEXP_and_IncludeExclude",keywords.at(i)) == true) parameters << switches.at(i);
                }
            }
        }

        parameters << "-r";

        for (int i = 2; i < argc; i++){
            parameters << (QString)argv[i];
        }

        scheduleScanObject * scanObject = new scheduleScanObject(0,"Direct Scan",parameters);

        scanObject->setWindowTitle("Direct Scan-Job");
        scanObject->setWindowIcon(QIcon(":/icons/icons/media.png"));
        scanObject->setModal(true);
        scanObject->exec();
        delete scanObject;
    } else {
        if (rc != "--force"){
            if( !server.listen( QHostAddress::LocalHost, PORT_NUM ) ) {
                qDebug() << "Application already running!";
                exit(0);
            }
        }

        QString filename = "clamav-gui-" + lang + ".qm";
        if (QFile::exists("/usr/share/clamav-gui/" + filename)){
            translatorLoaded = translator1.load(filename,"/usr/share/clamav-gui");
            if (translatorLoaded == true) a.installTranslator(&translator1);

            filename = "clamav-" + lang + ".qm";
            if (QFile::exists("/usr/share/clamav-gui/" + filename)){
                translatorLoaded = translator2.load(filename,"/usr/share/clamav-gui");
                if (translatorLoaded == true) a.installTranslator(&translator2);
            }
        }

        clamav_gui w;
        w.show();

        return a.exec();
    }
}
