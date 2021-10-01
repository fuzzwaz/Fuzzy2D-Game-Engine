//
//  Polygon.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Vector2.h"

#include <vector>
#include <memory>

//Polygon class represented by a list of points corresponding to each vertex
class Polygon
{
public:
    Polygon();

    const Vector2& GetCenter() const { return _center; }

    void operator=(const Polygon& source);

    /* Vertex Editing */
    void AddVertexPoint(float x, float y);
    void AddVertexPoint(const Vector2& vertex);
    void AddVertexPoint(const std::vector<Vector2>& vertices);
    void Rotate(float degrees); //Positive rotation is clockwise

    int GetNumOfVertices() const { return _numOfVertices; }
    const std::shared_ptr<const std::vector<Vector2>> GetVertices() const { return _vertices; } //Gets vertices in object coordinate space
    const std::shared_ptr<const std::vector<Vector2>> GetPerpendiculars() const; //If Perpendiculars are dirty, recalculates them before returning

private:
    Vector2 _center;
    std::shared_ptr<std::vector<Vector2>> _vertices = nullptr;
    mutable std::shared_ptr<std::vector<Vector2>> _perpendiculars = nullptr;
    int _numOfVertices = 0;

    mutable bool _dirtyPerpendiculars = true; //Dirty flag which signifies that the perpendiculars should be recalculated. Typically set when the poylgon is rotated or a vertex is added.

    void RecalculateCenterPoint();
    void RecalculatePerpendicularVectors() const; //Recalculates the perpendicular normals for each polygon edge given the current vertices. Resets dirty flag.
};

Vector2 ClockwisePerpendicularVector(const Vector2& pointA, const Vector2& pointB);
Vector2 ClockwisePerpendicularVector(const Vector2& vector);
Vector2 CounterClockwisePerpendicularVector(const Vector2& pointA, const Vector2& pointB);
Vector2 CounterClockwisePerpendicularVector(const Vector2& vector);