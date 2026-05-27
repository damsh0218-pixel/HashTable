#pragma once
#include <vector>
#include <list>
#include <string>
#include <utility>

using KeyType = std::string;
using ValueType = double;

class HashTable 
{
public:
    //! Конструктор
    explicit HashTable(size_t size = 100) noexcept;
    //! Деструктор
    ~HashTable();

    //! Вставка элемента в хеш-таблицу
    void insert(const KeyType &key, const ValueType &value);
    //! Поиск элемента в хеш таблице
    bool find(const KeyType &key, ValueType &value) const;
    //! Удаление элемента из хеш-таблицы
    void remove(const KeyType &key);
    //! Получение элемента по ключу
    ValueType& operator[](const KeyType &key);

    //! Загрузка хеш-таблицы
    double getLoadFactor();
    
    //! Для отладки
    int32_t getCapacity() const { return _capacity; }
    int32_t getSize() const { return _filled; }

private:
    int32_t _capacity;
    int32_t _filled;
    std::vector<std::list<std::pair<KeyType, ValueType>>> table;
    size_t hash_function(const KeyType &key) const;
    
    //! Приватный метод для перехеширования
    void rehash(int32_t new_capacity);
};