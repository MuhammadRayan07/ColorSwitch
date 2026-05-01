#include "Rotation.h"

void rotateAllShapes(Shape** shapes, int count, float angle)
{
    for (int i = 0; i < count; i++)
    {
        if (!shapes[i] || shapes[i]->isCollected())
            continue;
        shapes[i]->rotateShape(angle);
    }
}