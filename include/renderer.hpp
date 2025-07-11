#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "types.hpp"
#include "gameboard.hpp"

/**
 * @class Renderer
 * @brief Handles all terminal rendering, including grid display, tooltips, and styled text.
 *
 * The Renderer class manages the output buffer and provides methods to render the game grid,
 * tooltips, progress bars, and styled text to the terminal. It supports ANSI and color output,
 * and maintains frame state for animations and timed tooltips.
 */
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
        void appendTooltip(String title, String text, Styles styles, int duration = 1);

};

#endif