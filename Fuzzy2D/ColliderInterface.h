//
//  ColliderInterface.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <memory>
#include <vector>

class RigidBody;
struct ColliderBaton;
struct CollisionResponseInfo;
struct Vector2;
enum ColliderType;

/*
	Interface class that allows the CollisionManager to get needed information about Colliders
	to perform collision detection without granting too much access.
 */
class ColliderInterface
{
public:
    virtual bool IsCircular() const = 0; //If a collider is circular, the Physics engine may use Circular collision detection as an optimization
    virtual bool IsStatic() const = 0; //Static colliders do not respond to collisions
    virtual bool IsActive() const = 0; //Inactive colliders are completely skipped over during collision detection
    virtual bool IsTrigger() const = 0; //Trigger colliders do not apply forces onto other colliding objects
    virtual bool IsIgnoring(ColliderType type) const = 0; //Returns whether a specific ColliderType is being ignored by the Collider

    virtual Vector2 GetCenter() const = 0;
    virtual RigidBody GetAssociatedRigidBody() const = 0; //Rigidbody associated with the collider. Used to determine appropriate collision reponse information
    virtual Vector2 GetPosition() const = 0;
    virtual ColliderType GetColliderType() const = 0;
    virtual CollisionResponseInfo GetCollisionResponseInfo() const = 0;
    virtual double GetRadius() const = 0;
    virtual double GetMinimumCollisionDistance() const = 0; //Only other colliders that are within this distance will be checked during collision detection
    virtual ColliderBaton GetBaton() const = 0; //Barebones "baton" of information that is passed to colliding objects so that they can decide how to respond to it


    virtual const std::shared_ptr<const std::vector<Vector2>> GetVertices() const = 0;
    virtual const std::shared_ptr<const std::vector<Vector2>> GetPerpendiculars() const = 0;

    /* Collision Response */
    virtual void UpdateCollisionResponseInfo(const CollisionResponseInfo& info) = 0;
    virtual void ClearCollisionResponseInfo() = 0;
};