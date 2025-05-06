#include<iostream>
#include<omp.h>
#include<climits>

using namespace std;

void min(int arr[],int n){
    int min_val = INT_MAX;
    #pragma omp parallel for reduction(min:min_val)
    for(int i=0;i<n;i++){
        if(arr[i]<min_val){
            min_val = arr[i];
        }
    }
    cout<<"Minimum value: "<<min_val<<endl;
}
void max(int arr[],int n){
    int max_val = INT_MIN;
    #pragma omp parallel for reduction(max:max_val)
    for(int i=0;i<n;i++){
        if(arr[i]>max_val){
            max_val = arr[i];
        }
    }
    cout<<"Maximum value: "<<max_val<<endl;
}

void sum(int arr[],int n){
    int sum_val = 0;
    #pragma omp parallel for reduction(+:sum_val)
    for(int i=0;i<n;i++){
        sum_val += arr[i];
    }
    cout<<"Sum: "<<sum_val<<endl;
}

void avg(int arr[],int n){
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++){
        sum += arr[i];
    }
    double avg = (double)sum/n;
    cout<<"Average: "<<avg<<endl;
}

int main(){
    int n;
    cout<<"Enter the number of elements: ";
    cin>>n;
    int *arr = new int[n];
    cout<<"Enter the elements: ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    min(arr,n);
    max(arr,n);
    sum(arr,n);
    avg(arr,n);
    
    delete[] arr;
    return 0;
}