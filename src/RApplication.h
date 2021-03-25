#pragma once
#include "common.h"

namespace rocket
{
	class API RApplication
	{
	private:
		Ref<RWindow> window;

	public:
		RApplication();
		~RApplication();
		virtual void load();
		virtual void update();
		virtual void render();
		virtual void unload();

		Ref<REngine> getEngine();
		Ref<RInput> getInput();

		Ref<RWindow> createWindow(int width = 1280, int height = 720, int style = 0);
		Ref<RWindow> getWindow();
	};
}