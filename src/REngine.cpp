#include <REngine.h>

namespace rocket
{
    API
    REngine& REngine::instance(){
        static REngine instance;
        return instance;
    }
}