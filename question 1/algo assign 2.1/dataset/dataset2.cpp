#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point {
    double x;
    double y;
};

// Function to generate random points within a specified range
Point generateRandomPoint(double minX, double maxX, double minY, double maxY) {
    Point p;
    p.x = minX + static_cast<double>(rand()) / RAND_MAX * (maxX - minX);
    p.y = minY + static_cast<double>(rand()) / RAND_MAX * (maxY - minY);
    return p;
}

// Function to check if three points make a counter-clockwise turn
bool ccw(Point a, Point b, Point c) {
    return (b.y - a.y) * (c.x - b.x) > (b.x - a.x) * (c.y - b.y);
}

// Function to check if a polygon is convex
bool isConvex(const vector<Point>& points) {
    int n = points.size();
    if (n < 3) return false;

    bool isLeftTurn = ccw(points[0], points[1], points[2]);
    for (int i = 1; i < n; ++i) {
        if (ccw(points[i], points[(i+1)%n], points[(i+2)%n]) != isLeftTurn)
            return false;
    }
    return true;
}

// Function to generate a convex polygon with random vertices
vector<Point> generateConvexPolygon(int numVertices, double minX, double maxX, double minY, double maxY) {
    vector<Point> polygon;
    if (numVertices < 3) return polygon;

    for (int i = 0; i < numVertices; ++i) {
        polygon.push_back(generateRandomPoint(minX, maxX, minY, maxY));
    }

    // Check if polygon is convex, if not regenerate
    if (!isConvex(polygon)) {
        polygon.clear();
        polygon = generateConvexPolygon(numVertices, minX, maxX, minY, maxY);
    }

    return polygon;
}

// Function to write polygon data to CSV file
void writePolygonsToCSV(const vector<vector<Point>>& polygons, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    file << fixed << setprecision(2); // Set precision to two decimal places

    for (const auto& polygon : polygons) {
        for (const auto& point : polygon) {
            file <<"("<< point.x << "," << point.y <<")"<< ",";
        }
        file << endl;
    }

    file.close();
}

int main() {
    // Seed random number generator
    srand(time(nullptr));

    // Define parameters
    int numPolygons = 10; // Number of polygons to generate
    int maxVertices = 10; // Maximum number of vertices for each polygon
    double minX = -10.0, maxX = 10.0; // Range of x coordinates
    double minY = -10.0, maxY = 10.0; // Range of y coordinates

    vector<vector<Point>> polygons;

    // Generate polygons
    for (int i = 3; i <= maxVertices; ++i) {
        for (int j = 0; j < numPolygons; ++j) {
            polygons.push_back(generateConvexPolygon(i, minX, maxX, minY, maxY));
        }
    }

    // Write polygons to CSV file
    writePolygonsToCSV(polygons, "polygons.csv");

    cout << "Polygon data has been written to polygons.csv" << endl;

    return 0;
}