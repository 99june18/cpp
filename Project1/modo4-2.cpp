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
오버로딩 > 같은 이름을 가진, 함수가 여러개 존재하는 것
c에선 안되었던 것 > cpp에선 가능 > 함수 호출시, 사용하는 인자를 보고 판단
즉 오버로딩 함수가 있더라도, 해당 함수에서 정의하는 변수의 인자에 따른 함수를 부름
void print(int x), void print(char x)
> int a = 1; char b = 'c';
print(a); print(b); 면 첫번째는 int로 첫 함수, 두번째는 char여서 두번째 함수
함수이름은 같더라도, 인자가 다르면 다른 함수
만약 해당 인자 함수가 없다면, 최대로 근접한 함수로 접근한다.
# 최대로 근접 함수 규칙 알아두기

생성자 (초기화 과정을 도와준다)
> 객체 생성시 자동으로 호줄됨, 호줄되면 자동 초기화
클래스 이름 (인자) 꼴로 표현 > no return

디폴트 생성자, 즉 인자가 없는 생성자의 경우, A a() 처럼 함수처럼 호출해서는 안된다
클래스 이름 & 인자가 없을 경우, 디폴트 생성자 인식

    Date() {
        std::cout << "기본 생성자 호출!" << std::endl;
        year_ = 2012;
        month_ = 7;
        day_ = 12;
    } //디폴트 생성자

    Date(int year, int month, int day) {
        std::cout << "인자 3 개인 생성자 호출!" << std::endl;
        year_ = year;
        month_ = month;
        day_ = day;
    } //생성자 with 인자

    오버로딩과 생성자
*/