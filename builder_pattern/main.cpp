//
// Created by logan on 18-5-26.
//

#include <iostream>
#include <string>
#include <memory>
#include <list>

class Packing
{
public:
    virtual std::string Pack() = 0;
};

class Item
{
public:
    virtual std::string Name() = 0;
    virtual std::unique_ptr<Packing> PackingItem() = 0;
    virtual float Price() = 0;
};

class Wrapper : public Packing
{
public:
    std::string Pack()
    {
        return "Wrapper";
    }
};

class Bottle : public Packing
{
public:
    std::string Pack()
    {
        return "Bottle";
    }
};

class Burger : public Item
{
public:
    std::unique_ptr<Packing> PackingItem()
    {
        return std::make_unique<Wrapper>();
    }

    virtual float Price() = 0;
};

class ColdDrink : public Item
{
public:
    std::unique_ptr<Packing> PackingItem()
    {
        return std::make_unique<Bottle>();
    }

    virtual float Price() = 0;
};

class VegBurger : public Burger
{
public:
    float Price()
    {
        return 25.0f;
    }

    std::string Name()
    {
        return "Veg Burger";
    }
};

class ChickenBurger : public Burger
{
public:
    float Price()
    {
        return 50.0f;
    }

    std::string Name()
    {
        return "Chicken Burger";
    }
};

class Coke : public ColdDrink
{
public:
    float Price()
    {
        return 30.0f;
    }

    std::string Name()
    {
        return "Coke";
    }
};

class Pepsi : public ColdDrink
{
public:
    float Price()
    {
        return 35.0f;
    }

    std::string Name()
    {
        return "Pepsi";
    }
};

class Meal
{
public:
    ~Meal()
    {
        for (auto& item : item_lst_)
        {
            delete item;
            item = nullptr;
        }
    }
public:
    void AddItem(Item* item)
    {
        item_lst_.push_back(item);
    }

    float GetCost()
    {
        float cost = 0.0f;

        for (auto& item : item_lst_)
        {
            cost += item->Price();
        }

        return cost;
    }

    void ShowItems()
    {
        for (auto& item : item_lst_)
        {
            std::cout << "Item: " <<  item->Name() << std::endl;
            std::cout << "Packing: " << item->PackingItem()->Pack() << std::endl;
            std::cout << "Price: " << item->Price() << std::endl;
        }
    }
private:
    std::list<Item*> item_lst_;
};

class MealBuilder
{
public:
    void PrepareVegMeal(std::unique_ptr<Meal>& veg_meal)
    {
        veg_meal->AddItem(new VegBurger());
        veg_meal->AddItem(new Coke());
    }

    void PrepareNonVegMeal(std::unique_ptr<Meal>& veg_meal)
    {
        veg_meal->AddItem(new ChickenBurger());
        veg_meal->AddItem(new Pepsi());
    }
};

int main(int argc, char *argv[])
{
    MealBuilder meal_builder;

    std::unique_ptr<Meal> veg_meal = std::make_unique<Meal>();

    meal_builder.PrepareVegMeal(veg_meal);
    veg_meal->ShowItems();
    std::cout << "Total Cost: " << veg_meal->GetCost() << std::endl;

    std::cout << std::endl;

    std::unique_ptr<Meal> non_veg_meal = std::make_unique<Meal>();

    meal_builder.PrepareNonVegMeal(non_veg_meal);
    non_veg_meal->ShowItems();
    std::cout << "Total Cost: " << non_veg_meal->GetCost() << std::endl;

    return 1;
}