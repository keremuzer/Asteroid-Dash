#include "Leaderboard.h"

// Read the stored leaderboard status from the given file such that the "head_leaderboard_entry" member
// variable will point to the highest all-times score, and all other scores will be reachable from it
// via the "next_leaderboard_entry" member variable pointer.
void Leaderboard::read_from_file(const string &filename)
{
    // TODO: Your code here
}

// Write the latest leaderboard status to the given file in the format specified in the PA instructions
void Leaderboard::write_to_file(const string &filename)
{
    // TODO: Your code here
}

// Print the current leaderboard status to the standard output in the format specified in the PA instructions
void Leaderboard::print_leaderboard()
{
    // TODO: Your code here
}

//  Insert a new LeaderboardEntry instance into the leaderboard, such that the order of the high-scores
//  is maintained, and the leaderboard size does not exceed 10 entries at any given time (only the
//  top 10 all-time high-scores should be kept in descending order by the score).
void Leaderboard::insert(LeaderboardEntry *new_entry)
{
    if (head_leaderboard_entry == nullptr)
    {
        head_leaderboard_entry = new_entry;
        return;
    }

    if (new_entry->score > head_leaderboard_entry->score)
    {
        new_entry->next = head_leaderboard_entry;
        head_leaderboard_entry = new_entry;
    }
    else
    {
        LeaderboardEntry *current = head_leaderboard_entry;
        while (current->next != nullptr && new_entry->score <= current->next->score)
        {
            current = current->next;
        }
        new_entry->next = current->next;
        current->next = new_entry;
    }

    int size = 1;
    LeaderboardEntry *current = head_leaderboard_entry;
    while (current->next != nullptr)
    {
        size++;
        if (size > MAX_LEADERBOARD_SIZE)
        {
            LeaderboardEntry *excess = current->next;
            current->next = nullptr;
            while (excess != nullptr)
            {
                LeaderboardEntry *next = excess->next;
                delete excess;
                excess = next;
            }
            break;
        }
        current = current->next;
    }
}

// Free dynamically allocated memory used for storing leaderboard entries
Leaderboard::~Leaderboard()
{
    // TODO: Your code here
    LeaderboardEntry *current = head_leaderboard_entry;
    while (current != nullptr)
    {
        LeaderboardEntry *temp = current;
        current = current->next;
        delete temp;
    }
}
