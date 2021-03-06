/*
 *  PaddleApp.h
 *  Hybrid OSG Template
 *
 *  Created by Kenneth Kopecky on 8/15/09.
 *  Copyright 2009 Orange Element Studios. All rights reserved.
 *
 */

#ifndef PaddleAppCUZKENLOVESYOU
#define PaddleAppCUZKENLOVESYOU
#include <osg/Group>
#include <osg/Geode>
#include <osg/LightSource>
#include <osg/MatrixTransform>

class RacePath;
class Boat;

class PaddleApp
{
public:
	enum ButtonState {OFF, ON, TOGGLE_OFF, TOGGLE_ON};		//the four possible states of your standard button
	static PaddleApp& instance()	{static PaddleApp a;  return a;}				//singleton instance
	void init();
	void setHeadMatrix(osg::Matrixf m);
	void setWandMatrix(osg::Matrixf m);
	osg::Matrixf getHeadMatrix()		{return mHeadMatrix;}
	osg::Matrixf getWandMatrix()		{return mWandMatrix;}
	void update(float dt);										//timestep update
	osg::Group* getRoot() {return mRoot.get();}			//get our root scene node
	osg::Group* getModelGroup()	{return mModelGroup.get();}
	void buttonInput(unsigned int button, bool pressed);

	void setIsMaster(bool m)	{mIsMaster = m;}
	bool isMaster()				{return mIsMaster;}
	void drawStatus();									//draw run-time info, like frame rate, on the head node
	void handleArguments(int* argc, char** argv);		//process command line arguments
	void shutdown();									//clean up before exiting
	
	RacePath* getPath()					{return mPath;}
protected:

	//put very little in the constructor so we don't risk a recurisive call
	PaddleApp()
	{
		mIsMaster = true; mTargetTime = 0; mTotalTime = 0; mTimeStep = 0.01;
	}
	
	//update our calculated frame rate
	void updateFrameRate(float dt);

	RacePath* mPath;											//the path along which we're racin!
	osg::ref_ptr<osg::Group> mRoot;								//root of our scenegraph
	osg::ref_ptr<osg::MatrixTransform> mNavigation;				//navigation matrix
	osg::ref_ptr<osg::Group> mModelGroup;						//this is where we put things into the app!
	osg::Matrixf mWandMatrix;
	osg::Matrixf mHeadMatrix;
	osg::ref_ptr<osg::LightSource> mLightSource;
	std::vector<Boat*>				mBoats;
	void deToggleButtons();									//remove toggle status from our buttons after each frame to prevent events from happening repeatedly
	static const int NUMBUTTONS = 6;
	
	int mButtons[NUMBUTTONS];

	osg::MatrixTransform* mWandXForm;

	//timekeeping
	float mTargetTime;
	float mTotalTime;
	float mTimeStep;
	float mAvgFrameRate;

	//needed for clusteredness
	bool mIsMaster;										//is this the master node of the cluster?
};



#endif

