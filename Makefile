mainfile = gais.c
#for static lib
debug: $(mainfile) libdeleteTag_st.a
	gcc -pg -static $(mainfile) -L. -ldeleteTag_st -o debug
	rm -rf *.o
static: $(mainfile) libdeleteTag_st.a
	gcc -static $(mainfile) -L. -ldeleteTag_st -o static
	rm -rf *.o
	cp libdeleteTag_st.a readData.h define.h ../transfer
	cp libdeleteTag_st.a readData.h define.h ../toDB
	cp libdeleteTag_st.a readData.h define.h ../connectdb_http
	cp libdeleteTag_st.a readData.h define.h ../page_index
libdeleteTag_st.a: deleteTag.o readData.o regex.o 
	ar rcs libdeleteTag_st.a deleteTag.o readData.o regex.o
deleteTag.o: deleteTag.c 
	gcc -c deleteTag.c
readData.o: readData.c
	gcc -c readData.c
regex.o: regex.c
	gcc -c regex.c
#for share lib
share: $(mainfile) libdeleteTag_sh.so
	gcc $(mainfile) -L. -ldeleteTag_sh -o share
	rm -rf *.o
	cp libdeleteTag_sh.so readData.h define.h ../transfer
	cp libdeleteTag_sh.so readData.h define.h ../toDB ../connectdb_http
	cp libdeleteTag_sh.so readData.h define.h ../connectdb_http
	cp libdeleteTag_sh.so readData.h define.h ../page_index
libdeleteTag_sh.so: deleteTag_sh.o readData_sh.o regex_sh.o 
	gcc -shared deleteTag_sh.o readData_sh.o regex_sh.o -o libdeleteTag_sh.so
deleteTag_sh.o: deleteTag.c 
	gcc -c -fPIC deleteTag.c -o deleteTag_sh.o
readData_sh.o: readData.c
	gcc -c -fPIC readData.c -o readData_sh.o
regex_sh.o: regex.c
	gcc -c -fPIC regex.c -o regex_sh.o
clean:
	rm -rf *.o
clear:
	rm -rf static share libdeleteTag_sh.so libdeleteTag_st.a result
	
