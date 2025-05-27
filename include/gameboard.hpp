#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP


#include "types.hpp"
#include "utils.hpp"

class GameBoard {
    private:
        std::vector<Cell> grid;
        int width, height;

        int getIndex(int x, int y);

    public:
        GameBoard(int w, int h);
        ~GameBoard();

        const Cell getCell(int x, int y) const;

        void setCell(const Cell& cell);
        void setCellType(cellType type);
        void setCellVisit(bool visited);
        void setCellCost(float cost);
        void setCellHeuristic(float cost);

        void createWallHorizontal(int x, int y, int len);
        void createWallVertical(int x, int y, int len);
        void flipCell(int x, int y);
};


#endif

