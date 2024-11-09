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
    std::ifstream file(player_file_name);
    if (!file)
    {
        std::cerr << "Error: Could not open file " << player_file_name << std::endl;
        return;
    }

    int row, col;
    file >> row >> col;

    std::string line;
    vector<vector<bool>> spacecraft_shape;

    while (getline(file, line))
    {
        std::vector<bool> shape_row;
        for (char c : line)
        {
            if (c == '1')
                shape_row.push_back(true);
            else if (c == '0')
                shape_row.push_back(false);
        }
        if (!shape_row.empty())
            spacecraft_shape.push_back(shape_row);
    }
    file.close();

    player = new Player(spacecraft_shape, row, col, player_name);
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
                        row.push_back(val == '1' ? true : false);
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
                        row.push_back(val == '1' ? true : false);
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
    CelestialObject *current_obj = celestial_objects_list_head;
    while (current_obj != nullptr)
    {
        current_obj->create_rotations();
        current_obj = current_obj->next_celestial_object;
    }

    file.close();
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
    // clear the grid
    for (int i = 0; i < space_grid.size(); i++)
    {
        for (int j = 0; j < space_grid[i].size(); j++)
        {
            space_grid[i][j] = 0;
        }
    }

    // Update the player's position
    for (int i = 0; i < player->spacecraft_shape.size(); i++)
    {
        for (int j = 0; j < player->spacecraft_shape[i].size(); j++)
        {
            if (player->spacecraft_shape[i][j])
            {
                space_grid[player->position_row + i][player->position_col + j] = 1;
            }
        }
    }

    // Detect collisions with player
    CelestialObject *current = celestial_objects_list_head;
    while (current != nullptr)
    {
        bool flag = false;
        if (current->time_of_appearance <= game_time && !current->destroyed)
        {
            int max_i = current->shape.size();
            for (int i = 0; i < max_i; i++)
            {
                if (flag)
                    break;
                int max_j = current->shape.at(i).size();
                for (int j = 0; j < max_j; j++)
                {
                    if (flag)
                        break;
                    if (current->shape[i][j])
                    {
                        int row = current->starting_row + i;
                        int col = space_grid[0].size() - (game_time - current->time_of_appearance) - 1 + j;
                        if (row >= 0 && row < space_grid.size() && col >= 0 && col < space_grid[0].size())
                        {
                            if (space_grid[row][col] == 1)
                            {
                                if (current->object_type == ASTEROID)
                                {
                                    std::cout << "Asteroid hit" << std::endl;
                                    player->lives--;
                                    if (player->lives == 0)
                                    {
                                        game_over = true;
                                    }
                                    current->destroyed = true;
                                    flag = true;
                                }
                                else if (current->object_type == LIFE_UP)
                                {
                                    player->lives++;
                                    current->destroyed = true;
                                }
                                else if (current->object_type == AMMO)
                                {
                                    player->current_ammo = player->max_ammo;
                                    current->destroyed = true;
                                }
                                current->delete_rotations(current);
                            }
                        }
                    }
                }
            }
        }
        current = current->next_celestial_object;
    }

    // Update bullet positions
    for (int k = 0; k < player->bullets.size(); k++)
    {
        Player::bullet &bullet = player->bullets[k];
        if (bullet.col < space_grid[0].size() && !bullet.destroyed)
        {
            space_grid[bullet.row][bullet.col] = 1;
            bullet.col++;
        }
        else
        {
            bullet.destroyed = true;
        }
    }

    // Update celestial objects
    CelestialObject *current_obj = celestial_objects_list_head;
    while (current_obj != nullptr)
    {
        bool flag = false;
        if (current_obj->time_of_appearance <= game_time && !current_obj->destroyed)
        {
            for (int i = 0; i < current_obj->shape.size(); i++)
            {
                if (flag)
                    break;
                for (int j = 0; j < current_obj->shape[i].size(); j++)
                {
                    if (flag)
                        break;
                    if (current_obj->shape[i][j])
                    {
                        int row = current_obj->starting_row + i;
                        int col = space_grid[0].size() - (game_time - current_obj->time_of_appearance) + j;
                        col--;
                        if (row >= 0 && row < space_grid.size() && col >= 0 && col < space_grid[0].size())
                        {
                            if (space_grid[row][col] == 1)
                            {
                                if (current_obj->object_type == ASTEROID)
                                {
                                    std::cout << "Asteroid hit 2" << std::endl;
                                    space_grid[row][col] = 0;
                                    current_obj->shape[i][j] = false;
                                    for (int k = 0; k < player->bullets.size(); k++)
                                    {
                                        Player::bullet &bullet = player->bullets[k];
                                        if (bullet.row == row && bullet.col == col + 1 && !bullet.destroyed)
                                        {
                                            std::cout << "Bullet hit" << std::endl;
                                            bullet.destroyed = true;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                space_grid[row][col] = 1;
                            }
                        }
                    }
                }
            }
        }
        current_obj = current_obj->next_celestial_object;
    }
}

// Corresponds to the SHOOT command.
// It should shoot if the player has enough ammo.
// It should decrease the player's ammo
void AsteroidDash::shoot()
{
    // TODO: Your code here
    if (player->current_ammo > 0)
    {
        player->current_ammo--;
        int bullet_row = player->position_row + player->spacecraft_shape.size() / 2;
        int bullet_col = player->position_col + player->spacecraft_shape[0].size();
        player->bullets.push_back(Player::bullet{bullet_row, bullet_col});
    }
}

// Destructor. Remove dynamically allocated member variables here.
AsteroidDash::~AsteroidDash()
{
    // TODO: Your code here
    delete player;
    CelestialObject::delete_rotations(celestial_objects_list_head);
    leaderboard.write_to_file(leaderboard_file_name);
}
