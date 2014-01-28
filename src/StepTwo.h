//
//  StepTwo.h
//  PaddleboatQuest
//
//  Created by Ken Kopecky II on 1/28/14.
//
//

#ifndef __PaddleboatQuest__StepTwo__
#define __PaddleboatQuest__StepTwo__

#include <iostream>


//I can't think of a decent name for this class, so please change it later.
//StepTwo takes the state of the paddles as input and outputs either the position or
//speed that the boats should have, considering what state the inputs SHOULD be in
//in my head, it's red/green, but it doesn't have to be.
//either way, as a basis, we'll start with zero is green, 1 is red
//It also maintains a history of the last 512 or so frames of data per player, so we can
//figure out things like derivatives or record data or smooth things or just visualize stuff

//right now this will just put out placeholder values for going around in a circle with different colors per slice
class StepTwo
{
public:

	StepTwo();
	
	//here's probably the most important stuff
	int getStateForPos(float pos);						//what is the color state for a given section of the path?
	void setInputValue(int player, float value);		//called from the Image Processing step, tells what input we're getting from a particular player/zone
	//this one is listed cuz it's important, but can't be declared till after the PlayerData struct
	//const PlayerData& getPlayerData(int player);		//get everythign we need to know about a player	void setInputValue(int player, float value);		//pass input from the image processing to here.  which player/zone. Value should be between 0-1

	void update(float dt);								//timestep update
	
	
	//this just holds basic information about the player, as well as keeps track of
	//the recent values
	class PlayerData
	{
		public:
			int num;		//player number
			PlayerData()	{historyIndex = 0;  num = 0;}
			//a rolling history that we can use for sampling derivatives or for smoothing
			struct HistoryData
			{
				HistoryData(){timeStamp = 0; pos = 0; speed = 0; desiredInput = 0; input = 0;}
				float timeStamp;
				float pos;					//position (0-1) on the course
				float speed;				//time derivative of position
				float desiredInput;			//what we SHOULD be inputting to accelerate
				float input;				//what we actualy are inputting
			};
			
			HistoryData current;						//current data
			static const int HISTORY_SIZE = 512;		//store this many points of history data
			int historyIndex;							//where are we in our history array?
			HistoryData history[HISTORY_SIZE];			//the array where we store the looping history array

			//call this every frame to put our current data into our history
			void updateHistory();
	};
	
	const PlayerData& getPlayerData(int player);		//get everythign we need to know about a player
	
protected:

	static const int MAX_PLAYERS = 8;				//we'll probably just have two, but let's leave room
	int mNumPlayers;								//actual number of players
	PlayerData mPlayers[MAX_PLAYERS];
	

};
#endif /* defined(__PaddleboatQuest__StepTwo__) */
