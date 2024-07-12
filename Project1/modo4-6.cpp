#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

class MyString {
    char* string_content;  // 문자열 데이터를 가리키는 포인터
    int string_length;     // 문자열 길이

    mutable int memory_capacity;

public:
    // capacity 만큼 미리 할당함.
    explicit MyString(int capacity);

    // 문자열로 부터 생성
    MyString(const char* str);

    // 복사 생성자
    MyString(const MyString& str);

    ~MyString();

    int length() const;

    int capacity() const;

    void show() const;

    bool operator==(MyString& str);
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
    std::cout << "바꾸기 전 용량 : " << memory_capacity << std::endl;

    memory_capacity = 3;

    return memory_capacity;
}


void MyString::show() const {
    std::cout << "용량1: " << memory_capacity << std::endl;
}

// 연산자 오버로딩 추가
bool MyString::operator==(MyString& str) {

    for (int i = 0; i < std::min(string_length, str.string_length); i++)
    {
        if (string_content[i] == str.string_content[i]) {
            std::cout << "같다" << std::endl;
            return true;
        }
        else
        {
            std::cout << "다르다" << std::endl;
            return false;
        }
    }
}

void dosomething(MyString s) {
    int memory_capacity = 3;
    //복사본이라 show를 해도, 이상한 값이 나온다.
    s.show();
}

int main() {
    MyString str(9);
    dosomething(str); //복사본으로 들어가기 문에, 색다른 값이 나온다.
    str.capacity();
    str.show();


    MyString str1("a word");
    MyString str2("sentence");
    MyString str3("sentence");

    if (str1 == str2)
        std::cout << "str1 와 str2 같다." << std::endl;
    else
        std::cout << "st1 와 str2 는 다르다." << std::endl;

    if (str2 == str3)
        std::cout << "str2 와 str3 는 같다." << std::endl;
    else
        std::cout << "st2 와 str3 는 다르다" << std::endl;

}

/*
string class 생성에서, 미리 capacity를 할당하는 경우에 대하여, 만약 MyString을 인자로 받는 경우를 생각해보자

void DoSomethingWithString(MyString s) {
  // Do something...
}

DoSomethingWithString(MyString("abc")) 마치 이와 같다. 하지만 DoSomethingWithString("abc")와 같이 할당한 경우는?
즉 mystring을 명시적으로 생성하지 않앗을 경우를 의미한다.
"abc"가 Mystring의 인자인지 모르는 경우 역시 가능한가? >> mystring의 생성자 중 문자열로 만드는 생성자를 활용하여,
이를 암시적 변환이 발생한다.
역시 DoSomethingWithString(3)를 사용한다면, 원래 mystring 인자가 들어가야 할 곳에 다른 것이 들어갔다고 하더라도, 만약
이 인자가 생성할 수 있는 생성자가 있다면, 해당 생성자를 활용하여, 들어간다.
즉 3은 capacity를 생성하는 생성자를 타고 들어가서 DoSomethingWithString(MyString(3))같이 생성된다.
하지만 이러한 장점이 때론 의도치 않게 변환이 될 수도 있으니, 조심해야 한다.
 > 이런한 의도치 않은 변환을 막아주는 것이 바로 explict 키워드

 explicit는 class 외부 함수에서 객체를 만드는 함수가 있으며, main함수에서 객체 생성을 명시하지 않고, 암시적으로
 객체 생성 함수를 통해 객체 생성하는 경우를 방지 하기 위해 사용된다.
 ex) void DoSomethingWithString(MyString s) {
  // Do something...
}
int main() {
  DoSomethingWithString(3);  // ????
}

dosomething이라는 함수에서 s 객체를 만든다. 그리고 main함수에서는 객체를 따로 생성하지 않는다.
main에서 dosomething에 3을 인가한다는 것은 MyString s(3)으로 객체 & 생성자를 소환한 것으로 암시적으로 보여주는 것이다.
하지만 s(3)을 만드는 class의 생성자가 explicit을 사용하고 있다면, 해당 작업이 되지 않는다.
그렇다면 main에서 직접 MyString s(3)의 객체를 생성한 후, 대입시켜야 한다.

###### class 객체를 만드는 외부 함수의 경우, class내부의 생성자 말고, class 함수를 사용할 수 있다.###\
또한 이는 복사본이기 때문에, class에서 부여한 값에는 변화가 없고, 그 함수 내부에서 복사본으로 변화가능 > 원본에는 변화 x

mutable
const로 정의한 함수에서도 멤버 변수를 변경할 수 있도록 하는 것, 원래라면 변경 불가하다.
값을 read하는 함수와 같이 값의 변화가 요구되지 않는 경우, 보통 const를 사용한다.
하지만 특정 조건에 의하여, 값을 변경이 요구되는 경우도 생길 수 있다 > 예시로 cache를 들었다.
이때 함수의 const를 때는 것보단, 해당 변수값에 mutable을 생성해주면, 변화가 요구되는 것만 변환이 가능하며,
함수 자체는 const로 유지 할 수 있다.

*/