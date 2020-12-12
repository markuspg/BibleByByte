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

#include "storagecache.h"

#include <iostream>
#include <numeric>

using FreqArr = std::array<ll::ItemQty, ll::levelQty>;
// this array's purpose is to weigh the frequencies of variable repetitions
// level '0' shall be repeated daily, the highest level only every 384 days
// the levels shall be repeated every 1/2/3/8/32/64/96/384 days
constexpr static FreqArr frequencies{384, 192, 128, 48, 12, 6, 4, 1};

ll::ItemQty WeightedItemsPerMod(const StorageCache::LevelQtyArr& argArr)
{
    FreqArr::size_type freqArrIdx = 0;
    ll::ItemQty weightedItemQty = 0;
    for (const StorageCache::LevelQtyArr::value_type lvlQty : argArr) {
        weightedItemQty += lvlQty * frequencies.at(freqArrIdx);
        ++freqArrIdx;
    }
    return weightedItemQty;
}

StorageCache::StorageCache() : eng{std::random_device{}()}
{
    for (const std::pair<EModIds, const char*>& modInfo : GetModuleNames()) {
        itemsPerModPerLvl.emplace(modInfo.first, LevelQtyArr{});
    }
}

/*!
 * \brief Draw module and level of a random item
 * \return A DrawResult struct with the required info or empty, if no data
 * available
 */
std::unique_ptr<StorageCache::DrawResult> StorageCache::DoMonteCarloDraw() const
{
    // draw a random category and level indicator
    const double modDraw = dist(eng);
    const double lvlDraw = dist(eng);

    // compute the entire weighted item quantity
    const unsigned long totalWeightedItemQty = std::accumulate(
        itemsPerModPerLvl.cbegin(), itemsPerModPerLvl.cend(), 0ul,
        [](const ll::ItemQty argCurrQty,
           const std::map<EModIds, LevelQtyArr>::value_type& argCurrMod) {
            return argCurrQty + WeightedItemsPerMod(argCurrMod.second);
        });
    if (totalWeightedItemQty == 0) {
        return std::unique_ptr<DrawResult>{};
    }

    // choose module
    unsigned long weightedAccumulatedItems = 0ul;
    EModIds chosenModule = EModIds::ZZZ_MOD_QTY;
    const ll::ItemQty partitionQty
        = static_cast<ll::ItemQty>(modDraw * totalWeightedItemQty);
    for (const std::pair<EModIds, LevelQtyArr>& modLvls : itemsPerModPerLvl) {
        const ll::ItemQty weightedItemsInMod
            = WeightedItemsPerMod(modLvls.second);
        if ((weightedAccumulatedItems + weightedItemsInMod) > partitionQty) {
            chosenModule = modLvls.first;
            break;
        }
        weightedAccumulatedItems += weightedItemsInMod;
    }

    // choose level of module
    weightedAccumulatedItems = 0;
    ll::Level chosenLevel = 0;
    const ll::ItemQty modQty
        = WeightedItemsPerMod(itemsPerModPerLvl.at(chosenModule));
    const ll::ItemQty lvlPartQty = static_cast<ll::ItemQty>(lvlDraw * modQty);
    ll::Level lvlIdx = 0;
    FreqArr::size_type freqArrIdx = 0;
    for (const ll::ItemQty lvlQty : itemsPerModPerLvl.at(chosenModule)) {
        const ll::ItemQty weightedItemsInLvl
            = lvlQty * frequencies.at(freqArrIdx);
        if ((weightedAccumulatedItems + weightedItemsInLvl) > lvlPartQty) {
            chosenLevel = lvlIdx;
            break;
        }
        weightedAccumulatedItems += weightedItemsInLvl;
        ++freqArrIdx;
        ++lvlIdx;
    }

    std::uniform_int_distribution<ll::ItemQty> itemDist{
        0, itemsPerModPerLvl.at(chosenModule).at(chosenLevel) - 1};
    return std::unique_ptr<DrawResult>{
        new DrawResult{chosenModule, chosenLevel, itemDist(eng)}};
}

ll::ItemQty StorageCache::GetTotalStoredItemsQty() const
{
    ll::ItemQty totalQty = 0;

    for (const std::pair<EModIds, LevelQtyArr>& module : itemsPerModPerLvl) {
        totalQty += std::accumulate(module.second.cbegin(),
                                    module.second.cend(), 0ul);
    }

    return totalQty;
}

void StorageCache::InsertNewItem(const EModIds argMod)
{
    itemsPerModPerLvl.at(argMod)[0] += 1;
}

void StorageCache::ItemGotMoved(const EModIds argItemsMod,
                                const ll::Level argItemsPrevLvl,
                                const ll::Level argItemsNewLvl)
{
    LevelQtyArr& currMod{itemsPerModPerLvl.at(argItemsMod)};

    if (currMod.at(argItemsPrevLvl) == 0) {
        std::cerr << "A level's quantity cannot be decreased below '0'"
                  << std::endl;
        throw std::exception{};
    }

    // get the references first so that data remains unchanged in case of an
    // out-of-bounds
    ll::ItemQty& prevLvl = currMod.at(argItemsPrevLvl);
    ll::ItemQty& newLvl = currMod.at(argItemsNewLvl);

    prevLvl -= 1;
    newLvl += 1;
}

void StorageCache::SetCategoryQty(const EModIds argMod,
                                  const ll::Level argLvlIdx,
                                  const ll::ItemQty argQty)
{
    itemsPerModPerLvl.at(argMod).at(argLvlIdx) = argQty;
}
