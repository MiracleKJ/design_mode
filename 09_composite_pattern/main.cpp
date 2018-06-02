//
// Created by logan on 18-6-2.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

class Employee
{
public:
    Employee(const std::string &name, const std::string &dept, int salary)
            : name_(name), dept_(dept), salary_(salary) {}

    bool operator==(const Employee &rhs) const
    {
        return (name_ == rhs.name_ && dept_ == rhs.dept_ && salary_ == rhs.salary_);
    }

    void Add(const Employee &e)
    {
        subordinates_.push_back(e);
    }

    void Remove(const Employee &e)
    {
        subordinates_.erase(std::find(subordinates_.cbegin(), subordinates_.cend(), e));
    }

    std::vector<Employee> GetSubordinates() const
    {
        return subordinates_;
    }

    void Print()
    {
        std::cout << "Employee :[ Name : " << name_ << ", dept : " << dept_ << ", salary : " << salary_ << " ]" <<std::endl;
    }

private:
    std::string name_;
    std::string dept_;
    int salary_;
    std::vector<Employee> subordinates_;
};

void PrintEmployee(std::vector<Employee> subordinates)
{
    for (auto &employee : subordinates)
    {
        employee.Print();
        PrintEmployee(employee.GetSubordinates());
    }
}

int main(int argc, char *argv[])
{
    Employee ceo("John", "ceo", 30000);
    Employee head_sales("Robert", "Head Sales", 20000);
    Employee head_marketing("Michel", "Head Marketing", 20000);

    Employee clerk1("Laura", "Marketing", 10000);
    Employee clerk2("Bob", "Marketing", 10000);

    Employee sales_executive1("Richard", "Sales", 10000);
    Employee sales_executive2("Rob", "Sales", 10000);

    head_sales.Add(sales_executive1);
    head_sales.Add(sales_executive2);

    head_marketing.Add(clerk1);
    head_marketing.Add(clerk2);

    ceo.Add(head_sales);
    ceo.Add(head_marketing);

    ceo.Print();
    PrintEmployee(ceo.GetSubordinates());

    return 1;
}