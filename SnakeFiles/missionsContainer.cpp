#include "MissionsContainer.h"

void MissionsContainer::FillMeWithFileData()
{
	ifstream inFile("myMissionsFile.txt");

	int MinRange;
	int MaxRange;
	string str;

	int randomPart;
	
	string temp;
	if (inFile.is_open()) {
		getline(inFile, temp); //notes for user
		getline(inFile, temp); //notes for user
		getline(inFile, temp); //notes for user
		while (!inFile.eof()) {
			inFile >> str >> MinRange >> MaxRange >> randomPart;
			Mission mish(str, MinRange, MaxRange, randomPart);
			container.push_back(mish);
		}
		inFile.close();
	}
	else {
		system("cls");
		cout << "Cannot Open File! Try Again And Run..";
		getchar();
		exit(1);
	}
}
