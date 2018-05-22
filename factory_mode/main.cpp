//
// Created by kratos on 18-1-24.
//

#include <iostream>
#include <string>
#include <memory>

class Shape
{
public:
    virtual void Draw() = 0;
};

class Rectangle : public Shape
{
public:
    void Draw()
    {
        std::cout << "Inside Rectangle::Draw() method." << std::endl;
    }
};

class Square : public Shape
{
public:
    void Draw()
    {
        std::cout << "Inside Square::Draw() method." << std::endl;
    }
};

class Circle : public Shape
{
public:
    void Draw()
    {
        std::cout << "Inside Circle::Draw() method." << std::endl;
    }
};

// 形状工厂
class ShapeFactory
{
public:
    static std::unique_ptr<Shape> CreateShape(const std::string& shape_type)
    {
        if ("Rectangle" == shape_type)
        {
            return std::make_unique<Rectangle>();
        }
        else if ("Square" == shape_type)
        {
            return std::make_unique<Square>();
        }
        else if ("Circle" == shape_type)
        {
            return std::make_unique<Circle>();
        }
        else
        {
            return nullptr;
        }
    }
};

int main(int argc, char *argv[])
{
    auto shape1 = ShapeFactory::CreateShape("Rectangle");
    shape1->Draw();

    auto shape2 = ShapeFactory::CreateShape("Square");
    shape2->Draw();

    auto shape3 = ShapeFactory::CreateShape("Circle");
    shape3->Draw();

    return 1;
}
