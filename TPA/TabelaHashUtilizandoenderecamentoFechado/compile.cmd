@ECHO OFF
set /p versao=Insira a versao: V
set fileName=TabelaHash
set fullFileName=%fileName%.V%versao%

g++ -Wall -g3 -Wextra -static -static-libgcc -static-libstdc++ rascunho.cpp -o "builds/%fileName%.V%versao%.exe"

if exist "builds/debug.exe" (
   del "builds/debug.exe"
)
g++ -Wall -g3 -Wextra -static -static-libgcc -static-libstdc++ index.cpp -o "builds/debug.exe"

g++ -Wall -g3 -Wextra -static -static-libgcc -static-libstdc++ index.cpp -o "builds/%fullFileName%.exe"

tar -a -c -f "zip/%fullFileName%.zip" *data *builds *.h *.cpp functions.c *.cmd

msg * /v /w %fullFileName%.exe foi compilado!

start "RUN" "builds/%fullFileName%.exe"