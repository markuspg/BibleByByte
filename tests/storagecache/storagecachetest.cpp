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

#include <QtTest>

#include "storagecache.h"

#include <random>

class StorageCacheTest : public QObject
{
    Q_OBJECT

private slots:
    void InitAndTotalTest();
    void ItemInsertion();
    void ItemMoveTest();
    void RandomDrawTest();

};

void StorageCacheTest::InitAndTotalTest()
{
    // check if exception is thrown on invalid module type
    {
    StorageCache cache;
    QVERIFY_EXCEPTION_THROWN(cache.SetCategoryQty(EModIds::MOD_QTY, 0, 0),
                             std::out_of_range);
    }

    // check if the item quantities are correctly computed with static values
    {
    StorageCache cache;
    cache.SetCategoryQty(EModIds::BibleVerse, 7, 25237);
    cache.SetCategoryQty(EModIds::BibleVerse, 2, 4437);
    cache.SetCategoryQty(EModIds::SongVerse, 0, 29120);
    cache.SetCategoryQty(EModIds::BibleVerse, 5, 25591);
    cache.SetCategoryQty(EModIds::SongVerse, 1, 23423);
    cache.SetCategoryQty(EModIds::SongVerse, 7, 30146);
    cache.SetCategoryQty(EModIds::SongVerse, 2, 3814);
    cache.SetCategoryQty(EModIds::BibleVerse, 1, 19727);
    cache.SetCategoryQty(EModIds::SongVerse, 5, 2154);
    cache.SetCategoryQty(EModIds::BibleVerse, 6, 21442);
    cache.SetCategoryQty(EModIds::SongVerse, 4, 3485);
    cache.SetCategoryQty(EModIds::BibleVerse, 3, 6672);
    cache.SetCategoryQty(EModIds::SongVerse, 6, 13281);
    cache.SetCategoryQty(EModIds::SongVerse, 3, 22999);
    cache.SetCategoryQty(EModIds::BibleVerse, 0, 12793);
    cache.SetCategoryQty(EModIds::BibleVerse, 4, 1397);
    QCOMPARE(cache.GetTotalStoredItemsQty(), 245718ul);
    }

    // check if the item quantites are correctly computed with random values
    {
    std::mt19937_64 eng{std::random_device{"/dev/urandom"}()};
    std::uniform_int_distribution<ll::ItemQty>
        dist{0, std::numeric_limits<unsigned int>::max()};
    StorageCache cache;
    auto totalItemQty = 0ul;
    for (ll::Level i = 0; i < ll::levelQty; ++i) {
        const auto newBibleVerseQty = dist(eng);
        cache.SetCategoryQty(EModIds::BibleVerse, i, newBibleVerseQty);
        totalItemQty += newBibleVerseQty;
        const auto newSongVerseQty = dist(eng);
        cache.SetCategoryQty(EModIds::SongVerse, i, newSongVerseQty);
        totalItemQty += newSongVerseQty;
    }
    QCOMPARE(cache.GetTotalStoredItemsQty(), totalItemQty);
    }
}

void StorageCacheTest::ItemInsertion()
{
    // check if inserted items are correctly reflected by the item counts
    {
    StorageCache cache;
    // a few plain insertions
    cache.InsertNewItem(EModIds::BibleVerse);
    cache.InsertNewItem(EModIds::BibleVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    cache.InsertNewItem(EModIds::BibleVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    cache.InsertNewItem(EModIds::BibleVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    cache.InsertNewItem(EModIds::BibleVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 0), 5ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 0), 7ul);

    // a few insertions after previous moves
    cache.ItemGotMoved(EModIds::BibleVerse, 0, 1);
    cache.ItemGotMoved(EModIds::BibleVerse, 0, 2);
    cache.ItemGotMoved(EModIds::SongVerse, 0, 4);
    cache.ItemGotMoved(EModIds::BibleVerse, 0, 5);
    cache.ItemGotMoved(EModIds::SongVerse, 0, 2);
    cache.InsertNewItem(EModIds::BibleVerse);
    cache.InsertNewItem(EModIds::BibleVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    cache.InsertNewItem(EModIds::BibleVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    cache.InsertNewItem(EModIds::SongVerse);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 0), 5ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 0), 8ul);
    }
}

