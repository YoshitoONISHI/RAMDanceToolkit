#include "testApp.h"


/*!
 Scenes
 */
#include "BasicActor.h"
BasicActor basicActor;

#include "Line.h"
Line drawLines;

#include "BigBox.h"
BigBox bigbox;

#include "Future.h"
Future future;

#include "Donuts.h"
Donuts donuts;

#include "Stamp.h"
Stamp stamp;

#include "Expansion.h"
Expansion expansion;

#include "Particles.h"
Particles particles;

#include "Abacus.h"
Abacus abacus;

#include "SoundCube.h"
SoundCube soundcube;

#include "UpsideDown.h"
UpsideDown upsideDown;

#include "Kepler.h"
Kepler kepler;

#include "Graph3D.h"
Graph3D graph3D;




#pragma mark - oF methods
//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(ramColor::WHITE);
	
	/// ram setup
	// ------------------
	ramInit();
	oscReceiver.setup(10000);
	
	/// scenes setup
	// ------------------
	vector<ramBaseScene*> scenes;
	scenes.push_back( basicActor.getPtr() );
	scenes.push_back( drawLines.getPtr() );
	scenes.push_back( bigbox.getPtr() );
	scenes.push_back( future.getPtr() );
	scenes.push_back( donuts.getPtr() );
	scenes.push_back( stamp.getPtr() );
	scenes.push_back( expansion.getPtr() );
	scenes.push_back( particles.getPtr() );
	scenes.push_back( abacus.getPtr() );
	scenes.push_back( soundcube.getPtr() );
    scenes.push_back( upsideDown.getPtr() );
    scenes.push_back( kepler.getPtr() );
	scenes.push_back( graph3D.getPtr() );
	
	sceneManager.setup(scenes);
}

//--------------------------------------------------------------
void testApp::update()
{	
	/// Entities update
	// ------------------
	oscReceiver.update();
	
	
	/// Scenes update
	// ------------------
	sceneManager.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
	sceneManager.draw();
}

#pragma mark - ram methods

//--------------------------------------------------------------
void testApp::drawActor(ramActor &actor)
{
}

//--------------------------------------------------------------
void testApp::drawRigid(ramRigidBody &rigid)
{
}

#pragma mark - oF Events
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
	
}
