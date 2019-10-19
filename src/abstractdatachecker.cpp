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

#include "abstractcheckwdgt.h"
#include "abstractdatachecker.h"
#include "ui_abstractdatachecker.h"

#include <QtDebug>

AbstractDataChecker::AbstractDataChecker(AbstractCheckWdgt *const argDisplayWdgt,
                                         QWidget *const argParent) :
    QWidget{argParent},
    displayWdgt{argDisplayWdgt},
    ui{new Ui::AbstractDataChecker}
{
    ui->setupUi(this);

    ui->VLAbstractDataChecker->insertWidget(0, displayWdgt);

    connect(ui->PBCorrect, &QPushButton::clicked,
            this, &AbstractDataChecker::OnPBCorrectClicked);
    connect(ui->PBWrong, &QPushButton::clicked,
            this, &AbstractDataChecker::OnPBWrongClicked);
}

AbstractDataChecker::~AbstractDataChecker()
{
    delete ui;
}

void AbstractDataChecker::DataLevelUpdateFailed()
{
    setStyleSheet("background: red");
    setEnabled(false);
}

void AbstractDataChecker::OnPBCorrectClicked()
{
    SetPBWrongState(EPBWrongState::SHOW);

    emit DataVerificationSucceeded(currentlyCheckedData);
}

void AbstractDataChecker::OnPBWrongClicked()
{
    if (pbWrongState == EPBWrongState::SHOW) {
        SetPBWrongState(EPBWrongState::WRONG);
    } else {
        SetPBWrongState(EPBWrongState::SHOW);

        emit DataVerificationFailed(currentlyCheckedData);
    }
}

void AbstractDataChecker::SetDataToCheck(const AbstractDataTypeSharedPtr &argData)
{
    currentlyCheckedData = argData;

    displayWdgt->SetDataToCheck(argData);

    ui->PBWrong->setEnabled(true);
}

void AbstractDataChecker::SetPBWrongState(const EPBWrongState argNewState)
{
    if (argNewState == EPBWrongState::WRONG) {
        ui->PBWrong->setText(tr("Wrong"));
        ui->PBCorrect->setEnabled(true);
        pbWrongState = argNewState;
        displayWdgt->ShowData();
    } else {
        ui->PBWrong->setText(tr("Show"));
        ui->PBCorrect->setEnabled(false);
        pbWrongState = argNewState;
    }
}
