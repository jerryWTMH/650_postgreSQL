#include "exerciser.h"

void exercise(connection *C)
{
    //test_player(C);
    query1(C, 1, 35, 40, 0, 0, 0, 0, 5, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query2(C, "Maroon");
    query3(C, "Duke");
    query4(C, "NC", "DarkBlue");
    query5(C, 12);
}
