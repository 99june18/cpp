#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class A {
public:
	int a;

	A() { std::cout << "A ������ ȣ��" << std::endl;
	}

	virtual void print_A() {
		std::cout << a << std::endl;
	}
};

class B {
public:
	int b;

	B() { std::cout << "B ������ ȣ��" << std::endl;
	}

	virtual void print_B() {
		std::cout << b << std::endl;
	}
};

class C : public B, public A {
public:
	int c;

	C() : A(), B() { std::cout << "C ������ ȣ��" << std::endl;
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
virtual Ű���� 
parent, child class�� ���� ��, child�� parent�� ����Ͽ��� ��, parent�� �Լ� f�� virtual�� ���Ǿ���.
���⼭, Parent* p = new Parent();, Parent* c = new Child(); �̰�
p->f();
c->f(); �� ����Ѵٸ�, p�� c��� parent�� f�Լ��� �ҷ��ð����� ������ �Ǵµ�, virtual�� ���Ͽ�
p�� �״�� parent�� f�Լ�, c�� virtual�� ���Ͽ�, child�� f�Լ��� �ҷ��� ���̴�. > f�� �����Լ�

virtual �Ҹ���
Parent* p = new Child();
delete p;
�ش� �ڵ忡�� parent�� �Ҹ��ڿ� virtual�� ������ �ʾҴٸ�, ���� �ڵ��� ������� child�� �Ҹ��ڴ� ȣ����� �ʴ´�.
�ֳ��ϸ�, p�� Parent class�� �Ҹ��ڸ� �ҷ����� �ڵ尡 �ۼ��Ǿ� �ֱ� �����̴�.
�̴� Child class�� �޸� ���� ������ �ҷ� �� �� �ִ�.
�츮�� ����, parent�� �Ҹ��ڿ� virtual�� �޾��ָ�, delete p���� p�� child�� �Ҹ��ڸ� ȣ���ϰ� �Ǿ�, child�� �Ҹ��ڸ�
�θ���.
�׷��ٸ� parent �Ҹ��ڴ� ��� �Ǵ°��ΰ�? > �̴� child �Ҹ��ڸ� ȣ���ϸ鼭, child �Ҹ��ڰ� �˾Ƽ� parent �Ҹ��ڸ�
ȣ���Ѵ�. �̴� parent�� child�� ��ӵǾ� �ִٴ� ��� �����̴�.
�ݸ鿡 parent �Ҹ��ڸ� ���� �θ���, parent�� ��� ��ӵǾ� �ִ°���, ��� �ϴ°� �ƴϱ⿡, child�� �Ҹ��ڸ�
�θ��� ���� ���̴�. (�� ĳ����) ����ϴ°��� �θ��� > ��ӵǴ� ���� �˾Ƽ� �Ǵ� ��.

������ ����, ���۷����ε� virtual�� ����� �����ϴ�.
A a;
B b;
A& c = b;
���� ��� c�� A�� ���۷��� ���� c�� A class �Լ��� �ҷ���������, virtual�� �ִٸ�, c�� B class�� �Լ��� �ҷ��� ���̴�.

��� �Լ��� �����Լ��� ����� ���� �ʳ�? > ������ �ϴ�
������ ��� �����Լ��� ����� �Ǹ�, �����ص尡 �����Ͽ�, �Լ� ȣ�� �ð����� ������ �� �ִ�.
�����Լ��� ���� ���̺��� �ѹ� ��ģ �Ŀ�, �ش� �Լ��� �Ѿ�� ������, ���� �� ���� �ɸ���.

#���� ���� �Լ�

class Animal {
public:
	Animal() {
		std::cout << "���� : ";
	}
	virtual ~Animal() {}
	virtual void speak() = 0;
};
���� speak �Լ��� ���� �Ǹ�, ���� ���� ���� �׳� =0�� �Ǿ� �ִ�. > �̴� �ݵ�� �������̵� �Ǿ�� �ϴ� �Լ���
���� �� �� ������, ���� ���� �Լ��� �Ҹ���. 
�̰��� Ư¡�� ��ü ������ �Ұ����ϰ�, �翬��, �ش� �Լ��� ����� �Ұ����ϴ�.
�� ���� �����Լ��� ��ü ������ �Ұ����ϰ�, �ν��Ͻ��ϱ� ���ؼ��� �ٸ� class�� ��� �Ǿ�߸� �Ѵ�.
�߻� Ŭ������� �Ҹ����

�׷��ٸ� ��ü�� ������� �� �߻� Ŭ������ �� ����ϳ�? > class�� ���赵��� �� �� �ִ�
�� �ش� ���赵�� ������ Ư¡�ִ� �ٸ� class�� ���� ����϶�� Ʋ�� ���ǰ� �ִ�.
�߰������� ���� Ŭ������ �����ͷδ� ����� �����Ͽ�, ���� ������ �����ϰ� ���� �����ϴ�.
Animal* dog = new Dog();
dog->speak();

#���� ���
�⺻���� �ٸ� ��Ӱ� ������, �ٸ� ���� �� class�� ���� class�� ����Ѵٴ� ���Դϴ�.
class C : public A, public B {
 public:
  int c;
};
�̷������� class c�� class A,B�� ����ϰ� �ִٴ� ���Դϴ�.
Ư���� ���� ������ ȣ�� ������ ����ϴ� �������� �¿�ȴٴ� ���̴�. �� > class C : public A, public B ��
A > B ������ �׻� ȣ��ǰ�, class C : public B, public A �� B > A ������ �׻� ȣ��ȴٴ� ���̴�.

Ư�� ������ ��ӵǴ� class���� ���� �̸��� ����, �Լ��� ������ �ִٸ�, ��� �޴� ��ü ���忡��
��� class�� ����, �Լ����� ������ ���� �ʴ´�. >  �̸� �ٸ���

���� ���̾Ƹ�� ��ӵ� ������ �Ǵµ�, �� class�� �� class�� ��� �ް�, �Ǵٸ� �� class�� �� class�� ��� �޴´�.
 1 > 2 > 4 �̷������� �ǰ� �Ǹ�, �ƹ��� �Ȱ�ġ���� �Ͽ���, 1���� 4�� ������ ��ġ�� �ȴ�.
   > 3 >
 �ش� ������ , 2,3�� virtual�� �ٿ��ָ� �ذ�ȴ�.
 
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

���� ����� ����, �� ������ ��ü�� ���� �� �ִٴ� ������ ������, �ʹ� ���� ��ӿ� ������ �ʿ�� ����.
*/