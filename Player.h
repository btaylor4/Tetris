#ifndef Player_h
#define Player_h

#include <fstream>
#include <iomanip>
#include <string>

class Player {
private:
	int score;
	string name;
	string scoreNames[5];
	int highScores[5];
public:
	Player();
	int getScore();
	void increaseScore(int amount);
	void displayScores();
	void addScore();
	void setName(string name);
	void exportFile();
	void importFile();

};

// Constructor for the player class. Gets in the "scores.txt" file
// and assigns the player names to a string array and the scores
// to an integer array.
Player::Player() {
	score = 0;
	name = "Player 1";

	for (int i = 0; i < 5; i++) {
		scoreNames[i] = "";
	}

	for (int i = 0; i < 5; i++) {
		highScores[i] = 0;
	}
}

// Imports the score file
void Player::importFile() {
	int i = 0;
	int j = 0;
	string dummy;

	ifstream inputFile;
	inputFile.open("scores.txt");

	// Import the file from low to high
	if (inputFile) {
		inputFile >> scoreNames[i];
		i++;
		while (!inputFile.eof()) {
			inputFile >> highScores[j];
			j++;

			if (i == 5) {
				break;
			}

			inputFile >> scoreNames[i];
			i++;
		}
	}

	inputFile.close();
}

// Returns the score
int Player::getScore() {
	return score;
}

// Increase the score by the given amount
void Player::increaseScore(int amount) {
	this->score += amount;
}

// Display the scores to the screen
void Player::displayScores() {
	cout << endl;
	int j = 1;

	// Print the score names, then the scores
	for (int i = 0; i < 5; i++) {
		cout << j << ".) " << left << setw(10) << scoreNames[i] << " " << setw(15) << highScores[i] << endl;
		j++;
	}

	cout << endl;
}

// Set the name of the player
void Player::setName(string name) {
	this->name = name;
}

// Add a score when the game ends
void Player::addScore() {
	int n = 0;

	// Check if theres a place for the high score
	while (n < 5 && highScores[n] > this->score) {
		
		n++;
	}

	// If n < 5, then theres a place to insert the score
	if (n < 5)
	{
		// Move all scores down and insert the new score
		for (int i = 4; i > n; i--) {
			highScores[i] = highScores[i - 1];
		}

		// Insert the high score in the new place
		highScores[n] = this->score;
	}

	// Do the exact same process for the names as the high score
	if (n < 5) {
		for (int i = 4; i > n; i--) {
			scoreNames[i] = scoreNames[i - 1];
		}

		scoreNames[n] = this->name;
	}
	
}

// Export the file in order, low to high
void Player::exportFile() {
	ofstream outputFile;

	outputFile.open("scores.txt");

	for (int i = 0; i < 5; i++) {
		outputFile << scoreNames[i];
		outputFile << " ";
		outputFile << highScores[i];
		outputFile << endl;
	}

	outputFile.close();
}
#endif

