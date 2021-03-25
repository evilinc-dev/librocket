#include "RApplication.h"
#include "REngine.h"

namespace rocket
{
	API Ref<REngine> RApplication::getEngine() {
		return REngine::instance();
	}

	API RApplication::RApplication()
	{
		Ref<REngine> engine = REngine::instance();
		engine->_application = Ref<RApplication>(this);
	}

	API RApplication::~RApplication()
	{
		
	}
}