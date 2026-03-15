#include <iostream>
#include <string>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName= "";

};

struct stGameResults
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName= "";

};


int RandomNumber(int From, int To)
{
	//Function generater a random number

	int RandomNum = rand() % (To - From + 1) + From;

	return RandomNum;
}

enGameChoice ReadPlayerChoice()
{
	short Choice = 0;
	do
	{

		cout << "Your choice : [1]Stone, [2]Paper, [3]Scissors ?? ";
		cin >> Choice;



	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;

}

enGameChoice GetComputerChoice()
{
	return (enGameChoice) RandomNumber(1, 3);
}

enWinner HowWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}


	return enWinner::Player;

}

string WinnerName(enWinner Winner)
{
	string arrWinners[3] = { "Player","Computer","NoWinner" };
	return arrWinners[Winner - 1];
}

string ChoiceName(enGameChoice choice)
{
	string arrChoices[3] = { "Stone","Paper","Scissors" };
	return arrChoices[choice - 1];
}

void SetWinnerScreenColors(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F");// turn screen to Green
		break;
	case enWinner::Computer:
		system("color 4F");// turn screen to Red and start small sound 
		cout << "\a";
		break;
	default:
		system("color 6F");// turn screen to Yellow
		break;
	}


}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n\n---------------- Round [" <<RoundInfo.RoundNumber << "] --------------------------\n\n";
	cout << "Player 1 Choice : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner    : [" << RoundInfo.WinnerName << "]" << endl;
	cout << "\n\n------------------------------------------------------\n\n";

	SetWinnerScreenColors(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
	{
		return enWinner::Player;
	}
	else if (PlayerWinTimes < ComputerWinTimes)
	{
		return enWinner::Computer;
	}
	else if (PlayerWinTimes == ComputerWinTimes)
	{
		enWinner::Draw;
	}
}

stGameResults FillGameResults(int GameRoounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRoounds;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;

}

stGameResults PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begines : \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = HowWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);


		if (RoundInfo.Winner == enWinner::Player)
			PlayerWinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);

	}


	return FillGameResults(HowManyRound, PlayerWinTimes, ComputerWinTimes, DrawTimes);

}

short ReadHowManyRounds()
{
	short GameRound = 1;

	do
	{

		cout << "How many round 1 to 10 ??\n";
		cin >> GameRound;

	} while (GameRound < 1 || GameRound > 10);


	return GameRound;

}

string Tabs(short NumberofTabs)
{
	string t = "";

	for (int i = 1; i < NumberofTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}

	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "--------------------------------------------------------------------\n\n";
	cout << Tabs(2) << "               +++Game Over+++  \n\n";
    cout << Tabs(2) << "--------------------------------------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResults GameResuts)
{
	cout << Tabs(2) <<"----------------------[Game Results]--------------------------------\n";
	cout << Tabs(2) <<"Game Rounds : " << GameResuts.GameRounds << endl;
	cout << Tabs(2) <<"Player 1 won times : " << GameResuts.PlayerWinTimes  << endl;
	cout << Tabs(2) <<"Computer won times : " << GameResuts.ComputerWinTimes  << endl;
	cout << Tabs(2) <<"Draw times : " << GameResuts.DrawTimes  << endl;
	cout << Tabs(2) << "Final winner : " << GameResuts.WinnerName << endl;
	cout << Tabs(2) <<"--------------------------------------------------------------------";

	SetWinnerScreenColors(GameResuts.GameWinner);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);
		cout << "\n" << Tabs(3) << "Do you want play again ?? Y/N ??";
		cin >> PlayAgain;
	
	
	} while (PlayAgain == 'Y' || PlayAgain == 'y');


}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();


	return 0;
}
