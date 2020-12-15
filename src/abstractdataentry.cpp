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

#include "abstractdataentry.h"
#include "abstractentrywdgt.h"
#include "ui_abstractdataentry.h"

AbstractDataEntry::AbstractDataEntry(AbstractEntryWdgt* const argEntryWdgt,
                                     QWidget* const argParent) :
    QWidget{argParent}, entryWdgt{argEntryWdgt}, ui{new Ui::AbstractDataEntry}
{
    ui->setupUi(this);
    connect(ui->PBAdd, &QPushButton::clicked, this,
            &AbstractDataEntry::OnAddButtonClicked);

    entryWdgt->setParent(this);
    connect(entryWdgt, &AbstractEntryWdgt::DataComplete, this,
            &AbstractDataEntry::OnDataComplete);
    ui->VLAbstractDataEntry->insertWidget(0, entryWdgt);
}

AbstractDataEntry::~AbstractDataEntry() { delete ui; }

void AbstractDataEntry::OnAddButtonClicked()
{
    // disable the widget to prevent further save requests to be sent
    setEnabled(false);

    emit Req_DataSaving(entryWdgt->GetDataPr());
}

void AbstractDataEntry::OnDataComplete() { ui->PBAdd->setEnabled(true); }

void AbstractDataEntry::OnDataSavingFailed()
{
    // set the "Add" push button to false to signal failure to the user
    ui->PBAdd->setStyleSheet("background: red");

    // enable the button again to make another try to save possible
    setEnabled(true);
}

void AbstractDataEntry::OnDataSavingSucceeded()
{
    // reset the stylesheet to clear any previously signalled error conditions
    ui->PBAdd->setStyleSheet("");

    // clear the data entry widget and prepare entry of next data
    entryWdgt->ClearAndPrepare();

    // allow the user to send next request to save data
    setEnabled(true);

    // the "Add" push button shall be disabled until next data is available
    ui->PBAdd->setEnabled(false);
}
