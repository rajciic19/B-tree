#ifndef _Node_h_
#define _Node_h_

#include "Data.h"

const int m =3;


class Node
{
private:

	Data* keys;
	//long long key;
	Node** children;
	Node* parent;
	Node* next_leaf_ptr = nullptr;


	bool is_leaf;


	int keys_size;


	//Data* dat;

public:
	Node();
	Node(Data* key) : keys(key){};

	//long long get_key() const { return key };

	Data* get_keys() const { return keys; }

	/*void setData(Data* data) {
		dat = data;
	}*/


	friend class Tree;
	friend class Data;
	void printNode();

};

#endif
