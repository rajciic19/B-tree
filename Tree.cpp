#include <vector>
#include <queue>

#include <iostream>
#include <fstream>
#include "Tree.h"


Tree::Tree()
{
    root = nullptr;
}

Node* Tree::find_root()
{
    return root;
}



void Tree::insert(Data key)
{
    if (root == nullptr)
    {
        root = new Node;
        root->is_leaf = 1;
        root->keys_size = 1;
        root->keys[0] = key;
        //root->
    }
    else
    {
        Node* curr_node = root;
        Node* parent = nullptr;
        while (curr_node->is_leaf == 0)
        {
            parent = curr_node;
            for (int i = 0; i < curr_node->keys_size; i++)
            {
                if (key.key < curr_node->keys[i].key)
                {
                    curr_node = curr_node->children[i];
                    break;
                }
                if (i == curr_node->keys_size - 1)
                {
                    curr_node = curr_node->children[i + 1];
                    break;
                }
            }
        }
        if (curr_node->keys_size < m - 1)
        {
            //ubaci samo
            insert_key_in_node(key, curr_node);
        }
        else
        {
            //split do korena
            while (curr_node != nullptr)
            {
                if (curr_node->keys_size < m - 1)
                {
                    //ubaci samo
                    insert_key_in_node(key, curr_node);
                    break;
                }
                else if (curr_node == root)
                {
                    split_root(key, curr_node);
                    break;
                }
                else if (curr_node->is_leaf == true)
                {
                    key = split_leaf(key, curr_node);
                }
                else if (curr_node != root && curr_node->is_leaf == false)
                {
                    key = split_internal(key, curr_node);
                }
                curr_node = curr_node->parent;
            }
        }
    }
}


void Tree::insert_key_in_node(Data key, Node* curr_node)
{
    int i = 0, j = 0;
    while (curr_node->keys[i].key < key.key && i < curr_node->keys_size)
    {
        i++;
    }
    for (j = curr_node->keys_size; j > i; j--)
    {
        curr_node->keys[j] = curr_node->keys[j - 1];
    }
    curr_node->keys[i] = key;
    curr_node->keys_size++;
}

Data Tree::split_leaf(Data key, Node* curr_node)
{
    int i = 0, j = 0;
    Data keys[m + 1];
    Node* new_node = new Node;
    new_node->parent = curr_node->parent;
    new_node->is_leaf = true;
    new_node->next_leaf_ptr = curr_node->next_leaf_ptr;
    curr_node->next_leaf_ptr = new_node;
    for (i = 0; i < m; i++)
    {
        keys[i] = curr_node->keys[i];
    }
    i = 0;
    while (key.key > keys[i].key && i < m - 1)
    {
        i++;
    }
    for (j = curr_node->keys_size; j > i; j--)
    {
        keys[j] = keys[j - 1];
    }
    keys[i] = key;

    curr_node->keys_size = m - m / 2;
    new_node->keys_size = m / 2;

    //prebaci kljuceve
    for (i = 0; i < curr_node->keys_size; i++)
    {
        curr_node->keys[i] = keys[i];
    }
    for (j = 0; j < new_node->keys_size; j++, i++)
    {
        new_node->keys[j] = keys[i];
    }
    //namesti parent children pokazivace
    i = 0;
    while (curr_node->parent->children[i] != curr_node)
    {
        i++;
    }
    for (j = curr_node->parent->keys_size + 1; j > i; j--)
    {
        curr_node->parent->children[j] = curr_node->parent->children[j - 1];
    }
    curr_node->parent->children[i + 1] = new_node;



    return curr_node->keys[curr_node->keys_size - 1];
}

