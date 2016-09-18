#include <iostream>
#include <fstream>
#include <iomanip>
#include "PrintOuts.h"
#include "Shape.h"

#define DEFAULT_ARG_NUM 2
#define ARG_NUM_WITH_OFILE 3
#define OUTPUT_FILE_INDEX 2
#define INPUT_FILE_INDEX 1
#define WRONG_ARGS_NUM_MSG "Wrong number of arguments!"
#define ARG_USAGE_MSG "Usage: Shapes <input_filename> [<output_filename>]"

#define NEW_LINE_CHAR '\n'

using ShapeP = std::shared_ptr<Shape>;

/**
 * @brief Scans the file and adds shapes to the Shape container.
 * @param shapes Shapes vector container reference
 */
void initShapes(std::vector<ShapeP> &shapes)
{
    char type;
    CordType x, y;

    while(std::cin >> type)
    {
        std::vector<Point> points;
        // init the point with the values from the file and add the point to the Point container
        do
        {
            std::cin >> x >> y;
            points.push_back({x, y});
        } while (std::cin.get() != NEW_LINE_CHAR);

        // add the new shape
        shapes.push_back(Shape::createShape(type, points));
    }
}

/**
 * @brief Iterates over the Shapes container and checks for interesects. If any interesects
 * found, prints shape descritption and a message; otherwise calculates the overall area of the
 * shapes and prints it.
 * @param shapes Shape vector container.
 */
void processShapes(std::vector<ShapeP> &shapes)
{
    CordType area = 0;
    for(size_t i = 0; i < shapes.size(); i++)
    {
        ShapeP s1 = shapes[i];

        // iterate over the rest of the shapes and check for intersects.
        for (size_t j = i + 1; j < shapes.size(); j++)
        {
            ShapeP s2 = shapes[j];
            // Check for intersect
            if(*s1 & *s2)
            {
                s1->printShape();
                s2->printShape();
                reportDrawIntersect();
                return;
            }
        }

        //if no intersects found so far, add the area to the overall area.
        area += s1->calculateArea();
    }

    // if no intersects found, print the calculated overall area.
    printArea(area);
}

int main(int argc, char **argv)
{
    if(argc < DEFAULT_ARG_NUM)
    {
        std::cerr << WRONG_ARGS_NUM_MSG << std::endl << ARG_USAGE_MSG << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<ShapeP> shapes;

    std::streambuf *coutBackup = std::cout.rdbuf(), *cinBackup = std::cin.rdbuf();
    std::ifstream ifs(argv[INPUT_FILE_INDEX]);
    std::cin.rdbuf(ifs.rdbuf());
    std::cout << std::setprecision(2) << std::fixed;;

    if (argc == ARG_NUM_WITH_OFILE)
    {
        std::ofstream ofs(argv[OUTPUT_FILE_INDEX]);
        std::cout.rdbuf(ofs.rdbuf());
    }

    initShapes(shapes);
    processShapes(shapes);

    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);
    return EXIT_SUCCESS;
}
