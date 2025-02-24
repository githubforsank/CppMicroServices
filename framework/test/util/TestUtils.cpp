/*=============================================================================

Library: CppMicroServices

Copyright (c) The CppMicroServices developers. See the COPYRIGHT
file at the top-level directory of this distribution and at
https://github.com/CppMicroServices/CppMicroServices/COPYRIGHT .

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=============================================================================*/

#include "TestUtils.h"

#include "cppmicroservices/GetBundleContext.h"
#include "cppmicroservices/GlobalConfig.h"

#include "cppmicroservices/util/Error.h"
#include "cppmicroservices/util/FileSystem.h"

#include <TestingConfig.h>

#ifndef US_PLATFORM_WINDOWS
#  include <sys/time.h> // gettimeofday etc.
#else
#  include "cppmicroservices/util/String.h" // for utf8 conversion
#  include <direct.h>
#  include <io.h>
#endif

#ifdef US_PLATFORM_APPLE
#  include <unistd.h> // chdir, getpid, close, etc.
#endif

#include <fcntl.h>
#include <sys/stat.h> // mkdir, _S_IREAD, etc.

namespace cppmicroservices {

namespace testing {

#if defined(US_PLATFORM_APPLE)

double HighPrecisionTimer::timeConvert = 0.0;

HighPrecisionTimer::HighPrecisionTimer()
  : startTime(0)
{
  if (timeConvert == 0) {
    mach_timebase_info_data_t timeBase;
    mach_timebase_info(&timeBase);
    timeConvert = static_cast<double>(timeBase.numer) /
                  static_cast<double>(timeBase.denom) / 1000.0;
  }
}

void HighPrecisionTimer::Start()
{
  startTime = mach_absolute_time();
}

long long HighPrecisionTimer::ElapsedMilli()
{
  uint64_t current = mach_absolute_time();
  return static_cast<double>(current - startTime) * timeConvert / 1000.0;
}

long long HighPrecisionTimer::ElapsedMicro()
{
  uint64_t current = mach_absolute_time();
  return static_cast<double>(current - startTime) * timeConvert;
}

#elif defined(US_PLATFORM_POSIX)

HighPrecisionTimer::HighPrecisionTimer()
{
  startTime.tv_nsec = 0;
  startTime.tv_sec = 0;
}

void HighPrecisionTimer::Start()
{
  clock_gettime(CLOCK_MONOTONIC, &startTime);
}

long long HighPrecisionTimer::ElapsedMilli()
{
  timespec current;
  clock_gettime(CLOCK_MONOTONIC, &current);
  return (static_cast<long long>(current.tv_sec) * 1000 +
          current.tv_nsec / 1000 / 1000) -
         (static_cast<long long>(startTime.tv_sec) * 1000 +
          startTime.tv_nsec / 1000 / 1000);
}

long long HighPrecisionTimer::ElapsedMicro()
{
  timespec current;
  clock_gettime(CLOCK_MONOTONIC, &current);
  return (static_cast<long long>(current.tv_sec) * 1000 * 1000 +
          current.tv_nsec / 1000) -
         (static_cast<long long>(startTime.tv_sec) * 1000 * 1000 +
          startTime.tv_nsec / 1000);
}

#elif defined(US_PLATFORM_WINDOWS)

HighPrecisionTimer::HighPrecisionTimer()
{
  if (!QueryPerformanceFrequency(&timerFrequency))
    throw std::runtime_error("QueryPerformanceFrequency() failed");
}

void HighPrecisionTimer::Start()
{
  // DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
  QueryPerformanceCounter(&startTime);
  // SetThreadAffinityMask(GetCurrentThread(), oldmask);
}

long long HighPrecisionTimer::ElapsedMilli()
{
  LARGE_INTEGER current;
  QueryPerformanceCounter(&current);
  return (current.QuadPart - startTime.QuadPart) /
         (timerFrequency.QuadPart / 1000);
}

long long HighPrecisionTimer::ElapsedMicro()
{
  LARGE_INTEGER current;
  QueryPerformanceCounter(&current);
  return (current.QuadPart - startTime.QuadPart) /
         (timerFrequency.QuadPart / (1000 * 1000));
}

#endif

Bundle InstallLib(BundleContext frameworkCtx, const std::string& libName)
{
  std::vector<Bundle> bundles;

#if defined(US_BUILD_SHARED_LIBS)
  bundles = frameworkCtx.InstallBundles(LIB_PATH
                                        + util::DIR_SEP
                                        + US_LIB_PREFIX
                                        + libName
                                        + US_LIB_POSTFIX
                                        + US_LIB_EXT);
#else
  bundles = frameworkCtx.GetBundles();
#endif

  for (auto b : bundles) {
    if (b.GetSymbolicName() == libName)
      return b;
  }
  return {};
}

void ChangeDirectory(const std::string& destdir)
{
  errno = 0;
  int ret = chdir(destdir.c_str());
  if (ret != 0) {
    const std::string msg = "Unable to change directory to " + destdir + ": " +
                            util::GetLastCErrorStr();
    throw std::runtime_error(msg);
  }
}

TempDir::TempDir() {}

TempDir::TempDir(const std::string& path)
  : Path(path)
{}

TempDir::TempDir(TempDir&& o)
  : Path(std::move(o.Path))
{}

TempDir& TempDir::operator=(TempDir&& o)
{
  std::swap(Path, o.Path);
  return *this;
}

TempDir::~TempDir()
{
  if (!Path.empty()) {
    try {
      util::RemoveDirectoryRecursive(Path);
    } catch (const std::exception&) {
      // ignored
    }
  }
}

TempDir::operator std::string() const
{
  return Path;
}

Bundle GetBundle(const std::string& bsn, BundleContext context)
{
  if (!context)
    context = cppmicroservices::GetBundleContext();
  for (auto b : context.GetBundles()) {
    if (b.GetSymbolicName() == bsn)
      return b;
  }
  return {};
}
}
}
