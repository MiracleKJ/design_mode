//
// Created by logan on 18-5-27.
//

#include <iostream>
#include <memory>
#include <list>
#include <string.h>
#include <algorithm>

class Person
{
public:
    Person(const std::string& name, const std::string& gender, const std::string& marital_status)
    : name_(name)
    , gender_(gender)
    , marital_status_(marital_status)
    {}

    bool operator==(const Person& rhs) const
    {
        return name_ == rhs.name_ && gender_ == rhs.gender_ && marital_status_ == rhs.marital_status_;
    }

    bool operator!=(const Person& rhs) const
    {
        return !(operator==(rhs));
    }

    std::string GetName() const
    {
        return name_;
    }

    std::string GetGender() const
    {
        return gender_;
    }

    std::string GetMaritalStatus() const
    {
        return marital_status_;
    }

private:
    std::string name_;
    std::string gender_;
    std::string marital_status_;
};

class Criteria
{
public:
    virtual std::list<Person> MeetCriteria(std::list<Person>& person_lst) = 0;
};

class CriteriaMale : public Criteria
{
public:
    std::list<Person> MeetCriteria(std::list<Person>& person_lst)
    {
        std::list<Person> male_persons;

        for (const auto& person : person_lst)
        {
            if (0 == strcasecmp("male", person.GetGender().c_str()))
            {
                male_persons.push_back(person);
            }
        }

        return std::move(male_persons);
    }
};

class CriteriaFemale : public Criteria
{
public:
    std::list<Person> MeetCriteria(std::list<Person>& person_lst)
    {
        std::list<Person> female_persons;

        for (const auto& person : person_lst)
        {
            if (0 == strcasecmp("female", person.GetGender().c_str()))
            {
                female_persons.push_back(person);
            }
        }

        return std::move(female_persons);
    }
};

class CriteriaSingle : public Criteria
{
public:
    std::list<Person> MeetCriteria(std::list<Person>& person_lst)
    {
        std::list<Person> single_persons;

        for (const auto& person : person_lst)
        {
            if (0 == strcasecmp("single", person.GetMaritalStatus().c_str()))
            {
                single_persons.push_back(person);
            }
        }

        return std::move(single_persons);
    }
};

class AndCriteria : public Criteria
{
public:
    AndCriteria(Criteria* criterai,Criteria* other_criteria)
    : criteria_(criterai)
    , other_criteria_(other_criteria)
    {}

    std::list<Person> MeetCriteria(std::list<Person>& person_lst)
    {
        std::list<Person> first_criteria_persons = criteria_->MeetCriteria(person_lst);
        return std::move(other_criteria_->MeetCriteria(first_criteria_persons));
    }

private:
    Criteria* criteria_;
    Criteria* other_criteria_;
};

class OrCriteria : public Criteria
{
public:
    OrCriteria(Criteria* criterai,Criteria* other_criteria)
            : criteria_(criterai)
            , other_criteria_(other_criteria)
    {}

    std::list<Person> MeetCriteria(std::list<Person>& person_lst)
    {
        bool find = false;

        std::list<Person> first_criteria_persons = criteria_->MeetCriteria(person_lst);
        std::list<Person> orther_criteria_persons = other_criteria_->MeetCriteria(person_lst);

        for (const auto& other_person : orther_criteria_persons)
        {
            for (const auto& first_person : first_criteria_persons)
            {
                if (first_person == other_person)
                {
                    find = true;
                    break;
                }
                else
                {
                    find = false;
                }
            }

            if (!find)
            {
                first_criteria_persons.push_back(other_person);
            }
        }

        return std::move(first_criteria_persons);
    }

private:
    Criteria* criteria_;
    Criteria* other_criteria_;
};


void PrintPerson(const std::list<Person>& persons)
{
    for (const auto& person : persons)
    {
        std::cout << "Person: [ Name: " << person.GetName()
                  << ", Gender: " << person.GetGender()
                  << ", Marital Status: " << person.GetMaritalStatus()
                  << " ]" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::list<Person> persons;

    persons.push_back(Person("Robert","Male","Single"));
    persons.push_back(Person("John","Male","Married"));
    persons.push_back(Person("Laura","Female","Married"));
    persons.push_back(Person("Diana","Female","Single"));
    persons.push_back(Person("Mike","Male","Single"));
    persons.push_back(Person("Bobby","Male","Single"));

    std::unique_ptr<Criteria> male = std::make_unique<CriteriaMale>();
    std::unique_ptr<Criteria> female = std::make_unique<CriteriaFemale>();
    std::unique_ptr<Criteria> single = std::make_unique<CriteriaSingle>();
    std::unique_ptr<Criteria> single_and_male = std::make_unique<AndCriteria>(single.get(),male.get());
    std::unique_ptr<Criteria> single_or_male = std::make_unique<OrCriteria>(single.get(),female.get());

    std::cout << "Males" << std::endl;
    PrintPerson(male->MeetCriteria(persons));
    std::cout << std::endl;

    std::cout << "Females" << std::endl;
    PrintPerson(female->MeetCriteria(persons));
    std::cout << std::endl;

    std::cout << "Singles" << std::endl;
    PrintPerson(single->MeetCriteria(persons));
    std::cout << std::endl;

    std::cout << "SingleAndMales" << std::endl;
    PrintPerson(single_and_male->MeetCriteria(persons));
    std::cout << std::endl;

    std::cout << "SingleOrMales" << std::endl;
    PrintPerson(single_or_male->MeetCriteria(persons));
    std::cout << std::endl;

    return 1;
}