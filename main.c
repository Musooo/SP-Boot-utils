#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define MAX 100
#define CONF_FILE "prova.saka"

#if defined(_WIN32) || defined(__CYGWIN__)
   #define BASE_PATH "src\\main\\java\\"
   #define CREATEFILEPATH(buffer, groupId, artifactId, fileName, mod, mod2) (snprintf(buffer, MAX*2, "%s%s\\%s\\%s\\%s%s.java", BASE_PATH, groupId, artifactId, mod,fileName, mod2))
   #define DIR_PATH(buffer, groupId, artifactId, dir) (snprintf(buffer, MAX*2, "%s%s\\%s\\%s", BASE_PATH, groupId, artifactId, dir)) 
#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
   #define BASE_PATH "src/main/java/"
   #define CREATEFILEPATH(buffer, groupId, artifactId, fileName, mod, mod2) (snprintf(buffer, MAX*2, "%s%s/%s/%s/%s%s.java", BASE_PATH, groupId, artifactId, mod,fileName, mod2))
   #define DIR_PATH(buffer, groupId, artifactId, dir) (snprintf(buffer, MAX*2, "%s%s/%s/%s", BASE_PATH, groupId, artifactId, dir))   
#else
    #error Unknown environment!
#endif

int create_file(char *file_name, char *txt){
   FILE *file;

   file = fopen(file_name, "w");
   fprintf(file, txt);

   fclose(file);
   return 0;
}

int create_model(char *file_name, char groupId[MAX], char artifactId[MAX], char *name){
   FILE *file;

   file = fopen(file_name, "w");
   fprintf(file, "package %s.%s.model;\n\nimport jakarta.persistence.Entity;\nimport jakarta.persistence.Id;\nimport jakarta.persistence.Table;\nimport lombok.AllArgsConstructor;\nimport lombok.Getter;\nimport lombok.NoArgsConstructor;\nimport lombok.Setter;\n\n@Entity\n@Getter\n@Setter\n@AllArgsConstructor\n@NoArgsConstructor\n@Table(name = \"%s\")\n\npublic class %s {}", groupId, artifactId, name, name);

   fclose(file);
   return 0;
}

int create_service(char *file_name, char groupId[MAX], char artifactId[MAX], char *name, char *lname){

   FILE *file;

   file = fopen(file_name, "w");
   fprintf(file,"package %s.%s.service;\n\nimport org.springframework.beans.factory.annotation.Autowired;\nimport org.springframework.stereotype.Service;\nimport %s.%s.model.%s;\nimport %s.%s.repository.%sRepository;\n\nimport java.util.List;\n\n@Service\npublic class %sService {\n   @Autowired\n   private %sRepository %sRepository;\n\n   public List<%s> findAll() {\n      return %sRepository.findAll();\n   }\n\n   public %s findById(Tipo id) {\n      return %sRepository.findById(id).orElse(null);\n   }\n\n   public %s save(%s %s) {\n      return %sRepository.save(%s);\n   }\n\n}", groupId, artifactId, groupId, artifactId, name, groupId, artifactId, name, name, name, lname, name, lname, name, lname, name, name, lname, lname, lname);

   fclose(file);

   return 0;
}

int create_repository(char *file_name, char groupId[MAX], char artifactId[MAX], char *name){
   FILE *file;

   file = fopen(file_name, "w");
   fprintf(file, "package %s.%s.repository;\n\nimport org.springframework.data.jpa.repository.JpaRepository;\nimport org.springframework.stereotype.Repository;\nimport %s.%s.model.%s;\n@Repository\npublic interface %sRepository extends JpaRepository<%s, TipoId> {}", groupId, artifactId, groupId, artifactId, name, name, name);

   fclose(file);

   return 0;
}

int get_ids(char groupId[MAX], char artifactId[MAX]){
   FILE *file;
   file = fopen(CONF_FILE, "r");
   if (file == NULL) {
       perror("Error opening file");
       return -1;
   }

   if (fgets(groupId, MAX, file) == NULL) {
       perror("Error reading groupId");
       fclose(file);
       return -1;
   }

   groupId[strcspn(groupId, "\n")] = '\0';

   if (fgets(artifactId, MAX, file) == NULL) {
       perror("Error reading artifactId");
       fclose(file);
       return -1;
   }

   artifactId[strcspn(artifactId, "\n")] = '\0';

   fclose(file);
   return 0;
}



