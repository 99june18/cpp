#include <iostream>

class Date {
    int year_;
    int month_;  // 1 부터 12 까지.
    int day_;    // 1 부터 31 까지.

public:
    void SetDate(int year, int month, int day) {
        year_ = year;
        month_ = month;
        day_ = day;
    };

    void AddDay(int inc) {
        day_ += inc;

        if ((month_ % 2 == 1) && (month_ < 8)) { //1,3,5,7
            if (day_ > 31) {
                month_ += 1;
                day_ = day_ - 31;
            }
        }
        else if ((month_ == 8) || (month_ == 10) || (month_ == 12))
        { //8,10,12
            if (day_ > 31) {
                month_ += 1;
                day_ = day_ - 31;
            }
        }//1,3,5,7,8,10,12 > 31일
        else if ((month_ == 4) || (month_ == 6) || (month_ == 9) || (month_ == 11))
        {
            if (day_ > 30) {
                month_ += 1;
                day_ -= 30;
            }
        }
        else
        {
            if (day_ > 29) {
                month_ += 1;
                day_ -= 29;
            }
        }
    };
    void AddMonth(int inc) {
        month_ += inc;

        if (month_ > 12) {
            year_ += 1;
            month_ -= 12;
        }
    };
    void AddYear(int inc) {
        year_ += inc;
    };

    void ShowDate() {
        std::cout << "date : " << year_ << " " << month_ << " " << day_ << std::endl;
    };
};

int main() {
    Date date;

    date.SetDate(2012, 2, 28);
    date.AddDay(3);

    date.ShowDate();

    return 0;
}


/*
절차 지향
- 함수를 지향한다
- 중요한 부분을 함수(절차)로 쪼개어 처리한다

객체 지향
- 함수 안에 변수를 넣는것이 아니라, 변수자체에 함수를 가지고 있다.
ex. play(animal) = 절차 / animal.play = 객체
animal은 변수, 행동, 함수로 이루어진 객체이다.
> 변수들과 참고 자료들로 이루어진 덩어리
> 객체는 인스턴스 변수, 인스턴스 메소드(함수)로 둘러 쌓여 있다
 특징 : 변수는 함수들로 보호되어 있기에, 변수값을 고치기 위해서는
 함수를 통해서만 가능하다. > 캡슐화
 ex) Animal animal / animal.food = 100 (x), animal.increase_food(100) (ㅇ)

 >class로 객체 > 인스턴스
 class 내부 private에서 변수 지정되면 해당 변수는 객체 내부에서만 사용
 & public의 함수에서 값 인가하기 위해서는 다른 변수 인가해서, private 변수 조작 가능

 예시 보고 이해하기 > 년도 맞추기
*/