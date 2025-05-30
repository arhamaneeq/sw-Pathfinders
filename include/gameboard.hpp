#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP


#include "types.hpp"
#include "utils.hpp"

class GameBoard {
    private:
        std::vector<Cell> grid;
        int width, height;

        int getIndex(int x, int y) const;

    public:
        GameBoard(std::pair<int, int> wd);
        ~GameBoard();

        const Cell&   getCell(int x, int y) const;
        int getWidth() const;
        int getHeight() const;

        void          setCell(int x, int y, const Cell& cell);
        void      setCellType(int x, int y, cellType type);
        void     setCellVisit(int x, int y, bool visited);
        void      setCellCost(int x, int y, float cost);
        void setCellHeuristic(int x, int y, float cost);



        class Configurator {
            private:
                GameBoard* board;
            public:
                Configurator(GameBoard* b);

                void createWallHorizontal(int x, int y, int len);
                void   createWallVertical(int x, int y, int len);
                void         createWallAt(int x, int y);

                void        createEmptyAt(int x, int y);
         };

        friend class Configurator;
        Configurator config;
};



#endif

