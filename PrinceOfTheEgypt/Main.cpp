#include <iostream>
#include <format>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

int numberOfPeople = 100;
float bushelsOfWheat = 2800;
int numberOfAcres = 1000;
int roundNumber = 1;
int currentAcreCost;
int sownAcres = 0;
int bushesToEat;

int getRandomNum(int minBound, int maxBound) 
{
	srand(static_cast<unsigned int>(time(0)));
	int numberOfItterations = rand() % 10 + 1;
	int result = -1;
	for (int i = 0; i <= numberOfItterations; i++)
	{
		result = rand();
	}
	return (result % (maxBound - minBound)) + minBound;
}

void printReport(int peopleDied, int peopleArrived, bool wasPlague, int harvest,
			   int ammountFromAcre, int destroyedByRats)
{
	string report = "Мой повелитель, соизволь поведать тебе:\n";
	report += (roundNumber != 1) ? format("\t в году {} твоего высочайшего правления\n", roundNumber) : 
		                           format("\t это Ваш первый год высочайшего правления\n", roundNumber);
	if (roundNumber != 1) {
		report += (peopleDied > 0) ? format("\t {} человек умерли с голоду, и ", peopleDied) : "\t";
		report += (peopleArrived > 0) ? format("{} человек прибыли в наш великий город;\n", peopleArrived) : "";
		report += (wasPlague) ? "\t Чума уничтожила половину населения;\n" : "";
		report += format("\t Население города сейчас составляет {} человек;\n", numberOfPeople);
		report += format("\t Мы собрали {} бушелей пшеницы, по {} бушеля с акра;\n", harvest, ammountFromAcre);
	}
	report += (destroyedByRats == 0) ? "\t сейчас в амбаре 3103 бушеля пшеницы;\n" :
			  format("\t Крысы истребили {} бушелей пшеницы, сейчас в амбаре 3103 бушеля пшеницы;\n", destroyedByRats);
	report += format("\t Город сейчас занимает 220 акров;\n", numberOfAcres);
	report += format("\t 1 акр земли стоит сейчас {} бушель.\n", currentAcreCost);
	report += "Что пожелаешь, повелитель?\n";
	cout << report;
}

bool playRaund()
{
	if (roundNumber == 1)
	{
		currentAcreCost = getRandomNum(17, 26);
		printReport(0, 0, false, 0, 0, 0);
	}
	else {
		int ammountFromAcre = getRandomNum(1, 6);
		int harvest = ammountFromAcre * sownAcres;
		float destroyedByRats = (getRandomNum(0, 7) * (harvest + bushelsOfWheat)) / 100;
		bushelsOfWheat += harvest - destroyedByRats;
		int peopleDied = (bushesToEat - numberOfPeople * 20 > 0) ? 0 : ceil((bushesToEat - numberOfPeople * 20) / 20);
		float peopleArrived = ((peopleDied / 2 + (5 - ammountFromAcre) * bushelsOfWheat / 600 + 1) > 50) ? 50 : 0;
		bool wasPlague = getRandomNum(0, 100) < 15;
		printReport(peopleDied, peopleArrived, wasPlague, harvest, ammountFromAcre, destroyedByRats);
	}
}

bool getInput() {
	int a;
	int b;
	int c;
	cout << "Сколько акров земли повелеваешь купить? ";
	cin >> a;
	cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
	cin >> b;
	cout << "Сколько акров земли повелеваешь засеять? ";
	cin >> c;
	if (b + c * 0.5 + a * currentAcreCost < bushelsOfWheat || a < numberOfPeople * 10)
	{
		return false;
	}
	bushelsOfWheat -= b + c * 0.5 + a * currentAcreCost;
	numberOfAcres += a;
	bushesToEat = b;
	sownAcres = c;
	roundNumber += 1;
	return true;
}

void gameLoop()
{
	while (true) 
	{
		playRaund();
		while (!getInput())
		{
			cout <<
		}
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");
	gameLoop();
}