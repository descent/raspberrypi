
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

// 2  outer corner
// 4
// 6
// 8  TX out
// 10 RX in

extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern void PUT8 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern unsigned int GETPC ( void );
extern void dummy ( unsigned int );
extern unsigned int BRANCHTO ( unsigned int );

extern void uart_init ( void );
extern unsigned int uart_lcr ( void );
extern void uart_flush ( void );
extern void uart_send ( unsigned int );
extern unsigned int uart_recv ( void );
extern unsigned int uart_check ( void );
extern void hexstring ( unsigned int );
extern void hexstrings ( unsigned int );
extern void timer_init ( void );
extern unsigned int timer_tick ( void );

extern void timer_init ( void );
extern unsigned int timer_tick ( void );

//------------------------------------------------------------------------
int notmain ( void )
{
  // form : arm_os/leeos/chapter3/part2/cortex_a_mmu.c
  void init_sys_mmu(void);
  void start_mmu(void);

  uart_init();

  //hexstring(0x12345678);

  // uart_send

  while(1)
  {
    if (*(volatile unsigned int *)(0x3F000000 + 0x00215054) & 0x20) break;
  }
  *(volatile unsigned int *)(0x3F000000 + 0x00215040) = 0x31;

  while(1)
  {
    if (*(volatile unsigned int *)(0x3F000000 + 0x00215054) & 0x20) break;
  }
  *(volatile unsigned int *)(0x3F000000 + 0x00215040) = 0x32;

  while(1)
  {
    //if(GET32(AUX_MU_LSR_REG)&0x20) break;
    if (*(volatile unsigned int *)(0x3F000000 + 0x00215054) & 0x20) break;
  }
  *(volatile unsigned int *)(0x3F000000 + 0x00215040) = 0x33;

  uart_send(0x0D);
  uart_send(0x0A);

  init_sys_mmu();
  start_mmu();

  while(1)
  {
    //if(GET32(AUX_MU_LSR_REG)&0x20) break;
    if (*(volatile unsigned int *)(0xc8000000 + 0x00215054) & 0x20) break;
  }
  *(volatile unsigned int *)(0xc8000000 + 0x00215040) = 'A';

  while(1)
  {
    //if(GET32(AUX_MU_LSR_REG)&0x20) break;
    if (*(volatile unsigned int *)(0xc8000000 + 0x00215054) & 0x20) break;
  }
  *(volatile unsigned int *)(0xc8000000 + 0x00215040) = 'B';

  while(1)
  {
    //if(GET32(AUX_MU_LSR_REG)&0x20) break;
    if (*(volatile unsigned int *)(0xc8000000 + 0x00215054) & 0x20) break;
  }
  *(volatile unsigned int *)(0xc8000000 + 0x00215040) = 'C';

  while(1);

  return(0);
}
