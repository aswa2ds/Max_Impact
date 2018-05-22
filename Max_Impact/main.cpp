#include <iostream>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

enum color_type { WHITE, GREY, BLACK };


class vertex {
private:
	color_type color;
	int impact;
	vector<int> list;
public:
	vertex() {
		this->color = WHITE;
		this->impact = 0;
	}
	~vertex() {
		this->list.clear();
	}
	color_type get_color() {
		return this->color;
	}
	void color_change(color_type color) {
		this->color = color;
	}
	int list_len() {
		return this->list.size();
	}
	int at(int i) {
		return this->list[i];
	}
	void insert(int n) {
		this->list.push_back(n);
	}
	void print() {
		for (unsigned i = 0; i < this->list.size(); ++i)
			cout << this->list[i] << " ";
		cout << endl;
	}
};

stack<int> end_list;
vector<vertex> vertex_list;

void SCC();
void find_end(int);

int main() {
	string line;
	int loop = 0;
	while (getline(cin, line, '\n')) {
		if (loop == 6)	break;
		vertex v;
		istringstream p_list(line);
		int num;
		while (p_list >> num) {
			v.insert(num);
		}
		vertex_list.push_back(v);
		//v.print();
		loop++;
	}
	for (unsigned i = 0; i < vertex_list.size(); ++i) {
		cout << i << "->";
		vertex_list[i].print();
	}
	SCC();
	return 0;
}

void SCC() {
	for (unsigned i = 0; i < vertex_list.size(); ++i)
		if (vertex_list[i].get_color() == WHITE) 
			find_end(i);
	while (!end_list.empty()) {
		cout << end_list.top() << " ";
		end_list.pop();
	}
}

void find_end(int u) {
	//cout << u << endl;
	vertex_list[u].color_change(GREY);
	for (int i = 0; i < vertex_list[u].list_len(); ++i) {
		int v = vertex_list[u].at(i);
		if (vertex_list[v].get_color() == WHITE)
			find_end(v);
		else
			return;
	}
	end_list.push(u);
	vertex_list[u].color_change(BLACK);
}