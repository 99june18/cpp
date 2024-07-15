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

    // ������ ������ �Լ����� ���� :)

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    // ���� �� �Լ��� Complex �� private ��� �����鿡 ������ �� �ֽ��ϴ�.
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
    // �Է� ���� ���ڿ��� �м��Ͽ� real �κа� img �κ��� ã�ƾ� �Ѵ�.
    // ���ڿ��� ���� ������ �����ϴ� "[��ȣ](�Ǽ���)(��ȣ)i(�����)"
    // �� �� �� ���� ��ȣ�� ���� �����մϴ�. (������ + �� ����)

    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    // ���� ���� ������ �Ǵ� 'i' �� ��ġ�� ã�´�.
    int pos_i = -1;
    for (int i = 0; i != end; i++) {
        if (str[i] == 'i') {
            pos_i = i;
            break;
        }
    }

    // ���� 'i' �� ���ٸ� �� ���� �Ǽ� ���̴�.
    if (pos_i == -1) {
        real = get_number(str, begin, end - 1);
        return;
    }

    // ���� 'i' �� �ִٸ�,  �Ǽ��ο� ����θ� ����� ó���ϸ� �ȴ�.
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
            break;  // �� �̿��� �̻��� ���ڵ��� �� ���
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
friend Ű���� > �ٸ� Ŭ������ �Լ����� ���� �� �� �ִ� Ű����
������ �ٸ� class�� private�� ���, ������ �Ұ���������, friend�� ����ϸ� private�ӿ��� ������ �����ϴ�.
class�� friend�� ���, class���� �Լ����� friend class�� ��ü�� �����Ͽ�, �ش� ��ü�� ���� ��밡���ϴ�
�Լ��� friend �� ���, �Լ� ���ο��� ��ü ���� �� ��밡��.
& friend�� ���� �������� ������ ������ �ʸ� ��밡��(like ¦���)

���� ������
cpp���� ���� �����ڸ� *a.operator@(b);, *operator@(a, b); ������ ���� 2������ �ؼ��Ѵ�.
ù��°�� a�� class ���� �Լ��� �̿��ϴ� ���̸�, �ι�°�� class �ܺ� �Լ��� �̿��ϴ� ���̴�.
�� �ι�°�� class���� ����ϰ��� �Ѵٸ�, friend�� ����Ͽ��� �ϴ� ���̴�.
ex) 1+2 ���� 2�ڸ��� ��ü�� ���ٸ� ù��°�� �ؼ��� ���� ������, 
�ι�°�� �ؼ��� �Ǵµ�, �̸� class ������ private ������ ����ϱ� ���ؼ��� friend �Լ��� �̿��ؼ� ����������Ѵ�.
������ ���� ���� �����ڰ� 2������ ��� �ؼ��� �ȴ�. ���� �ϳ��� ������ ����Ѵ�.
(���� ������, �ι�°���̴�)

���� �ڽ��� �����ϴ� ���� �����ڴ� �ɹ� �Լ�, �ƴ� �ֵ��� �ܺ� �Լ��� �����Ѵ�.

����� ������
iostream�� ����Ǿ� �ִ� << operator�� ����ϰ� �ִµ�, ���� header�� �ִ� operation�� ����ϸ�, std::cout << a �� ����
��ü�� �ٷ� �д� ���� �Ұ����Ͽ�����, ���� �츮�� a.print() �Լ��� ����߾���.
������ ���� �ش� << operator�� �츮�� ������ class ���ο��� ��� �����ϰ� �Ѵٸ�, �� ��Ȳ�� �����ϰ� �� ���̴�.

std::ostream& operator<<(std::ostream& os, const Complex& c) {
  os << "( " << c.real << " , " << c.img << " ) ";
  return os;
}
������ ���� ostream header�� ��ü�� �ҷ������ν�, ���� a.print() �Լ� ���̵� <<�� ����� �� �ְ� �Ǿ���.

÷�� ������ > []  MyString class���� ����ϴ� ������, []�ȿ� ���� index�� ������, char& ���·� ����Ѵ�.

wrapper > ���𰡸� �Ѵ� ��� �ǹ̷�, �⺻ �ڷ������� ��ü�ν� �ٷ��� �Ҷ�, ����Ѵ�.
�� �⺻ �ڷ����� Ŭ������ �����Ͽ�, ������ �ڷ����� ��ü�� ����ϴ� ���� �ǹ��Ѵ�.
Ÿ���� ��ȭ class�� ��ü�� ���� type�� ��¥ int�� Ÿ������ ��ȯ�ϱ� ���ؼ��� ������ ���� Ÿ�� ��ȯ �����ڸ� 
�����ؾ��Ѵ�.
operator (��ȯ �ϰ��� �ϴ� Ÿ��) () > operator int() int�� Ÿ������ ��ȯ
�̶� �����ؾ� �� ������ ������ ó�� ����Ÿ���� ���ٴ� ���̴�.

����/���� ���� ������
a++ / ++a�� ��Ÿ���� �����ڴ� ��� ++�̴�. �׷��ٸ� ��� ������ ++�� �ΰ����� �����ϴ°�?"
���� : operator++() / ���� : operator++(int) > ���� ����, ������ �����ϱ� ����, ������ �ִ� ������, ū �ǹ� ����.
�߿��� ����� ������� �����ؾ��ϴ����� ���Ͽ� ���̰� �ִٴ� ���̴�.
���� �������� ���, ���� �ٲ� �ڽ��� �����ؾ� �ϸ�, ���� �������� ���, ���� �ٲ�� ���� ��ü�� �����ؾ��Ѵ�.
Test& operator++() {
    x++;
    std::cout << "���� ���� ������" << std::endl;
    return *this;
  }

  Test operator++(int) {
    Test temp(*this);
    x++;
    std::cout << "���� ���� ������" << std::endl;
    return temp;
  }

  ������ ++ ���� ��, *this�� �����ϴ� �ݸ�, ������ ��ü�� �����Ͽ�, ++�ϱ����� ��ü�� ��ȯ�ؾ� �Ѵ�. temp ��ü ������,
  ��ü ��ȯ ��, ++�����ϵ��� �Ѵ�.
*/