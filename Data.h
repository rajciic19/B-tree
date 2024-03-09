#ifndef _Data_h_
#define _Data_h_

#include <string>

using namespace std;

struct Data_struct
{
	long long ca_id;
	long long ca_b_id;
	long long ca_c_id;
	string ca_name;
	long long ca_tax_st;
	long double ca_bal;
	Data_struct(long long ca_b_id, long long ca_c_id, string ca_name, long long ca_tax_st,
		long double ca_bal) : ca_b_id(ca_b_id), ca_c_id(ca_c_id), ca_name(ca_name),
		ca_tax_st(ca_tax_st), ca_bal(ca_bal) {}
};

class Data
{
private:
	long long key;
	Data_struct* data;


public:
	Data() = default;
	Data(long long k) : key(k), data(NULL) {};

	void setData(Data_struct* dat) { data = dat; }

	Data_struct* get_data() const {
		return data;
	}
	long long get_key() {
		return key;
	}

	friend class Node;

	friend class Tree;
};

#endif
