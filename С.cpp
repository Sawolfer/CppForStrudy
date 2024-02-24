#include <iostream>
#include <string>
#include "vector"

using namespace std;

// abstract class DataStructure
template <typename K>
class DataStructure
{
protected:
    virtual void insert(K x) = 0;
    virtual void remove() = 0;
    virtual bool search(K x) = 0;
};
// abstract class SequentialDataStructure that inherits DataStructures
template <typename K>
class SequentialDataStructure : protected DataStructure<K>
{
protected:
    virtual void pushBack(K x) = 0;
    virtual void pushFront(K x) = 0;
    virtual void popBack() = 0;
    virtual void popFront() = 0;
};
// abstract class DynamicDataStructure that inherits DataStructure
template <typename K>
class DynamicDataStructure : protected DataStructure<K>
{
protected:
    virtual void resize(int new_size) = 0;
    virtual void clear() = 0;
};
// class List that inherits both SequentialDataStructure and  DynamicDataStructure
class List : protected SequentialDataStructure<int>, protected DynamicDataStructure<int>
{
    // main storege of data
    vector<int> arr;

public:
    // default constructor;
    List() {}
    // method that checks if List is empty
    bool isEmpty()
    {
        if (arr.size() == 0)
        {
            return true;
        }
        return false;
    }
    // method that append new value to the end of List
    void insert(int a) override
    {
        arr.push_back(a);
    }
    // method that remove the last element of List
    void remove() override
    {
        if (!isEmpty())
        {
            arr.pop_back();
        }
    }
    // method that return if List consist value a
    bool search(int a) override
    {
        for (int item : arr)
        {
            if (item == a)
            {
                return true;
            }
        }
        return false;
    }
    // method that append element et the end of List
    void pushBack(int a) override
    {
        arr.push_back(a);
    }
    // method that append element at the front of array
    void pushFront(int a) override
    {
        arr.push_back(a);
        for (int i = arr.size(); i > 0; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[0] = a;
    }
    // method that delete the last element from List
    void popBack() override
    {
        if (!isEmpty())
        {
            arr.pop_back();
        }
    }
    // method that delete the first element from List
    void popFront() override
    {
        if (!isEmpty())
        {
            for (int i = 0; i < arr.size() - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            arr.pop_back();
        }
    }
    // method that change size of List
    void resize(int new_size) override
    {
        if (new_size >= arr.size())
        {
            for (int i = 0; i < arr.size() - new_size; i++)
            {
                arr.push_back(0);
            }
        }
        else
        {
            for (int i = 0; i < (new_size - arr.size()); i++)
            {
                arr.pop_back();
            }
        }
    }
    // method that delete all elements of List
    void clear() override
    {
        for (int i = 0; i <= arr.size(); i++)
        {
            arr.pop_back();
        }
    }

public:
    // method that output all elements of List
    void diplay()
    {
        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
    }
};
// the main function 
int main()
{
    List list;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        // input all necessary data
        string op;
        int num;
        cin >> op;
        // invoke different methods dependencing of the operation
        if (op == "search")
        {
            cin >> num;
            if (list.search(num))
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
        else if (op == "insert")
        {
            cin >> num;
            list.insert(num);
        }
        else if (op == "remove")
        {
            list.remove();
        }
        else if (op == "pushBack")
        {
            cin >> num;
            list.pushBack(num);
        }
        else if (op == "pushFront")
        {
            cin >> num;
            list.pushFront(num);
        }
        else if (op == "popBack")
        {
            list.popBack();
        }
        else if (op == "popFront")
        {
            list.popFront();
        }
        else if (op == "resize")
        {
            cin >> num;
            list.resize(num);
        }
        else if (op == "clear")
        {
            list.clear();
        }
    }
    // output all elemts of List
    list.diplay();
    return 0;
}
