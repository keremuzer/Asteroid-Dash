#include <iostream>
#include "CelestialObject.h"

CelestialObject::CelestialObject(const vector<vector<bool>> &shape, ObjectType type, int start_row,
                                 int time_of_appearance)
    : shape(shape), object_type(type), starting_row(start_row), time_of_appearance(time_of_appearance)
{
    // TODO: Your code here
}

// Copy constructor for CelestialObject
CelestialObject::CelestialObject(const CelestialObject *other)
    : shape(other->shape),                          // Copy the 2D vector shape
      object_type(other->object_type),              // Copy the object type
      starting_row(other->starting_row),            // Copy the starting row
      time_of_appearance(other->time_of_appearance) // Copy the time of appearance
{
    // TODO: Your code here
}

// Function to create rotations of a celestial object, including the original shape
void CelestialObject::create_rotations()
{
    CelestialObject *current = this;
    CelestialObject *first_rotation = this;
    CelestialObject *new_rotation = new CelestialObject(current->rotate_right());
    new_rotation->next_celestial_object = this->next_celestial_object;

    if (equals(this->shape, new_rotation->shape))
    {
        delete new_rotation;
        this->right_rotation = this;
        this->left_rotation = this;
    }
    else
    {
        current->right_rotation = new_rotation;
        new_rotation->left_rotation = current;
        current = new_rotation;
        while (true)
        {
            new_rotation = new CelestialObject(current->rotate_right());
            new_rotation->next_celestial_object = this->next_celestial_object;

            if (equals(this->shape, new_rotation->shape))
            {
                delete new_rotation;
                break;
            }

            current->right_rotation = new_rotation;
            new_rotation->left_rotation = current;
            current = new_rotation;
        }
        current->right_rotation = first_rotation;
        first_rotation->left_rotation = current;
    }
}

// Function to rotate the celestial object to the right
CelestialObject CelestialObject::rotate_right()
{
    int new_rows = shape[0].size();
    int new_cols = shape.size();
    vector<vector<bool>> new_shape(new_rows, vector<bool>(new_cols));

    for (int i = 0; i < new_rows; i++)
    {
        for (int j = new_cols - 1; j >= 0; j--)
        {
            new_shape[i][new_cols - 1 - j] = shape[j][i];
        }
    }
    return CelestialObject(new_shape, object_type, starting_row, time_of_appearance);
}

// Function to compare the shapes of two celestial objects
bool CelestialObject::equals(vector<vector<bool>> shape1, vector<vector<bool>> shape2)
{
    if (shape1.size() != shape2.size() || shape1[0].size() != shape2[0].size())
    {
        return false;
    }
    for (int i = 0; i < shape1.size(); i++)
    {
        for (int j = 0; j < shape1[i].size(); j++)
        {
            if (shape1[i][j] != shape2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

// Function to delete rotations of a given celestial object. It should free the dynamically allocated
// memory for each rotation.
void CelestialObject::delete_rotations(CelestialObject *target)
{
    if (!target)
        return;

    CelestialObject *current = target->right_rotation;
    CelestialObject *next_rotation = nullptr;

    while (current && current != target)
    {
        next_rotation = current->right_rotation;
        current->right_rotation = nullptr;
        current->left_rotation = nullptr;

        delete current;
        current = next_rotation;
    }
    target->right_rotation = target;
    target->left_rotation = target;
}

// destructor
CelestialObject::~CelestialObject()
{
    delete_rotations(this);
}
