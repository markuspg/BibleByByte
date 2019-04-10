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

#include "storagecache.h"

#include <stdexcept>

StorageCache::StorageCache() :
    itemsPerCat{}
{
}

void StorageCache::SetCategoryQty(const unsigned short argCatIdx,
                                  const unsigned long argQty)
{
    if (argCatIdx >= categoryQty) {
        throw std::out_of_range{"Invalid category index given for update"};
    }
    itemsPerCat[argCatIdx] = argQty;
}
