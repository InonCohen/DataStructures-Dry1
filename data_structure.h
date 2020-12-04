#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "avl_tree.h"
#include "course_node.h"
#include "class_node.h"

typedef enum StatusType_t
{
    ALLOCATION_ERROR,
    INVALID_INPUT,
    SUCCESS,
    FAILURE
} StatusType;

class courseManager
{
private:
    avlTree<courseNode> courses;
    avlTree<classNode> classes;

public:
    courseManager();
    void *Init();
    StatusType AddCourse(int courseID, int numOfClasses);
    StatusType RemoveCourse(int courseID);
    StatusType WatchClass(int courseID, int classID, int time);
    StatusType TimeViewed(int courseID, int classID, int *timeViewed);
    StatusType GetMostViewedClasses(int numOfClasses, int *courses, int *classes);
    avlTree<courseNode> getCourses() { return this->courses; }
    avlTree<classNode> getClasses() { return this->classes; }
    void Quit(void **DS);
};

#endif