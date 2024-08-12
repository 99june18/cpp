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

// �⺻ ���ø�: �Ǻ���ġ ���� ��� ���⼭ �ռ� ���� ������ ���� �ʴ��� ������ �����ϴ�.
template<int N>
struct Fibonacci {
	static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

// Ư��ȭ ���ø�: �Ǻ���ġ ������ �⺻�� ����
template<>
struct Fibonacci<0> {
	static const int value = 0;
};

template<>
struct Fibonacci<1> {
	static const int value = 1;
};

int main() {
	const int fib10 = Fibonacci<5>::value; // Fibonacci<10>�� ������ Ÿ�ӿ� ���
	std::cout << "Fibonacci<10>::value = " << fib10 << std::endl;

	return 0;
}


/*
�ٸ� ���ø� ���ڷ� �ν��Ͻ�ȭ �ϸ� �ٸ� �ڵ带 �����ϸ�, �� ���� tpye�� �ٸ� ������ ��Ÿ���� �ȴ�
�� Array<int, 5> Array<int, 3> �� ���� �ٸ� type�� �Ǵ� ���̴�.

��ġ ��ü�� �����ϵ� Ÿ���� ���� �� �� �ִ�. tpyedef (struct)<����> ��ü�̸� �̷������� ���� �� ��
��ü �̸��� ���� type�� ���� �� �� �ִ� ���̴�. �̶� ����ؾ� �ϴ� ���� static const �̴�
�̴� class ���ο��� ���� �ʱ�ȭ �� �� �ִ� ���� static const �ۿ� ���� �����̴�.

#include <iostream>
#include <typeinfo>

template <int N>
struct Int {
  static const int num = N;
};

template <typename T, typename U>
struct add {
  typedef Int<T::num + U::num> result;  (type::type�� ���� �� �ϳ� ����)�� ���� Ÿ���� ����� �� �ִ�.
};

int main() {
  typedef Int<1> one;
  typedef Int<2> two;

  typedef add<one, two>::result three;  //main���� ������ type�� �ٸ� �Լ����� ������ type�� ����� ���, ������ ���� ���
  �� ������ type�� ������ ������ �� ::�� ������ �ǰ�, ������ type�� �̿��ؼ� �� type�� type�� ����ҷ���, ::�ϰ� �� �ۼ�

  std::cout << "Addtion result : " << three::num << std::endl;
}

�ش� ���ø� ���캸�� �ϴ� typedef�� ����ϱ� ���ؼ�, header�� typeinfo�� ����߰�, static const�� type�� �����ϱ� ����
�غ� �Ͽ���
typedef Int<1> one; ���� ���� ��ó�� ��ġ one ��ü�� ������ �Ű�����, one�� ��ü�� �ƴ϶� one�̶�� type�� ���� �� ���̰�, one Ÿ����
num = 1�� ������ �ִ� �ͷ� �ؼ��� �� �ִ�. ���� add struct���� ó�� ::�� ����ؼ� one Ÿ���� num�� ������ ���ο� Ÿ���� ���� �� �ִ�

using�� ����Ѵٸ� ������ typedef�� ��ġ ��ü ���� �ϵ��� ������ ���ο� Ÿ���� �̸���, ��üó�� �������� �ʰ� ���������� ���� �� �� �ִ�.
�� typedef Ratio<2, 3> rat; ó�� rat ��ü�� �ƴ϶� Ÿ���� �����ϴ� �Ϳ���, using rat = Ratio<2,3> �ϸ� ���������� rat Ÿ����
����� ���� ������ �� �� �ִ�
���ο� Ÿ���� ���� �� ��, ��üó���� �ƴ϶�, using�� �Ἥ ������ Ÿ�� ���� ����
�տ��� �� �Ͽ��� �� ó��, Ÿ�Ը��� ������ ������ �ϴ� ���� TMP��� �Ѵ�. �ӵ��� �߿��� ���, ��ó�� Ÿ�Ը� ������ ������ 
�����ϴ� TMP�� ����Ѵ�. ������ �ڵ� �ۼ��ϱ⿡ ��ư�, ������� �ſ� ��ƴٴ� ������ ������ �ִ�.
*/