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

#include "songverseentrywdgt.h"
#include "ui_songverseentrywdgt.h"

SongVerseEntryWdgt::SongVerseEntryWdgt(QWidget *const argParent) :
    AbstractEntryWdgt{argParent},
    ui{new Ui::SongVerseEntryWdgt}
{
    ui->setupUi(this);

    // TODO(markuspg) fill CBSongName with already known songs

    connect(ui->PTEVerseText, &QPlainTextEdit::textChanged,
            this, &SongVerseEntryWdgt::OnDataChanged);
}

SongVerseEntryWdgt::~SongVerseEntryWdgt()
{
    delete ui;
}

void SongVerseEntryWdgt::ClearAndPrepare()
{
    ui->PTEVerseText->setPlainText("");
    ui->SBSongVerseNo->setValue(ui->SBSongVerseNo->value() + 1);
}

AbstractDataTypeSharedPtr SongVerseEntryWdgt::GetDataPr()
{
    if (dataHasBeenCompleted == false) {
        return AbstractDataTypeSharedPtr{};
    }
    return AbstractDataTypeSharedPtr{
        new SongVerse{ui->CBSongName->currentText(),
                      static_cast<unsigned short>(ui->SBSongVerseNo->value()),
                      ui->PTEVerseText->toPlainText()}};
}

void SongVerseEntryWdgt::OnDataChanged()
{
    if (ui->PTEVerseText->toPlainText().size() != 0) {
        dataHasBeenCompleted = true;
        emit DataComplete();
    }
}
