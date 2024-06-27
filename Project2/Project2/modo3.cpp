#include <iostream>

typedef struct Animal {
	char name[30];

	int age;
	int health;
	int food;
	int clean;
};

void create(Animal* animal) {
	std::cout << "이름 : ";
	std::cin >> animal->name;

	std::cout << "나이 : ";
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

//c 언어 malloc과 유사 
//int* p = new int; new는 메모리 할당이라 pointer 사용
//int 형 addr 생성 & p가 해당 메모리 공간 pointing 한다.

/*array 구조는 int* array = new int[3];
 하지만 할당된 메모리에 값을 인가할때, *사용 x
 array[1] = 3;
 & delete시 delete[] array

 괄호 안에 있는 변수랑 밖에 있는 변수랑 지정이 달라진다
 그리고 지정이 안되어있다면 알아서 가장 가까운 범위에서 찾아간다
 { a = 3 } & a = 3이랑 다르다

 struct 구조에서 pointer로 struct 설명시 -> 사용
 아니면 . 사용 ex) animal->name , animal.name
 struct 구조 불편성 > 객체 지향 요구 (4단원)
 */