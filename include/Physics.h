//
// Created by jtucker on 10/25/21.
//

#ifndef LIFTOFF_PHYSICS_H
#define LIFTOFF_PHYSICS_H

#include <btBulletDynamicsCommon.h>
#include "game_logic.h"
#include "graphics_headers.h"
#include <vector>

class Physics {

public:
    Physics();
    ~Physics();

    void PoolSetup(btCollisionShape *table);
    void ballReset();
    void Tilt();
    void detectCollision();
    
    bool anyBallsMoving();
    bool Scratch();
    bool EightBallInPocket();
    void setAllBallsActive();
    void resetBallPositions();
    void updateActiveBalls();
    void checkGameStatus();
    void swapPlayers();
    void gameReset();
    
    bool activeBalls[16];
    bool roundStarted = false;
    bool playerScored = false;
    bool playerWon = true;
    int winner = 0;
    int player = 1;
    float timer = 10.0f;
    
    btVector3 ballPositions[16] = 
    {btVector3(0, 1.0, -8),//cue ball
    btVector3(0, 1.0, 5),//one ball
    btVector3(1, 1.0, 7),//two ball
    btVector3(2, 1.0, 9),//three ball
    btVector3(3, 1.0, 11),//four ball
    btVector3(-4, 1.0, 13),//five ball
    btVector3(2, 1.0, 13),//six ball
    btVector3(-1, 1.0, 11),//seven ball
    btVector3(0, 1.0, 9),//eight ball
    btVector3(-1, 1.0, 7),//nine ball
    btVector3(-2, 1.0, 9),//ten ball
    btVector3(-3, 1.0, 11),//eleven ball
    btVector3(4, 1.0, 13),//twelve ball
    btVector3(-2, 1.0, 13),//thirteen ball
    btVector3(1, 1.0, 11),//fourteen ball
    btVector3(0, 1.0, 13),};//fifteen ball

    std::vector<btRigidBody*> RBVec;
    btRigidBody* cueStickRB;
    btRigidBody* tableRB;
    btDiscreteDynamicsWorld *dynamicsWorld;
    GameLogic glRules;
    btVector3 baseInertia = btVector3(1.0, 1.0, 1.0);
};


#endif //LIFTOFF_PHYSICS_H
