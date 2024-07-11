#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>


class MyString
{
	int capacity;
	int length;
	char* memory; //���ڿ� ���� ����

public:
	//char - ���ڿ� ����
	MyString(char string);

	//string - ����
	MyString(const char* source);

	//���� ������
	MyString(const MyString& str);

	//���ڿ� ���� ���ϱ�
	int stringlength() const;

	//assign �Լ� (����)
	MyString& assign(const MyString& str);
	//assign for const
	MyString& assign(const char* str);

	//Ư�� ��ġ get
	char get(int i) const;

	//��ġ �ֱ�
	MyString& append(const MyString& str);

	//erase �Լ�
	MyString& erase(int num);

	//find �Լ�
	int find(const MyString& str) const;

	//compare �Լ�
	int compare(const MyString& str) const;

	~MyString();

	void print() const;

};

MyString::MyString(char string)
{
	std::cout << "����" << std::endl;
	memory = new char[1];
	memory[0] = string;
	length = 1;
}

MyString::MyString(const char* source) {

	std::cout << "���ڿ�" << std::endl;
	length = strlen(source);
	capacity = length;
	memory = new char[length];
	for (int i = 0; i < length; i++) {
		memory[i] = source[i];
	}
}

MyString::MyString(const MyString& str) {
	std::cout << "����" << std::endl;
	length = str.length;
	memory = new char[length];

	for (int i = 0; i < length; i++) {
		memory[i] = str.memory[i];
	}
}

int MyString::stringlength() const {
	return length;
}

MyString& MyString::assign(const MyString& str) {
	if (str.length > length) {
		std::cout << "�� ���� �Ҵ�" << std::endl;
		delete[]memory;
		memory = new char[str.length];
	}

	length = str.length;

	for (int i = 0; i < length; i++)
	{
		memory[i] = str.memory[i];
	}
	std::cout << "assign �Ϸ�" << std::endl;

	return *this;
}

MyString& MyString::assign(const char* str) {
	int new_length = strlen(str);

	if (new_length > length) {
		std::cout << "�� ���� �Ҵ�" << std::endl;
		delete[]memory;
		memory = new char[new_length];
	}

	length = new_length;

	for (int i = 0; i < length; i++)
	{
		memory[i] = str[i];
	}
	std::cout << "assign �Ϸ�" << std::endl;
	return*this;
}

char MyString::get(int i) const {
	if (i > length || i < 0)
	{
		return NULL;
	}
	else
	{
		std::cout << memory[i] << std::endl;
		return memory[i];
	}
}

MyString& MyString::append(const MyString& str) {

	if (length + str.length > capacity) {
		// ���� ���Ӱ� �������� �Ҵ��� �ؾ� �Ѵ�.
		capacity = length + str.length;

		char* prev_string_content = memory;
		memory = new char[capacity];

		// �ϴ� insert �Ǵ� �κ� ���������� ������ �����Ѵ�.
		int i;
		for (i = 0; i < length; i++) {
			memory[i] = prev_string_content[i];
		}

		// �׸��� ���ӿ� insert �Ǵ� ���ڿ��� �ִ´�.
		for (int j = 0; j != str.length; j++) {
			memory[i + j] = str.memory[j];
		}

		delete[] prev_string_content;

		length = length + str.length;
		return *this;
	}
	else {
		for (int i = 0; i < length; i++) {
			memory[i] = str.memory[i];
		}
		length = length + str.length;
		return *this;
	}
}

MyString& MyString::erase(int num) {
	char* contain = memory;

	memory = new char[length - num];

	length -= num;

	for (int i = 0; i < length; i++)
	{
		memory[i] = contain[i];
	}
	return *this;
}

int MyString::find(const MyString& str) const {
	int i, j;

	for (i = 0; i <= length; i++) {
		for (j = 0; j < str.length; j++) {
			if (memory[i + j] != str.memory[j]) break;
		}

		if (j == str.length) return (i + 1);
	}

	return -1;
}

int MyString::compare(const MyString& str) const {
	for (int i = 0; i < std::min(length, str.length); i++)
	{
		if (memory[i] < str.memory[i]) {
			return 1;
		}
		else return -1;
	}

	if (length == str.length) return 0;

	if (length < str.length) {
		return 1;
	}
	else return -1;

	// ��ü�� �� ũ�� 1, �Լ��� ���ԵǴ� ��ü�� �� ũ�� -1
}

MyString::~MyString()
{
	std::cout << "�޸� ����" << std::endl;
	delete[] memory;
}

void MyString::print() const {
	for (int i = 0; i < length; i++)
	{
		std::cout << memory[i];
	}
	std::cout << "\n";
	std::cout << "���� : " << length << std::endl;
}

int main() {
	MyString str1("abcd");
	MyString str2("abc");

	std::cout << str1.compare(str2) << std::endl;
}


/* ���ڿ� ����,���� : ���ڿ� Ŭ����
* ������ ����� ���� ���� = char�� ���������, cpp���� string�̶�� �ش�
* �� �����ϰ� �־�, include <string>���� ���ڿ��� �ۼ��� �� �ִ�
* ������ ���⼱ ������ ���ڿ��� �����ϴ� class�� ������� �Ѵ�.
*
* ���� ��� ������ ���� ��ȭ���� �ʴ´ٸ�, const �Լ��� ����!!!

 assign �Լ� (=�� ������ ������ �Ѵ�)
 str.assign("str")
 ȣ���� ��ü�� �������� ������ ���Ѵٸ�, ���۷��� �Լ� ����, *this ��ȯ ���
 �׳� �Լ��� ������ ���, ���纻�� ��ȯ�Ѵ�.

 �޸� �Ҵ��� ��, ������ memory �ʱ�ȭ ��, �Է��� �� ���, delay�� ũ�� ������
 �ѹ��� �� ũ�� �÷� ���� ������, �����Ѵ�. > �� 2�� ���� �÷� ���´�.




 �Լ��� ���� ����� ���鼭 �����ϱ�
 */