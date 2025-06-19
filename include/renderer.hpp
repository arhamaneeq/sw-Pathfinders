#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "types.hpp"
#include "gameboard.hpp"

class Renderer {
    private:
        using Styles = std::initializer_list<std::string_view>;

        int frame;

        int vw, vh;
        bool colourSupport;
        bool ansiSupport;

        ToolTip tooltip;
        
        std::ostringstream outputBuffer;

        void clearScreen();
        void renderTooltip();
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

        void appendGrid(const Grid& grid); 
        
        void appendLine();
        void appendEmpty();
        void appendProgressBar(float percentProgress); 

        void appendText(std::string txt, Styles styles = {}, bool newLine = true);
        void appendTextCenter(std::string txt, Styles styles = {});
        void appendInput(std::string txt, Styles styles = {});
        void appendTooltip(std::string txt, std::string title, int duration = 50);

};

#endif