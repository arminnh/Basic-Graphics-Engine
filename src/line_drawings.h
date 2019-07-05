#ifndef HEADER_LINE_DRAWINGS
#define HEADER_LINE_DRAWINGS

#include <tuple>
#include <vector>

#include "tools/EasyImage.h"
#include "tools/ini_configuration.hh"

#include "util.h"
#include "figures.h"

class LineDrawing : public Figure
{
public:
    std::vector<std::tuple<int, int>> lines;

    LineDrawing(ini::Section &config);

    const std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &o, const LineDrawing &ld);
};

#endif