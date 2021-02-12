#ifndef DOER_H
#define DOER_H

#include "list.hpp"

#include <cstdlib>
#include <ctime>
#include <sstream>

using std::cout;
using std::cin;
using namespace std;

template <typename NODETYPE>
class Wrapper : public List<NODETYPE>
{
    private:
    List<NODETYPE> *pList;
    std::string player;
    int score;

    public:
    Wrapper();
    Wrapper(std::string plyr, int scr);
    //void loadList();
    void runGame(ListNode<NODETYPE> *head, int rounds);
    void gameHelper();
    void output_profile();
    void load_prev();

    void printRules();
    int print_menu();
    
    //setters
    void set_player(std::string p); 
    void set_score(int s);
 
    //getters
    std::string get_player() const;
    int get_score() const;
};

template <typename NODETYPE>
void Wrapper<NODETYPE>::Wrapper()
: List<NODETYPE>() {
    pList = pList->getHead();
    player = NULL;
    score = 0;
}

template <typename NODETYPE>
void Wrapper<NODETYPE>::Wrapper(std::string new_plyr, int prev_score)
: List<NODETYPE>() {
    pList = pList->getHead();
    player = new_plyr;
    score = prev_score;
}

template <typename NODETYPE>
void Wrapper<NODETYPE>::load_prev()
{
    std::fstream input;
    input.open("profiles.csv");
    if (input.good())
    {
        std::string player_h, score_hold;
        getline(input, score_hold, '\n');
        std::stringstream ayeitsyoboiuhhhskinmnypenis(score_hold);
        getline(ayeitsyoboiuhhhskinmnypenis, player_h, ',');
        score_hold.clear();
        getline(ayeitsyoboiuhhhskinmnypenis, score_hold);
        //getline(input, score_hold, '\n');
        set_player(player_h);
        cout << "loaded user: " << player_h << " with a score of " << score_hold;
        set_score(stoi(score_hold));
    }
    input.close();
}

template <typename NODETYPE>
void Wrapper<NODETYPE>::set_player(std::string p)
{
    this->player = p;
}

template <typename NODETYPE>
void Wrapper<NODETYPE>::set_score(int s)
{
    this->score = s;
}

template <typename NODETYPE>
std::string Wrapper<NODETYPE>::get_player() const
{
    return this->player;
}

template <typename NODETYPE>
int Wrapper<NODETYPE>::get_score() const
{
    return this->score;
}

template <typename NODETYPE>
int Wrapper<NODETYPE>::print_menu()
{
    int option;
    do {
        std::cout << " _________________________________ \n"
                  << "|     Easy Linux Command Study    |\n" 
                  << "|_________________________________|\n" 
                  << "|            MAIN MENU            |\n" 
                  << "|                                 |\n"
                  << "|            [1] Rules            |\n" 
                  << "|       [2] New user playing      |\n" 
                  << "|     [3] Load previous player    |\n" 
                  << "|        [4] Add commands         |\n" 
                  << "|           [5] Exit :(           |\n"
                  << "|_________________________________|\n"
                  << "| Enter one of the options 1 -> 5 |\n" 
                  << "|_________________________________|\n";
        std::cin >> option;
        //system("CLS");
    } while((option > 5) || (option < 1));

    return option;
}

template <typename NODETYPE>
void Wrapper<NODETYPE>::printRules()
{
    std::cout << "To start off you are prompted for a name and then how many rounds of linux command's \n"
              << "to be questioned on. You will be shown the command then 3 possible anwsers of what the description for\n"
              << "that command can be. Guess right and you get a point, and if you guess incorrectly then you lose a point\n";
}

template <typename NODETYPE>
void Wrapper<NODETYPE>::gameHelper()
{
    int rounds, option;
    std::string name;
    system("CLS");
    option = print_menu();

    // buildiung list for the case of option being less than 5 
    // can use only one case do to the menu function forcing option to be from 1 -> 5
    // therefore we dont waste building the list if the user chooses to exit as the first option

    if(option < 5)
    {
        List();
        pList = getHead();
    }
    else
    {
        exit();
    }
    switch (option) {
        case 1:
            printRules();
            gameHelper();
        case 2:
            cout << "Enter your name: ";
            getline(cin, name);
            set_player(name);
            //build list
            std::cout << "How many commands do you want to practice out of " << pList->getsize() << "?\n";
            do {
            std::cin >> rounds;
            } while(rounds < 0);
            runGame(this->pList->pHead, rounds);
            output_profile();
            output_list(this->pList->pHead);
            break;
        case 3:
            load_prev();
            cout << "Username: " << get_player() << "\nPrevious score: " << get_score() << std::endl;
            //build list
            std::cout << "How many commands do you want to practice out of " << pList->getsize() << "?\n";
            do {
            std::cin >> rounds;
            } while(rounds < 0);
            runGame(this->pList->pHead, rounds);
            output_profile();
            output_list(this->pList->pHead);
            break;
        case 4:
            //build list
            addCommand();
            gameHelper();
        case 5:
            output_profile();
            output_list(this->pList->pHead);
            exit();
    }
}

template <typename NODETYPE>
void Wrapper<NODETYPE>::runGame(ListNode<NODETYPE> *pCur, int rounds)
{
    srand (time(NULL));
    //list(pCur);
    for (int n = 0; n < rounds; n++)
    {
        int rand_location = rand() % pCur->getsize() + 1;
        do{
            if (!pCur->get_next())
            {
                pCur = getHead();
            }
            pCur = pCur->get_next();
            rand_location--;
        } while(rand_location != 1);
        cout << "Command: " << pCur->pData->get_command();
        int rand_display = rand() % 2 + 1;
        //int display_order = rand() % 2 + 1;
        int choice;
        if ( rand_display == 1 )
        {
            cout << "\nDescription 1: " << pCur->pData->get_descrip();
            cout << "\nDescription 2: " << getHead()->get_next()->pData->get_descrip();
            cout << "\nDescription 3: " << getTail()->pData->get_descrip();
            do 
            {
                cin >> choice;
            } while((choice > 3) || (choice < 1));
            if (choice == 1)
            this->score++;
            else 
            this->score--;
        }
        else if ( rand_display == 2 )
        {
            cout << "\nDescription 1: " << getHead()->pData->get_descrip();
            cout << "\nDescription 2: " << pCur->pData->get_descrip();
            cout << "\nDescription 3: " << getHead()->pNext->pNext->pData->get_descrip();
            do 
            {
                std::cin >> choice;
            } while((choice > 3) && (choice < 1));
            if (choice == 2)
            this->score++;
            else 
            this->score--;  
        }
        else
        {
            cout << "\ndescription 1: " << getTail()->pData->get_descrip();
            if (!pCur->pNext)
            cout << "\nDescription 2: " << pCur->pNext->pData->get_descrip();
            else
            cout << "\nDescription 2: " << getTail()->get_descrip();
            cout << "\nDescription 3: " << pCur->pData->get_descrip();
            do 
            {
                std::cin >> choice;
            } while((choice > 3) && (choice < 1));
            if (choice == 3)
            this->score++;
            else 
            this->score--; 
        }
    }
}

template <typename NODETYPE>
void Wrapper<NODETYPE>::output_profile()
{
    std::fstream output;
    output.open("/home/ss/findthis/CptS223/pa/1/profiles.csv");
    output << this->player << ',' << this->score << "\n";

    output.close(); 
}

#endif