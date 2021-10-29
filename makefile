our_shell: main.c char_vector.o get_line.o tokenise.o command_parse.o char_vector_vector.o job_vector.o command.o job.o change_prompt.o executeJob.o pipe.o execute_command.o PWDFuncs.o fileIORedirect.o
	gcc -std=c99 main.c char_vector.o get_line.o tokenise.o command_parse.o char_vector_vector.o job_vector.o command.o job.o change_prompt.o executeJob.o pipe.o execute_command.o PWDFuncs.o fileIORedirect.o -o our_shell
fileIORedir.o: fileIORedir.h fileIORedir.c
	gcc -std=c99 fileIORedir.c -c
PWDFuncs.o: PWDFuncs.h PWDFuncs.c
	gcc -std=c99 PWDFuncs.c -c
wildcard_path_expand.o: wildcard_path_expand.c wildcard_path_expand.h command.o
	gcc -std=c99 wildcard_path_expand.c -c
command_parse.o: command_parse.h command_parse.c command.o
	gcc -std=c99 command_parse.c -c
tokenise.o: tokenise.h tokenise.c char_vector_vector.o char_vector.o
	gcc -std=c99 tokenise.c -c
get_line.o: get_line.h get_line.c char_vector.o
	gcc -std=c99 get_line.c -c
job_vector.o: job_vector.h job_vector.c job.o
	gcc -std=c99 job_vector.c -c
job.o: job.c job.h command.o
	gcc -std=c99 job.c -c
command.o: command.h command.c char_vector.o char_vector_vector.o
	gcc -std=c99 command.c -c
char_vector_vector.o: char_vector_vector.h char_vector_vector.c char_vector.o
	gcc -std=c99 char_vector_vector.c -c
char_vector.o: char_vector.h char_vector.c
	gcc -std=c99 char_vector.c -c
change_prompt.o: change_prompt.h change_prompt.c char_vector.o
	gcc -std=c99 change_prompt.c -c
executeJob.o: executeJob.h executeJob.c job.o pipe.o fileIORedirect.o execute_command.o
	gcc -std=c99 executeJob.c -c
pipe.o: pipe.h pipe.c
	gcc -std=c99 pipe.c -c
execute_command.o: execute_command.h execute_command.c command.o change_prompt.o PWDFuncs.o
	gcc -std=c99 execute_command.c -c
clean:
	rm *.o

