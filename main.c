#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include<stdio.h>
double wcount(char buffer[],char word[])
{
            char string[100];

            sprintf(string,"awk '$1 ~ /%s/ {++c} END {print c}' FS=: %s > count.dat",word,buffer);
            system(string);
            sprintf(string,"awk '$1 ~ / / {++c} END {print c}' FS=: %s > countw.dat",buffer);
            system(string);
            FILE *f1, *f2;
            char nr[100],dr[100];
            int i;
            int num=0, den=0;
            f1 = fopen("count.dat","r");
            fscanf(f1,"%s",nr);
            //printf("%s",nr);
            fclose(f1);
            fflush(f1);
            f2 = fopen("countw.dat","r");
            fscanf(f2,"%s",dr);
            //printf("%s\n",dr);
            fclose(f2);
            fflush(f2);
            /*for(i=2;i>=0;i--)
            {
                num = num*10 + nr[i];
                //printf("%c",nr[i]);
            }
            for(i=2;i>=0;i--)
            {
                den = den*10 + dr[i];
            }*/
            num = atoi(nr);
            den = atoi(dr);
            //printf("nr= %d dr= %d\n",num,den);
            float value;
            value = (float)num/den;
            //printf("val = %f\n", value);
            return value;

}

long int count=0;
void list_dir(const char* directory_name, char word[]) {
    DIR* directory_handle = opendir(directory_name);
    if (directory_handle == NULL) {
        fprintf(stderr, "Could not open directory %s.\n", directory_name);
        return;
    }

    char buffer[1024], string[500];

    struct dirent* dentry;
    int directory_name_length = strlen(directory_name);

    memcpy(buffer, directory_name, directory_name_length);
    buffer[directory_name_length] = '/';

    while ((dentry = readdir(directory_handle)) != NULL) {
        char* name = dentry->d_name;
        int length = strlen(name);

        // Skip the dotted elements.
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;

        // Concatenate the directory name with the element name.
        memcpy(buffer + directory_name_length + 1, name, length);
        buffer[directory_name_length + 1 + length] = 0;

        //printf("%s\n", buffer);
        FILE *fp;
        fp = fopen(buffer,"r");
        if(strlen(buffer)>10)
        {
           // printf("file opened\n");

            /*while(!feof(fp))
            {
                fscanf(fp,"%s",string);
                if(!strcmp(string,"Thesis"))
                {
                    count++;
                }
            }*/
            float val;
            val = wcount(buffer, word);
            printf("feature = %f \n", val);



        fclose(fp);
        fflush(fp);
       }
        // Proceed recursively if the element is a directory.
        struct stat s;
        if (stat(buffer, &s) != 0) {
            fprintf(stderr, "WARNING: stat() failed on %s\n", buffer);
            continue;
        }

        mode_t mode = s.st_mode;
        if (mode & S_IFDIR && !(mode & S_IFLNK)) {
            list_dir(buffer,word);
        }

    }
    closedir(directory_handle);

}

int main(int argc, char** argv) {
    /*if (argc != 2) {
        fprintf(stderr, "Expected exactly 2 arguments.\n");
        return -1;
    }*/
    int i;
    list_dir("../wordcount2/webkb/staff","master");
    //system("awk 'END{print c}{c+=$0}' filewordcount.txt > result.txt");
    FILE *file;
    file = fopen("result.txt","r");
    char freq[100];
    fscanf(file,"%s",freq);
    fclose(file);
    //puts(freq);
   /* for( i=strlen(freq)-1;i>=0;i--)
    {
        count = count*10 + freq[i];
    }*/
    //printf("no of occurences= %s\n",count);

    return 0;
}
