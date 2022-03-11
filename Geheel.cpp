//
// Created by yassir on 09.03.22.
//

#include <algorithm>
#include "Geheel.h"

img::EasyImage Geheel::draw2DLines(const Lines2D &lines, int size) {
    for (auto line : lines){
        xcoordinaten.push_back(line.p1.x);
        xcoordinaten.push_back(line.p2.x);
        ycoordinaten.push_back(line.p1.y);
        ycoordinaten.push_back(line.p2.y);
    }
    auto [min_x, max_x] = std::minmax_element(std::begin(xcoordinaten), std::end(xcoordinaten));
    auto [min_y, max_y] = std::minmax_element(std::begin(ycoordinaten), std::end(ycoordinaten));

    double x_afstand = *max_x - *min_x;
    double y_afstand = *max_y - *min_y;

    double image_x = size * (x_afstand / std::max(x_afstand, y_afstand));
    double image_y = size * (y_afstand / std::max(x_afstand, y_afstand));

    double schaalfactor = 0.95 * (image_x / x_afstand);

    double dc_x = schaalfactor * ((*min_x + *max_x)/2);
    double dc_y = schaalfactor * ((*min_y + *max_y)/2);
    double dx = (image_x / 2) - dc_x;
    double dy = (image_y / 2) - dc_y;

    img::EasyImage img;
    for (auto line : lines){
        line.p1.schaling(schaalfactor);
        line.p2.schaling(schaalfactor);
        line.p1.optelling(dx, dy);
        line.p2.optelling(dx,dy);
        line.p1.afronden();
        line.p2.afronden();
        img::Color color = img::Color(line.color.red * 255, line.color.green * 255, line.color.blue * 255);
        img.draw_line(line.p1.x, line.p1.y, line.p2.x, line.p2.y, color);
    }
    return img;
}

Lines2D Geheel::drawLSystem(const LParser::LSystem2D &l_system) {
    initiator = l_system.get_initiator();
    alfabet = l_system.get_alphabet();
    starting_angle = l_system.get_starting_angle();
    replacement = l_system.get_replacement(initiator[0]);
    iterations = l_system.get_nr_iterations();
    angle = l_system.get_angle();

    for (int i = 0; i < iterations; i++){
        for (char c : replacement){
            if (c == initiator[0]){

            } else{

            }
        }
    }

    return Lines2D();
}


