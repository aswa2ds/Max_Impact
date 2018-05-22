#include <iostream>
#include <vector>
#include <sstream>
#include <stack>

using namespace std;

enum color_type { WHITE, GREY, BLACK };
int cnum = 0;

class vertex {
private:
	color_type color;
	vector<int> list;
public:
	vertex() {
		this->color = WHITE;
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

class SCC {
private:
	int num;
	color_type color;
	int impact;
	vector<int> iner;
	vector<int> list;
public:
	SCC() {
		this->num = cnum++;
		this->color = WHITE;
		this->impact = 0;
	}
	~SCC() {
		this->iner.clear();
		this->list.clear();
	}
	void insert_iner(int v){
		this->iner.push_back(v);
	}
	void insert_list(int n){
		this->list.push_back(n);
	}
};

stack<int> end_list;
vector<vertex> vertex_list;
vector<vertex> reverse_G;
vector<SCC> C_G;

void SCC();
void find_end(int);
void create_C_G();

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
	cout << "vertex_list:" << endl;
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
	/*while (!end_list.empty()) {
		cout << end_list.top() << " ";
		end_list.pop();
	}*/
	for (unsigned i = 0; i < vertex_list.size(); ++i) {
		vertex v;
		reverse_G.push_back(v);
	}
	//cout << reverse_G.size() << endl;
	for (unsigned i = 0; i < vertex_list.size(); ++i) {
		for (int j = 0; j < vertex_list[i].list_len(); ++j) {
			int v = vertex_list[i].at(j);
			reverse_G[v].insert(i);
		}
	}
	cout << "reverse_G:" << endl;
	for (unsigned i = 0; i < reverse_G.size(); ++i) {
		cout << i << "->";
		reverse_G[i].print();
	}
	cout << endl;
	create_C_G();
}

void find_end(int u) {
	//cout << u << endl;
	vertex_list[u].color_change(GREY);
	for (int i = 0; i < vertex_list[u].list_len(); ++i) {
		int v = vertex_list[u].at(i);
		if (vertex_list[v].get_color() == WHITE)
			find_end(v);
	}
	end_list.push(u);
	vertex_list[u].color_change(BLACK);
}

void create_C_G(){
	while(!end_list.empty()){
		int v = end_list.top();
		end_list.pop();
		if(reverse_G[v].get_color() == WHITE){
			reverse_G[v].color_change(GREY);
			
		}
	}
}
