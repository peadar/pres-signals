void do_signal(struct pt_regs *regs)
{
	struct ksignal ksig;
	int restart_scall;

	restart_scall = in_syscall(regs) && syscall_restartable(regs);

	if (get_signal(&ksig)) {
		if (restart_scall) {
			arc_restart_syscall(&ksig.ka, regs);
			syscall_wont_restart(regs);	/* No more restarts */
		}
		handle_signal(&ksig, regs);
		return;
	}

	if (restart_scall) {
		/* No handler for syscall: restart it */
		if (regs->r0 == -ERESTARTNOHAND ||
		    regs->r0 == -ERESTARTSYS || regs->r0 == -ERESTARTNOINTR) {
			regs->r0 = regs->orig_r0;
			regs->ret -= is_isa_arcv2() ? 2 : 4;
		} else if (regs->r0 == -ERESTART_RESTARTBLOCK) {
			regs->r8 = __NR_restart_syscall;
			regs->ret -= is_isa_arcv2() ? 2 : 4;
		}
		syscall_wont_restart(regs);	/* No more restarts */
	}

	/* If there's no signal to deliver, restore the saved sigmask back */
	restore_saved_sigmask();
}
