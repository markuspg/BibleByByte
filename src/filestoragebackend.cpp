/*
 * Copyright 2019 Markus Prasser
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

#include "filestoragebackend.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

FileStorageBackend::FileStorageBackend(QObject* const argParent) :
    AbstractStorageBackend{argParent}
{
    // prepare storage directories for all modules' data
    for (const std::pair<EModIds, const char*>& moduleData : GetModuleNames()) {
        // first create the modules' directories themselves
        const QString dataDirPath{
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
            + "/" + moduleData.second};
        QDir dataDir{dataDirPath};
        if (QFile::exists(dataDir.absolutePath()) == false) {
            if (dataDir.mkpath(dataDir.absolutePath()) == false) {
                qWarning()
                    << "Failed to create data directory for FileStorageBackend";
                throw IOException{};
            }
        }
        // then create the directories for the different learning levels
        for (ll::Level i = 0; i < ll::levelQty; ++i) {
            QDir catDir{dataDirPath + "/" + QString::number(i)};
            if (QFile::exists(catDir.absolutePath()) == false) {
                if (catDir.mkpath(catDir.absolutePath()) == false) {
                    qWarning() << "Failed to create category directories"
                                  " for FileStorageBackend";
                    throw IOException{};
                }
            }
        }
    }
    if (UpdateCache() == false) {
        qWarning() << "Failed to update FileStorageBackend cache";
        throw IOException{};
    }
}

AbstractStorageBackend::MoveResult
    FileStorageBackend::MoveData(const AbstractDataTypeSharedPtr& argData,
                                 const bool argMoveLevelUp)
{
    bool errorOccurred = false;
    bool moveHappened = false;
    ll::Level newLevel = std::numeric_limits<ll::Level>::max();
    ll::Level prevLevel = std::numeric_limits<ll::Level>::max();

    const QString dataDirPath{
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/"
        + GetModuleNameById(argData->GetType())};

    // check in which level the item is contained
    for (ll::Level i = 0; i < ll::levelQty; ++i) {
        if (QFile::exists(dataDirPath + "/" + QString::number(i) + "/"
                          + argData->GetIdentifier() + ".txt")
            == true) {
            // throw, if the item exists in more than one category
            if (prevLevel != std::numeric_limits<ll::Level>::max()) {
                qWarning() << "No item may exist in more than one level";
                throw IOException{};
                // don't break, the iteration shall include all levels
            }
            prevLevel = i;
        }
    }
    if (std::numeric_limits<ll::Level>::max() == prevLevel) {
        qWarning() << "Every item has to be contained in exactly one level";
        throw IOException{};
    }

    // don't move if the data item cannot be moved any further in its direction
    if (((argMoveLevelUp == true) && (prevLevel == ll::levelQty - 1))
        || ((argMoveLevelUp == false) && (prevLevel == 0))) {
        return MoveResult{errorOccurred, moveHappened, newLevel, prevLevel};
    }

    // compute the old and new paths ...
    const QString currFilePath{dataDirPath + "/" + QString::number(prevLevel)
                               + "/" + argData->GetIdentifier() + ".txt"};
    const ll::Level newLvl = argMoveLevelUp ? prevLevel + 1u : prevLevel - 1u;
    const QString newFilePath{dataDirPath + "/" + QString::number(newLvl) + "/"
                              + argData->GetIdentifier() + ".txt"};

    // ... and finally attempt to move the file
    if (QFile::rename(currFilePath, newFilePath) == true) {
        moveHappened = true;
        newLevel = static_cast<ll::Level>(newLvl);
    } else {
        qWarning() << "Failed to move" << currFilePath << "to" << newFilePath;
        errorOccurred = true;
    }

    return MoveResult{errorOccurred, moveHappened, newLevel, prevLevel};
}

void FileStorageBackend::RetrieveRandomData()
{
    // chose and locate a file
    const std::unique_ptr<StorageCache::DrawResult> drawRes{
        cache.DoMonteCarloDraw()};
    if (!drawRes) {
        return;
    }
    const QString modName{GetModuleNameById(drawRes->mod)};
    QDir dataDir{
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
        + QString{"/%1/%2"}.arg(modName).arg(QString::number(drawRes->lvlIdx))};
    QFileInfo dataDirInfo(dataDir.absolutePath());
    if ((dataDirInfo.exists() == false) || (dataDirInfo.isDir() == false)) {
        qWarning() << "Expected data directory" << dataDir.absolutePath()
                   << "does not exist";
        emit DataRetrievalFailed();
        return;
    }
    const QStringList files{
        dataDir.entryList(QStringList{"*.txt"}, QDir::Files, QDir::Name)};

    // open and read the file
    const QString dataFileName{files.at(static_cast<int>(drawRes->itemIdx))};
    QFile dataFile{dataDir.absolutePath() + "/" + dataFileName};
    if (dataFile.exists() == false) {
        qWarning() << "Data file" << dataFile.fileName() << "does not exist";
        emit DataRetrievalFailed();
        return;
    }
    if (dataFile.open(QIODevice::ReadOnly) == false) {
        qWarning() << "Failed to open data file" << dataFile.fileName();
        emit DataRetrievalFailed();
        return;
    }
    const qint64 dataSize{dataFile.size()};
    QByteArray dataBuf(static_cast<int>(dataSize), '\0');
    if (dataFile.read(dataBuf.data(), dataSize) != dataSize) {
        qWarning() << "Failed to read data from" << dataFile.fileName();
        emit DataRetrievalFailed();
        return;
    }
    dataFile.close();

    // parse the file and emit the result
    const AbstractDataTypeSharedPtr res{AbstractDataType::ParseFromData(
        drawRes->mod, drawRes->lvlIdx,
        QString{dataFileName}.replace(".txt", ""), dataBuf)};

    if (res) {
        emit DataRetrievalSucceeded(res);
        return;
    }
    qWarning() << "Could not parse data";
    emit DataRetrievalFailed();
}

bool FileStorageBackend::SaveDataInternally(
    const AbstractDataTypeSharedPtr& argData)
{
    if (!argData) {
        qWarning() << "Empty data got passed for saving";
        return false;
    }
    QFile outFile{
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
        + QString{"/%1/0/"}.arg(GetModuleNameById(argData->GetType()))
        + argData->GetIdentifier() + ".txt"};
    if (outFile.open(QIODevice::Text | QIODevice::WriteOnly) == false) {
        return false;
    }
    const QByteArray outDataBuf{argData->GetData()};
    if (outFile.write(outDataBuf) == outDataBuf.size()) {
        return true;
    }
    return false;
}

bool FileStorageBackend::UpdateCache()
{
    for (const std::pair<EModIds, const char*>& modInfo : GetModuleNames()) {
        for (ll::Level i = 0; i < ll::levelQty; ++i) {
            const QString dirPath{
                QStandardPaths::writableLocation(
                    QStandardPaths::AppDataLocation)
                + QString{"/%1/"}.arg(GetModuleNameById(modInfo.first))
                + QString::number(i)};
            if (QFile::exists(dirPath) == false) {
                return false;
            }
            QDir dirInfo{dirPath};
            cache.SetCategoryQty(
                modInfo.first, i,
                static_cast<ll::ItemQty>(
                    dirInfo.entryList(QStringList{"*.txt"}, QDir::Files)
                        .size()));
        }
    }

    return true;
}
