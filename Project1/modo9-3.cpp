/*
#include <iostream>

template <typename T>
class Array {
public:
	Array(int n) : data(new T[n]), n(n) {};
	
	~Array() {
		delete[] data;
	}

	void getarray(T *arr) {
		for (int i = 0; i < n; i++)
		{
			data[i] = arr[i];
		}
	}

	void print() {
		for (int i = 0; i < n; i++) {
			std::cout << data[i] << ", ";
		}
		std::cout << std::endl;
	}

private:
	T* data;
	unsigned int n;
};

int main() {
	int arr_w[5] = {1,2,3,4,5};

	Array<int> arr(5);

	arr.getarray(arr_w);
	arr.print();

}
*/

#include <iostream>

// 기본 템플릿: 피보나치 수열 계산 여기서 앞선 값이 정해져 있지 않더라도 연산이 가능하다.
template<int N>
struct Fibonacci {
	static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

// 특수화 템플릿: 피보나치 수열의 기본값 설정
template<>
struct Fibonacci<0> {
	static const int value = 0;
};

template<>
struct Fibonacci<1> {
	static const int value = 1;
};

int main() {
	const int fib10 = Fibonacci<5>::value; // Fibonacci<10>을 컴파일 타임에 계산
	std::cout << "Fibonacci<10>::value = " << fib10 << std::endl;

	return 0;
}


/*
다른 템플릿 인자로 인스턴스화 하면 다른 코드를 생성하며, 두 개의 tpye이 다른 것으로 나타나게 된다
즉 Array<int, 5> Array<int, 3> 은 서로 다른 type이 되는 것이다.

마치 객체를 선언하듯 타입을 선언 할 수 있다. tpyedef (struct)<인자> 객체이름 이런식으로 선언 할 시
객체 이름을 가진 type을 선언 할 수 있는 것이다. 이때 사용해야 하는 것은 static const 이다
이는 class 내부에서 값을 초기화 할 수 있는 것은 static const 밖에 없기 때문이다.

#include <iostream>
#include <typeinfo>

template <int N>
struct Int {
  static const int num = N;
};

template <typename T, typename U>
struct add {
  typedef Int<T::num + U::num> result;
};

int main() {
  typedef Int<1> one;
  typedef Int<2> two;

  typedef add<one, two>::result three;

  std::cout << "Addtion result : " << three::num << std::endl;
}

해당 예시를 살펴보면 일단 typedef를 사용하기 위해서, header로 typeinfo를 사용했고, static const로 type를 선언하기 위한
준비를 하였다
typedef Int<1> one; 에서 보는 것처럼 마치 one 객체를 선언한 거같은데, one은 객체가 아니라 one이라는 type이 선언 된 것이고, one 타입은
num = 1을 가지고 있는 것로 해석할 수 있다. 따라서 add struct에서 처럼 ::를 사용해서 one 타입의 num을 가지고 새로운 타입을 만들 수 있다

using을 사용한다면 기존에 typedef로 마치 객체 선언 하듯이 선언한 새로운 타입의 이름을, 객체처럼 선언하지 않고 직관적으로 이해 할 수 있다.
즉 typedef Ratio<2, 3> rat; 처럼 rat 객체가 아니라 타입을 선언하는 것에서, using rat = Ratio<2,3> 하면 직관적으로 rat 타입이
만들어 지는 것으로 볼 수 있다
새로운 타입을 선언 할 때, 객체처럼이 아니라, using을 써서 직관적 타입 생성 가능
앞에서 말 하였던 것 처럼, 타입만을 가지고 연산을 하는 것을 TMP라고 한다. 속도가 중요한 경우, 이처럼 타입만 가지고 연산을 
진행하는 TMP를 사용한다. 하지만 코드 작성하기에 어렵고, 디버깅이 매우 어렵다는 단점을 가지고 있다.
*/