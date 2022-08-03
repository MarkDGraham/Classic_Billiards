#include "object.h"

Object::Object(const char * path, btRigidBody *RB)
{
    Vertices = {};
    Indices = {};
    bool res = loadObj(path);
    mRigidBody = RB;

    if(res)
    {
        glGenBuffers(1, &VB);
        glBindBuffer(GL_ARRAY_BUFFER, VB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
    }
    angle = 0.0f;
}

Object::Object(const char * path, btTriangleMesh *mObjMesh)
{
    Vertices = {};
    Indices = {};
    bool res = loadObj(path, mObjMesh);
    mRigidBody = nullptr;

    if(res)
    {
        glGenBuffers(1, &VB);
        glBindBuffer(GL_ARRAY_BUFFER, VB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &IB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
    }
    angle = 0.0f;
}


Object::~Object()
{
    Vertices.clear();
    Indices.clear();
}



glm::mat4 Object::GetModel()
{
    return model;
}

//Unique object update functions -----------------------------------------------------------------------------------
void Table::Update(unsigned int dt, float globalSpeed) {

    btTransform trans;
    btScalar m[16];
    mRigidBody->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(m);
    model = glm::make_mat4(m) *
            //glm::translate(glm::vec3(0,-1.1,0)) *
            glm::scale(glm::vec3(1,1,1));
            //glm::rotate(glm::mat4(1), float(M_PI/2), glm::vec3(0, 1, 0));
}
void Sphere::Update(unsigned int dt, float globalSpeed) {

    btTransform trans;
    btScalar m[16];
    glm::vec3 vel = glm::vec3(mRigidBody->getLinearVelocity().x(), mRigidBody->getLinearVelocity().y(), mRigidBody->getLinearVelocity().z());
    float len = glm::length(vel);

    if(len > 30) {
        btVector3 newVel = btVector3(mRigidBody->getLinearVelocity().x() /2, mRigidBody->getLinearVelocity().y() /2, mRigidBody->getLinearVelocity().z() /2);
        mRigidBody->setLinearVelocity(newVel);

    }
    mRigidBody->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(m);
    model = glm::make_mat4(m) *
            glm::scale(glm::vec3(1.0));


}


void CueStick::Update(unsigned int dt, float globalSpeed) {

    btTransform trans;
    btVector3 position;
    btTransform parentTrans;
    btScalar m[16];

    mRigidBody->getMotionState()->getWorldTransform(trans);
    mParentRB->getMotionState()->getWorldTransform(parentTrans);

    glm::vec3 cueVec = glm::vec3(parentTrans.getOrigin().x(), parentTrans.getOrigin().y(), parentTrans.getOrigin().z());
    glm::vec3 stickVec = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
    //glm::vec3 normCue = glm::normalize(cueVec);
    //glm::vec3 normStick = glm::normalize(stickVec);

    //Set rotation of cuestick to always point a cue ball
    glm::vec3 direction = cueVec - stickVec;
    btVector3 btDirection = btVector3(direction.x, direction.y, direction.z);
    btVector3 btDirectionyaw = btVector3(direction.x, 0, direction.z);
    float btAngle = btDirectionyaw.angle(btVector3(1,0,0)) - float(M_PI/2);
    float btAngleYaw = btDirectionyaw.angle(btDirection);
    if(btDirectionyaw.z() > 0) {
        btAngle = -btAngle;
    }
    else {
        btAngle += float(M_PI);
    }
    btQuaternion qt(btAngle, btAngleYaw, 0);
    trans.setRotation(qt);

    //keep the distance from stick to ball
    float distance = glm::length(direction);
    //keep the linear speed of the cue ball
    glm::vec3 vel = glm::vec3(mParentRB->getLinearVelocity().x(), mParentRB->getLinearVelocity().y(), mParentRB->getLinearVelocity().z());
    float len = glm::length(vel);

    float xpos = 5 * sin(posAngle);
    float zpos = 5 * -cos(posAngle);
    float ypos = 1.2f;
    //glm::vec3 cuePos = glm::vec3(xpos, ypos, zpos);
    //float posDistance = glm::length(cuePos);

    if(posAngle >= glm::radians(360.0f)) {
        posAngle = glm::radians(0.0f);
    }
    if(posAngle < glm::radians(0.0f)) {
        posAngle = glm::radians(358.0f);
    }


    //control states
    if(readyState) {
        offset.x = xpos;
        offset.z = zpos;
        offset.y = ypos;
        position = parentTrans.getOrigin() + btVector3(offset.x, offset.y, offset.z);
        trans.setOrigin(position);
        if(len < 0.2) {
            canShoot = true;
        }
    }

    if(aimingState) {
        if(movingBackward) {
            if(distance < 10) {
                offset -= (0.2f * glm::normalize(direction)) ;
                distance = glm::length(direction);


                position = parentTrans.getOrigin() + btVector3(offset.x, offset.y, offset.z);
                trans.setOrigin(position);
            }
            else {
                movingBackward = false;
                movingForward = true;
            }
        }
        else {
            if(distance > 2) {
                offset += (0.2f * glm::normalize(direction)) ;
                position = parentTrans.getOrigin() + btVector3(offset.x, offset.y, offset.z);
                trans.setOrigin(position);
            }
            else {
                movingBackward = true;
            }
        }
        mRigidBody->setRestitution((((distance - 1) * 4) * 0.1) / 2);

    }


    if(shootingState) {
        offset += (0.8f * glm::normalize(direction)) ;
        float rest = mRigidBody->getRestitution();
        rest = rest;
        if(distance > 1.9) {
            position = parentTrans.getOrigin() + btVector3(offset.x, offset.y, offset.z);
            trans.setOrigin(position);
        }
        else {
            position = parentTrans.getOrigin() + btVector3(offset.x, offset.y, offset.z);
            trans.setOrigin(position);
            shootingState = false;
            readyState = true;
            canShoot = false;
        }
    }


    //Set the transform of the rigidbody and model
    mRigidBody->getMotionState()->setWorldTransform(trans);
    trans.getOpenGLMatrix(m);
    model = glm::make_mat4(m) *
            //glm::translate(glm::mat4(1), (direction * 0.8f)) *
            glm::rotate(float(M_PI), glm::vec3(0,1,0));
            //glm::scale(glm::vec3(0.5, 0.5, 10));

}



void SkyBox::Update(unsigned int dt, float globalSpeed) {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0)) *
            glm::rotate(glm::mat4(1.0f), float(M_PI + M_PI/16), glm::vec3(1.0, 0.0, 0.0)) *
            glm::rotate(glm::mat4(1.0f), float(M_PI/2), glm::vec3(0.0, 1.0, 0.0)) *
            //glm::rotate(glm::mat4(1.0f), float(M_PI/32), glm::vec3(1.0, 0.0, 0.0)) *
            //Scale
            glm::scale(glm::mat4(1.0f), glm::vec3(500));

}

