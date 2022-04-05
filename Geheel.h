
#ifndef ENGINE_GEHEEL_H
#define ENGINE_GEHEEL_H


#include "Line2D.h"
#include "easy_image.h"
#include "l_parser.h"
#include <math.h>

using Lines2D = std::vector<Line2D>;

class Geheel {
private:
    std::set<char> alfabet;
    std::string replacement;
    double angle;
    std::string initiator;
    unsigned int iterations;
    double starting_angle;
    std::string fullString;
    int size;
    Lines2D lines2D;
    std::pair<double, double> lastPos = {0,0};
    img::Color color;
    img::Color backgroundcolor;

    void fixAngle();
    double gradsToRads(double an) const;
    void makeLine(const char &c);
    bool isInAlphabet(const char &c) const;
public:
    void drawLSystem(const LParser::LSystem2D &l_system, int s, img::Color c, img::Color backg);
    img::EasyImage draw2DLines();
    std::string replacementFixer(std::string s, unsigned int counter, const LParser::LSystem2D &l_system);


};


#endif //ENGINE_GEHEEL_H
