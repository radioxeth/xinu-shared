/* in file addargs.c */
extern	status	addargs(pid32, int32, int32[], int32,char *, void *);

/* in file ascdate.c */
extern	status	ascdate(uint32, char *);

/* in file bufinit.c */
extern	status	bufinit(void);

/* in file chprio.c */
extern	pri16	chprio(pid32, pri16);

/* in file clkupdate.S */
extern	uint32	clkcount(void);

/* in file clkhandler.c */
extern	interrupt clkhandler(void);

/* in file clkinit.c */
extern	void	clkinit(void);

/* in file clkint.S */
extern	void	clkint(void);

/* in file close.c */
extern	syscall	close(did32);

/* in file control.c */
extern	syscall	control(did32, int32, int32, int32);

/* in file create.c */
extern	pid32	create(void *, uint32, pri16, char *, uint32, ...);

/* in file ctxsw.S */
extern	void	ctxsw(void *, void *);

/* in file dot2ip.c */
extern	uint32	dot2ip(char *, uint32 *);

/* in file queue.c */
extern	pid32	enqueue(pid32, qid16);

/* in file intutils.S */
extern	intmask	disable(void);

/* in file intutils.S */
extern	void	enable(void);

/* in file evec.c */
extern	int32	initevec(void);
extern	int32	set_evec(uint32, uint32);
extern	void	trap(int32);

/* in file exception.c */
extern  void exception(int32, int32*);

/* in file freebuf.c */
extern	syscall	freebuf(char *);

/* in file freemem.c */
extern	syscall	freemem(char *, uint32);

/* in file getbuf.c */
extern	char	*getbuf(bpid32);

/* in file getc.c */
extern	syscall	getc(did32);

/* in file getitem.c */
extern	pid32	getfirst(qid16);

/* in file dhcp.c */
extern	uint32	getlocalip(void);

/* in file getmem.c */
extern	char	*getmem(uint32);

/* in file getpid.c */
extern	pid32	getpid(void);

/* in file getprio.c */
extern	syscall	getprio(pid32);

/* in file getstk.c */
extern	char	*getstk(uint32);

/* in file gettime.c */
extern	status	gettime(uint32 *);

/* in file getutime.c */
extern	status	getutime(uint32 *);

/* in file halt.S */
extern	void	halt(void);

/* in file init.c */
extern	syscall	init(did32);

/* in file initialize.c */
extern	int32	sizmem(void);

/* in file insert.c */
extern	status	insert(pid32, qid16, int32);

/* in file insertd.c */
extern	status	insertd(pid32, qid16, int32);

/* in file intr.S */
extern	uint16	getirmask(void);

/* in file ioerr.c */
extern	devcall	ioerr(void);

/* in file ionull.c */
extern	devcall	ionull(void);

/* in file kill.c */
extern	syscall	kill(pid32);

/* in file lexan.c */
extern	int32	lexan(char *, int32, char *, int32 *, int32 [], int32 []);

/* in file lpgetc.c */
extern	devcall	lpgetc(struct dentry *);

/* in file lpinit.c */
extern	devcall	lpinit(struct dentry *);

/* in file lpopen.c */
extern	devcall	lpopen(struct dentry *, char *, char *);

/* in file lpputc.c */
extern	devcall	lpputc(struct dentry *, char);

/* in file lpread.c */
extern	devcall	lpread(struct dentry *, char *, int32);

/* in file lpwrite.c */
extern	devcall	lpwrite(struct dentry *, char *, int32);

/* in file mark.c */
extern	void	_mkinit(void);

/* in file memcpy.c */
extern	void	*memcpy(void *, const void *, int32);

/* in file memcpy.c */
extern	int32	*memcmp(void *, const void *, int32);

/* in file memset.c */
extern  void    *memset(void *, const int, int32);

/* in file mkbufpool.c */
extern	bpid32	mkbufpool(int32, int32);

/* in file mount.c */
extern	syscall	mount(char *, char *, did32);
extern	int32	namlen(char *, int32);

/* in file newqueue.c */
extern	qid16	newqueue(void);

/* in file open.c */
extern	syscall	open(did32, char *, char *);

