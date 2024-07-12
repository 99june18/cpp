#include <iostream>

typedef struct Animal {
	char name[30];

	int age;
	int health;
	int food;
	int clean;
};

void create(Animal* animal) {
	std::cout << "�̸� : ";
	std::cin >> animal->name;

	std::cout << "���� : ";
	std::cin >> animal->age;

	animal->health = 100;
	animal->food = 100;
	animal->clean = 100;
}

void play(Animal* animal) {
	animal->health -= 10;
}

void pass(Animal* animal) {
	animal->health += 10;
}

void stat(Animal* animal) {
	std::cout << animal->name << std::endl;
	std::cout << animal->age << std::endl;
	std::cout << animal->health << std::endl;
	std::cout << animal->food << std::endl;
	std::cout << animal->clean << std::endl;
}

//new, delete

//c ��� malloc�� ���� 
//int* p = new int; new�� �޸� �Ҵ��̶� pointer ���
//int �� addr ���� & p�� �ش� �޸� ���� pointing �Ѵ�.

/*array ������ int* array = new int[3];
 ������ �Ҵ�� �޸𸮿� ���� �ΰ��Ҷ�, *��� x
 array[1] = 3;
 & delete�� delete[] array

 ��ȣ �ȿ� �ִ� ������ �ۿ� �ִ� ������ ������ �޶�����
 �׸��� ������ �ȵǾ��ִٸ� �˾Ƽ� ���� ����� �������� ã�ư���
 { a = 3 } & a = 3�̶� �ٸ���

 struct �������� pointer�� struct ����� -> ���
 �ƴϸ� . ��� ex) animal->name , animal.name
 struct ���� ���� > ��ü ���� �䱸 (4�ܿ�)

 branch pratice
 */