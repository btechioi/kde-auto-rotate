#!/bin/make

all: build

src = auto-rotate.c

build: auto-rotate

auto-rotate: $(src)
	gcc $(src) `pkg-config --cflags --libs glib-2.0 gio-2.0` -o $@

install: build
	sudo cp auto-rotate /usr/local/bin

config-systemd:
	mkdir -p ~/.config/systemd/user
	cp auto-rotate.service ~/.config/systemd/user/
	systemctl --user enable auto-rotate
	systemctl --user start auto-rotate
	systemctl --user status auto-rotate
	loginctl enable-linger $(USER)

config-systemv:
	echo "Use systemd instead"
	sudo cp auto-rotate.sh /etc/init.d/
	echo "You still have to adjust the run-levels"

run: build
	echo "Make sure you have closed the lid or suspended first: systemctl suspend"
	./auto-rotate --verbose

clean:
	rm -f auto-rotate

.PHONY: all install config-systemd config-systemv run clean
