#include <iostream>
using namespace std;

class Team {
private:
    string name;
    int matches, wins, draws, losses;
    int goalsScored, goalsConceded;
    int points;

public:
    static int totalTeams;

    void input() {
        cout << "Enter team name: ";
        cin >> name;

        cout << "Enter matches played: ";
        cin >> matches;

        cout << "Enter wins: ";
        cin >> wins;

        cout << "Enter draws: ";
        cin >> draws;

        cout << "Enter losses: ";
        cin >> losses;

        cout << "Enter goals scored: ";
        cin >> goalsScored;

        cout << "Enter goals conceded: ";
        cin >> goalsConceded;

        if (matches < 0) matches = 0;
        if (wins < 0) wins = 0;
        if (draws < 0) draws = 0;
        if (losses < 0) losses = 0;

        calculatePoints();
        totalTeams++;
    }

    void calculatePoints() {
        points = (wins * 3) + (draws * 1);
    }

    int goalDifference() {
        return goalsScored - goalsConceded;
    }

    int getPoints() {
        return points;
    }

    int getWins() {
        return wins;
    }

    int getGoalsScored() {
        return goalsScored;
    }

    string getName() {
        return name;
    }

    void display() {
        cout << "\nTeam: " << name;
        cout << "\nPoints: " << points;
        cout << "\nGoal Difference: " << goalDifference();
        cout << "\nWins: " << wins;
        cout << "\nGoals Scored: " << goalsScored << endl;
    }
};

int Team::totalTeams = 0;

bool isBetter(Team a, Team b) {
    if (a.getPoints() != b.getPoints())
        return a.getPoints() > b.getPoints();

    if (a.goalDifference() != b.goalDifference())
        return a.goalDifference() > b.goalDifference();

    if (a.getWins() != b.getWins())
        return a.getWins() > b.getWins();

    return a.getGoalsScored() > b.getGoalsScored();
}

int main() {
    int groups, teamsPerGroup;

    cout << "Enter number of groups: ";
    cin >> groups;

    cout << "Enter number of teams per group: ";
    cin >> teamsPerGroup;

    Team groupWinners[20];
    Team teams[20];

    for (int g = 0; g < groups; g++) {
        cout << "\nGroup " << g + 1 << endl;

        for (int i = 0; i < teamsPerGroup; i++) {
            cout << "\nTeam " << i + 1 << endl;
            teams[i].input();
        }

        int winner = 0;

        for (int i = 1; i < teamsPerGroup; i++) {
            if (isBetter(teams[i], teams[winner])) {
                winner = i;
            }
        }

        groupWinners[g] = teams[winner];

        cout << "\nWinner of Group " << g + 1 << ": ";
        cout << groupWinners[g].getName() << endl;
    }

    int champion = 0;

    for (int i = 1; i < groups; i++) {
        if (isBetter(groupWinners[i], groupWinners[champion])) {
            champion = i;
        }
    }

    cout << "\nOverall Champion: " << groupWinners[champion].getName();
    cout << "\nTotal Teams Participated: " << Team::totalTeams << endl;

    return 0;
}
