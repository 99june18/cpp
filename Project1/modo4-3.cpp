#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <iostream>

class Photon_Cannon {
    int hp, shield;
    int coord_x, coord_y;
    int damage;

    char* name;

public:
    Photon_Cannon(int x, int y);
    Photon_Cannon(int x, int y, const char* cannon_name);
    Photon_Cannon(const Photon_Cannon& cp);
    ~Photon_Cannon();

    void show_status();
    void stat();
};

Photon_Cannon::Photon_Cannon(int x, int y) {
    std::cout << "생성자 호출" << std::endl;
    hp = shield = 100;
    coord_x = x;
    coord_y = y;
    damage = 20;

    name = NULL;
}
Photon_Cannon::Photon_Cannon(int x, int y, const char* cannon_name) {
    std::cout << "이름 생성자 호출" << std::endl;
    hp = shield = 100;
    coord_x = x;
    coord_y = y;
    damage = 20;

    name = new char[strlen(cannon_name) + 1];
    strcpy(name, cannon_name);
}

Photon_Cannon::Photon_Cannon(const Photon_Cannon& cp) {
    std::cout << "복사 생성자 호출" << std::endl;
    hp = cp.hp;
    shield = cp.shield;
    coord_x = cp.coord_x;
    coord_y = cp.coord_y;
    damage = cp.damage;

    name = new char[strlen(cp.name) + 1];
    strcpy(name, cp.name);
}

Photon_Cannon::~Photon_Cannon() {

    std::cout << "제거자" << std::endl;

    if (name) {
        delete[] name;
    };
}

void Photon_Cannon::show_status() {
    std::cout << "Photon Cannon :: " << name << std::endl;
    std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
        << std::endl;
    std::cout << " HP : " << hp << std::endl;
}

void Photon_Cannon::stat() {
    std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
        << std::endl;
    std::cout << " HP : " << hp << std::endl;
}

int main() {
    Photon_Cannon pc(2, 3);
    Photon_Cannon pc1(3, 3, "Cannon");
    Photon_Cannon pc2 = pc1;

    pc.stat();
    pc1.show_status();
    pc2.show_status();
}


/*
동적 할당 > new를 통해 메모리 주소 할당, & 생성자 사용
marine[0] = new Marine(3,2);
#new 사용시 메모리 주소값이 할당 > ***** (pointer 사용) (중요)
***********배열은 포인터라 동적 할당이 요구됨 (중요)
동적 할당 > 사용자가 메모리를 조절할 수 있는것 > malloc, new처럼 메모리 주소
를 코드를 실행할 때에만 부여하도록 함.

소멸자
생성자와 비슷하고, 자동으로 호출하는데, 메모리값을 지우는 역할을 한다
마치 delete인데, 자동 delete.
~(class 이름) 으로 표기
인자가 없다. ex) delete [] name;
생성자에 의해 생성되었다면 소멸자로 인하여, 제거 해줘야한다.

복사 생성자 T(const T& a); T = class
이는 a로 class에 정의된 값들을 복사만 가능하다. a를 이용하여, class에 정의된
값에 값을 인가하거나 하는 일은 불가능하다. const인자로 받았기 때문이다.

디폴트 복사 생성자의 한계 (복사 생성자를 만들지 않아도, 복사가 된다)
하지만 그럴경우, 다음과 같은 문제가 발생한다.
복사 생정자와 기존의 생성자 2개가 같은 주소값을 가리키고 있을 것이다
하지만 소멸자에 의해 기존 생성자가 제거될 경우(즉, 해당 호출이 끝났을 때)
, 복사 생성자가 가리키고 있는 주소값이 사라지게 된다.
즉 T pc2 = pc1;으로 디폴트 복사를 할 경우, 위와 같은 문제가 발생한다
>> 깊은 복사 요구됨 (복사 생성자를 따로 만들어 져야 한다)
메모리로 동적 할당되는 name의 경우, 따로 복사 생성자 내부에서 주소를
할당 시켜 준다면, 오류없이 해결 가능하다.

#strcpy(name,marine_name) = marine_name을 name 위치로 복사
*/