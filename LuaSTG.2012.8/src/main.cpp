#include "lstg.h"

int main(int argc, char** argv)
{
	lstg * l=lstg_open();
	l->start(argc,argv);
	lstg_close();
}