#Commande du compilateur
CFLAGS= -std=gnu99 -ffreestanding -O2 -Wall -Wextra
CC= /home/louis/Documents/os/cross_compiler_32bits/bin/i686-elf-gcc $(CFLAGS)

ASFLAGS=
AS= /home/louis/Documents/os/cross_compiler_32bits/bin/i686-elf-as $(ASFLAGS)

LDFLAGS= -T build/linker.ld -ffreestanding -O2 -nostdlib -lgcc
LD= /home/louis/Documents/os/cross_compiler_32bits/bin/i686-elf-gcc $(LDFLAGS)
#
projet_name= Shea.bin
Projet = build/bin/$(projet_name)
#Sources du projet
Sources_c = src/kernel.c

Sources_s = src/boot.s


Objects_c = $(Sources_c:.c=.o)
Objects_s = $(Sources_s:.s=.o)

Dependances = $(Sources:.c=.d)

iso_folder = isodir
boot_folder = $(iso_folder)/boot
iso_name = $(projet_name:.bin=.iso)

create_iso: build
	cp $(Projet) $(boot_folder)/$(projet_name)
	grub-mkrescue -o $(iso_name) $(iso_folder)

build: $(Objects_c) $(Objects_s)
	$(LD) -o $(Projet) $+
	rm -f $(Objects_c) $(Objects_s)

# Créer les fichier objets pour les linker ensuite
$(Objects_c): $(Sources_c)
	$(CC) -o $@ -c $<

$(Objects_s): $(Sources_s)
	$(AS) $< -o $@ 


# inclusion des dependances
-include $(Dependances)