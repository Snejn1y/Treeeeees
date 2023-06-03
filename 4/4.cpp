#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;

unsigned int small_rotations_avl = 0;
unsigned int small_rotations_rb = 0;

struct elem
{
    int data;
    unsigned int h;
    elem* left, * right;

    elem(int value = 0) : left(nullptr), right(nullptr), data(value), h(0) {}
};

struct avl_tree
{
    elem* top;

    avl_tree(void) : top(NULL) {}
};

unsigned int height(elem* el)
{
    return el ? el->h : 0;
}

int balance_factor(elem* el)
{
    return height(el->right) - height(el->left);
}

void calc_height(elem* el)
{
    unsigned int h_left = height(el->left);
    unsigned int h_right = height(el->right);
    el->h = (h_left > h_right ? h_left : h_right) + 1;
}

elem* left_rotate(elem* l)
{
    elem* r = l->right;
    l->right = r->left;
    r->left = l;
    calc_height(l);
    calc_height(r);
    small_rotations_avl++;
    return r;
}

elem* right_rotate(elem* r)
{
    elem* l = r->left;
    r->left = l->right;
    l->right = r;
    calc_height(l);
    calc_height(r);
    small_rotations_avl++;
    return l;
}

elem* balancing(elem* el)
{
    calc_height(el);
    if (balance_factor(el) == 2)
    {
        if (balance_factor(el->right) < 0)
            el->right = right_rotate(el->right);
        el = left_rotate(el);
        return el;
    }
    else if (balance_factor(el) == -2)
    {
        if (balance_factor(el->left) > 0)
            el->left = left_rotate(el->left);
        el = right_rotate(el);
        return el;
    }
    return el;
}
elem* ins(elem* el, const int& data)
{
    if (!el)
        return new elem(data);
    if (data < el->data)
        el->left = ins(el->left, data);
    else
        el->right = ins(el->right, data);

    return balancing(el);
}

void add(avl_tree& avl_tr, const int& data)
{
    avl_tr.top = ins(avl_tr.top, data);
}

elem* find_left(elem* el)
{
    return el->left ? find_left(el->left) : el;
}

elem* removemin(elem* el)
{
    if (!el->left)
        return el->right;
    el->left = removemin(el->left);
    return balancing(el);
}

elem* remove(elem* el, const int& data)
{
    if (!el)
        return 0;
    if (data < el->data)
        el->left = remove(el->left, data);
    else if (data > el->data)
        el->right = remove(el->right, data);
    else
    {
        elem* q = el->left;
        elem* r = el->right;
        delete el;

        if (!r)
            return q;

        elem* min = find_left(r);
        min->right = removemin(r);
        min->left = q;
        return balancing(min);
    }
    return balancing(el);
}

void del(avl_tree& avl_tr, const int& data)
{
    avl_tr.top = remove(avl_tr.top, data);
}

void postfix(elem* top)
{
    if (!top)
        return;
    postfix(top->left);
    postfix(top->right);
    std::cout << top->data << " ";
}

void prefix(elem* top)
{
    if (!top)
        return;
std:; cout << top->data << " ";
    prefix(top->left);
    prefix(top->right);
}

void infix(elem* top)
{
    if (!top)
        return;
    infix(top->left);
    std::cout << top->data << " ";
    infix(top->right);
}

void inputTree(avl_tree& tree, int n)
{
    std::cout << "Введіть " << n << " елементів для дерева:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        int data;
        std::cin >> data;
        add(tree, data);
    }
}

void randTree(avl_tree& tree, int n)
{
    for (int i = 0; i < n; i++)
    {
        int data = std::rand();
        add(tree, data);
    }
}

elem* find_min(elem* el)
{
    return el && el->left ? find_min(el->left) : el;
}

void remove_r(avl_tree& avl_tr, const int& r)
{
    while (find_min(avl_tr.top) && find_min(avl_tr.top)->data <= r)
    {
        del(avl_tr, find_min(avl_tr.top)->data);
    }
}

void delete_avl_nodes(elem* node)
{
    if (node == nullptr)
        return;
    delete_avl_nodes(node->left);
    delete_avl_nodes(node->right);
    delete node;
}

struct rb_node
{
    int red;
    int data;
    rb_node* link[2];
};

struct rb_tree
{
    rb_node* root;
    int count;
    rb_tree(void) : root(NULL) {}
};

rb_node* rb_single(rb_node* root, int dir)
{
    rb_node* save = root->link[!dir];
    root->link[!dir] = save->link[dir];
    save->link[dir] = root;
    root->red = 1;
    save->red = 0;
    small_rotations_rb++;
    return save;
}

