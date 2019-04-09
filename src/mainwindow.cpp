#include "configurationhandler.h"
#include "filestoragebackend.h"
#include "mainwindow.h"
#include "sqlitestoragebackend.h"
#include "ui_mainwindow.h"
#include "modules/bibleVerse/versechecker.h"
#include "modules/bibleVerse/verseentry.h"

#include <QDebug>

#include <memory>

MainWindow::MainWindow(QWidget *const argParent) :
    QMainWindow{argParent},
    configHndlr{new ConfigurationHandler},
    storageBackend{configHndlr->GetConfigValue(
                       ConfigurationHandler::ECV::STORAGE_BACKEND) == "file"
        ? reinterpret_cast<AbstractStorageBackend*>(new FileStorageBackend)
        : reinterpret_cast<AbstractStorageBackend*>(new SqliteStorageBackend)},
    ui{new Ui::MainWindow}
{
    configHndlr->setParent(this);
    storageBackend->setParent(this);

    ui->setupUi(this);
    const auto tmpChecker = new VerseChecker{this};
    auto tmpLayoutItem = ui->VLCheck->replaceWidget(ui->WCheck, tmpChecker);
    if (tmpLayoutItem != nullptr) {
        tmpLayoutItem->widget()->deleteLater();
        delete tmpLayoutItem;
        tmpLayoutItem = nullptr;
    } else {
        qWarning() << "Could not replace WCheck";
    }
    tmpChecker->show();
    const auto tmpEntry = new VerseEntry{this};
    connect(tmpEntry, &AbstractDataEntry::Req_DataSaving,
            storageBackend, &AbstractStorageBackend::SaveData);
    connect(storageBackend, &AbstractStorageBackend::DataSavingFailed,
            tmpEntry, &AbstractDataEntry::OnDataSavingFailed);
    connect(storageBackend, &AbstractStorageBackend::DataSavingSucceeded,
            tmpEntry, &AbstractDataEntry::OnDataSavingSucceeded);
    tmpLayoutItem = ui->VLEntry->replaceWidget(ui->WEntry, tmpEntry);
    if (tmpLayoutItem != nullptr) {
        tmpLayoutItem->widget()->deleteLater();
        delete tmpLayoutItem;
        tmpLayoutItem = nullptr;
    } else {
        qWarning() << "Could not replace WEntry";
    }
    tmpEntry->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
