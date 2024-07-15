#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>

class Complex {
private:
    double real, img;

    double get_number(const char* str, int from, int to) const;

public:
    Complex(double real, double img) : real(real), img(img) {}
    Complex(const Complex& c) { real = c.real, img = c.img; }
    Complex(const char* str);

    Complex operator+(const Complex& c) const;
    Complex operator-(const Complex& c) const;
    Complex operator*(const Complex& c) const;
    Complex operator/(const Complex& c) const;

    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);

    Complex& operator=(const Complex& c);

    void println() {
        std::cout << "( " << real << " , " << img << " ) " << std::endl;
    }
};
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
    char* num;
    double value = 0.0;

    if (from > to)
    {
        return 0.0;
    }

    num = new char[to - from];

    if (from == 0) {
        for (int i = from; i <= to; i++)
        {
            num[i] = str[i];
        }
    }
    else
    {
        for (int i = from; i <= to; i++)
        {
            num[i - from] = str[i];
        }
    }
    
    value = atof(num);

    return value;
    
}
Complex Complex::operator+(const Complex& c) const {
    Complex temp(real + c.real, img + c.img);
    return temp;
}
Complex Complex::operator-(const Complex& c) const {
    Complex temp(real - c.real, img - c.img);
    return temp;
}
Complex Complex::operator*(const Complex& c) const {
    Complex temp(real * c.real - img * c.img, real * c.img + img * c.real);
    return temp;
}
Complex Complex::operator/(const Complex& c) const {
    Complex temp(
        (real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
        (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
    return temp;
}

Complex& Complex::operator+=(const Complex& c) {
    (*this) = (*this) + c;
    return *this;
}
Complex& Complex::operator-=(const Complex& c) {
    (*this) = (*this) - c;
    return *this;
}
Complex& Complex::operator*=(const Complex& c) {
    (*this) = (*this) * c;
    return *this;
}
Complex& Complex::operator/=(const Complex& c) {
    (*this) = (*this) / c;
    return *this;
}
Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main() {
    Complex a(0, 0);
    Complex b(0, 0);
    Complex c(0, 0);
    Complex d(0, 0);
    a = a + "-1.1 + i3.923";
    a.println();
    b = b - "1.2-i1.823";
    b.println();
    c = c + "3.4";
    c.println();
    d = d + "-i1.25";
    d.println();
}

/*
c언어에서 사용하던, 연산자들(+,-,==)등은 모두 int,float등의 타입에만 사용되었다. 즉,string 타입에선 사용 불가
하지만 cpp에선 사용자 정의 연산자 사용가능, 즉 이처럼 기존에 사용되었던 타입 말고, 사용자가 정의 할 수 있는
연산자들을 오버로딩이다고 한다. > 연산자 오버로딩

(리턴 타입) operator(연산자) (연산자가 받는 인자) 다음과 같은 형태로 연산자 오버로딩 함수를 만들면 된다.
bool MyString::operator==(MyString& str)

이러면 str1.operator==(str2)와 같이 객체가 함수 정의 형태가 아닌, str1 == str2와 같이 표현이 가능하다
같은 작동 방식,but 더 직관적인 표시가 가능하다.

복소수 class
복사 생성자가 요구된다. 왜냐하면, 그냥 그값으로 연산시, 첫줄에서 연산된 값이 다음 줄에 영향을 가게 되어
이상한 값으로 연산이 진행된다.
따라서 연산자 오버로딩 함수 내부에서, 생성자를 생성자를 따로 지정하여 연산후 다시 지정하는 식으로 설계하여야 한다,
Complex Complex::operator+(const Complex& c) const {
    Complex temp(real + c.real, img + c.img);
    return temp;
}

여기서 temp라는 객체 생성후, real와 img의 손상없이 모든 연산 이후, 생성자가 만들어지기 때문에, 위의 문제와 같은 일은 
발생하지 않는다.
또한 함수가 complex& 꼴이 아닌 이유 역시, 연산하기 전에 값의 변화가 발생하면 안되기 때문에, 그냥 class의 값으로 
리턴이 발생하도록 함수가 설계되었다.

대입 연산자는 객체의 변화가 요구되기 때문에, &꼴로 리턴되게 하였으며, 불필요한 복사가 없어도 된다.

*********** &꼴의 class return과 그냥 class꼴의 return간의 차이를 인지하자 > 더 공부하기 ************** 
*/