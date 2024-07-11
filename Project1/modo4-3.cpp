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
    std::cout << "������ ȣ��" << std::endl;
    hp = shield = 100;
    coord_x = x;
    coord_y = y;
    damage = 20;

    name = NULL;
}
Photon_Cannon::Photon_Cannon(int x, int y, const char* cannon_name) {
    std::cout << "�̸� ������ ȣ��" << std::endl;
    hp = shield = 100;
    coord_x = x;
    coord_y = y;
    damage = 20;

    name = new char[strlen(cannon_name) + 1];
    strcpy(name, cannon_name);
}

Photon_Cannon::Photon_Cannon(const Photon_Cannon& cp) {
    std::cout << "���� ������ ȣ��" << std::endl;
    hp = cp.hp;
    shield = cp.shield;
    coord_x = cp.coord_x;
    coord_y = cp.coord_y;
    damage = cp.damage;

    name = new char[strlen(cp.name) + 1];
    strcpy(name, cp.name);
}

Photon_Cannon::~Photon_Cannon() {

    std::cout << "������" << std::endl;

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
���� �Ҵ� > new�� ���� �޸� �ּ� �Ҵ�, & ������ ���
marine[0] = new Marine(3,2);
#new ���� �޸� �ּҰ��� �Ҵ� > ***** (pointer ���) (�߿�)
***********�迭�� �����Ͷ� ���� �Ҵ��� �䱸�� (�߿�)
���� �Ҵ� > ����ڰ� �޸𸮸� ������ �� �ִ°� > malloc, newó�� �޸� �ּ�
�� �ڵ带 ������ ������ �ο��ϵ��� ��.

�Ҹ���
�����ڿ� ����ϰ�, �ڵ����� ȣ���ϴµ�, �޸𸮰��� ����� ������ �Ѵ�
��ġ delete�ε�, �ڵ� delete.
~(class �̸�) ���� ǥ��
���ڰ� ����. ex) delete [] name;
�����ڿ� ���� �����Ǿ��ٸ� �Ҹ��ڷ� ���Ͽ�, ���� ������Ѵ�.

���� ������ T(const T& a); T = class
�̴� a�� class�� ���ǵ� ������ ���縸 �����ϴ�. a�� �̿��Ͽ�, class�� ���ǵ�
���� ���� �ΰ��ϰų� �ϴ� ���� �Ұ����ϴ�. const���ڷ� �޾ұ� �����̴�.

����Ʈ ���� �������� �Ѱ� (���� �����ڸ� ������ �ʾƵ�, ���簡 �ȴ�)
������ �׷����, ������ ���� ������ �߻��Ѵ�.
���� �����ڿ� ������ ������ 2���� ���� �ּҰ��� ����Ű�� ���� ���̴�
������ �Ҹ��ڿ� ���� ���� �����ڰ� ���ŵ� ���(��, �ش� ȣ���� ������ ��)
, ���� �����ڰ� ����Ű�� �ִ� �ּҰ��� ������� �ȴ�.
�� T pc2 = pc1;���� ����Ʈ ���縦 �� ���, ���� ���� ������ �߻��Ѵ�
>> ���� ���� �䱸�� (���� �����ڸ� ���� ����� ���� �Ѵ�)
�޸𸮷� ���� �Ҵ�Ǵ� name�� ���, ���� ���� ������ ���ο��� �ּҸ�
�Ҵ� ���� �شٸ�, �������� �ذ� �����ϴ�.

#strcpy(name,marine_name) = marine_name�� name ��ġ�� ����
*/