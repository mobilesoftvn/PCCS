#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H

#include <CompileConfig.h>
#include <phantom.h>
#include <physics/Vector3.h>
#include <sharedlib/serialization/Data.h>
#include "structures/Center.h"
#include "structures/Corner.h"
#include "structures/Edge.h"
#include "structures/fortune/voronoi.h"
namespace PGC{
    class LIBEXPORT VoronoiDiagram{
    public:
        VoronoiDiagram(int width, int height, int numPoints, int relaxCount = 0, bool distribute = false);
        ~VoronoiDiagram();

        void addChildDiagram(VoronoiDiagram* child);
        VoronoiDiagram* getParent();
        VoronoiDiagram* getChild();
        void relax(int count);
        void improveEdgeLength();
        vector<Data> toJSON();
    public: //properties
        vector<Vector3>*    vertices;
        vector<Corner*>*    corners;
        vector<Center*>*    centers;
        vector<Edge*>*      edges;
    private: //functions
        void buildGraph(vector<Vector3>* points);
        void distribute(vector<Vector3>* points);
    private: //properties
        VoronoiDiagram* parent;
        VoronoiDiagram* child;

        float width, height, numPoints;
        vor::VoronoiDiagramGenerator* vdg;
    };
}

#endif /* VORONOIDIAGRAM_H */