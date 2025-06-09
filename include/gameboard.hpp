#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP


#include "types.hpp"
#include "utils.hpp"

class Grid {
    private:
        std::vector<Cell> grid;
        int width, height;

        int getIndex(const Coord& P) const;

    public:
        Grid(std::pair<int, int> wd);
        ~Grid();

        const Cell&   getCell(const Coord& P) const;

        int getWidth() const;
        int getHeight() const;

        void          setCell(const Coord& P, const Cell& cell);
        void      setCellType(const Coord& P, cellType type);
        void     setCellVisit(const Coord& P, bool visited);
        void      setCellCost(const Coord& P, float cost);
        void setCellHeuristic(const Coord& P, float cost);

        class Configurator {
            private:
                Grid* grid;
            public:
                Configurator(Grid* b);

                void createWallHorizontal(const Coord& P, int len);
                void   createWallVertical(const Coord& P, int len);
                void         createWallAt(const Coord& P);
                void         createTypeAt(const Coord& P, cellType type);

                void        createEmptyAt(const Coord& P);
         };

        friend class Configurator;
        Configurator config;
};



#endif

