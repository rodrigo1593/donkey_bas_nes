@echo off

call _compile game nrom_256_vert

del *.o

sleep 5
D:\--Games--\Nestopia\nestopia.exe %cd%/game.nes"