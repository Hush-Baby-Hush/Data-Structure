/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */
<<<<<<< HEAD
    unsigned int hash__ = hashes::hash(key, size);
    while (table[hash__] != NULL) {
        hash__ = (hash__ + 1) % size;
=======

    elems++;
    size_t p = hashes::hash(key,size);
    
    if (shouldResize()==true)
    {
        resizeTable();   
>>>>>>> e070d8d81c0f17d0e4e9e4b3976b81ed6f41b4de
    }
    table[hash__] = new std::pair<K, V>(key, value);
    should_probe[hash__] = true;
    elems++;
    if (shouldResize()) 
    {
<<<<<<< HEAD
        resizeTable();
=======
        if (table[p] == NULL) 
        {
            should_probe[p]=true;
            table[p] = new std::pair<K, V>(key,value);
            break;
        }
        p = (p+1) % size;
        if (p != q)
        {
            continue;
        }
        else
        {
            break;
        }
        
>>>>>>> e070d8d81c0f17d0e4e9e4b3976b81ed6f41b4de
    }
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
    int idx = findIndex(key);
    if (idx != -1) {
        delete table[idx];
        table[idx] = NULL;
        --elems;
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    size_t idx = hashes::hash(key, size);
    size_t start = idx;
    while (should_probe[idx]) {
        if (table[idx] != NULL && table[idx]->first == key)
            return idx;
        idx = (idx + 1) % size;
        // if we've looped all the way around, the key has not been found
        if (idx == start)
            break;
    }
    return -1;

}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    size_t nsz_ = findPrime(size * 2);
    delete[] should_probe;
    should_probe = new bool[nsz_];
    std::pair<K, V>** temp = new std::pair<K, V>*[nsz_];
    for (size_t i = 0; i < nsz_; i++) {
        temp[i] = NULL;
        should_probe[i] = false;
    }
    for (size_t i = 0; i < size; i++) {
        if (table[i]) {
            size_t idx = hashes::hash(table[i]->first, nsz_);
            while (temp[idx])
            {
                idx = (idx + 1) % nsz_;
            }
            temp[idx] = table[i];
            should_probe[idx] = true;
        }
    }
    delete[] table;
    table = temp;
    size = nsz_;
}
