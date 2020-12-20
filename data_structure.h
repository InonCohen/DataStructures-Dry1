#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "avl_tree.hpp"
#include "avl_node.hpp"
#include "class_node.h"
#include "course_node.h"
#include "library.h"

class classNode;
class courseNode;

class courseManager
{
private:
    avlTree<courseNode>* courses;
    avlTree<classNode>* classes;
    int classes_counter = 0;

public:
    courseManager();
    ~courseManager();
    StatusType AddCourse(int courseID, int numOfClasses);
    StatusType RemoveCourse(int courseID);
    StatusType WatchClass(int courseID, int classID, int time);
    StatusType TimeViewed(int courseID, int classID, int *timeViewed);
    StatusType GetMostViewedClasses(int numOfClasses, int *courses, int *classes);
    avlTree<courseNode>* getCourses() { return this->courses; }
    avlTree<classNode>* getClasses() { return this->classes; }
    void Quit(void **DS);
    StatusType replaceClass(avlNode<classNode> *ptr, int courseID, int classID, int time, avlNode<courseNode> *course);
};

#endif