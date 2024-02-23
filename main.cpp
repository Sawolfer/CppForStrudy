#include <iostream>
#include "vector"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

template<typename K, typename V>
class GenericType{
protected:
    K key;
    V value;
public:
    GenericType(K key, V value){
        this -> key = key;
        this -> value = value;
    }
    V getValue(){
        return value;
    };
    K getKey(){
        return key;
    }
};

template<typename K, typename V>
class GenericFunc{
public:
    virtual void push(K, V);
    virtual V pop(K);
    virtual V peek(K);

};


template<typename K, typename V>
class GenericStack : public GenericFunc<K, V>{

    vector<GenericType<K, V> > stack;

public:
    void push(K, V) override{
//        GenericType<>
        stack.push_back();
    }
    V pop(K) override{

    }
    V peek(K) override{

    }

};