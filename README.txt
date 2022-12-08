Program należy uruchamiać w środowisku UNIX. 

Wszystkie skrypty należy uruchamiać mając working directory w folderze scripts.

Obsługę programu najlepiej przeprowadzić używając skryptów znajdujących się w folderze scripts.

Skrypt install_requirements.sh instaluje pakiety wymagane do uruchomienia projektu (cmake i build-essentialls).
Należy go uruchomić jako root.

Skrypt compile.sh kompiluje rozwiązanie do folderu bin.
Skrypt run_tests.sh wykonuje kalkulacje dla wszystkich plików z rodzinami znajdującymi się w folderze test_sets. 
Dla każdego pliku o nazwie $FILE tworzony jest plik ${FILE}.out z wynkiem programu.
Aby dodać własne pliki do przetestowania należy jedynie wkleić je do folderu test_sets.

Obsługa programu.
Gdy program zostanie uruchomiony bez parametrów zostanie uruchomiony tryb interaktywny. 
Tryb interaktywny pozwala wpisywać w pętli pliki oraz wybierać jakie metryki mają być dla nich wykonane,

Gdy program będzie uruchomiony z (dowolną ilością) parametrów będą one potraktowane jako ścieżki do plików.
Program wywoła wtedy wszystkie metryki dla każdego z tych plików i będzie je po kolei wypisywać na stdout, które można przekierować do pliku.

W folderze test_sets znajdują się przykładowe metryki i wyniki dla nich (pliki .out)