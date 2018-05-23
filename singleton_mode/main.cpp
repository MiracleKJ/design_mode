//
// Created by logan on 18-5-23.
//

#include <iostream>
#include <memory>

class SingleObject
{
private:
    SingleObject() = default;
    SingleObject(const SingleObject&) = delete;
    SingleObject(const SingleObject&&) = delete;
    SingleObject& operator=(const SingleObject&) = delete;

public:
    static SingleObject* GetInstance()
    {
        if (nullptr == single_object_)
        {
            single_object_ = new SingleObject();
        }

        return single_object_;
    }

    static void DestroyInstance()
    {
        if (single_object_)
        {
            delete single_object_;
            single_object_ = nullptr;
        }
    }

    void Test()
    {
        std::cout << "hello world" << std::endl;
    }

private:
    static SingleObject* single_object_;
};

SingleObject* SingleObject::single_object_ = nullptr;

int main(int argc, char *argv[])
{
    SingleObject::GetInstance()->Test();
    SingleObject::GetInstance()->Test();
    SingleObject::GetInstance()->Test();

    SingleObject::DestroyInstance();
    return 1;
}