void StorageCacheTest::ItemMoveTest()
{
    // check if exception is thrown if an item should be moved from an empty level
    {
    StorageCache cache;
    // initialize with a few random values
    cache.SetCategoryQty(EModIds::BibleVerse, 0, 17);
    cache.SetCategoryQty(EModIds::SongVerse, 3, 17);
    cache.SetCategoryQty(EModIds::BibleVerse, 5, 2);
    cache.SetCategoryQty(EModIds::BibleVerse, 6, 28);

    // move items out of level 5, one item moves a level down ...
    cache.ItemGotMoved(EModIds::BibleVerse, 5, 4);
    // ... another item moves a level up ...
    cache.ItemGotMoved(EModIds::BibleVerse, 5, 6);
    // ... and then an exception is thrown since all items are gone
    QVERIFY_EXCEPTION_THROWN(cache.ItemGotMoved(EModIds::BibleVerse, 5, 3),
                             std::exception);
    }

    // check the item quantities after a few moves
    {
    StorageCache cache;
    // initialize with a few random values
    cache.SetCategoryQty(EModIds::BibleVerse, 5, 231);
    cache.SetCategoryQty(EModIds::SongVerse, 2, 42);
    cache.SetCategoryQty(EModIds::BibleVerse, 3, 993);
    cache.SetCategoryQty(EModIds::BibleVerse, 2, 32423);
    cache.SetCategoryQty(EModIds::BibleVerse, 7, 192);

    // conduct a few moves
    cache.ItemGotMoved(EModIds::SongVerse, 2, 1);
    cache.ItemGotMoved(EModIds::BibleVerse, 5, 0);
    cache.ItemGotMoved(EModIds::BibleVerse, 7, 0);
    cache.ItemGotMoved(EModIds::BibleVerse, 3, 4);

    // check if the values got moved properly
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 0), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 1), 1ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 2), 41ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 3), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 4), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 5), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 6), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 7), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 0), 2ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 1), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 2), 32423ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 3), 992ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 4), 1ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 5), 230ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 6), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 7), 191ul);

    // check if the data is still valid and unchanged after a thrown exception
    QVERIFY_EXCEPTION_THROWN(cache.ItemGotMoved(EModIds::MOD_QTY, 7, 1),
                             std::out_of_range);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 1), 0ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 7), 191ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 1), 1ul);
    QCOMPARE(cache.GetItemQty(EModIds::SongVerse, 7), 0ul);
    QVERIFY_EXCEPTION_THROWN(cache.ItemGotMoved(EModIds::BibleVerse, 8, 3),
                             std::out_of_range);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 3), 992ul);
    QVERIFY_EXCEPTION_THROWN(cache.ItemGotMoved(EModIds::BibleVerse, 2, 8),
                             std::out_of_range);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 3), 992ul);
    cache.ItemGotMoved(EModIds::BibleVerse, 2, 3);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 2), 32422ul);
    QCOMPARE(cache.GetItemQty(EModIds::BibleVerse, 3), 993ul);
    }
}

void StorageCacheTest::RandomDrawTest()
{
    {
    // create and insert certain random values into cache
    constexpr ll::ItemQty bibleVerseItemFactor = 5;
    StorageCache cache;
    constexpr StorageCache::LevelQtyArr lvlIniVals{
            19242, 11923, 4192, 2129, 507, 402, 299, 100
    };
    for (ll::Level i = 0; i < ll::levelQty; ++i) {
        cache.SetCategoryQty(EModIds::BibleVerse, i, lvlIniVals.at(i)
                                                     * bibleVerseItemFactor);
        cache.SetCategoryQty(EModIds::SongVerse, i, lvlIniVals.at(i));
    }
    QCOMPARE(cache.GetTotalStoredItemsQty(), 232764ul);

    // draw random items and record frequencies
    using ResultsVec = std::vector<StorageCache::DrawResult>;
    ResultsVec results;
    constexpr ResultsVec::size_type iterationsQty = 1000000;
    results.reserve(iterationsQty);
    for (ResultsVec::size_type i = 0; i < iterationsQty; ++i) {
        results.emplace_back(std::move(*(cache.DoMonteCarloDraw().get())));
    }

    // verify probabilites while allowing 10% deviation
    const auto bibleVerseQty = std::count_if(results.cbegin(), results.cend(),
            [](const StorageCache::DrawResult &argRes)
                    { return argRes.mod == EModIds::BibleVerse; } );
    const auto songVerseQty = std::count_if(results.cbegin(), results.cend(),
            [](const StorageCache::DrawResult &argRes)
                    { return argRes.mod == EModIds::SongVerse; } );
    QVERIFY(((static_cast<ll::ItemQty>(songVerseQty) * bibleVerseItemFactor * 0.9)
             < bibleVerseQty)
            && ((static_cast<ll::ItemQty>(songVerseQty) * bibleVerseItemFactor * 1.1)
                > bibleVerseQty));
    }
}

QTEST_APPLESS_MAIN(StorageCacheTest)

#include "storagecachetest.moc"
