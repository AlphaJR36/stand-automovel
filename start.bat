@echo off
setlocal

echo Compilando o programa...
gcc -o src\output\stand.exe src\main.c src\functions\car.c src\functions\purchase.c src\functions\user.c src\functions\utility.c

rem Verifica o código de erro da compilação
if %errorlevel% neq 0 (
    echo Erro na compilacao.
    exit /b %errorlevel%
)

rem Verifica se o arquivo executável existe
if not exist src\output\stand.exe (
    echo Erro: o arquivo stand.exe nao foi encontrado na pasta src\output.
    exit /b 1
)

echo Mudando para a pasta src\output...
cd src\output

rem Verifica se houve erro ao mudar de diretório
if %errorlevel% neq 0 (
    echo Erro ao mudar para a pasta src\output.
    exit /b %errorlevel%
)

echo Executando o programa stand.exe...
stand.exe

rem Verifica se houve erro ao executar o programa
if %errorlevel% neq 0 (
    echo Erro ao executar o programa.
    pause
)

endlocal
