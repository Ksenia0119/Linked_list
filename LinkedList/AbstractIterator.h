#pragma once
//@author Maltseva K.V.
template<class T>
// абстрактный класс итератор
class Iterator {
public:
    //получение значени€ элемента,не измен€€ его
    virtual T& operator*() const = 0;
    //переход к следующему элементу коллекции
    virtual Iterator<T>& operator++() = 0;
    //сравнивает текущий итератор с другим и возвращает true,
    //если они указывают на один и тот же элемент
    virtual bool operator==(const Iterator<T>& other) const = 0;
    //сравнивает текущий итератор с другим и возвращает true,
   //если они Ќ≈ указывают на один и тот же элемент
    virtual bool operator!=(const Iterator<T>& other) const = 0;
    virtual ~Iterator() {}
};
//абстрактный класс итератируемого
template<class T>
class Iterable {
public:
    //начало коллекции
    virtual Iterator<T> begin() const = 0;
    //конец коллекции
    virtual Iterator<T> end() const = 0;
    virtual ~Iterable() {}
};
