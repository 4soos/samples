extern "C" void kmain()
{
	const short color = 0x0F00;
	const char* hello = "Hello cpp world!";
	short* vga = (short*)0xb8000;
	for (int i = 0; i<16;++i)
		vga[i+80] = color | hello[i];
}
// nasm -f elf32 boot4.asm -o boot4.o
// i386-elf-g++ -m32 kmain.cc boot4.o -o kernel.bin -nostdlib -ffreestanding -std=c++11 -mno-red-zone 
// -fno-exceptions -nostdlib -fno-rtti -Wall -Wextra -Werror -T linker.ld
