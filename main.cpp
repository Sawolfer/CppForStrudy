#include <iostream>
#include <vector>
void swapRef(int &a, int &b){
    int t = a;
    a = b;
    b =  t;
}
void swapPointer(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
int main() {
        int seconds;

        std::cin>>seconds;

        int hours, minutes;

        hours = seconds / 3600;
        seconds = seconds % 3600;
        minutes = seconds / 60;
        seconds = seconds % 60;

        std::cout << "first task " << hours << ":" << minutes << ":" << seconds << std::endl;
        int a =3;
        int b = 5;
        swapRef(a, b);
        std::cout << "task 2.1 " << a << " " << b<< std::endl;
        swapPointer(&a, &b);
        std::cout << "task 2.2 " << a << " " << b<< std::endl;

        int count;
        std::cin >> count;
        int arr[count];

        for (int i =0; i<count; i++){
            std::cin >> arr[i];
        }

        std::vector<int> v1;

        for (int i=0; i<count; i++){
            bool t = true;
            for (int j=0; j<v1.size(); j++){
                if (arr[i] == v1[j]){
                    t = false;
                }
            }
            if (t){
                v1.push_back(arr[i]);
            }
        }

        for(auto item : v1){
            std::cout << item << " ";
        }

        return 0;
    }


