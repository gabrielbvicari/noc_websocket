#include "defs.h"
#include "noc.h"
#include "gen_file.h"

int main(int argc, char **argv)
{
    FILE *file;
    char line[1024], *conversion;
    int topology;
    int kind_output;

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        exit(-1);
    }

    topology = strtol(argv[2], &conversion, 10);
    kind_output = strtol(argv[3], &conversion, 10);
    qt_nodes_x = strtol(argv[4], &conversion, 10);
    qt_nodes_y = strtol(argv[5], &conversion, 10);

    switch (topology) {
    default:
    case 0:
        num_routers = qt_nodes_x * qt_nodes_y;
        if (qt_nodes_x != qt_nodes_y) {
            printf("Error: Mesh must be squared.\n");
            exit(1);
        }
        if (qt_nodes_x < 2 || qt_nodes_y < 2) {
            printf("Error: Mesh must be greater than 1x1.\n");
            exit(1);
        }

        break;
    case 1:
        printf("Error: Not implemented yet.\n");
        exit(1);
        break;
    }

    for (int c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n')
            num_lines++;
    }

    rewind(file);

    for (int i = 0; i < 2; i++) {
        num_lines--;
        fgets(line, sizeof(line), file);
    }

    data.str = malloc(num_lines * sizeof(char*));
    for (int i = 0; i < num_lines; i++)
        data.str[i] = malloc((LENGTH + 1) * sizeof(char)); 

    for (int i = 0; i < num_lines; i++) {        
        if (fscanf(file, "%d %d \"%[^\"]\" %d", &data.source[i], &data.target[i], data.str[i], &data.end[i]) != 4) {
            printf("Error: Arguments missing in line %d of the input file.\n", i + 2);
            exit(1);
        }

        if (data.source[i] < 0 || data.target[i] < 0) {
            printf("Error: Invalid router address.\n");
            exit(1);
        }

        if (data.source[i] < 10) {
            src.x[i] = 0;
            src.y[i] = data.source[i];
        }
        else {
            src.x[i] = data.source[i] / 10;
            src.y[i] = data.source[i] % 10;
        }

        if (data.target[i] < 10) {
            tgt.x[i] = 0;
            tgt.y[i] = data.target[i];
        }
        else {
            tgt.x[i] = data.target[i] / 10;
            tgt.y[i] = data.target[i] % 10;
        }

        if (src.x[i] >= qt_nodes_x || src.y[i] >= qt_nodes_x || tgt.x[i] >= qt_nodes_x || tgt.x[i] >= qt_nodes_x) {
            printf("Error: Invalid router address.\n");
            exit(1);
        }
    }

    pthread_t routers[num_routers], processors[num_routers];

    for (int i = 0; i < num_routers; i++) {
        pe.x[i] = aux_x;
        pe.y[i] = aux_y;

        if (pthread_create(&routers[i], NULL, &router, (void *) &i)) {
            printf("Error: Router %d%d could not be created!\n", pe.x[i], pe.y[i]);
            exit(-2);
        }
        if (aux_x < qt_nodes_x - 1)
            aux_x++;
        else if (aux_y < qt_nodes_y - 1) {
            aux_x = 0;
            aux_y++;
        }
    }

    if (pthread_create(&processors[0], NULL, &processor, NULL)) {
        printf("Error: Processor could not be created!\n");
        exit(-2);
    }

    pthread_join(processors[0], NULL);

    for (int i = 0; i < num_routers; i++) {
        pthread_join(routers[i], NULL);
    }

    if (!kind_output)
        create_json();
    else
        create_xml();
    
    free(data.str);

    return (0);
}