#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

class listNode {
    int key; //roomID
    listNode *next;
    listNode *prev;

public:
    listNode(int key, listNode *next = nullptr, listNode *prev = nullptr,
             listNode *up = nullptr, listNode *down = nullptr) : key(
            key) {};

    listNode* getNext() {
        return this->next;
    }

    listNode* getPrev() {
        return this->prev;
    }


    void addNodeNext(listNode* node){
        this->next = node;
    }
    void addNodePrev(listNode* node){
        this->prev = node;

    }


    int getKey(){
        return this->key;
    }

    void addKey(int key){
        this->key = key;
    }


};

class linkedListRooms {
    listNode *head;
    listNode *tail;
    listNode *available;


public:
    explicit linkedListRooms (int hour, int rooms){

        listNode* newAvailable = new listNode(AVAILABLE);
        listNode* newHead = new listNode(0);
        listNode* newTail = new listNode(TAIL);


        this->head = newHead;
        this->head->addKey(hour);
        this->available = newAvailable;
        this->tail = newTail;

        this->head->addNodePrev(nullptr);
        this->head->addNodeNext(newAvailable);
        this->available->addNodeNext(newTail);
        this->available->addNodePrev(newHead);
        this->tail->addNodePrev(newAvailable);
        this->tail->addNodeNext(nullptr);

        this->createListRoom(rooms);
    };

    ~linkedListRooms(){
        listNode* iterator = head;
        listNode* temp = nullptr;

        while(iterator) {
            temp = iterator->getNext();
            delete iterator;
            iterator = temp;
        }
    }



    listNode* getAvailable(){
        return this->available;
    }

    listNode* getTail(){
        return this->tail;
    }

    listNode* getHead(){
        return this->head;
    }
    // return one list to one hour
    void createListRoom(int roomAmount) {
        if (!this || roomAmount < 0) {
            return;
        }

        listNode *tempPrev = this->getHead();
        for (int i = 0; i < roomAmount; i++) {
            listNode *newlistNode = new listNode(i);
            newlistNode->addNodeNext(this->available);
            this->available->addNodePrev(newlistNode);
            newlistNode->addNodePrev(tempPrev);
            tempPrev->addNodeNext(newlistNode);
            tempPrev = newlistNode;
        }
    }

    listNode* findAvailable(listNode* head){
        if(!head){
            return nullptr;
        }
        listNode* tempHead = head;
        while (tempHead->getKey()!=AVAILABLE){
            tempHead = tempHead->getNext();
        }
        return tempHead;
    }




    void makeUnAvailable(listNode* unAvailable) {
        if(!this) {
            return;
        }
        listNode* tempAvailable = findAvailable(head);
                listNode *tempNext = unAvailable->getNext();
                listNode *tempPrev = unAvailable->getPrev();
                listNode *tempNextAvail = tempAvailable->getNext();
                unAvailable->addNodeNext(tempNextAvail);
                unAvailable->addNodePrev(tempAvailable);
                tempAvailable->addNodeNext(unAvailable);
                tempNextAvail->addNodePrev(unAvailable);
                tempPrev->addNodeNext(tempNext);
                tempNext->addNodePrev(tempPrev);
    }


    void makeAvailable(listNode* available) {
        if(!this) {
            return;
        }
        listNode* tempAvailable = findAvailable(head);
                listNode *tempNext = available->getNext();
                listNode *tempPrev = available->getPrev();
                listNode *tempPrevAvail = tempAvailable->getPrev();
                available->addNodeNext(tempAvailable);
                available->addNodePrev(tempPrevAvail);
                tempAvailable->addNodePrev(available);
                tempPrevAvail->addNodeNext(available);
                tempPrev->addNodeNext(tempNext);
                tempNext->addNodePrev(tempPrev);
            }




    int* createArrayOfFreeRooms(int* freeRooms) {
        if(!this || !freeRooms) {
            return nullptr;
        }
        listNode* iterator = this->getHead();
        iterator = iterator->getNext();
        int i = 0;
        while (iterator->getKey() != AVAILABLE){
            freeRooms[i] = iterator->getKey();
            i++;
            iterator = iterator->getNext();
        }
        return freeRooms;
    }

    int numOfLecturesAvail(){
        int counter = 0;
        listNode* iterator = head;
        while(iterator->getNext()->getKey() != AVAILABLE) {
            counter++;
            iterator = iterator->getNext();
        }
        return counter;
    }
};


#endif //MIVNE_LISTROOMS_H
