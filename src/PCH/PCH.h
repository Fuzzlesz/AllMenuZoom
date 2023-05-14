#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI

#include <ranges>

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

#ifdef NDEBUG
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <spdlog/sinks/msvc_sink.h>
#endif

using namespace std::literals;

namespace logger = SKSE::log;

#include <ClibUtil/distribution.hpp>
#include <ClibUtil/numeric.hpp>
#include <ClibUtil/simpleINI.hpp>
#include <ClibUtil/singleton.hpp>
#include <ClibUtil/string.hpp>
#include <MergeMapperPluginAPI.h>
#include <ankerl/unordered_dense.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <srell.hpp>

#define DLLEXPORT __declspec(dllexport)

namespace logger = SKSE::log;

namespace string = clib_util::string;
namespace numeric = clib_util::numeric;
namespace ini = clib_util::ini;
namespace dist = clib_util::distribution;

using namespace std::literals;
using namespace string::literals;
using namespace clib_util::singleton;

namespace stl
{
	using namespace SKSE::stl;

	template <class T>
	void write_thunk_call(std::uintptr_t a_src)
	{
		auto& trampoline = SKSE::GetTrampoline();
		SKSE::AllocTrampoline(14);
		T::func = trampoline.write_call<5>(a_src, T::thunk);
	}
}
namespace util
{
	using SKSE::stl::report_and_fail;
	using SKSE::stl::to_underlying;
	using SKSE::stl::utf8_to_utf16;

	struct comp_str_cis
	{
		bool operator()(const std::string& a_lhs, const std::string& a_rhs) const
		{
			return ::_stricmp(a_lhs.c_str(), a_rhs.c_str()) < 0;
		}
	};

	template <typename T>
	using istring_map = std::map<std::string, T, comp_str_cis>;

	template <typename Map, typename Result>
	inline bool try_get(
		Map const& a_map,
		typename Map::key_type const& a_key,
		typename Result& a_result)
	{
		if (const auto it = a_map.find(a_key); it != a_map.end()) {
			a_result = static_cast<Result>(it->second);
			return true;
		}

		return false;
	}	
}

#ifdef SKYRIM_AE
#define OFFSET(se, ae) ae
#define OFFSET_3(se, ae, vr) ae
#elif SKYRIMVR
#define OFFSET(se, ae) se
#define OFFSET_3(se, ae, vr) vr
#else
#define OFFSET(se, ae) se
#define OFFSET_3(se, ae, vr) se
#endif

#include "Plugin.h"
#include "Common.h"
