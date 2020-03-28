#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

const long long MAX_ROOMS = 1000000000000;
const long long MAX_N = 200000;

vector<long long> slow_solution(long long k, vector<long long> room_number) {
    map<long long, bool> roomIsFull;

    vector<long long> result;
    for (long long request : room_number) {
        for (long long i = request; i <= k; i++) {
            if (!roomIsFull[i]) {
                roomIsFull[i] = true;
                result.push_back(i);
                break;
            }
        }
    }

#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

const long long MAX_ROOMS = 1000000000000;
const long long MAX_N = 200000;

vector<long long> slow_solution(long long k, vector<long long> room_number) {
    map<long long, bool> roomIsFull;

    vector<long long> result;
    for (long long request : room_number) {
        for (long long i = request; i <= k; i++) {
            if (!roomIsFull[i]) {
                roomIsFull[i] = true;
                result.push_back(i);
                break;
            }
        }
    }

    return result;
}


struct Space {
    Space* parent;
    long long left;
    long long right;
};

Space spaces[MAX_N];
int nSpaces;
map<long long, Space*> spaceMap;

void init() {
    nSpaces = 0;
    spaceMap.clear();
}

Space* newSpace(long long room) {
    Space* newSpace = &spaces[nSpaces++];
    *newSpace = { NULL, room, room };
    return newSpace;
}

Space* findRoot(Space* space) {
    if (!space->parent) {
        return space;
    }
    Space* root = findRoot(space->parent);
    space->parent = root;
    return root;
}

Space* getSpace(long long room) {
    Space* space = spaceMap[room];
    return space;
}

long long getRight(Space* space) {
    Space* root = findRoot(space);
    return root->right;
}

void mergeSpaces(Space* spaceA, Space* spaceB) {
    Space* rootA = findRoot(spaceA);
    Space* rootB = findRoot(spaceB);
    if (rootA == rootB) {
        return;
    }
    rootA->left = min(rootA->left, rootB->left);
    rootA->right = max(rootA->right, rootB->right);
    rootB->parent = rootA;
    spaceB->parent = rootA;
}

long long getRoomNumber(long long request) {
    long long allocatedRoomNumber = request;

    Space* curSpace = getSpace(request);
    bool roomIsEmpty = !curSpace;
    if (!roomIsEmpty) {
        allocatedRoomNumber = getRight(curSpace) + 1;
    }

    curSpace = newSpace(allocatedRoomNumber);
    Space* prevSpace = getSpace(allocatedRoomNumber - 1);
    Space* nextSpace = getSpace(allocatedRoomNumber + 1);
    if (prevSpace) {
        mergeSpaces(prevSpace, curSpace);
    }
    if (nextSpace) {
        mergeSpaces(nextSpace, curSpace);
    }

    Space* root = findRoot(curSpace);
    spaceMap[allocatedRoomNumber] = root;

    return allocatedRoomNumber;
}

vector<long long> fast_solution(long long k, vector<long long> room_number) {
    init();

    vector<long long> result;

    for (long long request : room_number) {
        long long allocatedRoomNumber = getRoomNumber(request);
        result.push_back(allocatedRoomNumber);
    }

    return result;
}

vector<long long> solution(long long k, vector<long long> room_number) {
    //return slow_solution(k, room_number);
    return fast_solution(k, room_number);
}
