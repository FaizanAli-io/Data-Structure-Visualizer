#include <vector>
#include <iostream>
using namespace std;

#ifndef STRUCTURES
#define STRUCTURES

template <typename T>
struct DynamicSafeArray
{
    int size;
    T *data;

    DynamicSafeArray() : size(0), data(nullptr) {}

    T &operator[](int index)
    {
        if (index >= size || index < 0)
            cout << "Invalid Index...\n";
        else
            return data[index];
    }

    void append(T val)
    {
        size++;
        T *newdata = new T[size];

        for (int i = 0; i < size - 1; i++)
            newdata[i] = data[i];
        newdata[size - 1] = val;

        delete[] data;
        data = newdata;
    }

    void remove(T val)
    {
        int ind = -1;
        for (int i = 0; i < size; i++)
            if (data[i] == val)
                ind = i;

        if (ind == -1)
            return;

        size--;
        T *newdata = new T[size];

        for (int i = 0; i < ind; i++)
            newdata[i] = data[i];
        for (int i = ind + 1; i < size + 1; i++)
            newdata[i - 1] = data[i];

        delete[] data;
        data = newdata;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
            cout << data[i] << ' ';
        cout << endl;
    }
};

template <typename T>
struct ListNode
{
    T data;
    ListNode<T> *next;

    ListNode(T data, ListNode<T> *next = nullptr)
        : data(data), next(next) {}
};

template <typename T>
struct TreeNode
{
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent;

    TreeNode(T data, TreeNode<T> *left = nullptr, TreeNode<T> *parent = nullptr)
        : data(data), left(left), right(right), parent(parent) {}
};

template <typename T>
struct LinkedList
{
    ListNode<T> *head;
    ListNode<T> *tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    inline bool isEmpty() { return head == nullptr; }

    ListNode<T> *getHead() { return head; }

    ListNode<T> *getTail() { return tail; }

    void append(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data);

        if (isEmpty())
            head = newNode;
        else
            tail->next = newNode;
        tail = newNode;
    }

    void appendPriority(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data);

        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
        }

        else
        {
            if (*(head->data) > *(data))
            {
                newNode->next = head;
                head = newNode;
            }

            else
            {
                ListNode<T> *temp = head;
                while (temp->next && *(temp->next->data) < *(data))
                    temp = temp->next;
                newNode->next = temp->next;
                temp->next = newNode;
            }

            while (tail->next != nullptr)
                tail = tail->next;
        }
    }

    void prepend(T data)
    {
        ListNode<T> *newNode = new ListNode<T>(data);

        if (isEmpty())
            tail = newNode;
        else
            newNode->next = head;
        head = newNode;
    }

    T removeHead()
    {
        if (isEmpty())
            return T();

        ListNode<T> *temp = head;

        if (temp == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
            head = head->next;

        T tempval = temp->data;
        delete temp;
        return tempval;
    }

    T removeTail()
    {
        if (isEmpty())
            return T();

        ListNode<T> *temp = head;

        if (temp == tail)
        {
            head = nullptr;
            tail = nullptr;
        }

        else
        {
            while (temp->next != tail)
                temp = temp->next;

            tail = temp;
            temp = tail->next;
            tail->next = nullptr;
        }

        T tempval = temp->data;
        delete temp;
        return tempval;
    }

    int getLength()
    {
        int size = 0;
        for (ListNode<T> *cur = head; cur != nullptr; cur = cur->next)
            size++;
        return size;
    }

    void print()
    {
        for (ListNode<T> *cur = head; cur != nullptr; cur = cur->next)
            cout << cur->data << " -> ";
        cout << "NULL" << endl;
    }

    ~LinkedList()
    {
        if (head != nullptr)
            delete head;
        if (tail != nullptr)
            delete tail;
    }
};

template <typename T>
struct AVLTree
{
    TreeNode<T> *root;

    inline int max(int a, int b) { return a > b ? a : b; }

    inline int getBalance(TreeNode<T> *node) { return getHeight(node->left) - getHeight(node->right); }

    int getHeight(TreeNode<T> *node) { return node ? max(getHeight(node->left), getHeight(node->right)) + 1 : -1; }

    TreeNode<T> *leftRotate(TreeNode<T> *x)
    {
        TreeNode<T> *y = x->right;
        TreeNode<T> *t = y->left;

        y->left = x;
        x->right = t;

        return y;
    }

    TreeNode<T> *rightRotate(TreeNode<T> *x)
    {
        TreeNode<T> *y = x->left;
        TreeNode<T> *t = y->right;

        y->right = x;
        x->left = t;

        return y;
    }

    TreeNode<T> *balanceTree(TreeNode<T> *node)
    {
        if (node)
        {
            node = balanceHelper(node);

            if (node->left)
                node->left = balanceTree(node->left);

            if (node->right)
                node->right = balanceTree(node->right);
        }

        return node;
    }

