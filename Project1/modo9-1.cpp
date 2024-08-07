#include <iostream>
#include <string>

template <typename T>
class Vector {
    T* data;
    int capacity;
    int length;

public:
    // 어떤 타입을 보관하는지

    typedef T value_type;

    // 생성자
    Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

    // 맨 뒤에 새로운 원소를 추가한다.
    void push_back(T s) {
        if (capacity <= length) {
            T* temp = new T[capacity * 2];
            for (int i = 0; i < length; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            capacity *= 2;
        }

        data[length] = s;
        length++;
    }

    // 임의의 위치의 원소에 접근한다.
    T operator[](int i) { return data[i]; }

    // x 번째 위치한 원소를 제거한다.
    void remove(int x) {
        for (int i = x + 1; i < length; i++) {
            data[i - 1] = data[i];
        }
        length--;
    }

    // 현재 벡터의 크기를 구한다.
    int size() { return length; }

    ~Vector() {
        if (data) {
            delete[] data;
        }
    }
};

template <>
class Vector<bool> {
    unsigned int* data;
    int capacity;
    int length;

public:
    typedef bool value_type;

    // 생성자
    Vector(int n = 1)
        : data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0) {
        for (int i = 0; i < capacity; i++) {
            data[i] = 0;
        }
    }

    // 맨 뒤에 새로운 원소를 추가한다.
    void push_back(bool s) {
        if (capacity * 32 <= length) {
            unsigned int* temp = new unsigned int[capacity * 2];
            for (int i = 0; i < capacity; i++) {
                temp[i] = data[i];
            }
            for (int i = capacity; i < 2 * capacity; i++) {
                temp[i] = 0;
            }

            delete[] data;
            data = temp;
            capacity *= 2;
        }

        if (s) {
            data[length / 32] |= (1 << (length % 32));
        }

        length++;
    }

    // 임의의 위치의 원소에 접근한다.
    bool operator[](int i) { return (data[i / 32] & (1 << (i % 32))) != 0; }

    // x 번째 위치한 원소를 제거한다.
    void remove(int x) {
        for (int i = x + 1; i < length; i++) {
            int prev = i - 1;
            int curr = i;

            // 만일 curr 위치에 있는 비트가 1 이라면
            // prev 위치에 있는 비트를 1 로 만든다.
            // 1판단 인자 > & 사용
            // 1 추가 인자 > | 사용
            if (data[curr / 32] & (1 << (curr % 32))) {
                data[prev / 32] |= (1 << (prev % 32));
            }
            // 아니면 prev 위치에 있는 비트를 0 으로 지운다.
            // 일단 다 1에서 pre 부분만 xor시켜서 1110111 같이 만들고
            // 이 부분 & 사용해서 0으로 만듬
            else {
                unsigned int all_ones_except_prev = 0xFFFFFFFF;
                all_ones_except_prev ^= (1 << (prev % 32));
                data[prev / 32] &= all_ones_except_prev;
            }
        }
        length--;
    }

    // 현재 벡터의 크기를 구한다.
    int size() { return length; }
    ~Vector() {
        if (data) {
            delete[] data;
        }
    }
};

int main() {
    // int 를 보관하는 벡터를 만든다.
    Vector<int> int_vec;
    int_vec.push_back(3);
    int_vec.push_back(2);

    std::cout << "-------- int vector ----------" << std::endl;
    std::cout << "첫번째 원소 : " << int_vec[0] << std::endl;
    std::cout << "두번째 원소 : " << int_vec[1] << std::endl;

    Vector<std::string> str_vec;
    str_vec.push_back("hello");
    str_vec.push_back("world");
    std::cout << "-------- std::string vector -------" << std::endl;
    std::cout << "첫번째 원소 : " << str_vec[0] << std::endl;
    std::cout << "두번째 원소 : " << str_vec[1] << std::endl;

    Vector<bool> bool_vec;
    bool_vec.push_back(true);
    bool_vec.push_back(true);
    bool_vec.push_back(false);
    bool_vec.push_back(false);
    bool_vec.push_back(false);
    bool_vec.push_back(true);
    bool_vec.push_back(false);
    bool_vec.push_back(true);
    bool_vec.push_back(false);
    bool_vec.push_back(true);
    bool_vec.push_back(false);
    bool_vec.push_back(true);
    bool_vec.push_back(false);
    bool_vec.push_back(true);
    bool_vec.push_back(false);
    bool_vec.push_back(true);
    bool_vec.push_back(false);

    std::cout << "-------- bool vector ---------" << std::endl;
    for (int i = 0; i < bool_vec.size(); i++) {
        std::cout << bool_vec[i];
    }
    std::cout << std::endl;
}

