.thumb
.syntax     unified

// ON START:
// - CPU reads isr_vectors and sets it as interrupts catchers
// - Sets isr_vectors[0] as SP
// - Jumps on Platform_ResetHandler

.type       Platform_ResetHandler, %function
.global     Platform_ResetHandler
Platform_ResetHandler:
    b       Kernel_EntryPoint