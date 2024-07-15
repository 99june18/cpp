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
c���� ����ϴ�, �����ڵ�(+,-,==)���� ��� int,float���� Ÿ�Կ��� ���Ǿ���. ��,string Ÿ�Կ��� ��� �Ұ�
������ cpp���� ����� ���� ������ ��밡��, �� ��ó�� ������ ���Ǿ��� Ÿ�� ����, ����ڰ� ���� �� �� �ִ�
�����ڵ��� �����ε��̴ٰ� �Ѵ�. > ������ �����ε�

(���� Ÿ��) operator(������) (�����ڰ� �޴� ����) ������ ���� ���·� ������ �����ε� �Լ��� ����� �ȴ�.
bool MyString::operator==(MyString& str)

�̷��� str1.operator==(str2)�� ���� ��ü�� �Լ� ���� ���°� �ƴ�, str1 == str2�� ���� ǥ���� �����ϴ�
���� �۵� ���,but �� �������� ǥ�ð� �����ϴ�.

���Ҽ� class
���� �����ڰ� �䱸�ȴ�. �ֳ��ϸ�, �׳� �װ����� �����, ù�ٿ��� ����� ���� ���� �ٿ� ������ ���� �Ǿ�
�̻��� ������ ������ ����ȴ�.
���� ������ �����ε� �Լ� ���ο���, �����ڸ� �����ڸ� ���� �����Ͽ� ������ �ٽ� �����ϴ� ������ �����Ͽ��� �Ѵ�,
Complex Complex::operator+(const Complex& c) const {
    Complex temp(real + c.real, img + c.img);
    return temp;
}

���⼭ temp��� ��ü ������, real�� img�� �ջ���� ��� ���� ����, �����ڰ� ��������� ������, ���� ������ ���� ���� 
�߻����� �ʴ´�.
���� �Լ��� complex& ���� �ƴ� ���� ����, �����ϱ� ���� ���� ��ȭ�� �߻��ϸ� �ȵǱ� ������, �׳� class�� ������ 
������ �߻��ϵ��� �Լ��� ����Ǿ���.

���� �����ڴ� ��ü�� ��ȭ�� �䱸�Ǳ� ������, &�÷� ���ϵǰ� �Ͽ�����, ���ʿ��� ���簡 ��� �ȴ�.

*********** &���� class return�� �׳� class���� return���� ���̸� �������� > �� �����ϱ� ************** 
*/