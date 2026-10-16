#include <delynoi/models/basic/Point.h>
#include <delynoi/models/Region.h>
#include <delynoi/models/generator/functions/functions.h>
#include <delynoi/voronoi/TriangleVoronoiGenerator.h>

#include <delynoi/utilities/poisson_sampler.h>

int main(){
    std::vector<Point> l_points = {Point(10,0), Point(20,0), Point(20,20), Point(0,20), Point(0,10), Point(10,10)};
    Region l_region(l_points);

    /*
    l_region.generateSeedPoints(
        PointGenerator(
            functions::random_double(0,20),
            functions::random_double(0,20)
        ),
        15, 15);
    */

    auto points = poisson_disk_sampling(20, 20, 1, 30);
    l_region.addSeedPoints(points);

    std::vector<Point> seeds = l_region.getSeedPoints();

    TriangleVoronoiGenerator g(seeds, l_region);
    Mesh<Polygon> LRandom = g.getMesh();
    LRandom.printInFile("LShapedMesh.txt");
}