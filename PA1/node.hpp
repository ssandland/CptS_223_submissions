#ifndef NODE_H
#define NODE_H

#include "data.hpp"

using namespace std;



template <typename DATATYPE>
class ListNode : public Data<DATATYPE> {
    private:
    Data<DATATYPE> *pData;
    ListNode<DATATYPE> *pNext;
    ListNode<DATATYPE> *pHead;
    ListNode<DATATYPE> *pTail;

    public:
    ListNode();
    ListNode(std::string newC, std::string newD);
    //ListNode(Data<DATATYPE> *newData);
    // ~ListNode(); not necessary due to the list desctructor

    void new_node(Data<std::string> *pData);
    void new_node(std::string newC, std::string newD);
    void insertAtFront(ListNode<DATATYPE> *pNew);
    void removeNode(ListNode<DATATYPE> *pCur, DATATYPE c);
    bool isEmpty() { return pHead == nullptr; }
    
    //getters
    ListNode<DATATYPE> *& get_next() const;
    ListNode<DATATYPE> * getHead() const { return this->pHead; }
    ListNode<DATATYPE> * getTail() const { return this->pTail; }

    //setters
    void setHead(ListNode<DATATYPE> *pNew) { this->pHead = pNew; }
    void setTail(ListNode<DATATYPE> *pNew) { this->pTail = pNew; }
    void set_next(ListNode<DATATYPE> *newNext);
};

template <typename DATATYPE>
ListNode<DATATYPE>::ListNode() 
: pData.Data<DATATYPE>() {
    //pData = nullptr;
    pNext = nullptr;
    pTail = nullptr;
    pHead = nullptr;
}

template <typename DATATYPE>
ListNode<DATATYPE>::ListNode(std::string newC, std::string newD) 
: pData.Data<DATATYPE>(newC, newD) {
    pNext = nullptr;
    pTail = nullptr;
    pHead = nullptr;
}


template <typename DATATYPE>
void ListNode<DATATYPE>::new_node(std::string newC, std::string newD)
{
    ListNode<DATATYPE> *temp = new ListNode<DATATYPE>(newC, newD);
}

template <typename DATATYPE>
void ListNode<DATATYPE>::new_node(Data<std::string> *newData)
{
    ListNode<DATATYPE> *temp = new ListNode<DATATYPE>();
    temp->pData = newData;
    insertAtFront(temp);
}

template <typename DATATYPE>
ListNode<DATATYPE>*& ListNode<DATATYPE>::get_next() const
{
    return this->pNext;
}

template <typename DATATYPE>
void ListNode<DATATYPE>::insertAtFront(ListNode<DATATYPE> *pNew)
{
    if(isEmpty()) 
    {
        this->pHead->setHead(pNew);
        this->pTail->setHead(pNew);
        this->size++;
    }
    if(pNew != nullptr)
    {
        pNew->set_next(pHead);
        this->pHead->setHead(pNew);
        this->size++;   
    }
}

template <typename DATATYPE>
void ListNode<DATATYPE>::removeNode(ListNode<DATATYPE> * pCur, DATATYPE c)
{
    if (pHead->pData->command == c)
    {
        pCur = pHead->pNext;
        delete pHead;
        this->pHead = pCur;
        this->size--;
    }
    else 
    {
        do
        {
            if (pCur->pNext->pData->command == c)
            {
                ListNode<DATATYPE> * pTemp;
                pTemp = pCur->pNext;
                pCur->pNext = pTemp->pNext;
                delete pTemp;
                this->size--;
                break;
            }
            else
            pCur = pCur->pNext;
        } while(pCur->pNext != nullptr);
        cout << "There was no command called " << c;     
    }
}

template <typename DATATYPE>
void ListNode<DATATYPE>::set_next(ListNode<DATATYPE> *newNext)
{
    this->pNext = newNext;
}



#endif