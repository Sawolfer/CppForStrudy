#include <iostream>
#include <string>

using namespace std;
// method that will alculate sum from ith to jth elements
int calculateSum(int *arr, int i, int j)
{
    int *ptr = arr;
    int sum = 0;
    for (int a = i; a <= j; a++)
    {
        sum += *(ptr + a);
    }
    return (sum);
}
// method that will be change ith variable to j
void setItem(int *arr, int i, int a)
{
    int *ptr = arr;
    ptr += i;
    *ptr = a;
}
// the main function
int main()
{
    // input all variables
    int n, m;
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        arr[i] = tmp;
    }
    // loop in which we ivoke method sum or set
    for (int i = 0; i < m; i++)
    {
        string skip, op, a, b;
        cin >> op;
        cin >> a >> b;
        int intA = stoi(a);
        int intB = stoi(b);
        if (op == "sum")
        {
            cout << calculateSum(arr, intA, intB) << "\n";
        }
        if (op == "set")
        {
            setItem(arr, intA, intB);
        }
    }
    // output
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}