Data Tree::split_internal(Data key, Node* curr_node)
{
    int i = 0, j = 0;
    Data keys[m + 1];
    Node* new_node = new Node;
    Node** temp_children = new Node * [m + 2];

    for (i = 0; i <= curr_node->keys_size + 1; i++)
    {
        temp_children[i] = curr_node->children[i];
    }

    new_node->parent = curr_node->parent;
    new_node->is_leaf = false;
    for (i = 0; i < m; i++)
    {
        keys[i] = curr_node->keys[i];
    }
    i = 0;
    while (key.key > keys[i].key && i < m - 1)
    {
        i++;
    }
    for (j = curr_node->keys_size; j > i; j--)
    {
        keys[j] = keys[j - 1];
    }
    keys[i] = key;

    curr_node->keys_size = m / 2;
    new_node->keys_size = m / 2;

    for (i = 0; i < curr_node->keys_size; i++)
    {
        curr_node->keys[i]= keys[i];
    }
    if (m % 2 == 1)
    {
        i++;
    }
    for (j = 0; j < new_node->keys_size; j++, i++)
    {
        new_node->keys[j] = keys[i];
    }


    i = 0;
    while (curr_node->parent->children[i] != curr_node)
    {
        i++;
    }
    for (j = curr_node->parent->keys_size + 1; j > i; j--)
    {
        curr_node->parent->children[j] = curr_node->parent->children[j - 1];
    }
    curr_node->parent->children[i + 1] = new_node;



    j = 0;
    for (i = 0; i < curr_node->keys_size - 1; i++)
    {
        j++;
    }
    for (i = 0; i <= new_node->keys_size; i++, j++)
    {
        new_node->children[i] = temp_children[j + 2];
        new_node->children[i]->parent = new_node;
    }


    return keys[m / 2];
}

void Tree::split_root(Data key, Node* curr_node)
{
    Node* new_root = new Node;
    Node* new_node = new Node;
    Node** temp_children = new Node * [m + 2];
    int i = 0, j = 0;
    Data keys[m + 1];
    new_node->next_leaf_ptr = curr_node->next_leaf_ptr;
    curr_node->next_leaf_ptr = new_node;
    if (curr_node->is_leaf == true)
    {
        new_node->is_leaf = true;
    }
    else
    {
        for (i = 0; i <= curr_node->keys_size + 1; i++)
        {
            temp_children[i] = curr_node->children[i];
        }
    }


    for (i = 0; i < m; i++)
    {
        keys[i] = curr_node->keys[i];
    }
    i = 0;
    while (key.key > keys[i].key && i < m - 1)
    {
        i++;
    }
    for (j = curr_node->keys_size; j > i; j--)
    {
        keys[j] = keys[j - 1];
    }
    keys[i] = key;

    Data key_to_go;
    if (m % 2 == 1)
    {
        key_to_go = keys[m / 2];
        if (curr_node->is_leaf == true)
        {
            curr_node->keys_size = m - m / 2;
            new_node->keys_size = m / 2;
        }
        else
        {
            curr_node->keys_size = m / 2;
            new_node->keys_size = m / 2;
        }
    }
    else
    {
        key_to_go = keys[m / 2 - 1];

        if (curr_node->is_leaf == true)
        {
            curr_node->keys_size = m / 2;
            new_node->keys_size = m / 2;
        }
        else
        {
            curr_node->keys_size = m / 2 - 1;
            new_node->keys_size = m / 2;
        }
    }

    //prebaci kljuceve
    for (i = 0; i < curr_node->keys_size; i++)
    {
        curr_node->keys[i] = keys[i];
    }

    if (curr_node->is_leaf == false)
    {
        i++;
    }


    for (j = 0; j < new_node->keys_size; j++, i++)
    {
        new_node->keys[j] = keys[i];
    }
    //namesti pokazivače od curr i new
    if (curr_node->is_leaf != true)
    {
        j = 0;
        for (i = 0; i < curr_node->keys_size - 1; i++)
        {
            j++;
        }
        for (i = 0; i <= new_node->keys_size; i++, j++)
        {
            new_node->children[i] = temp_children[j + 2];
            new_node->children[i]->parent = new_node;
        }
    }





    //napravi nov koren
    new_root->children[0] = curr_node;
    new_root->children[1] = new_node;
    new_root->keys[0] = key_to_go;

    curr_node->parent = new_root;
    new_node->parent = new_root;
    new_root->keys_size = 1;
    new_root->is_leaf = false;

    root = new_root;
}



void Tree::print_tree(Node* root, int level)
{
    queue<Node*> queue;
    queue.push(root);
    while (!q.empty())
    {
        Node* current_node = queue.front();
        queue.pop();
        for (int i = 0; i < current_node->keys_size; i++)
        {
            if (i != current_node->keys_size - 1) cout << current_node->keys[i].key << "|";
            else cout << current_node->keys[i].key;
        }
        cout << endl;
        if (!current_node->is_leaf)
        {
            for (int i = 0; i <= current_node->keys_size; i++)
            {
                q.push(current_node->children[i]);
            }
        }
    }

}




