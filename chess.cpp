#include "chess.h"

using namespace std;

int Board::count = 0;
int Board::countForKing = 0;
int Board::countForRook = 0;

Square::Square()
{
	this->color = NONE;
	this->piece = EMPTY;
	this->countForPawn = 0;
}

Piece Square::getPiece()
{
	return piece;
}

Color Square::getColor()
{
	return color;
}

Color Board::squareindex(int x, int y)
{
	return square[x][y].getColor();
}

int Square::getCFP()
{
	return countForPawn;
}

void Board::start()
{
	setBoard();
	string x;
	string y;
	int x1, x2, y1, y2;
	cout << " The game starts with the white player" << endl;
	cout << " Enter the coordinates for the movement of the figures" << endl;
	while (0 != 10)
	{
		cin >> x >> y;
		x1 = x[0] - 96;
		y1 = x[1] - 48;
		x2 = y[0] - 96;
		y2 = y[1] - 48;
		if (whichPlayers(x1, y1))
		{
			muevFigur(x1, y1, x2, y2);
		}
		else
		{
			cout << " The entered coordinate is incorrect" << endl;
			cout << " Try again" << endl;
		}
	}
}

void Square::setCFP(int x)
{
	this->countForPawn = x;
}

void Square::setSpace(Square *space)
{
	color = space->color;
	piece = space->piece;
}

void Square::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

void Square::setPieceAndColor(Piece pc, Color cl)
{
	piece = pc;
	color = cl;
}

void Square::setPiece(Piece pc)
{
	piece = pc;
}

void Board::setBoard()
{
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[0][1].setPieceAndColor(KNIGHT, WHITE);
	square[0][2].setPieceAndColor(BISHOP, WHITE);
	square[0][3].setPieceAndColor(QUEEN, WHITE);
	square[0][4].setPieceAndColor(KING, WHITE);
	square[0][5].setPieceAndColor(BISHOP, WHITE);
	square[0][6].setPieceAndColor(KNIGHT, WHITE);
	square[0][7].setPieceAndColor(ROOK, WHITE);

	square[7][0].setPieceAndColor(ROOK, BLACK);
	square[7][1].setPieceAndColor(KNIGHT, BLACK);
	square[7][2].setPieceAndColor(BISHOP, BLACK);
	square[7][3].setPieceAndColor(QUEEN, BLACK);
	square[7][4].setPieceAndColor(KING, BLACK);
	square[7][5].setPieceAndColor(BISHOP, BLACK);
	square[7][6].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);

	for (int i = 0; i < 8; i++)
	{
		square[1][i].setPieceAndColor(PAWN, WHITE);
		arrPawn[i] = new Pawn(WHITE, 0, 1, i);
		square[6][i].setPieceAndColor(PAWN, BLACK);
		arrPawn[i + 8] = new Pawn(BLACK, 0, 6, i);
	}

	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[i][j].setPieceAndColor(EMPTY, NONE);
	}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}

	printBoard();
}

void Board::printBoard()
{
	KingPossiblyMuve.clear();
	betweenfigures.clear();
	system("clear");
	cout << "   a   b   c   d   e   f   g   h" << endl;
	cout << "  --------------------------------" << endl;
	for (int i = 1; i <= 8; ++i)
	{
		cout << i << "|";
		for (int j = 1; j <= 8; ++j)
		{
			Piece piece = square[i - 1][j - 1].getPiece();
			Color color = square[i - 1][j - 1].getColor();
			switch (piece)
			{
			case KING:
				(color == WHITE) ? cout << " \u2654 "
							<< "|"
						 : cout << " \u265A "
							<< "|";
				break;
			case QUEEN:
				(color == WHITE) ? cout << " \u2655 "
							<< "|"
						 : cout << " \u265B "
							<< "|";
				break;
			case KNIGHT:
				(color == WHITE) ? cout << " \u2658 "
							<< "|"
						 : cout << " \u265E "
							<< "|";
				break;
			case BISHOP:
				(color == WHITE) ? cout << " \u2657 "
							<< "|"
						 : cout << " \u265D "
							<< "|";
				break;
			case ROOK:
				(color == WHITE) ? cout << " \u2656 "
							<< "|"
						 : cout << " \u265C "
							<< "|";
				break;
			case PAWN:
				(color == WHITE) ? cout << " \u2659 "
							<< "|"
						 : cout << " \u265F "
							<< "|";
				break;
			case EMPTY:
				cout << "   "
				     << "|";
				break;

			default:
				break;
			}
		}

		cout << i << endl;
		cout << "  --------------------------------" << endl;
	}
	cout << "   a   b   c   d   e   f   g   h" << endl;
}

