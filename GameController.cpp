#include "GameController.h"
#include <fstream>

// Simply instantiates the game
GameController::GameController(
    const string &space_grid_file_name,
    const string &celestial_objects_file_name,
    const string &leaderboard_file_name,
    const string &player_file_name,
    const string &player_name

)
{
    game = new AsteroidDash(space_grid_file_name, celestial_objects_file_name, leaderboard_file_name, player_file_name,
                            player_name);
    // TODO: Your code here, if you want to perform extra initializations
}

// Reads commands from the given input file, executes each command in a game tick
void GameController::play(const string &commands_file)
{
    // TODO: Your code here
    std::ifstream file(commands_file);
    std::string line;

    while (getline(file, line))
    {
        if (line == "PRINT_GRID")
        {
            game->print_space_grid();
        }
        else if (line == "SHOOT")
        {
            game->shoot();
        }
        else if (line == "LEFT")
        {
            game->player->move_left();
        }
        else if (line == "RIGHT")
        {
            game->player->move_right(game->space_grid[0].size());
        }
        else if (line == "MOVE_UP")
        {
            game->player->move_up();
        }
        else if (line == "MOVE_DOWN")
        {
            game->player->move_down(game->space_grid.size());
        }
        else if (line == "NOP")
        {
            // Do nothing
        }
        game->update_space_grid();
    }

    /*vector<vector<int>> expected1 = {{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < 99; i++)
    {
        game->player->move_up();
        game->update_space_grid();
    }

    // print space grid
    for (int i = 0; i < game->space_grid.size(); i++)
    {
        for (int j = 0; j < game->space_grid[i].size(); j++)
        {
            std::cout << game->space_grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    if (game->space_grid == expected1)
    {
        std::cout << "Test 1 passed" << std::endl;
    }*/
}

// Destructor to delete dynamically allocated member variables here
GameController::~GameController()
{
    // TODO: Your code here
    delete game;
}
