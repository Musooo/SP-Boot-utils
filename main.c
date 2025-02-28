#include <stdio.h>
#include <string.h>

#define BASE_PATH "src/main/java/"
#define MAX 100
#define CREATEFILEPATH(buffer, groupId, artifactId, fileName, mod, mod2) (snprintf(buffer, MAX, "%s%s/%s/%s/%s%s.java", BASE_PATH, groupId, artifactId, mod,fileName, mod2))
#define CONF_FILE "prova.saka"


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
   fprintf(file,"package %s.%s.service;\n\nimport org.springframework.beans.factory.annotation.Autowired;\nimport org.springframework.stereotype.Service;\nimport %s.%s.model.%s;\nimport %s.%s.repository.%sRepository;\n\nimport java.util.List;\n\n@Service\npublic class %sService {\n@Autowired\nprivate %sRepository %sRepository;\n\npublic List<%s> findAll() {\nreturn %sRepository.findAll();\n}\n\npublic %s findById(String id) {\nreturn %sRepository.findById(id).orElse(null);\n}\n\n}", groupId, artifactId, groupId, artifactId, name, groupId, artifactId, name, name, name, lname, name, lname, name, lname);

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

int create_files(char groupId[MAX], char artifactId[MAX], char *fileName){
   char model[MAX], repo[MAX], service[MAX];

   char lname[MAX];
   strcpy(lname, fileName);
   if (lname[0] >= 'A' && lname[0] <= 'Z') {
      lname[0] += ('a' - 'A');
   }
   
   CREATEFILEPATH(model, groupId, artifactId, fileName, "model", "");
   CREATEFILEPATH(repo, groupId, artifactId, fileName, "repository", "Repository");
   CREATEFILEPATH(service, groupId, artifactId, fileName, "service", "Service");

   create_model(model, groupId, artifactId, fileName);
   create_service(service, groupId, artifactId, fileName, lname);
   create_file(repo, "");
   
   return 0;
}

int main(int argc, char **argv){
   // -s groupId artifactId
   // nomeclasse
   if (strcmp(argv[1], "-s") == 0){
      if (argc<4){
         printf("not enough argv, you have to put groupId artifactId");
         return -1;
      }
      char path[MAX];
      snprintf(path, MAX, "%s\n%s\n", argv[2], argv[3]);
      create_file("prova.saka", path);
   }else {
      if (argc<2){
         printf("no");
      }
      char groupId[MAX], artifactId[MAX];
      get_ids(groupId,artifactId);
      create_files(groupId, artifactId, argv[1]);
   }


   return 0;
}

