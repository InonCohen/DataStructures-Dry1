#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

#include "data_structure.h"
#include "avl_node.h"

courseManager::courseManager() {}

void *courseManager::Init() : courses(), classes()
{
    return this;
}

StatusType courseManager::AddCourse(int courseID, int numOfClasses)
{
    if (courseID <= 0 || numOfClasses <= 0)
        return INVALID_INPUT;
    courseNode new_course;
    new_course.setId(courseID);
    new_course.setNumOfClasses(numOfClasses);
    if (!new_course)
        return ALLOCATION_ERROR;

    // if (find(this->getCourses().getRoot(), *new_course))
    // {
    //     delete new_course;
    //     return FAILURE;
    // }

    avlTreeResult_t insert_result = this->courses.insert(new_course);
    if (insert_result == AVL_TREE_OUT_OF_MEMORY)
        return ALLOCATION_ERROR;
    else if (insert_result == AVL_TREE_SUCCESS)
    {
        new_course->defaultValues();
        return SUCCESS;
    }
    delete new_course;
    return FAILURE;
}

StatusType courseManager::RemoveCourse(int courseID)
{
    if (courseID <= 0)
        return INVALID_INPUT;

    courseNode searching_course_template;
    searching_course_template.setId(courseID);
    avlNode<courseNode> *course_pointer = find(this->getCourses().getRoot(), searching_course_template);
    courseNode temp_course(*course_pointer);
    if (!course_pointer)
        return FAILURE;

    //Course Exists in tree

    //TODO - what happens when removing doesnt go well (should keep data structure like it was)

    //Remove all classes in this course
    int number_of_classes = course_pointer->getValue().getNumOfClasses();
    for (int i = 0; i < number_of_classes; i++)
    {
        avlNode<classNode> *class_to_remove = *(course_pointer->getValue().getPointersArray() + i);
        if (class_to_remove)
            this->getClasses().remove(class_to_remove->getValue());
    }
    avlTreeResult_t remove_result = this->courses.remove(*course_pointer);
    if (remove_result == AVL_TREE_SUCCESS)
        return SUCCESS;
    else if (remove_result == AVL_TREE_FAILURE)
        return FAILURE;
    else
        return INVALID_INPUT;
}

StatusType courseManager::TimeViewed(int courseID, int classID, int *timeViewed)
{
    if (courseID <= 0 || classID​ < 0)
        return INVALID_INPUT;

    courseNode new_course;
    new_course.setId(courseID);
    avlNode<courseNode> *wanted_course = find(DS->courses, new_course);
    if (!wanted_course)
        return FAILURE;

    int num_of_classes = wanted_course->getValue().getNumOfClasses();
    if (classID > num_of_classes)
        return INVALID_INPUT;

    avlNode<classNode>* ptr = wanted_course->getClass(classID);
    if (!ptr)
        *timeViewed = 0;
    else
        *timeViewed = ptr->getTime();
    
    return SUCCESS;
}

StatusType courseManager::WatchClass(int courseID, int classID, int time)
{
    if (courseID <= 0 || classID​ < 0​ || time <= 0)
        return INVALID_INPUT;

    courseNode temp_course;
    temp_course.setId(courseID);
    avlNode<courseNode> *wanted_course = find(this->getCourses().getRoot(), temp_course);
    if (!wanted_course)
    {
        return FAILURE;
    }
    int num_of_classes = wanted_course->getTime();
    if (classID + 1 > num_of_classes)
    {
        return INVALID_INPUT;
    }
    return (wanted_course->getClass(classID)->setTime(time));
}

StatusType courseManager::GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    if (DS == NULL || numOfClasses <= 0)
    {
        return INVALID_INPUT;
    }
    if (classes.length() < numOfClasses)
    { // is it necessary/possible todo: in AVL Tree, create a counter for all leaves and a functions that provides this number
        reutrn FAILURE;
    }
}

void courseManager::Quit(void **DS)
{
    free(*DS->classes);
    free(*DS->courses);
    *DS = nullptr;
}
#endif