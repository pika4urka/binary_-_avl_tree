#include <iostream>
#include <vector>

class BinaryTree
{
	const int inf = 1e9;
	class Tree
	{
	public:
		int elem;
		Tree* LeftTree;
		Tree* RightTree;
		Tree* UpTree;

		Tree(int elem, Tree* UpTree = NULL)
		{
			this->elem = elem;
			this->UpTree = UpTree;
			LeftTree = NULL;
			RightTree = NULL;
		}

		Tree() : Tree(0) { }

		~Tree()
		{
			delete LeftTree;
			delete RightTree;
		}
	};

	size_t level;
	Tree* BTree;
	Tree* Up;
	std::vector<int> vecEl;

	void filling_vector(std::vector<std::string>& vec, Tree* tree,
		size_t lvl, size_t ch, std::vector<int>& vecElements);

	std::vector<std::string> convertTree2Vec();
	void fill_empty_cells(size_t lvl, Tree* tree, size_t ch);

public:

	BinaryTree()
	{
		Up = new Tree();
		BTree = Up;
		level = 0;
	}

	~BinaryTree()
	{
		delete Up;
	}

	int get_elem();
	void add_elem(int elem);

	void stepUp();
	void stepLeft();
	void stepRight();

	bool isBegin();
	bool isEnd();

	bool checkLeft();
	bool checkRight();

	void visualization();
	std::vector<int>& get_VecElem();
};
