// Just for implementation of Inorder, Preorder, Postorder, BFS, and DFS

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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
namespace breadthfirstsearch{ void search(const Node*, int); }
namespace depthfirstsearch{ bool search(const Node*, int); }

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
	const void bfs(int value) const { breadthfirstsearch::search(this->Root, value); }
	const void dfs(int value) const { if(not depthfirstsearch::search(this->Root, value)) { std::cout << "Value: (" << value << ") not found!" << std::endl; }; }


	friend std::ostream& operator<<(std::ostream&, const CompleteBinaryTree&);
	friend std::ostream& operator<<(std::ostream&, const Node*);
	friend void inorder::traverse(const Node*);
	friend void preorder::traverse(const Node*);
	friend void postorder::traverse(const Node*);
	friend void breadthfirstsearch::search(const Node*, int);
	friend bool depthfirstsearch::search(const Node*, int);
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

namespace breadthfirstsearch {
	void search(const Node* node, int value) {
		if(node == nullptr) { std::cout << " Tree is empty! "; return; }
		else if (node->value == value) { std::cout << "Found value: " << value << std::endl; return; }
		else {
			std::queue<const Node*> queue{};
			queue.push(node);

			while(queue.size()) {
				const Node* front = queue.front();
				if (front->value == value) { std::cout << "Found value: " << value << std::endl; return; }
				if (queue.front()->left != nullptr) { queue.push(queue.front()->left); }
				if (queue.front()->right!= nullptr) { queue.push(queue.front()->right); }
				queue.pop();
			}
			std::cout << "Value: (" << value << ") not found!" << std::endl;
			return;
		}
	}
}

namespace depthfirstsearch {
	bool search(const Node* node, int value) {
		if (node == nullptr) { return false; }
		else if (node->value == value) { std::cout << "Found value: " << value << std::endl; return true; }
		if (search(node->left, value)) { return true; };
		if (search(node->right, value)) { return true; };
		return false;
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

	std::cout << "\nSearching for value: " << 10 << std::endl;
	tree.bfs(10);

	std::cout << "\nSearching for value: " << 5 << std::endl;
	tree.bfs(5);
	
	std::cout << "\nSearching for value: " << 20 << std::endl;
	tree.bfs(20);

	std::cout << "\nSearching for value: " << 8 << std::endl;
	tree.dfs(8);

	std::cout << "\nSearching for value: " << 1 << std::endl;
	tree.dfs(1);
	
	std::cout << "\nSearching for value: " << 40 << std::endl;
	tree.dfs(40);

	return 0;
}