//-----------------------------------------------------------------------------------------------------------------

bool Object::loadObj(const char *path) {

    //Create aiScene from file with Assimp importer
    m_Scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    meshNumber = m_Scene->mNumMeshes;
    aiMesh *mesh;

    Magick::InitializeMagick(nullptr);

    texture = new GLuint[meshNumber];
    for(unsigned int j = 0; j < meshNumber; j++)
    {

        if(m_Scene->HasMaterials())
        {
            const aiMaterial* material = m_Scene->mMaterials[j+1];
            aiString texturePath;

            if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
                {
                    Magick::Blob blob;
                    Magick::Image *image;
                    image = new Magick::Image(std::string("../res/Textures/") + texturePath.C_Str());
                    image->write(&blob, "RGBA");


                    //generate texture in OpenGL
                    glGenTextures(1, &texture[j]);
                    glBindTexture(GL_TEXTURE_2D, texture[j]);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    delete image;
                }
            }
        }
    }

    for(unsigned int meshNum = 0; meshNum < meshNumber; meshNum++)
    {
        mesh = m_Scene->mMeshes[meshNum]; //holds current mesh
        meshData.push_back(meshInfo(mesh->mNumFaces * 3, Indices.size())); // add 1 mesh to meshData vector & starting index

        aiColor4D colorVal(0.0f, 0.0f, 0.0f, 1.0f); //r, g, b, a, (a controls transparency)
        m_Scene->mMaterials[meshNum + 1]->Get(AI_MATKEY_COLOR_DIFFUSE, colorVal);
        aiMaterial* mtrl; // define a material type (stores materials)
        mtrl = m_Scene->mMaterials[mesh->mMaterialIndex]; //retrieve current mesh materials
        glm::vec3 colorVert(0.0f, 0.0f, 0.0f); // initialize a temporary color vertex
        glm::vec2 textureVert(0.0f, 0.0f); //initialize a temporary texture vertex

        if (mtrl != NULL)
        {
            if (AI_SUCCESS == aiGetMaterialColor(mtrl, AI_MATKEY_COLOR_DIFFUSE, &colorVal))
            {
                colorVert.x = colorVal.r;
                colorVert.y = colorVal.g;
                colorVert.z = colorVal.b;
            }
        }

        // Get INDICES (and vertices) from MESH
        int faceNumber = mesh->mNumFaces; //holds the number of faces in the current mesh

        for (int f = 0; f < faceNumber; f++) //traverse each face, save the 3 indices
        {
            aiFace* face = &mesh->mFaces[f]; // get the current face
            // Use index value to load vertex values from mVertices
            for (int i = 0; i < 3; i++)
            {
                Indices.push_back(face->mIndices[i]);  // push back face indices onto Indices
                if (mesh->HasTextureCoords(0))
                {
                    aiVector3D vert = mesh->mTextureCoords[0][face->mIndices[i]];
                    textureVert.x = vert.x;
                    textureVert.y = vert.y;
                }
                // load vertexs for face using mesh indices
                aiVector3D vertVect = mesh->mVertices[Indices.back()]; // get current vertices vector
                aiVector3D normVect = mesh->mNormals[Indices.back()];
                glm::vec3 tempPos = glm::vec3(vertVect.x, vertVect.y, vertVect.z);
                glm::vec3 tempNorm = glm::vec3(normVect.x, normVect.y, normVect.z);

                Vertex* tempVertex = new Vertex(tempPos, colorVert, textureVert, tempNorm);
                Vertices.push_back(*tempVertex); // push back position and color vector into Vertices
            }

        }
    }

    return true;
}

