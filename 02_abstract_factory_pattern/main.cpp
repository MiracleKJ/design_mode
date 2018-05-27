//
// Created by kratos on 18-1-24.
//

#include <iostream>
#include <string>
#include <memory>

class Shape
{
public:
    virtual ~Shape(){}
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

class Color
{
public:
    virtual ~Color(){}
    virtual void Fill() = 0;
};

class Red : public Color
{
public:
    void Fill()
    {
        std::cout << "Inside Red::Fill() method." << std::endl;
    }
};

class Green : public Color
{
public:
    void Fill()
    {
        std::cout << "Inside Green::Fill() method." << std::endl;
    }
};

class Blue : public Color
{
public:
    void Fill()
    {
        std::cout << "Inside Blue::Fill() method." << std::endl;
    }
};

class AbstractFactory
{
public:
    virtual ~AbstractFactory(){}
    virtual std::unique_ptr<Shape> CreateShape(const std::string& shape_type) = 0;
    virtual std::unique_ptr<Color> CreateColor(const std::string& color_type) = 0;
};

// 形状工厂
class ShapeFactory : public AbstractFactory
{
public:
    std::unique_ptr<Shape> CreateShape(const std::string& shape_type)
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

    std::unique_ptr<Color> CreateColor(const std::string& color_type)
    {
        return nullptr;
    }
};

// 颜色工厂
class ColorFactory : public AbstractFactory
{
public:
    std::unique_ptr<Shape> CreateShape(const std::string& shape_type)
    {
        return nullptr;
    }

    std::unique_ptr<Color> CreateColor(const std::string& color_type)
    {
        if ("Red" == color_type)
        {
            return std::make_unique<Red>();
        }
        else if ("Green" == color_type)
        {
            return std::make_unique<Green>();
        }
        else if ("Blue" == color_type)
        {
            return std::make_unique<Blue>();
        }
        else
        {
            return nullptr;
        }
    }
};

// 工厂生成器
class FactoryProducer
{
public:
    static std::unique_ptr<AbstractFactory> CreateFactory(const std::string& factory_type)
    {
        if ("Shape" == factory_type)
        {
            return std::make_unique<ShapeFactory>();
        }
        else if ("Color" == factory_type)
        {
            return std::make_unique<ColorFactory>();
        }
        else
        {
            return nullptr;
        }
    }
};

int main(int argc, char *argv[])
{
    // 形状工厂
    auto shape_factory = FactoryProducer::CreateFactory("Shape");

    auto shape1 = shape_factory->CreateShape("Circle");
    shape1->Draw();

    auto shape2 = shape_factory->CreateShape("Rectangle");
    shape2->Draw();

    auto shape3 = shape_factory->CreateShape("Square");
    shape3->Draw();

    // 颜色工厂
    auto color_factory = FactoryProducer::CreateFactory("Color");

    auto color1 = color_factory->CreateColor("Red");
    color1->Fill();

    auto color2 = color_factory->CreateColor("Green");
    color2->Fill();

    auto color3 = color_factory->CreateColor("Blue");
    color3->Fill();

    return 1;
}