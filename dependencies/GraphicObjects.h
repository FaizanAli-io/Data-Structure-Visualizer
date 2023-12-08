#include <cstdlib>
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Utilities.h"

#ifndef GRAPHICOBJECTS
#define GRAPHICOBJECTS

struct Arrow
{
    bool visible;
    RectangleShape line;
    CircleShape triangle;

    Arrow()
    {
        float r = 30;
        triangle.setRadius(r);
        triangle.setOrigin(r, r);
        triangle.setPointCount(3);
        triangle.setOutlineThickness(-2);

        line.setFillColor(Color(0, 255, 0));
        triangle.setFillColor(Color(0, 255, 0));
        triangle.setOutlineColor(Color(255, 255, 0));

        visible = false;
    }

    void set(Vector2f beg, Vector2f end, float scale = 1)
    {
        visible = true;

        Vector2f dirVector = (end - beg) * scale;
        int arrowLength = magnitude(dirVector.x, dirVector.y);
        int angleBetween = angleInDegrees(dirVector.x, dirVector.y);

        line.setPosition(beg);
        triangle.setPosition(beg + dirVector);
        line.setSize(Vector2f(arrowLength, 10));

        line.setRotation(angleBetween);
        triangle.setRotation(angleBetween + 90);
    }

    void draw(RenderWindow *win)
    {
        if (visible)
        {
            win->draw(line);
            win->draw(triangle);
        }
    }
};

struct Label : public Arrow
{
    Text text;

    Label(Font &font, string value) : Arrow()
    {
        text.setFont(font);
        text.setCharacterSize(36);
        text.setFillColor(Color(125, 0, 155));
        text.setString(value);

        Vector2f textSize = text.getGlobalBounds().getSize();
        text.setOrigin(textSize.x * 0.5, textSize.y * 0.75);
    }

    void set(Vector2f beg, Vector2f end, Vector2f offset, float scale = 1)
    {
        Arrow::set(beg, end, scale);
        text.setPosition(beg + offset);
    }

    void draw(RenderWindow *win)
    {
        Arrow::draw(win);
        win->draw(text);
    }
};

struct NodeObject
{
    int nodeData;

    Text text;
    Arrow pointer1;
    Arrow pointer2;
    CircleShape shape;

    Vector2f dir;
    Vector2f nextPos;

    NodeObject(Font &font)
    {
        float r = 80.f;
        shape.setRadius(r);
        shape.setOrigin(r, r);
        shape.setPointCount(100);
        shape.setOutlineThickness(-4.f);
        shape.setFillColor(Color(0, 0, 255));
        shape.setOutlineColor(Color(255, 0, 0));

        text.setFont(font);
        text.setCharacterSize(72);
        text.setFillColor(Color(255, 0, 255));
    }

    void setData(int val)
    {
        nodeData = val;
        setText();
    }

    void setText()
    {
        text.setString(to_string(nodeData));
        Vector2f textSize = text.getGlobalBounds().getSize();
        text.setOrigin(textSize.x * 0.5, textSize.y * 0.75);
    }

    void setPos(Vector2f pos)
    {
        shape.setPosition(pos.x, pos.y);
        text.setPosition(pos.x, pos.y);
    }

    void moveBody()
    {
        shape.move(dir.x, dir.y);
        text.move(dir.x, dir.y);
    }

    void setNextPos(Vector2f pos, int div)
    {
        dir = pos - shape.getPosition();
        nextPos = pos;
        dir.x /= div;
        dir.y /= div;
        pointer1.visible = false;
        pointer2.visible = false;
    }

    void setArrow(Vector2f dst, int n, float factor = 0.6f)
    {
        Vector2f src = shape.getPosition();

        if (n == 1)
            pointer1.set(src, dst, factor);
        else if (n == 2)
            pointer2.set(src, dst, factor);
    }

    void setAllAlpha(int i)
    {
        i = i > 255 ? 255 : i;
        i = i < 0 ? 0 : i;

        Color col = shape.getFillColor();
        col.a = i;
        shape.setFillColor(col);

        col = shape.getOutlineColor();
        col.a = i;
        shape.setOutlineColor(col);

        col = text.getFillColor();
        col.a = i;
        text.setFillColor(col);
    }

    void draw(RenderWindow *win)
    {
        pointer1.draw(win);
        pointer2.draw(win);
        win->draw(shape);
        win->draw(text);
    }

    bool operator>(NodeObject &obj) { return this->nodeData > obj.nodeData; }

    bool operator<(NodeObject &obj) { return this->nodeData < obj.nodeData; }
};

struct BoxObject
{
    int w, b;
    Text text;
    RectangleShape box;

    BoxObject(Font &font)
    {
        text.setFont(font);
        text.setCharacterSize(64);
        text.setFillColor(Color(255, 0, 255));

        w = 300, b = 80;
        box.setSize(Vector2f(w, b));
        box.setOutlineThickness(-4.f);
        box.setFillColor(Color(0, 0, 255));
        box.setOutlineColor(Color(255, 0, 0));
    }

    void setText(string x)
    {
        text.setString(x);
        Vector2f textSize = text.getGlobalBounds().getSize();
        text.setOrigin(textSize.x * 0.5, textSize.y * 0.75);
    }

    void setPos(Vector2f pos)
    {
        box.setPosition(pos.x, pos.y);
        text.setPosition(pos.x + w / 2, pos.y + b / 2);
    }

    void setAllAlpha(int i)
    {
        i = i > 255 ? 255 : i;
        i = i < 0 ? 0 : i;

        Color col = box.getFillColor();
        col.a = i;
        box.setFillColor(col);

        col = box.getOutlineColor();
        col.a = i;
        box.setOutlineColor(col);

        col = text.getFillColor();
        col.a = i;
        text.setFillColor(col);
    }

    void draw(RenderWindow *win)
    {
        win->draw(box);
        win->draw(text);
    }
};

struct Button : public BoxObject
{
    bool enabled;

    Button(Font &font) : BoxObject(font), enabled(true)
    {
        text.setCharacterSize(72);
        text.setFillColor(Color(125, 0, 155));

        w = 350, b = 150;
        box.setSize(Vector2f(w, b));
        box.setOutlineThickness(-8.f);
        box.setFillColor(Color(0, 0, 155));
    }

    bool isOverlap(Vector2i mPos)
    {
        if (!enabled)
            return false;

        Vector2f pos = box.getPosition();
        Vector2f size = box.getSize();

        return mPos.x >= pos.x && mPos.x <= pos.x + size.x &&
               mPos.y >= pos.y && mPos.y <= pos.y + size.y;
    }

    void draw(RenderWindow *win)
    {
        if (enabled)
        {
            win->draw(box);
            win->draw(text);
        }
    }

    void setHoverColor() { box.setOutlineColor(Color(0, 75, 0)); }

    void setNormalColor() { box.setOutlineColor(Color(0, 0, 75)); }
};

ostream &operator<<(ostream &out, NodeObject *obj)
{
    string s = obj->text.getString();
    return out << s;
}

#endif
