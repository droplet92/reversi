#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <sstream>

namespace reversi
{
	constexpr int WINDOW_SCALE = 100;

	struct BoardPosition
	{
		int brow, bcol;

		BoardPosition(const int row = -1, const int col = -1) : brow(row), bcol(col) {}
		BoardPosition(const BoardPosition& copy) : brow(copy.brow), bcol(copy.bcol) {}

		std::string toString() const
		{
			std::stringstream ss;
			ss << '(' << brow << ',' << bcol << ')';
			return ss.str();
		}

		BoardPosition unit() const { return { (brow ? brow / abs(brow) : 0),(bcol ? bcol / abs(bcol) : 0) }; }

		bool onSide(const BoardPosition pos) const
		{
			if (*this == pos) return false;

			const BoardPosition comp = (*this - pos);
			return (comp <= BoardPosition{ 1,1 }) && (comp >= BoardPosition{ -1,-1 });
		}
		bool inBoundary() const { return (*this >= BoardPosition{ 0, 0 }) && (*this <= BoardPosition{ 7, 7 }); }

		inline BoardPosition operator+(const BoardPosition pos) const { return { brow + pos.brow, bcol + pos.bcol }; }
		inline BoardPosition operator-(const BoardPosition pos) const { return { brow - pos.brow, bcol - pos.bcol }; }
		inline BoardPosition operator*(const BoardPosition pos) const { return { brow * pos.brow, bcol * pos.bcol }; }
		inline void operator+=(const BoardPosition pos) { brow += pos.brow; bcol += pos.bcol; }

		friend bool operator!=(const BoardPosition p1, const BoardPosition p2) { return (p1.brow != p2.brow) || (p1.bcol != p2.bcol); }
		friend bool operator<=(const BoardPosition p1, const BoardPosition p2) { return (p1.brow <= p2.brow) && (p1.bcol <= p2.bcol); }
		friend bool operator>=(const BoardPosition p1, const BoardPosition p2) { return (p1.brow >= p2.brow) && (p1.bcol >= p2.bcol); }
		friend bool operator==(const BoardPosition p1, const BoardPosition p2) { return (p1.brow == p2.brow) && (p1.bcol == p2.bcol); }
	};

	struct Position
	{
		int row, col;

		Position(const int row = -1, const int col = -1) : row(row), col(col) {}
		Position(const Position& copy) : row(copy.row), col(copy.col) {}

		sf::Vector2f toVector2D() const { return { static_cast<float>(row), static_cast<float>(col) }; }
		BoardPosition toBoardPosition() const { return { (row / WINDOW_SCALE), (col / WINDOW_SCALE) }; }

		inline Position operator+(const Position pos) const { return { row + pos.row, col + pos.col }; }
		inline Position operator-(const Position pos) const { return { row - pos.row, col - pos.col }; }
		inline Position operator*(const Position pos) const { return { row * pos.row, col * pos.col }; }
		inline void operator+=(const Position pos) { row += pos.row; col += pos.col; }

		friend bool operator!=(const Position p1, const Position p2) { return (p1.row != p2.row) || (p1.col != p2.col); }
		friend bool operator<=(const Position p1, const Position p2) { return (p1.row <= p2.row) && (p1.col <= p2.col); }
		friend bool operator>=(const Position p1, const Position p2) { return (p1.row >= p2.row) && (p1.col >= p2.col); }
		friend bool operator==(const Position p1, const Position p2) { return (p1.row == p2.row) && (p1.col == p2.col); }
	};
}