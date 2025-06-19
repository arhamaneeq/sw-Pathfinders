#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "types.hpp"
#include "gameboard.hpp"

class Renderer {
    private:
        using Styles = std::initializer_list<std::string_view>;
        using String = std::string;

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

        void appendText(String txt, Styles styles = {}, bool newLine = true);
        void appendTextCenter(String txt, Styles styles = {});
        void appendInput(String txt, Styles styles = {});
        void appendTooltip(String txt, String title, int duration = 50);

};

#endif