#include "checkers_rectangle.h"
#include "../../util.h"

img::EasyImage CheckersRectangle::generate()
{
    double w_block = this->w / this->nr_x_blocks;
    double h_block = this->h / this->nr_y_blocks;
    int curr_x_block = 0;
    int curr_y_block = 0;

    for (unsigned int x = 0; x < this->w; x++) {
        for (unsigned int y = 0; y < this->h; y++) {
            curr_x_block = x / w_block;
            curr_y_block = y / h_block;

            if ((curr_x_block + curr_y_block) % 2 == 0) {
                this->color_pixel(x, y, this->color_white);
            } else {
                this->color_pixel(x, y, this->color_black);
            }
        }
    }

    return this->img;
}

img::EasyImage generate_checkers_rectangle_image(const ini::Configuration &config)
{
    CheckersRectangle cr = CheckersRectangle(
        config["ImageProperties"]["width"].as_int_or_die(),
        config["ImageProperties"]["height"].as_int_or_die(),
        config["BlockProperties"]["nrXBlocks"].as_int_or_die(),
        config["BlockProperties"]["nrYBlocks"].as_int_or_die(),
        config["BlockProperties"]["colorWhite"].as_double_tuple_or_die(),
        config["BlockProperties"]["colorBlack"].as_double_tuple_or_die(),
        config["BlockProperties"]["invertColors"].as_bool_or_default(false)
    );

    return cr.generate();
}