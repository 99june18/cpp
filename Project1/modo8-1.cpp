#include <iostream>
#include <string>

using namespace std;

class Cell {
protected:
	int x, y;
	Table* table;

	string data;

public:
	virtual string stringify();
	virtual int to_numeric();

	Cell(string data, int x, int y, Table* table) : data(data), x(x), y(y), table(table) {}
};

string Cell::stringify() { return data; }

int Cell::to_numeric() { return 0; }

class Table{
protected:
	// 행 및 열의 최대 크기
	int max_row_size, max_col_size;

	// 데이터를 보관하는 테이블
	// Cell* 을 보관하는 2차원 배열이라 생각하면 편하다
	// 값이 인가 될 때마다, Cell pointer를 이용해서, cell class address get.
	Cell* ** data_table;

public:
	Table(int max_row_size, int max_col_size);

	~Table();

	// 새로운 셀을 row 행 col 열에 등록한다.
	void reg_cell(Cell* c, int row, int col) {
		if (row > max_row_size || col > max_col_size) {
			return;
		}

		if (data_table[row][col]) {
			delete data_table[row][col];
		}
		data_table[row][col] = c;
	}

	// 해당 셀의 정수값을 반환한다.
	// s : 셀 이름 (Ex. A3, B6 과 같이)
	int to_numeric(const string& s) {
		int col = s[0] - 'A';
		int row = atoi(s.c_str() + 1) - 1;

		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col]) {
				return data_table[row][col]->to_numeric();
			}
		}

		return 0;
	}

	// 행 및 열 번호로 셀을 호출한다.
	int to_numeric(int row, int col) {
		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col]) {
				return data_table[row][col]->to_numeric();
			}
		}
		return 0;
	}

	// 해당 셀의 문자열을 반환한다.
	string stringify(const string& s) {
		int col = s[0] - 'A';
		int row = atoi(s.c_str() + 1) - 1;

		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col]) {
				return data_table[row][col]->stringify();
			}
		}

		return "";
	}

	string stringify(int row, int col) {
		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col]) {
				return data_table[row][col]->stringify();
			}
		}
		return "";
	}

	virtual string print_table() = 0;
};

Table::Table(int max_row_size, int max_col_size) : max_row_size(max_row_size), max_col_size(max_col_size) {
	data_table = new Cell ** [max_row_size];
	for (int i = 0; i < max_row_size; i++)
	{
		data_table[i] = new Cell * [max_col_size];
		for (int j = 0; j < max_col_size; j++)
		{
			data_table[i][j] = NULL;
		}
	}
}

Table::~Table() {
	//Cell 각각 지우기
	for (int i = 0; i < max_row_size; i++) {
		for (int j = 0; j < max_col_size; j++) {
			if (data_table[i][j]) delete data_table[i][j];
		}
	}
	//Table 할당 지우기
	for (int i = 0; i < max_row_size; i++) {
		delete[] data_table[i];
	}
	delete[] data_table;
}

std::ostream& operator<<(std::ostream& o, Table& table) {
	o << table.print_table();
	return o;
}

class TxtTable : public Table {
	string repeat_char(int n, char c) {
		string s = "";
		for (int i = 0; i < n; i++)
		{
			s.push_back(c);
		}
	}

	// 숫자로 된 열 번호를 A, B, .... Z, AA, AB, ...  이런 순으로 매겨준다.
	string col_num_to_str(int n) {
		string s = "";

		if (n < 26) {
			s.push_back('A' + n);
		}

		else
		{
			char first = 'A' + (n / 26) - 1;
			char second = 'A' + (n % 26);

			s.push_back(first);
			s.push_back(second);
		}
	}

public:
	TxtTable(int row, int col) : Table(row,col) {}

	// 텍스트로 표를 깨끗하게 출력해준다.
	string print_table() {

		int* max_col_width = new int[max_col_size];

		for (int i = 0; i < max_col_size; i++)
		{
			int max_width = 2;
			for (int j = 0; j < max_row_size; j++)
			{
				if (data_table[j][i]) {
					max_width = data_table[j][i]->stringify().length();
				}
			}
			max_col_width[i] = max_width;
		}

		string table = "   ";
		int total_col = 4;
		for (int i = 0; i < max_col_size; i++)
		{
			if (max_col_width[i]) {
				int size = max_col_width[i];
				table += "|  ";
				table += col_num_to_str(i);
				table += repeat_char(size - col_num_to_str(i).length(), ' ');

				total_col += (size + col_num_to_str(i).length() + 1);
			}
		}

		table += "\n";

		for (int i = 0; i < max_row_size; i++)
		{
			table += repeat_char(total_col, '-');
			table += "\n";
			table += to_string(i + 1);
			table += repeat_char(2, ' ');
			for (int j = 0; j < total_col; j++)	
			{
				if (data_table[i][j]) {
					table += "| ";
					table += data_table[i][j]->stringify();
					table += repeat_char(max_col_width[j] - data_table[i][j]->stringify().length() - 2, ' ');
				}
				
			}
			table += "\n";
		}

		return table;
	}
};

int main() {
	TxtTable table(5, 5);

	table.reg_cell(new Cell("Hello~", 0, 0, &table), 0, 0);
	table.reg_cell(new Cell("C++", 0, 1, &table), 0, 1);

	table.reg_cell(new Cell("Programming", 1, 1, &table), 1, 1);
	table.print_table();
}

/*
excel 만들기
사용할 2가지 자료구조들
1.vector : 배열의 크기를 맘대로 조절할 수 있는 가변 길이 배열
즉 배열처럼 [] 연산자로 원하는 위치에 접근가능
2.stack : 최 상단에 있는 데이터에만 접근가능한 구조
push 새로운 것을 쌓는다. pop 맨 위에 있는 data를 뺀다.

Vector::Vector(int n = 1)의 생성자에서 int n = 1이 의미하는 것은 디폴트 인자인데
이는 1를 넣는 것이 아니라, 아무 인자, 즉 어떠한 정수를 넣지 않는다면, 디폴트로 1이 인가가 된다는 의미이다
1이 들어간다는게 아니라, 2나 4을 넣으면 그것이 인가가 된다. 아무 것도 안넣었을 때만 1이 인가된다.
주의 사항 : 디폴트 인자를 class 내부 함수에서 선언을 하였다면, 외부 함수에선 선언해서는 안되고
외부 함수에서 선언하였다면, 내부 함수에선 선언해서는 안된다.
즉 둘 중 하나의 함수에서만 선언이 되어야 한다는 규칙이 있다.
*/