#include <iostream>
#include "HashTable.h"

int main() {
    HashTable ht(4); 
    ht.insert("apple", 1.5);
    ht.insert("banana", 2.3);
    ht.insert("cherry", 3.7);
    ValueType val;
    if (ht.find("banana", val)) {
        std::cout << "  Найдено banana = " << val << "\n";
    }
    std::cout << "  Load factor: " << ht.getLoadFactor() << "\n\n";
    ht.insert("apple", 5.0);
    ht.find("apple", val);
    std::cout << "  apple обновлено на = " << val << "\n\n";
    std::cout << "  ht[\"cherry\"] = " << ht["cherry"] << "\n";
    ht["date"] = 4.2;
    std::cout << "  ht[\"date\"] = " << ht["date"] << " (новый элемент)\n\n";
    ht.remove("banana");
    if (!ht.find("banana", val)) {
        std::cout << "  banana успешно удален\n";
    }
    std::cout << "  Текущий размер: " << ht.getSize() << "\n\n";
    std::cout << "  Начальный capacity: " << ht.getCapacity() << "\n";
    std::cout << "  Начальный load factor: " << ht.getLoadFactor() << "\n";
    std::cout << "  Добавляем много элементов...\n";
    
    for (int i = 0; i < 100; i++) {
        ht.insert("key" + std::to_string(i), i * 1.0);
        if (i > 0 && i % 20 == 0) {
            std::cout << "    После " << i << " элементов: capacity=" 
                      << ht.getCapacity() << ", load factor=" 
                      << ht.getLoadFactor() << "\n";
        }
    }
    
    std::cout << "\n  Итоговый capacity: " << ht.getCapacity() << "\n";
    std::cout << "  Итоговый размер: " << ht.getSize() << "\n";
    std::cout << "  Итоговый load factor: " << ht.getLoadFactor() << "\n";
    bool all_found = true;
    for (int i = 0; i < 100; i++) {
        if (!ht.find("key" + std::to_string(i), val)) {
            std::cout << "  Ошибка: key" << i << " не найден!\n";
            all_found = false;
        }
    }
    if (all_found) {
        std::cout << "  Все 100 элементов успешно найдены!\n";
    }
    ht.find("key50", val);
    std::cout << "  key50 = " << val << " (ожидается 50.0)\n";
    return 0;
}