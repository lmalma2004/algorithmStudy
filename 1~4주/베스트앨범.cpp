#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Song {
public:
	int id;
	int playTime;
public:
	Song(int i, int p) {
		id = i;
		playTime = p;
	}
};
class compareLess {
public:
	bool operator()(const Song& s1, const Song& s2) {
		if (s1.playTime == s2.playTime)
			return s1.id > s2.id;
		return s1.playTime < s2.playTime;
	}
};
class Genre {
public:
	int playTime;
	priority_queue<Song, vector<Song>, compareLess> songs;
public:
	Genre() {
		playTime = 0;
	}
};
bool compareGenre(const Genre& g1, const Genre& g2) {
	return g1.playTime > g2.playTime;
}
vector<Genre> mgenres;
map<string, int> genersMap;

vector<int> solution(vector<string> genres, vector<int> plays) {
	for (int i = 0; i < genres.size(); i++) {
		Song currSong(i, plays[i]);
        //처음 보는 장르
		if (genersMap.find(genres[i]) == genersMap.end()) {
			int currSize = mgenres.size();
			Genre newGenre;
			newGenre.songs.push(currSong);
            newGenre.playTime += plays[i];
			mgenres.push_back(newGenre);
			genersMap[genres[i]] = currSize;
		}
		else {
			int genreIdx = genersMap[genres[i]];
			mgenres[genreIdx].songs.push(currSong);
			mgenres[genreIdx].playTime += plays[i];
		}
	}
	sort(mgenres.begin(), mgenres.end(), compareGenre);
	vector<int> ret;
	for (int i = 0; i < mgenres.size(); i++) {
		for (int j = 0; j < 2; j++) {
			if (!mgenres[i].songs.empty()) {
				ret.push_back(mgenres[i].songs.top().id);
				mgenres[i].songs.pop();
			}
		}
	}
	return ret;
}

int main() {
	vector<string> d;
	d.push_back("classic");
	d.push_back("pop");
	d.push_back("classic");
	d.push_back("classic");
	d.push_back("pop");
	vector<int> p = { 500, 600, 150, 800, 2500 };

	solution(d, p);
	return 0;
}
