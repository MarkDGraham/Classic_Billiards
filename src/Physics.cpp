//
// Created by jtucker on 10/25/21.
//

#include "Physics.h"
#include <iostream>


Physics::Physics() {


    //create parameters
    //Tells bullet how to check for collisions between objects. This will also help eliminate object pairs that should not collide.
    btBroadphaseInterface *broadphase = new btDbvtBroadphase();
    //This is a collision algorithm. It can be used to register a callback that filters overlapping broadphase proxies (collision bounding box)
    btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();
    //Used in conjunction with collisionConfiguration for the collision algorithm. It will send events to the objects.
    btCollisionDispatcher *dispatcher = new btCollisionDispatcher(collisionConfiguration);
    //This causes the objects to interact properly, taking into account gravity, forces, collisions, and hinge constraints.
    btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver;

    //Create world
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    //Set Gravity
    dynamicsWorld->setGravity(btVector3(0, -9.81, 0.0));

    setAllBallsActive();

}
Physics::~Physics() {

}

void Physics::PoolSetup(btCollisionShape *table) {

    btScalar mass(1);
    btVector3 inertia(0, 0, 0);
    btDefaultMotionState *shapeMotionState = NULL;
    btRigidBody *RBptr = nullptr;


    //create cuestick
    //btCollisionShape *blockCS = new btBoxShape(btVector3(1, 1, 5));
    btCollisionShape *CylinderCS = new btCylinderShapeZ(btVector3(0.1, 0.1, 0.1));

    //create spheres
    btCollisionShape *cueCS = new btSphereShape(1);
    btCollisionShape *oneCS = new btSphereShape(1);
    btCollisionShape *twoCS = new btSphereShape(1);
    btCollisionShape *threeCS = new btSphereShape(1);
    btCollisionShape *fourCS = new btSphereShape(1);
    btCollisionShape *fiveCS = new btSphereShape(1);
    btCollisionShape *sixCS = new btSphereShape(1);
    btCollisionShape *sevenCS = new btSphereShape(1);
    btCollisionShape *eightCS = new btSphereShape(1);
    btCollisionShape *nineCS = new btSphereShape(1);
    btCollisionShape *tenCS = new btSphereShape(1);
    btCollisionShape *elevenCS = new btSphereShape(1);
    btCollisionShape *twelveCS = new btSphereShape(1);
    btCollisionShape *thirteenCS = new btSphereShape(1);
    btCollisionShape *fourteenCS = new btSphereShape(1);
    btCollisionShape *fifteenCS = new btSphereShape(1);


    //Setup and add rigidbody shapes to world
    //Sets initial positioning
    //cuestick
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 3, -10)));
    mass = btScalar(0);
    inertia = btVector3(2.0f, 2.0f, 2.0f);
    CylinderCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(mass, shapeMotionState, CylinderCS, inertia);
    cylinderRigidBodyCI.m_restitution = 0.1f;
    RBptr = new btRigidBody(cylinderRigidBodyCI);
    //Makes the RB kinematic
    RBptr->setCollisionFlags(RBptr->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);

    cueStickRB = RBptr;

    //table
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0, 0, 0)));
    //0 mass and intertia make it static
    mass = btScalar(0);
    inertia = btVector3(0, 0, 0);
    table->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(mass, shapeMotionState, table, inertia);
    tableRigidBodyCI.m_friction = 0.1f;
    tableRigidBodyCI.m_restitution = 0.7f;
    RBptr = new btRigidBody(tableRigidBodyCI);
    dynamicsWorld->addRigidBody(RBptr);
    tableRB = RBptr;

    //balls
    //cue
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1.0, -8)));
    mass = btScalar(0.2);
    inertia = btVector3(0, 0, 0);
    cueCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo cueRigidBodyCI(mass, shapeMotionState, cueCS, inertia);
    cueRigidBodyCI.m_restitution = 0.97f;
    cueRigidBodyCI.m_friction = 0.3f;
    cueRigidBodyCI.m_rollingFriction = 0.05f;
    cueRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(cueRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

    //one
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1.0, 5)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    oneCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo oneRigidBodyCI(mass, shapeMotionState, oneCS, inertia);
    oneRigidBodyCI.m_restitution = 0.97f;
    oneRigidBodyCI.m_friction = 0.3f;
    oneRigidBodyCI.m_rollingFriction = 0.05f;
    oneRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(oneRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

    //two
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, 1.0, 7)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    twoCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo twoRigidBodyCI(mass, shapeMotionState, twoCS, inertia);
    twoRigidBodyCI.m_restitution = 0.97f;
    twoRigidBodyCI.m_friction = 0.3f;
    twoRigidBodyCI.m_rollingFriction = 0.05f;
    twoRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(twoRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

    //three
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(2, 1.0, 9)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    threeCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo threeRigidBodyCI(mass, shapeMotionState, threeCS, inertia);
    threeRigidBodyCI.m_restitution = 0.97f;
    threeRigidBodyCI.m_friction = 0.3f;
    threeRigidBodyCI.m_rollingFriction = 0.05f;
    threeRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(threeRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //four
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(3, 1.0, 11)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    fourCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo fourRigidBodyCI(mass, shapeMotionState, fourCS, inertia);
    fourRigidBodyCI.m_restitution = 0.97f;
    fourRigidBodyCI.m_friction = 0.3f;
    fourRigidBodyCI.m_rollingFriction = 0.05f;
    fourRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(fourRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //five
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-4, 1.0, 13)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    fiveCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo fiveRigidBodyCI(mass, shapeMotionState, fiveCS, inertia);
    fiveRigidBodyCI.m_restitution = 0.97f;
    fiveRigidBodyCI.m_friction = 0.3f;
    fiveRigidBodyCI.m_rollingFriction = 0.05f;
    fiveRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(fiveRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //six
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(2, 1.0, 13)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    sixCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo sixRigidBodyCI(mass, shapeMotionState, sixCS, inertia);
    sixRigidBodyCI.m_restitution = 0.97f;
    sixRigidBodyCI.m_friction = 0.3f;
    sixRigidBodyCI.m_rollingFriction = 0.05f;
    sixRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(sixRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //seven
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-1, 1.0, 11)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    sevenCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo sevenRigidBodyCI(mass, shapeMotionState, sevenCS, inertia);
    sevenRigidBodyCI.m_restitution = 0.97f;
    sevenRigidBodyCI.m_friction = 0.3f;
    sevenRigidBodyCI.m_rollingFriction = 0.05f;
    sevenRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(sevenRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //eight
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1.0, 9)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    eightCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo eightRigidBodyCI(mass, shapeMotionState, eightCS, inertia);
    eightRigidBodyCI.m_restitution = 0.97f;
    eightRigidBodyCI.m_friction = 0.3f;
    eightRigidBodyCI.m_rollingFriction = 0.05f;
    eightRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(eightRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //nine
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-1, 1.0, 7)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    nineCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo nineRigidBodyCI(mass, shapeMotionState, nineCS, inertia);
    nineRigidBodyCI.m_restitution = 0.97f;
    nineRigidBodyCI.m_friction = 0.3f;
    nineRigidBodyCI.m_rollingFriction = 0.05f;
    nineRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(nineRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //ten
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-2, 1.0, 9)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    tenCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo tenRigidBodyCI(mass, shapeMotionState, tenCS, inertia);
    tenRigidBodyCI.m_restitution = 0.97f;
    tenRigidBodyCI.m_friction = 0.3f;
    tenRigidBodyCI.m_rollingFriction = 0.05f;
    tenRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(tenRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //eleven
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-3, 1.0, 11)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    elevenCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo elevenRigidBodyCI(mass, shapeMotionState, elevenCS, inertia);
    elevenRigidBodyCI.m_restitution = 0.97f;
    elevenRigidBodyCI.m_friction = 0.3f;
    elevenRigidBodyCI.m_rollingFriction = 0.05f;
    elevenRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(elevenRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //twelve
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(4, 1.0, 13)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    twelveCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo twelveRigidBodyCI(mass, shapeMotionState, twelveCS, inertia);
    twelveRigidBodyCI.m_restitution = 0.97f;
    twelveRigidBodyCI.m_friction = 0.3f;
    twelveRigidBodyCI.m_rollingFriction = 0.05f;
    twelveRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(twelveRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //thirteen
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-2, 1.0, 13)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    thirteenCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo thirteenRigidBodyCI(mass, shapeMotionState, thirteenCS, inertia);
    thirteenRigidBodyCI.m_restitution = 0.97f;
    thirteenRigidBodyCI.m_friction = 0.3f;
    thirteenRigidBodyCI.m_rollingFriction = 0.05f;
    thirteenRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(thirteenRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //fourteen
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, 1.0, 11)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    fourteenCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo fourteenRigidBodyCI(mass, shapeMotionState, fourteenCS, inertia);
    fourteenRigidBodyCI.m_restitution = 0.97f;
    fourteenRigidBodyCI.m_friction = 0.3f;
    fourteenRigidBodyCI.m_rollingFriction = 0.05f;
    fourteenRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(fourteenRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);

        //fifteen
    shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1.0, 13)));
    mass = btScalar(0.1);
    inertia = btVector3(0, 0, 0);
    fifteenCS->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo fifteenRigidBodyCI(mass, shapeMotionState, fifteenCS, inertia);
    fifteenRigidBodyCI.m_restitution = 0.97f;
    fifteenRigidBodyCI.m_friction = 0.3f;
    fifteenRigidBodyCI.m_rollingFriction = 0.05f;
    fifteenRigidBodyCI.m_spinningFriction = 0.1;
    RBptr = new btRigidBody(fifteenRigidBodyCI);
    RBptr->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(RBptr);
    RBVec.push_back(RBptr);






}
void Physics::ballReset() {
    if(!glRules.getGameOver())
    {
        btRigidBody *RBptr = RBVec.at(0);

        btTransform transform;
        RBptr->getMotionState()->getWorldTransform(transform);
        transform.setOrigin(btVector3(0, 1.0, -8));
        RBptr->getMotionState()->setWorldTransform(transform);
        RBptr->setCenterOfMassTransform(transform);

        RBptr->setAngularVelocity(btVector3(0,0,0));
        RBptr->setLinearVelocity(btVector3(0, 0, 0));
        RBptr->setAngularVelocity(btVector3(0,0,0));
    }

}

