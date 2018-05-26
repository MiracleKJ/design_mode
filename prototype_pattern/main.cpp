//
// Created by logan on 18-5-26.
//

#include <iostream>
#include <string>
#include <map>
#include <memory>

class Shape
{
public:
    Shape(const std::string& type = "Shape") : type_(type)
    {}

    std::string GetType()
    {
        return type_;
    }

    std::string GetId()
    {
        return id_;
    }

    void SetId(const std::string& id)
    {
        id_ = id;
    }

    virtual void Draw() = 0;

protected:
    std::string type_;

private:
    std::string id_;
};


class Rectangle : public Shape
{
public:
    Rectangle() : Shape("Rectangle")
    {}

    void Draw()
    {
        std::cout << "Inside Rectangle::Draw() method." << std::endl;
    }
};

class Square : public Shape
{
public:
    Square() : Shape("Square")
    {}

    void Draw()
    {
        std::cout << "Inside Square::Draw() method." << std::endl;
    }
};

class Circle : public Shape
{
public:
    Circle() : Shape("Circle")
    {}

    void Draw()
    {
        std::cout << "Inside Circle::Draw() method." << std::endl;
    }
};

class ShapeCache
{
public:
    Shape* GetShape(const std::string& id)
    {

        return shape_map_[id].get();
    }

    void LoadCache()
    {
        shape_map_.insert(std::make_pair("1",std::make_unique<Circle>()));
        shape_map_.insert(std::make_pair("2",std::make_unique<Square>()));
        shape_map_.insert(std::make_pair("3",std::make_unique<Rectangle>()));
    }

private:
    std::map<std::string, std::unique_ptr<Shape> > shape_map_;
};

void test(ShapeCache* shape_cache)
{
    auto shape1 = shape_cache->GetShape("1");
    std::cout << "Shape: " << shape1->GetType() << std::endl;
    shape1->Draw();

    auto shape2 = shape_cache->GetShape("2");
    std::cout << "Shape: " << shape2->GetType() << std::endl;
    shape2->Draw();

    auto shape3 = shape_cache->GetShape("3");
    std::cout << "Shape: " << shape3->GetType() << std::endl;
    shape3->Draw();
}

int main(int argc, char *argv[])
{
    ShapeCache shape_cache;
    shape_cache.LoadCache();

    test(&shape_cache);

    std::cout << std::endl;

    test(&shape_cache);

    return 1;
}