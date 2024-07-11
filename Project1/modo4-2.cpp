#include <iostream>
#include <math.h>

class Point {

public:
    int x1, y1;
    int x2, y2;

    void add_point1(int pos_x, int pos_y) {
        x1 = pos_x;
        y1 = pos_y;
    };

    void add_point2(int pos_x, int pos_y) {
        x2 = pos_x;
        y2 = pos_y;
    }
};


class Geometry {
    int x1, x2;
    int y1, y2;

    double distx, disty, distance;

public:
    void xgetpoint(const Point& p1, const Point& p2) {
        x1 = p1.x1;
        x2 = p2.x2;
    };

    void ygetpoint(const Point& p1, const Point& p2) {
        y1 = p1.y1;
        y2 = p2.y2;
    }

    void Distance() {
        distx = sqrt((x2 - x1) ^ 2);
        disty = sqrt((y2 - y1) ^ 2);

        distance = distx + disty;
    };

    void print() {
        std::cout << distance << std::endl;
    }
};

int main() {
    Point point;
    Geometry geometry;

    point.add_point1(3, 3);
    point.add_point2(2, 2);

}

/*
�����ε� > ���� �̸��� ����, �Լ��� ������ �����ϴ� ��
c���� �ȵǾ��� �� > cpp���� ���� > �Լ� ȣ���, ����ϴ� ���ڸ� ���� �Ǵ�
�� �����ε� �Լ��� �ִ���, �ش� �Լ����� �����ϴ� ������ ���ڿ� ���� �Լ��� �θ�
void print(int x), void print(char x)
> int a = 1; char b = 'c';
print(a); print(b); �� ù��°�� int�� ù �Լ�, �ι�°�� char���� �ι�° �Լ�
�Լ��̸��� ������, ���ڰ� �ٸ��� �ٸ� �Լ�
���� �ش� ���� �Լ��� ���ٸ�, �ִ�� ������ �Լ��� �����Ѵ�.
# �ִ�� ���� �Լ� ��Ģ �˾Ƶα�

������ (�ʱ�ȭ ������ �����ش�)
> ��ü ������ �ڵ����� ȣ�ٵ�, ȣ�ٵǸ� �ڵ� �ʱ�ȭ
Ŭ���� �̸� (����) �÷� ǥ�� > no return

����Ʈ ������, �� ���ڰ� ���� �������� ���, A a() ó�� �Լ�ó�� ȣ���ؼ��� �ȵȴ�
Ŭ���� �̸� & ���ڰ� ���� ���, ����Ʈ ������ �ν�

    Date() {
        std::cout << "�⺻ ������ ȣ��!" << std::endl;
        year_ = 2012;
        month_ = 7;
        day_ = 12;
    } //����Ʈ ������

    Date(int year, int month, int day) {
        std::cout << "���� 3 ���� ������ ȣ��!" << std::endl;
        year_ = year;
        month_ = month;
        day_ = day;
    } //������ with ����

    �����ε��� ������
*/