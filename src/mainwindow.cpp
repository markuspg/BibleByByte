/*
 * Copyright 2019 Markus Prasser
 *
 * This file is part of LeitnerLearner.
 *
 *  LeitnerLearner is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  LeitnerLearner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with LeitnerLearner.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "configurationhandler.h"
#include "filestoragebackend.h"
#include "mainwindow.h"
#include "sqlitestoragebackend.h"
#include "ui_mainwindow.h"
#include "modules/bibleVerse/versechecker.h"
#include "modules/bibleVerse/verseentry.h"
#include "modules/songVerse/songverseentry.h"

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
    connect(tmpChecker, &AbstractDataChecker::DataVerificationFailed,
            storageBackend, &AbstractStorageBackend::MoveDataOneLevelDown);
    connect(tmpChecker, &AbstractDataChecker::DataVerificationSucceeded,
            storageBackend, &AbstractStorageBackend::MoveDataOneLevelUp);
    connect(storageBackend, &AbstractStorageBackend::DataMovingFailed,
            tmpChecker, &AbstractDataChecker::DataLevelUpdateFailed);
    connect(storageBackend, &AbstractStorageBackend::DataRetrievalSucceeded,
            tmpChecker, &AbstractDataChecker::SetDataToCheck);
    auto tmpLayoutItem = ui->VLCheck->replaceWidget(ui->WCheck, tmpChecker);
    if (tmpLayoutItem != nullptr) {
        tmpLayoutItem->widget()->deleteLater();
        delete tmpLayoutItem;
        tmpLayoutItem = nullptr;
    } else {
        qWarning() << "Could not replace WCheck";
    }
    tmpChecker->show();

    const auto tmpVerseEntry = new VerseEntry{this};
    connect(tmpVerseEntry, &AbstractDataEntry::Req_DataSaving,
            storageBackend, &AbstractStorageBackend::SaveData);
    connect(storageBackend, &AbstractStorageBackend::DataSavingFailed,
            tmpVerseEntry, &AbstractDataEntry::OnDataSavingFailed);
    connect(storageBackend, &AbstractStorageBackend::DataSavingSucceeded,
            tmpVerseEntry, &AbstractDataEntry::OnDataSavingSucceeded);
    tmpLayoutItem = ui->VLBibleVerseEntryTab->replaceWidget(ui->WBibleVerseEntry,
                                                            tmpVerseEntry);
    if (tmpLayoutItem != nullptr) {
        tmpLayoutItem->widget()->deleteLater();
        delete tmpLayoutItem;
        tmpLayoutItem = nullptr;
    } else {
        qWarning() << "Could not replace WBibleVerseEntry";
    }
    tmpVerseEntry->show();

    const auto tmpSongVerseEntry = new SongVerseEntry{this};
    connect(tmpSongVerseEntry, &AbstractDataEntry::Req_DataSaving,
            storageBackend, &AbstractStorageBackend::SaveData);
    connect(storageBackend, &AbstractStorageBackend::DataSavingFailed,
            tmpSongVerseEntry, &AbstractDataEntry::OnDataSavingFailed);
    connect(storageBackend, &AbstractStorageBackend::DataSavingSucceeded,
            tmpSongVerseEntry, &AbstractDataEntry::OnDataSavingSucceeded);
    tmpLayoutItem = ui->VLSongVerseEntryTab->replaceWidget(ui->WSongVerseEntry,
                                                           tmpSongVerseEntry);
    if (tmpLayoutItem != nullptr) {
        tmpLayoutItem->widget()->deleteLater();
        delete tmpLayoutItem;
        tmpLayoutItem = nullptr;
    } else {
        qWarning() << "Could not replace WBibleVerseEntry";
    }
    tmpSongVerseEntry->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Initialize()
{
    storageBackend->RetrieveRandomData();
}
