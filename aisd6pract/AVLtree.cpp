#include "AVLtree.h"
#include <sstream>
#include <string>
#include <math.h>

void AVLtree::redUp(Tree* tree)
{
	while (tree->UpTree != NULL)
		tree = tree->UpTree;
	Up = tree;
}

void AVLtree::lvlred(int ch, Tree* tree)
{
	if (tree == NULL)
		return void();

	if (ch > level)
		level = ch;

	lvlred(++ch, tree->LeftTree);
	lvlred(ch, tree->RightTree);
}

void AVLtree::minTurnL(Tree* tree)
{
	Tree* tr1, * tr2, * tr3, * tr4;

	tr1 = tree;
	tr2 = tree->RightTree;
	tr3 = tree->RightTree->LeftTree;
	tr4 = tree->UpTree;

	if (tr2 != NULL) tr2->UpTree = tr4;
	if (tr1 != NULL) tr1->UpTree = tr2;
	tr2->LeftTree = tr1;
	tr1->RightTree = tr3;
	if (tr3 != NULL) tr3->UpTree = tr1;

	if (tr4 != NULL)
		if (tr4->LeftTree == tr1)
			tr4->LeftTree = tr2;
		else
			tr4->RightTree = tr2;

	tr1->levelDown = std::max((tr1->LeftTree != NULL) ? tr1->LeftTree->levelDown : 0,
		(tr1->RightTree != NULL) ? tr1->RightTree->levelDown : 0) + 1;

	tr2->levelDown = std::max((tr2->LeftTree != NULL) ? tr2->LeftTree->levelDown : 0,
		(tr2->RightTree != NULL) ? tr2->RightTree->levelDown : 0) + 1;
}

void AVLtree::minTurnR(Tree* tree)
{
	Tree* tr1, * tr2, * tr3, * tr4;

	tr1 = tree;
	tr2 = tree->LeftTree;
	tr3 = (tree->LeftTree->RightTree != NULL) ? tree->LeftTree->RightTree : NULL;
	tr4 = tree->UpTree;

	if (tr2 != NULL) tr2->UpTree = tr4;
	if (tr1 != NULL) tr1->UpTree = tr2;
	if (tr3 != NULL) tr3->UpTree = tr1;
	tr2->RightTree = tr1;
	tr1->LeftTree = tr3;

	if (tr4 != NULL)
		if (tr4->LeftTree == tr1)
			tr4->LeftTree = tr2;
		else
			tr4->RightTree = tr2;

	tr1->levelDown = std::max((tr1->LeftTree != NULL) ? tr1->LeftTree->levelDown : 0,
		(tr1->RightTree != NULL) ? tr1->RightTree->levelDown : 0) + 1;

	tr2->levelDown = std::max((tr2->LeftTree != NULL) ? tr2->LeftTree->levelDown : 0,
		(tr2->RightTree != NULL) ? tr2->RightTree->levelDown : 0) + 1;
}

void AVLtree::maxTurnL(Tree* tree)
{
	Tree* tr1, * tr2, * tr3, * tr4, * tr5, * tr6;

	tr1 = tree;
	tr6 = tree->UpTree;
	tr2 = tree->RightTree;
	tr3 = tree->RightTree->LeftTree;
	tr4 = tr3->LeftTree;
	tr5 = tr3->RightTree;

	if (tr3 != NULL) tr3->UpTree = tr6;
	if (tr1 != NULL) tr1->UpTree = tr3;
	if (tr2 != NULL) tr2->UpTree = tr3;
	if (tr4 != NULL) tr4->UpTree = tr1;
	if (tr5 != NULL) tr5->UpTree = tr2;

	tr3->LeftTree = tr1;
	tr3->RightTree = tr2;
	tr1->RightTree = tr4;
	tr2->LeftTree = tr5;


	if (tr6 != NULL)
		if (tr6->LeftTree == tr1)
			tr6->LeftTree = tr3;
		else
			tr6->RightTree = tr3;

	tr1->levelDown = std::max((tr1->LeftTree != NULL) ? tr1->LeftTree->levelDown : 0,
		(tr1->RightTree != NULL) ? tr1->RightTree->levelDown : 0) + 1;

	tr2->levelDown = std::max((tr2->LeftTree != NULL) ? tr2->LeftTree->levelDown : 0,
		(tr2->RightTree != NULL) ? tr2->RightTree->levelDown : 0) + 1;

	tr3->levelDown = std::max(tr1->levelDown, tr2->levelDown) + 1;
}

