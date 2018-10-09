#if 0
#include "mpcc.h"
#endif

#include "uncroppedimagesfinder.h"

int main()
{
 #if 0
    MPCC votes("https://en.numista.com/forum/topic73312.html");
    votes.get_voting_results();
#endif

    UncroppedImagesFinder uif("New Caledonia");
    uif.print();

}
