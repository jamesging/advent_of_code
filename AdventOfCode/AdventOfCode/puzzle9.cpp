#include "puzzle9.hpp"

#include <list>

int puzzle9::numPlayers;
int puzzle9::highestMarble;
int puzzle9::scoringValue;

std::pair<int, long> puzzle9::playMarbleGame() {
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

void puzzle9::runPuzzle(const int _numPlayers, const int _highestMarble, const int _scoringValue) {
    numPlayers = _numPlayers;
	highestMarble = _highestMarble;
	scoringValue = _scoringValue;
    puzzle9 puzzle;
    
    std::pair<int, long> winningPlayer = puzzle.playMarbleGame();
    highestMarble *= 100;
	std::pair<int, long> partTwoWinner = puzzle.playMarbleGame();

	printf("Player %d won the game with %ld points\n", winningPlayer.first, winningPlayer.second);
	printf("Player %d won part two with %ld points\n", partTwoWinner.first, partTwoWinner.second);
}
