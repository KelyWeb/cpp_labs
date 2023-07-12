#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

////////FLAFS FOR CONSOLE///////
struct SearchFlags {          //
    bool type_l;              // LYNK SEARCH FLAG
    bool type_d;              // DIR SEARCH FLAG
    bool type_s;              // SORT FLAG
    bool type_f;              // FILE SEARCH FLAG
} default_types;              //
////////////////////////////////
////////STORAGE STRUCTURE///////
struct strings_path{          //
    char ** strings;          //
    int  *  strings_size;     //
} default_strings_path;       //
////////////////////////////////


static const char * INVALID_ARG  = "Invalid arg in program..";
static const char * INVALID_PATH = "Invalid pathname in program..";

void directory_files(char * actually_diretory, struct SearchFlags * search_flags, struct strings_path * main_path);
char** add_file_descritpion(char ** all_descriptions, int* size_desriptions, char * desription_name);
void loading_flags(struct SearchFlags* flags, int fork_argc, char ** fork_argv);
int detect_true_flag(const char* check_flag);


int main(int argc, char ** argv) {
    struct SearchFlags* test_flags = malloc(sizeof(struct SearchFlags));
    loading_flags(test_flags, argc, argv);

    //test_dir_files(argv[1], test_flags);
    
    struct strings_path * test_path = malloc(sizeof(struct strings_path));
    test_path -> strings_size = malloc(sizeof(int));
    *(test_path -> strings_size) = 1;
    test_path -> strings = malloc(sizeof(char *) * 1) ;
    test_path -> strings[0] = malloc(sizeof(char) * 100);
    strcpy(test_path -> strings[0], argv[0]);

    directory_files(argv[1], test_flags, test_path);

    for(int i = 0; i < *(test_path -> strings_size); i++) {
        fputs(test_path -> strings[i], stdout);
        fputs("\n", stdout);
    }
    
}


char** add_file_descritpion(char** all_descriptions, int* size_desriptions, char* desription_name) {
    
    *(size_desriptions) += 1;
    char** returned_array = realloc(all_descriptions, sizeof(char *) * (*(size_desriptions)));

    returned_array[*(size_desriptions) - 1] = malloc(sizeof(char) * (strlen(desription_name) + 1));

    strcpy(returned_array[*(size_desriptions) - 1], desription_name);

    return returned_array;
}

int detect_true_flag(const char* check_flag) {
    if(!(strcmp("-f", check_flag))) return 1;
    if(!(strcmp("-l", check_flag))) return 2;
    if(!(strcmp("-d", check_flag))) return 3;
    if(!(strcmp("-s", check_flag))) return 4;
    return -1;
}

void loading_flags(struct SearchFlags* flags, int fork_argc, char** fork_argv) {
    if(fork_argc == 1) return;
    else {
        for(int flag = 2; flag < fork_argc; flag++) {
            int flag_result = detect_true_flag(fork_argv[flag]);

            if(flag_result == -1) perror(INVALID_ARG);

            if(flag_result == 1) flags -> type_f = true;
            if(flag_result == 2) flags -> type_l = true;
            if(flag_result == 3) flags -> type_d = true;
            if(flag_result == 4) flags -> type_s = true;   
        }
    }
}

void directory_files(char * actually_file_path, struct SearchFlags * search_flags, struct strings_path * main_path) {
    DIR* actual_open_folder = opendir(actually_file_path);
    
    if(actual_open_folder == NULL) { 
        perror(INVALID_PATH);
        exit(EXIT_FAILURE);
    }

    struct dirent* actual_file = NULL;

    while((actual_file = readdir(actual_open_folder)) != NULL) {
        if(!(strcmp(actual_file -> d_name, "..")) || !(strcmp(actual_file -> d_name, "."))) continue;

        if(((actual_file -> d_type) == DT_DIR && (search_flags -> type_d) == 1) ||
            ((actual_file -> d_type) == DT_REG && (search_flags -> type_f) == 1) ||
            ((actual_file -> d_type) == DT_LNK && (search_flags -> type_l) == 1)){
                //Строка для хранения полного собранного пути к файлу или папке//
                char* assemble_link_string = malloc(sizeof(char) * (strlen(actually_file_path) + strlen(actual_file -> d_name) + 5));
                
                strcpy(assemble_link_string, actually_file_path); 
                strcat(assemble_link_string, actual_file -> d_name);
                main_path -> strings = add_file_descritpion(main_path -> strings, main_path -> strings_size, assemble_link_string);

                if((actual_file -> d_type) == DT_DIR) {
                    strcat(assemble_link_string, "/");
                    directory_files(assemble_link_string, search_flags, main_path);
                }

                free(assemble_link_string);
            }
    }
    closedir(actual_open_folder);
}
