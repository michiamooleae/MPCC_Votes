#include "mpcc.h"

int main()
{


    MPCC votes("https://en.numista.com/forum/topic73312.html");
    votes.get_voting_results();


    return EXIT_SUCCESS;
}
