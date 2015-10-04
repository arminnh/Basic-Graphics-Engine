/****************************************
* Author: Armin Halilovic
* Date: 26 februari 2013 - 8 maart 2013 
* Title: 2D lines.cc
*****************************************/

#include "2Dlines.h"

img::EasyImage draw_2D_lines(Lines2D& lines, int size, img::Color kleur) {
	std::list<Line2D>::iterator iter;							//An iterator over the list with lines	
	iter = lines.begin();
	
	double Xmax = std::max(iter->p1.x, iter->p2.x);				//First we take the Max and Min values of the first element in the list
	double Xmin = std::min(iter->p1.x, iter->p2.x);
	double Ymax = std::max(iter->p1.y, iter->p2.y);
	double Ymin = std::min(iter->p1.y, iter->p2.y);
	
	for (iter = lines.begin(); iter != lines.end(); ++iter) {	//The we use the iterator to determine the Max and Min values of all lines
		Xmax = std::max(std::max(iter->p1.x, iter->p2.x), Xmax);
		Xmin = std::min(std::min(iter->p1.x, iter->p2.x), Xmin);
		Ymax = std::max(std::max(iter->p1.y, iter->p2.y), Ymax);
		Ymin = std::min(std::min(iter->p1.y, iter->p2.y), Ymin);
	}
	
	double Xrange = Xmax - Xmin;
	double Yrange = Ymax - Ymin;
	
	double ImageX = size * (Xrange / std::max(Xrange, Yrange));	//ImageX and ImageY determine the size of the image
	double ImageY = size * (Yrange / std::max(Xrange, Yrange));
	
	double d = 0.95 * (ImageX / Xrange);						//A scaling factor d
	for(iter = lines.begin(); iter != lines.end(); ++iter) {	//Mutiply all coords with d to get the scale we want
		iter->p1.x *= d;
		iter->p1.y *= d;
		iter->p2.x *= d;
		iter->p2.y *= d;
	}
	
	double DCx = d * ((Xmin + Xmax) / 2);						//Some values to help move the picture
	double DCy = d * ((Ymin + Ymax) / 2);
	
	double dx = (ImageX / 2) - DCx;								//Ditto
	double dy = (ImageY / 2) - DCy;
	for(iter = lines.begin(); iter != lines.end(); ++iter) {	//Add (dx, dy) to all points, so we move te picture to its right position
		iter->p1.x += dx;
		iter->p1.y += dy;
		iter->p2.x += dx;
		iter->p2.y += dy;
	}
	
	ImageX = round_to_int(ImageX);								//Round the values we need to draw the picture
	ImageY = round_to_int(ImageY);
	for(iter = lines.begin(); iter != lines.end(); ++iter) {
		iter->p1.x = round_to_int(iter->p1.x);
		iter->p1.y = round_to_int(iter->p1.y);
		iter->p2.x = round_to_int(iter->p2.x);
		iter->p2.y = round_to_int(iter->p2.y);
	}
	
	img::EasyImage image(ImageX, ImageY, kleur);				//Draw the picture
	for (iter = lines.begin(); iter != lines.end(); ++iter) {
		img::Color c(iter->color.red, iter->color.green, iter->color.blue); 
		image.draw_line(iter->p1.x, iter->p1.y, iter->p2.x, iter->p2.y, c);
	}
	
	return image;
}

Lines2D convert_2DL_to_line_list(LParser::LSystem2D& TweeDL_systeem, Lines2D& list, img::Color lijnkleur) {
	std::set<char> Alphabet = TweeDL_systeem.get_alphabet();
	std::string initiator = TweeDL_systeem.get_initiator();
	unsigned int NrIterations = TweeDL_systeem.get_nr_iterations();
	std::string vervanging = "";								//A new string to help with replacement
	
	double angle = TweeDL_systeem.get_angle();					//Convert to radians.
	angle = angle * (PI / 180);
	double StartingAngle = TweeDL_systeem.get_starting_angle();
	StartingAngle = StartingAngle * (PI / 180);
	double alfa = StartingAngle;
	
	for (unsigned int i = 0; i < NrIterations; i++) {			//Execute the replacements on the initiator.
		for (std::string::const_iterator it = initiator.begin(); it != initiator.end(); it++) {
			if (*it == '+') {
				vervanging.append("+");
			} else if (*it == '-') {
				vervanging.append("-");
			} else if (*it == '(') {
				vervanging.append("(");
			} else if (*it == ')') {
				vervanging.append(")");
			} else if (*it == ' ') {
				continue;
			} else {
				vervanging.append(TweeDL_systeem.get_replacement(*it));
			}
		}
		initiator = vervanging;
		vervanging = "";
	}
	
	Line2D lijn;												//Next, use the new string to construct lines.
	Point2D punt;												//A point initialised to (0, 0) to help construct lines.
	punt.x = 0;
	punt.y = 0;
	stack<double> stack;
	for (std::string::const_iterator itt = initiator.begin(); itt != initiator.end(); itt++) {
		if (*itt == '+') {										//If you "turn left".
			alfa += angle;
		} else if (*itt == '-') {								//If you "turn right".
			alfa -= angle;
		} else if (*itt == '(') {								//For each open bracket.
			stack.push(punt.x);
			stack.push(punt.y);
			stack.push(alfa);
		} else if (*itt == ')') {								//For each closed bracket.
			alfa = stack.top();
			stack.pop();
			punt.y = stack.top();
			stack.pop();
			punt.x = stack.top();
			stack.pop();
		} else if (TweeDL_systeem.draw(*itt) == 1) {			//If a line has to be drawn.
			lijn.p1.x = punt.x;
			lijn.p1.y = punt.y;

			punt.x += cos(alfa);
			punt.y += sin(alfa);

			lijn.p2.x = punt.x;
			lijn.p2.y = punt.y;

			list.push_back(lijn);
		} else {												//If no line has to be drawn.
			punt.x += cos(alfa);
			punt.y += sin(alfa);
		}
	}

	std::list<Line2D>::iterator iteratecolors;					//Give the lines a color.			
	for(iteratecolors = list.begin(); iteratecolors != list.end(); ++iteratecolors) {
		iteratecolors->color.red = lijnkleur.red;
		iteratecolors->color.green = lijnkleur.green;
		iteratecolors->color.blue = lijnkleur.blue;
	}
	
	return list;
}

img::EasyImage teken_2DL(const ini::Configuration& config) {
	int size = config["General"]["size"].as_int_or_die();
	std::vector<double> backgroundcolor = config["General"]["backgroundcolor"].as_double_tuple_or_die();
	img::Color background(backgroundcolor[0] * 255, backgroundcolor[1] * 255, backgroundcolor[2] * 255);
	std::vector<double> systemcolor = config["2DLSystem"]["color"].as_double_tuple_or_die();
	img::Color linecolor(systemcolor[0] * 255, systemcolor[1] * 255, systemcolor[2] * 255);
	std::string input = config["2DLSystem"]["inputfile"].as_string_or_die();
	const char* inputfile = input.c_str();

	LParser::LSystem2D l_system;								//Initialize the parser for the l system.
	std::ifstream input_stream(inputfile);
	input_stream >> l_system;
	input_stream.close();

	Lines2D ListOfLines;
	convert_2DL_to_line_list(l_system, ListOfLines, linecolor);	//Convert the 2DL system to a list of lines.
	return draw_2D_lines(ListOfLines, size, background); 
}
