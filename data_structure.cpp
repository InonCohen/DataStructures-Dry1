#include "data_structure.h"

courseManager::courseManager() : courses(new avlTree<courseNode>()), classes(new avlTree<classNode>())
{
    // avlTree<courseNode> *new_courses = new avlTree<courseNode>();
    // if (!new_courses)
    //     return NULL;
    // avlTree<classNode> *new_classes = new avlTree<classNode>();
    // if (!new_courses)
    // {
    //     delete new_courses;
    //     return NULL;
    // }
    // this->courses = new_courses;
    // this->classes = new_classes;
    // std::cout << "CREATED DATA STRUCTURE" << std::endl;
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
    // std::cout << "adding course: " << courseID << " With: " << numOfClasses << " classes." << std::endl;
    // if (this->getCourses()->getRoot())
    //     std::cout << "current root is: " << this->getCourses()->getRoot() /*->getValue()->getId()*/ << std::endl;

    courseNode *new_course = new courseNode(courseID, numOfClasses);

    avlTreeResult_t insert_result = this->getCourses()->insert(new_course);

    if (insert_result != AVL_TREE_SUCCESS)
        return (StatusType)insert_result;

    this->classes_counter += numOfClasses;
    return (StatusType)insert_result;
}

StatusType courseManager::RemoveCourse(int courseID)
{
    if (courseID <= 0)
        return INVALID_INPUT;

    courseNode searching_course_template;
    searching_course_template.setId(courseID);
    avlNode<courseNode> *course_pointer = find(this->getCourses()->getRoot(), &searching_course_template);
    if (!course_pointer)
        return FAILURE;
    // courseNode temp_course(course_pointer->getValue());
    //Course Exists in tree

    //TODO - what happens when removing doesnt go well (should keep data structure like it was)

    //Remove all classes in this course
    int number_of_classes = course_pointer->getValue()->getNumOfClasses();
    for (int i = 0; i < number_of_classes; i++)
    {
        avlNode<classNode> *class_to_remove = *(course_pointer->getValue()->getPointersArray() + i);
        if (class_to_remove)
            this->getClasses()->remove(class_to_remove->getValue());
    }
    avlTreeResult_t remove_result = this->getCourses()->remove((course_pointer->getValue()));
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
    avlNode<courseNode> *wanted_course = find(this->getCourses()->getRoot(), &new_course);
    if (!wanted_course)
        return FAILURE;

    int num_of_classes = wanted_course->getValue()->getNumOfClasses();
    if (classID + 1 > num_of_classes)
        return INVALID_INPUT;

    avlNode<classNode> *ptr = wanted_course->getValue()->getClassPointer(classID);
    if (!ptr)
        *timeViewed = 0;
    else
        *timeViewed = ptr->getValue()->getTime();

    return SUCCESS;
}

StatusType courseManager::WatchClass(int courseID, int classID, int time)
{
    if (courseID <= 0 || classID < 0 || time <= 0)
        return INVALID_INPUT;

    courseNode temp_course;
    temp_course.setId(courseID);
    avlNode<courseNode> *wanted_course = find(this->getCourses()->getRoot(), &temp_course);
    if (!wanted_course)
    {
        // std::cout << "not found class to watch." << std::endl;
        return FAILURE;
    }

    int num_of_classes = wanted_course->getValue()->getNumOfClasses();
    if (classID + 1 > num_of_classes)
        return INVALID_INPUT;

    avlNode<classNode> *ptr = wanted_course->getValue()->getClassPointer(classID);
    return this->replaceClass(ptr, courseID, classID, time, wanted_course);
}

StatusType courseManager::replaceClass(avlNode<classNode> *ptr, int courseID, int classID, int time, avlNode<courseNode> *course)
{
    classNode *temp;
    if (!ptr)
    {
        classNode *new_class = new classNode(courseID, classID, course, time);
        if (!new_class)
            return (StatusType)AVL_TREE_OUT_OF_MEMORY;
        temp = new_class;
        twListNode<int> *node_to_remove = course->getValue()->getClassNodePointer(classID);
        if (course->getValue()->getList()->remove(node_to_remove) != TW_LIST_SUCCESS)
            return (StatusType)TW_LIST_FAILURE;
    }
    else
    {
        classNode *new_class = new classNode(ptr->getValue()->getCourseId(), ptr->getValue()->getClassId(), (avlNode<courseNode> *)ptr->getValue()->getParentPointer(), ptr->getValue()->getTime() + time);
        if (!new_class)
            return (StatusType)AVL_TREE_OUT_OF_MEMORY;
        avlTreeResult_t remove_old_class_result = this->getClasses()->remove((ptr->getValue()));
        if (remove_old_class_result != AVL_TREE_SUCCESS)
            return (StatusType)remove_old_class_result;
        temp = new_class;
    }
    avlTreeResult_t insert_class_result = this->getClasses()->insert(temp);
    if (insert_class_result != AVL_TREE_SUCCESS)
        return (StatusType)insert_class_result;
    else
    {
        avlNode<classNode> *class_pointer = find(this->getClasses()->getRoot(), temp);
        return (StatusType)course->getValue()->setClassPointer(classID, class_pointer);
    }
}

void copyNodeToArrays(avlNode<classNode> *node, int *courses, int *classes, int index)
{
    courses[index] = node->getValue()->getCourseId();
    classes[index] = node->getValue()->getClassId();
}

void copyEmptyClassesToArray(avlNode<courseNode> *node, int *courses, int *classes, int *index_address, int classes_with_zero_views)
{
    twListNode<int> *head = node->getValue()->getList()->getHead();
    twListNode<int> *tail = node->getValue()->getList()->getTail();
    std::cout << *index_address << std::endl;
    if (!head)
        return;

    // twListNode<int> *head_copy = head;
    // while (head_copy->getNext() != tail) 
    // {
    //     head_copy = head_copy->getNext();
    //     std::cout << head_copy->getValue() << std::endl;
    // }
    while (head->getNext() != tail && (classes_with_zero_views - *index_address))
    {
        head = head->getNext();
        std::cout << node->getValue()->getId() << std::endl;
        courses[*index_address] = node->getValue()->getId();
        std::cout << head->getValue() << std::endl;
        classes[*index_address] = head->getValue();
        (*index_address)++;
    }
}

StatusType courseManager::GetMostViewedClasses(int numOfClasses, int *courses, int *classes)
{
    // std::cout << this->classes_counter << std::endl;
    if (numOfClasses <= 0)
    {
        return INVALID_INPUT;
    }
    if (this->classes_counter < numOfClasses)
        return FAILURE;

    int classes_with_zero_views = this->getClasses()->reverseInOrder(numOfClasses, copyNodeToArrays, courses, classes);
    // std::cout << classes_with_zero_views << std::endl;

    if (classes_with_zero_views == 0)
        return SUCCESS;
    else
        this->getCourses()->nonRecursiveInOrder(classes_with_zero_views, copyEmptyClassesToArray, courses + classes_with_zero_views - 1, classes + classes_with_zero_views - 1);
    return SUCCESS;
}
