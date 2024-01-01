#include <iostream>
#include <sstream>
#include <vector>


class AVLtree
{
	const int inf = 1e9;
	class Tree
	{
	public:
		int elem;
		Tree* LeftTree;
		Tree* RightTree;
		Tree* UpTree;
		int  levelDown;
		int diff;

		Tree(int elem, Tree* UpTree = NULL)
		{
			this->elem = elem;
			this->UpTree = UpTree;
			LeftTree = NULL;
			RightTree = NULL;
			levelDown = 1;
			diff = 0;
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

	std::vector<std::string> vecStrElem;

	void redUp(Tree* tree);

	void delempty(Tree* tree);

	void filling_vector(std::vector<std::string>& vec, Tree* tree, size_t lvl, size_t ch);
	std::vector<std::string> convertTree2Vec();
	void fill_empty_cells(size_t lvl, Tree* tree, size_t ch);

	void lvlred(int num, Tree* tree);

	void rebalancing(Tree* tree);
	void minTurnL(Tree* tree);
	void minTurnR(Tree* tree);
	void maxTurnL(Tree* tree);
	void maxTurnR(Tree* tree);
	void check_balance(Tree* tree);

	void delElem(double num, Tree* tree);

public:

	AVLtree()
	{
		Up = new Tree();
		BTree = Up;
		level = 0;
	}

	~AVLtree()
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
	void del(double num);
};
