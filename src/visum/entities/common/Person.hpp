/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#include <visum/entities/Entity.hpp>

namespace visum {

class Person
    : public Entity
{

  public:

    explicit Person(const std::string& id);

    Person() = delete;

    virtual ~Person() = default;

    Person(const Person&) = delete;

    Person& operator=(const Person&) = delete;

    Person(Person&&) = delete;

    Person& operator=(Person&&) = delete;

  private:

    template<class Archive> void serialize(Archive& archive)
    {
        archive(cereal::make_nvp("Entity",
                                 cereal::base_class<Entity>(this)));
    }

    // cppcheck-suppress unusedFunction
    template<class Archive> static void load_and_construct(Archive& ar,
                                                           cereal::construct<Person>& construct)
    {
        std::string id;
        ar(id);
        construct(id);
    }

    friend class cereal::access;

};

}
