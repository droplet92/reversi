#pragma once
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
#include <memory>
#include "Stone.hpp"

template <size_t NROW, size_t NCOL>
class Board
{
public:
	using row = std::array<Stone*, NROW>;

public:
	virtual ~Board() {}
	virtual std::vector<std::weak_ptr<Stone>> getPlacables() const = 0;
	virtual uint32_t getScore(const uint32_t aiPlayerType) const = 0;
	virtual uint32_t issuperior(const uint32_t aiPlayerType) const = 0;
	virtual bool isover() const = 0;

	virtual void put(const uint32_t type, const Stone& s) = 0;
	virtual void retract(const Stone& s) = 0;
};
