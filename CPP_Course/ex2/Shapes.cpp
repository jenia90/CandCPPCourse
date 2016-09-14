#include <iostream>
#include <fstream>
#include "PrintOuts.h"
#include "Shape.h"

#define DEFAULT_ARG_NUM 2
#define ARG_NUM_WITH_OFILE 3
#define OUTPUT_FILE_INDEX 2
#define INPUT_FILE_INDEX 1
#define WRONG_ARGS_NUM_MSG "Wrong number of arguments!"
#define ARG_USAGE_MSG "Usage: Shapes <input_filename> [<output_filename>]"

#define NEW_LINE_CHAR '\n'

/**
 * @brief Scans the file and adds shapes to the Shape container.
 * @param shapes Shapes vector container reference
 */
void initShapes(std::vector<Shape*> &shapes)
{
    char type;
    CordType x, y;

    std::cin >> type;

    while(!std::cin.eof())
    {
        std::vector<Point> points;
        // init the point with the values from the file and add the point to the Point container
        do
        {
            Point p;
            std::cin >> x;
            std::cin >> y;
            p.set(x, y);
            points.push_back(p);
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
void processShapes(std::vector<Shape *> shapes)
{
    bool intersectFound = false;
    CordType area = 0;
    for(size_t i = 0; i < shapes.size(); i++)
    {
        Shape *s1 = shapes[i];

        // iterate over the rest of the shapes and check for intersects.
        for (size_t j = i; j < shapes.size(); ++j)
        {
            Shape *s2 = shapes[j];
            // Check for intersect
            if(*s1 & *s2)
            {
                s1->printShape();
                s2->printShape();
                reportDrawIntersect();
                
                intersectFound = true;
            }
        }

        //if no intersects found so far, add the area to the overall area.
        if(!intersectFound)
        {
            area += s1->calculateArea();
        }
    }

    // if no intersects found, print the calculated overall area.
    if(!intersectFound)
    {
        printArea(area);
    }
}

int main(int argc, char **argv)
{
    if(argc < DEFAULT_ARG_NUM)
    {
        std::cerr << WRONG_ARGS_NUM_MSG << std::endl << ARG_USAGE_MSG << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<Shape*> shapes;

    std::ifstream ifs(argv[INPUT_FILE_INDEX]);
    std::cin.rdbuf(ifs.rdbuf());

    if (argc == ARG_NUM_WITH_OFILE)
    {
        std::ofstream ofs(argv[OUTPUT_FILE_INDEX]);
        std::cout.rdbuf(ofs.rdbuf());
    }

    initShapes(shapes);
    processShapes(shapes);


    return EXIT_SUCCESS;
}
