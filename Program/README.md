Aby uruchomić program potrzebny jest kompilator GCC w wersji 6.0 w górę.

Do kompilowania używana jest flaga -fconcepts, wspierająca koncepty.

Sposób kompilacji (Windows):

g++ Main.cpp Edge.cpp Edge.h Operations.cpp Operations.hpp Concepts.hpp Concepts.cpp -fconcepts -o out

Uruchomienie:

out
