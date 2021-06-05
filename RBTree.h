#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

enum Color
{
    RED,
    BLACK
};

class Node
{
public:

    Color color;
    string key;
    char value;
    Node* parent;
    Node* right;
    Node* left;

    Node(bool isRED, string Key, char Value)
    {
        if (isRED)
            color = RED;
        else
            color = BLACK;
        key = Key;
        value = Value;
        parent = NULL;
        right = NULL;
        left = NULL;
    }

    bool operator ==(string N)
    {
        return key == N;
    }

    bool operator >(string N)
    {
        int l1 = key.length();
        int l2 = N.length();
        int l_min;

        if (l1 <= l2)
            l_min = l1;
        else
            l_min = l2;

        int key_bit;
        int N_bit;

        for (int i = 0; i < l_min; i++)
        {
            key_bit = key[i] - '0';
            N_bit = N[i] - '0';
            if (key_bit > N_bit)
                return 1;
            else if (key_bit < N_bit)
                return 0;
        }

        if (l1 < l2)
        {
            N_bit = N[l1] - '0';
            if (N_bit == 1)
                return 0;
            else
                return 1;
        }
        else if (l2 < l1)
        {
            key_bit = key[l2] - '0';
            if (key_bit == 1)
                return 1;
            else
                return 0;
        }
        return 0;
    }

    bool operator <(string N)
    {
        return !(*this > N || *this == N);
    }
};

class RBtree
{
public:
    RBtree() { root = NULL; }                       // constructor
    void insert(string key, char value);            // method for adding an item with key and value
    void remove(string key);                        // method for deleting a tree element by key
    char find(string key);                          // method to find an element by key
    void clear();                                   // method for clearing an associative array
    string get_keys();                              // method returns a list of keys 
    string get_values();                            // method returns a list of values
    void print();                                   // console output
    string get_key_by_inf(char inf);                //method item search by information value
    ~RBtree();                                      // destructor
private:
    Node* root;
    void insertfix(Node* t);                                // balancing method after adding a node
    void deletefix(Node* node, bool mode);                  // balancing method after node removal
    void leftrotate(Node* node);                            // left turn
    void rightrotate(Node* node);                           // right turn
    Node* insert(string key, char value, Node* parent);     // method for adding a node to a tree
    void deleting(Node* delNode);                           //method handles item deletion
    Node* getNode(string k, Node* cur);                     //method searches for an element by key
    Node* getMin(Node* cur);                                //the method searches for the leftmost minimum element
    class Iterator
    {
    public:

        Iterator(Node* root)
        {
            current = root;
            s = new Stack;
        }

        Node* next()
        {
            if (!current)
                return NULL;
            if (current->right)
                s->push(current->right);
            Node* ans = current;
            if (current->left)
                current = current->left;
            else
                current = s->pop();
            return ans;
        }

        ~Iterator() { delete s; }

    private:

        class Stack
        {
        public:

            Stack() { head = NULL; }

            void push(Node* in)
            {
                Elem* insert = new Elem;
                insert->inf = in;
                insert->next = head;
                head = insert;
            }

            Node* pop()
            {
                if (!head)
                    return NULL;
                Node* ans = head->inf;
                Elem* del = head;
                head = head->next;
                delete del;
                return ans;
            }

            ~Stack()
            {
                while (head)
                    pop();
            }


        private:

            struct Elem
            {
                Node* inf;
                Elem* next;
            };

            Elem* head;
        };

        Node* current;
        Stack* s;
    };
};

void RBtree::insert(string key, char value)
{
    if (!root)
        root = new Node(0, key, value);
    else
    {
        Node* t;
        try { t = insert(key, value, root); }
        catch (exception& exception) { throw invalid_argument("\nThere is already a node with the same key."); }
        insertfix(t);
    }
}

