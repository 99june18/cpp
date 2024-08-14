#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << "[" << *begin << "] ";
		begin++;
	}
	std::cout << std::endl;
}

int main() {
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	std::cout << "처음 vec 상태 ------" << std::endl;
	print(vec.begin(), vec.end());

	std::cout << "벡터 전체에 1 을 더한다" << std::endl;
	std::transform(vec.begin(), vec.end(), vec.begin(), [](int i) {return i + 1; });
	print(vec.begin(), vec.end());
}

/*
알고리즘은 컨테이너에 반복자를 가지고 복잡한 작업을 수행하는 라이브러리이다.
template <typename Iter>
void do_something(Iter begin, Iter end);

template <typename Iter, typename Pred>
void do_something(Iter begin, Iter end, Pred pred)

알고리즘은 다음과 같은 형태를 가진다. 첫번째는 반복자의 시작점과 끝점 뒤를 받고, 두번째는 반복자의 시작점과 끝점 뒤와 pred에서 특정한
조건을 받는다. 이 특정한 조건을 서술자라고 하고, 서술자는 보통 bool를 리턴하는 functor이다.

첫번째 알고리즘으로는 sort가 있다. sort에도 3가지 종류가 있는데, sort, stable_sort, partial_sort이다
sort는 일반적인 정렬 함수, stable_sort는 정렬을 하되 원소들 간의 순서를 보존함 > 예를 들어 sort는 a,b 순으로 있는 상태에서, a,b가 같은
값이면 이를 출력할때 a,b / b,a 랜덤하게 나오지만, stable_sort는 순서를 보존하여, a,b로 나오게 된다. 이 때문에 sort보단 느리다
partial_sort는 배열의 일부분만 정렬

sort 함수는 컨테이너의 시작, 끝 지점은 인자로 받아서 사용 할 수 있으며 sort(vec.begin(), vec.end());
sort는 컨테이너가 랜덤access되는 거만 가능하다. 예를 들어 vector이다. list나 deque는 direction이라서 sort사용이 불가능하다.
sort는 기본적으로 오름차순으로 분류해주는데, 내림차순으로 하고 싶다면 sort의 3번째 인자에, 조건을 붙여준다.
struct int_compare {
	bool operator()(const int a, const int b) {
		return a > b;
	}
};
다음과 같이 bool 형식의 functor를 3번째 조건으로 사용. 
함수 객체(Functor)를 위한 구조체(struct)를 정의해주시고, 그 안에 bool operator() 함수를 만들어주면 함수 객체(Functor) 완성

partial_sort는 받는 인자가 (start, middle, end) 3개로 정렬은 start에서 end까지 중에 middle 까지만 수행하라는 것이다.
즉 start에서 middle 까진 오름차순으로 정렬하고, 이후는 random으로 두자.
--------------------------------------------------------------------------------------------------------------------------------
값을 제거 하는 방법에는 erase가 있다. iterator의 위치에 있는 원소를 제거하는 방식이다. 하지만 많은 작업을 수행하기에는 부족하다
따라서 remove을 사용한다. 그전에 앞서 erase함수의 2가지 form을 살펴보자
erase는 iterator을 인자로 받아 iterator 위치 원소제거 Iterator erase(Iterator pos);
다음으로는 iterator의 first, last 사이에 있는 모든 원소 지우는 방법 Iterator erase(Iterator first, Iterator last);
remove는 값을 실제로 제거한다는 의미보다는 제거하고자 하는 원소를 끝쪽으로 옮겨둔다는 의미가 더 맞는 의미이다
remove의 형태는 (시작, 끝, value) 순으로, 시작에서 끝까지 원하는 value 모두를 끝쪽으로 옮겨두고, iterarion은 삭제되지 않은 마지막에서 
한칸 앞의 iteration를 return한다.
따라서 remove는 보통 erase와 같이 사용한다. 즉 remove가 return하는 iteration에서 부터 end까지 지워버리면, remove가 요구하는 value값을
제거한 거만 남게 된다.
remove는 forwarditerator여서 다른 컨테이너에서도 사용 가능함
remove할 조건을 넣고 싶다면 remove_if를 사용하고 마지막 변수에 조건에 대한 함수를 넣으면 된다.
----------------------------------------------------------------------------------------------------------------------------------
람다 함수를 통해 우리는 이름없는 함수객체를 만들수 있다. 만약 람다 함수를 만든다면 다음 형태로 만들어 진다.
[capture list] (받는 인자) -> 리턴 타입 { 함수 본체 } / [](int i) -> bool { return i % 2 == 1; }
int i를 인자로 받고, bool을 리턴하는 함수이다. 리턴 타입을 생략하는 경우 [capture list] ( 받는 인자) {함수 본체} 형태
즉 [](int i) { return i % 2 == 1; } 꼴인데, 이때면 컴파일러가 알아서 함수 본체를 보고 return type을 추측해준다.
받는 인자에 값을 인가 하고 싶다면 [](int i) { return i % 2 == 1; }(3); 처럼 ()안에 인자 넣으면 되고 또는 함수 호출로 해결도 가능
람다 함수를 컨테이너에 대한 알고리즘의 조건문으로 사용한다면, 받는 인자는 컨테이너 안에 있는 값이 될 것이다.
따라서 따로 i값을 인가해 주지 않아도 작동이 된다.
또 중요한 점은 결국 람다 함수도 함수 인지라, 외부 변수를 접근하기 위해서 capture list을 사용한다. 해당 capture list에 외부에서 
선언된 변수의 레퍼런스(&)를 넣는다. 그러면 해당 레퍼런스를 람다 함수 내부에서 사용할 수 있게 되는 것이다.
레퍼런스를 사용하는 이유는 그 값을 람다 함수 내부에서 변경해야 하기 때문이다.
만약에 class 내부에서 맴버 함수로 람다를 사용하고, 맴버 변수를 capture list로 사용한다면 컴파일이 안될 것이다. 왜냐하면
맴버 함수는 private라기 때문이다.(람다의 capture list에 있는 것은 일반 변수로 생각하기 때문이다)
private한 맴버 변수를 사용하려면, this를 capture list에 넣고, this->맴버 변수 이런식으로 접근을 해야한다.
-----------------------------------------------------------------------------------------------------------------------
원소 수정(transform)
transform (시작 반복자, 끝 반복자, 결과를 저장할 컨테이너의 시작 반복자, Pred)의 형태는 다음과 같이 생겼다.
transform(vec.begin(), vec.end(), vec.begin(), [](int i) { return i + 1; });
즉 시작에서 끝까지에서 pred에 있는 조건을 실행하고 그것을 처음에서 부터 조건 실행한다는 느낌이다.
즉 위 코드 해석하면, 처음부터 끝까지, 원소 1씩 더하는 조건을 처음에서 새로운 컨테이너로 더한다.
주의해야 할 점은 조건이 실행되는 칸이 컨테이너의 크기보다 크면 안된다. 즉 저 코드에서 3번째 인자인 vec.begin()을 vec.begin()+1하면
새로운 컨테이너가 채워지다가, 마지막 한칸이 남게 되는 문제가 생긴다.  > for문 사용 안하고 컨테이너에 반복 작업 실행 가능
--------------------------------------------------------------------------------------------------------------------------
원소 탐색하는 함수(find, `find_if, any_of, all_of)
std::find(vec.begin(), vec.end(), 3); 꼴로 처음부터 끝까지 탐색하여 3이라는 value를 찾으면, 해당 value의 위치의 iteration을
리턴하는 함수이다. 동일한 value가 있다면 먼저 찾은 거의 iteration을 return한다. 해당 위치를 표시하기 위해 distance라는 것을
사용해서, distance(vec.begin(), find로 리턴한 iteration)하면 찾은 value의 위치를 알려준다.
만약 동일한 원소를 계속 찾고자 한다면, while문을 사용하여, 첫번째 찾은 value의 iteration을 재귀함수로 다시 vec.begin() 대신
작성하면 된다
즉 auto current = vec.begin(); / current = std::find(current, vec.end(), 3) 와 같다.
하지만 유의사항은 만약 컨테이너에서 find를 지원한다면 컨테이너 find를 사용하자. 왜냐하면 알고리즘 find는 컨테이너의 정보도 모른체
작동하는데, 컨테이너의 find는 정보를 알고 작동하기 때문에 빠른 속도를 나타낼 것이다.
또한 find_if를 사용하면 마지막 변수로 들어가는 것을 조건문 람다함수로 사용할 수 있다.
마지막으로 all_of 와 any_of는 all_of는 범위안에 있는 모든 인자가 주어진 조건을 만족해야지만 true를 내보내는 함수이고
any_of는 범위 안에 있는 모든 인자중 주어진 조건을 하나라도 만족을 하면 true를 리턴한다.
------------------------------------------------------------------------------------------------------------------------
이러한 알고리즘을 사용하는데, std::하고 사용할 알고리즘 사용하면 된다.
*/