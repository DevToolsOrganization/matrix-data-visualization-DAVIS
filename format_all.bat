@echo off
REM === Настройки ===
REM Относительный путь к clang-format.exe
set CLANG_FORMAT=%~dp0code_style\cpp\clang-format.exe

REM Корневая папка проекта (текущая)
set PROJECT_DIR=%cd%

echo start to format all *.cpp and *.h files in %PROJECT_DIR% ...

REM Рекурсивный обход всех файлов
for /R "%PROJECT_DIR%" %%f in (*.cpp *.h) do (
    echo format: %%f
    "%CLANG_FORMAT%" -i "%%f"
)

echo all code base formatting process is finished
ping localhost -n 3 >nul

