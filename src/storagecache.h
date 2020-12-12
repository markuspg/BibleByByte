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

#ifndef BBB_STORAGECACHE_H
#define BBB_STORAGECACHE_H

#include "global_definitions.h"
#include "modules/helpers.h"

#include <map>
#include <memory>
#include <random>

class StorageCache
{
public:
    struct DrawResult {
        constexpr DrawResult(EModIds argMod, ll::Level argLvlIdx,
                             ll::ItemQty argItemIdx) :
            mod{argMod}, lvlIdx{argLvlIdx}, itemIdx{argItemIdx}
        {
        }
        DrawResult(const DrawResult& argDrawRes) = default;
        DrawResult(DrawResult&& argDrawRes) = default;

        const EModIds mod;
        const ll::Level lvlIdx;
        const ll::ItemQty itemIdx;
    };

    using LevelQtyArr = std::array<ll::ItemQty, ll::levelQty>;

    StorageCache();

    // TODO(markuspg) Replace by std::optional as soon as C++17 is permitted
    std::unique_ptr<DrawResult> DoMonteCarloDraw() const;
    ll::ItemQty GetTotalStoredItemsQty() const;
    void InsertNewItem(EModIds argMod);
    void ItemGotMoved(EModIds argItemsMod, ll::Level argItemsPrevLvl,
                      ll::Level argItemsNewLvl);
    void SetCategoryQty(EModIds argMod, ll::Level argLvlIdx,
                        ll::ItemQty argQty);

#ifdef CACHE_TEST
    ll::ItemQty GetItemQty(EModIds argItemsMod, ll::Level argItemsLvl) const
    {
        return itemsPerModPerLvl.at(argItemsMod).at(argItemsLvl);
    }
#endif

private:
    mutable std::uniform_real_distribution<double> dist;
    mutable std::mt19937_64 eng;
    std::map<EModIds, LevelQtyArr> itemsPerModPerLvl;
};

#endif // BBB_STORAGECACHE_H
