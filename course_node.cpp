#include "course_node.h"

courseNode::courseNode(const int courseID, const int numOfClasses) :
        course_id(courseID), num_of_classes(numOfClasses),
        classes_pointers_array(new avlNode<classNode> *[numOfClasses]),
        zero_views_node_pointers(new twListNode<int> *[numOfClasses]),
        zero_views_classes(new twList<int>())
{
/* avlNode<classNode> **new_classes_pointers_array = new avlNode<classNode> *[numOfClasses];
// if (!new_classes_pointers_array)
//     return NULL;
// twListNode<int>** new_zero_views_node_pointers = new twListNode<int> *[numOfClasses];
// if (!new_zero_views_node_pointers)
// {
//     delete[] new_classes_pointers_array;
//     return NULL;
// }
// twList<int>* new_zero_views_classes = new twList<int>();
// if (!new_zero_views_classes)
// {
//     delete[] new_classes_pointers_array;
//     delete[] new_zero_views_node_pointers;
//     return NULL;
// }
// this->classes_pointers_array = new_classes_pointers_array;
// this->zero_views_classes = new_zero_views_classes;
// this->zero_views_node_pointers = new_zero_views_node_pointers; */
    for (int i = 0; i < this->num_of_classes; i++)
    {
        *(this->classes_pointers_array + i) = NULL;
        this->zero_views_classes->addLast(i);
        *(this->zero_views_node_pointers + i) = this->zero_views_classes->getTail()->getPrev();
    }
}

courseNode::courseNode():
        classes_pointers_array(new avlNode<classNode> *[1]),
        zero_views_node_pointers(new twListNode<int> *[1]),
        zero_views_classes(new twList<int>())
{}


// courseNode::courseNode(const courseNode &other) : course_id(other.courseID), num_of_classes(other.numOfClasses),
//         classes_pointers_array(new avlNode<classNode> *[other.numOfClasses]),
//         zero_views_node_pointers(new twListNode<int> *[other.numOfClasses]),
//         zero_views_classes(new twList<int>()){
//     for (int i = 0; i < this->num_of_classes; i++)
//     {
//         *(this->classes_pointers_array + i) = *(other.getPointersArray() + i);
//     }
//     linkedListRooms *new_zero_views_classes = new linkedListRooms(other->getList());
//     if (!new_zero_views_classes)
//     {
//         delete[] new_classes_pointers_array;
//         return NULL;
//     }
//     listNode **new_zero_views_node_pointers = new listNode *[other.getNumOfClasses()];
//     if (!new_zero_views_node_pointers)
//     {
//         delete[] new_classes_pointers_array;
//         delete[] new_zero_views_classes;
//         return NULL;
//     }
//     listNode* head = this->new_zero_views_classes->getHead();
//     for (int i = 0; i < this->num_of_classes; i++)
//     {
//         *(this->zero_views_node_pointers + i) = head;
//         head = head->getNext();
//     }
// }

courseNode::~courseNode()
{
    delete[] this->classes_pointers_array;
    delete[] this->zero_views_node_pointers;
    delete this->zero_views_classes;
}

void courseNode::setId(int new_id)
{
    this->course_id = new_id;
}
void courseNode::setNumOfClasses(int numOfClasses)
{
    this->num_of_classes = numOfClasses;
}

avlNode<classNode> *courseNode::getClass(const int classID)
{
    if (classID > num_of_classes)
    {
        return NULL;
    }
    return classes_pointers_array[classID];
}

CourseStatus courseNode::setClassPointer(int classID, avlNode<classNode> *class_ptr)
{
    if (!class_ptr)
        return COURSE_FAILURE;
    *(this->classes_pointers_array + classID) = class_ptr;
    return COURSE_SUCCESS;
}

bool courseNode::operator<(const courseNode& courseToCompare) const
{
    return this->course_id < courseToCompare.course_id;
}

bool courseNode::operator!() const
{
    if (getId())
        return false;
    return true;
}

bool courseNode::operator==(const courseNode& courseToCompare) const
{
    return this->course_id == courseToCompare.course_id;
}

bool courseNode::operator<=(const courseNode& courseToCompare) const
{
    return this->course_id <= courseToCompare.course_id;
}
bool courseNode::operator>(const courseNode& courseToCompare) const
{
    return !(*this <= courseToCompare);
}
