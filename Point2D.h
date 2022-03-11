//
// Created by yassir on 09.03.22.
//

#ifndef ENGINE_POINT2D_H
#define ENGINE_POINT2D_H


class Point2D {
public:
    double x;
    double y;
    int x_afgerond;
    int y_afgerond;

    void schaling(double schaalfactor);

    void optelling(double dx, double dy);

    void afronden();
};


#endif //ENGINE_POINT2D_H
