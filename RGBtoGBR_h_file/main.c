#include <stdio.h>
#include <mem.h>

int main(int argc, char **argv)
{
    if (argc < 2){
        printf("Please input only one filname as argument.");
    }

    FILE * fin;
    FILE * fout;

    fin = fopen(argv[1], "rb");
    if (fin == NULL){
        printf("Could not find file..");
    }

    char name[100] = {0};
    char name2[100] = {0};
    strncpy(name, argv[1], strlen(argv[1])-3);
    strcat(name, "h\0");

    printf("Opening file: %s\n", name);
    fout = fopen(name, "w");

    int rgb[3]= {0};

    strncpy(name2, name, strlen(name)-2);
    /*
     * Read past metadata
     */
    printf("\nPrinting metadata:\n");
    for (int i = 0; i < 4; i++){
        int a = 'e';
        while (a != '\n'){
            a = fgetc(fin);
            printf("%c", a);
        }
    }

    printf("\nPrinting new .h file.\n");


    fprintf(fout, "#ifndef SRC_%s_H_\n", strupr(name2));
    fprintf(fout, "#define SRC_%s_H_\n\n", strupr(name2));
    fprintf(fout, "u8 %s[]={\n", name2);

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

    fprintf(fout, "};\n\n#endif\n");

    fclose(fin);
    fclose(fout);




    printf("Done!\n");
    return 0;
}
