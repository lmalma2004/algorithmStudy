#include <iostream>
#include <cstdio>
using namespace std;
int A[5000000];

int Partition(int list[], int left, int right)
{
    int pivot = list[left];
    int i = left + 1, j = right;

    while (i <= j) {
        while (list[i] <= pivot && i <= right) i++;
        while (list[j] >= pivot && j >= (left + 1)) j--;
        if (i <= j) std::swap(list[i], list[j]);
    }
    std::swap(list[left], list[j]);
    return j;
}

//pivot이 위치하는 index == index번째 값
//결국 pivot이 위치하는 index를 찾는것
int quickSelect(int list[], int left, int right, int k)
{
    int nth = Partition(list, left, right);

    if (nth == k) return list[nth];
    else if (nth > k) quickSelect(list, left, nth - 1, k);
    else if (nth < k) quickSelect(list, nth + 1, right, k);
}

int main(void)
{
    int n, k; 
    cin >> n >> k;
    k--;

    for (int i = 0; i < n; i++) 
        scanf("%d", &A[i]);
    cout << quickSelect(A, 0, n - 1, k);
    return 0;
}

