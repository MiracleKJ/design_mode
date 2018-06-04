//
// Created by logan on 18-6-4.
//
#include <iostream>
#include <string>
#include <memory>

class Shape
{
public:
    ~Shape(){}

    virtual void Draw() = 0;
};

class Rectangle : public Shape
{
public:
    void Draw()
    {
        std::cout << "Shape: Rectangle" << std::endl;
    }
};

class Circle : public Shape
{
public:
    void Draw()
    {
        std::cout << "Shape: Circle" << std::endl;
    }
};

class ShapeDecorator : public Shape
{
public:
    ShapeDecorator(Shape* decorated_shape) : decorated_shape_(decorated_shape) {}

    void Draw()
    {
        decorated_shape_->Draw();
    }

protected:
    Shape* decorated_shape_;
};

class RedShapeDecorator : public ShapeDecorator
{
public:
    RedShapeDecorator(Shape* decorated_shape) : ShapeDecorator(decorated_shape) {}

    void Draw()
    {
        decorated_shape_->Draw();
        SetRedBorder(decorated_shape_);
    }

    void SetRedBorder(Shape* decorated_shape)
    {
        std::cout << "Border COlor: Red" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    auto circle = std::make_unique<Circle>();

    auto circle2 = std::make_unique<Circle>();
    auto rectangle = std::make_unique<Rectangle>();

    auto red_circle = std::make_unique<RedShapeDecorator>(circle2.get());
    auto red_rectangle = std::make_unique<RedShapeDecorator>(rectangle.get());

    circle->Draw();

    red_circle->Draw();

    red_rectangle->Draw();

    return 1;
}