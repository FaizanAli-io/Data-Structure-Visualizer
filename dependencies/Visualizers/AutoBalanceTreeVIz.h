#include "../Structures.h"
#include "../GraphicObjects.h"

#ifndef AVLTREE
#define AVLTREE

struct AutoBalanceTreeVisualizer
{
    const float updateSpeed = 0.01;
    const int animationFrames = 50;

    Font font;
    Clock clock;
    RenderWindow *window;
    Button *b1, *b2, *b3, *b4;
    AVLTree<NodeObject *> *tree;
    NodeObject *lastVisited;

    AutoBalanceTreeVisualizer(RenderWindow *win) : window(win)
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        tree = new AVLTree<NodeObject *>;
        lastVisited = nullptr;

        b1 = new Button(font, 54);
        b1->setText("Insert Node");
        b1->setPos(Vector2f(1200, 25));

        b2 = new Button(font, 54);
        b2->setText("Delete Root");
        b2->setPos(Vector2f(1200, 250));

        b3 = new Button(font);
        b3->setText("In Order");
        b3->setPos(Vector2f(1200, 475));

        b4 = new Button(font, 54);
        b4->setText("Level Order");
        b4->setPos(Vector2f(1200, 700));
    }

    void time_delay()
    {
        clock.restart();

        float delay = updateSpeed * 40;

        while (clock.getElapsedTime() <= seconds(delay))
            ;
    }

    void insert_node_viz(int data)
    {
        NodeObject *obj = new NodeObject(font);
        obj->setData(data);

        tree->insert(obj);

        setNextPosition(tree->root, 600, 100, 300, 200);

        movementLoop();

        time_delay();

        tree->root = tree->balanceTree(tree->root);

        setNextPosition(tree->root, 600, 100, 300, 200);

        movementLoop();
    }

    void deleteRoot()
    {
        tree->remove(tree->root->data);

        setNextPosition(tree->root, 600, 100, 300, 200);

        movementLoop();
    }

    void inorderTraversal(TreeNode<NodeObject *> *node)
    {
        if (lastVisited != nullptr)
            lastVisited->shape.setOutlineThickness(-4.f);

        if (node != nullptr)
        {
            inorderTraversal(node->left);

            node->data->shape.setOutlineColor(Color(0, 255, 0));
            node->data->shape.setOutlineThickness(8.f);
            lastVisited = node->data;
            time_delay();

            window->clear();
            visualize();
            window->display();

            inorderTraversal(node->right);
        }
    }

    void levelorderTraversal()
    {
        LinkedList<TreeNode<NodeObject *> *> nodes;

        nodes.append(tree->root);

        while (!nodes.isEmpty())
        {
            TreeNode<NodeObject *> *current = nodes.removeHead();

            if (current->left)
                nodes.append(current->left);

            if (current->right)
                nodes.append(current->right);

            if (lastVisited != nullptr)
                lastVisited->shape.setOutlineThickness(-4.f);

            current->data->shape.setOutlineColor(Color(255, 0, 0));
            current->data->shape.setOutlineThickness(8.f);
            lastVisited = current->data;
            time_delay();

            window->clear();
            visualize();
            window->display();
        }

        if (lastVisited != nullptr)
            lastVisited->shape.setOutlineThickness(-4.f);
    }

    void buttonClicked(Vector2i mPos)
    {
        if (b1->isOverlap(mPos))
            insert_node_viz(rand() % 500);

        else if (b2->isOverlap(mPos))
            deleteRoot();

        else if (b3->isOverlap(mPos))
            inorderTraversal(tree->root);

        else if (b4->isOverlap(mPos))
            levelorderTraversal();
    }

    void buttonHover(Vector2i mPos)
    {
        b1->setNormalColor();
        b2->setNormalColor();
        b3->setNormalColor();
        b4->setNormalColor();

        if (b1->isOverlap(mPos))
            b1->setHoverColor();

        else if (b2->isOverlap(mPos))
            b2->setHoverColor();

        else if (b3->isOverlap(mPos))
            b3->setHoverColor();

        else if (b4->isOverlap(mPos))
            b4->setHoverColor();
    }

    void setNextPosition(TreeNode<NodeObject *> *node, int x, int y, int dx, int dy)
    {
        if (node != nullptr)
        {
            node->data->setNextPos(Vector2f(x, y), animationFrames);

            setNextPosition(node->left, x - dx, y + dy, dx / 2, dy);
            setNextPosition(node->right, x + dx, y + dy, dx / 2, dy);
        }
    }

    void movementLoop()
    {
        int i = 0;
        while (i < animationFrames)
        {
            if (clock.getElapsedTime() >= seconds(updateSpeed))
            {
                moveNodes(tree->root);
                clock.restart();
                i++;
            }

            window->clear();
            visualize();
            window->display();
        }

        finalizePosition(tree->root);
    }

    void finalizePosition(TreeNode<NodeObject *> *node)
    {
        if (node != nullptr)
        {
            node->data->setPos(node->data->nextPos);

            if (node->left == nullptr)
                node->data->pointer1.visible = false;
            else
                node->data->setArrow(node->left->data->shape.getPosition(), 1);

            if (node->right == nullptr)
                node->data->pointer2.visible = false;
            else
                node->data->setArrow(node->right->data->shape.getPosition(), 2);

            finalizePosition(node->left);
            finalizePosition(node->right);
        }
    }

    void moveNodes(TreeNode<NodeObject *> *node)
    {
        if (node != nullptr)
        {
            node->data->moveBody();
            moveNodes(node->left);
            moveNodes(node->right);
        }
    }

    void drawTree(TreeNode<NodeObject *> *node)
    {
        if (node != nullptr)
        {
            node->data->draw(window);
            drawTree(node->left);
            drawTree(node->right);
        }
    }

    void visualize()
    {
        drawTree(tree->root);

        b1->draw(window);
        b2->draw(window);
        b3->draw(window);
        b4->draw(window);
    }
};

#endif