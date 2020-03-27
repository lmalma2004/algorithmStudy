// 문제가 개편 되었습니다. 이로 인해 함수 구성이 변경되어, 과거의 코드는 동작하지 않을 수 있습니다.
// 새로운 함수 구성을 적용하려면 [코드 초기화] 버튼을 누르세요. 단, [코드 초기화] 버튼을 누르면 작성 중인 코드는 사라집니다.
#include <string>
#include <vector>
#include <algorithm>
#define MAX 1000000001
#include <iostream>
using namespace std;

// 문제가 개편 되었습니다. 이로 인해 함수 구성이 변경되어, 과거의 코드는 동작하지 않을 수 있습니다.
// 새로운 함수 구성을 적용하려면 [코드 초기화] 버튼을 누르세요. 단, [코드 초기화] 버튼을 누르면 작성 중인 코드는 사라집니다.
#include <string>
#include <vector>
#include <algorithm>
#define MAX 1000000001
#include <iostream>
using namespace std;

//length의 거리가 가능한지 물어본다.
//length이하의 거리의 바위면 지운다.
//지우는 바위수가 n을 초과하면 false다.
bool isPossible(int length, vector<int> rocks, int n){
    int removeCnt = 0;
    int currPos = 0; //출발 지점 = 0
    
    for(int i=0; i<rocks.size(); i++){
        //rocks[i]를 지우는 경우
        if(rocks[i] - currPos < length) 
            removeCnt++; 
        //rocks[i]를 안지우는 경우
        else
            currPos = rocks[i]; 
        
        if(removeCnt > n)
            return false;
    }
    return true;
}
int solution(int distance, vector<int> rocks, int n) {
    rocks.push_back(distance);
    sort(rocks.begin(), rocks.end());
    
    int lo = 0;
    int hi = MAX;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        if(isPossible(mid, rocks, n))
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return hi;
}
