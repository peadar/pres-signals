/*
 * OK, we're invoking a handler
 */
static void
handle_signal(struct ksignal *ksig, struct pt_regs *regs)
{
	sigset_t *oldset = sigmask_to_save();
	int failed;

	/* Set up the stack frame */
	failed = setup_rt_frame(ksig, oldset, regs);

	signal_setup_done(failed, ksig, 0);
}


