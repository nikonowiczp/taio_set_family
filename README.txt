INSTRUKCJA

W folderze bin znajdują się dwa foldery - taio_gui oraz taio_console.

Istnieje statyczny limit długości ścieżki do plików: MAXPATH 2048, znajduje się w pliku src/taio_console/main.c
Istnieje statyczny limit długości linii w pliku wejściowym: MAX_LENGTH 32768 w pliku src/taio_lib/SetParser.h

Taio_gui to wersja rozwiązania z interfejsem użytkownika, taio_console bez.
Oba rozwiązania wykonują ten sam kod (napisany w języku C).
Zalecane jest używane wersji GUI - jest ona łatwiejsza w użytkowaniu.
Pozwala wczytywać i wykonywać algorytmy dla całych folderów lub plików wybranych w eksploratorze windows.

Taio_console to wersja konsolowa. Pozwala ona na zapętlone wczytywanie programów oraz zapisywanie wyników do plików.
Taio_console posiada również tryb nieinteraktywny. 
Wystarczy jako pierwszy argument podać folder wyjściowy a jako kolejne wpisywać pliki wejściowe. 
Uruchomić z argumentem -h aby wyświetlić pomoc.

KOMPILACJA

Kompilacja wersji taio_console wymaga jedynie kompilatora języka C. 
Została przetestowana i skompilowana za pomocą kompilatora mingw81_32.

Kompilacja wersji taio_gui wymaga posiadania zainstalowanych bibliotek Qt5.
Została przetestowana i skompilowana za pomocą kompilatora mingw81_32 i wersji biblioteki QT 5.15.2

Do tworzenia plików kompilacji używany jest CMake, a do kompilacji może być dowolny program typu make.
Aby skompilować tylko projekt taio_console należy użyć komendy 
Build: cmake.exe --build ${OUTPUT} --target taio_console
${OUTPUT} to folder wyjściowy. Analogicznie dla projektu taio_gui lub all aby skompilować oba.

Aby skompilować którykolwiek projekt należy posiadać odpowiednio skonfigurowane środowisko:
w zmiennej PATH musi znaleźć się cmake, kompilator i w przypadku GUI również odpowiedni qmake(dla takiego samego kompilatora jak używany).