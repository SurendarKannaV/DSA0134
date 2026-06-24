#include <iostream>
using namespace std;

class Election {
private:
    int votes[50][50];
    int regions, candidates;

public:
    static int totalVotes;

    void input() {
        cout << "Enter number of regions: ";
        cin >> regions;

        cout << "Enter number of candidates: ";
        cin >> candidates;

        for (int i = 0; i < regions; i++) {
            cout << "\nRegion " << i + 1 << endl;

            for (int j = 0; j < candidates; j++) {
                cout << "Enter votes for Candidate " << j + 1 << ": ";
                cin >> votes[i][j];

                if (votes[i][j] < 0) {
                    votes[i][j] = 0;
                }

                totalVotes += votes[i][j];
            }
        }
    }

    void regionWinner() {
        for (int i = 0; i < regions; i++) {
            int maxVotes = votes[i][0];
            bool tie = false;
            int winner = 0;

            for (int j = 1; j < candidates; j++) {
                if (votes[i][j] > maxVotes) {
                    maxVotes = votes[i][j];
                    winner = j;
                    tie = false;
                } else if (votes[i][j] == maxVotes) {
                    tie = true;
                }
            }

            cout << "\nRegion " << i + 1 << ": ";

            if (tie)
                cout << "Tie condition";
            else
                cout << "Winner is Candidate " << winner + 1;

            cout << " with " << maxVotes << " votes";
        }
    }

    void overallWinner() {
        int total[50] = {0};

        for (int j = 0; j < candidates; j++) {
            for (int i = 0; i < regions; i++) {
                total[j] += votes[i][j];
            }
        }

        int maxVotes = total[0];
        int winner = 0;
        bool tie = false;

        for (int j = 1; j < candidates; j++) {
            if (total[j] > maxVotes) {
                maxVotes = total[j];
                winner = j;
                tie = false;
            } else if (total[j] == maxVotes) {
                tie = true;
            }
        }

        cout << "\n\nOverall Result: ";

        if (tie)
            cout << "Overall tie condition";
        else
            cout << "Overall Winner is Candidate " << winner + 1;

        cout << "\nTotal Votes Polled: " << totalVotes << endl;
    }
};

int Election::totalVotes = 0;

int main() {
    Election e;

    e.input();
    e.regionWinner();
    e.overallWinner();

    return 0;
}