void Board::muevFigur(int x1, int y1, int x2, int y2)
{

	if (x1 < 0 || x1 > 8 || y1 < 0 || y1 > 8 ||
	    x2 < 0 || x2 > 8 || y2 < 0 || y2 > 8)
	{
		cout << " The entered coordinate is incorrect" << endl;
		cout << " Try again" << endl;
	}
	else
	{

		Piece p = square[y1 - 1][x1 - 1].getPiece();
		Color c = square[y1 - 1][x1 - 1].getColor();
		switch (p)
		{
		case BISHOP:
			if (BishopMuve(x1, y1, x2, y2))
			{
				Piece tmpPiece = square[y2 - 1][x2 - 1].getPiece();
				Color tmpColor = square[y2 - 1][x2 - 1].getColor();
				square[y2 - 1][x2 - 1] = square[y1 - 1][x1 - 1];
				square[y1 - 1][x1 - 1].setPieceAndColor(EMPTY, NONE);
				if (to_check(c))
				{

					printBoard();
					check(x2 - 1, y2 - 1);
					++count;
				}
				else
				{
					square[y1 - 1][x1 - 1] = square[y2 - 1][x2 - 1];
					square[y2 - 1][x2 - 1].setPieceAndColor(tmpPiece, tmpColor);
					cout << " The entered coordinate is incorrect" << endl;
					cout << " Try again" << endl;
				}
			}
			else
			{
				cout << " The entered coordinate is incorrect" << endl;
				cout << " Try again" << endl;
			}
			break;

		case ROOK:
			if (RookMuve(x1, y1, x2, y2))
			{
				Piece tmpPiece = square[y2 - 1][x2 - 1].getPiece();
				Color tmpColor = square[y2 - 1][x2 - 1].getColor();
				square[y2 - 1][x2 - 1] = square[y1 - 1][x1 - 1];
				square[y1 - 1][x1 - 1].setPieceAndColor(EMPTY, NONE);
				if (to_check(c))
				{

					printBoard();
					check(x2 - 1, y2 - 1);
					++count;
					++countForRook;
				}
				else
				{
					square[y1 - 1][x1 - 1] = square[y2 - 1][x2 - 1];
					square[y2 - 1][x2 - 1].setPieceAndColor(tmpPiece, tmpColor);
					cout << " The entered coordinate is incorrect" << endl;
					cout << " Try again" << endl;
				}
			}
			else
			{

				cout << " The entered coordinate is incorrect" << endl;
				cout << " Try again" << endl;
			}
			break;

		case KING:
			if (KingMuve(x1, y1, x2, y2))
			{
				square[y2 - 1][x2 - 1] = square[y1 - 1][x1 - 1];
				square[y1 - 1][x1 - 1].setPieceAndColor(EMPTY, NONE);
				printBoard();
				check(x2 - 1, y2 - 1);
				++count;
				++countForKing;
				//cout<<countForKing;
			}
			else
			{
				cout << " The entered coordinate is incorrect" << endl;
				cout << " Try again" << endl;
			}
			break;

		case QUEEN:
			if (QueenMuve(x1, y1, x2, y2))
			{
				Piece tmpPiece = square[y2 - 1][x2 - 1].getPiece();
				Color tmpColor = square[y2 - 1][x2 - 1].getColor();
				square[y2 - 1][x2 - 1] = square[y1 - 1][x1 - 1];
				square[y1 - 1][x1 - 1].setPieceAndColor(EMPTY, NONE);
				if (to_check(c))
				{

					printBoard();
					check(x2 - 1, y2 - 1);
					++count;
				}
				else
				{
					square[y1 - 1][x1 - 1] = square[y2 - 1][x2 - 1];
					square[y2 - 1][x2 - 1].setPieceAndColor(tmpPiece, tmpColor);
					cout << " The entered coordinate is incorrect" << endl;
					cout << " Try again" << endl;
				}
			}
			else
			{
				cout << " The entered coordinate is incorrect" << endl;
				cout << " Try again" << endl;
			}
			break;

		case KNIGHT:
			if (KnightMuve(x1, y1, x2, y2))
			{
				Piece tmpPiece = square[y2 - 1][x2 - 1].getPiece();
				Color tmpColor = square[y2 - 1][x2 - 1].getColor();
				square[y2 - 1][x2 - 1] = square[y1 - 1][x1 - 1];
				square[y1 - 1][x1 - 1].setPieceAndColor(EMPTY, NONE);
				if (to_check(c))
				{

					printBoard();
					check(x2 - 1, y2 - 1);
					++count;
				}
				else
				{
					square[y1 - 1][x1 - 1] = square[y2 - 1][x2 - 1];
					cout << " The entered coordinate is incorrect" << endl;
					cout << " Try again" << endl;
				}
			}
			else
			{
				cout << " The entered coordinate is incorrect" << endl;
				cout << " Try again" << endl;
			}
			break;

		case PAWN:

			if (PawnMuve(x1, y1, x2, y2))
			{
				Piece tmpPiece = square[y2 - 1][x2 - 1].getPiece();
				Color tmpColor = square[y2 - 1][x2 - 1].getColor();
				square[y2 - 1][x2 - 1] = square[y1 - 1][x1 - 1];
				square[y1 - 1][x1 - 1].setPieceAndColor(EMPTY, NONE);
				if (to_check(c))
				{
					for (int i = 0; i < 16; ++i)
					{
						if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
						    arrPawn[i]->get_Pindex2() == x1 - 1)
						{
							arrPawn[i]->set_Index(y2 - 1, x2 - 1);
						}
					}

					if (y2 == 8 || y2 == 1)
					{
						int x = 0;
						cout << "Select the figure number"
						     << "\n"
						     << "Queen  = 1 :"
						     << "\n"
						     << "Knight = 2 :"
						     << "\n"
						     << "Bishop = 3 :"
						     << "\n"
						     << "Rook   = 4 :" << endl;
						cin >> x;
						switch (x)
						{
						case 1:
							square[y2 - 1][x2 - 1].setPiece(QUEEN);
							break;
						case 2:
							square[y2 - 1][x2 - 1].setPiece(KNIGHT);
							break;
						case 3:
							square[y2 - 1][x2 - 1].setPiece(BISHOP);
							break;
						case 4:
							square[y2 - 1][x2 - 1].setPiece(ROOK);
							break;

						default:
							break;
						}
					}

					printBoard();
					check(x2 - 1, y2 - 1);
					++count;
				}
				else
				{
					square[y1 - 1][x1 - 1] = square[y2 - 1][x2 - 1];
					square[y2 - 1][x2 - 1].setPieceAndColor(tmpPiece, tmpColor);
					cout << " The entered coordinate is incorrect" << endl;
					cout << " Try again" << endl;
				}
			}
			else
			{
				cout << " The entered coordinate is incorrect" << endl;
				cout << " Try again" << endl;
			}
			break;
		case EMPTY:
			cout << " The entered coordinate is incorrect" << endl;
			cout << " Try again" << endl;
			break;

		default:
			break;
		}
	}
}

