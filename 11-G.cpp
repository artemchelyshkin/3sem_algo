/*
Комитет По Исследованию Бинарных Вирусов обнаружил, что некоторые 
последовательности единиц и нулей являются кодами вирусов. Комитет 
изолировал набор кодов вирусов. Последовательность из единиц и нулей 
называется безопасной, если никакой ее подотрезок (т.е. последовательность 
из соседних элементов) не является кодом вируса. Сейчас цель комитета состоит в том, 
чтобы установить, существует ли бесконечная безопасная последовательность из единиц и нулей.
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <queue>
#include <stack>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::map;
using std::queue;
using std::stack;

struct _node {
  int finish = 0;
  int dfs = 0;
  map<char, _node*> nodes;
  _node* parent;
  _node* suf;
  int number = 0;
};

class trie {
private:

  int iii = 1;

  bool cycle = false;

  vector<_node*> _nodes;

  _node* head;

  void _add(_node* node, _node* parent, vector<char>::const_iterator start, vector<char>::const_iterator finish);

  bool _print(_node* head, char elem);

  void _suff_link(_node* start, _node* curr, char letter);

  void _DFS(_node* curr_node);

  void _add_finish(_node* node);

public:

  trie();

  void add_word(const vector<char>& word);

  void add_word(vector<char>::iterator start, vector<char>::iterator finish);

  void BFS();

  void fill();

  void print();

  void find_cycle();

  ~trie();

};

/*----------------------------------------------------------------------------------------------*/

trie::trie() {
  head = new _node;
  head->parent = head;
  head->suf = head;
  _nodes.push_back(head);
}

void trie::_add_finish(_node* node) {
  node->finish++;
  for (auto child : node->nodes) {
    child.second->finish++;
    _add_finish(child.second);
  }
}

void trie::_add(_node* node, _node* parent, vector<char>::const_iterator start,
  vector<char>::const_iterator finish) {
  node->parent = parent;
  if (start == finish) {
    _add_finish(node);
    return;
  }
  if (node->nodes.count(*start) > 0) {
    _node* tmp = node->nodes[*start];
    if (tmp->parent->finish) {
      tmp->finish++;
    }
    return _add(tmp, node, ++start, finish);
  }
  else {
    _node* new_node = new _node;
    new_node->number = iii;
    iii++;
    new_node->parent = node;
    if (new_node->parent->finish) {
      new_node->finish++;
    }
    _nodes.push_back(new_node);
    node->nodes[*start] = new_node;
    return _add(new_node, node, ++start, finish);
  }
}


bool trie::_print(_node* node, char elem) {
  cout << node->number << ". " << elem << ":  ";
  for (auto tmp : node->nodes) {
    char child = tmp.first;
    cout << child << " ";
  }
  cout << "suff : " << node->suf->number;
  cout << std::endl;
  for (auto tmp : node->nodes) {
    bool d = _print(tmp.second, tmp.first);
  }
  return 0;
}
void trie::add_word(const vector<char>& word) {
  return _add(head, head, word.begin(), word.end());
}

void trie::add_word(vector<char>::iterator start, vector<char>::iterator finish) {
  _add(head, head, start, finish);
}

void trie::print() {
  bool tmp = _print(head, '&');
  if (tmp) {
    head = new _node;
  }
}

trie::~trie() {
  for (size_t i = 0; i < _nodes.size(); ++i) {
    delete _nodes[i];
  }
}

void trie::find_cycle() {
  _DFS(head);
  if (cycle) {
    cout << "TAK";
  }
  else {
    cout << "NIE";
  }
}

void trie::_DFS(_node* curr_node) {
  curr_node->dfs = 1;
  if (!curr_node->finish) {
    for (auto child : curr_node->nodes) {
      if (child.second->dfs == 1 && !child.second->finish) {
        cycle = true;
      }
      else {
        if (child.second->dfs == 0 && !child.second->finish) {
          _node* next = child.second;
          _DFS(next);
        }
      }
    }
  }
  curr_node->dfs = 2;
}

void trie::_suff_link(_node* start, _node* curr, char letter) {
  if (curr->nodes.find(letter) != curr->nodes.end()) {
    start->suf = curr->nodes[letter];
    if (curr->nodes[letter]->finish) {
      _add_finish(start);
    }
    return;
  }
  if (curr == head) {
    start->suf = head;
    return;
  }
  else {
    _suff_link(start, curr->suf, letter);
  }
}

void trie::BFS() {
  queue<_node*> q;
  q.push(head);
  while (q.size() > 0) {
    _node* elem = q.front();
    q.pop();
    for (auto child : elem->nodes) {
      if (elem == head) {
        child.second->suf = head;
      }
      else {
        _suff_link(child.second, elem->suf, child.first);
      }
      q.push(child.second);
    }
  }
}

void trie::fill() {
  queue<_node*> q;
  q.push(head);
  while (q.size() > 0) {
    _node* elem = q.front();
    q.pop();
    for (auto child : elem->nodes) {
      q.push(child.second);
    }
    if (elem == head) {
      if (elem->nodes.count('0') == 0) {
        elem->nodes['0'] = head;
      }
      if (elem->nodes.count('1') == 0) {
        elem->nodes['1'] = head;
      }
    }
    else {
      if (elem->nodes.count('0') == 0) {
        elem->nodes['0'] = elem->suf->nodes['0'];
      }
      if (elem->nodes.count('1') == 0) {
        elem->nodes['1'] = elem->suf->nodes['1'];
      }
    }
  }
}

/*----------------------------------------------------------------------------------------------*/

int main() {
  trie pl;
  size_t number_of_words = 0;
  cin >> number_of_words;
  for (size_t i = 0; i < number_of_words; ++i) {
    string word;
    cin >> word;
    vector<char> vec_word;
    for (size_t j = 0; j < word.size(); ++j) {
      vec_word.push_back(word[j]);
    }
    pl.add_word(vec_word);
  }

  pl.BFS();
  pl.fill();
  pl.find_cycle();
}
