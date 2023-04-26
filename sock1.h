enum {
	TCP_ESTABLISHED = 1,
	TCP_SYN_SENT,
	TCP_SYN_RECV,
	TCP_FIN_WAIT1,
	TCP_FIN_WAIT2,
	TCP_TIME_WAIT,
	TCP_CLOSE,
	TCP_CLOSE_WAIT,
	TCP_LAST_ACK,
	TCP_LISTEN,
	TCP_CLOSING,	/* Now a valid state */

	TCP_MAX_STATES	/* Leave at the end! */
};

#define HLIST_HEAD(name) struct hlist_head name = {  .first = NULL }

typedef struct {
	volatile int counter;
} atomic_t;
struct hlist_node {
	struct hlist_node *next, **pprev;
};
struct hlist_head {
	struct hlist_node *first;
};
#define RAW_IRQ_DISABLED 0
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})
#define hlist_entry(ptr, type, member) container_of(ptr,type,member)
#define prefetch(x) __builtin_prefetch(x)
#define hlist_for_each_entry(tpos, pos, head, member)			 \
	for (pos = (head)->first;					 \
	     pos && ({ prefetch(pos->next); 1;}) &&			 \
		({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = pos->next)
#define sk_for_each(__sk, node, list) \
	hlist_for_each_entry(__sk, node, list, sk_node)


#define typecheck(type,x) \
({	type __dummy; \
	typeof(x) __dummy2; \
	(void)(&__dummy == &__dummy2); \
	1; \
})

# define trace_hardirqs_off()		do { } while (0)




# define trace_hardirqs_on()		do { } while (0)
#define local_irq_restore(flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		if (raw_irqs_disabled_flags(flags)) {	\
			raw_local_irq_restore(flags);	\
			trace_hardirqs_off();		\
		} else {				\
			trace_hardirqs_on();		\
			raw_local_irq_restore(flags);	\
		}					\
	} while (0)
#define raw_local_irq_restore(flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		local_irq_restore(flags);		\
	} while (0)

# define raw_local_irq_save(flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		local_irq_save(flags);			\
	} while (0)
#define local_irq_save(flags)				\
	do {						\
		typecheck(unsigned long, flags);	\
		raw_local_irq_save(flags);		\
		trace_hardirqs_off();			\
	} while (0)





struct socket {
	
	struct sock		*sk;

};

struct sock_common {
	/*
	 * first fields are not copied in sock_copy()
	 */
	union {
		struct hlist_node	skc_node;
	};
	atomic_t		skc_refcnt;
	volatile unsigned char	skc_state;
};

enum sock_flags {
	SOCK_DEAD,
	SOCK_DONE,
	SOCK_URGINLINE,
	SOCK_KEEPOPEN,
	SOCK_LINGER,
	SOCK_DESTROY,
	SOCK_BROADCAST,
	SOCK_TIMESTAMP,
	SOCK_ZAPPED,
	SOCK_USE_WRITE_QUEUE, /* whether to call sk->sk_write_space in sock_wfree */
	SOCK_DBG, /* %SO_DEBUG setting */
	SOCK_RCVTSTAMP, /* %SO_TIMESTAMP setting */
	SOCK_RCVTSTAMPNS, /* %SO_TIMESTAMPNS setting */
	SOCK_LOCALROUTE, /* route locally only, %SO_DONTROUTE setting */
	SOCK_QUEUE_SHRUNK, /* write queue has been shrunk recently */
	SOCK_TIMESTAMPING_TX_HARDWARE,  /* %SOF_TIMESTAMPING_TX_HARDWARE */
	SOCK_TIMESTAMPING_TX_SOFTWARE,  /* %SOF_TIMESTAMPING_TX_SOFTWARE */
	SOCK_TIMESTAMPING_RX_HARDWARE,  /* %SOF_TIMESTAMPING_RX_HARDWARE */
	SOCK_TIMESTAMPING_RX_SOFTWARE,  /* %SOF_TIMESTAMPING_RX_SOFTWARE */
	SOCK_TIMESTAMPING_SOFTWARE,     /* %SOF_TIMESTAMPING_SOFTWARE */
	SOCK_TIMESTAMPING_RAW_HARDWARE, /* %SOF_TIMESTAMPING_RAW_HARDWARE */
	SOCK_TIMESTAMPING_SYS_HARDWARE, /* %SOF_TIMESTAMPING_SYS_HARDWARE */
};

struct sock {
	/*
	 * Now struct inet_timewait_sock also uses sock_common, so please just
	 * don't add nothing before this first member (__sk_common) --acme
	 */
struct sock_common	__sk_common;
#define sk_state		__sk_common.skc_state
#define sk_refcnt		__sk_common.skc_refcnt
#define sk_node			__sk_common.skc_node
};

typedef unsigned short __u16;
#define ATPORT_RESERVED	128
#define ATPORT_LAST	254		/* 254 is only legal on localtalk */ 
#define	EBUSY		16	/* Device or resource busy */
#define	IFF_LOOPBACK	0x8		/* is a loopback net		*/
#define	IFF_POINTOPOINT	0x10		/* interface is has p-p link	*/
#define	EADDRNOTAVAIL	99	/* Cannot assign requested address */
#define ATADDR_ANYNET	(__u16)0
#define	ENOBUFS		105	/* No buffer space available */
#define	ENOTCONN	107	/* Transport endpoint is not connected */
#define AF_APPLETALK	5	/* AppleTalk DDP 		*/


typedef unsigned short	   u_int16_t;
#define __be16	u_int16_t
typedef unsigned char __u8;
typedef unsigned short	sa_family_t;

struct atalk_addr {
	__be16	s_net;
	__u8	s_node;
};
struct sockaddr_at {
	sa_family_t	  sat_family;
	__u8		  sat_port;
	struct atalk_addr sat_addr;
	char		  sat_zero[8];
};

struct atalk_sock {
	/* struct sock has to be the first member of atalk_sock */
	struct sock	sk;
	__be16		dest_net;
	__be16		src_net;
	unsigned char	dest_node;
	unsigned char	src_node;
	unsigned char	dest_port;
	unsigned char	src_port;
};

struct net_device
{
unsigned int		flags;	/* interface flags (a la BSD)	*/
};

struct atalk_iface {
	struct net_device	*dev;
	struct atalk_addr	address;
	int			status;
#define ATIF_PROBE	1		/* Probing for an address */
#define ATIF_PROBE_FAIL	2		/* Probe collided */
	struct atalk_iface	*next;
};