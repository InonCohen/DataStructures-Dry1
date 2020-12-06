#include "course_node.h"

courseNode::courseNode(const int courseID, const int numOfClasses) : course_id(courseID), num_of_classes(numOfClasses)
{
    int *new_classes_id = new int[numOfClasses];
    this->classes_id = new_classes_id;

    avlNode<classNode>** new_classes_pointers_array = new avlNode<classNode>* [numOfClasses];
    this->classes_pointers_array = new_classes_pointers_array;
}

courseNode::courseNode(const courseNode& other): course_id(other.getId()), num_of_classes(other.getNumOfClasses()),
            classes_id(new int[other.getNumOfClasses()]), classes_pointers_array(new avlNode<classNode>* [other.getNumOfClasses()])
{
    for (int i = 0; i < this->num_of_classes; i++)
    {
        *(this->classes_id+i) = *(other.getClasses()+i);
        *(this->classes_pointers_array+i) = *(other.getPointersArray()+i);
    }
}

courseNode::~courseNode()
{
    delete[] this->classes_id;
    delete[] this->classes_pointers_array;
}

void courseNode::defaultValues()
{
    for (int i = 0; i < this->num_of_classes; i++)
    {
        *(this->classes_id+i) = i;
        *(this->classes_pointers_array+i) = NULL;
    }
}

void courseNode::setId(int new_id)
{
    this->course_id = new_id;
}
void courseNode::setNumOfClasses(int numOfClasses)
{
    this->num_of_classes = numOfClasses;
}


avlNode<classNode>* courseNode::getClass(const int classID){
    if(classID>num_of_classes){
        return NULL;
    }
    return classes_pointers_array[classID];
}

StatusType courseNode::setClassPointer(int classID, avlNode<classNode>* class_ptr)
{
    if (!class_ptr)
        return FAILURE;
    *(this->classes_pointers_array+classID) = class_ptr;
    return SUCCESS;
}


bool courseNode::operator<(const courseNode courseToCompare)
{
    return this->course_id < courseToCompare.course_id;
}

bool courseNode::operator==(const courseNode courseToCompare)
{
    return this->course_id == courseToCompare.course_id;
}


bool courseNode::operator<=(const courseNode courseToCompare)
{
    return this->course_id <= courseToCompare.course_id;
}
bool courseNode::operator>(const courseNode courseToCompare)
{
    return !(*this <= courseToCompare);
}

