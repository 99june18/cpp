#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Marine {
    static int total_marine_num;
    const static int i = 0;

    int hp;                // ���� ü��
    int coord_x, coord_y;  // ���� ��ġ
    bool is_dead;

    const int default_damage;  // �⺻ ���ݷ�

public:
    Marine();              // �⺻ ������
    Marine(int x, int y);  // x, y ��ǥ�� ���� ����
    Marine(int x, int y, int default_damage);

    int attack() const;                          // �������� �����Ѵ�.
    Marine& be_attacked(int damage_earn);  // �Դ� ������
    void move(int x, int y);               // ���ο� ��ġ

    void show_status();  // ���¸� �����ش�.
    static void show_total_marine();
    ~Marine() { total_marine_num--; }
};
int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
    std::cout << "��ü ���� �� : " << total_marine_num << std::endl;
}
Marine::Marine()
    : hp(50), coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
    total_marine_num++;
}

Marine::Marine(int x, int y)
    : coord_x(x),
    coord_y(y),
    hp(50),

    default_damage(5),
    is_dead(false) {
    total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage)
    : coord_x(x),
    coord_y(y),
    hp(50),
    default_damage(default_damage),
    is_dead(false) {
    total_marine_num++;
}

void Marine::move(int x, int y) {
    coord_x = x;
    coord_y = y;
}
int Marine::attack() const { return default_damage; }
Marine& Marine::be_attacked(int damage_earn) {
    hp -= damage_earn;
    if (hp <= 0) is_dead = true;

    return *this;
}
void Marine::show_status() {
    std::cout << " *** Marine *** " << std::endl;
    std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
        << std::endl;
    std::cout << " HP : " << hp << std::endl;
    std::cout << " ���� �� ���� �� : " << total_marine_num << std::endl;
}

int main() {
    Marine marine1(2, 3, 5);
    marine1.show_status();

    Marine marine2(3, 5, 10);
    marine2.show_status();

    std::cout << std::endl << "���� 1 �� ���� 2 �� �� �� ����! " << std::endl;
    marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());

    marine1.show_status();
    marine2.show_status();
}

/*
������ ���ο� �ʱ�ȭ �۾� ���� (�ڵ� �ۼ� ���°� ����Ǿ�����, �����ϴ� ����
������ ��� > �ʱ�ȭ ����Ʈ (�ش� class�� private�� ������ Ȱ���Ѵ�
ex) hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
������ ȣ��� �ʱ�ȭ�� ���ÿ� �۾��Ѵ�.
������ �̸� : ����(�ʱ�ȭ ��) > form�̴�
�ش� �۾��� �ϴ� ������ ������ �ʱ�ȭ�� ���ÿ� �ϱ� �����̴�.
�� ���� �����ڴ� ���� �� �ʱ�ȭ : int a;, a = 3;
������ ������ �ʱ�ȭ�� : int a = 3;
��ǥ������ ����� ���۷����� ������ ���ÿ� �ʱ�ȭ�� �ؾ��Ѵ�.
�� const ����, ����,�ʱ�ȭ�� �ȵǰ�, ���� �� �ʱ�ȭ�� �������� ���������.

�� ������ Marine�� ������ ���� �溡 : static ���
static : ��ü�� �Ҹ�� �� �Ҹ�Ǵ°� �ƴ϶�, ���α׷��� ������ �� �Ҹ�

static �ʱ�ȭ ���, & if Marine class�ȿ� static�� �ִٸ�
int Marine::total_marine_num = 0;

class ���� ������ �� �ʱ�ȭ ������ ����, cosnt static �ۿ� ����.

static�� ���� ū Ư¡�� ��ü�� ���ӵ� ���� �ƴ�, class�� ���ӵȴٴ°��� ū Ư¡
����, class�� ����������, ���� ��������, ��� �ϳ��� ��ü�� ���ӵǴ� ����
�ƴ϶�, ���� ��ü���� ���� ������ ��밡���ϴ�.
static �Լ��� ��� ����, ��� �ϳ��� ��ü�� �Լ��θ� ����� ������ ���� �ƴ�,
class ��ü�� ���� �Լ��� ����� �����ϱ� ������, ���� ��ü���� ���� �Լ��� ���
�����ϴ�
ex) Marine marine1(2, 3, 5);
  Marine::show_total_marine();

  Marine marine2(3, 5, 10);
  Marine::show_total_marine();
  >> �ٸ� ��ü �ӿ��� ���� static �Լ� ���ȴ�.
  & ȣ���, (class) :: (static �Լ�) ���̴�.
  ���� static �Լ� ���ο��� static ������ ����� �����ϴ� (*****�߿�)

  this
  & (���۷���)�� �����ϴ� �Լ��� this
  this : ��ü �ڽ��� ����Ű�� ������ > �� �Լ��� ȣ���ϴ� ��ü �ڽ��� ����Ų��
  �ش� �Լ��� ȣ���ϴ� ��ü �ڽ��� ����Ų��.
  this = ��ü�� �ּҰ�.

  ���۷��� �Լ� & this return�ϸ� this�� ���Ͽ�, ��ü�� ����Ű�� �ڽ��� �����ϰ�
  �� ���̴� ����
  marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
  ���� ó�� marine2.be_attack�� this return���� marine2�� �ٽ� ���ϵǰ�,
  �̸� �ٽ� be_attacked�Ǿ, be_attacked�� 2�� ȣ��ȴ�.
  (this�� ���۷��� �Լ� �ٽ� ����) ***************************

  ���۷��� �Լ� & *this : this�� ���Ͽ�, ȣ���� ��ü�� return�Ǵµ�,
  ���۷��� �Լ��� ����� ���, ������ ��ü�� ���� �������� �޴´�.
  ������ �׳� �Լ��� ����� ���, ������ ��ü�� ������ ���纻�� �����Ѵ�.
  ����, ���� ��ü��� �� �� ����.

  const �Լ� : ���� �б⸸ �ϴ� �Լ�
  form : (������ �Լ� ����) const ����
  int Marine::attack() const { return default_damage; }
  �б⸸ �����ϴ�.
*/