void Tree::search_one(long long key, Node* temp)
{
    //Node node;

    Node* curr_node = temp;
    Node* parent = nullptr;
    while (curr_node->is_leaf == 0)
    {
        parent = curr_node;
        for (int i = 0; i < curr_node->keys_size; i++)
        {
            if (key <= curr_node->keys[i].key)
            {
                curr_node = curr_node->children[i];
                break;
            }
            if (i == curr_node->keys_size - 1)
            {
                curr_node = curr_node->children[i + 1];
                break;
            }
        }
    }
    int cnt = 0;
    while (curr_node->keys[cnt].key && cnt < curr_node->keys_size)
    {
        cnt++;
    }
    cnt--;
    cout << endl;
    cout << "Uspesno nadjen" << endl;
    //node = *curr_node;
    cout << curr_node->keys[cnt].key << "|" << curr_node->keys[cnt].get_data()->ca_b_id << "|" << curr_node->keys[cnt].get_data()->ca_c_id << "|" << curr_node->keys[cnt].get_data()->ca_name << "|" << curr_node->keys[cnt].get_data()->ca_tax_st << "|" << curr_node->keys[cnt].get_data()->ca_bal << endl;
    cout << endl << "Ukupan broj koraka" << getLevel(curr_node) + cnt;
}

void Tree::search_k(long long primary_keys[],int k, Node* temp)
{
    //Node node;
    ofstream file1("File_k.txt");
    //Node* curr_node = temp;
    Node* parent = nullptr;
    int steps = 0;
    for (int j = 0; j < k; j++)
    {
        Node* curr_node = temp;
        while (curr_node->is_leaf == 0)
        {
            parent = curr_node;
            for (int i = 0; i < curr_node->keys_size; i++)
            {
                if (primary_keys[j] <= curr_node->keys[i].key)
                {
                    curr_node = curr_node->children[i];
                    break;
                }
                if (i == curr_node->keys_size - 1)
                {
                    curr_node = curr_node->children[i + 1];
                    break;
                }
            }
        }
        int cnt = 0;
        while (curr_node->keys[cnt].key!=primary_keys[j] && cnt < curr_node->keys_size)
        {
            cnt++;
        }
        //cnt--;
        steps += getLevel(curr_node) + cnt + 1;
        file1<< curr_node->keys[cnt].key << "|" << curr_node->keys[cnt].get_data()->ca_b_id << "|" << curr_node->keys[cnt].get_data()->ca_c_id << "|" << curr_node->keys[cnt].get_data()->ca_name << "|" << curr_node->keys[cnt].get_data()->ca_tax_st << "|" << curr_node->keys[cnt].get_data()->ca_bal << endl;
    }
    cout <<endl<<"Broj koraka: " << steps;
    file1.close();
}

void Tree::search_k_suc(long long key, int k, Node* temp)
{
    ofstream file2("File_k_suc.txt");
    Node* curr_node = temp;
    Node* parent = nullptr;
    int steps = 0, cnt = 0, cnt1 = 0;
    while (curr_node->is_leaf == 0)
    {
        parent = curr_node;
        for (int i = 0; i < curr_node->keys_size; i++)
        {
            if (key < curr_node->keys[i].key)
            {
                curr_node = curr_node->children[i];
                break;
            }
            if (i == curr_node->keys_size - 1)
            {
                curr_node = curr_node->children[i + 1];
                break;
            }
        }
    }
    
    while (curr_node->keys[cnt].key!=key && cnt < curr_node->keys_size)
    {
        cnt++;
    }
    cnt--;
    steps = getLevel(curr_node) + cnt+1;
    cnt1 = 0;
    while (cnt1 < k)
    {
        cnt = 0;
        while (cnt < curr_node->keys_size && cnt1<k)
        {
            file2 << curr_node->keys[cnt].key << "|" << curr_node->keys[cnt].get_data()->ca_b_id << "|" << curr_node->keys[cnt].get_data()->ca_c_id << "|" << curr_node->keys[cnt].get_data()->ca_name << "|" << curr_node->keys[cnt].get_data()->ca_tax_st << "|" << curr_node->keys[cnt].get_data()->ca_bal << endl;
            cnt++;
            cnt1++;
        }
        steps += cnt1;
        if (curr_node->next_leaf_ptr != nullptr)
        {
            curr_node = curr_node->next_leaf_ptr;
        }
        else
        {
            break;
        }
        //cnt1++;
    }
    steps += cnt1;

    cout << endl;
    
    file2.close();
    cout << "Broj koraka: " << steps;
}




int Tree::getLevel(Node* root)
{
    Node* curr = root;
    int level = 0;
    while (!curr->is_leaf)
    {
        curr = curr->children[0];
        level++;
    }
    return level;
}
