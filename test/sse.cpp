#include <iostream>
#include <nogara/vector.hpp>
#include <nogara/expression/sse/traits.hpp>
#include <nogara/expression/io.hpp>

struct cpuinfo_t{
    union{
        unsigned eax;
        struct{
            unsigned stepping:4;
            unsigned model:4;
            unsigned family:4;
            unsigned processer_type:2;
            unsigned resaved1:2;
            unsigned ex_model:4;
            unsigned ex_family:8;
            unsigned resaved2:4;
        };
    };

    // ebx;
    union{
        unsigned ebx;
        struct{
            unsigned brand_index:8;
            unsigned line_size:8;
            unsigned processer:8;
            unsigned resaved22:8;
        };
    };
    // ecx
    union{
        unsigned ecx;
        struct{
            unsigned sse3:1;
            unsigned rev3:2;
            unsigned monitor:1;
            unsigned ds_cpl:1;
            unsigned vmx:1;//Virtualization Technology
            unsigned rev31:1;
            unsigned est:1;
            unsigned tm2:1;
            unsigned ssse3:1;//Supplemental Streaming SIMD Extensions 3
            unsigned cnxt_id:1;
            unsigned rev4:8;
            unsigned sse41:1;
            unsigned sse42:1;
            unsigned rev41:11;
        };
    };
    //edx
    union{
        unsigned edx;
        struct{
            unsigned fpu:1;
            unsigned vme:1;
            unsigned de:1;
            unsigned pse:1;
            unsigned tsc:1;
            unsigned msr:1;
            unsigned pae:1;
            unsigned mce:1;
            unsigned cx8:1;
            unsigned apic:1;
            unsigned rev5:1;
            unsigned sep:1;
            unsigned mtrr:1;
            unsigned pge:1;
            unsigned mca:1;
            unsigned cmov:1;
            unsigned pat:1;
            unsigned pse_36:1;
            unsigned psn:1;
            unsigned clfsh:1;
            unsigned rev6:1;
            unsigned ds:1;
            unsigned acpi:1;
            unsigned mmx:1;
            unsigned fxsr:1;
            unsigned sse:1;
            unsigned sse2:1;
            unsigned ss:1;
            unsigned htt:1;
            unsigned tm:1;
            unsigned ia64:1;
            unsigned pbe:1;
        };
    };
};

cpuinfo_t cpuid(){
    cpuinfo_t regs;
    asm volatile("movl $0x01, %%eax;"
                 "cpuid" :
                 "=a" (regs.eax),
                 "=b" (regs.ebx),
                 "=d" (regs.edx),
                 "=c" (regs.ecx));
    return regs;
}

#define support_check(cond) ((cond) ? "support" : "not_support")

void output(char const* check, char const* result){
    std::cout << check << " is " << result << std::endl;
}

int main(){
    cpuinfo_t cpu = cpuid();
    output("MMS",    support_check(cpu.mmx));
    output("SSE",    support_check(cpu.sse));
    output("SSE2",   support_check(cpu.sse2));
    output("SSE3",   support_check(cpu.sse3));
    output("SSSE3",  support_check(cpu.ssse3));
    output("SSE4.1", support_check(cpu.sse41));
    output("SSE4.2", support_check(cpu.sse42));
    output("IA-64", support_check(cpu.ia64));
    output("APiC", support_check(cpu.apic));
}
