#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "types.hpp"


class Renderer {
    private:
        int frame;
        int vw, vh;
        bool colourSupport;
        bool ansiSupport;

        std::ostringstream outputBuffer;

        char full, empty;

        void clearScreen();
    public:
        Renderer(std::pair<int, int> viewport, bool colourSupport, bool ansiSupport); 
        ~Renderer();

        void clear();
        void render();

        int getWidth();
        int getHeight();
        int getColourSupport();
        int getAnsiSupport();

        void testCheckerBoard();

        void appendGrid(); 
        
        void appendLine(); //TODO: define funcs
        void appendText();
        void appendProgressBar(float percentProgress); 
};

#endif