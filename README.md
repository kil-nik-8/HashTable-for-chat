# HashTable-for-chat
Реализация хранения данных в виде Хеш-таблицы для примитовной модели чата, в котором хранятся только логин и хеш от пароля. 

# Пользовательские типы данных
  - class HashTable;
  - struct Pair;
  - enum enPairStatus;

(Далее под "Login" понимается char[20])

+ class HashTable содержит:
    * Поля:
        - Pair* array; – массив данных
        - int mem_size; – максимальный размер массива
        - int count; – количество элементов, добавленных в массив
    * Методы:
        - void add(Login login, char* password); – добавление в ХТ нового элемента
        - void del(Login login); – удаление по логину
        - int find(Login login); – поиск по логину
        - void print(); – вывод ХТ на экран консоли

+ struct Pair содержит
    * Поля:
        - Login _login; – логин пользователя
        - int _hash; – хеш от пароля
        - enPairStatus status; – статус ячейки

+ enum enPairStatus содержит:
    * free; – ячейка свободна
    * engaged; – ячейка занята
    * deleted. – ячейка была удалена
