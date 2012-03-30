//////////////////////////////////////////////////////////////////////////
//  * From Cracking the Coding Interview, 5th edition 
//  * Problem 3.7
//  *
//  * An animal shelter holds only dogs and cats, and operates on a strictly
//  * "First in, first out" basis. People mush adopt either the "oldest" (based on
//  * arrival time) of all animals at the shelter, or they can select whether they
//  * would prefer a dog or a cat (and will receive the oldest animal of that type).
//  * They cannot select which specific animal they would like. Create the data
//  * structures to maintain this system and implement operations such as
//  * enqueue, dequeueAny, dequeueDog and dequeueCat.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <list>
#include <sstream>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

class Animal
{
public:
    Animal(std::string name, int id) : name_(name), id_(id) {}

    std::string name() const { return name_; }
    int id() const { return id_; }
    void NewId( int id ) { id_ = id; }

    virtual void CoutVoice() = 0;

private:
    std::string name_;
    int id_;
};

class Dog : public Animal
{
public:
    Dog(std::string name, int id) : Animal(name, id) {}

    void CoutVoice() { std::cout << "woolf, wuulf " << std::endl; }
};

class Cat : public Animal
{
public:
    Cat(std::string name, int id) : Animal(name, id) {}

    void CoutVoice() { std::cout << "miao, miaowuu " << std::endl; }
};

class AnimalShelter
{
public:
    AnimalShelter() : nextid(0) {}
    void Enqueue(Animal*);
    Dog* DequeDog();
    Cat* DequeCat();
    Animal* DequeAny();
    bool IsEmpty() { return doglist_.empty() && catlist_.empty(); }

private:
    std::list<Dog> doglist_;
    std::list<Cat> catlist_;
    int nextid;
};

void AnimalShelter::Enqueue(Animal* apet)
{
    if (dynamic_cast<Dog*>(apet)) // dog
    {
        doglist_.push_back(*dynamic_cast<Dog*>(apet));
    }
    else
    {
        catlist_.push_back(*dynamic_cast<Cat*>(apet));
    }
    ++nextid;
}

Dog* AnimalShelter::DequeDog()
{
    if (doglist_.empty())
    {
        return nullptr;
    } 
    else
    {
        Dog* next_dog = new Dog(doglist_.front());
        doglist_.pop_front();
        return next_dog;
    }
}

Cat* AnimalShelter::DequeCat()
{
    if (catlist_.empty())
    {
        return nullptr;
    } 
    else
    {
        Cat* next_cat = new Cat(catlist_.front());
        catlist_.pop_front();
        return next_cat;
    }
}

Animal* AnimalShelter::DequeAny()
{
    if (IsEmpty())
    {
        return nullptr;
    }

    Animal* next_pet;
    if (catlist_.empty() || doglist_.front().id() < catlist_.front().id())
    {
        next_pet = new Dog(doglist_.front());
        doglist_.pop_front();
    } 
    else
    {
        next_pet = new Cat(catlist_.front());
        catlist_.pop_front();
    }
    return next_pet;
}

//////////////////////////////////////////////////////////////////////////
}


int main(int argc, char** argv)
{
    using namespace std;

    const int ALL_SHELTER_PET_NUM = 10;

    AnimalShelter petshelter;
    for (int i=0; i<ALL_SHELTER_PET_NUM; ++i)
    {
        stringstream petname;
        if ( rand()%2==0 )
        {
            petname << "Dog" << i;
            Dog adog(petname.str(), i);
            petshelter.Enqueue(&adog);
        } 
        else
        {
            petname << "Cat" << i;
            Cat acat(petname.str(), i);
            petshelter.Enqueue(&acat);
        }
    }

    for (int i=0; i<ALL_SHELTER_PET_NUM; ++i)
    {
        Animal* apet = nullptr;
        switch ( rand()%3 )
        {
        case 0:
            apet = petshelter.DequeAny();
        	break;
        case 1:
            apet = petshelter.DequeDog();
            break;
        case 2:
            apet = petshelter.DequeCat();
            break;
        default:
            break;
        }
        if (apet != nullptr)
        {
            cout << "Name: " << apet->name() << " ID: " << apet->id() << endl;
            delete apet; // @@
        }
        else
        {
            cout << " That specific class of pet OOS! " << endl;
        }
    }

    return 0;
}