#ifndef COURSE_NODE_H
#define COURSE_NODE_H

#include "avl_node.h"
#include "class_node.h"

typedef enum StatusType_t
{
    ALLOCATION_ERROR,
    INVALID_INPUT,
    SUCCESS,
    FAILURE
} StatusType_t;

class courseNode
{
private:
    const int course_id;
    const int num_of_classes;
    int *classes_id;
    avlNode<classNode>** classes_pointers_array;

public:
    courseNode() = default;
    courseNode(const int courseID, const int numOfClasses);
    ~courseNode();
    classNode& getClass(const int classID);
    StatusType_t setClass(const classNode& new_class,const int classID);
};

#endif