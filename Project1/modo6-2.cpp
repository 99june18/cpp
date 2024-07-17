#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

class employee {
protected:
	std::string name;
	int age;

	std::string position;
	int rank;

public:
	//기본 생성자
	employee(std::string name, int age, std::string position, int rank);
	//복사 생성자
	employee(const employee& s);
	//정보 보여주는 함수
	virtual void print();
	//월급 계산
	virtual int pay();
};
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// 
//기본 생성자
employee::employee(std::string name, int age, std::string position, int rank)
	: name(name), age(age), position(position), rank(rank) {}

//복사 생성자
employee::employee(const employee& s) {
	name = s.name;
	age = s.age;
	position = s.position;
	rank = s.rank;
}

int employee::pay() {
	return 200 + 50 * rank;
}

void employee::print() {
	std::cout << "이름 : " << name << std::endl;
	std::cout << "나이 : " << age << std::endl;
	std::cout << "직책 : " << position << std::endl;
	std::cout << "등급 : " << rank << std::endl;
	std::cout << "월급 : " << pay() << std::endl;
	std::cout << "-------------------" << std::endl;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

class manager : public employee {
private:
	int year;

public:
	//기본 생성자
	manager(std::string name, int age, std::string position, int rank, int year);
	//복사 생성자
	manager(const manager& s);
	//정보 보여주는 함수
	void print() override; //override 안써도 돌아가는데, error 사전예방용이다.
	//월급 계산
	int pay() override;


};

manager::manager(std::string name, int age, std::string position, int rank, int year)
	: employee(name, age, position, rank), year(year) { }

manager::manager(const manager& s)
	: employee(s.name, s.age, s.position, s.rank) {
	year = s.year;

}

int manager::pay() {
	return (200 + rank * 50 + 5 * year);
}

void manager::print() {
	std::cout << "이름 : " << name << std::endl;
	std::cout << "나이 : " << age << std::endl;
	std::cout << "직책 : " << position << std::endl;
	std::cout << "등급 : " << rank << std::endl;
	std::cout << "월급 : " << pay() << std::endl;
	std::cout << "년도 : " << year << std::endl;
	std::cout << "-------------------" << std::endl;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

class employeelist {
private:
	int alloc_employee;        // 할당한 총 직원 수
	int current_employee;      // 현재 직원 수
	employee** employee_list; //employee class 가리키며, 배열구조 > ** 2개

public:
	//기본 생성자 employee class의 matrix가 생성됨
	employeelist(int alloc_employee);
	//employee 추가
	void add_employ(employee* employ);
	//print
	int current_num() const;
	//print info
	void print_employ() const;

	~employeelist();

};

employeelist::employeelist(int _alloc_employee) {
	alloc_employee = _alloc_employee;
	current_employee = 0;

	employee_list = new employee * [alloc_employee];
}

//employee 추가
//employee class를 받아서, 대입시킨다.
void employeelist::add_employ(employee* employ) {
	int temp;

	employee_list[current_employee] = employ;
	current_employee++;
}

int employeelist::current_num() const {
	return current_employee;
}

void employeelist::print_employ() const {
	int total_pay = 0;

	for (int i = 0; i < current_employee; i++)
	{
		employee_list[i]->print();
		total_pay += employee_list[i]->pay();
	}

	std::cout << "총 인원 : " << current_employee << std::endl;
	std::cout << "총 지출 : " << total_pay << std::endl;
}

employeelist::~employeelist() {
	delete[] employee_list;
}

int main() {
	employeelist size(10);
	employee s1("노홍철", 34, "평사원", 1);
	employee s2("하하", 34, "평사원", 1);
	manager s3("유재석", 41, "부장", 7, 12);
	manager s4("정준하", 43, "과장", 4, 15);
	manager s5("박명수", 43, "차장", 5, 13);
	employee s6("정형돈", 36, "대리", 2);
	employee s7("길", 36, "인턴", -2);

	size.add_employ(&s1);
	size.add_employ(&s2);
	size.add_employ(&s3);
	size.add_employ(&s4);
	size.add_employ(&s5);
	size.add_employ(&s6);
	size.add_employ(&s7);

	size.print_employ();
}

/*
상속을 사용하는 이유 : 객체지향 프로그램밍에서 추구하는 실제 객체의 추상화를 효과적이다
즉 구조체간의 관계를 표현할 수 있게 되었다.
즉 is a관계를 한다. 예시로 class manager : public employee > manager is a employee
manager class는 employee class에 있는 모든 것을 수행 할 수 있다.
화살표로 표시하자면, 상속 받은 class -> 상속 되는 class
+ 상속 받는 구조체는 상속 되는 구조체에 비해 더 구체화,특수화 되는 경향이 있다.

is a 관계의 상속 말고도, has a 관계의 상속도 있다. 이는 아예 상속 되는 class를 포함하고 있다.
즉 예시로 car이라는 class 안에, brake class, engine class등이 아예 포함되어 있는 상태를 의미한다.
C++ 프로그래밍에서 "is-a" 관계는 클래스 간의 상속 관계를 나타내며, 
"has-a" 관계는 클래스 내부에서 다른 클래스 객체를 포함하는 관계를 의미합니다

포인터 사용 상속 > Base* p_c = &c; 다음과 같이 base class 포인터의 p_c가 derived class의 객체 c를 가리킨다.
이때 p_c는 base의 포인터 이므로, what() 함수는 base에 있는 것이 출력된다.
이는 p_c가 derived class을 가리키고 있는 상태에서, p_c는 base의 what 함수를 부르면, derived class에 base what() 함수가
있어야만 실행이 된다.
근데 만약 Derived* p_p = &p;  p_p->what(); 이 된다면, p_p가 base 객체를 가리키고 있고, p_p가 derived class의 what함수
를 부르면, base 클래스에 derived class 함수인 what이 있어야만 실행이 되는데, 이는 다운 캐스팅이기 때문에 에러가 된다.
즉 상속 되는 쪽의 포인터가 상속 하는 쪽의 객체를 가리키는 경우는 ok, 하지만 그 반대는 불가

# 타입을 바꾸는 형변환으론 static_cast<바꾸려고 하는 타입>(대상);꼴이 존재한다.
static_cast<Derived*>(p_p); > p_p를 Derived* 로 형변환
여기서 캐스팅 오류를 미연에 방지 하는 dynamic_cast지원 > 컴파일 전에 캐스팅이 되는지를 확인부터 하는 애

다시 돌아가서, 업 캐스팅은 자유롭다고 하였기에, employee가 manager의 객체를 가리키는 것이 자유롭다.
즉 employee_list[i]->print(); 에서 manager 객체가 employ_list일때, print()는 employee의 class 안에 있기 때문에,
manager가 employ_list임에도 print는 employee class 함수에서 작동이 된다.

이 문제 해결 > virtual

virtual void what() { std::cout << "기반 클래스의 what()" << std::endl; }

Base p;
Derived c;

Base* p_c = &c;
Base* p_p = &p;

std::cout << " == 실제 객체는 Base == " << std::endl;
p_p->what();

std::cout << " == 실제 객체는 Derived == " << std::endl;
p_c->what();

virtual을 사용하면, 기존에는 p_p, p_c 모두 base의 what을 작동시켰을텐데, virtual이 들어감에 따라
해당 포인터 변수가 무엇을 가리키고 있느냐에 따른 값이 출력된다 > 즉 p_c는 derived의 what이 출력되고,
p_p는 base의 what이 출력된다.
이처럼 런타임에서 타입이 결정되는것이 동적 바인딩이라고 불린다 > virtual.

p_c->what(); 런타임 해석
"흠, p_c 는 Base 포인터니까 Base 의 what() 을 실행해야지"
"어 근데 what 이 virtual 이네?"

"잠깐. 이거 실제 Base 객체 맞어? 아니네 Derived 객체네"
"그럼 Derived 의 what 을 실행해야지"

정적 바인딩은 런타임 때 결정 나는 것이 아닌, 어떤 함수 호출에 따라 정해지는 것.

virtual의 위치는 동적 바인딩이 요구되는 함수에 붙인다. 보통 상속 되는 쪽에 붙이는 거 같다
또한 런타임이 판단하기에, 상속이 발생한 두 class 내부에서 기능은 같은데, 다른 함수로 판단이 되는 경우
즉 어떤거는 그냥이고 어떤거는 const로 런타임이 다른 함수로 판단한다.
따라서 override을 적어서, 이건 override가 요구되는 함수라고 알려주고, 만약 문제가 발생한다면, 이는 override 상황이
아닌것으로 error check이 가능하다
만약 override 안쓰고, 당연히 override되겠지로 하고 compile했는데 이상한 값이 나오면 큰 문제 발생 > 사전 방지용이다.

virtual 사용하려면, 두 class에서 상속되는 함수가 같은 이름이여야한다. > 컴파일이 같은 함수라고 판단해야함
const도 다른 함수로 판단한다.
*/