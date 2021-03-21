target_sources(rocket PRIVATE
	RAudioDevice.cpp
	RMusic.cpp
	RMusicBuffer.cpp
	RSoundEffect.cpp
	RSoundListener.cpp
	RSoundSource.cpp
)
target_sources(rocket PUBLIC
    RAudioDevice.h
	RMusic.h
	RMusicBuffer.h
	RSoundEffect.h
	RSoundListener.h
	RSoundSource.h
)