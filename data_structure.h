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
} StatusType_t;

class courseManager
{
private:
   avl_tree<course_node> courses;
   avl_tree<class_node> classes; 

public:
void*​ Init();
StatusType​ AddCourse (​void *​DS, ​int​ courseID, ​int​ numOfClasses);
StatusType​ RemoveCourse(​void *D​S, ​int​ courseID);
StatusType​ WatchClass(​void *​DS, i​nt​ courseID, i​nt​ classID, ​int ​time);
StatusType​ TimeViewed(​void *​DS, ​int​ courseID, ​int​ classID, ​int *​timeViewed);
StatusType​ GetMostViewedClasses(​void *​DS, ​int ​numOfClasses, ​int *​courses, ​int *​classes);
void ​Quit(​void **​DS);
};




#endif