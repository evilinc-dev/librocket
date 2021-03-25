#pragma once

#include "common.h"

namespace rocket
{
    class API REngine
    {
        friend class RApplication;
    private:
        REngine();
        ~REngine();

        Ref<RApplication> _application;

    public:
        static Ref<REngine> instance();
        
        void clear();
        void present();
        void init();
        void setClearColor(const RVector3& color);
        void shutdown();
    };
}