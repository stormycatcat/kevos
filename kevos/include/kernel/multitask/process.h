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

#ifndef _KEVOS_KERNEL_MULTITASK_PROCESS_H_
#define _KEVOS_KERNEL_MULTITASK_PROCESS_H_

#include <sys/types.h>
#include <kernel/mm/page_defs.h>
#include <kernel/mm/mem_layout.h>

#include <vector>

namespace multitask
{

constexpr std::size_t ustackSize=mm::page::pageSize*1024;
constexpr std::size_t kstackSize=mm::page::pageSize*1024;
constexpr std::size_t userRSP=(std::size_t)(&ustack_start_address)+ustackSize-8;

class Process
{
public:
    enum TYPE
    {
        KERNEL,
        USER
    };

    enum STATE
    {
        RUNNING,
        WAITING,
        KILLED,
        READY,
        NEW,
        EMPTY,
        BLOCKED,
        SLEEPING
    };

    Process(void* entry,TYPE type);

    ~Process();

    template<class T>
    T* getRegs(){return reinterpret_cast<T*>(regs);}

    template<class T>
    T* getVM(){return reinterpret_cast<T*>(vm);}

    void setState(STATE s){state=s;}

private:
    pid_t pid;
    pid_t ppid;
    TYPE type;
    STATE state;
    void* regs;
    void* vm;
    std::size_t priority;
    std::vector<void*> pages;
};


inline pid_t generateNextPid()
{
    static pid_t cache=0;
    return cache++;
}

}   // end of namespace kernel

#endif