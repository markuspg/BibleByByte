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

#ifndef ABSTRACTSTORAGEBACKEND_H
#define ABSTRACTSTORAGEBACKEND_H

#include "abstractdatatype.h"
#include "storagecache.h"

#include <QException>
#include <QObject>

class IOException : public QException
{
    IOException* clone() const override;
    void raise() const override;
};

class AbstractStorageBackend : public QObject
{
    Q_OBJECT

public:
    explicit AbstractStorageBackend(QObject *const argParent = nullptr);

public slots:
    void MoveDataOneLevelDown(AbstractDataTypeSharedPtr argData);
    void MoveDataOneLevelUp(AbstractDataTypeSharedPtr argData);
    virtual void RetrieveRandomData() = 0;
    void SaveData(const AbstractDataTypeSharedPtr &argData);

signals:
    void DataMovingFailed();
    void DataRetrievalFailed();
    void DataRetrievalSucceeded(AbstractDataTypeSharedPtr argData);
    void DataSavingFailed();
    void DataSavingSucceeded();

protected:
    struct MoveResult {
        constexpr MoveResult(bool argErrorHappened,
                             bool argMoveHappened,
                             std::optional<ll::Level> &&argNewLevel,
                             std::optional<ll::Level> &&argPrevLevel) noexcept :
            errorOccurred{argErrorHappened},
            moveHappened{argMoveHappened},
            newLevel{std::move(argNewLevel)},
            prevLevel{std::move(argPrevLevel)}
        {}

        const bool errorOccurred = true;
        const bool moveHappened = false;
        const std::optional<ll::Level> newLevel;
        const std::optional<ll::Level> prevLevel;
    };

    /*!
     * \brief MoveData moves the data item a category up or down
     * \param[in] argData The data item which shall be moved
     * \param[in] argMoveLevelUp True, if the data item shall be moved up, false otherwise
     * \return A MoveResult instance signalling the function's taken actions
     */
    virtual MoveResult MoveData(const AbstractDataTypeSharedPtr &argData,
                                bool argMoveLevelUp) = 0;
    virtual bool SaveDataInternally(const AbstractDataTypeSharedPtr &argData) = 0;
    virtual bool UpdateCache() = 0;

    StorageCache cache;

private:
    //! this shall ensure that the first inserted item is immediately send to
    //! the check widget (otherwise it will first be filled on next app restart)
    bool noItemSavedYet = true;
};

#endif // ABSTRACTSTORAGEBACKEND_H
