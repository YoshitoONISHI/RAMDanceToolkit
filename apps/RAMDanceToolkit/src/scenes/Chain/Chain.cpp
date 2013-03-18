//
//  Chain.cpp
//  Chain
//
//  Created by Onishi Yoshito on 2/19/13.
//
//

#include "Chain.h"

#pragma mark -
//--------------------------------------------------------------
static void pushAll()
{
    ofPushView();
    
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    GLint matrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glMatrixMode(GL_COLOR);
    glPushMatrix();
    
    glMatrixMode(matrixMode);
    
    ofPushStyle();
}

//--------------------------------------------------------------
static void popAll()
{
    ofPopStyle();
    
    GLint matrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
    
    glMatrixMode(GL_COLOR);
    glPopMatrix();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glMatrixMode(matrixMode);
    
    glPopAttrib();
    
    ofPopView();
}

#pragma mark -
//--------------------------------------------------------------
void Chain::setupControlPanel()
{
	
#ifdef RAM_GUI_SYSTEM_OFXUI
	
    const float w = 300.0f;
    const float dim = 16.0f;
    
	ofxUICanvas* panel = ramGetGUI().getCurrentUIContext();
	
    panel->addSlider("GRAVITY X", -3.0f, 3.0f, &mGravity.x, w, dim);
    panel->addSlider("GRAVITY Y", -3.0f, 3.0f, &mGravity.y, w, dim);
    panel->addSlider("GRAVITY Z", -3.0f, 3.0f, &mGravity.z, w, dim);
    
    panel->addSpacer(w, 1.0f);
    
    panel->addLabel("NUM EDGES", OFX_UI_FONT_SMALL);
    panel->addNumberDialer("NUM EDGES", 2, 100, &mNumEdges, 0);
    panel->addLabel("ATTACHING EDGES", OFX_UI_FONT_SMALL);
    panel->addNumberDialer("ATTACHING EDGE", 0, 100, &mAttachingEdge, 0);
    panel->addSlider("EDGE LENGTH", 1.0, 100, &mEdgeLength, w, dim);
    panel->addSlider("THICKNESS", 1.0, 100, &mThickness, w, dim);
    
    panel->addSpacer(w, 1.0f);
    panel->addLabel("Press [o] to add chain", OFX_UI_FONT_LARGE);
    panel->addSpacer(w, 1.0f);
    panel->addButton("REMOVE ALL", false, dim, dim);
	
    ofAddListener(panel->newGUIEvent, this, &Chain::onValueChanged);
#endif
}

#pragma mark -
//--------------------------------------------------------------
void Chain::setup()
{
    mChainBtDynamics.setup();
    
    mGravity.set(0.0f, 0.0f, 0.0f);
    mChainBtDynamics.setGravity(mGravity.x, mGravity.y, mGravity.z);

    mChains.clear();
    
    mNumEdges = 3;
    mAttachingEdge = 0;
    mEdgeLength = 50;
    mThickness = 5;
	
	ofAddListener(ofEvents().keyPressed, this, &Chain::onKeyPressed);
}

//--------------------------------------------------------------
void Chain::update()
{
    pushAll();
    mChainBtDynamics.update();
    popAll();
}

//--------------------------------------------------------------
void Chain::draw()
{
    pushAll();
    ramBeginCamera();
    ofEnableAlphaBlending();
    mChainBtDynamics.draw();
    ramEndCamera();
    popAll();
}


#pragma mark -
//--------------------------------------------------------------
void Chain::drawActor(const ramActor &actor)
{
	ofSetColor(ramColor::RED_DEEP);
    ramDrawBasicActor(actor);
    
    for (int i=0; i<mChains.size(); i++) {
        if (mChains.at(i))
            mChains.at(i)->update(actor);
    }
}

#pragma mark -
//--------------------------------------------------------------
void Chain::onValueChanged(ofxUIEventArgs& e)
{
    const string name = e.widget->getName();
    
    if (name=="GRAVITY X" || name=="GRAVITY Y" || name=="GRAVITY Z") {
        mChainBtDynamics.setGravity(mGravity.x, mGravity.y, mGravity.z);
    }
    else if (name=="ADD") {
        ofxUIButton *b = static_cast<ofxUIButton *>(e.widget);
        if (b->getValue()) return;
        
        if (!ramActorManager::instance().getLastSelectedNode()) {
            ofLogError("Chain") << "We must select a node at first!";
            return;
        }
        const string actorName = ramActorManager::instance().getLastSelectedNodeIdentifer().name;
        int nodeId =ramActorManager::instance().getLastSelectedNodeIdentifer().index;
        AttachableChain *chain;
        chain = new AttachableChain();
        chain->setup(&mChainBtDynamics);
        const ofVec3f pos = ramActorManager::instance().getLastSelectedNode()->getGlobalPosition();
        /// not good
        //chain->spawnChain(btVector3(pos.x, pos.y, pos.z), mNumEdges, mEdgeLength, mThickness);
        /// good
        chain->spawnChain(btVector3(0.0f, 100.0f, 0.0f), mNumEdges, mEdgeLength, mThickness);
        chain->attach(actorName, nodeId, mAttachingEdge);

        mChains.push_back(chain);
    }
    else if (name=="REMOVE ALL") {
        ofxUIButton *b = static_cast<ofxUIButton *>(e.widget);
        if (b->getValue()) return;
        
        for (int i=0; i<mChains.size(); i++) {
            delete mChains.at(i);
            mChains.at(i) = NULL;
        }
        mChains.clear();
        mChainBtDynamics.removeAllChains();
    }
}

void Chain::onKeyPressed(ofKeyEventArgs &e)
{
	if (e.key != 'o') return;
	
	if (!ramActorManager::instance().getLastSelectedNode()) {
		ofLogError("Chain") << "We must select a node at first!";
		return;
	}
	const string actorName = ramActorManager::instance().getLastSelectedNodeIdentifer().name;
	int nodeId =ramActorManager::instance().getLastSelectedNodeIdentifer().index;
	AttachableChain *chain;
	chain = new AttachableChain();
	chain->setup(&mChainBtDynamics);
	const ofVec3f pos = ramActorManager::instance().getLastSelectedNode()->getGlobalPosition();
	/// not good
	//chain->spawnChain(btVector3(pos.x, pos.y, pos.z), mNumEdges, mEdgeLength, mThickness);
	/// good
	chain->spawnChain(btVector3(0.0f, 100.0f, 0.0f), mNumEdges, mEdgeLength, mThickness);
	chain->attach(actorName, nodeId, mAttachingEdge);
	
	mChains.push_back(chain);
}

