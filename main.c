#include <stdio.h>


#define MAX 102
#define CREATEMODEL(modelFile,fileName, path) (snprintf(modelFile, MAX, "%s%s%s", path, fileName,".java"))
#define CREATEREPOSITORY(repoFile, fileName, path)  (snprintf(repoFile, MAX, "%s%s%s", path, fileName, "Repository.java"))
#define CREATESERVICE(serFile, fileName, path) (snprintf(serFile, MAX, "%s%s%s", path, fileName, "Service.java"))


int create_file(char *file_name){
   FILE *file;


   file = fopen(file_name, "w");
  
   fclose(file);
   return 0;
}


int create_files(char *name, char *path){
   char model[MAX], service[MAX], repo[MAX];
   CREATEMODEL(model, name, path);
   printf("%s\n", model);
   CREATEREPOSITORY(repo, name, path);
   printf("%s\n", repo);
   CREATESERVICE(service, name, path);
   printf("%s\n", service);


   create_file(model);
   create_file(service);
   create_file(repo);


   return 0;
}


int get_path(char buffer[MAX]){
   FILE *pathf = fopen("prova.saka", "r");
   fgets(buffer, MAX, pathf);
   fclose(pathf);
   return 0;
}


int main(int argc, char **argv){
   char buffer[MAX];
   get_path(buffer);
   create_files(argv[1], buffer);


   return 0;
}