void Physics::Tilt() {

    btRigidBody *RBptr = RBVec.at(0);
    RBptr->applyCentralImpulse(btVector3(0.0, 0, 0.5));


/*    if(RBptr->getWorldTransform().getOrigin().getX() < 0) {
        RBptr->applyCentralImpulse(btVector3(0.5, 0, 0.5));
    }
    else {
        RBptr->applyCentralImpulse(btVector3(-0.5, 0, 0.5));
    }*/

}

void Physics::detectCollision()
{
    //std::cout << "Collision" << std::endl;
    dynamicsWorld->performDiscreteCollisionDetection();

    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();

    for(int i = 0; i < numManifolds; i++)
    {
        btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* objectA = const_cast<btCollisionObject*>(contactManifold->getBody0());
        btCollisionObject* objectB =  const_cast<btCollisionObject*>(contactManifold->getBody1());
        contactManifold->refreshContactPoints(objectA->getWorldTransform(), objectB->getWorldTransform());
        int numContacts = contactManifold->getNumContacts();

    }
}

bool Physics::anyBallsMoving() {

    for(int i = 0; i < RBVec.size(); i++) 
    {
        if(activeBalls[i])
        {
            glm::vec3 vel = glm::vec3(RBVec.at(i)->getLinearVelocity().x(), 
            RBVec.at(i)->getLinearVelocity().y(), 
            RBVec.at(i)->getLinearVelocity().z());
            float len = glm::length(vel);
            if(len > 0.2) 
            {
                return true;
            }
        }
    }

    return false;
}
bool Physics::Scratch() {
    if(RBVec.at(0)->getCenterOfMassPosition().y() < -0.05) {
        printf("Scratch!\n");
        ballReset();
        return true;
    }
    return false;
}

