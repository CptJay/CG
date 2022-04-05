
#ifndef ENGINE_GEHEEL_H
#define ENGINE_GEHEEL_H


#include "Line2D.h"
#include "easy_image.h"
#include "l_parser.h"

using Lines2D = std::vector<Line2D>;

class Geheel {
    std::set<char> alfabet;
    std::string replacement;
    double angle;
    std::string initiator;
    unsigned int iterations;
    double starting_angle;

public:
    img::EasyImage draw2DLines(const Lines2D &lines, int size);
    Lines2D drawLSystem(const LParser::LSystem2D &l_system);
    std::string replacementfixer(std::string s, unsigned int counter, const LParser::LSystem2D &l_system);
};


#endif //ENGINE_GEHEEL_H