rb_node* rb_double(rb_node* root, int dir)
{
    root->link[!dir] = rb_single(root->link[!dir], !dir);
    return rb_single(root, dir);
}

int is_red(rb_node* node)
{
    return node != NULL && node->red;
}

rb_node* make_node(int data)
{
    rb_node* rn = new rb_node;
    if (rn) {
        rn->data = data;
        rn->red = 1;
        rn->link[0] = NULL;
        rn->link[1] = NULL;
    }
    return rn;
}

bool rb_insert(rb_tree* tree, int data)
{
    if (!tree->root)
    {
        tree->root = make_node(data);
        if (!tree->root)
            return false;
    }
    else
    {
        rb_node head = { 0 };
        rb_node* g, * t;
        rb_node* p, * q;
        int dir = 0, last;
        t = &head;
        g = p = NULL;
        q = t->link[1] = tree->root;
        while (true)
        {
            if (!q)
            {
                p->link[dir] = q = make_node(data);
                tree->count++;
                if (!q)
                    return false;
            }
            else if (is_red(q->link[0]) && is_red(q->link[1]))
            {
                q->red = 1;
                q->link[0]->red = 0;
                q->link[1]->red = 0;
            }
            if (is_red(q) && is_red(p))
            {
                int dir2 = t->link[1] == g;
                if (q == p->link[last])
                    t->link[dir2] = rb_single(g, !last);
                else
                    t->link[dir2] = rb_double(g, !last);
            }
            if (q->data == data)
                break;
            last = dir;
            dir = q->data < data;
            if (g)
                t = g;
            g = p, p = q;
            q = q->link[dir];
        }
        tree->root = head.link[1];
    }
    tree->root->red = 0;
    return true;
}

rb_node* find_min_node(rb_node* root)
{
    while (root->link[0])
        root = root->link[0];
    return root;
}

rb_node* remove_node(rb_node* root, int data, int& done)
{
    if (!root)
    {
        done = 1;
        return nullptr;
    }

    int dir = root->data < data;

    if (root->data == data)
    {
        if (!root->link[0] || !root->link[1])
        {
            rb_node* new_root = root->link[root->link[0] == nullptr];
            delete root;
            done = 1;
            return new_root;
        }
        else
        {
            rb_node* temp = find_min_node(root->link[1]);
            root->data = temp->data;
            root->link[1] = remove_node(root->link[1], temp->data, done);
        }
    }

    root->link[dir] = remove_node(root->link[dir], data, done);

    if (done)
        return root;

    return root;
}


bool rb_remove(rb_tree* tree, int data)
{
    int done = 0;
    tree->root = remove_node(tree->root, data, done);
    if (tree->root)
    {
        tree->root->red = 0;
    }
    return done;
}

rb_node* find_min_rb(rb_node* node)
{
    return node && node->link[0] ? find_min_rb(node->link[0]) : node;
}

void remove_r(rb_tree& tree, int r)
{
    rb_node* min_node = find_min_rb(tree.root);
    while (min_node && min_node->data <= r)
    {
        int min_data = min_node->data;
        rb_remove(&tree, min_data);
        min_node = find_min_rb(tree.root);
    }
}

void postfix(rb_node* top)
{
    if (!top)
        return;
    postfix(top->link[0]);
    postfix(top->link[1]);
    std::cout << top->data << " ";
}

void prefix(rb_node* top)
{
    if (!top)
        return;
    std::cout << top->data << " ";
    prefix(top->link[0]);
    prefix(top->link[1]);
}

void infix(rb_node* top)
{
    if (!top)
        return;
    infix(top->link[0]);
    std::cout << top->data << " ";
    infix(top->link[1]);
}

void inputTree(rb_tree& tree, int n)
{
    std::cout << "Введіть " << n << " елементів для дерева:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        int data;
        std::cin >> data;
        rb_insert(&tree, data);
    }
}

void randTree(rb_tree& tree, int n)
{
    for (int i = 0; i < n; i++)
    {
        int data = std::rand();
        rb_insert(&tree, data);
    }
}

void delete_rb_nodes(rb_node* node)
{
    if (!node)
        return;
    delete_rb_nodes(node->link[0]);
    delete_rb_nodes(node->link[1]);
    delete node;
}

void Ftest()
{
    cout << "AVL trees test \"avl.txt\":\n";
    ofstream out("avl.txt");
    int n = 0;
    double time = 0;
    for (int i = 0; i < 10; i++)
    {
        n += 10000;
        for (int k = 0; k < 5; k++)
        {
            avl_tree tree;
            randTree(tree, n);
            chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
            remove_r(tree, rand());
            chrono::time_point<chrono::steady_clock> done = chrono::steady_clock::now();
            time += chrono::duration_cast<chrono::milliseconds>(done - start).count();
            delete_avl_nodes(tree.top);
            tree.top = nullptr;
        }
        time /= 5000;
        cout << "AVL trees test. n = " << n << " Time = " << time << " Rotate: " << small_rotations_avl << endl;
        out << n << "\t" << time << "\t" << small_rotations_avl << "\n";
        small_rotations_avl = 0;
    }
    out.close();
}

