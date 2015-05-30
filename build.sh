g++ \
-std=c++11 \
./source/GLAH/Vector.cpp \
./source/GLAH/GLAHGraphics.cpp \
./source/spritesheet/SpriteSheet.cpp \
./source/spritesheet/UVTranslator.cpp \
./source/sqlite/DatabaseManager.cpp \
./source/game_state/OuterLoop.cpp \
./source/game_state/ProgramState.cpp \
./source/game_state/PSGameLoop.cpp \
./source/game_state/PSLevelEditor.cpp \
./source/game_state/PSLevelModifySelect.cpp \
./source/game_state/PSLevelSelect.cpp \
./source/game_state/PSMainMenu.cpp \
./source/game_objects/Cannon.cpp \
./source/game_objects/Enemy.cpp \
./source/game_objects/EnemySpawner.cpp \
./source/game_objects/GameObject.cpp \
./source/game_objects/GLText.cpp \
./source/game_objects/Goal.cpp \
./source/game_objects/Platform.cpp \
./source/game_objects/Player.cpp \
./source/game_objects/PlayerProjectile.cpp \
./source/game_objects/Shell.cpp \
./source/data/DBLevel.cpp \
./source/data/FileSettings.cpp \
./source/data/IniFile.cpp \
./source/math/Collision.cpp \
./source/main.cpp \
-I./include \
-lSDL2 \
-lSDL2_image \
-lsqlite3 \
-w \
-fmax-errors=1 


