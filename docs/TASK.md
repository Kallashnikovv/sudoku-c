Celem projektu jest stworzenie gry Sudoku w języku C. Program powinien umożliwiać generowanie planszy o różnych rozmiarach, zapewniając przy tym, że wygenerowane Sudoku będzie miało rozwiązanie.  

Opis zasad gry Sudoku
:

    Sudoku to łamigłówka liczbowa, której celem jest wypełnienie kwadratowej planszy o wymiarach n×n (najczęściej 9×9) cyframi od 1 do n tak, aby:
    W każdym wierszu każda cyfra występowała dokładnie jeden raz. W każdej kolumnie każda cyfra występowała dokładnie jeden razW każdym z mniejszych kwadratów o wymiarach √n×√n każda cyfra występowała dokładnie jeden raz
    Standardowa plansza Sudoku ma wymiary 9×9 i jest podzielona na 9 mniejszych kwadratów 3×3. Na początku gry niektóre komórki są już wypełnione liczbami (podpowiedzi), a zadaniem gracza jest wypełnienie pozostałych komórek zgodnie z powyższymi zasadami.
    

Wymagania funkcjonalne  
:

    Program powinien generować poprawną planszę Sudoku z rozwiązaniem
    Użytkownik powinien móc wybrać rozmiar planszy (minimum trzy opcje: 4×4, 9×9, 16×16)
    Program powinien oferować różne poziomy trudności, określające liczbę widocznych podpowiedzi

:

    Czytelne wyświetlanie planszy w konsoli
    Menu wyboru opcji (nowa gra, wybór rozmiaru planszy, poziom trudności, instrukcja, wyjście)
    Możliwość zapisania i wczytania stanu gry

:

    Wprowadzanie ruchów przez użytkownika (wskazanie komórki i wartości)
    Sprawdzanie poprawności ruchów gracza
    Możliwość usunięcia wprowadzonej wartości
    Opcjonalnie: podpowiedzi dla gracza

Algorytm generowania planszy Sudoku  

    Generowanie poprawnej planszy Sudoku wymaga kilku kroków:
    Wygenerowanie kompletnie wypełnionej planszy zgodnej z zasadami Sudoku
    Usunięcie niektórych cyfr, upewniając się, że plansza nadal ma dokładnie jedno rozwiązanie
    Można wykorzystać algorytm z nawrotami (backtracking) do generowania planszy. Istotne jest, aby:

        Losowo wybierać wartości, które będą wstawiane
        Sprawdzać poprawność planszy po każdym wstawieniu
        W przypadku zapętlenia, cofać się i próbować innych wartości

Pomocne materiały i linki

    Algorytm generowania planszy Sudoku (Geeks for Geeks) - https://www.geeksforgeeks.org/program-sudoku-generator/

Kryteria oceny
Projekt będzie oceniany według następujących kryteriów:
:

    Czytelność i struktura kodu
    Poprawne nazewnictwo zmiennych i funkcji
    Komentarze wyjaśniające skomplikowane części kodu
    Modularność i możliwość ponownego wykorzystania kodu (ważne)
    Znajomość kodu :)

:

    Brak wycieków pamięci (poprawne zwalnianie zaalokowanej pamięci)
    Poprawna obsługa wskaźników
    Sprawdzanie granic tablic i poprawności danych wejściowych

:

    Minimalizacja alokacji pamięci
    Efektywne struktury danych
    Unikanie niepotrzebnego duplikowania danych

:

    Program działa bez błędów i crashów
    Plansza jest poprawnie generowana i ma rozwiązanie
    Wszystkie wymagane funkcjonalności zostały zaimplementowane

:

    Intuicyjny sposób wprowadzania ruchów
    Czytelna prezentacja planszy
    Komunikaty dla użytkownika są jasne i pomocne
    Statystyki gry (czas, etc.)

Uwagi dodatkowe

    Projekt należy wykonać samodzielnie (można oczywiście używać LLMów, natomiast polecam dopiero po godzinie od zablokowania się nad czymś, lepiej was wyjdzie, jeśli pogłówkujecie sami, trust me)
    Korzystanie z dodatkowych bibliotek jest dozwolone natomiast, nie jest raczej potrzebne
    Kod musi być kompilowany bez ostrzeżeń przy użyciu standardowych flag kompilacji

Terminy i oddawanie projektu

    Projekt oddajemy w formie repozytorium na GitHubie, które ma:
    README.md z opisem programu, wiadomymi problemami etc.
    Screenshoty z działania programu lub ładny gif z rozgrywki
    Wasz ulubiony meme, z tego miesiąca (aby umilić sprawdzanie)