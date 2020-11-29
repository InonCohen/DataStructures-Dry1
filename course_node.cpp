#include "course_node.h"

courseNode::courseNode(const int courseID, const int numOfClasses) : course_id(courseID)
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