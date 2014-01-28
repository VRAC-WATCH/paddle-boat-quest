//
//  RacePath.cpp
//  PaddleboatQuest
//
//  Created by Ken Kopecky II on 1/27/14.
//
//

#include "RacePath.h"

using namespace osg;

RacePath::RacePath()
{
	//nothing here until we devise a real path
}

void RacePath::getPosAndVelAtTValue(float t, float tv, osg::Vec3 &pos, osg::Vec3 &vel)
{
	//for now we're just going around a circle
	float r = 5;
	float theta = t * 3.14159 * 2.0;
	pos = Vec3(r * cosf(theta), 0, r * -sinf(theta));
	vel = Vec3(6.28 * r * tv * -sinf(theta), 0, -r * 6.28 * tv * cosf(theta));
}