#include <iostream>
#include <string>

int main() {
	std::string s;
	std::cin >> s;

	// 위치 지정자를 한 칸 옮기고, 그 다음 문자를 훔쳐본다 (이 때는 움직이지 않음)
	char peek = std::cin.rdbuf()->snextc();

	std::cout << "첫 번째 단어 : " << s << std::endl;

	if (std::cin.fail()) std::cout << "Failed";
	std::cout << "두 번째 단어 맨 앞글자 : " << peek << std::endl;

	std::cin >> s; //두번째 단어가 입력된다 , 처음 값을 입력할 때, 띄어쓰기 있게 입력하면 띄어쓰기 이후가 이부분이 됨

	std::cout << "다시 읽으면 : " << s << std::endl;
}


/*
출력, 입력 라이브러리 > iostream
iostream은 여러 class를 상속하고 있다.
1. ios_base > 2.ios > 3.istream > 4.ostream > 5.iostream

1. ios_base : 입출력 형식 관련 data 처리
2. ios : 스트림 버퍼 초기화 > 즉 data를 읽을 때, 여러 byte data를 잠시 유지해놓는 곳 관련 class
3. istream : 본격적으로 입력에 수행되는 class > cin이 해당 class의 객체로 사용됨

istream 안에는 operator>>에서 여러 인자를 받는 함수들이 여러개 존재한다.
따라서 어떤 인자를 >> 옆에 붙히느냐에 따라 해당되는 함수가 불러오게 되는것이다.
또 다른 특징으로는 >> 는 공백문자 입력시 무시한다는 점이다.
즉 한 문장을 입력해도 띄어쓰기 기준으로 다른 string으로 인식하여, 만약 하나만 출력한다고 했을 때,
띄어쓰기 기준으로 그 이후는 사라지게 된다.
하지만 만약 정수형 변수를 입력으로 했는데, 입력하기를 문자를 입력하였을 때, 이상한 값이 출력되는 문제가 있다.

이는 ios class에 있는 flag bit와 관련이 있다. ios class에는 4종류의 flag bit가 있는데, 이들은
goodbit, badbit, failbit, eofbit 이렇게 4종류이다. 근데 윗 상황은 failbit가 켜진 상태이며
스트림에 복구 가능한 오류가 발생한 상태이다. 하지만 이 경우에는 스트림 버퍼에 저장되게 되는 '입력 문자 \n'이
제거 되지 않고 유지되어서, 계속해서 잘못 입력한 것이 유지되는 상태가 된다.

이게 NULL을 return하는 ios class 함수 >>>> operator void*() const;
해당 문제를 해결하기 위해서는 ios에서 사용되는 함수인 void*로 값을 변환하는 함수가 사용된다.
이 함수는 값이 제대로 들어왔다. 즉 badbit, failbit가 1이 되지 않는 경우, NULL을 리턴하지 않는다.
하지만 반대의 경우, 즉 int 형인데, 문자를 입력하였을 때, NULL이 return이 되게 된다.
여기서 compiler는 while문에는 bool이 맞는 형태이기 때문에, NULL은 FALSE로 변환하여,
잘못 입력된 입력에 대하여 while문을 벗어나게 만든다.

하지만 while문을 벗어나는 문제는 해결 할 수 있지만, 스트림 버퍼에 있는 값을 제거하지 못하는 문제를 해결하지 못하였다
즉 cin에 더이상 입력을 진행 할 수 없게 된다는 것이다. flag을 초기화해버리지 않는다면.
>> (즉 failbit가 켜지면 그 이후 cin에서는 입력을 받을 수 없게 된다.) ***********************

그때 사용되는 cin의 객체의 함수들 > std::cin.fail() / std::cin.clear() / std::cin.ignore()
fail은 cin으로 받은 입력으로 인하여, failbit나 badbit가 켜졌을 때 1을 내보내는 함수
clear는 flagbit을 초기화해서, goodbit로 만드는 역할 > fail 상태를 지울 수 있다
ignore는 최대 첫인자 만큼 두번째 문자가 나올 때까지 무시하겠다.
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

다음으로는 ios_base에 있는 함수 중에 16진법을 10진법으로 변환해주는 함수를 볼것이다.
이는 std::cin.setf 함수를 사용한다. 이 밖에서 std::hex이라는 함수도 사용 가능하다.
std::cin.setf(std::ios_base::hex, std::ios_base::basefield)는 입력으로 받은 값을 basefield에 넣었다가
해당 basefield에 있는 값을 초기화 시킨 후, hex로 바꾸는 함수를 의미한다.

또다른 방벙인 std::hex는 조작자라고 해서, std::cin이 받는 입력의 형식을 바꿔버리는 역할을 한다.
여기서는 hex로 조작해서 받게 된다. 이는 ios에 들어있는 함수이다

여기서 알 수 있는 사실은 std::(함수)로 우리는 수많은 조작자 함수를 사용할 수 있다는 점이다.
std::hex, std::left와 같이 필요할 때마다 불러서 사용가능하다.

앞서 말했던 것처럼 스트림 버퍼에 담겻다가 출력한다 했는데, 바로바로 출력하기 위해서, std::flush함수를 사용

int main() {
  std::string s;
  std::cin >> s;

  // 위치 지정자를 한 칸 옮기고, 그 다음 문자를 훔쳐본다 (이 때는 움직이지 않음)
  char peek = std::cin.rdbuf()->snextc();
  if (std::cin.fail()) std::cout << "Failed";
  std::cout << "두 번째 단어 맨 앞글자 : " << peek << std::endl;
  std::cin >> s;
  std::cout << "다시 읽으면 : " << s << std::endl;
}

stream 버퍼의 수행을 볼 수 있는 코드이다.
s를 통해 받은 문자열이 스트림 버퍼에 들어가게 된다. 이때 입력 문자열의 현재 위치를 가리키고 있는 포인터는 띄어쓰기
가 있는 부분일 것이다. 만약 띄어쓰기 있는 문자열이라면 왜냐하면 그 전까지는 이미 s에 들어가고, 띄어쓰기는 이후는
무시하기 때문이다.
즉 문자열 : hello world라면 hello가 스트림에 들어갔고, 포인터는 o 다음 띄어쓰기에 위치함
여기서 rdbuf() 함수로 스트림버퍼를 불러오며, snextc() 함수를 통해, 현재 포인터 위치에서 한칸 이동한 후,
이동한 칸에 있는 값을 읽는다. 여기서 중요한 점은 값을 엿본다는 것이다. 즉 값을 읽은 후 포인터는 원래 다음칸으로 이동
하지만, 엿본다는 점에서 그 값을 읽고 그 위치를 유지한다.
그래서 peek를 읽으면 w가 나오고, 계속 그 위치에 있어서 다음 값, 즉 띄어쓰기 다음 값을 읽었을 때, 또 w가 포함된
world가 출력되게 되는 것이다.

또한 이 함수들은 streambuf라는 class에 포함되어 있다.
*/