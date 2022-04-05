
#include <algorithm>
#include "Geheel.h"


img::EasyImage Geheel::draw2DLines() {
    double min_x = std::numeric_limits<double>::infinity();
    double min_y = std::numeric_limits<double>::infinity();
    double max_y = -std::numeric_limits<double>::infinity();
    double max_x = -std::numeric_limits<double>::infinity();
    for (auto &line: lines2D) {
        min_x = std::min(min_x, std::min(line.p1.x, line.p2.x));
        min_y = std::min(min_y, std::min(line.p1.y, line.p2.y));
        max_x = std::max(max_x, std::max(line.p1.x, line.p2.x));
        max_y = std::max(max_y, std::max(line.p1.y, line.p2.y));
    }
    double x_afstand = max_x - min_x;
    double y_afstand = max_y - min_y;

    double image_x = size * (x_afstand / std::max(x_afstand, y_afstand));
    double image_y = size * (y_afstand / std::max(x_afstand, y_afstand));

    double schaalfactor = 0.95 * (image_x / x_afstand);

    double dc_x = schaalfactor * ((min_x + max_x) / 2);
    double dc_y = schaalfactor * ((min_y + max_y) / 2);
    double dx = (image_x / 2) - dc_x;
    double dy = (image_y / 2) - dc_y;

    img::EasyImage img(image_x, image_y, backgroundcolor);
    for (auto &line: lines2D) {
        line.p1.schaling(schaalfactor);
        line.p2.schaling(schaalfactor);
        line.p1.optelling(dx, dy);
        line.p2.optelling(dx, dy);
        line.p1.afronden();
        line.p2.afronden();
        img.draw_line(line.p1.x, line.p1.y, line.p2.x, line.p2.y, this->color);
    }
    return img;
}

void Geheel::drawLSystem(const LParser::LSystem2D &l_system, int s, img::Color c, img::Color backg) {
    this->parser = l_system;
    this->color = c;
    this->backgroundcolor = backg;
    this->size = s;
    alfabet = l_system.get_alphabet();
    initiator = l_system.get_initiator(); //start string
    iterations = l_system.get_nr_iterations();
    angle = l_system.get_angle();
    starting_angle = l_system.get_starting_angle();
    unsigned int counter = 0;
    fullString = replacementFixer(initiator, counter, l_system);

    for (auto &fS: fullString) {
        if (fS == '+') {
            starting_angle += angle;
            fixAngle();
        } else if (fS == '-') {
            starting_angle -= angle;
            fixAngle();
        } else if (fS == '('){
            stackBrackets.push_back({lastPos.first, lastPos.second, starting_angle});
        } else if (fS == ')'){
            auto pep = stackBrackets.back();
            stackBrackets.pop_back();
            lastPos.first = pep.at(0);
            lastPos.second = pep.at(1);
            starting_angle = pep.at(2);
        } else {
            makeLine(fS);
        }

    }
}

std::string Geheel::replacementFixer(std::string s, unsigned int counter, const LParser::LSystem2D &l_system) {
    if (counter == iterations) {
        return s;
    } else {
        std::string a;
        counter++;
        for (auto c: s) {
            if (c == '+') {
                a += "+";
            } else if (c == '-') {
                a += "-";
            } else if (c == '(') {
                a += "(";
            } else if (c == ')') {
                a += ")";
            } else {
                a += l_system.get_replacement(c);
            }
        }
        return replacementFixer(a, counter, l_system);
    }
}

void Geheel::fixAngle() {
    while (starting_angle >= 360) {
        starting_angle -= 360;
    }
    while (starting_angle < 0) {
        starting_angle += 360;
    }
}

double Geheel::gradsToRads(double an) const {
    return an * (M_PI / 180);
}

void Geheel::makeLine(const char &c) {
    Line2D line2D;
    line2D.p1.x = lastPos.first;
    line2D.p1.y = lastPos.second;
    line2D.p2.x = line2D.p1.x + std::cos((gradsToRads(starting_angle)));
    line2D.p2.y = line2D.p1.y + std::sin((gradsToRads(starting_angle)));
    std::cout << c << std::endl;
    if (parser.draw(c)) {
        lines2D.push_back(line2D);
        lastPos = {line2D.p2.x, line2D.p2.y};
    }
}

bool Geheel::isInAlphabet(const char &c) const {
    for (auto &a: alfabet) {
        if (c == a) return true;
    }
    return false;
}


