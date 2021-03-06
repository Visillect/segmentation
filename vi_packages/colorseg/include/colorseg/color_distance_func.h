/*
Copyright (c) 2012-2018, Visillect Service LLC. All rights reserved.
Developed for Kharkevich Institute for Information Transmission Problems of the
              Russian Academy of Sciences (IITP RAS).

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

#include <colorseg/color_vertex.h>
#include <remseg/edge_heap.h>

namespace vi { namespace colorseg {

const double ME = 0.5;

inline EdgeValue shouldnotcall(const ColorVertex*) {
  return 0;//throw std::runtime_error("Should not call this dummy error function for some criteria");
}

EdgeValue criteria_r0(const ColorVertex *v1, const ColorVertex *v2);

EdgeValue criteria_r1(const ColorVertex *v1, const ColorVertex *v2);

EdgeValue error_r1(const ColorVertex *v);

EdgeValue criteria_r2(const ColorVertex *v1, const ColorVertex *v2);

EdgeValue error_r2(const ColorVertex *v);

bool isLTCluster(const ColorVertex *v1, const ColorVertex *v2);

}}	// ns vi::colorseg
