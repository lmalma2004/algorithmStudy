#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
map<long long, long long> parent;

long long find(long long room) {
    if (parent[room] == 0)
        return room;
    return parent[room] = find(parent[room]);
}
void union_(long long room1, long long room2) {
    room1 = find(room1);
    room2 = find(room2);
    if (room1 == room2)
        return;
    parent[room1] = room2;
}

long long pickRoom(long long room) {
    long long retRoom;
    long long preRoom = room - 1;
    long long nextRoom = room + 1;
    //방이 비어있는경우
    if (parent[room] == 0) {
        retRoom = room;
        union_(room, nextRoom);
    }
    else {
        retRoom = find(room);
        nextRoom = retRoom + 1;
        union_(retRoom, nextRoom);
    }
    return retRoom;
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for (int i = 0; i < room_number.size(); i++) {
        long long room = room_number[i];
        room = pickRoom(room);
        answer.push_back(room);
    }
    return answer;
}

int main() {
    vector<long long> rn = { 1,2,3,4,1 };
    solution(5, rn);
    return 0;
}
