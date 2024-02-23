#include <iostream>
#include <string>

using namespace std;

int calculateSum(int *arr, int i, int j){
    int *ptr = arr;
    int sum =0;
    for (int a = i; a <= j; a++){
        sum += *(ptr + a);
    }
    return (sum);
}

void setItem(int *arr, int i, int a){
    int *ptr = arr;
    ptr += i;
    *ptr = a;

}

int main() {

    int n, m;
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n; i++){
        int tmp;
        cin >> tmp;
        arr[i] = tmp;
    }

    for (int i = 0; i < m; i++){
        string skip, op, a, b;
        cin >> op;
        cin >> a >> b;
        int intA = stoi(a);
        int intB = stoi(b);
        if(op == "sum"){
            cout << calculateSum(arr, intA, intB) << "\n";
        }
        if (op == "set") {
            setItem(arr, intA, intB);
        }
    }

    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }

    return 0;
}