void Board::set_betweenfigures(int x1, int y1, int x2, int y2)
{
	betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
	//for Rook
	if (x1 == x2 || y1 == y2)
	{
		if ((x1 == x2) && (y1 < y2))
		{
			int i = (y2 - y1) - 1;
			for (int k = 0; k < i; ++k)
			{
				++y1;
				if (y1 == y2)
				{
					return;
				}
				betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
			}
		}

		if ((x1 == x2) && (y1 > y2))
		{
			int i = (y1 - y2) - 1;
			for (int k = 0; k < i; ++k)
			{
				--y1;
				if (y1 == y2)
				{
					return;
				}
				betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
			}
		}

		if ((y1 == y2) && (x1 < x2))
		{
			int i = (x2 - x1) - 1;
			for (int k = 0; k < i; ++k)
			{
				++x1;
				if (y1 == y2)
				{
					return;
				}
				betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
			}
		}

		if ((y1 == y2) && (x1 > x2))
		{
			int i = (x1 - x2) - 1;
			for (int k = 0; k < i; ++k)
			{
				--x1;
				if (y1 == y2)
				{
					return;
				}
				betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
			}
		}
	}

	// for Bishop
	if (square[y1 - 1][x1 - 1].getColor() != square[y2 - 1][x2 - 1].getColor())
	{
		if (x1 > x2 && y1 < y2)
		{
			int i = x1 - x2;
			i -= 1;
			for (int k = 0; k < i; ++k)
			{
				--x1;
				++y1;
				betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
			}
		}
		if (x1 < x2 && y1 > y2)
		{
			int i = x2 - x1;
			i -= 1;
			for (int k = 0; k < i; ++k)
			{
				++x1;
				--y1;
				betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
			}
		}
		if (x1 < x2 && y1 < y2)
		{
			int i = x2 - x1;
			i -= 1;
			for (int k = 0; k < i; ++k)
			{
				++x1;
				++y1;
				betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
			}
		}
		if (x1 > x2 && y1 > y2)
		{
			int i = x1 - x2;
			i -= 1;
			for (int k = 0; k < i; ++k)
			{
				--x1;
				--y1;
				betweenfigures.push_back(make_pair(y1 - 1, x1 - 1));
			}
		}
	}
	return;
}