//-------------------------------------------------------------------------------------------------
//Load Object with custom collision mesh
bool Object::loadObj(const char *path, btTriangleMesh *mTriMesh) {

    //Create aiScene from file with Assimp importer
    m_Scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    meshNumber = m_Scene->mNumMeshes;
    aiMesh *mesh;

    Magick::InitializeMagick(nullptr);

    texture = new GLuint[meshNumber];
    for(unsigned int j = 0; j < meshNumber; j++)
    {

        if(m_Scene->HasMaterials())
        {
            const aiMaterial* material = m_Scene->mMaterials[j+1];
            aiString texturePath;

            if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
                {
                    Magick::Blob blob;
                    Magick::Image *image;
                    image = new Magick::Image(std::string("../res/Textures/") + texturePath.C_Str());
                    image->write(&blob, "RGBA");


                    //generate texture in OpenGL
                    glGenTextures(1, &texture[j]);
                    glBindTexture(GL_TEXTURE_2D, texture[j]);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    delete image;
                }
            }
        }
    }

    for(unsigned int meshNum = 0; meshNum < meshNumber; meshNum++)
    {
        mesh = m_Scene->mMeshes[meshNum]; //holds current mesh
        meshData.push_back(meshInfo(mesh->mNumFaces * 3, Indices.size())); // add 1 mesh to meshData vector & starting index

        aiColor4D colorVal(0.0f, 0.0f, 0.0f, 1.0f); //r, g, b, a, (a controls transparency)
        m_Scene->mMaterials[meshNum + 1]->Get(AI_MATKEY_COLOR_DIFFUSE, colorVal);
        aiMaterial* mtrl; // define a material type (stores materials)
        mtrl = m_Scene->mMaterials[mesh->mMaterialIndex]; //retrieve current mesh materials
        glm::vec3 colorVert(0.0f, 0.0f, 0.0f); // initialize a temporary color vertex
        glm::vec2 textureVert(0.0f, 0.0f); //initialize a temporary texture vertex

        if (mtrl != NULL)
        {
            if (AI_SUCCESS == aiGetMaterialColor(mtrl, AI_MATKEY_COLOR_DIFFUSE, &colorVal))
            {
                colorVert.x = colorVal.r;
                colorVert.y = colorVal.g;
                colorVert.z = colorVal.b;
            }
        }

        // Get INDICES (and vertices) from MESH
        int faceNumber = mesh->mNumFaces; //holds the number of faces in the current mesh

        for (int f = 0; f < faceNumber; f++) //traverse each face, save the 3 indices
        {
            btVector3 triArray[3];
            aiFace* face = &mesh->mFaces[f]; // get the current face
            // Use index value to load vertex values from mVertices
            for (int i = 0; i < 3; i++)
            {
                Indices.push_back(face->mIndices[i]);  // push back face indices onto Indices
                if (mesh->HasTextureCoords(0))
                {
                    aiVector3D vert = mesh->mTextureCoords[0][face->mIndices[i]];
                    textureVert.x = vert.x;
                    textureVert.y = vert.y;
                }
                // load vertexs for face using mesh indices
                aiVector3D vertVect = mesh->mVertices[Indices.back()]; // get current vertices vector
                aiVector3D normVect = mesh->mNormals[Indices.back()];
                glm::vec3 tempPos = glm::vec3(vertVect.x, vertVect.y, vertVect.z);
                glm::vec3 tempNorm = glm::vec3(normVect.x, normVect.y, normVect.z);

                Vertex* tempVertex = new Vertex(tempPos, colorVert, textureVert, tempNorm);
                Vertices.push_back(*tempVertex); // push back position and color vector into Vertices

                //create btcollision triangle mesh from vertices
                aiVector3D position = mesh->mVertices[face->mIndices[i]];
                triArray[i] = btVector3(position.x, position.y, position.z);

            }
            mTriMesh->addTriangle(triArray[0], triArray[1], triArray[2]);

        }
    }

    return true;
}


void Object::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normal));

    for(unsigned int i = 0; i < meshData.size(); i++)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * meshData[i].meshSize, &Vertices[meshData[i].meshStartIndex], GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * meshData[i].meshSize, &Indices[meshData[i].meshStartIndex], GL_STATIC_DRAW);

        //bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    }

    //glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}


