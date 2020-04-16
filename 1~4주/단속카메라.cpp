#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool compare(const vector<int>& r1, const vector<int>& r2){
    return r1[0] < r2[0];
}
int solution(vector<vector<int>> routes) {
    sort(routes.begin(), routes.end(), compare);
    int cameraCnt = 1;
    int cameraLoc = routes[0][1];
    for(int i=1; i<routes.size(); i++){
        int nextCarStart = routes[i][0];
        int nextCarEnd   = routes[i][1];
        if(cameraLoc < nextCarStart){
            cameraLoc = nextCarEnd;
            cameraCnt++;
        }
        else if(cameraLoc > nextCarEnd){
            cameraLoc = nextCarEnd;
        }
    }
    return cameraCnt;
}
