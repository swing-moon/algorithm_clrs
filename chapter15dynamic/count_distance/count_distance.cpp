#include "count_distance.h"
#include <string.h>
using namespace std;
int main()
{
    char x[]=" algorithm";
    char y[]=" altruistic";
    int x_len=strlen(x),y_len=strlen(y);
    TABLE distance=count_distance(x,y,x_len,y_len);
    PRINT_sequence(distance,x_len,y_len);
}