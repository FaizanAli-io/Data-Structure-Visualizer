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
    RectangleShape line;
    CircleShape triangle;

    Arrow()
    {
        float r = 30.f;
        triangle.setRadius(r);
        triangle.setOrigin(r, r);
        triangle.setPointCount(3);
        triangle.setOutlineThickness(-3.f);

        line.setFillColor(Color(0, 255, 0));
        triangle.setFillColor(Color(0, 255, 0));
        triangle.setOutlineColor(Color(255, 255, 0));
    }

    void set(Vector2f beg, Vector2f end)
    {
        Vector2f dirVector = (end - beg) * 0.6f;
        float arrowLength = magnitude(dirVector.x, dirVector.y);
        int angleBetween = angleInDegrees(dirVector.x, dirVector.y);

        line.setPosition(beg);
        triangle.setPosition(beg + dirVector);
        line.setSize(Vector2f(arrowLength, 6.f));

        line.setRotation(angleBetween);
        triangle.setRotation(angleBetween + 90);
    }

    void draw(RenderWindow *win)
    {
        win->draw(line);
        win->draw(triangle);
    }
};

struct NodeObject
{
    Text text;
    Arrow pointer;
    CircleShape shape;

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

    void setText(string value)
    {
        text.setString(value);
        Vector2f textSize = text.getGlobalBounds().getSize();
        text.setOrigin(textSize.x * 0.5, textSize.y * 0.75);
    }

    void setPos(int x, int y)
    {
        shape.setPosition(x, y);
        text.setPosition(x, y);
    }

    void setArrow(Vector2f dst)
    {
        Vector2f src = shape.getPosition();
        pointer.set(src, dst);
    }

    void setAllAlpha(int i)
    {
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
        pointer.draw(win);
        win->draw(shape);
        win->draw(text);
    }
};

ostream &operator<<(ostream &out, NodeObject &obj)
{
    string s = obj.text.getString();
    return out << s;
}

struct Button
{
    Text text;
    RectangleShape box;

    Button(Font &font)
    {
        text.setFont(font);
        text.setCharacterSize(72);
        text.setFillColor(Color(125, 0, 155));

        int w = 350, b = 150;
        box.setSize(Vector2f(w, b));
        box.setOutlineThickness(-6.f);
        box.setFillColor(Color(0, 0, 155));
    }

    void setText(string x)
    {
        text.setString(x);
        Vector2f textSize = text.getGlobalBounds().getSize();
        text.setOrigin(textSize.x * 0.5, textSize.y * 0.75);
    }

    void setPos(int x, int y)
    {
        box.setPosition(x, y);
        text.setPosition(x + 175, y + 75);
    }

    bool isOverlap(int x, int y)
    {
        Vector2f pos = box.getPosition();
        Vector2f size = box.getSize();

        return x >= pos.x && x <= pos.x + size.x &&
               y >= pos.y && y <= pos.y + size.y;
    }

    void draw(RenderWindow *win)
    {
        win->draw(box);
        win->draw(text);
    }

    void setNormalColor()
    {
        box.setOutlineColor(Color(0, 0, 75));
    }

    void setHoverColor()
    {
        box.setOutlineColor(Color(0, 75, 0));
    }
};

#endif