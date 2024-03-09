#include <iostream>
#include <fstream>
#include <string>

#include "Tree.h"

using namespace std;

/*43000000001|4300000001|4300000001|Joshua Fowle Savings Account|1|6334235.05
43000000002 | 4300000003 | 4300000001 | Joshua Fowle Play Money | 2 | 2731646.43
43000000003 | 4300000004 | 4300000001 | Joshua Fowle Emergency Expenses | 2 | 7625683.59
43000000004 | 4300000005 | 4300000001 | Joshua Fowle Vacation Account | 2 | 79823.44
43000000005 | 4300000010 | 4300000001 | Joshua Fowle Healthcare Fund | 2 | 1104436.03
43000000006 | 4300000008 | 4300000001 | Joshua Fowle New Car Account | 1 | 1594842.08
43000000011 | 4300000004 | 4300000002 | Willie Swigert Joint Account | 1 | -9093725.95
43000000012 | 4300000003 | 4300000002 | Willie Swigert Business Account | 1 | 9288893.44
43000000013 | 4300000007 | 4300000002 | Willie Swigert College Fund | 1 | 8096128.80
43000000014 | 4300000006 | 4300000002 | Willie Swigert Flexible Spending | 0 | 9638415.62
43000000015 | 4300000001 | 4300000002 | Willie Swigert Play Money | 1 | -1877283.56
43000000016 | 4300000002 | 4300000002 | Willie Swigert Emergency Expenses | 2 | 7588354.79
43000000017 | 4300000005 | 4300000002 | Willie Swigert Vacation Account | 2 | 7102893.94
43000000018 | 4300000008 | 4300000002 | Willie Swigert Healthcare Fund | 2 | 7079673.10
43000000021 | 4300000001 | 4300000003 | Amos Labree Individual Account | 1 | -8591065.12
43000000022 | 4300000006 | 4300000003 | Amos Labree Family Trust | 1 | 2859736.31
43000000023 | 4300000007 | 4300000003 | Amos Labree Retirement Fund | 0 | 6271643.53
43000000024 | 4300000002 | 4300000003 | Amos Labree Joint Account | 2 | -7002828.09
43000000025 | 4300000009 | 4300000003 | Amos Labree Business Account | 1 | 4997031.51
43000000031 | 4300000005 | 4300000004 | Charlotte Ciciora Healthcare Fund | 1 | 1787356.81
*/


int main()
{
	int option;
	string l1, l2, l3, l4, l5, l6;
	long long ca_id;
	long long ca_b_id;
	long long ca_c_id;
	string ca_name;
	long long ca_tax_st;
	long double ca_bal;
	Tree node;
	Node node2;
	
	while (1) {
		cout << ("------MENU-----\n"
			"Izaberite opciju:\n"
			"1. Stvaranje indeksa\n"
			"2. Ispis indeksa\n"
			"3. Dodavanje novog zapisa\n"
			"4. Brisanje zapisa\n"
			"5. Pretrazivanje jednog podatka\n"
			"6. Pretrazivanje k podataka\n"
			"7. Pretrazivanje k sukcesivnih podataka\n"
			"8. Kraj\n"
			);
		cin >> option;
		if (option == 1)
		{

			ifstream File("1.txt");

			while (getline(File, l1, '|') && getline(File, l2, '|') && getline(File, l3, '|') && getline(File, l4, '|') && getline(File, l5, '|') && getline(File, l6))
			{

				ca_id = stoll(l1);
				//Data dat(stoll(l1));
				ca_b_id = stoll(l2);
				ca_c_id = stoll(l3);
				ca_name = l4;
				ca_tax_st = stoll(l5);
				ca_bal = stod(l6);
				Data_struct* data = new Data_struct(ca_b_id, ca_c_id, l4, ca_tax_st, ca_bal);
				data->ca_id = ca_id;
				Data dat(ca_id);
				dat.setData(data);
				//Node* node2=new Node(dat);
				node.insert(dat);//node2->get_keys()->get_data()->ca_id);
			}

			//m=4 visina 3
			/*node.insert(78);
			node.insert(13);
			node.insert(48);
			node.insert(38);
			node.insert(58);
			node.insert(23);
			node.insert(68);
			node.insert(1);
			node.insert(8);
			node.insert(5);*/

			//m=3 visina 3
			/*node.insert(5);
			node.insert(15);
			node.insert(2);
			node.insert(20);
			node.insert(3);
			node.insert(17);*/


			//m=3 visina 4
			/*node.insert(40);
			node.insert(20);
			node.insert(30);
			node.insert(25);
			node.insert(35);
			node.insert(22);
			node.insert(45);
			node.insert(37);
			node.insert(10);
			node.insert(18);
			node.insert(24);*/

			File.close();
		}
		else if (option == 2)
		{
			node.print_tree(node.find_root(), node.getLevel(node.find_root()));
		}
		else if (option == 3)
		{
			cout << "Unesite zapis: ";
			cin >> ca_id >> ca_b_id >> ca_c_id >> ca_name >> ca_tax_st >> ca_bal;
			Data_struct* data = new Data_struct(ca_b_id, ca_c_id, ca_name, ca_tax_st, ca_bal);
			data->ca_id = ca_id;
			Data dat(ca_id);
			dat.setData(data);
			node.insert(dat);
		}
		else if (option == 4)
		{
			//malo sutra
		}
		else if (option == 5)
		{
			long long primary_key;
			cout << "Unesite primarni kljuc: ";
			cin >> primary_key;
			node.search_one(primary_key, node.find_root());

		}
		else if (option == 6)
		{
			/*fstream file1;
			file1.open("File_K", ios::out);*/
			//ofstream file1("File_k.txt");

			long long primary_keys[10];
			int k;
			int steps = 0;
			cout << "Unesite k i primarne kljuceve";
			cin >> k;
			for (int i = 0; i < k; i++)
			{
				cin >> primary_keys[i];
			}
			node.search_k(primary_keys, k, node.find_root());

			/*for (int i = 0; i < k; i++)
			{
				steps+=node.search_k(primary_keys[i], node.find_root());
			}
			cout << "Broj koraka: " << steps;*/
			//file1.close();
		}
		else if (option == 7)
		{
			long long primary_key;
			int k;
			cout << "Unesite primarni kljuc i k";
			cin >> primary_key>>k;
			node.search_k_suc(primary_key, k, node.find_root());

		}
		else if (option == 8)
		{
			return 0;
		}
	}
}
