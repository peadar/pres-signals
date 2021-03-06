/* Called with IRQs disabled. */
__visible inline void prepare_exit_to_usermode(struct pt_regs *regs)
{
	struct thread_info *ti = current_thread_info();
	u32 cached_flags;

	addr_limit_user_check();

	lockdep_assert_irqs_disabled();
	lockdep_sys_exit();

	cached_flags = READ_ONCE(ti->flags);

	if (unlikely(cached_flags & EXIT_TO_USERMODE_LOOP_FLAGS))
		exit_to_usermode_loop(regs, cached_flags);

	/* Reload ti->flags; we may have rescheduled above. */
	cached_flags = READ_ONCE(ti->flags);

	if (unlikely(cached_flags & _TIF_IO_BITMAP))
		tss_update_io_bitmap();

	fpregs_assert_state_consistent();
	if (unlikely(cached_flags & _TIF_NEED_FPU_LOAD))
		switch_fpu_return();

#ifdef CONFIG_COMPAT
	/*
	 * Compat syscalls set TS_COMPAT.  Make sure we clear it before
	 * returning to user mode.  We need to clear it *after* signal
	 * handling, because syscall restart has a fixup for compat
	 * syscalls.  The fixup is exercised by the ptrace_syscall_32
	 * selftest.
	 *
	 * We also need to clear TS_REGS_POKED_I386: the 32-bit tracer
	 * special case only applies after poking regs and before the
	 * very next return to user mode.
	 */
	ti->status &= ~(TS_COMPAT|TS_I386_REGS_POKED);
#endif

	user_enter_irqoff();

	mds_user_clear_cpu_buffers();
}