/*
template 어떤 class에서 내가 원하는 type를 골라서 선택하고자 할때 사용한다
예시로 보면, vector class에서 vector에 저장 할 type이 string, int, char인지를 다 구분해야 하는데, 템플릿 사용하면
한 클래스 안에서 사용가능 > 틀은 찍어준다.
template <typename T>
하고, main에서 type 지정하고자 한 때 class<type> 객체 이름 이런식으로 지정
type을 전달할 수 있는 방법을 배운 것이다.
 Vector<std::string> str_vec;
    str_vec.push_back("hello");
    str_vec.push_back("world");
기존에는 Vector class의 객체로 class 객체 이런식으로 표현 했다면, template 사용시, class와 객체 사이에, template에 들어갈
type을 적어줌으로써 객체 생성이 가능해진다.
> 클래스 템플릿 인스턴스화 라고 한다.

하지만 여기서 하나의 특징점을 잡을 수 있는데, 만약 Vector<bool> bool_vec이라고 인스턴스를 했다고 가정하면
cpp에서 data 처리 단위가 1byte 크기이다. 하지만 bool의 경우 단지 1bit만으로 처리가 가능한데, 굳이, 8bit을 사용해야 하나
> 즉 메모리 낭비가 아닐 수 없다
따라서 이 경우 템플릿 특수화를 시킨다

함수의 템플릿 사용

template <typename T>
T max(T& a, T& b) {
  return a > b ? a : b;
}
class와 거의 비슷한 형태를 취하고 있다. 여기서 &는 굳이 안써도 되는데, 인스턴스로 메모리 할당을 줄이고자 만든 것 같다.
그리고 함수에서는 class와 달리 <type>과 같이 사용해서 정해주지 않고, 그냥 변수의 type을 설정하면, 해당 변수의 type을 따라가게
설계되어 있다.
즉 std::cout << "Max (" << s << "," << t << ") ? : " << max(s, t) << std::endl;
에서 max<int>(s,t) 안해서, int s, t; 이렇게 하면 알아서 int type으로 인식된다.

template 함수에서 typename을 struct 구조로 설정을 하여서, 마치 함수 인것 처럼 사용 하는 법이 함수 객체 Functor라고 한다.
함수는 아니지만 마치 함수인 것처럼 역할을 하는 것이다. > 객체가 함수 인것처럼 역할을 한다.
template <typename Cont, typename Comp>
void bubble_sort(Cont& cont, Comp& comp) {
  for (int i = 0; i < cont.size(); i++) {
    for (int j = i + 1; j < cont.size(); j++) {
      if (!comp(cont[i], cont[j])) {
        cont.swap(i, j);
      }
    }
  }
}
struct Comp1 {
  bool operator()(int a, int b) { return a > b; }
};
struct Comp2 {
  bool operator()(int a, int b) { return a < b; }
};
이런식으로 객체를 만들수 있는 struct에 operator를 정의를 해두고, 
이를 Comp1 comp1처럼 comp1 객체를 생성해주고, 이를 위 template의 Comp에 넣어주게 되면, if (!comp(cont[i], cont[j])) 문에서
()가 struct에 정의된 operator처럼 작동을 하게 된다. 즉 마치 함수가 수행되는 것처럼 보이지만, 알고 보면 객체에 정의된 operator가 
작동하면서 작업이 수행되는 과정을 알 수 있다.
operator()를 사용하는것이 기본이며, 선언한 객체에 ()를 붙임으로써 객체를 호출하는 거지만, 함수인 것처럼 작동을 한다.

template에서 type인자가 아닌것도 사용이 가능하다. 즉 그냥 int와 같은 것 해놓고, 사용할 때 <int, 5>와 같이 미리 지정해둔 type에 맞는
값을 인가함으로써 작동이 되게 할 수 도 있다.

template <typename T, int num>
T add_num(T t) {
  return t + num;
}
add_num<int, 5>(x)

또는 기본적으로 std::array<int, 5>처럼 설정되어 있는 경우도 있다. 이는 header array를 불러서 사용하는 경우
*/