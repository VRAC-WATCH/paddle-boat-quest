//
//  Boat.h
//  PaddleboatQuest
//
//  Created by Ken Kopecky II on 1/27/14.
//
//

#ifndef __PaddleboatQuest__Boat__
#define __PaddleboatQuest__Boat__

#include "GameObject.h"

//class that holds our boat

class Boat : public GameObject
{
public:

	Boat();
	
	virtual bool update(float dt);
	
	void setT(float t)						//set the boat's progress around the track
	{mT = t; updatePosition();}

	float getT()		{return mT;}		//what's our progress around the track?
	
	void setTV(float v)	{mTV = v;}			//set the rate of change for our T-value
	float getTV()		{return mTV;}		//get the rate of change for our T-value

protected:
	void updatePosition();					//called when our T-value changes
	
	float		mT;							//our T-value for traveling around the track.  need a better name!
	float		mTV;						//T-velocity
	
};


#endif /* defined(__PaddleboatQuest__Boat__) */
