#include <libk/stdio.h>
#include <tty.h>

void kernel_main(void) {
	terminal_initialize();
	for (int i = 0; i < 25; i++) {
		printf("Hello, kernel World!\n");
	}
	for (int i = 0; i < 5; i++) {
		printf("Scroll\n");
	}
}
