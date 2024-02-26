#include "HashTable.h"
#include <iostream>
HashTable::HashTable() {
    count = 0;
    mem_size = 15;
    array = new Pair[mem_size];
}

HashTable::~HashTable() {
    delete[] array;
}

int HashTable::hash_func(Login login, int offset) {
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < strlen(login); i++) {
        sum += login[i];
    }
    const double A = 0.7;
    const int M = 90;
    // вычисление хеша методом умножения
    sum = int(M * (A * sum - int(A * sum)));
    // квадратичные пробы
    return (sum % mem_size + offset * offset) % mem_size;
}

void HashTable::add(Login login, char* password) {
    int index = -1, i = 0, hash = -1;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index].status != enPairStatus::engaged) {
            // найдена пустая ячейка, занимаем ее
            hash = hash_func(password, 0);
            break;
        }
    }
    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную ячейку пару
    array[index] = Pair(login, hash);
    count++;
}

void HashTable::del(Login login) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        // ищем нужную ячейку
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index]._login, login)) 
        {
            // меняем статус и хеш от пароля
            array[index].status = enPairStatus::deleted;
            array[index]._hash = -1;
            count--;
            return;
        }
        // если дошли до свободной, то завершаем цикл
        else if (array[index].status == enPairStatus::free) {
            return;
        }
    }
}

int HashTable::find(Login login) {
    // берем пробы по всем i от 0 до размера массива
    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(login, i);
        // возвращаем найденную ячейку
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index]._login, login)) {
            return array[index]._hash;
        }
        // если не нашли, то возвращаем -1
        else if (array[index].status == enPairStatus::free) {
            return -1;
        }
    }
    return -1;
}

void HashTable::print()
{
    for (int i = 0; i < mem_size; i++)
    {
        if (array[i].status != free)
            std::cout << "login: " << array[i]._login
                << " | password hash: " << array[i]._hash
                << " | status: " << array[i].status << std::endl;
    }
    std::cout << std::endl << "Count: " << count << std::endl
        << "Memory size: " << mem_size << std::endl << std::endl;
}