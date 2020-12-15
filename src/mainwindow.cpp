/*
 * Copyright 2019-2020 Markus Prasser
 *
 * This file is part of BibleByByte.
 *
 *  BibleByByte is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  BibleByByte is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with BibleByByte.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "backend.h"
#include "configurationhandler.h"
#include "filestoragebackend.h"
#include "modules/bibleVerse/versechecker.h"
#include "modules/bibleVerse/verseentry.h"
#include "modules/songVerse/songverseentry.h"
#include "sqlitestoragebackend.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <memory>

MainWindow::MainWindow(QWidget* const argParent) :
    QMainWindow{argParent}, backend{new Backend}, ui{new Ui::MainWindow}
{
    backend->setParent(this);

    ui->setupUi(this);
    const auto tmpChecker = new VerseChecker{this};
    connect(tmpChecker, &AbstractDataChecker::DataVerificationFailed,
            backend->GetStorageBcknd(),
            &AbstractStorageBackend::MoveDataOneLevelDown);
    connect(tmpChecker, &AbstractDataChecker::DataVerificationSucceeded,
            backend->GetStorageBcknd(),
            &AbstractStorageBackend::MoveDataOneLevelUp);
    connect(backend->GetStorageBcknd(),
            &AbstractStorageBackend::DataMovingFailed, tmpChecker,
            &AbstractDataChecker::DataLevelUpdateFailed);
    connect(backend->GetStorageBcknd(),
            &AbstractStorageBackend::DataRetrievalSucceeded, tmpChecker,
            &AbstractDataChecker::SetDataToCheck);
    auto tmpLayoutItem = ui->VLCheck->replaceWidget(ui->WCheck, tmpChecker);
    if (tmpLayoutItem != nullptr) {
        tmpLayoutItem->widget()->deleteLater();
        delete tmpLayoutItem;
        tmpLayoutItem = nullptr;
    } else {
        qWarning() << "Could not replace WCheck";
    }
    tmpChecker->show();

    const auto& modNames{GetModuleNames()};
    for (const auto& modName : modNames) {
        ui->CBModuleChooser->addItem(modName.second,
                                     QVariant::fromValue(modName.first));
    }
    connect(
        ui->CBModuleChooser,
        static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, &MainWindow::OnModChanged);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::Initialize()
{
    ui->CBModuleChooser->currentIndexChanged(0);

    backend->Initialize();
}

void MainWindow::OnModChanged(const int argCurrentIdx)
{
    Q_UNUSED(argCurrentIdx)

    const auto newModVar{ui->CBModuleChooser->currentData()};
    if (newModVar.canConvert<EModIds>() == false) {
        qWarning() << "Invalid data in CBModuleChooser";
        return;
    }

    const auto newMod{newModVar.value<EModIds>()};
    AbstractDataEntry* tmpEntry = nullptr;
    if (newMod == EModIds::BibleVerse) {
        tmpEntry = new VerseEntry{this};
    } else if (newMod == EModIds::SongVerse) {
        tmpEntry = new SongVerseEntry{this};
    } else {
        qWarning() << "Invalid new module for entry chosen"
                   << static_cast<std::underlying_type<EModIds>::type>(newMod);
        return;
    }

    connect(tmpEntry, &AbstractDataEntry::Req_DataSaving,
            backend->GetStorageBcknd(), &AbstractStorageBackend::SaveData);
    connect(backend->GetStorageBcknd(),
            &AbstractStorageBackend::DataSavingFailed, tmpEntry,
            &AbstractDataEntry::OnDataSavingFailed);
    connect(backend->GetStorageBcknd(),
            &AbstractStorageBackend::DataSavingSucceeded, tmpEntry,
            &AbstractDataEntry::OnDataSavingSucceeded);
    auto tmpLayoutItem = ui->VLEntries->replaceWidget(ui->WEntry, tmpEntry);
    if (tmpLayoutItem != nullptr) {
        ui->WEntry = tmpEntry;
        tmpLayoutItem->widget()->deleteLater();
        delete tmpLayoutItem;
        tmpLayoutItem = nullptr;
    } else {
        qWarning() << "Could not replace WBibleVerseEntry";
    }
}
