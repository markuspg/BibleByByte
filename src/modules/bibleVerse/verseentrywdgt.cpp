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

#include "verseentrywdgt.h"
#include "ui_verseentrywdgt.h"

VerseEntryWdgt::VerseEntryWdgt(QWidget* const argParent) :
    AbstractEntryWdgt{argParent}, ui{new Ui::VerseEntryWdgt}
{
    ui->setupUi(this);

    for (const auto& bookData : bookTitles) {
        QVariant tmpData;
        tmpData.setValue(&bookData);
        ui->CBBibleBook->addItem(tr(bookData.prettyTitle), tmpData);
    }

    connect(ui->PTEVerseText, &QPlainTextEdit::textChanged, this,
            &VerseEntryWdgt::OnDataChanged);
}

VerseEntryWdgt::~VerseEntryWdgt() { delete ui; }

void VerseEntryWdgt::ClearAndPrepare()
{
    ui->PTEVerseText->setPlainText("");
    ui->SBVerseNo->setValue(ui->SBVerseNo->value() + 1);
}

AbstractDataTypeSharedPtr VerseEntryWdgt::GetDataPr()
{
    if (dataHasBeenCompleted == false) {
        return AbstractDataTypeSharedPtr{};
    }
    return AbstractDataTypeSharedPtr{
        new Verse{ui->CBBibleBook->currentData().value<BookTitleInfoPtr>(),
                  static_cast<unsigned short>(ui->SBChapterNo->value()),
                  static_cast<unsigned short>(ui->SBVerseNo->value()),
                  ui->PTEVerseText->toPlainText(), 0}};
}

void VerseEntryWdgt::OnDataChanged()
{
    if (ui->PTEVerseText->toPlainText().size() != 0) {
        dataHasBeenCompleted = true;
        emit DataComplete();
    }
}
