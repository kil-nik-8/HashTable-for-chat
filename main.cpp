#include <iostream>
#include "HashTable.h"

using namespace std;

int main()
{
	HashTable chat;
	chat.add((char*)"Nikita", (char*)"Password1");
	chat.add((char*)"Misha", (char*)"Password2");
	chat.add((char*)"Maksim", (char*)"Password3");
	chat.add((char*)"Dasha", (char*)"Password4");
	chat.add((char*)"Daniil", (char*)"Password5");
	chat.add((char*)"Denis", (char*)"Password6");
	chat.add((char*)"Lera", (char*)"Password7");
	chat.add((char*)"Andrew", (char*)"Password8");

	chat.print();

	chat.del((char*)"Lera");
	chat.del((char*)"Denis");

	chat.print();

	chat.add((char*)"Alex", (char*)"PASSWORD");

	chat.print();
	return 0;
}