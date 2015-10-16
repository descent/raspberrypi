
#ARMGNU ?= arm-none-eabi
ARMGNU ?= arm-linux-gnueabihf

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 

uart_mmu.bin : uart_mmu.elf
	$(ARMGNU)-objdump -D $< > uart05.list
	$(ARMGNU)-objcopy $< -O ihex $@.hex
	$(ARMGNU)-objcopy $< -O binary $@

uart_mmu.elf : start.o periph.o uart05.o cortex_a_mmu.o
	$(ARMGNU)-ld $^ -T memmap -o $@

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.s

start.o : start.s
	$(ARMGNU)-as start.s -o start.o

uart05.o : uart05.c
	$(ARMGNU)-gcc $(COPS) -c uart05.c -o uart05.o
cortex_a_mmu.o: cortex_a_mmu.c
	$(ARMGNU)-gcc $(COPS) -c $<

periph.o : periph.c
	$(ARMGNU)-gcc $(COPS) -c periph.c -o periph.o




LOPS = -Wall -m32 -emit-llvm
LLCOPS0 = -march=arm 
LLCOPS1 = -march=arm -mcpu=arm1176jzf-s
LLCOPS = $(LLCOPS1)
COPS = -Wall  -O2 -nostdlib -nostartfiles -ffreestanding
OOPS = -std-compile-opts

clang : uart05.clang.bin

uart05.bc : uart05.c
	clang $(LOPS) -c uart05.c -o uart05.bc

periph.bc : periph.c
	clang $(LOPS) -c periph.c -o periph.bc


uart05.clang.elf : memmap start.o uart05.bc periph.bc
	llvm-link periph.bc uart05.bc -o uart05.nopt.bc
	opt $(OOPS) uart05.nopt.bc -o uart05.opt.bc
	llc $(LLCOPS) uart05.opt.bc -o uart05.clang.s
	$(ARMGNU)-as uart05.clang.s -o uart05.clang.o
	$(ARMGNU)-ld -o uart05.clang.elf -T memmap start.o uart05.clang.o
	$(ARMGNU)-objdump -D uart05.clang.elf > uart05.clang.list

uart05.clang.bin : uart05.clang.elf
	$(ARMGNU)-objcopy uart05.clang.elf uart05.clang.hex -O ihex
	$(ARMGNU)-objcopy uart05.clang.elf uart05.clang.bin -O binary


