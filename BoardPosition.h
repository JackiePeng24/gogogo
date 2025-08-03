#pragma once
#include<iostream>

struct BoardPosition {
    int row; 
    int col; 

    BoardPosition(int r = -1, int c = -1) : row(r), col(c) {}

    bool isValid() const {
        return row >= 0 && row < 13 && col >= 0 && col < 15;
    }

    bool operator==(const BoardPosition& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const BoardPosition& other) const {
        return !(*this == other);
    }

    float distance(const BoardPosition& other) const {
        int dr = row - other.row;
        int dc = col - other.col;
        return dr * dr + dc * dc;
    }
}; 
