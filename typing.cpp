#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

// Load words from a file into a vector
vector<string> loadWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    if (file.is_open()) {
        string word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    }
    return words;
}

// Update the leaderboard
void updateLeaderboard(const string& username, int wpm, vector<pair<string, int>>& leaderboard) {
    leaderboard.push_back(make_pair(username, wpm));
    sort(leaderboard.begin(), leaderboard.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
}

// Show the leaderboard
void showLeaderboard(const vector<pair<string, int>>& leaderboard) {
    cout << "Leaderboard:" << endl;
    for (const auto& entry : leaderboard) {
        cout << entry.first << " - " << entry.second << " WPM" << endl;
    }
}

// Main typing test logic
void typingTest(const vector<string>& words) {
    cout << "Type the following words:" << endl;
    for (const string& word : words) {
        cout << word << " ";
    }
    cout << endl;

    string userTypedText;
    string correctText;
    int wordsTyped = 0;
    int incorrectWords = 0;
    auto startTime = chrono::high_resolution_clock::now();

    while (true) {
        string word;
        cin >> word;

        if (word == "Ctrl+Q") {
            cout << "You quit the game." << endl;
            return;
        }

        userTypedText += word + " ";
        correctText += words[wordsTyped] + " ";

        if (word == words[wordsTyped]) {
            wordsTyped++;
        } else {
            incorrectWords++;
        }

        if (wordsTyped == words.size()) {
            auto endTime = chrono::high_resolution_clock::now();
            double timeTaken = chrono::duration<double>(endTime - startTime).count();
            int wpm = static_cast<int>((wordsTyped - incorrectWords) / (timeTaken / 60));

            cout << "Words Typed: " << wordsTyped << endl;
            cout << "Time Taken: " << timeTaken << " seconds" << endl;
            cout << "Words Per Minute (WPM): " << wpm << endl;

            return;
        }
    }
}

int main() {
    srand(time(nullptr));
    string username;
    vector<pair<string, int>> leaderboard;
    vector<string> words = loadWordsFromFile("words.txt");

    cout << "Enter your username: ";
    cin >> username;

    while (true) {
        cout << "\nOptions:" << endl;
        cout << "1. Start typing test" << endl;
        cout << "2. Show leaderboard" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                typingTest(words);
                updateLeaderboard(username, leaderboard.back().second, leaderboard);
                break;
            case 2:
                showLeaderboard(leaderboard);
                break;
            case 3:
                cout << "Exiting the game." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
