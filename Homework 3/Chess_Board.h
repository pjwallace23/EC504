#ifndef _chess_board_dac
#define _chess_board_dac

#include <iostream>
#include <ostream>

using namespace std;


class Chess_Board
{
  friend ostream& operator<<(ostream& output, const Chess_Board& CB);
  // needs to be a friend to look at internal data...
  public: 
   	Chess_Board (int N);//
    bool goodMove(int i, int j); // Row i, col j is free from capture from existing queens
	void AddQueen(int i, int j); // add queen at (i,j)
	void RemoveQueen(int i, int j); // remove queen at (i,j)
	int getSize();
	void ClearBoard();
	void Solve(){DFS(0);}
    
  private:
    const static int Nmax = 50;
    int Nsize;
    int A[Nmax][Nmax]; // 0 where there are no queens, 1 where there are queens
	bool DFS(int row);
};

Chess_Board::Chess_Board(int N){  // no queens to start
        if (N > Nmax){
			cout << "Too big of a board " << endl;
			exit(1);
		}
		Nsize = N;
		for (int i = 0;i<N;i++){
			for (int j=0;j<N;j++){
				A[i][j]=0;
			}
		}
}

bool Chess_Board::DFS(int row){  // Add queen to row...
	bool found = false;
	int NN = getSize();
	static int num_queens = 0;
	bool b = false;
	//
	//This is the key function you need to write, which does DFS row by row looking for a placement
	// where previous queens cannot capture the current position.
	// This will use the goodMove function to check whether a queen position can be captured by 
	// queens on the board in previous rows.
	//
	//

	if (num_queens == NN)
	{
		num_queens = 0;
		return true;
	}

	for (int i = 0; i < NN; i++)
	{
		b = goodMove(row, i);
		if (b)
		{
			AddQueen(row, i);
			num_queens++;
			found = DFS(row+1);
			if(found)
			{
				break;
				return found;
			}
			else
			{
				RemoveQueen(row, i);
				num_queens--;
				b = false;
			}

		}
	}

	return found;
	
}

void Chess_Board::AddQueen(int i, int j){
	A[i][j] = 1;
}

void Chess_Board::RemoveQueen(int i, int j){
	A[i][j]=0;
}

bool Chess_Board::goodMove(int irow, int jcol){ // square is not captured by queens...
      int row,col,min;
	  //
	  //  This is the other function you have to create.  It checks whether the square in row irow, column
	  //  jcol can be captured by the existing queens on the board in rows 0 .. irow-1. 
	  //
	  //

	  // check column for queens
	  for (row = 0; row < irow; row++)
	  {
		  if (A[row][jcol] == 1)
		  {
			  return false;
		  }
	  }	 
	  // check diagonals (can't be below irow so only in the rows above, but can be in any column on the diagonal)
	  col = jcol;
	  //row = irow-1;
	  int l_col = col-1;
	  int r_col = col+1;
	  for (row = irow-1; row >= 0 ; row--)
	  {
		// check left diagonal
		  if (l_col >= 0)
		  {
			  if (A[row][l_col] == 1)
			  {
				  return false;
			  }
			  else
			  {
				  l_col--;
			  }
		  }
		// check right diagonal
		  if (r_col < Nsize)
		  {
			  if (A[row][r_col] == 1)
		  	 {
			  	return false;
		     }
			 else
			 {
				r_col++;
			 }
	  	  }
	  }
    return true;
}

int Chess_Board::getSize(){
	return Nsize;
}

void Chess_Board::ClearBoard(){
   for (int i = 0;i<Nsize;i++)
	   for (int j = 0; j<Nsize;j++)
		   A[i][j] = 0;
}

ostream& operator<<(ostream& output, const Chess_Board& CB){

	for (int i =0; i<CB.Nsize;i++){
		for (int j = 0; j<CB.Nsize;j++){
		   output << " " << CB.A[i][j] ;
		}
		output << endl;
	}
	return output;
}

#endif