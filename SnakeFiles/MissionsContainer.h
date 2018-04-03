#ifndef _Missions_Container_H_
#define _Missions_Container_H_

#include "Mission.h"
#include <vector>
#include <fstream>
#include <fstream>


class MissionsContainer
{
	vector<Mission> container{};
	MissionsIndx currentMissionIndx;
	Mission currentMission;

	void FillMeWithFileData();


public:
	void pushMission(Mission mish) { container.push_back(mish); }

	int getContainerSize()const { return container.size(); }

	Mission getRandomizeMissionsFromContainer() {
		currentMissionIndx = (MissionsIndx)(rand() % container.size());
		currentMission = container[int(currentMissionIndx)];
		currentMission.randomizeMyMish();
		return currentMission;
	}
	MissionsContainer() {
		FillMeWithFileData();
	}
};
#endif