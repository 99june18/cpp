#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

class employee {
private:
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
	void print();
	//월급 계산
	int pay();
};
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// 
//기본 생성자
employee::employee(std::string _name, int _age, std::string _position, int _rank) {
	name = _name;
	age = _age;
	position = _position;
	rank = _rank;
}

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

class manager {
private:
	std::string name;
	int age;

	std::string position;
	int rank;
	int year;

public:
	//기본 생성자
	manager(std::string _name, int _age, std::string _position, int _rank, int _year);
	//복사 생성자
	manager(const manager& s);
	//정보 보여주는 함수
	void print();
	//월급 계산
	int pay_manager();


};

manager::manager(std::string _name, int _age, std::string _position, int _rank, int _year) {
	name = _name;
	age = _age;
	position = _position;
	rank = _rank;
	year = _year;
}

manager::manager(const manager& s) {
	name = s.name;
	age = s.age;
	position = s.position;
	rank = s.rank;
	year = s.year;
}

int manager::pay_manager() {
	return (200 + rank * 50 + 5 * year);
}

void manager::print() {
	std::cout << "이름 : " << name << std::endl;
	std::cout << "나이 : " << age << std::endl;
	std::cout << "직책 : " << position << std::endl;
	std::cout << "등급 : " << rank << std::endl;
	std::cout << "월급 : " << pay_manager() << std::endl;
	std::cout << "년도 : " << year << std::endl;
	std::cout << "-------------------" << std::endl;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

class employeelist{
private:
	int alloc_employee;        // 할당한 총 직원 수
	int current_employee;      // 현재 직원 수
	employee** employee_list; //employee class 가리키며, 배열구조 > ** 2개

	int current_manager;
	manager** manager_list;

public:
	//기본 생성자 employee class의 matrix가 생성됨
	employeelist(int alloc_employee);
	//employee 추가
	void add_employ(employee* employ);
	//manager 추가
	void add_manager(manager* manage);
	//print
	int current_num() const;
	//print info
	void print_employ() const;

	~employeelist();

};

employeelist::employeelist(int _alloc_employee) {
	alloc_employee = _alloc_employee;
	current_employee = 0;
	current_manager = 0;

	employee_list = new employee*[alloc_employee];
	manager_list = new manager * [alloc_employee];
}
//employee 추가
//employee class를 받아서, 대입시킨다.
void employeelist::add_employ(employee* employ) {
	int temp;

	employee_list[current_employee] = employ;
	current_employee++;
}

void employeelist::add_manager(manager* manage) {
	int temp;

	manager_list[current_manager] = manage;
	current_manager++;
}

int employeelist::current_num() const {
	return current_employee + current_manager;
}

void employeelist::print_employ() const {
	int total_pay = 0;

	for (int i = 0; i < current_employee; i++)
	{
		employee_list[i]->print();
		total_pay += employee_list[i]->pay();
	}

	for (int i = 0; i < current_manager; i++)
	{
		manager_list[i]->print();
		total_pay += manager_list[i]->pay_manager();
	}

	std::cout << "총 인원 : " << current_employee + current_manager << std::endl;
	std::cout << "총 지출 : " << total_pay << std::endl;
}

employeelist::~employeelist() {
	delete[] employee_list;
	delete[] manager_list;
}

int main() {
	employeelist size(10);
	employee s1("노홍철", 34, "평사원", 1);
	employee s2("하하", 34, "평사원", 1);
	manager s3("유재석", 41, "부장", 7, 12);
	manager s4("정준하", 43, "과장", 4, 13);
	manager s5("박명수", 43, "차장", 5, 15);
	employee s6("정형돈", 36, "대리", 2);
	employee s7("길", 36, "인턴", -2);

	size.add_employ(&s1);
	size.add_employ(&s2);
	size.add_manager(&s3);
	size.add_manager(&s4);
	size.add_manager(&s5);
	size.add_employ(&s6);
	size.add_employ(&s7);

	size.print_employ();
}

/*
이전 시간에 구현한 string이라는 class를 header로 구현한 것이 있다 #include <string>
또한 이는 표준이므로 std::string을 붙여서 사용해야 한다. 또한 해당 string으로 지정된 변수의 경우,
해당 header에 저장되어 있는 여럿 함수를 사용할 수 있다. > a.뭐뭐 하면 여러 함수들 나온다.
ex) length, 연산자 오버로딩도 있다. > 이 밖에도 여러 함수가 있으므로, 문자열 사용시, 유용하게 사용해라.
	std::string a = "abc";
	std::string b = "def";
	std::string c = a;

	std::cout << "a의 길이 : " << a.length() << std::endl;

	std::cout << "합쳐 : " << a + b << std::endl;

사원관리 프로그램
다른 class의 사용하고자 한다면, (class 이름)* (임의) 이런 식으로 사용하려는 class을 가리키는 식으로 사용된다
만약 해당 class의 matrix을 사용하려면 ** 2개를 붙여서 사용한다. 
즉 원하는 class을 사용하고자 하면, *로 표현해줘야 한다.
또한 다른 class의 함수를 불러오고 있다면, ->를 사용해줘서 가져온다. 
더 추가적인 내용은 코드 분석하면서 익히기

상속
비슷한 코드 형식의 클래스 2개를 작성할 때, 복붙이 아닌 상속을 사용하여, 다른 클래스의 내용을 그대로 포함랗 수 있는 작업
을 수행 할 수 있는 것이 상속이다. > 다른 클래스의 무언가를 물려받아 사용한다.

class Base {
  std::string s;

 public:
  Base() : s("기반") {  std::cout << "기반 클래스" <<  std::endl; }

  void what() {  std::cout << s <<  std::endl; }
};

class Derived : public Base {
  std::string s;

 public:
  Derived() : Base(), s("파생") {
	 std::cout << "파생 클래스" <<  std::endl;

	// Base 에서 what() 을 물려 받았으므로
	// Derived 에서 당연히 호출 가능하다
	what();
  }
};

에서 class Derived : public Base, 즉 derived class에서 base class를 public 형태로 상속하겟다는 의미
또한 중요한 점은 derived 생성자에서, 상속하고자 하는 class의 생성자를 먼저 초기화 한 후, 자신의 변수를 생성해
줘야 한다는 특징을 가진다.

따라서 생성 순서 : Base 생성자 > derived 생성자 > what() 함수 순
what 함수의 s는 base꺼여서 base에서 지정한 값이 출력되고, 만약 derived에도 what 함수가 있다면, 그 땐
멀리 가지 않고, derived에 있는 what 함수를 사용한다. > overriding

여기서 만약, 상속 받은 class에서 상속하는 class의 private에 접근이 가능한가? > x
하지만 protected라는 것을 사용한다면, 상속받은 class에서 직접 상속하는 class의 private에 접근이 가능하며,
나머지 경우에는 불가능 > 즉 private와 public의 중간 단계라고 볼 수 있다.
private을 protected로 선언하면 된다.

또한 public으로 상속된다는 것은 접근이 그대로 유지, protected로 상속 > public은 protected로 바뀐다
private로 상속 > 모든 지시자들이 private로 바뀐다. 즉 선언한거 이상의 값들만 접근이 가능하게 된다.

그 밖에 상속된 class의 변수, 함수 모두 상속한 class 내부에서 사용 가능하다.
*/