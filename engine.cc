#include "easy_image.h"
#include "ini_configuration.h"
#include "Geheel.h"
#include "l_parser.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>


img::EasyImage test(){
    img::EasyImage image(256,256);
    for(unsigned int i = 0; i < 256; i++)
        for(unsigned int j = 0; j < 256; j++)
        {
            image(i,j).red = i;
            image(i,j).green = j;
            image(i,j).blue = (i+j)%256;
        }
    std::ofstream fout("test.bmp", std::ios::binary);
    fout << image;
    fout.close();
    return image;
}

img::Color Tuple2Color(std::vector<double> tup){
    img::Color color(tup.at(0) * 255, tup.at(1) * 255, tup.at(2) * 255);
    return color;
}

img::EasyImage intro(const ini::Configuration &configuration){
    auto type = configuration["General"]["type"].as_string_or_die();
    auto width = configuration["ImageProperties"]["width"].as_int_or_die();
    auto height = configuration["ImageProperties"]["height"].as_int_or_die();
    auto nrXBlocks = configuration["BlockProperties"]["nrXBlocks"].as_int_or_die();
    auto nrYBlocks = configuration["BlockProperties"]["nrYBlocks"].as_int_or_die();
    auto colorWhite = configuration["BlockProperties"]["colorWhite"].as_double_tuple_or_die();
    auto colorBlack = configuration["BlockProperties"]["colorBlack"].as_double_tuple_or_die();
    auto invertColors = configuration["BlockProperties"]["invertColors"].as_bool_or_default(false);

    auto W = width / nrXBlocks;
    auto H = height / nrYBlocks;
    img::EasyImage image(width, height);
    for (unsigned int i = 0; i < width; i++){
        for (unsigned int j = 0; j < height; j++){
            if ((i/W)%2 == (j/H)%2){
                image(i, j) = Tuple2Color(colorWhite);
            } else{
                image(i, j) = Tuple2Color(colorBlack);
            }
        }
    }
    return image;
}

img::EasyImage QuarterCircle(const ini::Configuration &configuration){
    auto type = configuration["General"]["type"].as_string_or_die();
    auto width = configuration["ImageProperties"]["width"].as_int_or_die();
    auto height = configuration["ImageProperties"]["height"].as_int_or_die();
    auto figure = configuration["LineProperties"]["figure"].as_string_or_die();
    auto nrLines = configuration["LineProperties"]["nrLines"].as_int_or_die();
    auto backgroundcolor = configuration["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
    auto lineColor = configuration["LineProperties"]["lineColor"].as_double_tuple_or_die();

    auto W = width / (nrLines - 1);
    auto H = height / (nrLines - 1);
    img::EasyImage image(width, height);

    return image;
}

img::EasyImage testLines(){
    img::EasyImage img;
    img.draw_line(0,0,0,0,img::Color(1,1,0));
    img.draw_line(0,0,1,1,img::Color(1,1,0));
    std::ofstream fout("testt.bmp", std::ios::binary);
    fout << img;
    fout.close();
    return img;
}

img::EasyImage generate_image(const ini::Configuration &configuration)
{
    std::string type = configuration["General"]["type"].as_string_or_die();
    int size = configuration["General"]["size"].as_int_or_die();
    auto backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    auto inputfile = configuration["2DLSystem"]["inputfile"].as_string_or_die();
    auto color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    LParser::LSystem2D l_system;
    std::ifstream input_stream("32_segment_curve.L2D");
    input_stream >> l_system;
    input_stream.close();

    Geheel geheel;
    auto x = geheel.drawLSystem(l_system);
	return geheel.draw2DLines(x, size);
}

std::vector<Line2D> line2Dfixer(LParser::LSystem2D &system2D, const std::string sign, std::vector<double> color){
    Line2D line;
    line.p2.x = 0;
    line.p2.y = 0;
    double x = 0;
    double y = 0;
}

int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                std::vector<std::string> args = std::vector<std::string>(argv+1, argv+argc);
                if (args.empty()) {
                        std::ifstream fileIn("filelist");
                        std::string filelistName;
                        while (std::getline(fileIn, filelistName)) {
                                args.push_back(filelistName);
                        }
                }
                for(std::string fileName : args)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(fileName);
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = testLines();
//                        img::EasyImage image = intro(conf);
//                        img::EasyImage image = generate_image(conf);

                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << fileName << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
