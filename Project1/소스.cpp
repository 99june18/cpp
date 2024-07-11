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
    obj.setValue(20);  // obj�� ���� ��ü�� ���纻
    std::cout << "Inside passByValue: " << obj.getValue() << std::endl;
}

int main() {
    MyClass obj(10);
    std::cout << "Before passByValue: " << obj.getValue() << std::endl;
    passByValue(obj);  // obj�� ���纻�� �Լ��� ���޵�
    std::cout << "After passByValue: " << obj.getValue() << std::endl;  // ���� ��ü�� ������ ����
    return 0;
}