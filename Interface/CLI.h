#ifndef CLI_H
#define CLI_H

#include "../structures/Queue.h"

inline void displayRoutineWaitingList(Queue& queue)
{
    if (queue.isEmpty())
    {
        cout << "No routine appointments are waiting." << endl;
        return;
    }

    cout << "\nRoutine Waiting List (Appointment IDs):" << endl;
    queue.display();
}

#endif