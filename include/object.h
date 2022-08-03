#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <cmath>

#include <iostream>

class Object
{
public:
    Object(const char * path, btRigidBody *RB);
    Object(const char * path, btTriangleMesh *mObjMesh);
    ~Object();
    virtual void Update(unsigned int dt, float globalSpeed) = 0;
    void Render();
    glm::mat4 GetModel();
    btRigidBody *GetRigidBody() {return mRigidBody;};
    bool loadObj(const char *path);
    bool loadObj(const char *path, btTriangleMesh *mTriMesh);

    btRigidBody *mRigidBody;
    btRigidBody *mParentRB;


    //cue controls
    //states
    bool readyState = true;
    bool aimingState = false;
    bool shootingState = false;
    bool canShoot = true;
    bool movingForward = false;
    bool movingBackward = true;

    bool isPressingSpace = false;
    bool isPressingLeft = false;
    bool isPressingRight = false;
    bool startedCuePower = false;
    float power = 0.12;
    glm::vec3 offset = glm::vec3 (0,0,0);
    float posAngle = glm::radians(0.0f);


protected:
    float angle;     //angle is set inside update. Gets set to dt * pi/1000 by default
    glm::mat4 model;


private:

    Assimp::Importer importer;
    const aiScene *m_Scene;
    unsigned int meshNumber;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<meshInfo> meshData;
    GLuint VB;
    GLuint IB;
    GLuint *texture;


};

class Table: public Object {
public:
    Table(const char * path, btRigidBody *RB): Object(path,RB){};
    Table(const char * path, btTriangleMesh *mTri): Object(path, mTri){};
    void Update(unsigned int dt, float globalSpeed) override;
};

class Sphere: public Object {
public:
    Sphere(const char * path, btRigidBody *RB): Object(path,RB){};
    void Update(unsigned int dt, float globalSpeed) override;

};



class CueStick: public Object {
public:
    CueStick(const char * path, btRigidBody *RB): Object(path, RB){};
    void Update(unsigned int dt, float globalSpeed) override;



};





class SkyBox: public Object {
public:
    SkyBox(const char * path, btRigidBody *RB): Object(path,RB){};
    void Update(unsigned int dt, float globalSpeed) override;

};

#endif /* OBJECT_H */
