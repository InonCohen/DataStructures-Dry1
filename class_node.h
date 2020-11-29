#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include "avl_node.h"
#include "course_node.h"

// typedef enum StatusType_t
// {
//     ALLOCATION_ERROR,
//     INVALID_INPUT,
//     SUCCESS,
//     FAILURE
// } StatusType_t;

class classNode
{
private:
    const int course_id;
    const int class_id;
    avlNode<courseNode> *parent;
    int time;

public:
    classNode() = {};
    classNode(const int course_id, const int class_id, avlNode<courseNode>* parent, int time);
    ~classNode();
};

#endif