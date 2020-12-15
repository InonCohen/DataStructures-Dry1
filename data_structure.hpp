#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

#include "data_structure.h"

courseManager::courseManager(): classes_counter(0)
{
    AvlTree<courseNode> *new_courses = new AvlTree<courseNode>();
    if (!new_courses)
        return NULL;
    AvlTree<courseNode> *new_classes = new AvlTree<classNode>();
    if (!new_courses)
    {
        delete new_courses;
        return NULL;
    }
    this->courses = new_courses;
    this->classes = new_classes;
}

courseManager::~courseManager()
{
    delete courses;
    delete classes;
}

StatusType courseManager::AddCourse(int courseID, int numOfClasses)
{
    if (courseID <= 0 || numOfClasses <= 0)
        return INVALID_INPUT;
    courseNode *new_course = new courseNode(courseID, numOfClasses);
    if (!new_course)
        return ALLOCATION_ERROR;
    // new_course.setId(courseID);
    // new_course.setNumOfClasses(numOfClasses);

    avlTreeResult_t insert_result = this->courses.insert(*new_course);
    if (insert_result != AVL_TREE_SUCCESS)
    {
        delete new_course;
        return (StatusType)insert_result;
    }
    else
    {
        this->classes_counter += numOfClasses;
        return (StatusType)insert_result;
    }
}

StatusType courseManager::RemoveCourse(int courseID)
{
    if (courseID <= 0)
        return INVALID_INPUT;

    courseNode searching_course_template;
    searching_course_template.setId(courseID);
    avlNode<courseNode> *course_pointer = find(this->getCourses().getRoot(), searching_course_template);
    if (!course_pointer)
        return FAILURE;
    // courseNode temp_course(course_pointer->getValue());
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
    avlTreeResult_t remove_result = this->courses.remove(course_pointer->getValue());
    if (remove_result == AVL_TREE_SUCCESS)
        this->classes_counter -= number_of_classes;
    return (StatusType)remove_result;
}

StatusType courseManager::TimeViewed(int courseID, int classID, int *timeViewed)
{
    if (courseID <= 0 || classID < 0)
        return INVALID_INPUT;

    courseNode new_course;
    new_course.setId(courseID);
    avlNode<courseNode> *wanted_course = find(this->getCourses().getRoot(), new_course);
    if (!wanted_course)
        return FAILURE;

    int num_of_classes = wanted_course->getValue().getNumOfClasses();
    if (classID + 1 > num_of_classes)
        return INVALID_INPUT;

    avlNode<classNode> *ptr = wanted_course->getValue().getClassPointer(classID);
    if (!ptr)
        *timeViewed = 0;
    else
        *timeViewed = ptr->getValue().getTime();

    return SUCCESS;
}

StatusType courseManager::WatchClass(int courseID, int classID, int time)
{
    if (courseID <= 0 || classID < 0 || time <= 0)
        return INVALID_INPUT;

    courseNode temp_course;
    temp_course.setId(courseID);
    avlNode<courseNode> *wanted_course = find(this->getCourses().getRoot(), temp_course);
    if (!wanted_course)
        return FAILURE;

    int num_of_classes = wanted_course->getValue().getNumOfClasses();
    if (classID + 1 > num_of_classes)
        return INVALID_INPUT;

    avlNode<classNode> *ptr = wanted_course->getValue().getClassPointer(classID);
    if (!ptr)
        wanted_course->getNodesPointer(classID)->removeNode();
    return this->replaceClass(ptr, courseID, classID, time, wanted_course);
}

StatusType courseManager::replaceClass(avlNode<classNode> *ptr, int courseID, int classID, int time, avlNode<courseNode> *course)
{
    classNode temp(courseID, classID);
    if (!ptr)
    {
        classNode new_class(courseID, classID, course, time);
        temp = new_class;
    }
    else
    {
        classNode new_class(ptr->getValue().getCourseId(), ptr->getValue().getClassId(), (avlNode<courseNode> *)ptr->getValue().getParentPointer(), ptr->getValue().getTime() + time);
        avlTreeResult_t remove_old_class_result = this->classes.remove(ptr->getValue());
        if (remove_old_class_result != AVL_TREE_SUCCESS)
            return (StatusType)remove_old_class_result;
        temp = new_class;
    }
    avlTreeResult_t insert_class_result = this->classes.insert(temp);
    if (insert_class_result != AVL_TREE_SUCCESS)
        return (StatusType)insert_class_result;
    else
    {
        avlNode<classNode> *class_pointer = find(this->getClasses().getRoot(), temp);
        return course->getValue().setClassPointer(classID, class_pointer);
    }
}

void copyNodeToArrays(avlNode<classNode> *node, int *courses, int *classes, int index)
{
    courses[index] = node->getValue().getCourseId();
    classes[index] = node->getValue().getClassId();
}

StatusType courseManager::GetMostViewedClasses(int numOfClasses, int *courses, int *classes)
{
    if (numOfClasses <= 0)
        return INVALID_INPUT;

    if (this->classes_counter < numOfClasses)
        return FAILURE;
    else
        int classes_with_zero_views = this->getClasses().getRoot().reverseInOrder(numOfClasses, copyNodeToArrays, courses, classes);

    if (classes_with_zero_views == 0)
        return SUCCESS;
    else
        this->getCourses().nonRecursiveInOrder(classes_with_zero_views, copyEmptyClassesToArray, courses + classes_with_zero_views, classes + classes_with_zero_views);
}

void copyEmptyClassesToArray(avlNode<courseNode> *node, int *courses, int *classes, int *index_address, int classes_with_zero_views)
{
    listNode head = node->getList()->getHead();
    if (!head)
        return;
    while (head && (classes_with_zero_views - *index_address))
    {
        courses[*index_address] = node->getId();
        classes[*index_address] = node->getValue().getClassId();
        *index_address++;
        head = head->getNext();
    }
}

#endif