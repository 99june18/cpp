#include <iostream>
#include <string>

template <typename T>
class Vector {
    T* data;
    int capacity;
    int length;

public:
    // � Ÿ���� �����ϴ���

    typedef T value_type;

    // ������
    Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

    // �� �ڿ� ���ο� ���Ҹ� �߰��Ѵ�.
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

    // ������ ��ġ�� ���ҿ� �����Ѵ�.
    T operator[](int i) { return data[i]; }

    // x ��° ��ġ�� ���Ҹ� �����Ѵ�.
    void remove(int x) {
        for (int i = x + 1; i < length; i++) {
            data[i - 1] = data[i];
        }
        length--;
    }

    // ���� ������ ũ�⸦ ���Ѵ�.
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

    // ������
    Vector(int n = 1)
        : data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0) {
        for (int i = 0; i < capacity; i++) {
            data[i] = 0;
        }
    }

    // �� �ڿ� ���ο� ���Ҹ� �߰��Ѵ�.
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

    // ������ ��ġ�� ���ҿ� �����Ѵ�.
    bool operator[](int i) { return (data[i / 32] & (1 << (i % 32))) != 0; }

    // x ��° ��ġ�� ���Ҹ� �����Ѵ�.
    void remove(int x) {
        for (int i = x + 1; i < length; i++) {
            int prev = i - 1;
            int curr = i;

            // ���� curr ��ġ�� �ִ� ��Ʈ�� 1 �̶��
            // prev ��ġ�� �ִ� ��Ʈ�� 1 �� �����.
            // 1�Ǵ� ���� > & ���
            // 1 �߰� ���� > | ���
            if (data[curr / 32] & (1 << (curr % 32))) {
                data[prev / 32] |= (1 << (prev % 32));
            }
            // �ƴϸ� prev ��ġ�� �ִ� ��Ʈ�� 0 ���� �����.
            // �ϴ� �� 1���� pre �κи� xor���Ѽ� 1110111 ���� �����
            // �� �κ� & ����ؼ� 0���� ����
            else {
                unsigned int all_ones_except_prev = 0xFFFFFFFF;
                all_ones_except_prev ^= (1 << (prev % 32));
                data[prev / 32] &= all_ones_except_prev;
            }
        }
        length--;
    }

    // ���� ������ ũ�⸦ ���Ѵ�.
    int size() { return length; }
    ~Vector() {
        if (data) {
            delete[] data;
        }
    }
};

int main() {
    // int �� �����ϴ� ���͸� �����.
    Vector<int> int_vec;
    int_vec.push_back(3);
    int_vec.push_back(2);

    std::cout << "-------- int vector ----------" << std::endl;
    std::cout << "ù��° ���� : " << int_vec[0] << std::endl;
    std::cout << "�ι�° ���� : " << int_vec[1] << std::endl;

    Vector<std::string> str_vec;
    str_vec.push_back("hello");
    str_vec.push_back("world");
    std::cout << "-------- std::string vector -------" << std::endl;
    std::cout << "ù��° ���� : " << str_vec[0] << std::endl;
    std::cout << "�ι�° ���� : " << str_vec[1] << std::endl;

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
template � class���� ���� ���ϴ� type�� ��� �����ϰ��� �Ҷ� ����Ѵ�
���÷� ����, vector class���� vector�� ���� �� type�� string, int, char������ �� �����ؾ� �ϴµ�, ���ø� ����ϸ�
�� Ŭ���� �ȿ��� ��밡�� > Ʋ�� ����ش�.
template <typename T>
�ϰ�, main���� type �����ϰ��� �� �� class<type> ��ü �̸� �̷������� ����
type�� ������ �� �ִ� ����� ��� ���̴�.
 Vector<std::string> str_vec;
    str_vec.push_back("hello");
    str_vec.push_back("world");
�������� Vector class�� ��ü�� class ��ü �̷������� ǥ�� �ߴٸ�, template ����, class�� ��ü ���̿�, template�� ��
type�� ���������ν� ��ü ������ ����������.
> Ŭ���� ���ø� �ν��Ͻ�ȭ ��� �Ѵ�.

������ ���⼭ �ϳ��� Ư¡���� ���� �� �ִµ�, ���� Vector<bool> bool_vec�̶�� �ν��Ͻ��� �ߴٰ� �����ϸ�
cpp���� data ó�� ������ 1byte ũ���̴�. ������ bool�� ��� ���� 1bit������ ó���� �����ѵ�, ����, 8bit�� ����ؾ� �ϳ�
> �� �޸� ���� �ƴ� �� ����
���� �� ��� ���ø� Ư��ȭ�� ��Ų��

�Լ��� ���ø� ���

template <typename T>
T max(T& a, T& b) {
  return a > b ? a : b;
}
class�� ���� ����� ���¸� ���ϰ� �ִ�. ���⼭ &�� ���� �Ƚᵵ �Ǵµ�, �ν��Ͻ��� �޸� �Ҵ��� ���̰��� ���� �� ����.
�׸��� �Լ������� class�� �޸� <type>�� ���� ����ؼ� �������� �ʰ�, �׳� ������ type�� �����ϸ�, �ش� ������ type�� ���󰡰�
����Ǿ� �ִ�.
�� std::cout << "Max (" << s << "," << t << ") ? : " << max(s, t) << std::endl;
���� max<int>(s,t) ���ؼ�, int s, t; �̷��� �ϸ� �˾Ƽ� int type���� �νĵȴ�.

template �Լ����� typename�� struct ������ ������ �Ͽ���, ��ġ �Լ� �ΰ� ó�� ��� �ϴ� ���� �Լ� ��ü Functor��� �Ѵ�.
�Լ��� �ƴ����� ��ġ �Լ��� ��ó�� ������ �ϴ� ���̴�. > ��ü�� �Լ� �ΰ�ó�� ������ �Ѵ�.
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
�̷������� ��ü�� ����� �ִ� struct�� operator�� ���Ǹ� �صΰ�, 
�̸� Comp1 comp1ó�� comp1 ��ü�� �������ְ�, �̸� �� template�� Comp�� �־��ְ� �Ǹ�, if (!comp(cont[i], cont[j])) ������
()�� struct�� ���ǵ� operatoró�� �۵��� �ϰ� �ȴ�. �� ��ġ �Լ��� ����Ǵ� ��ó�� ��������, �˰� ���� ��ü�� ���ǵ� operator�� 
�۵��ϸ鼭 �۾��� ����Ǵ� ������ �� �� �ִ�.
operator()�� ����ϴ°��� �⺻�̸�, ������ ��ü�� ()�� �������ν� ��ü�� ȣ���ϴ� ������, �Լ��� ��ó�� �۵��� �Ѵ�.

template���� type���ڰ� �ƴѰ͵� ����� �����ϴ�. �� �׳� int�� ���� �� �س���, ����� �� <int, 5>�� ���� �̸� �����ص� type�� �´�
���� �ΰ������ν� �۵��� �ǰ� �� �� �� �ִ�.

template <typename T, int num>
T add_num(T t) {
  return t + num;
}
add_num<int, 5>(x)

�Ǵ� �⺻������ std::array<int, 5>ó�� �����Ǿ� �ִ� ��쵵 �ִ�. �̴� header array�� �ҷ��� ����ϴ� ���
*/