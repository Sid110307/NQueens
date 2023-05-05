#include <iostream>
#include <chrono>
#include <cstdlib>

bool isSafe(int** board, int row, int col, int size)
{
    for (int i = 0; i < col; ++i) if (board[row][i]) return false;
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) if (board[i][j]) return false;
    for (int i = row, j = col; j >= 0 && i < size; ++i, --j) if (board[i][j]) return false;

    return true;
}

// TODO: better printing for 2+ digit numbers
void printBoard(int** board, int size)
{
    int numDigits = 1;
    int temp = size;

    while (temp > 9)
    {
        ++numDigits;
        temp /= 10;
    }

    std::cout << "     ";
    for (int i = 0; i < size; ++i) std::cout << i << std::string(numDigits * 3, ' ');
    std::cout << std::endl;

    std::cout << "   ";
    for (int i = 0; i < size; ++i) std::cout << "+" << std::string(numDigits * 3, '-');
    std::cout << "+" << std::endl;

    for (int i = 0; i < size; ++i)
    {
        std::cout << " " << std::string(numDigits - std::to_string(i).length(), ' ') << i << " |";
        for (int j = 0; j < size; ++j) std::cout << std::string(numDigits - (board[i][j] ? 1 : 0), ' ') << (board[i][j] ? " Q |" : "  |");
        std::cout << "\n   ";

        for (int j = 0; j < size; ++j) std::cout << "+" << std::string(numDigits * 3, '-');
        std::cout << "+" << std::endl;
    }

    std::cout << std::endl;
}

void solve(int** board, int col, bool* usedRows, bool* usedDiag1, bool* usedDiag2, int size, int& solutions)
{
    if (col == size)
    {
        ++solutions;
        printBoard(board, size);

        return;
    }

    for (int row = 0; row < size; ++row)
        if (!usedRows[row] && !usedDiag1[row + col] && !usedDiag2[row - col + size - 1])
        {
            board[row][col] = 1;
            usedRows[row] = true;
            usedDiag1[row + col] = true;
            usedDiag2[row - col + size - 1] = true;

            solve(board, col + 1, usedRows, usedDiag1, usedDiag2, size, solutions);
            board[row][col] = 0;

            usedRows[row] = false;
            usedDiag1[row + col] = false;
            usedDiag2[row - col + size - 1] = false;
        }
}

int main(int argc, char** argv)
{
    int size = 8;

    if (argc > 1)
    {
        try
        {
            size = std::stoi(argv[1]);
            if (size < 1)
            {
                std::cerr << "Error: Board size must be a positive integer." << std::endl;
                return EXIT_FAILURE;
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Error: Invalid board size." << std::endl;
            return EXIT_FAILURE;
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Error: Board size is too large." << std::endl;
            return EXIT_FAILURE;
        }
        catch (...)
        {
            std::cerr << "Error: Unknown error." << std::endl;
            return EXIT_FAILURE;
        }
    }
    else while (true)
    {
        std::cout << "Enter the size of the board (enter nothing for 8): ";
        std::string input;
        std::getline(std::cin, input);

        if (!input.empty())
        {
            try
            {
                size = std::stoi(input);

                if (size >= 1) break;
                else std::cerr << "Invalid input. Please enter a positive integer." << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Invalid input. Please enter an integer." << std::endl;
            }
        }
        else
        {
            size = 8;
            break;
        }
    }

    int** board = new int* [size];
    for (int i = 0; i < size; ++i) board[i] = new int[size]();

    bool* usedRows = new bool[size]();
    bool* usedDiag1 = new bool[2 * size - 1]();
    bool* usedDiag2 = new bool[2 * size - 1]();
    int solutions = 0;

    auto start = std::chrono::steady_clock::now();
    solve(board, 0, usedRows, usedDiag1, usedDiag2, size, solutions);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Solutions found: " << solutions << std::endl;
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    for (int i = 0; i < size; ++i) delete[] board[i];
    delete[] board;
    delete[] usedRows;
    delete[] usedDiag1;
    delete[] usedDiag2;

    return EXIT_SUCCESS;
}