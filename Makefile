NAME = MyGame
SRC = src/main.cpp TriEngine/src/TriEngine.cpp TriEngine/src/TriSprite.cpp TriEngine/src/TriObject.cpp TriEngine/src/TriCamera.cpp TriEngine/src/TriGroup.cpp TriEngine/src/TriClass.cpp
OBJ = $(SRC:%.cpp=%.o)

# --- CONFIGURATION PAR DÉFAUT ---
CC = g++
RM = rm -rf
CXXFLAGS = -std=c++17 -O3 -I lib/raylib/src/

# Chemin vers la lib raylib statique
RAYLIB_PATH = lib/raylib/src
RAYLIB_LIB = $(RAYLIB_PATH)/libraylib.a
RES_DIR = AppPackageResources
WINDRES = windres

# Debug flags
ifeq ($(DEBUG), 1)
	CXXFLAGS += -fsanitize=address -g3
endif

# --- DÉTECTION DU SYSTÈME / PLATEFORME ---

# Si l'utilisateur ne précise pas, on devine
ifndef PLATFORM
	ifeq ($(OS),Windows_NT)
		PLATFORM = WINDOWS
	else
		UNAME_S := $(shell uname -s)
		ifeq ($(UNAME_S),Darwin)
			PLATFORM = MACOS
		else
			PLATFORM = LINUX
		endif
	endif
endif

# --- CONFIGURATION SPÉCIFIQUE ---

# 1. WEB (EMSCRIPTEN)
ifeq ($(PLATFORM), WEB)
	CC = em++
	EXT = .html
# Flags spécifiques web : on preload le dossier assets
	LDFLAGS = -s USE_GLFW=3 -s ALLOW_MEMORY_GROWTH=1 -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap','requestFullscreen']" --preload-file assets --shell-file $(RES_DIR)/shell.html --preload-file $(RES_DIR)/favicon.ico@/favicon.ico
# LDFLAGS = -s USE_GLFW=3 -s ASYNCIFY --preload-file assets
# On force Raylib en mode WEB
	RAYLIB_MODE = PLATFORM_WEB
	RAYLIB_LIB = $(RAYLIB_PATH)/libraylib.web.a
	NAME = index
# Emscripten inclut ses propres libs, pas besoin de frameworks systemes
	SYS_LIBS = 

# 2. WINDOWS
else ifeq ($(PLATFORM), WINDOWS)
	EXT = .exe
	LDFLAGS = -static -mwindows
	RAYLIB_MODE = PLATFORM_DESKTOP
# Libs système Windows (GDI, WinMM, OpenGL)
	SYS_LIBS = -lopengl32 -lgdi32 -lwinmm
	OBJ += resource.o

# 3. MACOS
else ifeq ($(PLATFORM), MACOS)
	EXT = 
	LDFLAGS = 
	RAYLIB_MODE = PLATFORM_DESKTOP
# Frameworks Apple
	SYS_LIBS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

# 4. LINUX (Au cas où)
else
	EXT = 
	LDFLAGS = 
	RAYLIB_MODE = PLATFORM_DESKTOP
	SYS_LIBS = -lGL -lm -lpthread -ldl -lrt -lX11
endif

# --- RÈGLES DE COMPILATION ---

all: $(NAME)$(EXT)

# Compilation des objets
%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

resource.o: $(RES_DIR)/resource.rc
	$(WINDRES) $(RES_DIR)/resource.rc -o resource.o -I $(RES_DIR)

# Linkage Final
$(NAME)$(EXT): $(OBJ)
	@echo "Building Raylib for $(PLATFORM)..."
	make -C $(RAYLIB_PATH) PLATFORM=$(RAYLIB_MODE)
	@echo "Linking $(NAME)$(EXT)..."
	$(CC) $(CXXFLAGS) $(OBJ) $(RAYLIB_LIB) $(SYS_LIBS) $(LDFLAGS) -o $(NAME)$(EXT)

# Règle spécifique pour le Bundle Mac (ne fonctionne que sur Mac)
app: $(NAME)
ifeq ($(PLATFORM), MACOS)
# 1. Création de la structure
	@rm -rf $(NAME).app
	@mkdir -p $(NAME).app/Contents/MacOS
	@mkdir -p $(NAME).app/Contents/Resources
	
# 2. Copie des fichiers
	@cp $(NAME) $(NAME).app/Contents/MacOS/$(NAME)
	@cp $(RES_DIR)/Info.plist $(NAME).app/Contents/
	@cp $(RES_DIR)/favicon.icns $(NAME).app/Contents/Resources/favicon.icns
	@cp -r assets $(NAME).app/Contents/Resources/assets
	
# 3. NETTOYAGE AGRESSIF (L'ordre est important)
# Supprime les fichiers .DS_Store
	@find "$(NAME).app" -name ".DS_Store" -delete
# Supprime les fichiers cachés ._ (souvent la cause de l'erreur "resource fork")
	@find "$(NAME).app" -name "._*" -delete
# Nettoie tous les attributs étendus (quarantine, etc.) récursivement
	@xattr -cr "$(NAME).app"
	
# 4. Signature
	@echo "Signing..."
	@codesign --force --deep --sign - "$(NAME).app"
	@echo "App Bundle created successfully."
else
	@echo "Error: 'make app' is only for MacOS."
endif

dist: $(NAME)$(EXT)
ifeq ($(PLATFORM), WINDOWS)
	@echo "Création du package Windows..."
	@rm -rf Build_Windows
	@mkdir -p Build_Windows/$(NAME)
	
# Copie de l'exe et des assets dans un dossier propre
	@cp $(NAME).exe Build_Windows/$(NAME)/
	@cp -r assets Build_Windows/$(NAME)/assets
else
	@echo "Error: 'make dist' is only for MacOS."
endif

clean:
	@$(RM) $(OBJ)
	@$(RM) *.data *.wasm *.js *.html # Nettoyage Web

fclean: clean
	@$(RM) $(NAME) $(NAME).exe
	@$(RM) -r $(NAME).app
	make -C $(RAYLIB_PATH) clean

re: fclean all

re_dist: fclean dist

re_app: fclean app

.PHONY: all clean fclean re app