#include <iostream>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enGameWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
    short RoundNumber;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enGameWinner Winner;
    string RoundWinner;
};

struct stGameInfo {
    short GameRounds = 0;
    short PlayerWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enGameWinner GameWinner;
};

string ChoiceName(enGameChoice GameChoice) {
    string Choice[3] = { "Stone", "Paper", "Scissors" };
    return Choice[GameChoice - 1];
}

string WinnerName(enGameWinner GameWinner) {
    string Winner[3] = { "Player", "Computer", "Draw" };
    return Winner[GameWinner - 1];
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void ColorSystem(enGameWinner GameWinner) {
    if (GameWinner == enGameWinner::Computer) {
        system("color 4F");
        cout << "\a";
    }
    else if (GameWinner == enGameWinner::Player) {
        system("color 2F");
    }
    else {
        system("color 6F");
    }
}

int ReadNumberOfRounds() {
    int NumberOfRounds;
    do {
        cout << "How many rounds (1:10) ? ";
        cin >> NumberOfRounds;
    } while (NumberOfRounds < 1 || NumberOfRounds > 10);
    return NumberOfRounds;
}

int RandomNumber(int From, int To) {
    int Random = From + rand() % (To - From + 1);
    return Random;
}

enGameChoice ComputerGameChoice() {
    return (enGameChoice) RandomNumber(1, 3);
}

enGameChoice PlayerGameChoice() {
    short PlayerNumberChoice = 1;

    do {
        cout << "Your choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> PlayerNumberChoice;
    } while (PlayerNumberChoice < 1 || PlayerNumberChoice > 3);

    return (enGameChoice)PlayerNumberChoice;
}

enGameWinner WhoWonTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice) {
        return enGameWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice) {
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
            return enGameWinner::Player;
        break;
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            return enGameWinner::Player;
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            return enGameWinner::Player;
        break;
    }

    return enGameWinner::Computer;
}

void PrintRoundResult(stRoundInfo RoundInfo) {
    cout << "\n---------------- Round [" << RoundInfo.RoundNumber << "] ----------------\n";
    cout << "Player choice  : " << ChoiceName(RoundInfo.PlayerChoice)   << "\n";
    cout << "Computer choice: " << ChoiceName(RoundInfo.ComputerChoice) << "\n";
    cout << "Round winner   : " << WinnerName(RoundInfo.Winner)         << "\n";
    cout << "-------------------------------------------\n";
}

void PrintGameOverScreen() {
    cout << "\n\t\t\t-----------------------------------------------------------\n\n";
    cout << "\t\t\t                  +++ Game Over +++\n\n";
    cout << "\t\t\t-----------------------------------------------------------\n\n";
}

enGameWinner WhoWonTheGame(int ComputerWonTimes, int PlayerWonTimes) {
    if (ComputerWonTimes == PlayerWonTimes) {
        return enGameWinner::Draw;
    }
    else if (ComputerWonTimes < PlayerWonTimes) {
        return enGameWinner::Player;
    }
    else {
        return enGameWinner::Computer;
    }
}

stGameInfo FillGameResults(int ComputerWonTimes, int PlayerWonTimes, int DrawTimes, int NumberOfRounds) {
    stGameInfo GameInfo;
    GameInfo.ComputerWonTimes = ComputerWonTimes;
    GameInfo.PlayerWonTimes = PlayerWonTimes;
    GameInfo.DrawTimes = DrawTimes;
    GameInfo.GameRounds = NumberOfRounds;
    GameInfo.GameWinner = WhoWonTheGame(ComputerWonTimes, PlayerWonTimes);
    return GameInfo;
}

void PrintGameResult(stGameInfo GameInfo) {
    cout << "\t\t\t---------------------- [Game Result] ----------------------\n";
    cout << "\t\t\tGame rounds       : " << GameInfo.GameRounds              <<"\n";
    cout << "\t\t\tPlayer won times  : " << GameInfo.PlayerWonTimes          << "\n";
    cout << "\t\t\tComputer won times: " << GameInfo.ComputerWonTimes        << "\n";
    cout << "\t\t\tDraw times        : " << GameInfo.DrawTimes               << "\n";
    cout << "\t\t\tFinal winner      : " << WinnerName(GameInfo.GameWinner)  << "\n";
    cout << "\t\t\t-----------------------------------------------------------\n";
}

stGameInfo PlayGame(int NumberOfRounds) {
    stRoundInfo RoundInfo;
   
    short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
    for (int Round = 1; Round <= NumberOfRounds; Round++) {
        cout << "Round [" << Round << "] begins:\n";
        RoundInfo.RoundNumber = Round;
        RoundInfo.PlayerChoice = PlayerGameChoice();
        RoundInfo.ComputerChoice = ComputerGameChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        ColorSystem(RoundInfo.Winner);

        if (RoundInfo.Winner == enGameWinner::Player)
            PlayerWonTimes++;
        else if (RoundInfo.Winner == enGameWinner::Computer)
            ComputerWonTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
    }

    return FillGameResults(ComputerWonTimes, PlayerWonTimes, DrawTimes, NumberOfRounds);
}

void StartGame() {
    char PlayAgain = 'Y';

    do {
        ResetScreen();
        stGameInfo GameInfo = PlayGame(ReadNumberOfRounds());
        PrintGameOverScreen();
        PrintGameResult(GameInfo);

        cout << "\nDo you want to play again? (Y/N)? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand(time(0));
    StartGame();
    return 0;
}