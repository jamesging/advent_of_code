#include <stdio.h>
#include <list>
#include <map>

std::pair<int, long> playMarbleGame(const int numPlayers,
	const int highestMarble, const int scoringValue) {
	std::map<int, long> players;
	for (int i = 0;i < numPlayers;i++) {
		players[i] = 0;
	}

	std::list<int> marbles;
	marbles.push_back(0);
	marbles.push_back(1);
	
	auto currentPos = marbles.begin();
	currentPos++;
	int currentMarble = 2;
	while (currentMarble <= highestMarble) {
		int playerId = currentMarble%numPlayers;
		if (currentMarble%scoringValue == 0) {
			auto bonusIt = currentPos;
			int shiftAmount = 9;
			while (shiftAmount) {
				bonusIt--;
				shiftAmount--;
				if (bonusIt == marbles.begin()) {
					bonusIt = marbles.end();
				}
			}
			int bonusScore = *bonusIt;
			players[playerId] = players[playerId] + currentMarble + bonusScore;
			currentPos = marbles.erase(bonusIt);
		} else {
			currentPos = marbles.insert(currentPos, currentMarble);
		}
		currentPos++;
		if(currentPos == marbles.end()) {
			currentPos = marbles.begin();
		}
		currentPos++;
		currentMarble++;
	}
	long topScore = 0;
	int winningPlayer = 0;
	for (auto &player : players) {
		if (player.second > topScore) {
			topScore = player.second;
			winningPlayer = player.first;
		}
	}
	return std::make_pair(winningPlayer, topScore);
}

int main(int argc, char **argv) {
	if (argc != 4) {
                printf("Incorrect usage. Try: puzzle9 [number of players] [highest marble] \
			[scoring value]\n");
                return 1;
        }
	int numPlayers = atoi(argv[1]);
	int highestMarble = atoi(argv[2]);
	int scoringValue = atoi(argv[3]);
	std::pair<int, long> winningPlayer = playMarbleGame(numPlayers, highestMarble, scoringValue);
	std::pair<int, long> partTwoWinner = playMarbleGame(numPlayers, highestMarble*100, scoringValue);

	printf("Player %d won the game with %ld points\n", winningPlayer.first, winningPlayer.second);
	printf("Player %d won part two with %ld points\n", partTwoWinner.first, partTwoWinner.second);
	return 0;
}
