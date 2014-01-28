//
//  Boat.cpp
//  PaddleboatQuest
//
//  Created by Ken Kopecky II on 1/27/14.
//
//

#include "Boat.h"
#include "Util.h"
#include "PaddleApp.h"
#include "RacePath.h"

#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/Material>

using namespace osg;

Boat::Boat()
{
	mT = 0;
	mTV = 0.1;
	MatrixTransform* modelTransform = new MatrixTransform();
	mPat->addChild(modelTransform);
	
	//load a boat model
	MatrixTransform* n = Util::loadModel("jetski.3DS", 1.0/12 / 4, -90);
	
	if(n)
	{
//		Util::setTint(n, Vec4(1, 0, 0, 1));
		//the texture doesn't apply automatically for some reason, so let's do it manually
		Image* image = osgDB::readImageFile(Util::findDataFile("jetski.jpg"));
		Texture2D* tex = new Texture2D(image);
		n->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex);
	}
	
	modelTransform->addChild(n);
}

bool Boat::update(float dt)
{
	__FUNCTION_HEADER__
	//get new position and velocity values from the path
	mT += mTV * dt;
	updatePosition();
	return true;

}

void Boat::updatePosition()
{
	RacePath* rp = PaddleApp::instance().getPath();
	Vec3 pos;
	Vec3 vel;
	rp->getPosAndVelAtTValue(mT, mTV, pos, vel);
	
	setPos(pos);
	setForward(vel);		//velocity-align

}


