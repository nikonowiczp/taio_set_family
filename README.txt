Program należy uruchamiać w środowisku UNIX. Wszystkie skrypty należy uruchamiać mając working directory w folderze scripts.
Obsługę programu najlepiej przeprowadzić używając skryptów znajdujących się w folderze scripts.
Skrypt install_requirements.sh instaluje pakiety wymagane do uruchomienia projektu (cmake i build-essentialls). Należy go uruchomić jako root.
Skrypt compile.sh kompiluje rozwiązanie do folderu bin.
Skrypt run_tests.sh wykonuje kalkulacje dla wszystkich plików z rodzinami znajdującymi się w folderze test_sets. 
Dla każdego pliku o nazwie $FILE tworzony jest plik ${FILE}.out z wynkiem programu.
Aby dodać własne pliki do przetestowania należy jedynie wkleić je do folderu test_sets.