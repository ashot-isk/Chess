#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Piece
{
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN,
	EMPTY
};

enum Color
{
	WHITE,
	BLACK,
	NONE
};

class Pawn
{
public:
	Pawn(Color col, int counter, int x1, int y1)
	{
		this->col = col;
		this->counter = counter;
		this->x1 = x1;
		this->y1 = y1;
	}
	void set_Pcount(int counter)
	{
		this->counter = counter;
	}
	void set_Index(int x1, int y1)
	{
		this->x1 = x1;
		this->y1 = y1;
	}
	int get_pcount()
	{
		return this->counter;
	}
	int get_Pindex1() { return this->x1; }
	int get_Pindex2() { return this->y1; }

private:
	Color col;
	int counter, x1, y1;
};

class Square
{
	Piece piece;
	Color color;
	int x, y;
	int countForPawn;

public:
	Square();
	Piece getPiece();
	Color getColor();
	void setCFP(int x);
	int getCFP();
	void setSpace(Square *);
	void setEmpty();
	void setPieceAndColor(Piece, Color);
	void setPiece(Piece);
	void setX(int ex) { x = ex; }
	void setY(int why) { y = why; }
	int getX() { return x; }
	int getY() { return y; }
};

class Board
{
private:
	vector<pair<int, int>> betweenfigures;
	vector<pair<int, int>> KingPossiblyMuve;
	Square square[8][8];
	Color turn = WHITE;
	void printBoard();
	void setBoard();
	void muevFigur(int x1, int y1, int x2, int y2);
	void CheckMate( Color color);
	void set_betweenfigures(int x1, int y1, int x2, int y2);
	void set_KingPossiblyMuve(int x, int y);
	bool check(int x1, int y1, int x2, int y2);
	bool whichPlayers(int x1, int y1);
	bool BishopMuve(int x1, int y1, int x2, int y2);
	bool RookMuve(int x1, int y1, int x2, int y2);
	bool QueenMuve(int x1, int y1, int x2, int y2);
	bool PawnMuve(int x1, int y1, int x2, int y2);
	bool KingMuve(int x1, int y1, int x2, int y2);
	bool KnightMuve(int x1, int y1, int x2, int y2);
	bool check(int x, int y);
	bool to_check(Color c);

public:
	Pawn *arrPawn[16];
	Color squareindex(int x, int y);
	void start();
	static int count,countForRook,countForKing;
};