void AVLtree::maxTurnR(Tree* tree)
{
	Tree* tr1, * tr2, * tr3, * tr4, * tr5, * tr6;

	tr1 = tree;
	tr6 = tree->UpTree;
	tr2 = tree->LeftTree;
	tr3 = tree->LeftTree->RightTree;
	tr4 = tr3->LeftTree;
	tr5 = tr3->RightTree;

	if (tr3 != NULL) tr3->UpTree = tr6;
	if (tr2 != NULL) tr2->UpTree = tr3;
	if (tr1 != NULL) tr1->UpTree = tr3;
	if (tr4 != NULL) tr4->UpTree = tr2;
	if (tr5 != NULL) tr5->UpTree = tr1;

	tr3->LeftTree = tr2;
	tr3->RightTree = tr1;
	tr2->RightTree = tr4;
	tr1->LeftTree = tr5;

	if (tr6 != NULL)
		if (tr6->LeftTree == tr1)
			tr6->LeftTree = tr3;
		else
			tr6->RightTree = tr3;

	tr1->levelDown = std::max((tr1->LeftTree != NULL) ? tr1->LeftTree->levelDown : 0,
		(tr1->RightTree != NULL) ? tr1->RightTree->levelDown : 0) + 1;

	tr2->levelDown = std::max((tr2->LeftTree != NULL) ? tr2->LeftTree->levelDown : 0,
		(tr2->RightTree != NULL) ? tr2->RightTree->levelDown : 0) + 1;

	tr3->levelDown = std::max(tr1->levelDown, tr2->levelDown) + 1;
}

void AVLtree::rebalancing(Tree* tree)
{
	int l, r, lr, ll, rl, rr;

	if (tree->LeftTree != NULL)
	{
		l = tree->LeftTree->levelDown;
		lr = (tree->LeftTree->RightTree != NULL) ? tree->LeftTree->RightTree->levelDown : 0;
		ll = (tree->LeftTree->LeftTree != NULL) ? tree->LeftTree->LeftTree->levelDown : 0;
	}
	else
	{
		l = 0;
		lr = 0;
		ll = 0;
	}
	
	if (tree->RightTree != NULL)
	{
		r = tree->RightTree->levelDown;
		rr = (tree->RightTree->RightTree != NULL) ? tree->RightTree->RightTree->levelDown : 0;
		rl = (tree->RightTree->LeftTree != NULL) ? tree->RightTree->LeftTree->levelDown : 0;
	}
	else
	{
		r = 0;
		rr = 0;
		rl = 0;
	}

	if (l < r)
	{
		if (rl <= rr)
		{
			minTurnL(tree);
		}
		else
		{
			maxTurnL(tree);
		}
	}
	else
	{
		if (lr <= ll)
		{
			minTurnR(tree);
		}
		else
		{
			maxTurnR(tree);
		}
	}

	redUp(tree);
	level = 0;
	lvlred(1, Up);
}

int AVLtree::get_elem()
{
	return BTree->elem;
}

void AVLtree::stepUp()
{
	BTree = BTree->UpTree;
}

void AVLtree::stepLeft()
{
	BTree = BTree->LeftTree;
}

void AVLtree::stepRight()
{
	BTree = BTree->RightTree;
}

bool AVLtree::isBegin()
{
	if (BTree->UpTree == NULL)
		return true;
	else
		return false;
}

bool AVLtree::isEnd()
{
	if ((BTree->LeftTree == NULL) && (BTree->RightTree == NULL))
		return true;
	else
		return false;
}

bool AVLtree::checkLeft()
{
	if (BTree->LeftTree != NULL)
		return true;
	else
		return false;
}

bool AVLtree::checkRight()
{
	if (BTree->RightTree != NULL)
		return true;
	else
		return false;
}

void AVLtree::add_elem(int elem)
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
				stepLeft();
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
				stepRight();
				ch++;
				break;
			}
		}

		if (elem == BTree->elem)
			break;
	}

	if (ch > level)
		level = ch;

	ch = 1;
	int Llvl, Rlvl;
	Tree* newTree = BTree;
	while (true)
	{
		stepUp();
		if (BTree == NULL) break;
		ch++;
		if (ch > BTree->levelDown)
			BTree->levelDown = ch;
		else
			ch = BTree->levelDown;
	}
	BTree = newTree;

	while (true)
	{
		stepUp();
		if (BTree == NULL) break;
		Llvl = (BTree->LeftTree != NULL) ? BTree->LeftTree->levelDown : 0;
		Rlvl = (BTree->RightTree != NULL) ? BTree->RightTree->levelDown : 0;
		BTree->diff = abs(Llvl - Rlvl);

		if (BTree->diff > 1)
		{
			rebalancing(BTree);
		}
	}
}

void AVLtree::fill_empty_cells(size_t lvl, Tree* tree, size_t ch)
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

namespace avlT
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

void AVLtree::filling_vector(std::vector<std::string>& vec, Tree* tree, size_t lvl, size_t ch)
{
	if (ch == lvl)
	{
		std::string bufStr;

		bufStr = (tree->elem != inf) ? avlT::int2Str(tree->elem) : "**";       
		vec.push_back(bufStr);
		return void();
	}

	filling_vector(vec, tree->LeftTree, lvl, ch + 1);
	filling_vector(vec, tree->RightTree, lvl, ch + 1);

	return void();
}

