#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

/*
class Complex {
private:
    double real, img;

    double get_number(const char* str, int from, int to) const;

public:
    Complex(double real, double img) : real(real), img(img) {}
    Complex(const Complex& c) { real = c.real, img = c.img; }
    Complex(const char* str);

    Complex& operator=(const Complex& c);

    // 나머지 연산자 함수들은 생략 :)

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    // 이제 이 함수는 Complex 의 private 멤버 변수들에 접근할 수 있습니다.
    friend Complex operator+(const Complex& a, const Complex& b);
};

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    std::cout << "( " << c.real << " , " << c.img << " ) ";
    return os;
}

Complex operator+(const Complex& a, const Complex& b) {
    Complex temp(a.real + b.real, a.img + b.img);
    return temp;
}

Complex::Complex(const char* str) {
    // 입력 받은 문자열을 분석하여 real 부분과 img 부분을 찾아야 한다.
    // 문자열의 꼴은 다음과 같습니다 "[부호](실수부)(부호)i(허수부)"
    // 이 때 맨 앞의 부호는 생략 가능합니다. (생략시 + 라 가정)

    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    // 먼저 가장 기준이 되는 'i' 의 위치를 찾는다.
    int pos_i = -1;
    for (int i = 0; i != end; i++) {
        if (str[i] == 'i') {
            pos_i = i;
            break;
        }
    }

    // 만일 'i' 가 없다면 이 수는 실수 뿐이다.
    if (pos_i == -1) {
        real = get_number(str, begin, end - 1);
        return;
    }

    // 만일 'i' 가 있다면,  실수부와 허수부를 나누어서 처리하면 된다.
    real = get_number(str, begin, pos_i - 1);
    img = get_number(str, pos_i + 1, end - 1);

    if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;
}
double Complex::get_number(const char* str, int from, int to) const {
    bool minus = false;
    if (from > to) return 0;

    if (str[from] == '-') minus = true;
    if (str[from] == '-' || str[from] == '+') from++;

    double num = 0.0;
    double decimal = 1.0;

    bool integer_part = true;
    for (int i = from; i <= to; i++) {
        if (isdigit(str[i]) && integer_part) {
            num *= 10.0;
            num += (str[i] - '0');
        }
        else if (str[i] == '.')
            integer_part = false;
        else if (isdigit(str[i]) && !integer_part) {
            decimal /= 10.0;
            num += ((str[i] - '0') * decimal);
        }
        else
            break;  // 그 이외의 이상한 문자들이 올 경우
    }

    if (minus) num *= -1.0;

    return num;
}

Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main() {
    Complex a(0, 0);
    a = "-1.1 + i3.923" + a;
    std::cout << a;
}
*/

class Int {
    int data;

public:
    Int(int data) : data(data) {}
    Int(const Int& i) : data(i.data) {}

    operator int() { return data; }
};
int main() {
    Int x = 3;
    int a = x + 4;

    x = a * 2 + x + 4;
    std::cout << x << std::endl;
}
/*
friend 키워드 > 다른 클래스나 함수들을 접근 할 수 있는 키워드
기존에 다른 class의 private의 경우, 접근이 불가능했지만, friend를 사용하면 private임에도 접근이 가능하다.
class를 friend할 경우, class내부 함수에서 friend class의 객체를 생성하여, 해당 객체의 변수 사용가능하다
함수를 friend 할 경우, 함수 내부에서 객체 생성 후 사용가능.
& friend는 서로 지정하지 않으면 지정한 쪽만 사용가능(like 짝사랑)

이항 연산자
cpp에선 이항 연산자를 *a.operator@(b);, *operator@(a, b); 다음과 같이 2가지로 해석한다.
첫번째는 a의 class 내부 함수를 이용하는 것이며, 두번째는 class 외부 함수를 이용하는 것이다.
즉 두번째를 class에서 사용하고자 한다면, friend를 사용하여야 하는 것이다.
ex) 1+2 에서 2자리에 객체가 들어간다면 첫번째는 해석이 되지 않으며, 
두번째가 해석이 되는데, 이를 class 내부의 private 변수를 사용하기 위해서는 friend 함수를 이용해서 생성해줘야한다.
나머지 경우는 이항 연산자가 2가지로 모두 해석이 된다. 따라서 하나를 삭제해 줘야한다.
(보통 만능이, 두번째꺼이다)

보통 자신을 리턴하는 이항 연산자는 맴버 함수, 아닌 애들은 외부 함수로 정의한다.

입출력 연산자
iostream에 저장되어 있는 << operator를 사용하고 있는데, 기존 header에 있는 operation을 사용하면, std::cout << a 와 같이
객체를 바로 읽는 것이 불가능하였으며, 따라서 우리는 a.print() 함수를 사용했었다.
하지만 만약 해당 << operator를 우리가 지정한 class 내부에서 사용 가능하게 한다면, 위 상황도 가능하게 될 것이다.

std::ostream& operator<<(std::ostream& os, const Complex& c) {
  os << "( " << c.real << " , " << c.img << " ) ";
  return os;
}
다음과 같이 ostream header와 객체를 불러옴으로써, 따로 a.print() 함수 없이도 <<를 사용할 수 있게 되었다.

첨자 연산자 > []  MyString class에서 사용하는 것으로, []안에 들어가는 index을 받으며, char& 형태로 출력한다.

wrapper > 무언가를 싼다 라는 의미로, 기본 자료형들을 객체로써 다루어야 할때, 사용한다.
즉 기본 자료형을 클래스로 포장하여, 각각의 자료형을 객체로 사용하는 것을 의미한다.
타입의 변화 class의 객체로 받은 type을 진짜 int형 타입으로 변환하기 위해서는 다음과 같이 타입 변환 연산자를 
정의해야한다.
operator (변환 하고자 하는 타입) () > operator int() int형 타입으로 변환
이때 주의해야 한 사항은 생성자 처럼 리턴타입이 없다는 점이다.

전위/후위 증감 연산자
a++ / ++a을 나타내는 연산자는 모두 ++이다. 그렇다면 어떻게 동일한 ++로 두가지를 구분하는가?"
전위 : operator++() / 후위 : operator++(int) > 단지 전위, 후위를 구분하기 위해, 변수를 넣는 것이지, 큰 의미 없다.
중요한 사실은 어느값을 리턴해야하는지에 대하여 차이가 있다는 점이다.
전위 연산자의 경우, 값이 바뀐 자신을 리턴해야 하며, 후위 연산자의 경우, 값이 바뀌기 전의 객체를 리턴해야한다.
Test& operator++() {
    x++;
    std::cout << "전위 증감 연산자" << std::endl;
    return *this;
  }

  Test operator++(int) {
    Test temp(*this);
    x++;
    std::cout << "후위 증감 연산자" << std::endl;
    return temp;
  }

  전위는 ++ 진행 후, *this를 리턴하는 반면, 후위는 객체를 생성하여, ++하기전의 객체를 반환해야 한다. temp 객체 생성후,
  객체 반환 후, ++진행하도록 한다.
*/