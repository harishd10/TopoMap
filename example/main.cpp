#include <iostream>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <TopoMap.hpp>

std::string inputFile;
std::string outputFile;
int leafSize = 1;
bool verbose = false;

void readData(std::string dataFile, std::vector<double> &data, int &dim) {
    std::ifstream fi(dataFile);
    if(!fi.good()) {
        std::cerr << "Error reading file: " << dataFile << std::endl;
        exit(0);
    }

    dim = -1;
    data.clear();
    std::string line;
    while(std::getline(fi,line)) {

        std::vector<std::string> list;
        boost::split(list,line,boost::is_any_of(","));
        if(dim == -1) {
            dim = list.size();
        } else {
            if(dim != list.size()) {
                std::cerr << "Error!!! incorrect dimensions in input" << std::endl;
                exit(0);
            }
        }
        for(int d = 0;d < dim;d ++) {
            double val = std::atof(list[d].c_str());
            data.push_back(val);
        }
    }
    fi.close();
}

void writeProjection(std::vector<Point> &pts, std::string opFile) {
    std::ofstream fo(opFile);
    fo.precision(10);
    for(int i = 0;i < pts.size();i ++) {
        fo << pts[i].x << "," << pts[i].y << std::endl;
    }
    fo.close();
}

void printUsage() {
    std::cerr << "arguments:" << std::endl;
    std::cerr << "--input <csv file> (required argument) \t input point cloud as csv without any header. "
                 "Each line should be the coordinates of a single point." << std::endl;
    std::cerr << "--output <csv file> (required argument) \t file to which the projected points are stored." << std::endl;
    std::cerr << "--leafsize <integer> (optional argument. default = 1) \t this is used to set the leaf size of the kd-tree used for EMST computation" << std::endl;
    std::cerr << "--verbose (optional argument. default = false)" << std::endl;
}

void parseArguments(int argc, char *argv[]) {
    int ct = 0;
    for(int i = 1;i < argc;i ++) {
        std::string a(argv[i]);
        boost::trim(a);
        if(a.compare("--input") == 0) {
            inputFile = std::string((argv[i+1]));
            boost::trim(inputFile);
            ct ++;
        }
        if(a.compare("--output") == 0) {
            outputFile = std::string((argv[i+1]));
            boost::trim(outputFile);
            ct ++;
        }
        if(a.compare("--leafsize") == 0) {
            leafSize = atoi(argv[i+1]);
            if(leafSize < 1) {
                std::cerr << "Invalid usage: leaf size should be greater than 0." << std::endl;
                printUsage();
                exit(0);
            }
        }
        if(a.compare("--verbose") == 0) {
            verbose = true;
        }
        if(a.compare("--help") == 0) {
            printUsage();
            exit(0);
        }
    }

    if(ct != 2) {
        std::cerr << "Invalid usage: no input or output file present." << std::endl;
        printUsage();
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    parseArguments(argc, argv);

    std::vector<double> data;
    int dim;
    readData(inputFile,data,dim);
    std::cerr << "read data file " << inputFile << " with dimension " << dim << std::endl;

    TopoMap tm(leafSize,verbose);
    std::vector<Point> pts = tm.project(data,dim);

    std::cerr << "writing output" << std::endl;
    writeProjection(pts,outputFile);
    return 0;
}
