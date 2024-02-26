#pragma once
#include <string.h>

#define NAMELENGTH 20  // �����c����� ����� �����

typedef char Login[NAMELENGTH]; // ��� ��� ������

class HashTable { // ��� �������
public:

    HashTable();
    ~HashTable();
    // ���������� � �� ������ ��������
    void add(Login login, char* password);
    // �������� �� ������
    void del(Login login);
    // ����� �� ������
    int find(Login login);
    // ����� �� �� ����� �������
    void print();

private:

    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { // ���� ����-��������

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
    // ���-�������
    int hash_func(Login login, int offset);
    // ������ ������
    Pair* array;
    // ������������ ������ �������
    int mem_size;
    // ���������� ���������, ����������� � ������
    int count;
};