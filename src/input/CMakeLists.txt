target_sources(rocket PRIVATE
	RGameController.cpp
	RInput.cpp
	RKeyboard.cpp
	RMouse.cpp
	RTouchController.cpp
)
target_sources(rocket PUBLIC
	RGameController.h
	RInput.h
	RKeyboard.h
	RMouse.h
	RTouchController.h
)