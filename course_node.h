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
    int course_id;
    int num_of_classes;
    int *classes_id;
    avlNode<classNode>** classes_pointers_array;

public:
    courseNode() = default;
    courseNode(const courseNode& other);
    courseNode(const int courseID, const int numOfClasses);
    ~courseNode();
    avlNode<classNode>* getClass(const int classID);
    StatusType_t setClass(const classNode& new_class,const int classID);
    bool operator<(const courseNode courseToCompare);
    bool operator>(const courseNode courseToCompare);
    bool operator<=(const courseNode courseToCompare);
    bool operator==(const courseNode courseToCompare);
    void defaultValues();
    void setId(int new_id);
    int getId() {return this->course_id};
    const int getId() const {return this->course_id};
    void setNumOfClasses(int numOfClasses);
    int getNumOfClasses() {return this->num_of_classes;}
    const int getNumOfClasses() const {return this->num_of_classes;}
    int* getClasses() {return this->classes_id;}
    const int* getClasses() const {return this->classes_id;}
    avlNode<classNode>** getPointersArray() { return this->classes_pointers_array;}
    avlNode<classNode>** const getPointersArray() const { return this->classes_pointers_array;}
};

#endif