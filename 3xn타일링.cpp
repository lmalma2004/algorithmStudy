#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    if(n == 2)
        return 3;
    if(n % 2 == 1)
        return 0;
    
    long memo[5000];
    long add = 0;
    memo[0] = 1;
    memo[2] = 3;
    for(int i=4; i<=n; i+=2){
        add += memo[i-4] * 2; //특수케이스, add가 왜 memo[i - 4] * 2 인지..
        memo[i] = (memo[i - 2] * 3 + add) % 1000000007;
    }
    return memo[n] % 1000000007;
}

