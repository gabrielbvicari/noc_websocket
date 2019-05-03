#include "gen_file.h"

void create_json()
{
    read_neighbor_json();
    exec_router_json();
    exec_proc_json();
}

void read_neighbor_json()
{
    output = fopen("./output/output.json", "w");

    fprintf(output, "[\n");
    fprintf(output, "\t{\n");
    fprintf(output, "\t\t\"project\":\n");
    fprintf(output, "\t\t{\n");
    fprintf(output, "\t\t\t\"noc\":\n");
    fprintf(output, "\t\t\t{\n");
    fprintf(output, "\t\t\t\t\"x\": \"%d\",\n", qt_nodes_x);
    fprintf(output, "\t\t\t\t\"y\": \"%d\",\n", qt_nodes_y);
    fprintf(output, "\t\t\t\t\"topology\": \"MESH 2D""\",\n");
    fprintf(output, "\t\t\t\t\"routers\": \n");
    fprintf(output, "\t\t\t\t{\n");

    for (int i = 0; i <= num_routers; i++) {
	    fprintf(output, "\t\t\t\t\t\"pe\":\n");
		fprintf(output, "\t\t\t\t\t{\n");
		fprintf(output, "\t\t\t\t\t\t\"id\": \"%d\",\n", data.source[i]);

		if (neighbor_top(src.x[i], src.y[i] > 0)) {
			fprintf(output, "\t\t\t\t\t\t\"top\": ""\"%d%d""\""",\n", src.x[i], neighbor_top(src.x[i], src.y[i]));
		}

		if (neighbor_bottom(src.x[i], src.y[i] > 0)) {
			fprintf(output, "\t\t\t\t\t\t\"bottom\": ""\"%d%d""\""",\n", src.x[i], neighbor_bottom(src.x[i], src.y[i]));
        }

		if (neighbor_right(src.x[i], src.y[i] > 0)) {
			fprintf(output, "\t\t\t\t\t\t\"right\": ""\"%d%d""\""",\n", neighbor_right(src.x[i], src.y[i]), src.x[i]);

		}

	    if (neighbor_left(src.x[i],src.y[i] > 0)) {
			fprintf(output, "\t\t\t\t\t\t\"left\": ""\"%d%d""\""",\n", neighbor_left(src.x[i], src.y[i]), src.x[i]);

		}

	    fprintf(output, "\t\t\t\t\t\t\"local\": \"proc%d\"\n", proc_id);
        fprintf(output, "\t\t\t\t\t}");
        
        if (i == num_routers) {
            fprintf(output, "\n");
        }
        else {
            fprintf(output, ",\n");
        }

	    proc_id++;
	}

	fprintf(output, "\t\t\t\t}\n");
	fprintf(output, "\t\t\t},\n");

    fclose(output);
}

void exec_router_json()
{
    int total = 0;
    float perc_r = 0;
    float perc_l = 0;
    float perc_tt = 0;
    float perc_b = 0;
    float perc_loc = 0;

    output = fopen("./output/output.json", "a");

    fprintf(output, "\t\t\t\"communication\":\n");
    fprintf(output, "\t\t\t{\n");
    fprintf(output, "\t\t\t\t\"volume\":\n");
    fprintf(output, "\t\t\t\t{\n");

    for (int i = 0; i < num_routers; i++) {
	    total = right[i] + left[i] + top[i] + bottom[i];
	    perc_r = right[i] * 100.0 / total;
	    perc_l = left[i] * 100.0 / total;
	    perc_tt = top[i] * 100.0 / total;
	    perc_b = bottom[i] * 100.0 / total;
	    perc_loc = local[i] * 100.0 / total;

	    fprintf(output, "\t\t\t\t\t\"router\":\n");	
        fprintf(output, "\t\t\t\t\t{\n");

	    fprintf(output, "\t\t\t\t\t\t\"id\": ""\"%d%d""\""",\n", src.x[i], src.y[i]);
	    fprintf(output, "\t\t\t\t\t\t\"message_count\": ""\"%d""\""",\n", count_mes[i]);
	    fprintf(output, "\t\t\t\t\t\t\"ports\":\n");
	    fprintf(output, "\t\t\t\t\t\t{\n");
	    fprintf(output, "\t\t\t\t\t\t\t\"top\": ""\"%f%%""\""",\n", perc_tt);	
	    fprintf(output, "\t\t\t\t\t\t\t\"bottom\": ""\"%f%%""\""",\n", perc_b);	
	    fprintf(output, "\t\t\t\t\t\t\t\"left\": ""\"%f%%""\""",\n", perc_l);
	    fprintf(output, "\t\t\t\t\t\t\t\"right\": ""\"%f%%""\""",\n", perc_r);	
	    fprintf(output, "\t\t\t\t\t\t\t\"local\": ""\"%f%%""\"\n", perc_loc);
	    fprintf(output, "\t\t\t\t\t\t}\n");
	    fprintf(output, "\t\t\t\t\t}");

        if (i == num_routers - 1) {
            fprintf(output, "\n");
        }
        else {
            fprintf(output, ",\n");
        }
    }
    
    fprintf(output, "\t\t\t\t}\n");
    fprintf(output, "\t\t\t},\n");
    fprintf(output, "\t\t\t\"execution\":\n");
    fprintf(output, "\t\t\t{\n");

    fclose(output);
}

