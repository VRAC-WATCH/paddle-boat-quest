//
//  RacePath.h
//  PaddleboatQuest
//
//  Created by Ken Kopecky II on 1/27/14.
//
//

#ifndef __PaddleboatQuest__RacePath__
#define __PaddleboatQuest__RacePath__

#include <osg/MatrixTransform>
#include <iostream>


//this class holds the basic path for the race course
//give it a T value and delta T/second (percentage along path, not clock time), and it'll give you a position
//and velocity vector

//for now, the path will probs just be a circle
//eventually we might use a bezier curve or something neat like that


class RacePath
{
public:
	
	RacePath();
	//get a position along the racetrack
	//t is portion of the path (0-1), and tv is the rate of change of t per second
	void getPosAndVelAtTValue(float t, float tv, osg::Vec3& pos, osg::Vec3& vel);

};

#endif /* defined(__PaddleboatQuest__RacePath__) */
