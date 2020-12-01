#include "course_node.h"

courseNode::courseNode(const int courseID, const int numOfClasses) : course_id(courseID), num_of_classes(numOfClasses)
{
    int *new_classes_id = new int[numOfClasses];
    this->classes_id = new_classes_id;

    avlNode<classNode>** new_classes_pointers_array = new avlNode<classNode>* [numOfClasses];
    this->classes_pointers_array = new_classes_pointers_array;
}

courseNode::~courseNode()
{
    delete[] this->classes_id;
    delete[] this->classes_pointers_array;
}

classNode& courseNode::getClass(const int classID){
    if(classID>num_of_classes){
        return NULL;
    }
    return classes_pointers_array[classID];
}

StatusType_t courseNode::setClass(const classNode& new_class,const int classID){
    if( new_class==nullptr || classID<0 || classID>num_of_classes){
        return INVALID_INPUT;
    }
    classes_pointers_array[classID]=new_class;
    return SUCCESS;

}