    TreeNode<T> *balanceHelper(TreeNode<T> *node)
    {
        int balance = getBalance(node);

        if (balance > 1)
        {
            if (getBalance(node->left) >= 0)
                node = rightRotate(node);

            else
            {
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
        }

        else if (balance < -1)
        {
            if (getBalance(node->right) <= 0)
                node = leftRotate(node);
            else
            {
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }

        return node;
    }

    void insert(T data) { root = insertHelper(root, data); }

    TreeNode<T> *insertHelper(TreeNode<T> *node, T data)
    {
        if (node == nullptr)
            return new TreeNode<T>(data);
        else if (*data < *(node->data))
            node->left = insertHelper(node->left, data);
        else if (*data > *(node->data))
            node->right = insertHelper(node->right, data);
        else
            return node;

        return node;
    }

    void remove(T data) { root = removeHelper(root, data); }

    TreeNode<T> *removeHelper(TreeNode<T> *node, T data)
    {
        if (node == nullptr)
            return nullptr;
        else if (*(node->data) > *(data))
            node->left = removeHelper(node->left, data);
        else if (*(node->data) < *(data))
            node->right = removeHelper(node->right, data);
        else
        {
            if (!(node->left) && !(node->right))
                return nullptr;
            else if ((node->left) && !(node->right))
                node = node->left;
            else if (!(node->left) && (node->right))
                node = node->right;
            else if ((node->left) && (node->right))
            {
                T value = nextNode(node)->data;
                node->right = removeHelper(node->right, value);
                node->data = value;
            }
        }

        return balanceHelper(node);
    }

    TreeNode<T> *nextNode(TreeNode<T> *node)
    {
        node = node->right;
        while (node->left)
            node = node->left;
        return node;
    }

    TreeNode<T> *lastNode(TreeNode<T> *node)
    {
        node = node->left;
        while (node->right)
            node = node->right;
        return node;
    }

    AVLTree() : root(nullptr) {}

    T search(TreeNode<T> *node, int searchVal)
    {
        if (node == nullptr)
            return nullptr;
        else if (*(node->data) > searchVal)
            return search(node->left, searchVal);
        else if (*(node->data) < searchVal)
            return search(node->right, searchVal);
        else
            return node->data;
    }

    void inorder(TreeNode<T> *node = nullptr, int d = 0)
    {
        if (d == 0 && !node)
            node = root;

        if (node != nullptr)
        {
            inorder(node->left, d + 1);

            for (int i = 0; i < d; i++)
                cout << '\t';
            cout << node->data << endl;

            inorder(node->right, d + 1);
        }
    }

    void preorder(TreeNode<T> *node = nullptr, int d = 0)
    {
        if (d == 0 && !node)
            node = root;

        if (node != nullptr)
        {
            for (int i = 0; i < d; i++)
                cout << '\t';
            cout << node->data << endl;

            preorder(node->left, d + 1);

            preorder(node->right, d + 1);
        }
    }

    void postorder(TreeNode<T> *node = nullptr, int d = 0)
    {
        if (d == 0 && !node)
            node = root;

        if (node != nullptr)
        {
            postorder(node->left, d + 1);

            postorder(node->right, d + 1);

            for (int i = 0; i < d; i++)
                cout << '\t';
            cout << node->data << endl;
        }
    }

    void levelorder(TreeNode<T> *node = nullptr)
    {
        LinkedList<TreeNode<T> *> nodes;

        node ? nodes.append(node) : nodes.removeTail(root);

        while (!nodes.isEmpty())
        {
            TreeNode<T> *current = nodes.removeHead();

            if (current->left)
                nodes.append(current->left);
            if (current->right)
                nodes.append(current->right);

            cout << current->data << ' ';
        }

        cout << endl;
    }
};

template <typename T>
struct Heap
{
public:
    TreeNode<T> *root;
    bool minheap;

    Heap(bool min) : minheap(min) { root = nullptr; }

    void swap(TreeNode<T> *a, TreeNode<T> *b)
    {
        T temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    TreeNode<T> *insert(T data)
    {
        TreeNode<T> *newnode = new TreeNode<T>(data);

        if (root == nullptr)
            root = newnode;

        else
        {
            LinkedList<TreeNode<T> *> queue;

            queue.append(root);

            while (!queue.isEmpty())
            {
                TreeNode<T> *current = queue.removeHead();

                if (current->left == nullptr)
                {
                    current->left = newnode;
                    newnode->parent = current;
                    break;
                }

                else if (current->right == nullptr)
                {
                    current->right = newnode;
                    newnode->parent = current;
                    break;
                }

                queue.append(current->left);
                queue.append(current->right);
            }
        }

        return newnode;
    }

    bool lessThan(TreeNode<T> *a, TreeNode<T> *b)
    {
        if (minheap)
            return *(a->data) < *(b->data);
        else
            return *(a->data) > *(b->data);
    }

    bool moreThan(TreeNode<T> *a, TreeNode<T> *b)
    {
        if (minheap)
            return *(a->data) > *(b->data);
        else
            return *(a->data) < *(b->data);
    }

    void heapifyUp(TreeNode<T> *node)
    {
        while (node->parent != nullptr && lessThan(node, node->parent))
        {
            swap(node, node->parent);
            node = node->parent;
        }
    }

    TreeNode<T> *findLastNode()
    {
        if (root == nullptr)
            return nullptr;

        LinkedList<TreeNode<T> *> queue;

        queue.append(root);

        TreeNode<T> *current;

        while (!queue.isEmpty())
        {
            current = queue.removeHead();

            if (current->left != nullptr)
                queue.append(current->left);

            if (current->right != nullptr)
                queue.append(current->right);
        }

        return current;
    }

    void heapifyDown(TreeNode<T> *node)
    {
        while ((node->left != nullptr && moreThan(node, node->left)) ||
               (node->right != nullptr && moreThan(node, node->right)))
        {
            if (node->right == nullptr || lessThan(node->left, node->right))
            {
                swap(node, node->left);
                node = node->left;
            }

            else
            {
                swap(node, node->right);
                node = node->right;
            }
        }
    }

    void removeRoot()
    {
        if (root == nullptr)
            return;

        TreeNode<T> *lastNode = findLastNode();

        swap(root, lastNode);

        if (lastNode->parent)
        {
            if (lastNode->parent->left == lastNode)
                lastNode->parent->left = nullptr;

            else if (lastNode->parent->right == lastNode)
                lastNode->parent->right = nullptr;
        }
    }
};

#endif
