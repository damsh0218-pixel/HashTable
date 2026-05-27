#include "HashTable.h"
#include <functional>
#include <cstdint>

using namespace std;

HashTable::HashTable(size_t size) noexcept 
    : _capacity(static_cast<int32_t>(size))
    , _filled(0)
    , table(size)
{}

HashTable::~HashTable() = default;

size_t HashTable::hash_function(const KeyType &key) const {
    return hash<string>{}(key) % static_cast<size_t>(_capacity);
}

double HashTable::getLoadFactor() {
    if (_capacity == 0) return 0.0;
    return static_cast<double>(_filled) / _capacity;
}

void HashTable::rehash(int32_t new_capacity) {
    vector<list<pair<KeyType, ValueType>>> new_table(new_capacity);
    int32_t new_filled = 0;

    for (const auto& bucket : table) {
        for (const auto& elem : bucket) {
            size_t new_idx = hash<string>{}(elem.first) % static_cast<size_t>(new_capacity);
            if (new_table[new_idx].empty())
                ++new_filled;
            new_table[new_idx].push_back(elem);
        }
    }

    table = move(new_table);
    _capacity = new_capacity;
    _filled = new_filled;
}

void HashTable::insert(const KeyType &key, const ValueType &value) {
    size_t idx = hash_function(key);
    for (auto& elem : table[idx]) {
        if (elem.first == key) {
            elem.second = value;
            return;
        }
    }

    if (static_cast<double>(_filled + 1) / _capacity > 0.75) {
        int32_t new_cap = _capacity * 2;
        rehash(new_cap);
        idx = hash_function(key);
    }

    if (table[idx].empty())
        ++_filled;
    table[idx].push_back({key, value});
}

bool HashTable::find(const KeyType &key, ValueType &value) const {
    size_t idx = hash_function(key);
    for (const auto& elem : table[idx]) {
        if (elem.first == key) {
            value = elem.second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key) {
    size_t idx = hash_function(key);
    auto& bucket = table[idx];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            if (bucket.empty())
                --_filled;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key) {
    size_t idx = hash_function(key);
    for (auto& elem : table[idx]) {
        if (elem.first == key)
            return elem.second;
    }

    if (static_cast<double>(_filled + 1) / _capacity > 0.75) {
        int32_t new_cap = _capacity * 2;
        rehash(new_cap);
        idx = hash_function(key);
    }

    if (table[idx].empty())
        ++_filled;
    table[idx].push_back({key, ValueType{}});
    return table[idx].back().second;
}