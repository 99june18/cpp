#include <cstring>
#include <iostream>
#include <string>

size_t GetStringSize(const char* s) { return strlen(s); }

size_t GetStringSize(const std::string s) { return s.size(); } //const &를 사용함으로써, 원본 값을 변경하지 않고 + 참조함으로써
//메모리적으로 낭비가 없어진다.

template <typename T, typename... Ts>
size_t GetStringSize(const T& s, Ts... strs) {
    return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(std::string* concat_str) { return; } //*가 붙은 이유는 원본 함수에 있는 값을 변경해줘야 하기에
//주소값을 인자로 받아야 된다 > pointer 사용

template <typename T, typename... Ts>
void AppendToString(std::string* concat_str, const T& s, Ts... strs) {
    concat_str->append(s);
    AppendToString(concat_str, strs...);
}

template <typename T, typename... Ts>
std::string StrCat(const T& s, Ts... strs) {
    // 먼저 합쳐질 문자열의 총 길이를 구한다.
    size_t total_size = GetStringSize(s, strs...);

    // reserve 를 통해 미리 공간을 할당해 놓는다.
    std::string concat_str;
    concat_str.reserve(total_size);

    concat_str = s;
    AppendToString(&concat_str, strs...);

    return concat_str;
}

int main() {
    // std::string 과 const char* 을 혼합해서 사용 가능하다.
    std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"),
        " ", std::string("sentence"));
}

/*
template <typename T, typename... Types>
윗 예시의 코드에서 가변길이 템플릿에서는 함수인자가 2개를 받고 있더라도, 해당 함수를 재귀함수로 사용하려고 하면
해당 함수 인자에 typename... 으로 template 덩어리를 넣어주면 컴파일러가 알아서 해당 인자의 맨 처음을 첫 인자로 
두번째부터 덩어리를 다시 저장한다.

void AppendToString(std::string* concat_str, const T& s, Ts... strs) {
    concat_str->append(s);
    AppendToString(concat_str, strs...);
}
즉 이 코드를 살펴보면 concat_str를 제외하고 추가하고자 하는 string으로 인자 2개를 받는다. s와 strs
하지만 함수를 재귀함수로 사용하려고 하면, strs하나만 인가하는데, 이는 컴파일러가 자동으로 strs의 첫인자를 s로 주고
나머지 인자들을 strs로 넘긴다. 이러한 과정을 재귀함수로 계속 하면 strs에 저장될 string이 계속 줄면서 string이 추가된다.

보통 sizeof는 type의 메모리 byte를 지칭하는 type이지만, sizeof... 는 전체 인자의 개수를 리턴한다.
sizeof...(num) => num에 달려있는 인자의 개수를 리턴

또한 재귀함수를 사용하기 위해서, 우리는 아무값도 가지고 있지 않는 초기 상태의 함수를 만들어줬어야 했다.
void AppendToString(std::string* concat_str) { return; }

하지만 이는 Fold를 사용해서 초기 상태 표현이 가능하다.
template <typename... Ints>
int sum_all(Ints... nums) {
  return (... + nums);
}
다음과 같이 ...을 어떻게 활용해서 초기값을 마련할 수 있다.
*/