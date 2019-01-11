#include <stdio.h>
#include <mem.h>

void makeHeaderFile(FILE * fout, char * filename) {
fprintf(fout, "#ifndef SRC_%s_H_\n", strupr(filename));
fprintf(fout, "#define SRC_%s_H_\n\n", strupr(filename));
fprintf(fout, "#include \"xil_types.h\"\n\n");
fprintf(fout, "\textern u8 %s[];\n\n",strlwr(filename));
fprintf(fout, "\n#endif\n");
}



int main(int argc, char **argv)
{
    if (argc < 2){
        printf("Please input only one filname as argument.");
        return -1;
    }

    FILE * fin;
    FILE * fout;

    fin = fopen(argv[1], "rb");
    if (fin == NULL){
        printf("Could not find file..");
        return -1;
    }

    char name[100] = {0}; //"name.c"
    char name2[100] = {0}; //"NAME"
    char name3[100] = {0}; //"name.h"

    strncpy(name, argv[1], strlen(argv[1])-3); // Fjerne filformatet (ppm)
    strcat(name, "c\0");                        // Gør det til .c

    printf("Opening file: %s\n", name);
    fout = fopen(name, "w");                // laver fil pointer med name.c

    int rgb[3]= {0};

    strncpy(name2, name, strlen(name)-2);  // name2 "name.c" så filen name2 nu indeholder "name"



    /*
     * Read past metadata
     */
    printf("\nPrinting metadata:\n");
    for (int i = 0; i < 4; i++){
        int a = 'e';
        while (a != '\n'){
            a = fgetc(fin);
            //printf("%c", a);
        }
    }


    printf("\nPrinting new .c file.\n");


    fprintf(fout, "#include \"xil_types.h\"\n\n\n");
    fprintf(fout, "u8 %s[]={\n", strlwr(name2));

    char ending = 0;
    while (ending == 0){
        for (int j = 0; j < 6; j++){
            for (int i =0; i < 3; i++){
                rgb[i]=fgetc(fin);
                if (rgb[i] == -1){
                    ending = 1;
                    break;
                }
            }
            if (ending == 1)
                break;

            fprintf(fout, "%d, %d, %d,\t", rgb[1], rgb[2], rgb[0]);

        }//end for j

        fprintf(fout, "\n");
    }//end while

    fprintf(fout ,"};");
    fclose(fin);
    fclose(fout);


    printf("name indeholde %s\n", name);
    printf("name2 indeholder: %s\n", name2);
    strncpy(name, name2, strlen(name)+1);
    strcat(name, ".h\0");
    fout = fopen(name, "w");                // laver fil pointer til name.h

    printf("Makes header file now.\n");
    makeHeaderFile(fout, name2);            // Sender fil pointer og char array med name

    fclose(fout);


    printf("Done!\n");
    return 0;
}
