#ifndef HISTOGRAMPYRAMIDS_HPP_
#define HISTOGRAMPYRAMIDS_HPP_

#include "OpenCLManager.hpp"
#include <vector>

// TODO Quickfix before I refactor this
#ifndef COMMONS_H
typedef struct OpenCL {
    cl::Context context;
    cl::CommandQueue queue;
    cl::Program program;
    cl::Device device;
    cl::Platform platform;
    oul::GarbageCollector * GC;
} OpenCL;
#endif
namespace oul {

class HistogramPyramid {
    public:
        int getSum();
        virtual cl::Buffer createPositionBuffer() = 0;
        virtual void deleteHPlevels() = 0;
    protected:
        OpenCL ocl;
        int size;
        int sum;
};

class HistogramPyramid2D : public HistogramPyramid {
    public:
        HistogramPyramid2D(OpenCL & ocl);
        void create(cl::Image2D &image, int, int);
        cl::Buffer createPositionBuffer();
        void deleteHPlevels();
        void traverse(cl::Kernel &kernel, int);
    private:
        std::vector<cl::Image2D> HPlevels;
};

class HistogramPyramid3D : public HistogramPyramid {
    public:
        HistogramPyramid3D(OpenCL &ocl);
        void create(cl::Image3D &image, int, int, int);
        cl::Buffer createPositionBuffer();
        void deleteHPlevels();
        void traverse(cl::Kernel &kernel, int);
    private:
        std::vector<cl::Image3D> HPlevels;
};

class HistogramPyramid3DBuffer : public HistogramPyramid {
    public:
        HistogramPyramid3DBuffer(OpenCL &ocl);
        void create(cl::Buffer &buffer, int, int, int);
        cl::Buffer createPositionBuffer();
        void deleteHPlevels();
        void traverse(cl::Kernel &kernel, int);
    private:
        int sizeX,sizeY,sizeZ;
        std::vector<cl::Buffer> HPlevels;
};

#endif /* HISTOGRAMPYRAMIDS_HPP_ */
