#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class A {
public:
	int a;

	A() { std::cout << "A 생성자 호출" << std::endl;
	}

	virtual void print_A() {
		std::cout << a << std::endl;
	}
};

class B {
public:
	int b;

	B() { std::cout << "B 생성자 호출" << std::endl;
	}

	virtual void print_B() {
		std::cout << b << std::endl;
	}
};

class C : public B, public A {
public:
	int c;

	C() : A(), B() { std::cout << "C 생성자 호출" << std::endl;
	}

	void print() {
		print_A();
		print_B();
		std::cout << c << std::endl;
	}
};

int main() { 
	C c;
	c.a = 1;
	c.b = 2;
	c.c = 3;

	c.print();
}


/*
virtual 키워드 
parent, child class가 있을 때, child가 parent을 상속하였을 때, parent의 함수 f에 virtual이 사용되었다.
여기서, Parent* p = new Parent();, Parent* c = new Child(); 이고
p->f();
c->f(); 를 사용한다면, p와 c모두 parent의 f함수를 불러올것으로 예상이 되는데, virtual로 인하여
p는 그대로 parent의 f함수, c는 virtual로 인하여, child의 f함수를 불러올 것이다. > f는 가상함수

virtual 소멸자
Parent* p = new Child();
delete p;
해당 코드에서 parent의 소멸자에 virtual이 사용되지 않았다면, 다음 코드의 결과에서 child의 소멸자는 호출되지 않는다.
왜냐하면, p는 Parent class의 소멸자를 불러오는 코드가 작성되어 있기 때문이다.
이는 Child class의 메모리 누수 문제로 불러 올 수 있다.
우리는 따라서, parent의 소멸자에 virtual을 달아주면, delete p에서 p가 child의 소멸자를 호출하게 되어, child의 소멸자를
부른다.
그렇다면 parent 소멸자는 어떻게 되는것인가? > 이는 child 소멸자를 호출하면서, child 소멸자가 알아서 parent 소멸자를
호출한다. 이는 parent가 child에 상속되어 있다는 사실 때문이다.
반면에 parent 소멸자를 먼저 부르면, parent는 어디에 상속되어 있는거지, 상속 하는게 아니기에, child의 소멸자를
부를수 없는 것이다. (업 캐스팅) 상속하는것을 부르면 > 상속되는 것은 알아서 되는 것.

포인터 말고, 레퍼런스로도 virtual의 사용이 가능하다.
A a;
B b;
A& c = b;
에서 비록 c는 A의 레퍼런스 여서 c는 A class 함수를 불러오겠지만, virtual이 있다면, c는 B class의 함수를 불러올 것이다.

모든 함수를 가상함수로 만들면 좋지 않나? > 가능은 하다
하지만 모두 가상함수로 만들게 되면, 오버해드가 증가하여, 함수 호출 시간에서 느려질 수 있다.
가상함수는 가상 테이블을 한번 거친 후에, 해당 함수로 넘어가기 때문에, 조금 더 오래 걸린다.

#순수 가상 함수

class Animal {
public:
	Animal() {
		std::cout << "동물 : ";
	}
	virtual ~Animal() {}
	virtual void speak() = 0;
};
에서 speak 함수를 보게 되면, 몸통 정의 없이 그냥 =0이 되어 있다. > 이는 반드시 오버라이딩 되어야 하는 함수로
정의 할 수 있으며, 순수 가상 함수로 불린다. 
이것의 특징은 객체 생성이 불가능하고, 당연히, 해당 함수도 사용이 불가능하다.
즉 순수 가상함수는 객체 생성이 불가능하고, 인스턴스하기 위해서는 다른 class에 상속 되어야만 한다.
추상 클래스라고도 불리운다

그렇다면 객체도 못만드는 이 추상 클래스를 왜 사용하나? > class의 설계도라고 볼 수 있다
즉 해당 설계도로 개개인 특징있는 다른 class를 만들어서 사용하라는 틀로 사용되고 있다.
추가적으로 가상 클래스는 포인터로는 사용이 가능하여, 동적 선언이 가능하게 설계 가능하다.
Animal* dog = new Dog();
dog->speak();

#다중 상속
기본적인 다른 상속과 같지만, 다른 점은 한 class가 여러 class를 상속한다는 점입니다.
class C : public A, public B {
 public:
  int c;
};
이런식으로 class c가 class A,B를 상속하고 있다는 것입니다.
특이한 점은 생성자 호출 순서는 상속하는 순서에만 좌우된다는 점이다. 즉 > class C : public A, public B 면
A > B 순으로 항상 호출되고, class C : public B, public A 면 B > A 순으로 항상 호출된다는 점이다.

특이 사항은 상속되는 class들이 같은 이름의 변수, 함수를 가지고 있다면, 상속 받는 객체 입장에선
어느 class의 변수, 함수인지 구별이 되지 않는다. >  이름 다르게

또한 다이아몬드 상속도 문제가 되는데, 두 class가 한 class를 상속 받고, 또다른 한 class가 두 class를 상속 받는다.
 1 > 2 > 4 이런식으로 되게 되면, 아무리 안겹치려고 하여도, 1에서 4의 변수가 겹치게 된다.
   > 3 >
 해당 문제는 , 2,3에 virtual을 붙여주면 해결된다.
 
 class Human {
 public:
  // ...
};
class HandsomeHuman : public virtual Human {
  // ...
};
class SmartHuman : public virtual Human {
  // ...
};
class Me : public HandsomeHuman, public SmartHuman {
  // ...
};

다중 상속을 통해, 더 세밀한 객체를 만들 수 있다는 장점이 있지만, 너무 다중 상속에 집착할 필요는 없다.
*/