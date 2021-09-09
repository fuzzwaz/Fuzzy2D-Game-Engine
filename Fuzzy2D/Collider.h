//
//  Collider.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Common.h"
#include "ColliderBaton.h"
#include "CollisionResponse.h"
#include "ColliderInterface.h"
#include "RigidBody.h"
#include "Polygon.h"

#include <vector>
#include <memory> 

struct Vector2;
class RigidBody;

//A set of vertex points representing a Polygon used for collision detection and response
class Collider : public ColliderInterface
{
public:
    Collider();

    void Rotate(float degrees) { _Polygon.Rotate(degrees); }; //Positive rotation is clockwise

    bool IsCircular() const override { return _circular; } //If a collider is circular, the Physics engine may use Circular collision detection as an optimization
    bool IsStatic() const override { return _static; } //Applies forces to other colliders, but do not physically respond to collisions
    bool IsTrigger() const override { return _trigger; } //Does not apply forces to other colliders and does not physically respond to collisions
    bool IsActive() const override { return _active; } //Turns on or off the collider during collision detection

    inline bool IsIgnoring(ColliderType type) const override; //Returns whether a specific ColliderType is being ignored by the Collider

    /* Setters */
    void SetIsCircular(bool isCircular) { _circular = isCircular; }
    void SetIsStatic(bool isStatic) { _static = isStatic; }
    void SetIsTrigger(bool isTrigger) { _trigger = isTrigger; }
    void SetIsActive(const bool& active) { _active = active; }
    void SetPosition(const Vector2 position) { _origin = position; }
    void SetAssociatedRigidBody(const RigidBody* rigidBody) { _rigidBody = rigidBody; }
    void SetRadius(const double& radius) { _radius = radius; }
    void SetMinimumCollisionDistance(const double& distance) { _minimumCollisionDistance = distance * distance; }
	void SetColliderType(const ColliderType& type);
	void SetColliderIgnoreTypes(std::vector<ColliderType> ignoreTypes);

    /* Getters */
    inline Vector2 GetCenter() const override;
    RigidBody GetAssociatedRigidBody() const override;
    Vector2 GetPosition() const override { return _origin; }
    ColliderType GetColliderType() const override { return _type; }
    CollisionResponseInfo GetCollisionResponseInfo() const override { return _responseInfo; }
    ColliderBaton GetBaton() const override { return _Baton; }
    double GetRadius() const override { return _radius; }
    double GetMinimumCollisionDistance() const override { return _minimumCollisionDistance; }
    const std::shared_ptr<const std::vector<Vector2>> GetVertices() const override { return _Polygon.GetVertices(); }
    const std::shared_ptr<const std::vector<Vector2>> GetPerpendiculars() const override { return _Polygon.GetPerpendiculars(); }

    /* Collision Response */
    void UpdateCollisionResponseInfo(const CollisionResponseInfo& info);
    void ClearCollisionResponseInfo();

    Polygon _Polygon;
    ColliderBaton _Baton; //Barebones "baton" of information that is passed to colliding objects so that they can decide how to respond to it
    
private:
    Vector2 _origin;
    const RigidBody* _rigidBody = nullptr; //Rigidbody associated with the collider. Used to determine appropriate collision reponse information
    double _minimumCollisionDistance = 200000; //Only other colliders that are within this distance will be checked during collision detection
    double _radius = _minimumCollisionDistance; //Used for circular collision detection

    bool _circular = false; //Circular enough to be considered for ciricular collision detection (optimization)
    bool _static = false; //Applies forces to other colliders, but do not physically respond to collisions
    bool _trigger = false; //Does not apply forces to other colliders and does not physically respond to collisions
    bool _active = true; //Turns on or off the collider during collision detection

    ColliderType _type = ColliderType::ENVIRONMENT;
    bool _ignoreTypes[ColliderType::ALL]; //Collider Types that will be ignored during collision detection

    CollisionResponseInfo _responseInfo; //The most recent collision detection response information. Updated each frame.
};

