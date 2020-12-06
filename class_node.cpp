#include "class_node.h"

classNode::classNode(const int course_id, const int class_id, avlNode<courseNode> *parent, int time)
    : course_id(course_id), class_id(class_id), parent(parent), time(time)
{
}

classNode::classNode(const int course_id, const int class_id)
    : course_id(course_id), class_id(class_id)
{
}

classNode::classNode(const classNode &other)
    : course_id(other.course_id), class_id(other.class_id), parent(other.parent), time(other.time)
{
}

classNode &classNode::operator=(const classNode &other)
{
    this->parent = other.parent;
    this->time = other.time;
}

bool classNode::operator==(const classNode &other)
{
    if (this->time != other.time)
        return false;

    if (this->course_id != other.course_id)
        return false;

    if (this->class_id != other.class_id)
        return false;

    if (this->parent != other.parent)
        return false;

    return true;
}

bool classNode::operator<(const classNode &other) 
{
    if (this->time < other.time)
        return true;
    if (this->time > other.time)
        return false;
    else
    {
        if (this->course_id > other.course_id)
            return true;
        if (this->course_id < other.course_id)
            return false;
        else
        {
            if (this->class_id > other.class_id)
                return true;
            if (this->class_id < other.class_id)
                return false;
        }
    }
}


    // StatusType_t classNode::setTime(const int time_to_add){
    //     if(time_to_add<=0){
    //         return INVALID_INPUT;
    //     }
    //     time+=time_to_add;
    //     return SUCCESS;
    // }