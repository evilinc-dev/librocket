#include "REngine.h"

namespace rocket
{
    

    REngine::REngine():_application(nullptr) {}

    REngine::~REngine() {}

    API Ref<REngine> REngine::instance() {
        static Ref<REngine> instance;
        return instance;
    }

    API void REngine::init() {
        

    }

    API void REngine::setClearColor(const RVector3& color) {
        
    }

    API void REngine::clear() {
        
    }

    API void REngine::present() {
        
    }

    API void REngine::shutdown() {
        if (this->_application != nullptr) {
            this->_application->unload();
        }
    }

}