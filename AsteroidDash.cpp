#include "AsteroidDash.h"


// Constructor to initialize AsteroidDash with the given parameters
AsteroidDash::AsteroidDash(const string &space_grid_file_name,
                           const string &celestial_objects_file_name,
                           const string &leaderboard_file_name,
                           const string &player_file_name,
                           const string &player_name)

        : leaderboard_file_name(leaderboard_file_name), leaderboard(Leaderboard()) {

    read_player(player_file_name, player_name);  // Initialize player using the player.dat file
    read_space_grid(space_grid_file_name);  // Initialize the grid after the player is loaded
    read_celestial_objects(celestial_objects_file_name);  // Load celestial objects
    leaderboard.read_from_file(leaderboard_file_name);
}

// Function to read the space grid from a file
void AsteroidDash::read_space_grid(const string &input_file) {
    // TODO: Your code here
}

// Function to read the player from a file
void AsteroidDash::read_player(const string &player_file_name, const string &player_name) {
    // TODO: Your code here
}

// Function to read celestial objects from a file
void AsteroidDash::read_celestial_objects(const string &input_file) {
    // TODO: Your code here
}


// Print the entire space grid
void AsteroidDash::print_space_grid() const {
    // TODO: Your code here
}


// Function to update the space grid with player, celestial objects, and any other changes
// It is called in every game tick before moving on to the next tick.
void AsteroidDash::update_space_grid() {
    // TODO: Your code here
}

// Corresponds to the SHOOT command.
// It should shoot if the player has enough ammo.
// It should decrease the player's ammo
void AsteroidDash::shoot() {
    // TODO: Your code here
}

// Destructor. Remove dynamically allocated member variables here.
AsteroidDash::~AsteroidDash() {
    // TODO: Your code here
}