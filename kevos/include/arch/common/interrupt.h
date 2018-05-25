/* Copyright 2018 kevin Lau (http://github.com/stormycatcat)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef _KEVOS_ARCH_COMMON_INTERRUPT_H_
#define _KEVOS_ARCH_COMMON_INTERRUPT_H_

#include <arch/common/types.h>

KEVOS_NSS_3(kevos,arch,common);

class InterruptManager
{
public:
	static void initialize();
};

KEVOS_NSE_3(kevos,arch,common);

#endif
