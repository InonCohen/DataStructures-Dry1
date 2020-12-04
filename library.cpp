#include "library.h"
#include "data_structure.h"

#define DataStructureIsValid(DS) \
        if (!DS)\
            return INVALID_INPUT;
void *Init()
{
    courseManager *DS = new courseManager();
    if (!DS)
        return NULL;
    return (void *)DS;
}

StatusType AddCourse(void *DS, int courseID, int numOfClasses)
{
    DataStructureIsValid(DS);
    return (((courseManager *)DS)->AddCourse(courseID, numOfClasses));
}
StatusType RemoveCourse(void *DS, int courseID)
{
    DataStructureIsValid(DS);
    return ((courseManager *)DS)->RemoveCourse(courseID);
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    DataStructureIsValid(DS);
    return ((courseManager *)DS)->WatchClass(courseID, classID, time);
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    DataStructureIsValid(DS);
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    DataStructureIsValid(DS);
}