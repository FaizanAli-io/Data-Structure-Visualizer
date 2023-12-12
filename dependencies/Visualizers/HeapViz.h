#include "../Structures.h"
#include "../GraphicObjects.h"

#ifndef HEAP
#define HEAP

struct HeapVisualizer
{
    const float updateSpeed = 0.01;
    const int animationFrames = 50;
    bool minheap;

    Font font;
    Clock clock;
    RenderWindow *window;
    Button *b1, *b2, *b3, *b4;
    Heap<NodeObject *> *heap;
    NodeObject *lastVisited;

    HeapVisualizer(RenderWindow *win, bool min) : window(win), minheap(min)
    {
        font.loadFromFile("assets/fonts/font2.ttf");
        heap = new Heap<NodeObject *>(minheap);
        lastVisited = nullptr;

        b1 = new Button(font, 54);
        b1->setText("Insert Node");
        b1->setPos(Vector2f(1200, 25));

        b2 = new Button(font, 54);
        b2->setText("Delete Root");
        b2->setPos(Vector2f(1200, 250));

        b3 = new Button(font, 54);
        b3->setText("Level Order");
        b3->setPos(Vector2f(1200, 475));

        b4 = new Button(font, 54);
        b4->setText("Switch");
        b4->setPos(Vector2f(1200, 700));
    }

    void time_delay()
    {
        clock.restart();

        float delay = updateSpeed * 50;

        while (clock.getElapsedTime() <= seconds(delay))
            ;
    }

    void insert_node_viz(int data)
    {
        NodeObject *obj = new NodeObject(font);
        obj->setData(data);

        TreeNode<NodeObject *> *newnode = heap->insert(obj);

        setNextPosition(heap->root, 600, 100, 300, 200);

        movementLoop();

        time_delay();

        heap->heapifyUp(newnode);

        setNextPosition(heap->root, 600, 100, 300, 200);

        movementLoop();
    }

    void delete_root_viz()
    {
        heap->removeRoot();

        setNextPosition(heap->root, 600, 100, 300, 200);

        movementLoop();

        time_delay();

        heap->heapifyDown(heap->root);

        setNextPosition(heap->root, 600, 100, 300, 200);

        movementLoop();
    }

    void levelorderTraversal()
    {
        LinkedList<TreeNode<NodeObject *> *> nodes;

        nodes.append(heap->root);

        while (!nodes.isEmpty())
        {
            TreeNode<NodeObject *> *current = nodes.removeHead();

            if (current->left)
                nodes.append(current->left);

            if (current->right)
                nodes.append(current->right);

            if (lastVisited != nullptr)
                lastVisited->shape.setOutlineThickness(-4.f);

            current->data->shape.setOutlineColor(Color(0, 255, 255));
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

    void switchHeap()
    {
        LinkedList<TreeNode<NodeObject *> *> nodes;

        minheap = !minheap;

        Heap<NodeObject *> *newheap = new Heap<NodeObject *>(minheap);

        nodes.append(heap->root);

        while (!nodes.isEmpty())
        {
            TreeNode<NodeObject *> *current = nodes.removeHead();

            if (current->left)
                nodes.append(current->left);

            if (current->right)
                nodes.append(current->right);

            newheap->insert(current->data);
        }

        heap = newheap;

        setNextPosition(heap->root, 600, 100, 300, 200);

        movementLoop();
    }

    void buttonClicked(Vector2i mPos)
    {
        if (b1->isOverlap(mPos))
            insert_node_viz(rand() % 500);

        else if (b2->isOverlap(mPos))
            delete_root_viz();

        else if (b3->isOverlap(mPos))
            levelorderTraversal();

        else if (b4->isOverlap(mPos))
            switchHeap();
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
                moveNodes(heap->root);
                clock.restart();
                i++;
            }

            window->clear();
            visualize();
            window->display();
        }

        finalizePosition(heap->root);
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
        drawTree(heap->root);

        b1->draw(window);
        b2->draw(window);
        b3->draw(window);
        b4->draw(window);
    }
};

#endif