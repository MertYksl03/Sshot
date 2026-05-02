CC      = gcc
CFLAGS  = -Wall -Werror -g -std=c99 $(shell pkg-config --cflags gio-2.0 libnotify)
LIBS    = -lSDL3 -lSDL3_image -lm $(shell pkg-config --libs gio-2.0 libnotify) -lX11

SRC_DIR = src
OBJ_DIR = obj
OUT     = sshot

PREFIX        = /usr
BINDIR        = $(PREFIX)/bin
APPDIR        = $(PREFIX)/share/applications
ASSETSDIR     = $(PREFIX)/share/sshot

# Recursively find all source files and map them to object files
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# ──────────────────────────────────────────────
# Targets
# ──────────────────────────────────────────────

.PHONY: all build run clean install uninstall

all: build

## Final linking
$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

## Incremental compilation, preserving directory structure
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build: $(OUT)

run: build
	./$(OUT)

clean:
	@rm -rf $(OBJ_DIR) $(OUT)
	@echo "Cleaned build artifacts."

# ──────────────────────────────────────────────
# Install / Uninstall
# ──────────────────────────────────────────────

_check_root:
	@if [ "$$(id -u)" -ne 0 ]; then \
		echo "Error: This target must be run as root.  Use: sudo make install"; \
		exit 1; \
	fi

install: build _check_root
	@echo "Installing sshot..."
	@install -Dm755 $(OUT)           $(BINDIR)/$(OUT)
	@install -Dm644 sshot.desktop    $(APPDIR)/sshot.desktop
	@cp -r src/assets                $(ASSETSDIR)
	@update-desktop-database         $(APPDIR)
	@echo "Done. sshot installed to $(BINDIR)/$(OUT)"

uninstall: _check_root
	@echo "Uninstalling sshot..."
	@rm -f  $(BINDIR)/$(OUT)
	@rm -f  $(APPDIR)/sshot.desktop
	@rm -rf $(ASSETSDIR)
	@update-desktop-database $(APPDIR)
	@echo "Done."