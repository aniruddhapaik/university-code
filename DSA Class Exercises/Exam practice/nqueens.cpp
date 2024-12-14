#include <iostream>
#include <vector>

class Board {
  std::vector<std::vector<size_t>> newboard;
  std::vector<bool> columnoccupied;
  size_t maxq;
  size_t solutioncounter = 0;

public:
  Board(size_t nqueens) {
    this->maxq = nqueens;
    this->newboard.resize(this->maxq);
    for(auto& row: this->newboard) {
      row.resize(this->maxq);
    }
    this->columnoccupied.resize(this->maxq);
    this->placeQueens(0, this->newboard, this->columnoccupied);
  }

private:
  void placeQueens(size_t row, std::vector<std::vector<size_t>> board, std::vector<bool> coloccupied) {
    if (row < this->maxq) {
      for (size_t col = 0; col < this->maxq; col++) {
        if (not coloccupied[col]) {
          size_t br = row; size_t bc = col;
          bool validcell = true;
          for(; br >= 0 and br < this->maxq and bc >= 0 and bc < this->maxq; br--, bc--) {
            if (board[br][bc] == 1) {
              validcell = false;
              break;
            }
          }

          size_t fr = row; size_t fc = col;
          for(; fr >= 0 and fr < this->maxq and fc >= 0 and fc < this->maxq; fr--, fc++) {
            if (board[fr][fc] == 1) {
              validcell = false;
              break;
            }
          }

          if (validcell) {
            board[row][col] = 1;
            coloccupied[col] = true;
            size_t nextrow = row+1;
            placeQueens(nextrow, board, coloccupied);
            board[row][col] = 0;
            coloccupied[col] = false;
          }
        }
      }
    } else {
      this->printBoard(board);
    }
  }

  const void printBoard(std::vector<std::vector<size_t>>& board) {
    this->solutioncounter++; size_t queencount = 0;
    std::cout << "Solution " << this->solutioncounter << std::endl;
    
    for (auto& row : board) {
      for (auto& cell : row) {
        if (cell) {
          std::cout << "Q ";
        } else {
          std::cout << ". ";
        } 
      }
      queencount++;
      std::cout << "| Queen #" << queencount <<  std::endl;
    }
    std::cout << std::string(this->maxq*2, '-') << "+\n" << std::endl;
  }
};

int main(int argc, char* argv[]) {
  try {
    if (argc == 2) {
      Board* board = new Board(std::stoul(argv[1]));
    } else { throw 1; }
  } catch (int) {
    std::cout << "Exception occured: Enter a valid number of queens while running the executable" << std::endl;
    std::cout << "Example:  .\\nqueens.exe 4" << std::endl;
  }

  return 0;
}