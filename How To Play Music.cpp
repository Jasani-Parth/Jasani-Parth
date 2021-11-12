#include<iostream>
#include<windows.h>
#include<MMsystem.h>

using namespace std ;

/** ------------------------------------------------------------------- NOTE ------------------------------------------------------------------- **/
/** Music File Is in .wav format **/

int main(int argc,char *argv[])

{
	for (int i = 0 ; i < 4 ; i++ )
	{
		if(i == 0 )
		{
			std::cout << "FIRST MUSIC" ;

			PlaySound("/**__FILE-PATH__**/.wav",NULL,SND_SYNC) ;
		}

		if( i == 1 )
		{
			std::cout << "Second music" ;

			PlaySound("/**__FILE-PATH__**/.wav",NULL,SND_SYNC) ;
		}

	   if(i == 2)
	   {
	   	    std::cout << "Third Song " ;

	   	    PlaySound("/**__FILE-PATH__**/.wav",NULL,SND_SYNC) ;
	   }

	   if(i==3)
	   {
	   	  std::cout << "Fourth song " ; 

	   	  PlaySound("/**__FILE-PATH__**/.wav",NULL,SND_SYNC) ;
	   }

	}
	return 0 ;
}
