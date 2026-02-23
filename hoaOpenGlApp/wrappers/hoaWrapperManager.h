#pragma once
#include "hoaWrapper.h"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>

class hoaWrapperManager {
public:
    template<typename T, typename WrapperType>
    void registerWrapper(int type) {
        static_assert(std::is_base_of<hoaWrapper, WrapperType>::value,
            "WrapperType must inherit from hoaWrapper");

        static_assert(std::is_base_of<T, WrapperType>::value ||
            std::is_base_of<WrapperType, T>::value,
            "T and WrapperType must be related by inheritance");

        auto ptr = std::make_unique<WrapperType>();
        _wrappers[type][std::type_index(typeid(T))] = std::move(ptr);
    }

    template<typename T>
    T* getWrapper(int type) {
        auto typeIt = _wrappers.find(type);
        if (typeIt == _wrappers.end()) {
            return nullptr;
        }

        auto wrapperIt = typeIt->second.find(std::type_index(typeid(T)));
        if (wrapperIt == typeIt->second.end()) {
            return nullptr;
        }

        return wrapperIt->second;
    }

private:
    std::unordered_map<int, std::unordered_map<std::type_index, std::unique_ptr<hoaWrapper>>> _wrappers;
};
