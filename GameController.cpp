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
            game->update_space_grid();
            game->print_space_grid();
            game->current_score++;
        }
        else if (line == "SHOOT")
        {
            game->shoot();
            game->update_space_grid();
            game->current_score++;
        }
        else if (line == "MOVE_LEFT")
        {
            game->player->move_left();
            game->update_space_grid();
            game->current_score++;
        }
        else if (line == "MOVE_RIGHT")
        {
            game->player->move_right(game->space_grid[0].size());
            game->update_space_grid();
            game->current_score++;
        }
        else if (line == "MOVE_UP")
        {
            game->player->move_up();
            game->update_space_grid();
            game->current_score++;
        }
        else if (line == "MOVE_DOWN")
        {
            game->player->move_down(game->space_grid.size());
            game->update_space_grid();
            game->current_score++;
        }
        else if (line == "NOP")
        {
            game->update_space_grid();
            game->current_score++;
        }
        else
        {
            std::cerr << "Unknown command: " << line << std::endl;
        }

        // Increment game tick
        game->game_time++;
    }
    game->update_space_grid();
    file.close();
    game->game_over = true;

    std::cout << "GAME FINISHED! No more commands!" << std::endl;
    std::cout << "Tick: " << game->game_time << std::endl;
    std::cout << "Lives: " << game->player->lives << std::endl;
    std::cout << "Ammo: " << game->player->current_ammo << std::endl;
    std::cout << "Score: " << game->current_score << std::endl;
    std::cout << "High Score: " << (game->current_score ? game->current_score > game->high_score : game->high_score) << std::endl;

    for (int i = 0; i < game->space_grid.size(); i++)
    {
        for (int j = 0; j < game->space_grid[i].size(); j++)
        {
            if (game->space_grid[i][j] == 1)
            {
                std::cout << occupiedCellChar;
            }
            else
            {
                std::cout << unoccupiedCellChar;
            }
        }
        std::cout << std::endl;
    }
    std::cout << endl
              << "Leaderboard" << endl;
    std::cout << "-----------" << endl;
}

// Destructor to delete dynamically allocated member variables here
GameController::~GameController()
{
    // TODO: Your code here
    delete game;
}
