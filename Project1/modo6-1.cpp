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
	//�⺻ ������
	employee(std::string name, int age, std::string position, int rank);
	//���� ������
	employee(const employee& s);
	//���� �����ִ� �Լ�
	void print();
	//���� ���
	int pay();
};
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// 
//�⺻ ������
employee::employee(std::string _name, int _age, std::string _position, int _rank) {
	name = _name;
	age = _age;
	position = _position;
	rank = _rank;
}

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

class manager {
private:
	std::string name;
	int age;

	std::string position;
	int rank;
	int year;

public:
	//�⺻ ������
	manager(std::string _name, int _age, std::string _position, int _rank, int _year);
	//���� ������
	manager(const manager& s);
	//���� �����ִ� �Լ�
	void print();
	//���� ���
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
	std::cout << "�̸� : " << name << std::endl;
	std::cout << "���� : " << age << std::endl;
	std::cout << "��å : " << position << std::endl;
	std::cout << "��� : " << rank << std::endl;
	std::cout << "���� : " << pay_manager() << std::endl;
	std::cout << "�⵵ : " << year << std::endl;
	std::cout << "-------------------" << std::endl;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

class employeelist{
private:
	int alloc_employee;        // �Ҵ��� �� ���� ��
	int current_employee;      // ���� ���� ��
	employee** employee_list; //employee class ����Ű��, �迭���� > ** 2��

	int current_manager;
	manager** manager_list;

public:
	//�⺻ ������ employee class�� matrix�� ������
	employeelist(int alloc_employee);
	//employee �߰�
	void add_employ(employee* employ);
	//manager �߰�
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
//employee �߰�
//employee class�� �޾Ƽ�, ���Խ�Ų��.
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

	std::cout << "�� �ο� : " << current_employee + current_manager << std::endl;
	std::cout << "�� ���� : " << total_pay << std::endl;
}

employeelist::~employeelist() {
	delete[] employee_list;
	delete[] manager_list;
}

int main() {
	employeelist size(10);
	employee s1("��ȫö", 34, "����", 1);
	employee s2("����", 34, "����", 1);
	manager s3("���缮", 41, "����", 7, 12);
	manager s4("������", 43, "����", 4, 13);
	manager s5("�ڸ��", 43, "����", 5, 15);
	employee s6("������", 36, "�븮", 2);
	employee s7("��", 36, "����", -2);

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
���� �ð��� ������ string�̶�� class�� header�� ������ ���� �ִ� #include <string>
���� �̴� ǥ���̹Ƿ� std::string�� �ٿ��� ����ؾ� �Ѵ�. ���� �ش� string���� ������ ������ ���,
�ش� header�� ����Ǿ� �ִ� ���� �Լ��� ����� �� �ִ�. > a.���� �ϸ� ���� �Լ��� ���´�.
ex) length, ������ �����ε��� �ִ�. > �� �ۿ��� ���� �Լ��� �����Ƿ�, ���ڿ� ����, �����ϰ� ����ض�.
	std::string a = "abc";
	std::string b = "def";
	std::string c = a;

	std::cout << "a�� ���� : " << a.length() << std::endl;

	std::cout << "���� : " << a + b << std::endl;

������� ���α׷�
�ٸ� class�� ����ϰ��� �Ѵٸ�, (class �̸�)* (����) �̷� ������ ����Ϸ��� class�� ����Ű�� ������ ���ȴ�
���� �ش� class�� matrix�� ����Ϸ��� ** 2���� �ٿ��� ����Ѵ�. 
�� ���ϴ� class�� ����ϰ��� �ϸ�, *�� ǥ������� �Ѵ�.
���� �ٸ� class�� �Լ��� �ҷ����� �ִٸ�, ->�� ������༭ �����´�. 
�� �߰����� ������ �ڵ� �м��ϸ鼭 ������

���
����� �ڵ� ������ Ŭ���� 2���� �ۼ��� ��, ������ �ƴ� ����� ����Ͽ�, �ٸ� Ŭ������ ������ �״�� ���Զ� �� �ִ� �۾�
�� ���� �� �� �ִ� ���� ����̴�. > �ٸ� Ŭ������ ���𰡸� �����޾� ����Ѵ�.

class Base {
  std::string s;

 public:
  Base() : s("���") {  std::cout << "��� Ŭ����" <<  std::endl; }

  void what() {  std::cout << s <<  std::endl; }
};

class Derived : public Base {
  std::string s;

 public:
  Derived() : Base(), s("�Ļ�") {
	 std::cout << "�Ļ� Ŭ����" <<  std::endl;

	// Base ���� what() �� ���� �޾����Ƿ�
	// Derived ���� �翬�� ȣ�� �����ϴ�
	what();
  }
};

���� class Derived : public Base, �� derived class���� base class�� public ���·� ����ϰٴٴ� �ǹ�
���� �߿��� ���� derived �����ڿ���, ����ϰ��� �ϴ� class�� �����ڸ� ���� �ʱ�ȭ �� ��, �ڽ��� ������ ������
��� �Ѵٴ� Ư¡�� ������.

���� ���� ���� : Base ������ > derived ������ > what() �Լ� ��
what �Լ��� s�� base������ base���� ������ ���� ��µǰ�, ���� derived���� what �Լ��� �ִٸ�, �� ��
�ָ� ���� �ʰ�, derived�� �ִ� what �Լ��� ����Ѵ�. > overriding

���⼭ ����, ��� ���� class���� ����ϴ� class�� private�� ������ �����Ѱ�? > x
������ protected��� ���� ����Ѵٸ�, ��ӹ��� class���� ���� ����ϴ� class�� private�� ������ �����ϸ�,
������ ��쿡�� �Ұ��� > �� private�� public�� �߰� �ܰ��� �� �� �ִ�.
private�� protected�� �����ϸ� �ȴ�.

���� public���� ��ӵȴٴ� ���� ������ �״�� ����, protected�� ��� > public�� protected�� �ٲ��
private�� ��� > ��� �����ڵ��� private�� �ٲ��. �� �����Ѱ� �̻��� ���鸸 ������ �����ϰ� �ȴ�.

�� �ۿ� ��ӵ� class�� ����, �Լ� ��� ����� class ���ο��� ��� �����ϴ�.
*/