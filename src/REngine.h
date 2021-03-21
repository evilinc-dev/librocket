#pragma once

#include "common.h"

namespace rocket
{
    class API REngine
    {
    private:
        REngine();
        ~REngine();

        void* window;
        void* context;

    public:
        static REngine& instance();
        void clear();
        void present();
        void init();
        void setClearColor(const RVector3& color);
        void shutdown();
    };
}