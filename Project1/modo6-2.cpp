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
	//�⺻ ������
	employee(std::string name, int age, std::string position, int rank);
	//���� ������
	employee(const employee& s);
	//���� �����ִ� �Լ�
	virtual void print();
	//���� ���
	virtual int pay();
};
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// 
//�⺻ ������
employee::employee(std::string name, int age, std::string position, int rank)
	: name(name), age(age), position(position), rank(rank) {}

//���� ������
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
	std::cout << "�̸� : " << name << std::endl;
	std::cout << "���� : " << age << std::endl;
	std::cout << "��å : " << position << std::endl;
	std::cout << "��� : " << rank << std::endl;
	std::cout << "���� : " << pay() << std::endl;
	std::cout << "-------------------" << std::endl;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

class manager : public employee {
private:
	int year;

public:
	//�⺻ ������
	manager(std::string name, int age, std::string position, int rank, int year);
	//���� ������
	manager(const manager& s);
	//���� �����ִ� �Լ�
	void print() override; //override �Ƚᵵ ���ư��µ�, error ����������̴�.
	//���� ���
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
	std::cout << "�̸� : " << name << std::endl;
	std::cout << "���� : " << age << std::endl;
	std::cout << "��å : " << position << std::endl;
	std::cout << "��� : " << rank << std::endl;
	std::cout << "���� : " << pay() << std::endl;
	std::cout << "�⵵ : " << year << std::endl;
	std::cout << "-------------------" << std::endl;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

class employeelist {
private:
	int alloc_employee;        // �Ҵ��� �� ���� ��
	int current_employee;      // ���� ���� ��
	employee** employee_list; //employee class ����Ű��, �迭���� > ** 2��

public:
	//�⺻ ������ employee class�� matrix�� ������
	employeelist(int alloc_employee);
	//employee �߰�
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

//employee �߰�
//employee class�� �޾Ƽ�, ���Խ�Ų��.
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