void Board::set_KingPossiblyMuve(int x, int y)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; j++)
		{
			if (KingMuve(y + 1, x + 1, i + 1, j + 1))
			{
				KingPossiblyMuve.push_back(make_pair(i, j));
			}
		}
	}
}

void Board::CheckMate(Color color)
{
	//cout<<"funkciai skizb"<<endl;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (square[i][j].getColor() == color)
			{
				Piece pice = square[i][j].getPiece();
				switch (pice)
				{

				case BISHOP:
					for (int k = 0; k < betweenfigures.size(); ++k)
					{
						if (BishopMuve(j + 1, i + 1, betweenfigures[k].second + 1, betweenfigures[k].first + 1))
						{
							cout<<"bishop"<<endl;
							return;
						}
					}

					break;

				case ROOK:
					for (int k = 0; k < betweenfigures.size(); ++k)
					{
						if (RookMuve(j + 1, i + 1, betweenfigures[k].second + 1, betweenfigures[k].first + 1))
						{
							cout<<"rook"<<endl;
							return;
						}
					}

				case QUEEN:
					for (int k = 0; k < betweenfigures.size(); ++k)
					{
						if (QueenMuve(j + 0, i + 1, betweenfigures[k].second + 1, betweenfigures[k].first + 1))
						{
							//cout<<betweenfigures[k].first <<betweenfigures[k].second<<endl;
							//cout<<"queen"<<endl;
							return;
						}
					}

					break;

				case KNIGHT:
					for (int k = 0; k < betweenfigures.size(); ++k)
					{
						if (KnightMuve(j + 1, i + 1, betweenfigures[k].second + 1, betweenfigures[k].first + 1))
						{
							cout<<"dzi"<<endl;
							return;
						}
					}

					break;

				case PAWN:
					for (int k = 0; k < betweenfigures.size(); ++k)
					{
						if (PawnMuve(j + 1, i + 1, betweenfigures[k].second + 1, betweenfigures[k].first + 1))
						{
							cout<<"zinvor"<<endl;
							cout<<square[betweenfigures[k].first + 1][betweenfigures[k].second + 1].getPiece();
							return;
						}
					}

					break;

				default:
					break;
				}
			}
		}
	}
	cout<<"tagavor"<<endl;
	if (KingPossiblyMuve.empty())
	{  // cout<<"checkMate";
		if (color == WHITE)
		{
			cout << " CheckMate" << endl;
			cout << " Congratulations Black player won ";
		}
		else
		{
			cout << " Congratulations White player won ";
		}
	}
}

