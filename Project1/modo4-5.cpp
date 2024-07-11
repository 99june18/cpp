#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>


class MyString
{
	int capacity;
	int length;
	char* memory; //문자열 저장 공간

public:
	//char - 문자열 생성
	MyString(char string);

	//string - 생성
	MyString(const char* source);

	//복사 생성자
	MyString(const MyString& str);

	//문자열 길이 구하기
	int stringlength() const;

	//assign 함수 (복사)
	MyString& assign(const MyString& str);
	//assign for const
	MyString& assign(const char* str);

	//특정 위치 get
	char get(int i) const;

	//위치 넣기
	MyString& append(const MyString& str);

	//erase 함수
	MyString& erase(int num);

	//find 함수
	int find(const MyString& str) const;

	//compare 함수
	int compare(const MyString& str) const;

	~MyString();

	void print() const;

};

MyString::MyString(char string)
{
	std::cout << "문자" << std::endl;
	memory = new char[1];
	memory[0] = string;
	length = 1;
}

MyString::MyString(const char* source) {

	std::cout << "문자열" << std::endl;
	length = strlen(source);
	capacity = length;
	memory = new char[length];
	for (int i = 0; i < length; i++) {
		memory[i] = source[i];
	}
}

MyString::MyString(const MyString& str) {
	std::cout << "복사" << std::endl;
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
		std::cout << "새 동적 할당" << std::endl;
		delete[]memory;
		memory = new char[str.length];
	}

	length = str.length;

	for (int i = 0; i < length; i++)
	{
		memory[i] = str.memory[i];
	}
	std::cout << "assign 완료" << std::endl;

	return *this;
}

MyString& MyString::assign(const char* str) {
	int new_length = strlen(str);

	if (new_length > length) {
		std::cout << "새 동적 할당" << std::endl;
		delete[]memory;
		memory = new char[new_length];
	}

	length = new_length;

	for (int i = 0; i < length; i++)
	{
		memory[i] = str[i];
	}
	std::cout << "assign 완료" << std::endl;
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
		// 이제 새롭게 동적으로 할당을 해야 한다.
		capacity = length + str.length;

		char* prev_string_content = memory;
		memory = new char[capacity];

		// 일단 insert 되는 부분 직전까지의 내용을 복사한다.
		int i;
		for (i = 0; i < length; i++) {
			memory[i] = prev_string_content[i];
		}

		// 그리고 새롭에 insert 되는 문자열을 넣는다.
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

	// 객체가 더 크면 1, 함수에 대입되는 객체가 더 크면 -1
}

MyString::~MyString()
{
	std::cout << "메모리 제거" << std::endl;
	delete[] memory;
}

void MyString::print() const {
	for (int i = 0; i < length; i++)
	{
		std::cout << memory[i];
	}
	std::cout << "\n";
	std::cout << "길이 : " << length << std::endl;
}

int main() {
	MyString str1("abcd");
	MyString str2("abc");

	std::cout << str1.compare(str2) << std::endl;
}


/* 문자열 관리,보관 : 문자열 클래스
* 기존에 배웠던 것은 문자 = char를 사용했지만, cpp에선 string이라는 해더
* 를 지원하고 있어, include <string>으로 문자열을 작성할 수 있다
* 하지만 여기선 나만의 문자열을 지원하는 class를 만들고자 한다.
*
* 내부 멤버 변수의 값이 변화하지 않는다면, const 함수로 하자!!!

 assign 함수 (=과 동일한 역할을 한다)
 str.assign("str")
 호출한 객체의 직접적인 수정을 원한다면, 레퍼런스 함수 선언, *this 반환 사용
 그냥 함수로 선언할 경우, 복사본을 반환한다.

 메모리 할당할 때, 여러번 memory 초기화 후, 입력을 할 경우, delay가 크기 때문에
 한번에 좀 크게 늘려 놓은 다음에, 대입한다. > 약 2배 정도 늘려 놓는다.




 함수를 직접 만들어 가면서 이해하기
 */