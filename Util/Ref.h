#pragma once

namespace JEngine {

    template <typename T>
    class Ref
    {
    private:
        int* _ref;
        T* _data;

    public:
        Ref();
        Ref(T* data);
        Ref(const Ref<T>& other);
        ~Ref();

        Ref<T>& operator=(const Ref<T>& other);
        T* operator->();
        T& operator*();
        T* get();

        bool operator==(const Ref<T>& other);
        bool operator!=(const Ref<T>& other);
    };

    template <typename T>
    Ref<T>::Ref()
        : _ref(new int(0)), _data(nullptr)
    {}

    template <typename T>
    Ref<T>::Ref(T* data)
        : _ref(new int(1)), _data(data)
    {}

    template <typename T>
    Ref<T>::Ref(const Ref<T>& other)
    {
        if (*this != other) {
            _data = other._data;
            _ref = other._ref;
            *_ref += 1;
        }
    }

    template <typename T>
    Ref<T>::~Ref()
    {
        *_ref -= 1;
        if (*_ref <= 0 && _data)
            delete _data;
    }

    template <typename T>
    Ref<T>& Ref<T>::operator=(const Ref<T>& other)
    {
        if (*this != other) {
            _data = other._data;
            _ref = other._ref;
            *_ref += 1;
        }

        return *this;
    }

    template <typename T>
    T* Ref<T>::operator->()
    {
        return _data;
    }

    template <typename T>
    T& Ref<T>::operator*()
    {
        if (_data)
            return *_data;
        throw;
    }

    template <typename T>
    T* Ref<T>::get()
    {
        if (_data)
            return _data;
        return nullptr;
    }

    template <typename T>
    bool Ref<T>::operator==(const Ref<T>& other)
    {
        return (_data == other._data);
    }

    template<typename T>
    bool Ref<T>::operator!=(const Ref<T>& other)
    {
        return (_data != other._data);
    }

    template <typename T, typename... Args>
    static Ref<T> make_ref(Args&&... args)
    {
        T* t = new T(args...);
        return Ref<T>(t);
    }

    template <typename T>
    static Ref<T> make_ref(const T& copy)
    {
        T* t = new T(copy);
        return Ref<T>(t);
    }

}