#include <iostream>
#include <sstream>
#include "types.hpp"

class Renderer {
    private:
        size_t frame;
        dims viewport;
        bool colourSupport;
        bool ansiSupport;

        std::ostringstream outputBuffer;
    public:
        Renderer(dims viewport, bool colourSupport, bool ansiSupport); 
        ~Renderer();

        void clear();
        void render();

        void renderGrid(); //TODO: define gameboard object;
        
        void renderLine();
        void renderText();
        void renderProgressBar(float percentProgress); 
};