bool Board::whichPlayers(int x1, int y1)
{
	if (count % 2 == 0)
	{
		if (square[y1 - 1][x1 - 1].getColor() == BLACK)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (count % 2 != 0)
	{
		if (square[y1 - 1][x1 - 1].getColor() == WHITE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Board::BishopMuve(int x1, int y1, int x2, int y2)
{
	if (square[y1 - 1][x1 - 1].getColor() != square[y2 - 1][x2 - 1].getColor())
	{
		if (x1 > x2 && y1 < y2)
		{
			int i = x1 - x2;
			int j = x1, r = y1;
			i -= 1;
			for (int k = 0; k < i; ++k)
			{
				--x1;
				++y1;
				if (square[y1 - 1][x1 - 1].getColor() != NONE)
				{
					return false;
				}
				j = x1;
				r = y1;
			}
			if (j == (x2 + 1) && r == (y2 - 1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (x1 < x2 && y1 > y2)
		{
			int i = x2 - x1;
			i -= 1;
			int j = x1;
			int r = y1;
			for (int k = 0; k < i; ++k)
			{
				++x1;
				--y1;
				if (square[y1 - 1][x1 - 1].getColor() != NONE)
				{
					return false;
				}
				j = x1;
				r = y1;
			}

			if (j == (x2 - 1) && r == (y2 + 1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (x1 < x2 && y1 < y2)
		{
			int i = x2 - x1;
			i -= 1;
			int j = x1;
			int r = y1;
			for (int k = 0; k < i; ++k)
			{
				++x1;
				++y1;
				if (square[y1 - 1][x1 - 1].getColor() != NONE)
				{
					return false;
				}
				j = x1;
				r = y1;
			}

			if (j == (x2 - 1) && r == (y2 - 1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (x1 > x2 && y1 > y2)
		{
			int i = x1 - x2;
			i -= 1;
			int j = x1;
			int r = y1;
			for (int k = 0; k < i; ++k)
			{
				--x1;
				--y1;
				if (square[y1 - 1][x1 - 1].getColor() != NONE)
				{
					return false;
				}
				j = x1;
				r = y1;
			}
			if (j == (x2 + 1) && r == (y2 + 1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		if (x1 == x2 || y1 == y2)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Board::RookMuve(int x1, int y1, int x2, int y2)
{
	if (square[y1 - 1][x1 - 1].getColor() != square[y2 - 1][x2 - 1].getColor())
	{
		if (x1 == x2 || y1 == y2)
		{
			if ((x1 == x2) && (y1 < y2))
			{
				int i = (y2 - y1) - 1;
				for (int k = 0; k < i; ++k)
				{
					++y1;
					if (square[y1 - 1][x1 - 1].getColor() != NONE)
					{
						return false;
					}
					if (y1 == y2)
					{
						return true;
					}
				}
			}

			if ((x1 == x2) && (y1 > y2))
			{
				int i = (y1 - y2) - 1;
				for (int k = 0; k < i; ++k)
				{
					--y1;
					if (square[y1 - 1][x1 - 1].getColor() != NONE)
					{
						return false;
					}
					if (y1 == y2)
					{
						return true;
					}
				}
			}

			if ((y1 == 22) && (x1 < x2))
			{
				int i = (x2 - x1) - 1;
				for (int k = 0; k < i; ++k)
				{
					++x1;
					if (square[y1 - 1][x1 - 1].getColor() != NONE)
					{
						return false;
					}
					if (y1 == y2)
					{
						return true;
					}
				}
			}

			if ((y1 == y2) && (x1 > x2))
			{
				int i = (x1 - x2) - 1;
				for (int k = 0; k < i; ++k)
				{
					--x1;
					if (square[y1 - 1][x1 - 1].getColor() != NONE)
					{
						return false;
					}
					if (y1 == y2)
					{
						return true;
					}
				}
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool Board::QueenMuve(int x1, int y1, int x2, int y2)
{
	cout<<square[y1 - 1][x1 - 1].getPiece() << "hajord="<<square[y2 - 1][x2 - 1].getPiece()<<endl;

	if (square[y1 - 1][x1 - 1].getColor() != square[y2 - 1][x2 - 1].getColor())
	{
		if ((x1 == x2) || (y1 == y2))
		{
			return RookMuve(x1, y1, x2, y2);
		}
		else
		{
			return BishopMuve(x1, y1, x2, y2);
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Board::PawnMuve(int x1, int y1, int x2, int y2)
{
	if (square[y1 - 1][x1 - 1].getColor() == WHITE)
	{
		if (square[y1 - 1][x1 - 1].getColor() != square[y2 - 1][x2 - 1].getColor())
		{
			int f = y2 - y1;
			int k = x2 - x1;
			if (((f == 1) && (k == -1)) || ((f == 1) && (k == 1)) ||
			    ((k == 0) && (f == 1)) || ((k == 0) && (f == 2)))
			{
				if (((f == -1) && (k == 1)) || ((f == 1) && (k == 1)))
				{
					if (square[y2 - 1][x2 - 1].getColor() == BLACK)
					{
						for (int i = 0; i < 16; ++i)
						{
							if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
							    arrPawn[i]->get_Pindex2() == x1 - 1)
							{
								arrPawn[i]->set_Pcount(1);
							}
						}
						return true;
					}
					else
					{
						return false;
					}
				}

				if ((k == 0) && (f == 2) || ((k == 0) && (f == 1)))
				{
					if (square[y2 - 1][x2 - 1].getColor() == NONE)
					{
						if ((k == 0) && (f == 1))
						{
							for (int i = 0; i < 16; ++i)
							{
								if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
								    arrPawn[i]->get_Pindex2() == x1 - 1)
								{
									arrPawn[i]->set_Pcount(1);
								}
							}
							return true;
						}
					}
					else
					{
						return false;
					}
					for (int i = 0; i < 16; ++i)
					{
						if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
						    arrPawn[i]->get_Pindex2() == x1 - 1)
						{
							if (arrPawn[i]->get_pcount() == 0)
							{
								arrPawn[i]->set_Pcount(1);
								return true;
							}
							else
							{
								return false;
							}
						}
					}
				}

				for (int i = 0; i < 16; ++i)
				{
					if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
					    arrPawn[i]->get_Pindex2() == x1 - 1)
					{
						arrPawn[i]->set_Pcount(1);
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (square[y1 - 1][x1 - 1].getColor() != square[y2 - 1][x2 - 1].getColor())
		{
			int f = y2 - y1;
			int k = x2 - x1;
			if (((f == -1) && (k == 1)) || ((f == -1) && (k == -1)) ||
			    ((k == 0) && (f == -1)) || ((k == 0) && (f == -2)))
			{
				if (((f == -1) && (k == -1)) || ((f == -1) && (k == 1)))
				{
					if (square[y2 - 1][x2 - 1].getColor() == WHITE)
					{
						for (int i = 0; i < 16; ++i)
						{
							if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
							    arrPawn[i]->get_Pindex2() == x1 - 1)
							{
								arrPawn[i]->set_Pcount(1);
							}
						}
						return true;
					}
					else
					{
						return false;
					}
				}

				if ((k == 0) && (f == -2) || ((k == 0) && (f == -1)))
				{
					if (square[y2 - 1][x2 - 1].getColor() == NONE)
					{
						if ((k == 0) && (f == -1))
						{
							for (int i = 0; i < 16; ++i)
							{
								if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
								    arrPawn[i]->get_Pindex2() == x1 - 1)
								{
									arrPawn[i]->set_Pcount(1);
								}
							}
							return true;
						}
					}
					else
					{
						return false;
					}
					for (int i = 0; i < 16; ++i)
					{
						if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
						    arrPawn[i]->get_Pindex2() == x1 - 1)
						{
							if (arrPawn[i]->get_pcount() == 0)
							{

								arrPawn[i]->set_Pcount(1);
								return true;
							}
							else
							{
								return false;
							}
						}
					}
				}

				for (int i = 0; i < 16; ++i)
				{
					if (arrPawn[i]->get_Pindex1() == y1 - 1 &&
					    arrPawn[i]->get_Pindex2() == x1 - 1)
					{
						arrPawn[i]->set_Pcount(1);
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool Board::KnightMuve(int x1, int y1, int x2, int y2)
{
	if (square[y1 - 1][x1 - 1].getColor() != square[y2 - 1][x2 - 1].getColor())
	{
		int p = x1 - x2;
		int q = y1 - y2;
		if ((p == -2 && q == -1) || (p == -2 && q == 1) ||
		    (p == 2 && q == -1) || (p == 2 && q == 1) ||
		    (p == -1 && q == -2) || (p == -1 && q == 2) ||
		    (p == 1 && q == -2) || (p == 1 && q == 2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Board::KingMuve(int x1, int y1, int x2, int y2)
{
	if (square[y1 - 1][x1 - 1].getColor() != square[y2 - 1][x2 - 1].getColor())
	{
		int k = y1 - y2;
		int f = x1 - x2;
		Color color = square[y1 - 1][x1 - 1].getColor();
		if ((f == 1 && k == 1) || (f == -1 && k == -1) || (f == -1 && k == 1) || (f == 1 && k == -1) ||
		    (f == 1 && k == 0) || (f == 0 && k == 1) || (f == -1 && k == 0) || (f == 0 && k == -1))
		{
			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; j++)
				{
					Piece piece = square[i][j].getPiece();
					if (square[i][j].getColor() != color)
					{
						switch (piece)
						{
						case BISHOP:
							if (BishopMuve(j + 1, i + 1, x2, y2))

							{
								return false;
							}

							break;

						case ROOK:
							if (RookMuve(j + 1, i + 1, x2, y2))
							{
								return false;
							}

						case KING:
							if (KingMuve(j + 1, i + 1, x2, y2))
							{
								return false;
							}

							break;

						case QUEEN:
							if (QueenMuve(j + 1, i + 1, x2, y2))
							{
								return false;
							}

							break;

						case KNIGHT:
							if (KnightMuve(j + 1, i + 1, x2, y2))
							{
								return false;
							}

							break;

						case PAWN:

							if (PawnMuve(j + 1, i + 1, x2, y2))
							{
								return false;
							}

							break;

						default:
							break;
						}
					}
				}
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Board::check(int x, int y)
{

	int count = 0;
	Color color = square[y][x].getColor();
	Piece piece = square[y][x].getPiece();
	int z = 0;
	int c = 0;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((square[i][j].getPiece() == KING) && (square[i][j].getColor() != color))
			{
				z = i;
				c = j;

				Color colorForMat = square[z][c].getColor();

				//cout<<square[z][c].getColor()<<"piece= "<<square[z][c].getPiece()<<endl;
				//cout<<z<<c<<endl;
				switch (piece)
				{
				case BISHOP:
					if (BishopMuve(x + 1, y + 1, j + 1, i + 1))

					{
						cout << "check" << endl;
						set_betweenfigures(x + 1, y + 1, j + 1, i + 1);
						set_KingPossiblyMuve(z, c);
						CheckMate(colorForMat);
						count++;
					}

					break;

				case ROOK:
					if (RookMuve(x + 1, y + 1, j + 1, i + 1))
					{
						cout << "check" << endl;
						set_betweenfigures(x + 1, y + 1, j + 1, i + 1);
						set_KingPossiblyMuve(z, c);
						CheckMate(colorForMat);
						count++;
					}

				case KING:
					if (KingMuve(x + 1, y + 1, j + 1, i + 1))
					{
						cout << "check" << endl;
						set_betweenfigures(x + 1, y + 1, j + 1, i + 1);
						set_KingPossiblyMuve(z, c);
						CheckMate(colorForMat);
						count++;
					}

					break;

				case QUEEN:
					if (QueenMuve(x + 1, y + 1, j + 1, i + 1))
					{
						cout << "check" << endl;
						set_betweenfigures(x + 1, y + 1, j + 1, i + 1);
						set_KingPossiblyMuve(z, c);
						CheckMate(colorForMat);
						count++;
					}

					break;

				case KNIGHT:
					if (KnightMuve(x + 1, y + 1, j + 1, i + 1))
					{
						cout << "check" << endl;
						betweenfigures.push_back(make_pair(x, y));
						CheckMate(colorForMat);
						count++;
					}

					break;

				case PAWN:

					if (PawnMuve(x + 1, y + 1, j + 1, i + 1))
					{
						cout << "check" << endl;
						betweenfigures.push_back(make_pair(x, y));
						CheckMate(colorForMat);
						count++;
					}

					break;

				default:
					break;
				}
			}
		}
	}

	return true;
}

bool Board::to_check(Color c)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (square[i][j].getPiece() == KING && square[i][j].getColor() == c)
			{
				for (int k = 0; k < 8; ++k)
				{
					for (int f = 0; f < 8; ++f)
					{
						if (square[k][f].getColor() != c)
						{
							Piece p = square[k][f].getPiece();
							switch (p)
							{

							case BISHOP:
								if (BishopMuve(f + 1, k + 1, j + 1, i + 1))

								{
									return false;
								}

								break;

							case ROOK:
								if (RookMuve(f + 1, k + 1, j + 1, i + 1))
								{
									return false;
								}

							case KING:
								if (KingMuve(f + 1, k + 1, j + 1, i + 1))
								{
									return false;
								}

								break;

							case QUEEN:
								if (QueenMuve(f + 1, k + 1, j + 1, i + 1))
								{
									return false;
								}

								break;

							case KNIGHT:
								if (KnightMuve(f + 1, k + 1, j + 1, i + 1))
								{
									return false;
								}

								break;

							case PAWN:

								if (PawnMuve(f + 1, k + 1, j + 1, i + 1))
								{
									return false;
								}

								break;

							default:
								break;
							}
						}
					}
				}
			}
		}
	}
	return true;
}


int main()
{
	Board a;
	a.start();	
}