bool Physics::EightBallInPocket() {
    if(RBVec.at(8)->getCenterOfMassPosition().y() < -0.05) {
        //printf("8ball!\n");
        return true;
    }
    return false;
}

void Physics::setAllBallsActive()
{
    for(int i = 0; i < 16; i++)
    {
        activeBalls[i] = true;
    }
}

void Physics::updateActiveBalls() {
    for(int i = 0; i < RBVec.size() - 1; i ++) {
        if(RBVec.at(i)->getCenterOfMassPosition().y() < -0.05  &&
        activeBalls[i] == true) {
            if(player == 1)
            {
                if(i > 0 && i < 8)
                {
                    playerScored = true;
                    std::cout << "Player " << player << " scored!" << std::endl;
                }
            }
            else
            {
                if(i > 8)
                {
                    playerScored = true;
                    std::cout << "Player " << player << " scored!" << std::endl;
                }
            }
            activeBalls[i] = false;
            //printf("%i ball in pocket!\n", i);

        }
    }
}

void Physics::checkGameStatus()
{
    if(timer > 0)
    {
        timer = timer - 0.5f;
    }
    else
    {
        if(anyBallsMoving() && !roundStarted)
        {
            roundStarted = true;
        }

        if(roundStarted)
        {
            if(!anyBallsMoving())
            {
                updateActiveBalls();

                //8Ball sunk, check for winner
                if(!activeBalls[8])
                {
                    if((player == 1) && playerWon)
                    {
                        for(int i = 1; i < 8; i++)
                        {
                            if(activeBalls[i] == true)
                            {
                                playerWon = false;
                                std::cout << "Game Event: 8 ball sunk early!"
                                          << std::endl;
                            }

                        }
                    }
                    if((player == 2) && playerWon)
                    {
                        for(int i = 1; i < 8; i++)
                        {
                            if(activeBalls[i] == true)
                            {
                                playerWon = false;
                                std::cout << "Game Event: 8 ball sunk early!"
                                          << std::endl;
                            }

                        }
                    }
                    if(!playerWon)
                    {
                        swapPlayers();
                    }
                    winner = player;
                    gameReset();
                }

                //Check for Scratch
                if(!activeBalls[0])
                {
                    std::cout << "Game Event: Scratch" << std::endl;
                    activeBalls[0] = true;
                    ballReset();
                    playerScored = false;
                    roundStarted = false;
                    timer = 20.0f;
                }
                if(!playerScored)
                {
                    swapPlayers();
                    playerScored = false;
        	     roundStarted = false;

                }
                else
                {
                    roundStarted = false;
                    playerScored = false;
                }
            }

        }

    }
}

void Physics::swapPlayers()
{
    if(player == 1)
    {
        player++;
    }
    else
    {
        player = 1;
    }
}

void Physics::gameReset()
{
    resetBallPositions();
    setAllBallsActive();
    player = 1;
    playerScored = false;
    playerWon = true;
    roundStarted = false;
    winner = 0;
    timer = 10.0f;
}

void Physics::resetBallPositions()
{
    for(int i = 0; i < 16; i++)
    {
        btRigidBody *RBptr = RBVec.at(i);

        btTransform transform;
        RBptr->getMotionState()->getWorldTransform(transform);
        transform.setOrigin(btVector3(ballPositions[i]));
        RBptr->getMotionState()->setWorldTransform(transform);
        RBptr->setCenterOfMassTransform(transform);

        RBptr->setAngularVelocity(btVector3(0,0,0));
        RBptr->setLinearVelocity(btVector3(0, 0, 0));
        RBptr->setAngularVelocity(btVector3(0,0,0));
    }
}
