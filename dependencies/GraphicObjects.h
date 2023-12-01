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

    void setPos(Vector2f pos)
    {
        shape.setPosition(pos.x, pos.y);
        text.setPosition(pos.x, pos.y);
    }

    void setArrow(Vector2f dst)
    {
        Vector2f src = shape.getPosition();
        pointer.set(src, dst);
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
        pointer.draw(win);
        win->draw(shape);
        win->draw(text);
    }
};

struct BoxObject
{
    Text text;
    RectangleShape box;
    int w = 400, b = 75;

    BoxObject(Font &font)
    {
        text.setFont(font);
        text.setCharacterSize(64);
        text.setFillColor(Color(255, 0, 255));

        w = 400, b = 75;
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
        if (!enabled)
            return;

        win->draw(box);
        win->draw(text);
    }

    void enableButton() { enabled = true; }

    void disableButton() { enabled = false; }

    void setHoverColor() { box.setOutlineColor(Color(0, 75, 0)); }

    void setNormalColor() { box.setOutlineColor(Color(0, 0, 75)); }
};

ostream &operator<<(ostream &out, NodeObject &obj)
{
    string s = obj.text.getString();
    return out << s;
}

#endif
