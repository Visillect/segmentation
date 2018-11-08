/*

Copyright (c) 2011, Smart Engines Limited. All rights reserved.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDERS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of copyright holders.

*/

#pragma once
#ifndef MINIMGIO_SRC_V4L2SUBSYSTEM_H_INCLUDED
#define MINIMGIO_SRC_V4L2SUBSYSTEM_H_INCLUDED

#include <map>
#include <string>
#include <vector>

#include "subsystem.h"
#include "stream.h"

class V4L2SubSystem : public SubSystem
{
public:
  static SubSystem * Instance();
  int GetDeviceNameList(char *p_device_names, int size) const;
  int OpenStream(const char *p_device_name, char *p_URI, int size);

private:
  V4L2SubSystem();
  V4L2SubSystem(const V4L2SubSystem &);
  V4L2SubSystem &operator =(const V4L2SubSystem &);
};

#endif // MINIMGIO_SRC_V4L2SUBSYSTEM_H_INCLUDED
