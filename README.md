compute-profile-utils
=====================
Author: Jeff Larkin <jeff.larkin@gmail.com>

Utilities for making Nvidia Compute Command Line Profiler more useful in MPI applications.

setup_profile_filename.o
------------------------
This object file is intended to add the ability to easily output a different compute profiler
log for each MPI rank. By default the file will be named compute_profile_<rank>.log. It will
also set the lustre striping for each rank's file to 1.

### USAGE
#### C
```C
void compute_profile_filename();
int main(int argc, char **argv)
{
  int ierr, rank, i;

  MPI_Init(&argc, &argv);
  compute_profile_filename();

  ...

  MPI_Finalize();
  return ierr;
}
```
#### Fortran
```FORTRAN
program main
  use mpi
  call mpi_init()
  call compute_profile_filename()
  
  ...

  call mpi_finalize()
end program
````

#### Linking
Add `setup_profile_filename.o -L/opt/cray/lustre-cray_gem_s/default/lib64 -llustreapi`

### Caveats
This utility has only been tested on Cray XK6 machines to date. There is no reason that it 
shouldn't work on other machines as well, but it will be necessary to either remove the lustre
portions or update the link to -llustreapi.

### TODO
1. Add existing tests to repository
2. Hook into PMPI interface to make usage automatic
3. Add modulefile
4. Check value of COMPUTE_PROFILE_LOG to allows user-defined file names
5. Create MPI-aware post-processing utility.

