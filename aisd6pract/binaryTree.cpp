#include "BinaryTree.h"
#include <sstream>
#include <string>


int BinaryTree::get_elem()
{
	return BTree->elem;
}

void BinaryTree::stepUp()
{
	BTree = BTree->UpTree;
}

void BinaryTree::stepLeft()
{
	BTree = BTree->LeftTree;
}

void BinaryTree::stepRight()
{
	BTree = BTree->RightTree;
}

bool BinaryTree::isBegin()
{
	if (BTree->UpTree == NULL)
		return true;
	else
		return false;
}

bool BinaryTree::isEnd()
{
	if ((BTree->LeftTree == NULL) && (BTree->RightTree == NULL))
		return true;
	else
		return false;
}

bool BinaryTree::checkLeft()
{
	if (BTree->LeftTree != NULL)
		return true;
	else
		return false;
}

bool BinaryTree::checkRight()
{
	if (BTree->RightTree != NULL)
		return true;
	else
		return false;
}

void BinaryTree::add_elem(int elem)
{

	if (level == 0)
	{
		this->BTree->elem = elem;
		level = 1;
		return void();
	}
	BTree = Up;
	size_t ch = 1;
	while (true)
	{
		if (elem < BTree->elem)
		{
			if (checkLeft())
			{
				stepLeft();
				ch++;
				continue;
			}
			else
			{
				BTree->LeftTree = new Tree(elem, BTree);
				ch++;
				break;
			}
		}

		if (elem > BTree->elem)
		{
			if (checkRight())
			{
				stepRight();
				ch++;
				continue;
			}
			else
			{
				BTree->RightTree = new Tree(elem, BTree);
				ch++;
				break;
			}
		}

		if (elem == BTree->elem)
			break;
	}

	if (ch > level)
		level = ch;
	this->BTree = Up;
}

void BinaryTree::fill_empty_cells(size_t lvl, Tree* tree, size_t ch)
{
	if (ch == lvl)
		return void();
	if (ch == lvl - 1)
	{
		if (tree->LeftTree == NULL)
		{
			tree->LeftTree = new Tree(inf, tree);
		}

		if (tree->RightTree == NULL)
		{
			tree->RightTree = new Tree(inf, tree);
		}

		return void();
	}

	if (tree->LeftTree == NULL)
	{
		tree->LeftTree = new Tree(inf, tree);
	}

	if (tree->RightTree == NULL)
	{
		tree->RightTree = new Tree(inf, tree);
	}

	fill_empty_cells(lvl, tree->LeftTree, ch + 1);
	fill_empty_cells(lvl, tree->RightTree, ch + 1);


	return void();
}

namespace binT
{
	size_t quantityStr(size_t lvl)
	{
		size_t quant = 0;
		lvl--;
		for (size_t i = lvl; i >= 1; i--)
		{
			quant += (size_t)pow(2, i);
		}
		quant += lvl + 1;
		return quant;
	}

	void print(std::vector<std::string>& vec, size_t lvl, int width)
	{
		std::vector<std::string> vec2;
		{
			int ch = 0, ind = 0;
			for (int deg = 0, degrev = lvl - 1, height = pow(2, lvl - 1); deg < lvl; deg++, height /= 2, degrev--)
			{
				while (ch != pow(2, deg))
				{
					vec2.push_back(vec.at(ind));
					ind++;
					ch++;
				}
				ch = 0;
				int step = width / pow(2, deg + 1);
				step--;
				{
					std::string str(step, ' ');
					for (int i = 0; i < vec2.size(); i++)
					{
						std::cout << str << vec2.at(i);
						str += "  ";
						std::cout << str;
						str.resize(str.size() - 2);
					}
					std::cout << std::endl;
					vec2.resize(0);

					if (deg != (lvl - 1))
					{
						std::string str2 = "";
						for (int i = 0; i < height; i++)
						{
							for (int j = 0; j < pow(2, deg); j++)
							{
								std::cout << str << '/' << str2 << "\\";
								str += "  ";
								std::cout << str;
								str.resize(str.size() - 2);
							}
							std::cout << std::endl;
							str.resize(str.size() - 1);
							str2 += "  ";
						}
					}
				}
			}
		}
	}

	int height_search(size_t lvl)
	{
		int height = 0;
		for (int i = 1; i < lvl; i++)
		{
			height += pow(2, i);
		}
		height += lvl;
		return height;
	}

	int width_search(size_t lvl)
	{
		int width = 0;
		for (int i = 0; i < lvl; i++)
		{
			width += 2 * pow(2, i);
		}
		return width;
	}

	std::string int2Str(int num)
	{
		std::ostringstream ost;
		if (num < 10)
			ost << 0;
		ost << num;
		return ost.str();
	}

	int str2int(std::string& str)
	{
		std::stringstream ist;
		ist << str;
		int num;
		ist >> num;
		return num;
	}
}

void BinaryTree::filling_vector(std::vector<std::string>& vec, Tree* tree,
	size_t lvl,	size_t ch, std::vector<int>& vecElements)
{
	if (ch == lvl)
	{
		std::string bufStr;

		if (tree->elem != inf)
		{
			bufStr = binT::int2Str(tree->elem);
			vecElements.push_back(tree->elem);
		}
		else
			bufStr = "**";

		//bufStr = (tree->elem != inf) ? binT::int2Str(tree->elem) : "**";       //int2Str(tree->elem);
		vec.push_back(bufStr);
		return void();
	}

	filling_vector(vec, tree->LeftTree, lvl, ch + 1, vecEl);
	filling_vector(vec, tree->RightTree, lvl, ch + 1, vecEl);

	return void();
}

std::vector<std::string> BinaryTree::convertTree2Vec()
{
	std::vector<std::string> vec;

	for (size_t i = 1; i <= level; i++)
	{
		BTree = Up;

		filling_vector(vec, BTree, i, 1, vecEl);
	}

	return vec;
}

void BinaryTree::visualization()
{
	fill_empty_cells(level, Up, 1);

	auto vec = convertTree2Vec();
	//int height = height_search(level);  //высота
	int width = binT::width_search(level); //ширина

	binT::print(vec, level, width);
}

std::vector<int>& BinaryTree::get_VecElem()
{
	return vecEl;
}