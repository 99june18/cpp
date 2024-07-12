#include <iostream>

class MyClass {
public:
    MyClass(int value) : value(value) {}
    void setValue(int newValue) { value = newValue; }
    int getValue() const { return value; }
private:
    int value;
};

void passByValue(MyClass obj) {
    obj.setValue(20);  // obj는 원본 객체의 복사본
    std::cout << "Inside passByValue: " << obj.getValue() << std::endl;
}

int main() {
    MyClass obj(10);
    std::cout << "Before passByValue: " << obj.getValue() << std::endl;
    passByValue(obj);  // obj의 복사본이 함수로 전달됨
    std::cout << "After passByValue: " << obj.getValue() << std::endl;  // 원본 객체는 변하지 않음
    return 0;
}