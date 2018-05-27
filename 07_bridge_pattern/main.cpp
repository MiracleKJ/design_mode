//
// Created by logan on 18-5-27.
//
#include <iostream>
#include <string>
#include <memory>

class DrawAPI
{
public:
    virtual ~DrawAPI() {}
    virtual void DrawCircle(int radius, int x, int y) = 0;
};

class RedCircle : public DrawAPI
{
public:
    void DrawCircle(int radius, int x, int y)
    {
        std::cout << "Drawing Circle[ color: red, radius: " << radius
                  << ", x: " << x << ", " << "y: " << y << " ]" << std::endl;
    }
};

class GreenCircle : public DrawAPI
{
public:
    void DrawCircle(int radius, int x, int y)
    {
        std::cout << "Drawing Circle[ color: green, radius: " << radius
                  << ", x: " << x << ", " << "y: " << y << " ]" << std::endl;
    }
};

class Shape
{
public:
    Shape(DrawAPI* draw_api) : draw_api_(draw_api) {}
    virtual ~Shape() {}

public:
    virtual void Draw() = 0;

protected:
    DrawAPI* draw_api_;
};

class Circle : public Shape
{
public:
    Circle(int x, int y, int radius, DrawAPI* draw_api)
            : Shape(draw_api)
            , x_(x)
            , y_(y)
            , radius_(radius)
    {}

    void Draw()
    {
        draw_api_->DrawCircle(radius_,x_,y_);
    }

private:
    int x_;
    int y_;
    int radius_;
};

int main(int argc, char *argv[])
{
    std::unique_ptr<RedCircle> red = std::make_unique<RedCircle>();
    std::unique_ptr<GreenCircle> green = std::make_unique<GreenCircle>();

    std::unique_ptr<Shape> red_circle = std::make_unique<Circle>(100,100,10,red.get());
    std::unique_ptr<Shape> green_circle = std::make_unique<Circle>(100,100,10,green.get());

    red_circle->Draw();
    green_circle->Draw();

    return 1;
}