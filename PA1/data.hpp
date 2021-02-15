#ifndef DATA_H
#define DATA_H

#include <string>
#include <iostream>

template <typename S>
class Data
{
    template <typename X> friend class listNode;

    private: 
    S command;
    S description;

    public:
    Data();
    virtual ~Data();

    explicit Data(S c, S d);

    S get_command() const { return this->command; }
    S get_descrip() const { return this->description; }
    void set_command(S c)  { this->command = c; }
    void set_descrip(S d) { this->description = d; }

};

template <typename S>
Data<S>::Data()
{
    command = NULL;
    description = NULL;
}

template <typename S>
Data<S>::Data(S c, S d)
{
    command = c;
    description = d;
}

#endif