void Stest()
{
    cout << "RB trees test \"rb.txt\":\n";
    ofstream out("rb.txt");
    int n = 0;
    double time = 0;
    for (int i = 0; i < 10; i++)
    {
        n += 10000;
        for (int k = 0; k < 5; k++)
        {
            rb_tree tree;
            randTree(tree, n);
            chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
            remove_r(tree, rand());
            chrono::time_point<chrono::steady_clock> done = chrono::steady_clock::now();
            time += chrono::duration_cast<chrono::milliseconds>(done - start).count();
            delete_rb_nodes(tree.root);
            tree.root = nullptr;
        }
        time /= 5000;
        cout << "RB trees test. n = " << n << " Time = " << time << " Rotate: " << small_rotations_rb << endl;
        out << n << "\t" << time << "\t" << small_rotations_rb << "\n";
        small_rotations_rb = 0;
    }
    out.close();
}

void Show()
{
    avl_tree tree;

    add(tree, 10);
    add(tree, 5);
    add(tree, 15);
    add(tree, 3);
    add(tree, 7);
    add(tree, 12);
    add(tree, 18);

    cout << " AVL\nAn example of a tree:\n";
    infix(tree.top);
    cout << endl;

    add(tree, 0);
    add(tree, 4);
    add(tree, 8);

    infix(tree.top);
    cout << endl;

    int r = 8;
    remove_r(tree, r);

    std::cout << "Tree after remove:\n";
    infix(tree.top);
    std::cout << std::endl;


    rb_tree rbtree;

    rb_insert(&rbtree, 10);
    rb_insert(&rbtree, 5);
    rb_insert(&rbtree, 15);
    rb_insert(&rbtree, 3);
    rb_insert(&rbtree, 7);
    rb_insert(&rbtree, 12);
    rb_insert(&rbtree, 18);

    cout << " RB\nAn example of a tree:\n";
    infix(rbtree.root);
    cout << endl;

    rb_insert(&rbtree, 0);
    rb_insert(&rbtree, 4);
    rb_insert(&rbtree, 8);

    infix(rbtree.root);
    cout << endl;

    remove_r(rbtree, r);

    std::cout << "Tree after remove:\n";
    infix(rbtree.root);
    std::cout << std::endl;
}


int main()
{
    std::srand(std::time(0));
    while (1)
    {
        int c = 4;
        cout << "1. If u want to work with AVL trees;\n"
            "2. If u want to work with red-black trees;\n"
            "3. If u want analize all algorithms;\n"
            "4. Exemple trees;\n"
            "5. If u want exit;\n"
            "Choose: ";
        cin >> c;
        switch (c)
        {
        case 1:
        {
            int n = 0, r = 0;
            cout << "Enter a number of vertices: ";
            cin >> n;
            avl_tree tree;
            int f = 0;
            cout << "1. Enter from keyboard;\n"
                "2. Random;\n"
                "Choose: ";
            cin >> f;
            if (f == 1)
                inputTree(tree, n);
            else if (f == 2)
            {
                randTree(tree, n);
                cout << "You tree: \n";
                infix(tree.top);
                cout << endl;
            }
            else
            {
                cout << "U enter a wront number!";
                return 0;
            }
            cout << "Enter r: ";
            cin >> r;
            remove_r(tree, r);
            cout << "Your tree after removing all elements smaller than r:\n";
            infix(tree.top);
            cout << endl;
            break;
        }
        case 2:
        {
            int n = 0, r = 0;
            cout << "Enter a number of vertices: ";
            cin >> n;
            rb_tree tree;
            int f = 0;
            cout << "1. Enter from keyboard;\n"
                "2. Random;\n"
                "Choose: ";
            cin >> f;
            if (f == 1)
                inputTree(tree, n);
            else if (f == 2)
            {
                randTree(tree, n);
                cout << "You tree: \n";
                infix(tree.root);
                cout << endl;
            }
            else
            {
                cout << "U enter a wront number!";
                return 0;
            }
            cout << "Enter r: ";
            cin >> r;
            remove_r(tree, r);
            cout << "Your tree after removing all elements smaller than r:\n";
            infix(tree.root);
            cout << endl;
            break;
        }
        case 3:
        {
            Ftest();
            Stest();
            break;
        }
        case 4:
        {
            Show();
            break;
        }
        default:
            return 0;
        }
    }
}

