#include "exerciser.h"

void exercise(connection *C)
{
    // //test_player(C);

    query1(C, 1, 35, 40, 0, 0, 0, 0, 5, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query1(C, 1, 15, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0.4, 1.4);
    // query1(C, 0, 35, 40, 0, 0, 0, 3, 5, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query2(C, "Gold");
    query2(C, "Maroon");
    query3(C, "Duke");
    query3(C, "GeorgiaTech");
    query4(C, "MA", "Maroon");
    query4(C, "NC", "DarkBlue");
    query5(C, 12);
}