void RBtree::remove(string key)
{
    if (!root)
        throw runtime_error("\nThe tree is empty");
    Node* delNode = getNode(key, root);
    if (!delNode)
        throw runtime_error("\nNode does not exist");

    if (delNode->left && delNode->right)
    {
        Node* temp = delNode;
        delNode = getMin(delNode->right);
        temp->key = delNode->key;
        temp->value = delNode->value;
    }
    deleting(delNode);
}

char RBtree::find(string key)
{
    if (!root)
        throw runtime_error("\nThe tree is empty");
    Node* ans = getNode(key, root);
    if (!ans)
        throw runtime_error("\nNode does not exist");
    return ans->value;
}

void RBtree::clear()
{
    while (root)
        remove(root->key);
}

string RBtree::get_keys()
{
    if (!root)
        throw runtime_error("\nThe tree is empty");
    string ans;
    Iterator* Iter = new Iterator(root);
    Node* current = Iter->next();
    while (current)
    {
        ans += current->key;
        ans += ' ';
        current = Iter->next();
    }
    delete Iter;
    return ans;
}

string RBtree::get_values()
{
    if (!root)
        throw runtime_error("\nThe tree is empty");
    string ans;
    Iterator* Iter = new Iterator(root);
    Node* current = Iter->next();
    while (current)
    {
        ans += current->value;
        ans += ' ';
        current = Iter->next();
    }
    delete Iter;
    return ans;
}

void RBtree::print()
{
    if (!root)
        throw runtime_error("\nThe tree is empty");
    Iterator* Iter = new Iterator(root);
    Node* current = Iter->next();
    while (current)
    {
        cout << current->key << ' ' << current->value << endl;
        current = Iter->next();
    }
    delete Iter;
}

string RBtree::get_key_by_inf(char inf)
{
    string ans = "";
    Iterator* Iter = new Iterator(root);
    Node* current = Iter->next();
    while (current)
    {
        if (current->value == inf)
        {
            ans = current->key;
            break;
        }
        current = Iter->next();
    }
    delete Iter;
    return ans;
}

void RBtree::insertfix(Node* t)
{
    Node* P = t->parent;
    if (!P)
    {
        t->color = BLACK;
        root = t;
        return;
    }
    if (P->color == BLACK)
        return;

    Node* GP = P->parent;
    Node* U;
    if (GP->right == P)
        U = GP->left;
    else
        U = GP->right;

    Color U_color;
    if (!U)
        U_color = BLACK;
    else
        U_color = U->color;


    if (U_color == RED)
    {
        GP->color = RED;
        P->color = BLACK;
        U->color = BLACK;
        insertfix(GP);
    }
    else
    {
        if (P->right == t)
        {
            if (GP->left == P)
            {
                leftrotate(t);
                rightrotate(t);
                t->color = BLACK;
                GP->color = RED;
            }
            else
            {
                leftrotate(P);
                P->color = BLACK;
                GP->color = RED;
            }
        }
        else
        {
            if (GP->right == P)
            {
                rightrotate(t);
                leftrotate(t);
                t->color = BLACK;
                GP->color = RED;
            }
            else
            {
                rightrotate(P);
                P->color = BLACK;
                GP->color = RED;
            }
        }
    }
}

