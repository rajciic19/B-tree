#ifndef _Tree_h_
#define _Tree_h_

#include "Node.h"
#include <fstream>

using namespace std;


class Tree
{
private:

	Node* root;


public:

	Tree();

	void insert(Data key);
	void insert_key_in_node(Data key, Node* temp);

	Data split_leaf(Data key, Node* curr_node);
	Data split_internal(Data key, Node* curr_node);
	void split_root(Data key, Node* curr_node);

	void print_tree(Node* root, int level);




	Node* find_root();
	int getLevel(Node* root);

	void search_one(long long key, Node* temp);

	void search_k(long long key[], int k, Node* temp);

	void search_k_suc(long long key, int k, Node* temp);

	friend class Node;
	friend class Data;
};


#endif
