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

#include "ui_versecheckwdgt.h"
#include "verse.h"
#include "versecheckwdgt.h"

#include <QDebug>

VerseCheckWdgt::VerseCheckWdgt(QWidget *const argParent) :
    AbstractCheckWdgt{argParent},
    ui{new Ui::VerseCheckWdgt}
{
    ui->setupUi(this);
    ui->PTEVerseText->hide();
}

VerseCheckWdgt::~VerseCheckWdgt()
{
    delete ui;
}

void VerseCheckWdgt::SetDataToCheckInternal(
        const AbstractDataTypeSharedPtr &argData)
{
    const auto verseData = std::dynamic_pointer_cast<Verse>(argData);
    if (!verseData) {
        qWarning() << "Data of wrong type passed to VerseCheckWdgt";
        return;
    }
    ui->LEBook->setText(verseData->GetBook());
    ui->LEChapterNo->setText(QString::number(verseData->GetChapterNo()));
    ui->LEVerseNo->setText(QString::number(verseData->GetVerseNo()));
    ui->PTEVerseText->setPlainText(verseData->GetText());
}

void VerseCheckWdgt::ShowCheckedDataWdgt(const bool argDisplayData)
{
    if (argDisplayData == true) {
        ui->PTEVerseText->show();
    } else {
        ui->PTEVerseText->hide();
    }
}

void VerseCheckWdgt::ShowData()
{
    ShowCheckedDataWdgt(true);
}
