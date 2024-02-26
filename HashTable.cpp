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
    // ��������� ������
    int sum = 0, i = 0;
    for (; i < strlen(login); i++) {
        sum += login[i];
    }
    const double A = 0.7;
    const int M = 90;
    // ���������� ���� ������� ���������
    sum = int(M * (A * sum - int(A * sum)));
    // ������������ �����
    return (sum % mem_size + offset * offset) % mem_size;
}

void HashTable::add(Login login, char* password) {
    int index = -1, i = 0, hash = -1;
    // ����� ����� �� ���� i �� 0 �� ������� �������
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index].status != enPairStatus::engaged) {
            // ������� ������ ������, �������� ��
            hash = hash_func(password, 0);
            break;
        }
    }
    if (i >= mem_size) return; // ��� ���������, ��� �����

    // ������ � ��������� ������ ����
    array[index] = Pair(login, hash);
    count++;
}

void HashTable::del(Login login) {
    int index = -1, i = 0;
    // ����� ����� �� ���� i �� 0 �� ������� �������
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        // ���� ������ ������
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index]._login, login)) 
        {
            // ������ ������ � ��� �� ������
            array[index].status = enPairStatus::deleted;
            array[index]._hash = -1;
            count--;
            return;
        }
        // ���� ����� �� ���������, �� ��������� ����
        else if (array[index].status == enPairStatus::free) {
            return;
        }
    }
}

int HashTable::find(Login login) {
    // ����� ����� �� ���� i �� 0 �� ������� �������
    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(login, i);
        // ���������� ��������� ������
        if (array[index].status == enPairStatus::engaged &&
            !strcmp(array[index]._login, login)) {
            return array[index]._hash;
        }
        // ���� �� �����, �� ���������� -1
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