#include<stdlib.h>
//Standard Library for C
#include<unistd.h>
//
#include<termios.h>
//Terminal library for setting off flags.
struct termios orig_termios;//structure to store orignal state.
 ////function to disable raw mode that is set by our progrmam
void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
	//Standard file input, terminal flush buffer, and orignal terminal attributes used.
}
//function to enable raw mode i.e. set attributes by our wish.
void enableRawMode()
{
	tcgetattr(STDIN_FILENO,&orig_termios);//gets attributes of the orignal terminal.
	atexit(disableRawMode);

	struct termios raw=orig_termios;
	raw.c_lflag &= ~(ECHO);//ECHO FLAG IS SET OFF.
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);// raw attributes are set.
}
int main()
{
	enableRawMode();//raw mode is enabled.
	char c;
	while(read(STDIN_FILENO,&c,1)==1 && c!='q');//until q is read keep reading from user in terminal.
	return 0;
}