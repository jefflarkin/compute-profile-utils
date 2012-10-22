MPICC=cc
MPIFC=ftn
CUDAC=nvcc
OPENACCCC=cc
OPENACCFC=ftn
MPICMD=aprun -n 4 -N 1
CFLAGS+=-I/opt/cray/lustre-cray_gem_s/default/include
LDFLAGS+=-L/opt/cray/lustre-cray_gem_s/default/lib64 -llustreapi

setup_profile_filename.o: setup_profile_filename.c
	$(CC) $(CFLAGS) -c -o $*.o $<

.PHONY: clean
clean: 
	-rm -f *.o *.cub *.ptx *.lst *.mod cudaf.exe cudac.exe
