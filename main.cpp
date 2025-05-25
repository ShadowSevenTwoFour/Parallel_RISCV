#include "Assembler.h"
#include "ExecutionUnit.h"
#include "RegFile.h"
#include "Memory.h"

int main() {
    RegFile rf;
    Memory mem(1024);
    ExecutionUnit exec(4);
    exec.bind(&rf, &mem);

    auto program = assemble("user/usertest_1.s"); 
    for (const auto& instr : program)
        exec.submit(instr);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    printf("x3 = %ld\n", rf[3]);
}
