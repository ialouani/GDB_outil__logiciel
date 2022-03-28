FOLDER=./
CXX_FLAGS=gcc -std=c99 -g -O0
dho: dho.c
	gcc -std=c99 -g -O0 -o dho dho.c
dho_debug: dho
	gdb ./dho
xtrem: xtrem.c
	gcc -std=c99 -g -O0 -o xtrem xtrem.c
xtrem_debug: xtrem
	gdb ./xtrem
space: space.c
	gcc -std=c99 -g -O0 -o space space.c
space_debug: space
	gdb ./space
cafard: cafard.c
	gcc -std=c99 -g -O0 -o cafard cafard.c
cafard_debug: cafard
	gdb ./cafard
geek: geek.c
	gcc -std=c99 -g -O0 -o geek geek.c
geek_debug: geek
	gdb ./geek
hack: hack.c
	gcc -std=c99 -g -O0 -o hack hack.c
hack_debug: hack
	gdb ./hack
all1: gdb1.c
	$(CXX_FLAGS) -o $@ $<
all1_exec: all1
	gdb ./$^
all2: test1.c
	$(CXX_FLAGS) -o $@ $<
all2_exec: all2
	gdb ./$^
show_steps__1: ./summary1
	gedit $<
show_steps__2: ./summary2
	gedit $<
show_steps__3: ./summary3
	gedit $<
build_library: compile.sh
	./compile.sh
exec_static__1: build_library example_static
	./example_static
exec_dynamic__2: build_library update.sh
	./update.sh
debug_start_static: build_library example_static
	gdb ./example_static
exec_list: list.c
	$(CXX_FLAGS) $< -o $@
debug_start__2: exec_list
	gdb exec_list
clean: clean_2
	rm -f *.sh~ Makefile~ *.o *.c~ *.txt~ all1 all2 *.so *.a *.h~ exec_list
clean_2:
	rm -f example_static example_dynamique a.out dho xtrem cafard space geek hack
clean_part:
	rm -f *.o *.so *.a Makefile~
