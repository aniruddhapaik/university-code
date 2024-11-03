#include <iostream>
#include <string>
#include <vector>

class PlaceQueens {
 public:
  void setQueens(unsigned qc) {
    this->queens = qc;
    this->chessboard.resize(qc);
    for (auto& row : this->chessboard) {
      row.resize(qc, 0);
    }

    this->initialSetup();
    this->buildStateSpaceTree(0, 1);
  }

  const void printBoard() const {
    size_t nthqueen = 1;
    for (auto& row : this->chessboard) {
      for (auto& cell : row) {
        if (cell == 0) {
          std::cout << ". ";
        } else {
          std::cout << "Q ";
        }
      }
      std::cout << "| Queen #" << nthqueen << std::endl;
      nthqueen++;
    }
  }

 private:
  void initialSetup() {
    this->rowoccupied.clear();
    this->coloccupied.clear();

    this->rowoccupied.resize(this->queens, false);
    this->coloccupied.resize(this->queens, false);
  }

  void buildStateSpaceTree(size_t row, size_t nthqueen) {
    if (row == this->queens) {
      std::cout << "Solution: " << ++this->solutionscounter << std::endl;
      this->printBoard();
      std::cout << std::string(2 * this->queens, '-') << "+\n" << std::endl;
      return;
    }

    for (size_t col = 0; col < this->queens; col++) {
      if (this->checkValidity(row, col)) {
        this->chessboard[row][col] = nthqueen;
        this->rowoccupied[row] = true;
        this->coloccupied[col] = true;

        this->buildStateSpaceTree(row + 1, nthqueen + 1);

        this->chessboard[row][col] = 0;
        this->rowoccupied[row] = false;
        this->coloccupied[col] = false;
      }
    }
  }

  bool checkValidity(size_t row, size_t col) {
    if (this->rowoccupied[row]) {
      return false;
    }
    if (this->coloccupied[col]) {
      return false;
    }

    size_t i = row;
    size_t j = col;
    for (; i >= 0 and j >= 0 and i < this->queens and j < this->queens;
         i--, j--) {
      if (this->chessboard[i][j] > 0) {
        return false;
      }
    }

    i = row;
    j = col;
    for (; i >= 0 and j < this->queens and i < this->queens; i--, j++) {
      if (this->chessboard[i][j] > 0) {
        return false;
      }
    }

    return true;
  }

 private:
  size_t queens = 0;
  size_t solutionscounter = 0;
  std::vector<std::vector<size_t>> chessboard;

  std::vector<bool> rowoccupied;
  std::vector<bool> coloccupied;
};

int main() {
  PlaceQueens board;
  size_t numberofqueens = 8;
  std::cout << "** " << numberofqueens << " Queens Problem Solutions **\n";
  std::cout << "=================================\n";
  board.setQueens(numberofqueens);

  return 0;
}

// This was to find the first solution only:
/*
bool buildStateSpaceTree(size_t row, size_t nthqueen) {
  if (row == this->queens) {
    return true;
  }

 for (size_t col = 0; col < this->queens; col++) {
   if (this->checkValidity(row, col)) {
     this->chessboard[row][col] = nthqueen;
     this->rowoccupied[row] = true;
     this->coloccupied[col] = true;

     if (this->buildStateSpaceTree(row + 1, nthqueen + 1)) {
       return true;
     } else {
       this->chessboard[row][col] = 0;
       this->rowoccupied[row] = false;
       this->coloccupied[col] = false;

       continue;
     }
   } else {
     continue;  // just for clarity
   }
 }

 return false;
}
*/