	std::cout << "�� �ο� : " << current_employee << std::endl;
	std::cout << "�� ���� : " << total_pay << std::endl;
}

employeelist::~employeelist() {
	delete[] employee_list;
}

int main() {
	employeelist size(10);
	employee s1("��ȫö", 34, "����", 1);
	employee s2("����", 34, "����", 1);
	manager s3("���缮", 41, "����", 7, 12);
	manager s4("������", 43, "����", 4, 15);
	manager s5("�ڸ��", 43, "����", 5, 13);
	employee s6("������", 36, "�븮", 2);
	employee s7("��", 36, "����", -2);

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
����� ����ϴ� ���� : ��ü���� ���α׷��ֿ��� �߱��ϴ� ���� ��ü�� �߻�ȭ�� ȿ�����̴�
�� ����ü���� ���踦 ǥ���� �� �ְ� �Ǿ���.
�� is a���踦 �Ѵ�. ���÷� class manager : public employee > manager is a employee
manager class�� employee class�� �ִ� ��� ���� ���� �� �� �ִ�.
ȭ��ǥ�� ǥ�����ڸ�, ��� ���� class -> ��� �Ǵ� class
+ ��� �޴� ����ü�� ��� �Ǵ� ����ü�� ���� �� ��üȭ,Ư��ȭ �Ǵ� ������ �ִ�.

is a ������ ��� ����, has a ������ ��ӵ� �ִ�. �̴� �ƿ� ��� �Ǵ� class�� �����ϰ� �ִ�.
�� ���÷� car�̶�� class �ȿ�, brake class, engine class���� �ƿ� ���ԵǾ� �ִ� ���¸� �ǹ��Ѵ�.
C++ ���α׷��ֿ��� "is-a" ����� Ŭ���� ���� ��� ���踦 ��Ÿ����, 
"has-a" ����� Ŭ���� ���ο��� �ٸ� Ŭ���� ��ü�� �����ϴ� ���踦 �ǹ��մϴ�

������ ��� ��� > Base* p_c = &c; ������ ���� base class �������� p_c�� derived class�� ��ü c�� ����Ų��.
�̶� p_c�� base�� ������ �̹Ƿ�, what() �Լ��� base�� �ִ� ���� ��µȴ�.
�̴� p_c�� derived class�� ����Ű�� �ִ� ���¿���, p_c�� base�� what �Լ��� �θ���, derived class�� base what() �Լ���
�־�߸� ������ �ȴ�.
�ٵ� ���� Derived* p_p = &p;  p_p->what(); �� �ȴٸ�, p_p�� base ��ü�� ����Ű�� �ְ�, p_p�� derived class�� what�Լ�
�� �θ���, base Ŭ������ derived class �Լ��� what�� �־�߸� ������ �Ǵµ�, �̴� �ٿ� ĳ�����̱� ������ ������ �ȴ�.
�� ��� �Ǵ� ���� �����Ͱ� ��� �ϴ� ���� ��ü�� ����Ű�� ���� ok, ������ �� �ݴ�� �Ұ�

# Ÿ���� �ٲٴ� ����ȯ���� static_cast<�ٲٷ��� �ϴ� Ÿ��>(���);���� �����Ѵ�.
static_cast<Derived*>(p_p); > p_p�� Derived* �� ����ȯ
���⼭ ĳ���� ������ �̿��� ���� �ϴ� dynamic_cast���� > ������ ���� ĳ������ �Ǵ����� Ȯ�κ��� �ϴ� ��

�ٽ� ���ư���, �� ĳ������ �����Ӵٰ� �Ͽ��⿡, employee�� manager�� ��ü�� ����Ű�� ���� �����Ӵ�.
�� employee_list[i]->print(); ���� manager ��ü�� employ_list�϶�, print()�� employee�� class �ȿ� �ֱ� ������,
manager�� employ_list�ӿ��� print�� employee class �Լ����� �۵��� �ȴ�.

�� ���� �ذ� > virtual

virtual void what() { std::cout << "��� Ŭ������ what()" << std::endl; }

Base p;
Derived c;

Base* p_c = &c;
Base* p_p = &p;

std::cout << " == ���� ��ü�� Base == " << std::endl;
p_p->what();

std::cout << " == ���� ��ü�� Derived == " << std::endl;
p_c->what();

virtual�� ����ϸ�, �������� p_p, p_c ��� base�� what�� �۵��������ٵ�, virtual�� ���� ����
�ش� ������ ������ ������ ����Ű�� �ִ��Ŀ� ���� ���� ��µȴ� > �� p_c�� derived�� what�� ��µǰ�,
p_p�� base�� what�� ��µȴ�.
��ó�� ��Ÿ�ӿ��� Ÿ���� �����Ǵ°��� ���� ���ε��̶�� �Ҹ��� > virtual.

p_c->what(); ��Ÿ�� �ؼ�
"��, p_c �� Base �����ʹϱ� Base �� what() �� �����ؾ���"
"�� �ٵ� what �� virtual �̳�?"

"���. �̰� ���� Base ��ü �¾�? �ƴϳ� Derived ��ü��"
"�׷� Derived �� what �� �����ؾ���"

���� ���ε��� ��Ÿ�� �� ���� ���� ���� �ƴ�, � �Լ� ȣ�⿡ ���� �������� ��.

virtual�� ��ġ�� ���� ���ε��� �䱸�Ǵ� �Լ��� ���δ�. ���� ��� �Ǵ� �ʿ� ���̴� �� ����
���� ��Ÿ���� �Ǵ��ϱ⿡, ����� �߻��� �� class ���ο��� ����� ������, �ٸ� �Լ��� �Ǵ��� �Ǵ� ���
�� ��Ŵ� �׳��̰� ��Ŵ� const�� ��Ÿ���� �ٸ� �Լ��� �Ǵ��Ѵ�.
���� override�� ���, �̰� override�� �䱸�Ǵ� �Լ���� �˷��ְ�, ���� ������ �߻��Ѵٸ�, �̴� override ��Ȳ��
�ƴѰ����� error check�� �����ϴ�
���� override �Ⱦ���, �翬�� override�ǰ����� �ϰ� compile�ߴµ� �̻��� ���� ������ ū ���� �߻� > ���� �������̴�.

virtual ����Ϸ���, �� class���� ��ӵǴ� �Լ��� ���� �̸��̿����Ѵ�. > �������� ���� �Լ���� �Ǵ��ؾ���
const�� �ٸ� �Լ��� �Ǵ��Ѵ�.
*/