int get_idsPom() {
   FILE *file;
   char line[MAX], groupId[MAX] = "", artifactId[MAX] = "";
   

   // Need to find the second groupId and artifactId in the pom.xml file 
   int foundGroupId = 0;
   int foundArtifactId = 0;

   file = fopen("pom.xml", "r");
   if (file == NULL) {
       perror("Error opening file");
       return -1;
   }

   while (fgets(line, sizeof(line), file) != NULL) {

      char *start, *end;
      if ((start = strstr(line, "<groupId>")) != NULL) {
         start += strlen("<groupId>");
         if ((end = strstr(start, "</groupId>")) != NULL) {
            if (++foundGroupId == 2) {
               strncpy(groupId, start, end - start);
               groupId[end - start] = '\0';
            }
         }
      } else if ((start = strstr(line, "<artifactId>")) != NULL) {
         start += strlen("<artifactId>");
         if ((end = strstr(start, "</artifactId>")) != NULL) {
            if (++foundArtifactId == 2) {
               strncpy(artifactId, start, end - start);
               artifactId[end - start] = '\0';
            }
         }
      }

      if (foundGroupId >= 2 && foundArtifactId >= 2) {
         break;
      }
    }
   
   fclose(file);

   if (foundGroupId < 2 || foundArtifactId < 2) {
        printf("Error: Could not find the second occurrence of required tags in pom.xml\n");
        return -1;
    }

      char path[MAX];
      snprintf(path, MAX, "%s\n%s\n", groupId, artifactId);
      printf("Writing to file: %s\n", path);
      create_file(CONF_FILE, path);
      return 0;
}


int create_files(char groupId[MAX], char artifactId[MAX], char *fileName){
   char model[MAX*2], repo[MAX*2], service[MAX*2];

   char lname[MAX];
   strcpy(lname, fileName);
   if (lname[0] >= 'A' && lname[0] <= 'Z') {
      lname[0] += ('a' - 'A');
   }

   char groupIdS[MAX];
   strcpy(groupIdS, groupId);
   for(int i = 0; i<MAX; i++){
      if (groupIdS[i]=='.'){
         groupIdS[i]='/';
         break;
      }
   }
   
   CREATEFILEPATH(model, groupIdS, artifactId, fileName, "model", "");
   CREATEFILEPATH(repo, groupIdS, artifactId, fileName, "repository", "Repository");
   CREATEFILEPATH(service, groupIdS, artifactId, fileName, "service", "Service");

   create_model(model, groupId, artifactId, fileName);
   create_service(service, groupId, artifactId, fileName, lname);
   create_repository(repo, groupId, artifactId, fileName);
   
   return 0;
}

int create_dir(){
   char groupId[MAX], artifactId[MAX], dir_path[MAX*2];
   get_ids(groupId,artifactId);

   for(int i = 0; i<MAX; i++){
      if (groupId[i]=='.'){
         groupId[i]='/';
         break;
      }
   }

   DIR_PATH(dir_path, groupId, artifactId, "controller");
   mkdir(dir_path, S_IRWXU);

   DIR_PATH(dir_path, groupId, artifactId, "model");
   mkdir(dir_path, S_IRWXU);

   DIR_PATH(dir_path, groupId, artifactId, "repository");
   mkdir(dir_path, S_IRWXU);

   DIR_PATH(dir_path, groupId, artifactId, "service");
   mkdir(dir_path, S_IRWXU);

   return 0;
}

int help_text(){
   printf("help:\n");
   printf("settup the conf. file\n");
   printf("-s to set up the %s, follow that with <groupId> <artifactId>\n", CONF_FILE);
   printf("example: molten -s org.example prova\n");
   printf("-d to create controller, service, model, repository dir");
   printf("please do not create goofy groupId/artifact do not use special char except in the groupId where you should put a \".\"\n");
   printf("-a: to read the pom.xml and safe the <groupId> and <artifactId>\n");
   printf("How to create the files\n");
   printf("example: molten <ObkName>\n");
   printf("Remember to put the first letter capital, for now the program doesn't fix it\n");
   return 0;
}



int main(int argc, char **argv){
   // -s groupId artifactId
   // nomeclasse

   if (argc < 1){
      printf("My name is Linus Torvalds and I am your god.\n");
      return -1;
   }

   int i = 1;

   while (i < argc){
      if (strcmp(argv[i], "-d") == 0){
         printf("creating dirs\n");
         create_dir();
      }else if (strcmp(argv[i], "-s") == 0){
         if (i+2>argc){
            printf("not enough argv, you have to put groupId artifactId");
            return -1;
         }
         char path[MAX];
         snprintf(path, MAX, "%s\n%s\n", argv[i+1], argv[i+2]);
         create_file(CONF_FILE, path);
         i +=2;
      }else if(strcmp(argv[i], "-h") == 0){
         help_text();
      }else if(strcmp(argv[i], "-a") == 0){
         get_idsPom();
      }else {
         char groupId[MAX], artifactId[MAX];
         get_ids(groupId,artifactId);
         create_files(groupId, artifactId, argv[i]);
      }

      i++;
   }
   

   return 0;
}