void RBtree::deletefix(Node* node, bool mode)
{
    Node* P = node->parent;

    if (mode && !P)
    {
        root = node;
        return;
    }

    Node* S;
    if (P->left == node)
        S = P->right;
    else
        S = P->left;
    Node* Sl = S->left;
    Node* Sr = S->right;


    Color Sl_color, Sr_color;
    if (!Sl)
        Sl_color = BLACK;
    else
        (Sl_color = Sl->color);
    if (!Sr)
        Sr_color = BLACK;
    else
        (Sr_color = Sr->color);


    if (S->color == RED)
    {
        if (P->left == node)
            leftrotate(S);
        else
            rightrotate(S);
        S->color = BLACK;
        P->color = RED;
        deletefix(node, 0);
    }
    else if (P->color == BLACK && Sr_color == BLACK && Sl_color == BLACK)
    {
        S->color = RED;
        deletefix(P, 1);
    }
    else if (P->color == RED && Sr_color == BLACK && Sl_color == BLACK)
    {
        P->color = BLACK;
        S->color = RED;
    }
    else if (P->left == node && Sr_color == BLACK)
    {
        rightrotate(Sl);
        Sl->color = BLACK;
        S->color = RED;
        deletefix(node, 0);
    }
    else if (P->left == node && Sr_color == RED)
    {
        leftrotate(S);
        S->color = P->color;
        P->color = BLACK;
        Sr->color = BLACK;
    }
    else if (P->right == node && Sl_color == BLACK)
    {
        leftrotate(Sr);
        Sr->color = BLACK;
        S->color = RED;
        deletefix(node, 0);
    }
    else if (P->right == node && Sl_color == RED)
    {
        rightrotate(S);
        S->color = P->color;
        P->color = BLACK;
        Sl->color = BLACK;
    }
}

void RBtree::leftrotate(Node* node)
{
    Node* P = node->parent;
    Node* GP = P->parent;
    Node* leftC = node->left;
    node->parent = GP;
    if (GP)
    {
        if (GP->left == P)
            GP->left = node;
        else
            GP->right = node;
    }
    else
        root = node;
    P->parent = node;
    node->left = P;
    if (leftC)
        leftC->parent = P;
    P->right = leftC;
}

void RBtree::rightrotate(Node* node)
{
    Node* P = node->parent;
    Node* GP = P->parent;
    Node* rightC = node->right;
    node->parent = GP;
    if (GP)
    {
        if (GP->left == P)
            GP->left = node;
        else
            GP->right = node;
    }
    else
        root = node;
    P->parent = node;
    node->right = P;
    if (rightC)
        rightC->parent = P;
    P->left = rightC;
}

Node* RBtree::insert(string key, char value, Node* parent)
{
    if (key == parent->key)
        throw invalid_argument("");
    if (*parent < key)
    {
        if (!parent->right)
        {
            parent->right = new Node(1, key, value);
            parent->right->parent = parent;
            return parent->right;
        }
        else
            return insert(key, value, parent->right);
    }
    else
    {
        if (!parent->left)
        {
            parent->left = new Node(1, key, value);
            parent->left->parent = parent;
            return parent->left;
        }
        else
            return insert(key, value, parent->left);
    }
}

void RBtree::deleting(Node* delNode)
{
    if (delNode->color == RED)
    {
        if (delNode->parent->right == delNode)
            delNode->parent->right = NULL;
        else
            delNode->parent->left = NULL;
        delete delNode;
    }
    else if (delNode->left || delNode->right)
    {
        Node* child;
        if (delNode->left)
            child = delNode->left;
        else
            child = delNode->right;
        child->parent = delNode->parent;
        child->color = BLACK;

        if (!child->parent)
            root = child;
        else
        {
            if (delNode->parent->right == delNode)
                delNode->parent->right = child;
            else
                delNode->parent->left = child;
        }
        delete delNode;
    }
    else if (delNode == root)
    {
        root = NULL;
        delete delNode;
    }
    else
    {
        deletefix(delNode, 0);
        if (delNode->parent->left == delNode)
            delNode->parent->left = NULL;
        else
            delNode->parent->right = NULL;
        delete delNode;
    }
}

Node* RBtree::getNode(string k, Node* cur)
{
    if (!cur)
        return NULL;
    if (*cur == k)
        return cur;
    if (*cur < k)
        return getNode(k, cur->right);
    if (*cur > k)
        return getNode(k, cur->left);
}

Node* RBtree::getMin(Node* cur)
{
    while (cur->left)
        cur = cur->left;
    return cur;
}

RBtree::~RBtree()
{
    clear();
}