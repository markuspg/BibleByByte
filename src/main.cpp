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

#ifdef QML_APP
#include <sailfishapp.h>
#endif
#ifdef WIDGETS_APP
#include <QApplication>
#endif // WIDGETS_APP
#include <QDebug>
#include <QDir>
#include <QFile>
#ifdef QML_APP
#include <QGuiApplication>
#include <QQuickView>
#endif // QML_APP
#include <QStandardPaths>
#ifdef QML_APP
#include <QtQml>
#endif // QML_APP
#ifdef WIDGETS_APP
#include <QTimer>
#endif // WIDGETS_APP

#include "abstractdatatype.h"
#ifdef WIDGETS_APP
#include "mainwindow.h"
#else
#include "backend.h"
#endif // WIDGETS_APP
#include "modules/bibleVerse/booktitles.h"

int main(int argc, char *argv[]) {
#ifdef WIDGETS_APP
    QApplication app{argc, argv};
    app.setApplicationName("BibleByByte");
#endif // WIDGETS_APP
#ifdef QML_APP
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
#endif // QML_APP

    qRegisterMetaType<AbstractDataTypeSharedPtr>();
    qRegisterMetaType<BookTitleInfoPtr>();

    QDir dataDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)};
    if (QFile::exists(dataDir.absolutePath()) == false) {
        if (dataDir.mkpath(dataDir.absolutePath()) == false) {
            qWarning() << "Failed to create data directory";
            return 1;
        }
    }

#ifdef QML_APP
    qmlRegisterType<Backend>("com.github.biblebybyte.backend", 1, 0, "Backend");

    view->setSource(SailfishApp::pathTo("qml/harbour-biblebybyte.qml"));
    view->show();

    return app->exec();
#endif // QML_APP
#ifdef WIDGETS_APP
    MainWindow mainWin;
    mainWin.show();

    QTimer::singleShot(0, &mainWin, &MainWindow::Initialize);

    return app.exec();
#endif // WIDGETS_APP
}
