#pragma once
#include "Shape.h"
#include "CircleShapeObj.h"
#include "RectangleShapeObj.h"
#include "TriangleShapeObj.h"
#include "HorizontalLine.h"
#include "PlusShape.h"
#include "Difficulty.h"
#include <stdexcept>

class ShapeFactory
{
public:
    template<typename T>
    static T* createShape(float x, float y, float scale = 1.0f)
    {
        return new T(x, y, scale);
    }

    static Shape* createRandom(int type, float x, float y,
        float width, float scale, Difficulty diff)
    {
        switch (type)
        {
        case 0: return createShape<CircleShapeObj>(x, y, scale);
        case 1: return createShape<RectangleShapeObj>(x, y, scale);
        case 2: return createShape<TriangleShapeObj>(x, y, scale);
        case 3: return new HorizontalLine(y, width, scale);
        default:
            throw std::invalid_argument("Unknown shape type: " + std::to_string(type));
        }
    }
};