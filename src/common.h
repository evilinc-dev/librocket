#pragma once

#ifdef WIN32
    #define API __declspec(dllexport)
#else
    #define API __attribute__((visibility("default")))
#endif

#include <stddef.h>
#include <stdarg.h>
#include <cstdlib>
#include <cstddef>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <regex>
#include <thread>
#include <functional>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <list>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <bitset>
#include <mutex>
#include <queue>
#include <memory>
#include <string>
#include <string.h>

#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)
#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_EPSILON                0.000001f
#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))
#ifndef M_1_PI
#define M_1_PI                      0.31830988618379067154
#endif

namespace rocket
{

    class RMatrix;
    class RQuaternion;
    class RVector2;
    class RVector3;
    class RVector4;
    class RBoundingBox;
    class RBoundingSphere;
    class RFrustum;
    class RPlane;
    class RRay;

    class REngine;
    class RWindow;
    class RApplication;
    class RInput;
}
// -- MEMORY/TYPES -- //
#include "types/RConstants.h"
#include "types/REnums.h"
#include "types/RMemory.h"

// -- MATH -- //
#include "math/RMatrix.h"
#include "math/RQuaternion.h"
#include "math/RVector2.h"
#include "math/RVector3.h"
#include "math/RVector4.h"
#include "math/RBoundingBox.h"
#include "math/RBoundingSphere.h"
#include "math/RFrustum.h"
#include "math/RPlane.h"
#include "math/RRay.h"

// -- CORE -- //
#include "REngine.h"
#include "RWindow.h"
#include "RApplication.h"

// -- INPUT -- //
#include "input/RInput.h"
#include "input/RKeyboard.h"
#include "input/RMouse.h"
#include "input/RGameController.h"
// -- GFX -- //

// -- AUDIO -- //

// -- NET -- //

// -- UI -- //