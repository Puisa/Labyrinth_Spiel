#include "std_lib_inc.h"
// ein kleines Labyrinth-Spiel //
// Labyrinth-Dimensionen als konstante Ausdruecke
constexpr int kRows = 5;
constexpr int kCols = 5;

// Labyrinth-Definition
// Interpretiere als Zeilen, dann Spalten
const vector<vector<char>> kMaze =
        {
        {'#', '.', '.', '.', '.'},
        {'#', '.', '#', '.', '.'},
        {'.', 'Z', '#', '.', '.'},
        {'.', '#', '#', '#', '.'},
        {'.', '.', '.', '.', '.'},
        };


// Startposition des Spielers
const vector<int> kPlayerStartPosition = {4, 0};    //kPlayerStartPosition = {Zeile, Spalte}
vector<int> playerPos = kPlayerStartPosition;
vector<int> playerPosCheck = playerPos;             // testet mögliche neue Positionen vor einer Bewegung

// Funktion, die den Vektor aufbaut (in diesem Fall das Labyrinth)
// zeigt auch die aktuelle Spielerposition (S) an
void PrintMaze (const vector<vector<char>>  Maze, vector<int>  playerPos)
{
    for (int y = 0; y < kRows; ++y)
    {
        for (int x = 0; x < kCols; ++x)
        {
            if (playerPos[0]== y && playerPos[1] == x)
            {
                cout << 'S'<<" ";
            }
            else
            {
                cout << Maze[y][x]<<" ";
            }
        }
        cout << "\n";
    }

}

// Funktion, die schaut, ob es eine Wand oder ein Weg ist
// gibt je nach Ergebnis false oder true zurück
bool PlayerPositionCheck(const vector<int>& playerPos, const vector<vector<char>>& kMaze)
{
    int newRow = playerPos[0];
    int newCol = playerPos[1];

    if (newRow >= 0 && newRow < kRows && newCol >= 0 && newCol < kCols && kMaze[newRow][newCol] != '#')
    {
        return true;
    }
    return false;
}


// Funktion, um die Position basierend auf der Eingabe zu aktualisieren
vector<int> MovePlayer(char input, vector<int> playerPos)
{
    switch (input)
    {
        case 'a': // Nach links
            playerPos[1] -= 1;
            break;
        case 'd': // Nach rechts
            playerPos[1] += 1;
            break;
        case 's': // Nach unten
            playerPos[0] += 1;
            break;
        case 'w': // Nach oben
            playerPos[0] -= 1;
            break;
    }
    return playerPos;
}

bool InputVerarbeitung (char input, vector<int>& playerPosCheck, vector<int>& playerPos, const vector<vector<char>>& kMaze)
{
    if (input == 'h')  // Hilfe anzeigen
    {
        cout << "Steuere mit w s a d.\n";
        return false; // Keine Bewegung prüfen
    }
    else if (input == 'a' || input == 's' || input == 'd' || input == 'w') // Gültige Eingabe
    {
        playerPosCheck = MovePlayer(input, playerPos);
        return true; // Bewegung prüfen
    }
    else // Ungültige Eingabe
    {
        cout << "Diese Eingabe kenne ich nicht. Gib 'h' ein, um eine Hilfe zu erhalten.\n";
        return false;

    }
}


// Funktion, die Bewegung, Eingabeprüfung und Ausgabe realisiert
int main()
{
    char input;
    PrintMaze(kMaze,playerPos);
    while (cin)
    {
        cin >> input;

        // Funktion für die Eingabeverarbeitung
        if (InputVerarbeitung(input, playerPosCheck, playerPos, kMaze))
        {
            // wenn Bewegung geprüft werden soll
            if (PlayerPositionCheck(playerPosCheck, kMaze))
            {
                playerPos = playerPosCheck;
                PrintMaze(kMaze, playerPos);
            }
            // wenn keine Bewegung geprüft werden muss (z. B. bei ungültiger Eingabe oder Hilfe)
            else
            {
                cout << "Bewegung nicht moeglich!\n";
                PrintMaze(kMaze, playerPos);
            }
        // wenn das Ziel erreicht ist "JUHU"
            if (kMaze[playerPos[0]][playerPos[1]] == 'Z')
            {
                cout << "Ziel erreicht! Herzlichen Glueckwunsch!\n";
                break;
            }
        }
    }
    return 0;
}