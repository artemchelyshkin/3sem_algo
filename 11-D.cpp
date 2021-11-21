/*
Одна из новых возможностей текстового редактора «World XP» – это сортировка 
слов в предложении. Выход новой бета-версии редактора должен состоятся не позднее, 
чем через пять часов, а заявленная функция еще не реализована.
Требуется написать программу, осуществляющую сортировку слов в предложении. При этом все 
символы, отличные от букв, должны сохраниться и не поменять своего положения относительно 
вхождений слов. Для упрощения при подаче входных данных на вход вашей программы все такие 
символы будут заменены на символ «.» (точка). Таким образом символ «.» имеет смысл разделителя 
между словами. Например, строка «..aba.a..ba» после сортировки пример вид «..a.aba..ba», а 
строка «c..bb.a» примет вид «a..bb.c». Слова следует сортировать лексикографически, как в словаре.
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <map>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::map;

struct _node {
  int finish = 0;
  map<char, _node*> nodes;
};

class trie {
private:

  _node* head;

  void _del(_node* curr_node);

  void _add(_node* node, vector<char>::const_iterator start, vector<char>::const_iterator finish);

  bool _print(_node* head);

public:

  trie();

  void add_word(const vector<char>& word);

  void add_word(vector<char>::iterator start, vector<char>::iterator finish);

  void print();

  ~trie();

};

/*----------------------------------------------------------------------------------------------*/

trie::trie() {
  head = new _node;
}

void trie::_add(_node* node, vector<char>::const_iterator start,
  vector<char>::const_iterator finish) {
  if (start == finish) {
    node->finish++;
    return;
  }
  if (node->nodes.count(*start) > 0) {
    _node* tmp = node->nodes[*start];
    _add(tmp, ++start, finish);
  }
  else {
    _node* new_node = new _node;
    //cout << new_node->finish;
    node->nodes[*start] = new_node;
    _add(new_node, ++start, finish);
  }
}

void trie::_del(_node* curr_node) {
  for (auto var : curr_node->nodes) {
    _del(var.second);
  }
  delete curr_node;
}

bool trie::_print(_node* node) {
  if (node->finish > 0) {
    node->finish--;
    if (node->finish == 0 && node->nodes.empty()) {
      delete node;
      return 1;
    }
    else {
      return 0;
    }
  }
  char elem = node->nodes.begin()->first;
  cout << elem;
  bool d = _print(node->nodes.begin()->second);
  if (d) {
    node->nodes.erase(elem);
    if (node->nodes.empty()) {
      delete node;
      return 1;
    }
    else {
      return 0;
    }
  }
}

void trie::add_word(const vector<char>& word) {
  _add(head, word.begin(), word.end());
}

void trie::add_word(vector<char>::iterator start, vector<char>::iterator finish) {
  _add(head, start, finish);
}

void trie::print() {
  bool tmp = _print(head);
  if (tmp) {
    head = new _node;
  }
}

trie::~trie() {
  _del(head);
}

/*----------------------------------------------------------------------------------------------*/


int main() {
  trie pl;
  vector<char> str;
  string str2;
  cin >> str2;
  for (size_t i = 0; i < str2.size(); ++i) {
    str.push_back(str2[i]);
  }
  int cnt = 0;
  for (auto it = str.begin(); it != str.end(); it++) {
    if (*it != '.') {
      auto it2 = it;
      while (it2 != str.end() && *it2 != '.') {
        it2++;
      }
      pl.add_word(it, it2);
      cnt++;
      it = it2;
      if (it == str.end()) {
        break;
      }
    }
  }

  for (int i = 0; i < str2.size(); ++i) {
    if (str2[i] != '.') {
      pl.print();
      while (i != str2.size() && str2[i] != '.') {
        i++;
      }
      if (i != str2.size()) {
        cout << '.';
      }
    }
    else {
      cout << '.';
    }
  }

}
