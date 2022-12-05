ISODIR=isodir
BOOTDIR=$(ISODIR)/boot
ISONAME=Shea.iso

BINNAME=Shea.kernel
BINDIR=kernel

.PHONY: all clean install

all: install

clean:
	cd kernel;\
	make clean;\
	cd ../

install:
	cd kernel;\
	$(MAKE) -f ./Makefile;\
	cd ../;\

	mkdir -p $(ISODIR);\
	mkdir -p $(BOOTDIR);\
	mkdir -p $(BOOTDIR)/grub;\

	cp grub.cfg $(BOOTDIR)/grub/grub.cfg;\
	cp $(BINDIR)/$(BINNAME) $(BOOTDIR)/$(BINNAME);\
	grub-mkrescue -o $(ISONAME) $(ISODIR)

