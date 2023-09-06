CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_O = out/types_work.o out/read_file.o out/output_graph.o out/connectivity.o out/delete_peak.o out/main.o
ALL_I = inc/types_work.h inc/read_file.h inc/output_graph.h inc/connectivity.h inc/delete_peak.h inc/common.h

out/%.o:src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_O) $(ALL_I)
	$(CC) -o $@ $(ALL_O)

clean:
	rm -rf *.o *.exe out/*.o