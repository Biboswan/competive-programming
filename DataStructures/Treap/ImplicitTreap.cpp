#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <stack>

using namespace std;

class Node;
typedef Node *pNode;

class Node
{
public:
    int val, size, priority;
    pNode left, right, parent;
    bool rev;

    Node(int val)
    {
        this->val = val;
        priority = rand();
        left = NULL;
        right = NULL;
        parent = NULL;
        size = 1;
        rev = false;
    }
};

class Treap
{
public:
    pNode root;

    Treap()
    {
        root = NULL;
    }

    int count(pNode x)
    {
        return x ? x->size : 0;
    }

    void updateSize(pNode x)
    {
        if (x)
        {
            x->size = count(x->left) + 1 + count(x->right);
        }
    }

    void updateParentChildren(pNode x)
    {
        if (x)
        {
            if (x->left)
            {
                x->left->parent = x;
            }

            if (x->right)
            {
                x->right->parent = x;
            }
        }
    }

    void push(pNode t)
    {
        if (t && t->rev)
        {
            t->rev = false;
            swap(t->left, t->right);
            if (t->left)
            {
                t->left->rev ^= true;
            }
            if (t->right)
            {
                t->right->rev ^= true;
            }
        }
    }

    void split(pNode t, pNode &left, pNode &right, int key)
    {
        if (!t)
        {
            left = NULL;
            right = NULL;
            return;
        }

        push(t);

        if (key == (count(t->left) + 1))
        {
            left = t;
            right = t->right;
            t->right = NULL;
        }
        else if (key <= count(t->left))
        {
            split(t->left, left, t->left, key);
            right = t;
        }
        else
        {
            //cout << "t:" << t->val << endl;
            split(t->right, t->right, right, key - count(t->left) - 1);
            left = t;
        }

        updateSize(t);
        updateParentChildren(t);
    }

    void merge(pNode &t, pNode t1, pNode t2)
    {
        push(t1);
        push(t2);

        if (!t1 || !t2)
        {
            t = t1 ? t1 : t2;
            return;
        }

        if (t1->priority > t2->priority)
        {
            merge(t1->right, t1->right, t2);
            t = t1;
        }
        else
        {
            merge(t2->left, t1, t2->left);
            t = t2;
        }

        updateSize(t);
        updateParentChildren(t);
    }

    pNode insert(int pos, int val)
    {
        pNode t1, t2;
        pNode n = new Node(val);
        split(root, t1, t2, pos);
        merge(t1, t1, n);
        merge(root, t1, t2);
        return n;
    }

    void reverse(int l, int h)
    {
        pNode t1, t2, t3, t4;
        split(this->root, t1, t2, h);
        split(t1, t3, t4, l - 1);
        if (t4)
        {
            t4->rev ^= true;
        }
        merge(t1, t3, t4);
        merge(this->root, t1, t2);
    }

    int getElementByPos(int pos)
    {
        pNode t = this->root;
        while (t)
        {
            push(t);
            int l = count(t->left);
            if (l + 1 == pos)
            {
                return t->val;
            }
            else if (pos <= l)
            {
                t = t->left;
            }
            else
            {
                pos = pos - l - 1;
                t = t->right;
            }
        }

        return -1;
    }

    int getPosByElement(pNode x)
    {
        pNode prev = NULL;
        int pos = 0;
        stack<bool> isRight;
        while (x)
        {
            if (prev != NULL)
            {
                if (x->right == prev)
                {
                    isRight.push(true);
                }
                else
                {
                    isRight.push(false);
                }
            }
            prev = x;
            x = x->parent;
        }

        pNode t = this->root;
        bool dir;
        while (!isRight.empty())
        {
            dir = isRight.top();
            isRight.pop();
            if (t->rev)
            {
                dir ^= true;
                //cout << "right:" << dir;
            }
            push(t);
            prev = t;
            t = dir ? t->right : t->left;
            if (dir)
            {
                pos += 1 + count(prev->left);
            }
        }
        push(t);
        if (t)
        {
            pos += 1 + count(t->left);
        }
        //cout << "\n";
        return pos;
    }
};

void inorder(pNode n)
{
    if (!n)
    {
        return;
    }

    inorder(n->left);
    cout << n->val << " ";
    inorder(n->right);
}

void preorder(pNode x)
{
    if (!x)
    {
        return;
    }
    cout << x->val << " ";
    preorder(x->left);
    preorder(x->right);
}

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N, Q;
    cin >> N;
    cin >> Q;
    unordered_map<int, pNode> valToElement;

    Treap *tr = new Treap();
    for (int i = 1; i <= N; i++)
    {
        valToElement[i] = tr->insert(i, i);
    }

    /**inorder(tr->root);
    cout << "\n";
    preorder(tr->root);
    cout << "\n";
    **/
    int op, a, b;
    for (int i = 0; i < Q; i++)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> a;
            cin >> b;
            tr->reverse(a, b);
            /**
                        inorder(tr->root);
                        cout << "\n";
                        preorder(tr->root);
                        cout << "\n";
                    **/
            break;
        case 2:
            cin >> a;
            cout << "element " + to_string(a) + " is at position " + to_string(tr->getPosByElement(valToElement[a])) << "\n";
            break;
        case 3:
            cin >> a;
            cout << "element at position " + to_string(a) + " is " + to_string(tr->getElementByPos(a)) << "\n";
            break;
        }
    }

    return 0;
}
