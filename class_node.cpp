#include "class_node.h"



classNode::classNode(const int course_id, const int class_id, avlNode<courseNode>* parent, int time)
    : course_id(course_id), class_id(class_id), parent(parent), time(time)
{}
int classNode::getTime(){
    return time;
}

StatusType_t classNode::setTime(const int time_to_add){
    if(time_to_add<=0){
        return INVALID_INPUT;
    }
    time+=time_to_add;
    return SUCCESS;
}