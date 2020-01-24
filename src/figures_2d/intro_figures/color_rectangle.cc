#include "color_rectangle.h"
#include "../../util.h"

img::EasyImage ColorRectangle::generate()
{
    for (unsigned int x = 0; x < this->w; x++) {
        for (unsigned int y = 0; y < this->h; y++) {
            double w_ratio = (double) x / this->w;
            double h_ratio = (double) y / this->h;

            this->img(x, y).red = round_to_int(255.0 * w_ratio);
            this->img(x, y).green = round_to_int(255.0 * h_ratio);
            this->img(x, y).blue = round_to_int(255.0 * (h_ratio + w_ratio));
        }
    }

    return this->img;
}

img::EasyImage generate_color_rectangle_image(const ini::Configuration &config)
{
    ColorRectangle cr = ColorRectangle(
        config["ImageProperties"]["width"].as_int_or_die(),
        config["ImageProperties"]["height"].as_int_or_die()
    );

    return cr.generate();
}