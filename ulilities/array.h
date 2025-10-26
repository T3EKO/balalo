#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

template <class T>
class Array {
private:
    std::vector<T> vec;

public:
    Array() { }
    Array(std::initializer_list<T> initList) : vec{initList} { }

    size_t size() {
        return vec.size();
    }

    bool contains(T el) {
        for(size_t i = 0;i < size();i++) {
            if((*this)[i] == el) return true;
        }
        return false;
    }

    void resize(size_t newSize) {
        vec.resize(newSize);
    }

    T& operator[](size_t index) {
        return vec[index];
    }

    void append(T el) {
        vec.push_back(el);
    }

    void insert(T el, size_t index) {
        typename std::vector<T>::iterator iter = vec.begin();
        std::advance(iter, index);
        vec.insert(iter, el);
    }

    T removeAt(size_t index) {
        T value = (*this)[index];
        typename std::vector<T>::iterator iter = vec.begin();
        std::advance(iter, index);
        vec.erase(iter);
        return value;
    }

    Array<T> map(std::function<T(T, size_t, Array&)> callback) {
        Array<T> newArray{};
        newArray.resize(size());
        for(size_t index = 0;index < size();index++) {
            newArray[index] = callback(this[index], index, *this);
        }
        return newArray;
    }

    Array<T> filter(std::function<bool(T, size_t, Array&)> predicate) {
        Array<T> newArray{};
        for(size_t index = 0;index < size();index++) {
            if(!predicate((*this)[index], index, *this)) continue;
            newArray.append((*this)[index]);
        }
        return newArray;
    }

    Array<T> filterByMask(size_t bitMask) {
        return this->filter([=](T v, size_t i, Array<T>& _) -> bool {
            return (bitMask >> i) & 0b1;
        });
    }

    void sort(std::function<bool(T, T)> comp) {
        std::sort(vec.begin(), vec.end(), comp);
    }

    void stable_sort(std::function<bool(T, T)> comp) {
        std::stable_sort(vec.begin(), vec.end(), comp);
    }

    std::string stringify(std::function<std::string(T)> stringFactory) {
        std::string str{};
        for(int i = 0;i < size();i++) {
            str += stringFactory((*this)[i]);
            if(i < size() - 1) str += ", ";
        }
        return str;
    }

    static std::string stringify(Array<T> array, std::function<std::string(T)> stringFactory) {
        return array.stringify(stringFactory);
    }
};