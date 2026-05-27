CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
TARGET = hash_table_demo

# Исходные файлы
SOURCES = HashTable.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Цель по умолчанию
all: $(TARGET)

# Линковка
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Компиляция .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(TARGET) $(OBJECTS)

# Пересборка
rebuild: clean all

.PHONY: all run clean rebuild
