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

#include <arch/x86/x64/gdt.h>
#include <kernel/mm/mem_layout.h>

KEVOS_NSS_3(arch,x86,x64);

SystemDescriptor GDT::items[gdtSize];

struct __packed__
{
    uint32_t reserved1;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved2;
    uint64_t ist0;
    uint32_t reserved3[15];
}__knTSS;

void GDT::setItem(size_t index,uint64_t base,
                uint32_t limit,uint8_t dpl,uint8_t code,uint8_t tss)
{
    if(index>=gdtSize)
        return;
    uint8_t* gdtHelper=reinterpret_cast<uint8_t*>(&items[index]);
    *reinterpret_cast<uint16_t*>(&gdtHelper[0])=limit&0xFFFF;
    *reinterpret_cast<uint16_t*>(&gdtHelper[2])=base&0xFFFF;
    gdtHelper[4]=(base>>16)&0xFF;

    gdtHelper[5]=(tss?0x89:0x92)|((dpl&0x3)<<5)|(code?0x8:0);
    gdtHelper[6]=((limit>>16)&0xF)|(code?0xA0:0xC0);

    gdtHelper[7]=(base>>24)&0xFF;
    *reinterpret_cast<uint32_t*>(&gdtHelper[8])=(base>>32)&0xFF;

    *reinterpret_cast<uint32_t*>(&gdtHelper[12])=0;
}

void GDT::initialize()
{
    __knTSS.ist0=reinterpret_cast<uint64_t>(&kstack_start_address);
    __knTSS.rsp0=(uint64_t)(&kstack_start_address);

    setItem(3, 0, 0, 3, 1, 0);
    setItem(4, 0, 0, 3, 0, 0);
    setItem(5, reinterpret_cast<uint64_t>(&__knTSS), sizeof(__knTSS)-1, 0, 0, 1);

    struct __packed__ GDTPointer
    {
        uint16_t limit;
        uint64_t address;
    } gdtPtr={
        sizeof(items)-1,
        reinterpret_cast<uint64_t>(items)
    };
    __asm__ __volatile__("lgdt %[gdtr]" : : [gdtr]"m"(gdtPtr));
    __asm__ __volatile__("ltr %%ax": : "a"(__KERNEL_TSS));
}

KEVOS_NSE_3(x64,x86,arch);
