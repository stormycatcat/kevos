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

/*****************************************************************************
*  @file     assert.h                            
*  @brief    内核断言                 
*                                   
*                                            
*  @author   Kevin Lau                       
*  @email    skl510006@gmail.com              
*  @version  0.1.1              
*  @date     2018/5/20
*****************************************************************************/

#ifndef _KEVOS_ARCH_COMMON_ASSERT_H_
#define _KEVOS_ARCH_COMMON_ASSERT_H_

#include <sys/types.h>

#include <cstddef>

#ifndef __KEVOS_NODEBUG__
	#define assert(cond) do {(cond)?void(0):__assert(#cond,__LINE__,__FILE__);}while(0)
#else
	#define assert(cond)
#endif

void __assert(const char* cond,uint32_t line,const char* file);


#endif
