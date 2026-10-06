#include "clamav_gui.h"
#include <QTranslator>
#include <QApplication>
#include <QtNetwork/QTcpServer>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include "schedulescanobject.h"
#include "setupfilehandler.h"
#include "sharedvars.cpp"
#include "toolbox.h"

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
    bool showMainWindow = false;
    bool translatorLoaded = false;

    QApplication a(argc, argv);
    lang = QLocale::system().name();

    if (argc > 1) rc=(QString)argv[1];
    if (argc > 2) setLang = (QString) argv[2];

    if (rc == "--language")
        printf("\nDesktop Language Settings: %s\n",lang.toStdString().c_str());

    QFile file;
    if (file.exists(QDir::homePath() + "/.clamav-gui/settings.ini") == true)
    {
        setupFileHandler setupFile(QDir::homePath() + "/.clamav-gui/settings.ini");
        if (setupFile.keywordExists("Setup","language") == true)
            lang = setupFile.getSectionValue("Setup","language").mid(1,5);
        else
            lang = "en_GB";
    }

    if (rc == "--setlang")
        lang = setLang;

    if (rc == "--scan")
    {
        if (file.exists(QDir::homePath() + "/.clamav-gui/settings.ini") == true)
        {
            setupFileHandler setupFile(QDir::homePath() + "/.clamav-gui/settings.ini");

            assembleScanParameters(&setupFile,&parameters);
        }

        parameters << "-r";

        for (int i = 2; i < argc; i++)
            parameters << (QString)argv[i];

        scheduleScanObject * scanObject = new scheduleScanObject(0,"Direct Scan",parameters);

        scanObject->setWindowTitle("Direct Scan-Job");
        scanObject->setWindowIcon(QIcon(":/icons/icons/media.png"));
        scanObject->setModal(true);
        scanObject->exec();
        delete scanObject;
    }
    else {
        if (rc != "--force")
        {
            if( !server.listen( QHostAddress::LocalHost, PORT_NUM ) )
            {
                qDebug() << "Application already running!";
                exit(0);
            }
        }

        QString filename = "clamav-gui-" + lang + ".qm";
        QString translationPath;
        if (isRunninginFlatPak())
            translationPath = "/app/usr/share/clamav-gui/";
        else
            translationPath = QCoreApplication::applicationDirPath() + "/../share/clamav-gui/";
        if (QFile::exists(translationPath + filename))
        {
            translatorLoaded = translator1.load(filename,translationPath);
            if (translatorLoaded == true) a.installTranslator(&translator1);

            filename = "clamav-" + lang + ".qm";
            if (QFile::exists(translationPath + filename))
            {
                translatorLoaded = translator2.load(filename,translationPath);
                if (translatorLoaded == true) a.installTranslator(&translator2);
            }
        }

        if (QFileInfo::exists(QDir::homePath() + "/.clamav-gui/settings.ini") == true)
        {
            setupFileHandler * setupFile = new setupFileHandler(QDir::homePath() + "/.clamav-gui/settings.ini");
            if (setupFile->getSectionValue("Setup","WindowState") == "maximized")
            {
                showMainWindow = true;
                setupFile->setSectionValue("Settings", "ShowHideMainWindow", true);
            }
            else
                setupFile->setSectionValue("Settings", "ShowHideMainWindow", false);
            delete setupFile;
        }

        clamav_gui w;
        if (showMainWindow == true)
            w.show();

        return a.exec();
    }
}
