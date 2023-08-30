#include "pch.h"
#include "ProceduralGenerationAlgorithms.h"


vector<Vec2> SimpleRandomWalk(Vec2 startPosition, int walkLength)
{
	vector<Vec2> path;
	path.push_back(startPosition);
	Vec2 prevPosition = startPosition;
	for (int i = 0; i < walkLength; ++i) {
		Vec2 newposition = prevPosition;
		vector<Vec2>::iterator iter = path.begin();
		int j = 0;
		while (true) {
			newposition = prevPosition + GetRandomCardinalDirection(i+j);
			auto it = std::find(path.begin(), path.end(), newposition);
			if (it == path.end()) {
				path.push_back(newposition);
				prevPosition = newposition;
				break;
			}
			else {
				j++;
			}
		}
		
		
	}

	return path;
}

Vec2 GetRandomCardinalDirection(int _time)
{
	vector<Vec2> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	srand(_time);
	int a = rand();
	return directions[rand() % 4];
}
