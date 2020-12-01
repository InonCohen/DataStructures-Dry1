#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

#include "data_structure.h"

void* courseManager::Init(): courses(),classes(){
    return this;
}

StatusType​ courseManager::AddCourse (​void *​DS, ​int​ courseID, ​int​ numOfClasses){
    if(DS==NULL || courseID<=0 || numOfClasses<=0){
        return INVALID_INPUT;
    }
    if(find(DS->courses, courseID)){
        return FAILURE;
    }
    course_node *new_course = new course_node(courseID, numOfClasses);
    if(!new_course){
        return ALLOCATION_ERROR;
    }
    if(DS->courses.insert(new_course) == AVL_TREE_SUCCESS){
        return SUCCESS;
    }
    return FAILURE;
}

StatusType​ courseManager::RemoveCourse(​void *D​S, ​int​ courseID){
     if(DS==NULL || courseID<=0){
        return INVALID_INPUT;
     }
    if(!find(DS->courses, courseID)){
        return FAILURE;
    }
    if(avlTree<courseNode>::remove(DS->courses, courseID) == AVL_TREE_SUCCESS){
        return SUCCESS;
    }
    return FAILURE;
}


StatusType​ courseManager::TimeViewed(​void *​DS, ​int​ courseID, ​int​ classID, ​int *​timeViewed){
    if(​DS==NULL || courseID<=0 || classID​<0){
        return INVALID_INPUT;
    }
    courseNode* wanted_course = find(DS->courses,courseID);
    if(!wanted_course){
        return FAILURE;
    }
    int num_of_classes = wanted_course.numOfClasses;
    if (classID>num_of_classes){
        return INVALID_INPUT;
    }
    classNode wanted_class = wanted_course(classID);
    *TimeViewed=wanted_class.getTime();
    return SUCCESS;



#endif