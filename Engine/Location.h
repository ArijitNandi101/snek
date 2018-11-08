#pragma once
struct Location {
	void add(const Location& loc) {
		this->x += loc.x;
		this->y += loc.y;
	}
	bool operator==(const Location& loc) const {
		return (x == loc.x && y == loc.y);
	}
	int x;
	int y;
};