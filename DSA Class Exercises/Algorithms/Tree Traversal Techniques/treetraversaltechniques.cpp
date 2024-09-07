#include <iostream>
#include <vector>

template <typename T>
struct Node_t {
	Node_t* left;
	Node_t* right;
	T value;

	Node_t(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}
};

namespace int_tree { typedef Node_t<int> Node; }
using namespace int_tree;

class CompleteBinaryTree {
private:
	Node* Root = nullptr;

public:
	void operator=(const std::vector<int>& treearr) {
		if (treearr.size()) {
			std::vector<Node*> temptree;
			temptree.resize(treearr.size(), nullptr);
			for(size_t i = 0; i < treearr.size(); ++i) { temptree.at(i) = new Node(treearr.at(i)); }
			for(size_t y = 0; y < treearr.size(); ++y) {
				if ((y+1)*2-1 < treearr.size()) { temptree.at(y)->left = temptree.at((y+1)*2-1);}
				else { break; }

				if ((y+1)*2 < treearr.size()) { temptree.at(y)->right = temptree.at((y+1)*2);}
				else { break; }
			}
		}
	}
};

int main() {
	CompleteBinaryTree tree;

	tree = std::vector<int>{1,2,3,4,5,6,7};

	return 0;
}