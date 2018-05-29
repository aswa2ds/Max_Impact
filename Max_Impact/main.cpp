#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <algorithm>

using namespace std;

enum color_type { WHITE, GREY, BLACK };
int cnum = 0;

class vertex {
private:
	color_type color;
	int belong;
	vector<int> list;
public:
	vertex() {
		this->color = WHITE;
		this->belong = -1;
	}
	~vertex() {
		this->list.clear();
	}
	void belong_change() {
		this->belong += cnum;
	}
	int get_belong() {
		return this->belong;
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
	vector<int> impact_list;
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
		this->impact += 1;
		this->iner.push_back(v);
	}
	color_type get_color() {
		return this->color;
	}
	void color_change(color_type color) {
		this->color = color;
	}
	void insert_list(int n){
		this->list.push_back(n);
	}
	void print_iner() {
		for (int i = 0; i < this->iner.size(); ++i)
			cout << this->iner[i] << " ";
		cout << endl;
	}
	void print_list() {
		for (int i = 0; i < this->list.size(); ++i)
			cout << this->list[i] << " ";
		cout << endl;
	}
	int get_num() {
		return this->num;
	}
	int iner_len() {
		return this->iner.size();
	}
	int list_len() {
		return this->list.size();
	}
	int iner_at(int i) {
		return this->iner[i];
	}
	int list_at(int i) {
		return this->list[i];
	}
	int get_impact() {
		return this->impact;
	}
	void impact_inser(int i) {
		this->impact_list.push_back(i);
	}
	void impact_plus(int impact) {
		this->impact += impact;
	}
	vector<int>::iterator iner_begin() {
		return this->iner.begin();
	}
	vector<int>::iterator iner_end() {
		return this->iner.end();
	}
};

stack<int> end_list;
vector<vertex> vertex_list;
vector<vertex> reverse_G;
vector<SCC> C_G;

void toSCC();
void find_end(int);
void create_C_G();
void SCC_DFS(int );

int main() {
	string line;
	//int loop = 0;
	while (getline(cin, line, '\n')) {
		//if (loop == 6)	break;
		vertex v;
		istringstream p_list(line);
		int num;
		while (p_list >> num) {
			v.insert(num);
		}
		vertex_list.push_back(v);
		//v.print();
		//loop++;
	}
	/*cout << "vertex_list:" << endl;
	for (unsigned i = 0; i < vertex_list.size(); ++i) {
		cout << i << "->";
		vertex_list[i].print();
	}*/
	toSCC();
	for (int i = 0; i < C_G.size(); ++i) {
		if (C_G[i].get_color() == WHITE)
			SCC_DFS(i);
	}
	int max_impact = 0;
	int C = 0;
	for (int i = 0; i < C_G.size(); ++i) {
		if (C_G[i].get_impact() >= max_impact) {
			C = i;
			max_impact = C_G[i].get_impact();
		}
	}
	cout << "I have read the rules about plagiarism punishment" << endl;
	cout << max_impact-1 << endl;
	sort(C_G[C].iner_begin(), C_G[C].iner_end());
	C_G[C].print_iner();
	return 0;
}

void toSCC() {
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
	/*cout << "reverse_G:" << endl;
	for (unsigned i = 0; i < reverse_G.size(); ++i) {
		cout << i << "->";
		reverse_G[i].print();
	}*/
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

void dfs(int v) {
	vertex_list[v].belong_change();
	for (int i = 0; i < reverse_G[v].list_len(); ++i) {
		int w = reverse_G[v].at(i);
		if (reverse_G[w].get_color() == WHITE) {
			C_G[cnum - 1].insert_iner(w);
			reverse_G[w].color_change(GREY);
			dfs(w);
		}
	}
	reverse_G[v].color_change(BLACK);
}

void create_C_G(){
	while(!end_list.empty()){
		int v = end_list.top();
		end_list.pop();
		if(reverse_G[v].get_color() == WHITE){
			reverse_G[v].color_change(GREY);
			SCC c;
			c.insert_iner(v);
			C_G.push_back(c);
			dfs(v);
		}
	}
	for (int i = 0; i < C_G.size(); ++i) {
		for (int j = 0; j < C_G[i].iner_len(); ++j) {
			int w = C_G[i].iner_at(j);
			for (int k = 0; k < vertex_list[w].list_len(); ++k) {
				int x = vertex_list[w].at(k);
				if (vertex_list[x].get_belong() != C_G[i].get_num())
					C_G[i].insert_list(vertex_list[x].get_belong());
			}
		}
	}

	/*for (int i = 0; i < C_G.size(); ++i) {
		cout << C_G[i].get_num() << ":" << C_G[i].get_impact() << "->";
		C_G[i].print_list();
	}*/
}

void SCC_DFS(int u) {
	C_G[u].color_change(GREY);
	for (int i = 0; i < C_G[u].list_len(); ++i) {
		int v = C_G[u].list_at(i);
		if (C_G[v].get_color() == WHITE) {
			SCC_DFS(v);
			C_G[u].impact_plus(C_G[v].get_impact());
		}

	}
	C_G[u].color_change(BLACK);

}
