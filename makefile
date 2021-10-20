our_shell: main.c char_vector.o get_line.o tokenise.o command_parse.o char_vector_vector.o job_vector.o command.o job.o
	gcc main.c char_vector.o get_line.o tokenise.o command_parse.o char_vector_vector.o job_vector.o command.o job.o -o our_shell
fileIORedir.o: fileIORedir.h fileIORedir.c
	gcc fileIORedir.c -c
PWDFuncs.o: PWDFuncs.h PWDFuncs.c
	gcc PWDFuncs.c -c
wildcard_path_expand.o: wildcard_path_expand.c wildcard_path_expand.h command.o
	gcc wildcard_path_expand.c -c
command_parse.o: command_parse.h command_parse.c command.o
	gcc command_parse.c -c
tokenise.o: tokenise.h tokenise.c char_vector_vector.o char_vector.o
	gcc tokenise.c -c
get_line.o: get_line.h get_line.c char_vector.o
	gcc get_line.c -c
job_vector.o: job_vector.h job_vector.c job.o
	gcc job_vector.c -c
job.o: job.c job.h command.o
	gcc job.c -c
command.o: command.h command.c char_vector.o char_vector_vector.o
	gcc command.c -c
char_vector_vector.o: char_vector_vector.h char_vector_vector.c char_vector.o
	gcc char_vector_vector.c -c
char_vector.o: char_vector.h char_vector.c
	gcc char_vector.c -c
clean:
	rm *.o

