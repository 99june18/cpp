#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Marine {
    static int total_marine_num;
    const static int i = 0;

    int hp;                // 마린 체력
    int coord_x, coord_y;  // 마린 위치
    bool is_dead;

    const int default_damage;  // 기본 공격력

public:
    Marine();              // 기본 생성자
    Marine(int x, int y);  // x, y 좌표에 마린 생성
    Marine(int x, int y, int default_damage);

    int attack() const;                          // 데미지를 리턴한다.
    Marine& be_attacked(int damage_earn);  // 입는 데미지
    void move(int x, int y);               // 새로운 위치

    void show_status();  // 상태를 보여준다.
    static void show_total_marine();
    ~Marine() { total_marine_num--; }
};
int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
    std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
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
    std::cout << " 현재 총 마린 수 : " << total_marine_num << std::endl;
}

int main() {
    Marine marine1(2, 3, 5);
    marine1.show_status();

    Marine marine2(3, 5, 10);
    marine2.show_status();

    std::cout << std::endl << "마린 1 이 마린 2 를 두 번 공격! " << std::endl;
    marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());

    marine1.show_status();
    marine2.show_status();
}

/*
생성자 새로운 초기화 작업 수행 (코드 작성 형태가 변경되었지만, 수행하는 일은
동일한 경우 > 초기화 리스트 (해당 class에 private한 변수를 활용한다
ex) hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
생성자 호출과 초기화를 동시에 작업한다.
생성자 이름 : 변수(초기화 값) > form이다
해당 작업을 하는 이유는 생성과 초기화를 동시에 하기 때문이다.
즉 기존 생성자는 생성 후 초기화 : int a;, a = 3;
하지만 생성자 초기화는 : int a = 3;
대표적으로 상수와 레퍼런스는 생성과 동시에 초기화를 해야한다.
즉 const 사용시, 생성,초기화가 안되고, 생성 후 초기화면 생성에서 에러생긴다.

총 생성된 Marine의 개수를 세는 방벙 : static 사용
static : 객체가 소멸될 때 소멸되는게 아니라, 프로그램이 종류할 떄 소멸

static 초기화 방법, & if Marine class안에 static이 있다면
int Marine::total_marine_num = 0;

class 변수 정의할 때 초기화 가능한 경우는, cosnt static 밖에 없다.

static의 가장 큰 특징은 객체에 종속된 것이 아닌, class에 종속된다는것이 큰 특징
따라서, class가 끝나야지만, 값이 없어지며, 어느 하나의 객체에 종속되는 것이
아니라, 여러 객체에서 같은 변수로 사용가능하다.
static 함수의 경우 역시, 어느 하나의 객체의 함수로만 사용이 가능한 것이 아닌,
class 전체에 대한 함수로 사용이 가능하기 때문에, 여러 객체에서 같은 함수를 사용
가능하다
ex) Marine marine1(2, 3, 5);
  Marine::show_total_marine();

  Marine marine2(3, 5, 10);
  Marine::show_total_marine();
  >> 다른 객체 임에도 같은 static 함수 사용된다.
  & 호출시, (class) :: (static 함수) 꼴이다.
  또한 static 함수 내부에선 static 변수만 사용이 가능하다 (*****중요)

  this
  & (레퍼런스)를 리턴하는 함수와 this
  this : 객체 자신을 가리키는 포인터 > 이 함수를 호출하는 객체 자신을 가리킨다
  해당 함수를 호출하는 객체 자신을 가리킨다.
  this = 객체의 주소값.

  레퍼런스 함수 & this return하면 this로 인하여, 객체가 가리키는 자신을 리턴하게
  될 것이다 따라서
  marine2.be_attacked(marine1.attack()).be_attacked(marine1.attack());
  에서 처음 marine2.be_attack의 this return으로 marine2가 다시 리턴되고,
  이를 다시 be_attacked되어서, be_attacked가 2번 호출된다.
  (this와 레퍼런스 함수 다시 보기) ***************************

  레퍼런스 함수 & *this : this로 인하여, 호출한 객체가 return되는데,
  레퍼런스 함수를 사용한 경우, 리턴한 객체에 대한 참조값을 받는다.
  하지만 그냥 함수를 사용한 경우, 리턴한 객체의 임의의 복사본을 리턴한다.
  따라서, 같은 객체라고 볼 수 없다.

  const 함수 : 값을 읽기만 하는 함수
  form : (기존의 함수 정의) const 형태
  int Marine::attack() const { return default_damage; }
  읽기만 가능하다.
*/