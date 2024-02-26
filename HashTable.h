#pragma once
#include <string.h>

#define NAMELENGTH 20  // Зафикcируем длину имени

typedef char Login[NAMELENGTH]; // тип имя фрукта

class HashTable { // хэш таблица
public:

    HashTable();
    ~HashTable();
    // добавление в ХТ нового элемента
    void add(Login login, char* password);
    // удаление по логину
    void del(Login login);
    // поиск по логину
    int find(Login login);
    // вывод ХТ на экран консоли
    void print();

private:

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { // пара ключ-значение

        Pair() :
            _login(""),
            _hash(-1),
            status(enPairStatus::free)
        {}
        Pair(Login login, int hash) :
            _hash(hash),
            status(enPairStatus::engaged) {
            memcpy(_login, login, NAMELENGTH);
        }
        Pair& operator = (const Pair& other) {
            _hash = other._hash;
            memcpy(_login, other._login, NAMELENGTH);
            status = other.status;

            return *this;
        }

        bool operator == (const Pair& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || (_hash == other._hash && !strcmp(_login, other._login)));
        }

        Login _login;
        int _hash;

        enPairStatus status;
    };
    // Хеш-Функция
    int hash_func(Login login, int offset);
    // массив данных
    Pair* array;
    // максимальный размер массива
    int mem_size;
    // количество элементов, добавленных в массив
    int count;
};