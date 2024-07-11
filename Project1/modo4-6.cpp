#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

class MyString {
    char* string_content;  // ���ڿ� �����͸� ����Ű�� ������
    int string_length;     // ���ڿ� ����

    mutable int memory_capacity;

public:
    // capacity ��ŭ �̸� �Ҵ���.
    explicit MyString(int capacity);

    // ���ڿ��� ���� ����
    MyString(const char* str);

    // ���� ������
    MyString(const MyString& str);

    ~MyString();

    int length() const;

    int capacity() const;

    void show() const;
};

MyString::MyString(int capacity) {
    string_content = new char[capacity];
    string_length = 0;
    memory_capacity = capacity;
    std::cout << "capacity : " << memory_capacity << std::endl;
}

MyString::MyString(const char* str) {
    string_length = 0;
    while (str[string_length++]) {
    }

    string_content = new char[string_length];
    memory_capacity = string_length;

    for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}

MyString::MyString(const MyString& str) {
    string_length = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++)
        string_content[i] = str.string_content[i];
}

MyString::~MyString() { delete[] string_content; }

int MyString::length() const { return string_length; }

int MyString::capacity() const { 
    std::cout << "�ٲٱ� �� �뷮 : " << memory_capacity << std::endl;

    memory_capacity = 3;

    return memory_capacity; 
}


void MyString::show() const {
    std::cout << "�뷮1: " << memory_capacity << std::endl;
}

void dosomething(MyString s) {
    int memory_capacity = 3;
    //���纻�̶� show�� �ص�, �̻��� ���� ���´�.
    s.show();
}

int main() {
    MyString str(9);
    dosomething(str); //���纻���� ���� ������, ���ٸ� ���� ���´�.
    str.capacity();
    str.show();
}

/*
string class ��������, �̸� capacity�� �Ҵ��ϴ� ��쿡 ���Ͽ�, ���� MyString�� ���ڷ� �޴� ��츦 �����غ���

void DoSomethingWithString(MyString s) {
  // Do something...
}

DoSomethingWithString(MyString("abc")) ��ġ �̿� ����. ������ DoSomethingWithString("abc")�� ���� �Ҵ��� ����?
�� mystring�� ��������� �������� �ʾ��� ��츦 �ǹ��Ѵ�.
"abc"�� Mystring�� �������� �𸣴� ��� ���� �����Ѱ�? >> mystring�� ������ �� ���ڿ��� ����� �����ڸ� Ȱ���Ͽ�,
�̸� �Ͻ��� ��ȯ�� �߻��Ѵ�.
���� DoSomethingWithString(3)�� ����Ѵٸ�, ���� mystring ���ڰ� ���� �� ���� �ٸ� ���� ���ٰ� �ϴ���, ����
�� ���ڰ� ������ �� �ִ� �����ڰ� �ִٸ�, �ش� �����ڸ� Ȱ���Ͽ�, ����.
�� 3�� capacity�� �����ϴ� �����ڸ� Ÿ�� ���� DoSomethingWithString(MyString(3))���� �����ȴ�.
������ �̷��� ������ ���� �ǵ�ġ �ʰ� ��ȯ�� �� ���� ������, �����ؾ� �Ѵ�.
 > �̷��� �ǵ�ġ ���� ��ȯ�� �����ִ� ���� �ٷ� explict Ű����

 explicit�� class �ܺ� �Լ����� ��ü�� ����� �Լ��� ������, main�Լ����� ��ü ������ ������� �ʰ�, �Ͻ������� 
 ��ü ���� �Լ��� ���� ��ü �����ϴ� ��츦 ���� �ϱ� ���� ���ȴ�. 
 ex) void DoSomethingWithString(MyString s) {
  // Do something...
}
int main() {
  DoSomethingWithString(3);  // ????
}

dosomething�̶�� �Լ����� s ��ü�� �����. �׸��� main�Լ������� ��ü�� ���� �������� �ʴ´�.
main���� dosomething�� 3�� �ΰ��Ѵٴ� ���� MyString s(3)���� ��ü & �����ڸ� ��ȯ�� ������ �Ͻ������� �����ִ� ���̴�.
������ s(3)�� ����� class�� �����ڰ� explicit�� ����ϰ� �ִٸ�, �ش� �۾��� ���� �ʴ´�.
�׷��ٸ� main���� ���� MyString s(3)�� ��ü�� ������ ��, ���Խ��Ѿ� �Ѵ�.

###### class ��ü�� ����� �ܺ� �Լ��� ���, class������ ������ ����, class �Լ��� ����� �� �ִ�.###\
���� �̴� ���纻�̱� ������, class���� �ο��� ������ ��ȭ�� ����, �� �Լ� ���ο��� ���纻���� ��ȭ���� > �������� ��ȭ x

mutable
const�� ������ �Լ������� ��� ������ ������ �� �ֵ��� �ϴ� ��, ������� ���� �Ұ��ϴ�.
���� read�ϴ� �Լ��� ���� ���� ��ȭ�� �䱸���� �ʴ� ���, ���� const�� ����Ѵ�.
������ Ư�� ���ǿ� ���Ͽ�, ���� ������ �䱸�Ǵ� ��쵵 ���� �� �ִ� > ���÷� cache�� �����.
�̶� �Լ��� const�� ���� �ͺ���, �ش� �������� mutable�� �������ָ�, ��ȭ�� �䱸�Ǵ� �͸� ��ȯ�� �����ϸ�, 
�Լ� ��ü�� const�� ���� �� �� �ִ�.

*/