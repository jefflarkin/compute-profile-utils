#include <errno.h>
#include <stddef.h>
#include <lustre/liblustreapi.h>
#include <lustre/lustre_user.h>
/* int llapi_file_create(char *name, long stripe_size, int stripe_offset, int stripe_count, int stripe_pattern); */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


/* Sets the filename for the compute profiler to cuda_profile_<rank>.log */
void compute_profile_filename()
{
  int rank=0, size=1, ierr;
  char filename[255], *compute_profile;

  /* 
   * Check whether COMPUTE_PROFILE or CUDA_PROFILE are set
   * and abort if not. 
   * FIXME Should also check whether enabled.
   */
  compute_profile = getenv("COMPUTE_PROFILE");
  if ( compute_profile == NULL )
  {
    compute_profile = getenv("CUDA_PROFILE");
  }
  if ( compute_profile == NULL )
  {
    return;
  }
  /* If MPI is initialized, get the rank and size for filename */
  MPI_Initialized(&ierr);
  if ( ierr )
  {
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &size);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  }

  /* Zero-pad the filename with the rank */
  if (size < 10)
    snprintf(filename, 255, "cuda_profile_%d.log", rank);
  else if (size < 100)
    snprintf(filename, 255, "cuda_profile_%0d.log", rank);
  else if (size < 1000)
    snprintf(filename, 255, "cuda_profile_%00d.log", rank);
  else if (size < 10000)
    snprintf(filename, 255, "cuda_profile_%000d.log", rank);
  else if (size < 100000)
    snprintf(filename, 255, "cuda_profile_%0000d.log", rank);
  else if (size < 1000000)
    snprintf(filename, 255, "cuda_profile_%00000d.log", rank);

  /* 
   * Attempt to open file and set stripe count to 1. Since the file
   * may exist from a previous run, attempt an unlink first. If the
   * unlink succeeds or the file doesn't exist, oceed with setting striping,
   * otherwise fall back to default striping and let the profiler deal with
   * further file errors.
   */
  ierr = unlink(filename);
  if ( (!ierr) || (ierr == ENOENT) )
  {
    ierr = llapi_file_create(filename, 0, -1, 1, 0);
  }
  setenv("COMPUTE_PROFILE_LOG",filename,1);
}
//  Fortran Wrapper
void compute_profile_filename_(){ compute_profile_filename(); }
