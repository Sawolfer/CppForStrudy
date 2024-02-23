#include <iostream>
#include <string>
#include "vector"

using namespace std;

template<typename K>
class DataStructure{
protected:
    virtual void insert(K x) = 0;
    virtual void remove() = 0;
    virtual bool search(K x) = 0;
};

template<typename K>
class SequentialDataStructure : protected DataStructure<K>{
protected:
    virtual void pushBack(K x) = 0;
    virtual void pushFront(K x) = 0;
    virtual void popBack() = 0;
    virtual void popFront() = 0;
};

template<typename K>
class DynamicDataStructure : protected DataStructure<K>{
protected:
    virtual void resize(int new_size) = 0;
    virtual void clear() = 0;
};

class List : protected SequentialDataStructure<int>, protected DynamicDataStructure<int>{

    vector<int> arr;

public:
    List(){}
    bool isEmpty(){
        if (arr.size() == 0){
            return true;
        }
        return false;
    }
    void insert(int a) override{
        arr.push_back(a);
    }
    void remove() override {
        if (!isEmpty()){
            arr.pop_back();
        }
    }
    bool search(int a) override {
        for (int item : arr){
            if (item == a){
                return true;
            }
        }
        return false;
    }
    void pushBack(int a) override{
        arr.push_back(a);
    }
    void pushFront(int a) override{
        arr.push_back(a);
        for (int i = arr.size(); i > 0; i--){
            arr[i] = arr[i-1];
        }
        arr[0] = a;
    }
    void popBack() override{
        if (!isEmpty()){
            arr.pop_back();
        }
    }
    void popFront() override{
        if (!isEmpty()){
            for (int i = 0; i < arr.size()-1; i++){
                arr[i] = arr[i+1];
            }
            arr.pop_back();
        }

    }
    void resize(int new_size) override{
        if (new_size >= arr.size()){
            for (int i = 0; i < arr.size() - new_size; i++){
                arr.push_back(0);
            }
        } else {
            for (int i = 0; i < (new_size - arr.size()); i++){
                arr.pop_back();
            }
        }

    }
    void clear() override{
        for (int i = 0; i <= arr.size(); i++){
            arr.pop_back();
        }
    }
public:
    void diplay(){
        for (int i =0; i< arr.size(); i++){
            cout << arr[i] << " ";
        }
    }

};




int main(){
    List list;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++){
        string op;
        int num;
        cin >> op;
        if (op == "search"){
            cin >> num;
            if (list.search(num)){
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else if (op == "insert"){
            cin >> num;
            list.insert(num);
        } else if (op == "remove") {
            list.remove();
        } else if (op == "pushBack"){
            cin >> num;
            list.pushBack(num);
        } else if (op == "pushFront"){
            cin >> num;
            list.pushFront(num);
        } else if (op == "popBack"){
            list.popBack();
        } else if (op == "popFront"){
            list.popFront();
        } else if (op == "resize"){
            cin >> num;
            list.resize(num);
        } else if (op == "clear") {
            list.clear();
        }
    }
    list.diplay();
    return 0;
}

