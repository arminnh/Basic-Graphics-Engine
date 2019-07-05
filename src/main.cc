#include <fstream>

#include "tools/EasyImage.h"
#include "tools/ini_configuration.hh"

#include "image.h"
#include "color_rectangle.h"
#include "checkers_rectangle.h"
#include "line_structures.h"
#include "l_systems.h"
#include "wireframes.h"

img::EasyImage generate_image(const ini::Configuration &config)
{
    std::string type = config["General"]["type"].as_string_or_die();

    if (type == "IntroColorRectangle") {
        return generate_color_rectangle(config);
    } else if (type == "IntroBlocks") {
        return generate_checkers_rectangle(config);
    } else if (type == "IntroLines") {
        return generate_line_structure(config);
    } else if (type == "2DLSystem") {
        return generate_l_system_2d(config);
    } else if (type == "Wireframe") {
        return generate_wireframe_drawing(config);
    } else {
        std::cerr << "Unknown image type '" << type << "'." << std::endl;
        return img::EasyImage();
    }
}

int main(int argc, char const* argv[])
{
    int retVal = 0;

    try {
        for (int i = 1; i < argc; ++i) {
            ini::Configuration conf;

            try {
                std::ifstream fin(argv[i]);
                fin >> conf;
                fin.close();
            } catch (ini::ParseException& ex) {
                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                retVal = 1;
                continue;
            }

            img::EasyImage image = generate_image(conf);
            if (image.get_height() > 0 && image.get_width() > 0) {
                std::string fileName(argv[i]);
                std::string::size_type pos = fileName.rfind('.');

                if (pos == std::string::npos) {
                    //filename does not contain a '.' --> append a '.bmp' suffix
                    fileName += ".bmp";
                } else {
                    fileName = fileName.substr(0,pos) + ".bmp";
                }

                try {
                    std::ofstream f_out(fileName.c_str(), std::ios::trunc | std::ios::out);
                    f_out << image;

                } catch (std::exception& ex) {
                    std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                    retVal = 1;
                }
            } else {
                std::cout << "Could not create image for " << argv[i] << std::endl;
            }
        }
    } catch (const std::bad_alloc &exception) {
        std::cerr << "Error: insufficient memory" << std::endl;
        retVal = 100;
    }

    return retVal;
}
