#include <iostream>

class Date {
    int year_;
    int month_;  // 1 ���� 12 ����.
    int day_;    // 1 ���� 31 ����.

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
        }//1,3,5,7,8,10,12 > 31��
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
���� ����
- �Լ��� �����Ѵ�
- �߿��� �κ��� �Լ�(����)�� �ɰ��� ó���Ѵ�

��ü ����
- �Լ� �ȿ� ������ �ִ°��� �ƴ϶�, ������ü�� �Լ��� ������ �ִ�.
ex. play(animal) = ���� / animal.play = ��ü
animal�� ����, �ൿ, �Լ��� �̷���� ��ü�̴�.
> ������� ���� �ڷ��� �̷���� ���
> ��ü�� �ν��Ͻ� ����, �ν��Ͻ� �޼ҵ�(�Լ�)�� �ѷ� �׿� �ִ�
 Ư¡ : ������ �Լ���� ��ȣ�Ǿ� �ֱ⿡, �������� ��ġ�� ���ؼ���
 �Լ��� ���ؼ��� �����ϴ�. > ĸ��ȭ
 ex) Animal animal / animal.food = 100 (x), animal.increase_food(100) (��)

 >class�� ��ü > �ν��Ͻ�
 class ���� private���� ���� �����Ǹ� �ش� ������ ��ü ���ο����� ���
 & public�� �Լ����� �� �ΰ��ϱ� ���ؼ��� �ٸ� ���� �ΰ��ؼ�, private ���� ���� ����

 ���� ���� �����ϱ� > �⵵ ���߱�
*/