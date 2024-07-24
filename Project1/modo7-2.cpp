#include <iostream>
#include <sstream>
#include <string>

std::string to_str(int x) {
    std::ostringstream ss;
    ss << x;

    return ss.str();
}
int main() {
    std::cout << "문자열로 변환:: 1 + 2 = " << to_str(1 + 2) << std::endl;

    return 0;
}

/*
    file의 입출력을 위해서는 header file로 fstream을 사용해서 file의 값을 받을 수 있다
    std::ifstream 을 이용해서 객체를 생성하고, 객체를 통해 열고자 하는 file을 받는다.
    열고자 하는 file이 있는지 > open되었는지를 확인 하기 위해서는 ifstream의 객체.open()/ open함수를 사용해서
    확인 가능하고, 값을 읽기위해서, cin에서 사용했던것 처럼 >> 사용한다.
    이때, 읽히는 값은 띄어쓰기까지 읽힌다.
    open된 file을 자동으로 닫아주는 close하는 기능은 소멸자로 ifstream이 보유하고 있기에, 자동으로 close해준다.
    
    하지만 같은 객체를 사용해서, 다른 file을 open하기 위해서는, 기존에 열었던 file을 닫아주는 code를 작성한 후
    다은 file을 열어주어야 한다 > 이때 객체.close() 함수 사용한다.

    >> file의 open > 객체 선언시 생성자로 사용해도 되고, 객체.open() 함수 사용가능
    >> file의 close > 소멸자로 스스로 close되지만, 같은 객체의 다른 file의 open하기 위해서는 자체적으로 close해야한다.
       객체.close() 함수 사용.

    file 전체 값을 읽기 위해서는 
    1.file안에 있는 data의 크기를 알아야 한다
    그러기 위해서는 seekg() 함수를 사용해서, 위치 지정자를 파일 끝으로 이동해주고, tellg() 함수를 사용해서,
    파일 끝이로 이동한 위치 지정자까지의 크기를 읽는다 > 처음 부터 끝까지의 크기를 읽으니깐 총 file안에 있는
    data의 크기를 읽는 것이 된다
    2.해당 크기 만큼의 buffer를 생성해주고, 그 값에 문자열을 배열해주면 된다.
    해당 크기 만큼의 buffer 생성은 string 변수에 resize() 함수를 사용해서, file 크기 만큼의 buffer 생성한다.
    이후 다시 위치 지정자를 처음으로 변환해주고 (seekg()), read() 함수를 사용해서, 해당 size만큼의 값을 buffer에 부여
    한 후 값을 읽으면 된다.
     
    if (in.is_open()) {
        in.seekg(0, std::ios::end);        >> 위치 지정자 파일 끝
        size = in.tellg();                 >> 크기 계산
        in.seekg(0, std::ios::beg);        >> 위피 지정자 처음으로 
        s.resize(size);                    >> 크기 만큼의 메모리 buffer 생성
        in.read(&s[0], size);              >> size만큼 값을 읽어서 s에 저장
        std::cout << s << std::endl;       >> 출력
    }

    getline 함수 : 파일에서 \n이 나올때 까지 최대 지정한 크기 -1만큼 읽는다.
    -1를 해주는 이유는 읽은 char 변수의 맨 마지막 문자로 null을 넣어서 종료하기 때문이다.
    \n 말고, 내가 원하는 문자가 나올때까지 값을 읽게 만들 수도 있다.
    getline(buf,100,'?')에서 ?가 나올때까지 읽는다 라는 것이다.
    한가지 주의 해야 할 점은 getline을 사용하기 위해서 char 변수를 사용하였는데, 만약 char 변수의 크기가 
    file안에 입력된 값에 비해 작게 형성되어 있다면, 그 전에 while문에서 문제가 발생한다.
    이 점을 예방하기 위해서, > string을 사용한다.
    
    getline(in, s)를 사용한다면, 따로 char의 크기를 지정할 필요가 없어진다.
    첫 인자 : file 객체이름 / 두번째 인자 : buffer에 저장될 string 이름
    
    file에 write하기
    std::ostream에 해당하는 객체를 생성하면 값의 write가 가능해진다. 만약 해당 file이 없다면 file을 생성하고
    write되게 된다. & write할때 std::ios::app의 조건을 붙여주면, write할때 값을 지우고 write하는게 아니라,
    그 위에 덧붙여서 값을 write하게 된다.

    ios::ate : 자동으로 파일 끝에서 부터 읽기와 쓰기를 실시합니다. 
    (즉 파일을 열 때 위치 지정자가 파일 끝을 가리키고 있게 됩니다)  >> app을 사용하면 거의 사용 안한다.

    ios::trunc : 파일 스트림을 열면 기존에 있던 내용들이 모두 지워집니다. 
    기본적으로 ofstream 객체를 생성할 때 이와 같은 설정으로 만들어집니다.

    ios::in, std::ios::out : 파일에 입력을 할 지 출력을 할 지 지정하며, 
    ifstream 과 ofstream 객체를 생성할 때 각각은 이미 설정되어 있습니다.

    ofstream도 역시 연산자 오버로딩이 가능하다. 

    마지막으로 문자열 스트림 (std::stringstream)의 기능은 이 객체로 부터 받은 정보를 마치 파일에 기록해 두고
    거기서 입력을 받는 것처럼 기능을 한다. 가상의 스트림 버퍼역할을 한다.

    istringstream은 객체에서 입력 받은 값을 >> 를 통해 주어지는 변수의 type에 맞춰 주는 것으로 보면 된다
    마치 atoi처럼 생각하면 된다.

    std::istringstream ss(s);
    double x;
    ss >> x;
    보면 ss객체로 받은 string type의 s를 double type의 x로 주면서, s값이 출력될 때, double type이 된다.

    반대로 ostringstream의 경우, 반대의 작업이 진행된다.

    std::string to_str(int x) {
    std::ostringstream ss;
    ss << x;
    return ss.str();
    }

    int x로 받은 값을 문자열 ss로 변환해준다.
*/