/* in file panic.c */
extern	void	panic(char *);

/* in file pci.c */
extern	int32	pci_init(void);

/* in file ptclear.c */
extern	void	_ptclear(struct ptentry *, uint16, int32);

/* in file ptcount.c */
extern	int32	ptcount(int32);

/* in file ptcreate.c */
extern	syscall	ptcreate(int32);

/* in file ptdelete.c */
extern	syscall	ptdelete(int32, int32);

/* in file ptinit.c */
extern	syscall	ptinit(int32);

/* in file ptrecv.c */
extern	uint32	ptrecv(int32);

/* in file ptreset.c */
extern	syscall	ptreset(int32, int32);

/* in file ptsend.c */
extern	syscall	ptsend(int32, umsg32);

/* in file putc.c */
extern	syscall	putc(did32, char);

/* in file read.c */
extern	syscall	read(did32, char *, uint32);

/* in file ready.c */
extern	status	ready(pid32, bool8);

/* in file receive.c */
extern	umsg32	receive(void);

/* in file recvclr.c */
extern	umsg32	recvclr(void);

/* in file recvtime.c */
extern	umsg32	recvtime(int32);

/* in file resched.c */
extern	void	resched(void);

/* in file intutils.S */
extern	void	restore(intmask);

/* in file resume.c */
extern	pri16	resume(pid32);

/* in file sched_cntl.c */
extern	status	sched_cntl(int32);

/* in file seek.c */
extern	syscall	seek(did32, uint32);

/* in file semcount.c */
extern	syscall	semcount(sid32);

/* in file semcreate.c */
extern	sid32	semcreate(int32);

/* in file semdelete.c */
extern	syscall	semdelete(sid32);

/* in file semreset.c */
extern	syscall	semreset(sid32, int32);

/* in file send.c */
extern	syscall	send(pid32, umsg32);

/* in file shell.c */
extern 	process shell(did32);

/* in file signal.c */
extern	syscall	signal(sid32);

/* in file signaln.c */
extern	syscall	signaln(sid32, int32);

/* in file sleep.c */
extern	syscall	sleepms(uint32);
extern	syscall	sleep(uint32);

/* in file start.S */
extern	int32	inb(int32);
extern	int32	inw(int32);
extern	int32	inl(int32);
extern	int32	outb(int32, int32);
extern	int32	outw(int32, int32);
extern	int32	outl(int32, int32);
extern	int32	outsw(int32, int32, int32);
extern	int32	insw(int32, int32 ,int32);

/* in file suspend.c */
extern	syscall	suspend(pid32);

/* in file ttyControl.c */
extern	devcall	ttyControl(struct dentry *, int32, int32, int32);

/* in file ttyDispatch.c */
extern	interrupt	ttyDispatch(void);

/* in file ttyGetc.c */
extern	devcall	ttyGetc(struct dentry *);

/* in file ttyInter_in.c */
extern	void	ttyInter_in(struct ttycblk *, struct uart_csreg *);

/* in file ttyInter_out.c */
extern	void	ttyInter_out(struct ttycblk *, struct uart_csreg *);

/* in file ttyInterrupt.c */
extern	void	ttyInterrupt(void);

/* in file ttyInit.c */
extern	devcall	ttyInit(struct dentry *);

/* in file ttyKickOut.c */
extern	void	ttyKickOut(struct ttycblk *, struct uart_csreg *);

/* in file ttyPutc.c */
extern	devcall	ttyPutc(struct dentry *, char);

/* in file ttyRead.c */
extern	devcall	ttyRead(struct dentry *, char *, int32);

/* in file ttyWrite.c */
extern	devcall	ttyWrite(struct dentry *, char *, int32);

/* in file unsleep.c */
extern	syscall	unsleep(pid32);

/* in file userret.c */
extern	void	userret(void);

/* in file wait.c */
extern	syscall	wait(sid32);

/* in file wakeup.c */
extern	void	wakeup(void);

/* in file write.c */
extern	syscall	write(did32, char *, uint32);

/* in file xdone.c */
extern	void	xdone(void);

/* in file yield.c */
extern	syscall	yield(void);
