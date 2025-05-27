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
    public:
        Renderer(std::pair<int, int> viewport, bool colourSupport, bool ansiSupport); 
        ~Renderer();

        void clear();
        void render();

        void renderGrid(); //TODO: define gameboard object;
        
        void renderLine();
        void renderText();
        void renderProgressBar(float percentProgress); 
};

#endif