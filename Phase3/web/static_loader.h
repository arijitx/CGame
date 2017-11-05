#include<stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>

string static_files_name[2]={"static/html/index.html","static/js/main.js"};
int static_files_count=2;
map<string,char*> static_files;

char* load_static(const char* file_name){
    char* f;
    int size;
    struct stat s;
    int fd = open (file_name, O_RDONLY);
    int status = fstat (fd, & s);
    size = s.st_size;
    f= (char *) mmap (0, size, PROT_READ, MAP_SHARED, fd, 0);
    return f;
}

int load_all_static_files(){
    for(int i=0;i<static_files_count;i++){
        char *x;
        x=load_static(static_files_name[i].c_str());
        static_files[static_files_name[i]]=x;
        //cout<<"file"<<static_files[static_files_name[i]]<<endl;
    }
    return 1;
}
