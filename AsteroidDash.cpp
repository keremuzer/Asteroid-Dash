#include "AsteroidDash.h"
#include <fstream>
#include <sstream>

// Constructor to initialize AsteroidDash with the given parameters
AsteroidDash::AsteroidDash(const string &space_grid_file_name,
                           const string &celestial_objects_file_name,
                           const string &leaderboard_file_name,
                           const string &player_file_name,
                           const string &player_name)

    : leaderboard_file_name(leaderboard_file_name), leaderboard(Leaderboard())
{

    read_player(player_file_name, player_name);          // Initialize player using the player.dat file
    read_space_grid(space_grid_file_name);               // Initialize the grid after the player is loaded
    read_celestial_objects(celestial_objects_file_name); // Load celestial objects
    leaderboard.read_from_file(leaderboard_file_name);
}

// Function to read the space grid from a file
void AsteroidDash::read_space_grid(const string &input_file)
{
    // TODO: Your code here
    std::ifstream file;
    file.open(input_file);
    std::string line;
    while (getline(file, line))
    {
        std::vector<int> row;
        std::istringstream iss(line);
        int val;
        while (iss >> val)
        {
            row.push_back(val);
        }
        space_grid.push_back(row);
    }
    file.close();
}

// Function to read the player from a file
void AsteroidDash::read_player(const string &player_file_name, const string &player_name)
{
    // TODO: Your code here
    std::ifstream file;
    file.open(player_file_name);
    int row, col;
    file >> row >> col;
    std::string line;
    std::vector<std::vector<bool>> spacecraft_shape;
    while (getline(file, line))
    {
        std::vector<bool> row;
        std::istringstream iss(line);
        bool val;
        while (iss >> val)
        {
            row.push_back(val);
        }
        spacecraft_shape.push_back(row);
    }
    player = new Player(spacecraft_shape, row, col, player_name);
    file.close();
}

// Function to read celestial objects from a file
void AsteroidDash::read_celestial_objects(const string &input_file)
{
    // TODO: Your code here
    CelestialObject *current = celestial_objects_list_head;
    std::ifstream file;
    file.open(input_file);
    std::string line;
    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<std::vector<bool>> shape;
        ObjectType obj_type;
        char val;
        while (iss >> val)
        {
            if (val == '[')
            {
                obj_type = ASTEROID;
                while (val != ']')
                {
                    std::vector<bool> row;
                    while (iss >> val && val != ']')
                    {
                        row.push_back(val);
                    }
                    shape.push_back(row);
                    // go to the next line

                    getline(file, line);
                    iss = std::istringstream(line);
                }
                int s = std::stoi(line.substr(2));
                getline(file, line);
                int t = std::stoi(line.substr(2));
                if (celestial_objects_list_head == nullptr)
                {
                    celestial_objects_list_head = new CelestialObject(shape, obj_type, s, t);
                    current = celestial_objects_list_head;
                }
                else
                {
                    current->next_celestial_object = new CelestialObject(shape, obj_type, s, t);
                    current = current->next_celestial_object;
                }
            }

            if (val == '{')
            {
                while (val != '}')
                {
                    std::vector<bool> row;
                    while (iss >> val && val != '}')
                    {
                        row.push_back(val);
                    }
                    shape.push_back(row);
                    // go to the next line
                    getline(file, line);
                    iss = std::istringstream(line);
                }
                int s = std::stoi(line.substr(2));
                getline(file, line);
                int t = std::stoi(line.substr(2));
                getline(file, line);
                if (line == "e:ammo")
                {
                    obj_type = AMMO;
                }
                else if (line == "e:life")
                {
                    obj_type = LIFE_UP;
                }
                if (celestial_objects_list_head == nullptr)
                {
                    celestial_objects_list_head = new CelestialObject(shape, obj_type, s, t);
                    current = celestial_objects_list_head;
                }
                else
                {
                    current->next_celestial_object = new CelestialObject(shape, obj_type, s, t);
                    current = current->next_celestial_object;
                }
            }
        }
    }
}

// Print the entire space grid
void AsteroidDash::print_space_grid() const
{
    // TODO: Your code here
}

// Function to update the space grid with player, celestial objects, and any other changes
// It is called in every game tick before moving on to the next tick.
void AsteroidDash::update_space_grid()
{
    // TODO: Your code here
}

// Corresponds to the SHOOT command.
// It should shoot if the player has enough ammo.
// It should decrease the player's ammo
void AsteroidDash::shoot()
{
    // TODO: Your code here
}

// Destructor. Remove dynamically allocated member variables here.
AsteroidDash::~AsteroidDash()
{
    // TODO: Your code here
}
