#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define size 20

int main(int argc, char const *argv[])
{
  if(argc != 3)
    return 1;

  char buffer[size];

  int tmp_file = open(argv[1], O_RDONLY);
  int destination_file = open(argv[2], O_WRONLY);

  if (tmp_file < 0)
  {
    printf("The file doesn't exist\n");
    close(tmp_file);
    close(destination_file);
    return 1;
  }

  if (destination_file < 0)
  {
   printf("hi\n");
   open(argv[2], O_WRONLY);
   destination_file = creat(argv[2], S_IRUSR);
   printf("Juhu it works\n");
  }

  int readedBytes;
  printf("Writing in destination_file\n");

  readedBytes = read(tmp_file, buffer, size);
  write(destination_file, buffer, readedBytes);

  close(tmp_file);
  close(destination_file);
  return 0;
}
