# Lab10
# By: Jackie Herrick
# Date: 11/07/26 
  # a. These programs go through the basic system calls on a Portable Operating System Interface (POSIX) operating system. 
   # Signal disposition - determines what process/action is being done when a signal is being delivered. For instants, it can      # tell you whether the signal is ignored, handled by default, caught with a custom handler, or causes termination/core        # dump.
   # A signal handler is a function that the operating system calls when a specific signal (such as SIGINT, SIGSEGV, or       
   SIGTERM) occurs, allowing a program to override the default behavior and define custom responses.
  # b. How to build the program
      # 	Term (Terminate): the process is terminated immediately (examples: e.g., SIGKILL, SIGSEGV).
      # 	Ign (Ignore): It discards signal at delivery time, but  process continues as if the signal never occurred.
      # 	Core (Core Dump): The process is terminated, and the kernel writes a core dump file containing the process’s 
          # memory state
      # 	Stop (Stop): The process is suspended (stopped) and placed in a stopped state.
      # 	Cont (Continue): Resumes execution on currently stopped process.
      #   SIGINT: Interrupt Signal (Ctr+C) 
      #   SIGTERM: Termination Signal. 
          # int kill(pid_t pid, int sig); 
          # pid = Process ID of the target process
          # sig = Signal to send
      #   SIGUSR1: User-Defined Signal 1. Its behavior is determined entirely by the receiving program
      #   SIGKILL: Signal Kill. Immediate Terminates all the current processes.
          # kill -9 <pid>
      #   SIGSTOP: Signal Stop. Pause/suspend execution.
          # -STOP <pid>
  # c. How to run the program – available command-line options
          
          # gcc SIGTERM.c
          # ./a.out

          # * gcc signal_segfault.c
          # ./a.out
  
          # gcc send_signal.c -o send_signal PID_Number
          # ./send_signal
          # gcc rev_signal.c -o rev_signal
          #./rev_signal 

          # gcc signal_sigaction.c
          # ./a.out
          # kill -SIGUSR1 PID_Number
          
         # gcc tennis2.c -o tennis2
         # ./tennis2
         # make clean

         # gcc tennis1.c -o tennis1
         # ./tennis1 PID_Number
         # make clean
