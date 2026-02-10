#include "crawl.h"

int returnValue = 0;
void returnVal(const int x) { returnValue = x;}

int main(void)
{
    run(640, 480, "Crawl", returnVal);
    return returnValue;
}