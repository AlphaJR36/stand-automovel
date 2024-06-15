@echo off
setlocal

echo Compilando o programa...
gcc -o src/output/stand.exe src/main.c src/functions/car.c src/functions/purchase.c src/functions/user.c src/functions/utility.c
if %errorlevel% neq 0 (
    echo Erro na compilacao.
    exit /b %errorlevel%
)

if not exist src/output/stand.exe (
    echo Erro: o arquivo stand.exe nao foi encontrado na pasta src\output.
    exit /b 1
)

echo Mudando para a pasta src\output...
cd src\output
if %errorlevel% neq 0 (
    echo Erro ao mudar para a pasta src\output.
    exit /b %errorlevel%
)

echo Executando o programa stand.exe...
stand.exe
if %errorlevel% neq 0 (
    echo Erro ao executar o programa.
    exit /b %errorlevel%
)

pause
endlocal
