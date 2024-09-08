// Just for implementation of Inorder, Preorder, Postorder, BFS, and DFS

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

class CompleteBinaryTree;

namespace int_tree { typedef Node_t<int> Node; }
using namespace int_tree;

namespace inorder{ void traverse(const Node*); };
namespace preorder{  void traverse(const Node*); };
namespace postorder{  void traverse(const Node*); };

class CompleteBinaryTree {
private:
	Node* Root = nullptr;
	const std::vector<int>* Treearr = nullptr;

public:
	void operator=(const std::vector<int>* treearr) {
		if (treearr->size()) {
			this->Treearr = treearr;
			std::vector<Node*> temptree;
			temptree.resize(treearr->size(), nullptr);
			for(size_t i = 0; i < treearr->size(); ++i) { temptree.at(i) = new Node(treearr->at(i)); }
			for(size_t y = 0; y < treearr->size(); ++y) {
				if ((y+1)*2-1 < treearr->size()) { temptree.at(y)->left = temptree.at((y+1)*2-1);}
				else { break; }

				if ((y+1)*2 < treearr->size()) { temptree.at(y)->right = temptree.at((y+1)*2);}
				else { break; }
			}
			this->Root = temptree.at(0);
		}
	}

	const void inorder() const { inorder::traverse(this->Root); }
	const void preorder() const { preorder::traverse(this->Root);	}
	const void postorder() const { postorder::traverse(this->Root); }


	friend std::ostream& operator<<(std::ostream&, const CompleteBinaryTree&);
	friend std::ostream& operator<<(std::ostream&, const Node*);
	friend void inorder::traverse(const Node*);
	friend void preorder::traverse(const Node*);
	friend void postorder::traverse(const Node*);
};

std::ostream& operator<<(std::ostream& COUT, const CompleteBinaryTree& tree) {
	if (tree.Treearr->size()) {
		COUT << "[ " << tree.Treearr->at(0);
		for (size_t i = 1; i < tree.Treearr->size(); ++i) {
			COUT << " | " << tree.Treearr->at(i);
		}
		COUT << " ]";
	} else {
		COUT << " Tree is empty! ";
	}
	
	return COUT;
}

std::ostream& operator<<(std::ostream& COUT, const Node* node) {
	if (node == nullptr) { COUT << " Node is null "; }
	else {
		COUT << node->value;
	}

	return COUT;
}

namespace inorder {
	void traverse(const Node* node) {
		if (node == nullptr) { return; }
		traverse(node->left);
		std::cout << ' ' << node << ' ';
		traverse(node->right);
	}
}

namespace preorder {
	void traverse(const Node* node) {
		if (node == nullptr) { return; }
		std::cout << ' ' << node << ' ';
		traverse(node->left);
		traverse(node->right);
	}
}

namespace postorder {
	void traverse(const Node* node) {
		if (node == nullptr) { return; }
		traverse(node->left);
		traverse(node->right);
		std::cout << ' ' << node << ' ';
	}
}

int main() {
	CompleteBinaryTree tree;

	tree = new std::vector<int>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

	std::cout << "Tree (breadth first): " << tree << std::endl;
	std::cout << std::endl;

	std::cout << "In-order  : [";
	tree.inorder();
	std::cout << " ]" << std::endl;

	std::cout << "Pre-order : [";
	tree.preorder();
	std::cout << " ]" << std::endl;

	std::cout << "Post-order: [";
	tree.postorder();
	std::cout << " ]" << std::endl;

	return 0;
}