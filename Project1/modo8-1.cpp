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
	// �� �� ���� �ִ� ũ��
	int max_row_size, max_col_size;

	// �����͸� �����ϴ� ���̺�
	// Cell* �� �����ϴ� 2���� �迭�̶� �����ϸ� ���ϴ�
	// ���� �ΰ� �� ������, Cell pointer�� �̿��ؼ�, cell class address get.
	Cell* ** data_table;

public:
	Table(int max_row_size, int max_col_size);

	~Table();

	// ���ο� ���� row �� col ���� ����Ѵ�.
	void reg_cell(Cell* c, int row, int col) {
		if (row > max_row_size || col > max_col_size) {
			return;
		}

		if (data_table[row][col]) {
			delete data_table[row][col];
		}
		data_table[row][col] = c;
	}

	// �ش� ���� �������� ��ȯ�Ѵ�.
	// s : �� �̸� (Ex. A3, B6 �� ����)
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

	// �� �� �� ��ȣ�� ���� ȣ���Ѵ�.
	int to_numeric(int row, int col) {
		if (row < max_row_size && col < max_col_size) {
			if (data_table[row][col]) {
				return data_table[row][col]->to_numeric();
			}
		}
		return 0;
	}

	// �ش� ���� ���ڿ��� ��ȯ�Ѵ�.
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
	//Cell ���� �����
	for (int i = 0; i < max_row_size; i++) {
		for (int j = 0; j < max_col_size; j++) {
			if (data_table[i][j]) delete data_table[i][j];
		}
	}
	//Table �Ҵ� �����
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

	// ���ڷ� �� �� ��ȣ�� A, B, .... Z, AA, AB, ...  �̷� ������ �Ű��ش�.
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

	// �ؽ�Ʈ�� ǥ�� �����ϰ� ������ش�.
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
excel �����
����� 2���� �ڷᱸ����
1.vector : �迭�� ũ�⸦ ����� ������ �� �ִ� ���� ���� �迭
�� �迭ó�� [] �����ڷ� ���ϴ� ��ġ�� ���ٰ���
2.stack : �� ��ܿ� �ִ� �����Ϳ��� ���ٰ����� ����
push ���ο� ���� �״´�. pop �� ���� �ִ� data�� ����.

Vector::Vector(int n = 1)�� �����ڿ��� int n = 1�� �ǹ��ϴ� ���� ����Ʈ �����ε�
�̴� 1�� �ִ� ���� �ƴ϶�, �ƹ� ����, �� ��� ������ ���� �ʴ´ٸ�, ����Ʈ�� 1�� �ΰ��� �ȴٴ� �ǹ��̴�
1�� ���ٴ°� �ƴ϶�, 2�� 4�� ������ �װ��� �ΰ��� �ȴ�. �ƹ� �͵� �ȳ־��� ���� 1�� �ΰ��ȴ�.
���� ���� : ����Ʈ ���ڸ� class ���� �Լ����� ������ �Ͽ��ٸ�, �ܺ� �Լ����� �����ؼ��� �ȵǰ�
�ܺ� �Լ����� �����Ͽ��ٸ�, ���� �Լ����� �����ؼ��� �ȵȴ�.
�� �� �� �ϳ��� �Լ������� ������ �Ǿ�� �Ѵٴ� ��Ģ�� �ִ�.
*/