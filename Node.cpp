#include "Node.h"

Node::Node()
{
	is_leaf = 0;
	keys_size = 0;
	//keys = new long long[m];
	children = new Node * [m + 1];
	parent = nullptr;
	keys = new Data[m];
}
