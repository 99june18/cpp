#include <cstring>
#include <iostream>
#include <string>

size_t GetStringSize(const char* s) { return strlen(s); }

size_t GetStringSize(const std::string s) { return s.size(); } //const &�� ��������ν�, ���� ���� �������� �ʰ� + ���������ν�
//�޸������� ���� ��������.

template <typename T, typename... Ts>
size_t GetStringSize(const T& s, Ts... strs) {
    return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(std::string* concat_str) { return; } //*�� ���� ������ ���� �Լ��� �ִ� ���� ��������� �ϱ⿡
//�ּҰ��� ���ڷ� �޾ƾ� �ȴ� > pointer ���

template <typename T, typename... Ts>
void AppendToString(std::string* concat_str, const T& s, Ts... strs) {
    concat_str->append(s);
    AppendToString(concat_str, strs...);
}

template <typename T, typename... Ts>
std::string StrCat(const T& s, Ts... strs) {
    // ���� ������ ���ڿ��� �� ���̸� ���Ѵ�.
    size_t total_size = GetStringSize(s, strs...);

    // reserve �� ���� �̸� ������ �Ҵ��� ���´�.
    std::string concat_str;
    concat_str.reserve(total_size);

    concat_str = s;
    AppendToString(&concat_str, strs...);

    return concat_str;
}

int main() {
    // std::string �� const char* �� ȥ���ؼ� ��� �����ϴ�.
    std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"),
        " ", std::string("sentence"));
}

/*
template <typename T, typename... Types>
�� ������ �ڵ忡�� �������� ���ø������� �Լ����ڰ� 2���� �ް� �ִ���, �ش� �Լ��� ����Լ��� ����Ϸ��� �ϸ�
�ش� �Լ� ���ڿ� typename... ���� template ����� �־��ָ� �����Ϸ��� �˾Ƽ� �ش� ������ �� ó���� ù ���ڷ� 
�ι�°���� ����� �ٽ� �����Ѵ�.

void AppendToString(std::string* concat_str, const T& s, Ts... strs) {
    concat_str->append(s);
    AppendToString(concat_str, strs...);
}
�� �� �ڵ带 ���캸�� concat_str�� �����ϰ� �߰��ϰ��� �ϴ� string���� ���� 2���� �޴´�. s�� strs
������ �Լ��� ����Լ��� ����Ϸ��� �ϸ�, strs�ϳ��� �ΰ��ϴµ�, �̴� �����Ϸ��� �ڵ����� strs�� ù���ڸ� s�� �ְ�
������ ���ڵ��� strs�� �ѱ��. �̷��� ������ ����Լ��� ��� �ϸ� strs�� ����� string�� ��� �ٸ鼭 string�� �߰��ȴ�.

���� sizeof�� type�� �޸� byte�� ��Ī�ϴ� type������, sizeof... �� ��ü ������ ������ �����Ѵ�.
sizeof...(num) => num�� �޷��ִ� ������ ������ ����

���� ����Լ��� ����ϱ� ���ؼ�, �츮�� �ƹ����� ������ ���� �ʴ� �ʱ� ������ �Լ��� ��������� �ߴ�.
void AppendToString(std::string* concat_str) { return; }

������ �̴� Fold�� ����ؼ� �ʱ� ���� ǥ���� �����ϴ�.
template <typename... Ints>
int sum_all(Ints... nums) {
  return (... + nums);
}
������ ���� ...�� ��� Ȱ���ؼ� �ʱⰪ�� ������ �� �ִ�.
*/