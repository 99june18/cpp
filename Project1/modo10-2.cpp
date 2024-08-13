#include <iostream>
#include <unordered_set>
#include <string>

template <typename T>
void print_set(std::unordered_set<T>& s) {
    for (auto ele : s) {
        std::cout << ele << std::endl;
    }
}

template <typename T>
void is_exist(std::unordered_set<T>& s, T key) {
    auto itr = s.find(key);
    if (itr != s.end()) {
        std::cout << key << " : 값이 있다" << std::endl;
    }
    else
    {
        std::cout << key << " : 값이 없다" << std::endl;
    }
}
int main() {
    std::unordered_set<std::string> s;
    s.insert("hi");
    s.insert("my");
    s.insert("name");
    s.insert("is");
    s.insert("psi");
    s.insert("welcome");
    s.insert("to");
    s.insert("c++");

    print_set(s);

    is_exist(s, std::string("to"));

    s.erase(std::string("hi"));

    print_set(s);
    is_exist(s, std::string("hi"));
}


/*
컨테이너의 또 다른 종류인 연관 컨테이너는 시퀀스 컨테이너와 다르게 키(key)-값(value) 구조를 갖는다.
즉 어떤 키를 넣으면 해당 키에 해당하는 값을 돌려준다. 키와 값은 연관되어 있는 구조로 되어 있다.
2가지 point : key값이 컨테이너에 있는가? / 만약 있다면, 어떤 값에 대응되느냐? 다음 2가지를 만족해야한다.
이 중에서 전자의 경우 set, multiset를 활용하여 알 수 있고, 후자는 map, multimap를 활용하여 알 수 있다.
물론 map으로 2가지 point 모두 알 수 있지만, 메모리가 크다. 따라서 key의 유무만 궁금하다면 set을 활용한다.
------------------------------------------------------------------------------------------------------------
set에서 insert를 통해 값을 인가할 때, 시퀀스 컨테이너 처럼 그 값의 위치까지 고려해서 넣어주지 않고, set는 그냥 막 넣는다는 관점이다
즉 set안에 해당 원소가 있느냐 없느냐가 중요하다
또한 set에 들어있는 원소는 넣은 순서로 출력되는게 아니라, set안에서 자동으로 정렬된 상태를 유지한다는 특징이 있다.
어찌보면 원소를 막 넣는데, 순서를 지키면서 넣는다는 느낌이다.
set의 진가는 set안에 원소가 있느냐, 없느냐를 판단할 때 나타난다. 원소를 찾을 때, find 함수를 사용하는데, 만약 해당 원소가 있다면
iterator type을 리턴하고, 없다면, s.end()를 리턴한다. > if문에서 == 안쓰고 != s.end()로 있는지 없는지 판단함
그리고 백터에서는 원소를 찾기 위해서는 모든 백터 원소를 찾아야 했지만, set는 tree 구조를 형성하고 있어, 복잡도면에서 백터에 비해
빠르게 수행 할 수 있다는 장점이 있다.
또한 또 다른 특징으로는 중복되는 원소를 가지고 있지 않는다. insert로 아무리 같은 수를 많이 넣어도 단 하나의 원소만 가지고 있는 상태다.
만약 중복 원소를 허용하려고 하면, multiset를 사용한다.

만약 template에 내가 정의한 class를 넣는다고 하면, 그냥 class로는 정의되지 않는다. 왜냐하면 set는 원소를 정렬해서 넣어두는데, 정렬
하기 위해 사용하는 < 에 대한게 정의 되어 있지 않기 때문이다. int 나 다른 보편적인 거는 정의 되어 있는듯함
따라서 set에 class를 넣기 위해서는 class에 < 도 정의해 줘야한다
< operator를 구현하는데 가장 중요한 사실은 const class t처럼 const 레퍼런스를 갖는 const 함수를 반드시 사용해야 한다.
bool operator<(const Todo& t) const { //const Todo를 레퍼런스로 갖는 const함수
        if (priority == t.priority) {
            return job_desc < t.job_desc;
        }
        return priority > t.priority;
    }
왜냐하면, set 내부에서는 오직 상수 반복자를 사용하는데, 상수 반복자는 상수 함수만을 호출 할 수 있기 때문이다.
또 중요한 점이라면, set는 == 를 판단하지 못하기 때문에, 값이 같다면, >와 <에서 모두 false가 나오는게 같은 것으로 판단하게 된다.
따라서 순서를 정하는 기준이 되는 원소가 같을 때는 어떻게 처리할지에 대한 코드도 작성해 줘야 한다는 점이다. 아니면 순서 판단 기준 원소
가 같은 걸로 판단되어, 중복으로 판단하여 안나온다.
class 내부에 < 비교 operator를 넣어도 되지만, 다른 class에 < 를 선언하고, 그걸 friend에서 사용하고 template에, 2개의 class를
넣어서 사용할 수도 있다.
실제로 set의 template 선언할 때 < >에 들어가는 2번째 인자는 비교인자를 받는다. 안들어가면 key class의 < operator 사용하고 사용자
지정 comparator를 넣어줘도 된다.
----------------------------------------------------------------------------------------------------------------------------------
다음으로는 map인데, map은 인자로 2개를 받는다 <key, value> 이렇게 그리고 key나 value값을 출력 하고자 하면,
iterator->first, iterator->second로 key와 value값을 뽑아 낼 수 있다.
iterator 사용안하고 값을 뽑아내는데는 범위 기반 for 문 사용하는데, 이때는 .first, .second와 같이 ->이 아니라 .으로 나타내주면 됨
다음으로는 값을 인가할때, insert를 사용하는데, insert 내부에서 여러가지 표현가능
std::pair<std::string, double>("박세웅", 2.23), std::make_pair("차우찬", 3.04), {"add",200} 많은 경우가 있으니 찾아보면서 하면되고
insert 사용 안하고, 그냥 []로 대입하여도 된다. 즉 pitcher_list["니퍼트"] = 3.56; 면 key가 니퍼트, value가 3.56이 된다.
값을 출력할때도 []를 사용할 수 있는데, 주의사항은 해당 key에 해당 되는 value가 없다면 원래 오류가 떠야 하지만, []는 0이라는 값을
출력하게 된다. 즉 default하게 된다. 따라서, find 함수로 key에 해당하는 value가 있는지 먼저 확인하고, []를 사용해서 뽑아내는 것이
좋다.
마지막으로 map 역시 중복 값은 갖은 것으로 판단하게 되고, 만약 중복 되는 key가 들어오게 되면, 이후 해당 key에 대한 작업은
무시된다. 만약 key값을 바꾸고 싶다면, []를 사용해 주면 된다.
----------------------------------------------------------------------------------------------------------------------------------
multiset과 multimap을 사용하면 중복하여 insert한 값도 뽑아낼 수 있다
사용법은 선언할 때, set, map 대신 multiset, multimap을 사용하면 된다.
multimap을 사용하게 될 경우, map에서 사용하였던 []를 사용하지 못하게 되는데, 그 이유는 한 key값에 여러 value가 붙어 있는데
어떤 값을 뽑을 지 모르기 때문이다.
그럼 같이 key에 대해서 어떤 value를 뽑느냐는 상황마다 다르게 나타난다. 즉 find(key) 했을 때 어떤 값이 나와도 이상하지 않다
그럼 한 key에 있는 모든 value를 뽑는 방법은 equal_range 함수로 한 key에 할당된 range를 선정하고, 
range.first와 range.second를 이용해서, 시작에서 끝을 선언해주고 for문 이용해서, itr->second로 value를 뽑아낼 수 있다.
----------------------------------------------------------------------------------------------------------------------------------
unordered_set과 unordered_map의 경우, 기존 set과 map은 값을 정렬하였지만, 이 둘은 정렬되지 않는 상태를 유지한다.
즉 random 순서로 나오게 된다.
이 두개를 사용하는 이유는 insert, erase, find 모두 복잡도가 크지 않아 빠른 속도로 진행된다는 점이다.
그 이유는 hash 함수를 사용하기 때문인데, hash 함수를 통해 같은 원소는 같은 상자에 들어가게 되어, hash가 내보내는 값만으로
그 원소가 있는지를 판단할 수 있다
가끔 한 상자에 다른 원소가 들어가기도 하는 hash 충돌이 발생하는데, 그거 여도 평균적으로 시간이 짧다. 
따라서 빠른 시간을 요구하는 경우 unordered_set과 unordered_map를 사용한다.
사용자가 만든 class를 unordered_set과 unordered_map에 넣으려고 한다면, 자체적인 hash 함수를 만들어 줘야 하는데,
이 부분은 쉽지 않고, 만약 만든다면, 라이브러리에 있는 hash를 사용해서 제작한다.
> 자세한 내용은 skip

*/