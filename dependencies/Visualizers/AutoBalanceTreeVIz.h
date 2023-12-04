#include "../Structures.h"
#include "../GraphicObjects.h"

#ifndef AVLTREE
#define AVLTREE

template <typename T>
void AVLTree<T>::recursiveTreeDraw(TreeNode<T> *node, RenderWindow *win)
{
    if (node != nullptr)
    {
        node->data->draw(win);
        recursiveTreeDraw(node->left, win);
        recursiveTreeDraw(node->right, win);
    }
}

template <typename T>
void AVLTree<T>::recursivesetPosition(TreeNode<T> *node, RenderWindow *win,
                                      int x, int y, int dx, int dy)
{
    if (node != nullptr)
    {
        node->data->setPos(Vector2f(x, y));

        int newXL = x - dx;
        int newXR = x + dx;

        recursivesetPosition(node->left, win, newXL, y + dy, dx / 2, dy);
        recursivesetPosition(node->right, win, newXR, y + dy, dx / 2, dy);

        if (node->left != nullptr)
            node->data->setArrow1(node->left->data->shape.getPosition());
        else
            node->data->pointer1.visible = false;

        if (node->right != nullptr)
            node->data->setArrow2(node->right->data->shape.getPosition());
        else
            node->data->pointer2.visible = false;
    }
}

struct AutoBalanceTreeVisualizer
{
    const float updateSpeed = 0.01;
    const float animationSpeed = 3;

    Font font;
    Clock clock;
    RenderWindow *window;
    Button *b1, *b2, *b3, *b4;
    AVLTree<NodeObject *> *tree;

    AutoBalanceTreeVisualizer(RenderWindow *win) : window(win)
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        tree = new AVLTree<NodeObject *>;

        b1 = new Button(font);
        b1->setText("Insert");
        b1->setPos(Vector2f(1200, 25));
    }

    void insert_node_viz(int data)
    {
        NodeObject *obj = new NodeObject(font);
        obj->setData(data);
        tree->insert(obj);

        tree->recursivesetPosition(tree->root, window, 600, 100, 300, 200);
    }

    void buttonClicked(Vector2i mPos)
    {
        if (b1->isOverlap(mPos))
            insert_node_viz(rand() % 500);

        // else if (b2->isOverlap(mPos))
        //     prepend_node_viz(rand() % 500);

        // else if (b3->isOverlap(mPos))
        //     del_tail_viz();

        // else if (b4->isOverlap(mPos))
        //     del_head_viz();
    }

    void buttonHover(Vector2i mPos)
    {
        b1->setNormalColor();
        // b2->setNormalColor();
        // b3->setNormalColor();
        // b4->setNormalColor();

        if (b1->isOverlap(mPos))
            b1->setHoverColor();

        // else if (b2->isOverlap(mPos))
        //     b2->setHoverColor();

        // else if (b3->isOverlap(mPos))
        //     b3->setHoverColor();

        // else if (b4->isOverlap(mPos))
        //     b4->setHoverColor();
    }

    void visualize()
    {
        tree->recursiveTreeDraw(tree->root, window);

        b1->draw(window);
    }
};

#endif