void exec_proc_json()
{
    output = fopen("./output/output.json", "a");

	for (int i = 0; i < num_routers; i++) {
		fprintf(output, "\t\t\t\t\"proc\":\n");
		fprintf(output, "\t\t\t\t{\n");

		fprintf(output, "\t\t\t\t\t\"id\": ""\"proc%d\""",\n", i);
		fprintf(output,"\t\t\t\t\t\"requests\": ""\"%d""\"""\n", local[i]);
		
		fprintf(output, "\t\t\t\t}");

        if (i == num_routers - 1) {
            fprintf(output, "\n");
        }
        else {
            fprintf(output, ",\n");
        }
	}

    fprintf(output, "\t\t\t}\n");
    fprintf(output, "\t\t}\n");
    fprintf(output, "\t}\n");
    fprintf(output, "]\n");

    fclose(output);
}

void create_xml()
{
    output = fopen("./output/output.xml", "w");

	fprintf(output, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(output, "<project>\n");
    fprintf(output, "\t<noc>\n");
    fprintf(output, "\t\t<x>%d</x>\n", qt_nodes_x);
    fprintf(output, "\t\t<y>%d</y>\n", qt_nodes_y);
    fprintf(output, "\t\t<topology>Mesh 2D</topology>\n");
    fprintf(output, "\t\t<routers>\n");

    for (int i = 0; i <= num_routers; i++) {
		fprintf(output, "\t\t\t<node>\n");
		fprintf(output, "\t\t\t\t<id>%d</id>\n", data.source[i]);
		
		if (neighbor_top(src.x[i], src.y[i] > 0)) {
			fprintf(output, "\t\t\t\t<top>%d%d</top>\n", src.x[i], neighbor_top(src.x[i], src.y[i]));
		}

		if (neighbor_bottom(src.x[i], src.y[i] > 0)) {
			fprintf(output, "\t\t\t\t<bottom>%d%d</bottom>\n", src.x[i], neighbor_bottom(src.x[i], src.y[i]));
		}

		if (neighbor_right(src.x[i], src.y[i] > 0)) {
			fprintf(output, "\t\t\t\t<right>%d%d</right>\n", neighbor_right(src.x[i], src.y[i]), src.x[i]);

		}

	    if (neighbor_left(src.x[i], src.y[i] > 0)) {
			fprintf(output, "\t\t\t\t<left>%d%d</left>\n", neighbor_left(src.x[i], src.y[i]), src.x[i]);
		}

	    fprintf(output, "\t\t\t\t<local>proc%d</local>\n", proc_id);
        fprintf(output, "\t\t\t</node>\n");

	    proc_id++;
	}

    fprintf(output, "\t\t</routers>\n");
    fprintf(output, "\t</noc>\n");
	fprintf(output, "<project>\n");

    fclose(output);
}

int neighbor_top(int x, int y)
{
	if (y >= qt_nodes_y - 1)
		return (0);
	else
		return (y + 1);
}

int neighbor_bottom(int x, int y)
{
	if (y == 0)
		return (0);
	else
        return (y - 1);
}

int neighbor_right(int x, int y)
{
	if (x >= qt_nodes_x - 1)
		return (0);
	else
		return (x + 1);
}

int neighbor_left(int x, int y)
{
	if (x == 0)
		return (0);
	else
		return (x - 1);
}