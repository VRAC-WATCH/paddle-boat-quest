//
//  StepTwo.cpp
//  PaddleboatQuest
//
//  Created by Ken Kopecky II on 1/28/14.
//
//

#include "StepTwo.h"
#include <math.h>
#include "Util.h"

StepTwo::StepTwo()
{
	mNumPlayers = 2;
	
}

int StepTwo::getStateForPos(float pos)
{
	while(pos < 0) pos += 1.0;		//account for )pos < 0)
	return ((int)(pos*20))%2;				//just return 1 or 0, based on where we are around the path
}

void StepTwo::setInputValue(int player, float value)
{
	if(player < 0 || player >= MAX_PLAYERS) //guard against bad player numbers
	{
		//report bad player numbers so we can quickly fix them
		Util::logError("Input data sent for an invalid player (%i)", player);
		return;
	}

	mPlayers[player].current.input = value;
}

const StepTwo::PlayerData& StepTwo::getPlayerData(int player)
{
	if(player < 0 || player >= MAX_PLAYERS) //guard against bad player numbers
	{
		//if we're asked for an invalid player number, report it so we can fix it quickly.
		Util::logError("Player data requested for an invalid player (%i)", player);
		player = 0;
	}
	return mPlayers[player];
	
}

void StepTwo::update(float dt)
{
	//__FUNCTION_HEADER__ is for built-in, low-overhead time profiling
	//profile results are printed to the console when the app exits
	__FUNCTION_HEADER__

	//update position and speed of each player
	for(int i = 0; i < mNumPlayers; i++)
	{
		//right now, just compare current input to desired input
		int desired = getStateForPos(mPlayers[i].current.pos);
		float current = mPlayers[i].current.input;
	
		float speed = (1.0 - fabs((float)desired-current)) / 30.f;
		

		mPlayers[i].current.speed = speed;
		mPlayers[i].current.pos += speed * dt;
		mPlayers[i].current.desiredInput = desired;
		mPlayers[i].current.timeStamp += dt;
		//finally, update the player's history
		mPlayers[i].updateHistory();
	}

}

void StepTwo::PlayerData::updateHistory()
{
	historyIndex = (historyIndex+1)%HISTORY_SIZE;
	history[historyIndex] = current;
}

