#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>


struct dirent* direntry;
struct stat attributes;

int main(int argc, char const *argv[])
{
  DIR * dir;

  if (argc == 1)
  {
  	dir = opendir(".");
  }

  if (dir == 0)
  {
      printf("Directory doesn't exist" );
      return 0;
  }
  while ((direntry = readdir(dir)) != 0)
  {
      if(stat(direntry->d_name, &attributes) < 0)
        return 1;

      printf("\n");
      if(S_ISBLK(attributes.st_mode))
        printf("b");
      else if (S_ISREG(attributes.st_mode))
        printf("-");
      else if (S_ISCHR(attributes.st_mode))
        printf("c");
      else if (S_ISLNK(attributes.st_mode))
        printf("l");
      else if (S_ISDIR(attributes.st_mode))
        printf("d");

      printf((attributes.st_mode & S_IRUSR) ? "r" : "-");
  		printf((attributes.st_mode & S_IWUSR) ? "w" : "-");
  		printf((attributes.st_mode & S_IXUSR) ? "x" : "-");
  		printf((attributes.st_mode & S_IRGRP) ? "r" : "-");
  		printf((attributes.st_mode & S_IWGRP) ? "w" : "-");
  		printf((attributes.st_mode & S_IXGRP) ? "x" : "-");
  		printf((attributes.st_mode & S_IROTH) ? "r" : "-");
  		printf((attributes.st_mode & S_IWOTH) ? "w" : "-");
      printf((attributes.st_mode & S_IXOTH) ? "x " : "- ");

      printf("%d ",attributes.st_uid);
      printf("%d ",attributes.st_gid);
      printf("%ld \t",attributes.st_size);

      char time[18];
      strftime(time, 18, "%Y-%m-%d-%H-%M", localtime(&attributes.st_mtime));
      printf("%s ",time);
      printf("%s",direntry->d_name );
  }
  closedir(dir);
  printf("\n");
  return 0;
}
