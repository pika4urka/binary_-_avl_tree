#include <iostream>
#include "BinaryTree.h"
#include "AVLtree.h"
#include <fstream>

using namespace std;

void reading_tree(BinaryTree& tree1, AVLtree& tree2)
{
	ifstream ist("file.txt");
	int num;
	while (!ist.eof())
	{
		ist >> num;
		tree1.add_elem(num);
	}
	ist.close();
	ist.open("file.txt");

	while (!ist.eof())
	{
		ist >> num;
		tree2.add_elem(num);
	}
	ist.close();
}

void ZaDaNiE(BinaryTree& tree, AVLtree& tree2)
{
	auto vec = tree.get_VecElem();
	int sum = 0;

	for (int i = 0; i < vec.size(); i++)
		sum += vec.at(i);
	double srArifm = (double)sum / (double)vec.size();
	try
	{
		tree2.del(srArifm);

		tree2.visualization();
	}
	catch (runtime_error& err)
	{
		cout << "error";
	}
}


int main()
{ 
	BinaryTree tree;
	AVLtree tree2;
	
	reading_tree(tree, tree2);
	
	tree.visualization();
	tree2.visualization();

	ZaDaNiE(tree, tree2);

	return 0;
}