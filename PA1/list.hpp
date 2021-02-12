#ifndef LIST_H
#define LIST_H

#include "node.hpp"
#include <fstream>

using namespace std;

template <typename NODETYPE>
class List : public ListNode<NODETYPE>
{
    private:
    ListNode<NODETYPE> *pHead;
    ListNode<NODETYPE> *pTail;
    int size;

    public:
    List();
    ~List();

    void loadList();
    void deleteItAll();

    //List<S> *newnode(S c, S d);
    void output_list(ListNode<NODETYPE> *pCurr);
    void addCommand();
    int getsize() const { return size; }
    void setsize(int s) { size = s; }

};

template <typename NODETYPE>
List<NODETYPE>::List()
: ListNode<NODETYPE>() {
    //pHead = nullptr;
    //pTail = nullptr;
    size = 0;
    
    pHead = getHead();
    pTail = getTail();
}

template <typename NODETYPE>
List<NODETYPE>::~List()
{
    deleteItAll();
}

template <typename NODETYPE>
void List<NODETYPE>::loadList()
{
    std::fstream input;
    input.open("commands.csv");
    std::string cmd_holder, des_holder, comma_holder;

    while(!input.eof())
    {
        getline(input, cmd_holder, ',');
        getline(input, comma_holder, '"');
        getline(input, des_holder, '"');
        Data<std::string> *newData = new Data<std::string>(cmd_holder, des_holder);
        new_node<Data<std::string>>(newData);
    }
    input.close();
}

template <typename NODETYPE>
void List<NODETYPE>::deleteItAll()
{
    if (pHead != nullptr) 
    {
        ListNode<NODETYPE> *temp = new ListNode<NODETYPE>();
        temp = pHead;
        pHead = pHead->pNext;
        delete temp;
        deleteItAll();
    }
    delete pHead;
    delete pTail;
    this->size = 0; 
}

template <typename NODETYPE>
void List<NODETYPE>::addCommand()
{
    std::string command, description;
    std::cout << "Enter the new command name: ";
    getline(std::cin, command);
    std::cout << "Enter the new command's description: ";
    getline(std::cin, description);

    Data<std::string> *newData = new Data<std::string>(command, description);
    new_node(newData);
}

template <typename NODETYPE>
void List<NODETYPE>::output_list(ListNode<NODETYPE> *pCur)
{
    std::fstream output;
    output.open("commands.csv");
    do { 
        output << pCur->pData->get_command() << ',' << '"' << pCur->pData->get_descrip() << '"' << "\n";
        pCur = pCur->pNext;
    } while(pCur->pData->get_command() != NULL);

    output.close();
}

#endif