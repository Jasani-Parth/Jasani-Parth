#include<iostream>
#include<windows.h>
#include<MMsystem.h>

using namespace std ;

/** ------------------------------------------------------------------- NOTE ------------------------------------------------------------------- **/
/** Music File Is in .wav format **/

int main(int argc,char *argv[])
{
	PlaySound("/**__FILE-PATH__**/.wav",NULL,SND_SYNC) ;
	return 0 ;
}
