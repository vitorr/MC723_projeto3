/******************************************************
 * This is the main file for the mips1 ArchC model    *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 
const char *project_name="mips1";
const char *project_file="mips1.ac";
const char *archc_version="2.0beta1";
const char *archc_options="-abi -dy ";

#include  <systemc.h>
#include  "mips1.H"
#include  "ac_tlm_mem.h"
#include  "router.h"
#include  "lock.h"
#include  "psin.h"
#include  "pcos.h"
#include  <string.h>

using user::ac_tlm_mem;
using user::router;
using user::lock;
using user::psin;
using user::pcos;

int sc_main(int ac, char *av[])
{
  char * av_tmp[100];
  int ac_tmp;
  int i;

  //!  ISA simulator
  mips1 mips1_proc1("proc1");
  mips1 mips1_proc2("proc2");
  mips1 mips1_proc3("proc3");
  mips1 mips1_proc4("proc4");
  mips1 mips1_proc5("proc5");
  mips1 mips1_proc6("proc6");
  mips1 mips1_proc7("proc7");
  mips1 mips1_proc8("proc8");
  ac_tlm_mem mem("mem");
  router rtr("rtr");
  lock l("l");
  psin s("s");
  pcos c("c");

#ifdef AC_DEBUG
  ac_trace("mips1_proc1.trace");
#endif 

  mips1_proc1.DM_port(rtr.target_export);
  mips1_proc2.DM_port(rtr.target_export);
  mips1_proc3.DM_port(rtr.target_export);
  mips1_proc4.DM_port(rtr.target_export);
  mips1_proc5.DM_port(rtr.target_export);
  mips1_proc6.DM_port(rtr.target_export);
  mips1_proc7.DM_port(rtr.target_export);
  mips1_proc8.DM_port(rtr.target_export);
  rtr.DM_port(mem.target_export);
  rtr.LOCK_port(l.target_export);
  rtr.PSIN_port(s.target_export);
  rtr.PCOS_port(c.target_export);

  //Initialize processors.
  for (i = 0; i < ac; i++) {
    av_tmp[i] = (char *) malloc (strlen (av[i]));
    strcpy (av_tmp[i], av[i]);
  }
  ac_tmp = ac;
  mips1_proc1.init(ac_tmp, av_tmp);

  for (i = 0; i < ac; i++) {
    av_tmp[i] = (char *) malloc (strlen (av[i]));
    strcpy (av_tmp[i], av[i]);
  }
  ac_tmp = ac;
  mips1_proc2.init(ac_tmp, av_tmp);

  for (i = 0; i < ac; i++) {
    av_tmp[i] = (char *) malloc (strlen (av[i]));
    strcpy (av_tmp[i], av[i]);
  }
  ac_tmp = ac;
  mips1_proc3.init(ac_tmp, av_tmp);

  for (i = 0; i < ac; i++) {
    av_tmp[i] = (char *) malloc (strlen (av[i]));
    strcpy (av_tmp[i], av[i]);
  }
  ac_tmp = ac;
  mips1_proc4.init(ac_tmp, av_tmp);

  for (i = 0; i < ac; i++) {
    av_tmp[i] = (char *) malloc (strlen (av[i]));
    strcpy (av_tmp[i], av[i]);
  }
  ac_tmp = ac;
  mips1_proc5.init(ac_tmp, av_tmp);

  for (i = 0; i < ac; i++) {
    av_tmp[i] = (char *) malloc (strlen (av[i]));
    strcpy (av_tmp[i], av[i]);
  }
  ac_tmp = ac;
  mips1_proc6.init(ac_tmp, av_tmp);

  for (i = 0; i < ac; i++) {
    av_tmp[i] = (char *) malloc (strlen (av[i]));
    strcpy (av_tmp[i], av[i]);
  }
  ac_tmp = ac;
  mips1_proc7.init(ac_tmp, av_tmp);

  for (i = 0; i < ac; i++) {
    av_tmp[i] = (char *) malloc (strlen (av[i]));
    strcpy (av_tmp[i], av[i]);
  }
  ac_tmp = ac;
  mips1_proc8.init(ac_tmp, av_tmp);


  cerr << endl;

  sc_start();

  mips1_proc1.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  mips1_proc1.ac_sim_stats.time = sc_simulation_time();
  mips1_proc1.ac_sim_stats.print();
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  return mips1_proc1.ac_exit_status;
}
