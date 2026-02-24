#ifndef REGISTRYFACTORY_H
#define REGISTRYFACTORY_H
#pragma once
#include <map>
#include <functional>
#include <memory>

template<class ID, class BaseClass, class ... Args>
class RegistryFactory
{
public:
    using Creator = std::function<std::unique_ptr<BaseClass>(Args...)>;

    void registerFactory(const ID &id, Creator creator) {
        factories[id] = std::move(creator);
    }

    std::unique_ptr<BaseClass> create(const ID& id, Args... args) const
    {
        auto it = factories.find(id);
        if (it != factories.end())
            return it->second(std::forward<Args>(args)...);

        return nullptr;
    }
protected:
    std::map<ID, Creator> factories;

};

#endif // REGISTRYFACTORY_H