std::vector<std::string> AVLtree::convertTree2Vec()
{
	std::vector<std::string> vec;

	for (size_t i = 1; i <= level; i++)
	{
		BTree = Up;

		filling_vector(vec, BTree, i, 1);
	}

	return vec;
}

void AVLtree::visualization()
{
	fill_empty_cells(level, Up, 1);

	vecStrElem = convertTree2Vec();
	//int height = height_search(level);  //высота
	int width = avlT::width_search(level); //ширина

	avlT::print(vecStrElem, level, width);
}

void AVLtree::check_balance(Tree* tree)
{
	int lvlL, lvlR;
	while (tree->UpTree != NULL)
	{
		lvlL = (tree->RightTree != NULL) ? tree->RightTree->levelDown : 0;
		lvlR = (tree->LeftTree != NULL) ? tree->LeftTree->levelDown : 0;
		if (abs(lvlL - lvlR) > 1)
		{
			rebalancing(tree);
			redUp(tree);
			break;
		}
	}
}

void AVLtree::delElem(double num, Tree* tree)
{
	if ((tree == NULL) /*|| (tree->elem == inf)*/)
		return void();

	Tree* bufTree1, * bufTree2, * bufTree3;
	if (tree->elem > num)
	{
		//int s = tree->elem;
		//double l = num;
		bufTree1 = tree->UpTree;
		bufTree2 = tree;
		if (tree->RightTree != NULL)
		{
			delete tree->RightTree;
			tree->RightTree = NULL;
		}
		if (tree->LeftTree == NULL)
		{
			delete tree;
			bufTree1->RightTree = NULL;
			tree = bufTree1;
		}
		else
		{
			while (tree->LeftTree != NULL)
			{
				tree = tree->LeftTree;
				if (tree->elem <= num)
				{
					tree->UpTree->LeftTree = NULL;
					delete bufTree2;
					bufTree1->RightTree = tree;
					delElem(num, bufTree1);
				}
			}
			if ((tree->LeftTree == NULL) && (tree->elem > num))
			{
				delete bufTree2;
				bufTree1->RightTree = NULL;
				return void();
			}

		}
			/*while (tree->LeftTree != NULL)
			{
				tree = tree->LeftTree;
				if (tree->elem <= num)
				{
					bufTree3 = tree;
					tree->UpTree->LeftTree = NULL;
					bufTree1->RightTree = NULL;
					delete bufTree2;
					bufTree1->RightTree = bufTree3;
					bufTree3->UpTree = bufTree1;
					tree = bufTree1;
					tree->levelDown = std::max((tree->LeftTree != NULL) ? tree->LeftTree->levelDown : 0,
						(tree->RightTree != NULL) ? tree->RightTree->levelDown : 0) + 1;
					break;
				}
			}*/
	}

	delElem(num, tree->RightTree);
}

void AVLtree::delempty(Tree* tree)
{
	if (tree->elem == inf)
	{
		Tree* tr;
		tr = tree;
		tree = tree->UpTree;
		if (tree->LeftTree == tr)
			tree->LeftTree = NULL;
		else
			tree->RightTree = NULL;

		delete tr;
		return void();
	}

	if (tree->LeftTree != NULL) delempty(tree->LeftTree);
	if (tree->RightTree != NULL) delempty(tree->RightTree);

}

void AVLtree::del(double num)
{
	Tree* tree;
	BTree = Up;
	delempty(Up);
	while ((BTree->LeftTree != NULL)/* && (BTree->LeftTree->elem != inf)*/)
		stepLeft();
	while (BTree->UpTree != NULL)
	{
		//stepUp();

		if (BTree->elem > num)
		{
			tree = BTree->LeftTree;
			tree->UpTree = NULL;
			BTree->LeftTree = NULL;
			delete Up;
			Up = tree;
			delElem(num, tree->RightTree);
			BTree = tree;
			break;
		}
		else
			delElem(num, BTree->RightTree);
		stepUp();
	}

	if (BTree->UpTree == NULL)
	{
		if (BTree->elem > num)
		{
			tree = BTree->LeftTree;
			tree->UpTree = NULL;
			BTree->LeftTree = NULL;
			delete Up;
			Up = tree;
			delElem(num, tree->RightTree);
			BTree = tree;
		}
		else
			delElem(num, BTree->RightTree);
	}

	int el;
	for (int i = 0; i < vecStrElem.size(); i++)
	{
		try
		{
			el = std::stoi(vecStrElem.at(i));
			if (el > num)
				vecStrElem.at(i) = "**";
		}
		catch (const std::logic_error& err)
		{
			continue;
		}
	}
	redUp(BTree);
	level = 0;
	lvlred(1, Up);
}