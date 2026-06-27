#pragma once

#include "Types.hpp"
#include "Enums.hpp"
#include "Loader.hpp"
#include "Functions.hpp"
#include "Context.hpp"
#include "Capabilities.hpp"
#include "ContextEvents.hpp"

#ifndef METAGL_NO_DEBUG
#include "Debug.hpp"
#endif

#ifndef METAGL_NO_ENUM_NAMES
#include "EnumNames.hpp"
#endif

#ifdef __EMSCRIPTEN__
#include "Emscripten.hpp"
#endif
