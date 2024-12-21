#include<iostream>
template<typename T, typename K>
K max(T a, T b){
    return a>b;
}

template<typename T, int size>
T maxOfArray(T arr[]){
    T maxi=arr[0];
    for(int i=0;i<size;i++)
       maxi = std::max(maxi,arr[i]);
       return maxi;
}

template<typename T>
class stack{
    public:
    T arr[7];
   stack(T inputArr[]) {
        for (int i = 0; i < 7; ++i) {
            arr[i] = inputArr[i];  // Manually copying elements
        }
    }
    T* getter(){
        return arr;
    }
};
int main(){
    bool a = max<int,bool>(4,5);
    std::cout<<a<<std::endl;
    char arr[] = {'a','b','c','d','e','f','g','h'};
    int arr1[]= {1,2,3,5,9,6,77,8,22,4,7};
    std::cout<<maxOfArray<char,8> (arr)<<std::endl;
    std::cout<<maxOfArray<int,10> (arr1)<<std::endl;
    // stack<int> s({1,2,7,8,5,98,9});  this is wrong, can't decay into pointer.
     int stackArr[7] = {1, 2, 7, 8, 5, 98, 9};  // Use an array
    stack<int> s(stackArr);  // Pass the array to the constructor
    std::cout<<s.getter()[0]<<std::endl;
    stack<int> *p = &s;
    std::cout<<p->getter()[5];
    return 0;
}
