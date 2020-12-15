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

#ifndef BBB_SINGLETON_H
#define BBB_SINGLETON_H

#include <QException>

#include <atomic>

namespace BibleByByte {

// InstanceExistsException -----------------------------------------------------

/*!
 * \brief Exception thrown if a new Singleton instance is created while one
 * exists already
 */
class InstanceExistsException : public QException
{
    InstanceExistsException* clone() const override;
    void raise() const override;
};

// Singleton -------------------------------------------------------------------

template <typename T> class Singleton
{
public:
    /*!
     * \brief Destroy Singleton<T> instance and re-allow creation of new ones
     */
    virtual ~Singleton() { instanceExists.clear(); }

protected:
    /*!
     * \brief Construct a new instance of Singleton<T>
     *
     * \exception InstanceExistsException This is thrown if a Singleton<T>
     * instance is being constructed while another one still exists
     */
    Singleton()
    {
        if (instanceExists.test_and_set()) {
            throw InstanceExistsException{};
        }
    }

private:
    //! Flag hinting if there exists a Singleton<T> instance already
    static std::atomic_flag instanceExists;
};

template <typename T>
std::atomic_flag Singleton<T>::instanceExists = ATOMIC_FLAG_INIT;

} // namespace BibleByByte

#endif // BBB_SINGLETON_H
