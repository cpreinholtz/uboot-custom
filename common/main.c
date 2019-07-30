/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* #define	DEBUG	*/

#include <common.h>
#include <autoboot.h>
#include <cli.h>
#include <console.h>
#include <version.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * Board-specific Platform code can reimplement show_boot_progress () if needed
 */
__weak void show_boot_progress(int val) {}

static void run_preboot_environment_command(void)
{
#ifdef CONFIG_PREBOOT
	char *p;

	p = getenv("preboot");
	if (p != NULL) {
# ifdef CONFIG_AUTOBOOT_KEYED
		int prev = disable_ctrlc(1);	/* disable Control C checking */
# endif

		run_command_list(p, -1, 0);

# ifdef CONFIG_AUTOBOOT_KEYED
		disable_ctrlc(prev);	/* restore Control C checking */
# endif
	}
#endif /* CONFIG_PREBOOT */
}







/* We come here after U-Boot is initialised and ready to process commands */
void main_loop(void)
{
	
	const char *s;

	bootstage_mark_name(BOOTSTAGE_ID_MAIN_LOOP, "main_loop");

#ifdef CONFIG_VERSION_VARIABLE
	setenv("ver", version_string);  /* set version variable */
#endif /* CONFIG_VERSION_VARIABLE */

	cli_init();

/*********************************************************************************************************************************/
	setenv("homeipconfig","echo beginning home ip config && "\
			"setenv ipaddr 192.168.1.20 && "\
			"setenv serverip 192.168.1.191 \0");	
	setenv("ibdsipconfig","echo beginning epaddle ip config && "\
			"setenv ipaddr 192.168.10.101 && "\
			"setenv serverip 192.168.10.10 \0");
	setenv("serveribdsipconfig","echo beginning server ip config && "\
			"setenv serverip 192.168.10.10 \0");
	setenv("nggnipconfig","echo beginning nggn ip config && "\
			"setenv ipaddr 159.4.2.20 && "\
			"setenv serverip 159.4.7.254 \0");


/*boot 10.2.1*/  /* nggn (server)+ dhcp  +  PS+PL */
	/*setenv("ncibds","setenv ncip 159.4.7.254 ; setenv stdout nc; setenv stdin nc \0");
	setenv("preboot","run nggnipconfig; dhcp 0x100000 SOC1.bit; ping 159.4.7.254 && run ncibds \0");*/
	
/*boot 10.2.1*/  /* ibds (server)  PS+PL */
	/*setenv("ncibds","setenv ncip 192.168.10.10 ; setenv stdout nc; setenv stdin nc \0");
	setenv("preboot","run ibdsipconfig; ping 192.168.10.10 && run ncibds \0");*/




/*********************************************************************************************************************************/

	run_preboot_environment_command();

#if defined(CONFIG_UPDATE_TFTP)
	update_tftp(0UL, NULL, NULL);
#endif /* CONFIG_UPDATE_TFTP */

	

/*********************************************************************************************************************************/
	












/*boot 10.2.2*/  /* nggn (server)+ dhcp + netconsole (define and active) +  PS+PL */
/*setenv("stdin","nc \0");
setenv("stdout","nc \0");
setenv("stderr","nc \0");
setenv("ncip","159.4.2.153 \0");
setenv("bootdelay","10\0");
setenv("preboot","'run servernggnipconfig && dhcp ${ddraddr} SOChw.bit && ping $159.4.2.153 && version ;' \0");

	setenv("sdboot","setenv bootcmd run trenznggnboot &&"\
			"setenv servernggnipconfig 'setenv serverip 159.4.2.153  && setenv ddraddr 0x01000000 &&  setenv ddrfaddr 0x01000070'  &&"\
			"setenv trenznggnboot 'run servernggnipconfig && dhcp ${ddraddr} SOChw.bit && run trenz2boot&& version'&&"\
			"setenv trenz2boot ' echo trenz n boot begin && fpga load 0 ${ddrfaddr} ${filesize} && run trenzPSboot'  && "\
			"setenv trenzPSboot 'echo tftp trenz PS SOCsw.elf && tftpboot ${ddraddr}  SOCsw.elf &&  bootelf ${ddraddr} '&& " \
			"setenv stdin nc && setenv stdout nc&& setenv stderr nc && setenv ncip 159.4.2.153 && " \
			"saveenv && " \
			"run trenznggnboot \0" );

/*boot 10.2.3*/  /* nggn (server)+ dhcp + netconsole (define and active) +  PS+PL */
/*setenv("stdin","nc \0");
setenv("stdout","nc \0");
setenv("stderr","nc \0");
setenv("ncip","159.4.2.153 \0");
setenv("bootdelay","10\0");
setenv("preboot","'setenv serverip 159.4.2.153  && dhcp ${ddraddr} SOChw.bit && ping $159.4.2.153 && version ;' \0");

	setenv("sdboot","setenv bootcmd run trenznggnboot &&"\
			"setenv servernggnipconfig 'setenv serverip 159.4.2.153  && setenv ddraddr 0x01000000 &&  setenv ddrfaddr 0x01000070'  &&"\
			"setenv trenznggnboot 'run servernggnipconfig && dhcp ${ddraddr} SOChw.bit && run trenz2boot&& version'&&"\
			"setenv trenz2boot ' echo trenz n boot begin && fpga load 0 ${ddrfaddr} ${filesize} && run trenzPSboot'  && "\
			"setenv trenzPSboot 'echo tftp trenz PS SOCsw.elf && tftpboot ${ddraddr}  SOCsw.elf &&  bootelf ${ddraddr} '&& " \
			"setenv stdin nc && setenv stdout nc&& setenv stderr nc && setenv ncip 159.4.2.153 && " \
			"saveenv && " \
			"run trenznggnboot \0" );


/*boot 10.2.4*/  /* nggn (server)+ dhcp + netconsole (define and active) +  PS+PL */
/*setenv("stdin","nc \0");
setenv("stdout","nc \0");
setenv("stderr","nc \0");
setenv("ncip","159.4.2.153:9000 \0");
setenv("bootdelay","10\0");
setenv("preboot","'setenv serverip 159.4.2.153  && dhcp ${ddraddr} SOChw.bit && ping $159.4.2.153 && version ;' \0");

	setenv("sdboot","setenv bootcmd run trenznggnboot &&"\
			"setenv servernggnipconfig 'setenv serverip 159.4.2.153  && setenv ddraddr 0x01000000 &&  setenv ddrfaddr 0x01000070'  &&"\
			"setenv trenznggnboot 'run servernggnipconfig && dhcp ${ddraddr} SOChw.bit && run trenz2boot&& version'&&"\
			"setenv trenz2boot ' echo trenz n boot begin && fpga load 0 ${ddrfaddr} ${filesize} && run trenzPSboot'  && "\
			"setenv trenzPSboot 'echo tftp trenz PS SOCsw.elf && tftpboot ${ddraddr}  SOCsw.elf &&  bootelf ${ddraddr} '&& " \
			"setenv stdin nc && setenv stdout nc&& setenv stderr nc && setenv ncip 159.4.2.153:9000 && " \
			"saveenv && " \
			"run trenznggnboot \0" );


/*boot 10.2.5*/  /* nggn (server)+ dhcp + netconsole (define and active) +  PS+PL */
/*
setenv("stdin","nc \0");
setenv("stdout","nc \0");
setenv("stderr","nc \0");
setenv("ncip","159.4.2.153:9000 \0");
setenv("bootdelay","10\0");
setenv("preboot","'setenv serverip 159.4.2.153  && dhcp ${ddraddr} high1.bit && ping $159.4.2.153 && version ;' \0");

	setenv("sdboot","setenv bootcmd run znggnboot &&"\
			"setenv servernggnipconfig 'setenv serverip 159.4.2.153  && setenv ddraddr 0x01000000 &&  setenv ddrfaddr 0x01000070'  &&"\
			"setenv zednggnboot 'run servernggnipconfig && dhcp ${ddraddr} high1.bit && run zed2boot&& version'&&"\
			"setenv zed2boot ' echo zed n boot begin && fpga load 0 ${ddrfaddr} ${filesize} && run zedPSboot'  && "\
			"setenv zedPSboot 'echo tftp zed PS baremetal.elf && tftpboot ${ddraddr}  baremetal.elf &&  bootelf ${ddraddr} '&& " \
			"setenv stdin nc && setenv stdout nc && setenv stderr nc && setenv ncip 159.4.2.153:9000 && " \
			"saveenv && " \
			"run zednggnboot \0" );*/



/*	printf("clark's mod for zed\n\r");

	setenv("sdboot","echo beginning custom baremetal boot && "\
			"setenv ipaddr 192.168.1.20 && "\
			"setenv serverip 192.168.1.191 && "\
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 5980028 && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 ");*/


/*this one works but I want to try to make it better*/

	/*printf("clark's mod for trenz\n\r"); 

	setenv("sdboot","echo beginning custom baremetal ps+pl boot for nggn network and trenz&& "\
			"run ibdsipconfig && "\
			"ping 192.168.10.1 ; "\
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 ${filesize} && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");*/

/*boot1*/  /* dhcp + nggn (server) + PL+ PS */

	/*setenv("sdboot","echo beginning custom baremetal ps+pl boot for nggn network and trenz&& "\
			"dhcp && "\
			"run serveripconfig && "\
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 ${filesize} && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");

/*boot1.5*/  /* dhcp + nggn (server) +  PS */

	/*setenv("sdboot","echo beginning custom && "\
			"dhcp && "\
			"run serveripconfig && "\
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");

/*boot2*/   /* dhcp + ping+ nggn (server) + PL+ PS */   /*not compiled yet*/
	/*setenv("sdboot","echo beginning custom baremetal ps+pl boot for nggn network and trenz&& "\
			"dhcp && "\
			"ping 159.4.2.153; "\
			"run serveripconfig && "\
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 ${filesize} && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");

/*boot3*/   /* dhcp + ping+ nggn (server) + PL+ PS */  /*not compiled yet*/
	/*setenv("sdboot","echo beginning custom baremetal ps+pl boot for nggn network and trenz&& "\
			"dhcp && "\
			"run serveripconfig && "\
			"saveenv"\
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 ${filesize} && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");


/*boot4*/    /* ibds+ saveenv (will prob fail once) + PL+ PS */
	/*setenv("sdboot","echo beginning custom baremetal ps+pl boot for nggn network and trenz&& "\
			"run ibdsipconfig && "\
			"saveenv &&"\
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 ${filesize} && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");

/*boot4.5*/    /* ibds+ saveenv (will prob fail once) + PL+ PS */
	/*setenv("sdboot","echo beginning custom baremetal ps+pl boot for nggn network and trenz&& "\
			"run ibdsipconfig && "\
			"saveenv&&"\
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");

/*boot5*/    /* ibds+ saveenv (will prob fail once)+ sleep + PL+ PS */
	/*setenv("sdboot","echo beginning custom baremetal ps+pl boot for nggn network and trenz&& "\
			"run ibdsipconfig && "\
			"sleep 5 && "\
			"saveenv && "\ 			
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 ${filesize} && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");








/*boot6*/
	/*setenv("sdboot","echo beginning custom baremetal ps+pl boot for nggn network and trenz&& "\
			"run ibdsipconfig && "\
			"ping 192.168.10.10; "\
			"saveenv"\
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 ${filesize} && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 \0");





/* working copy 8/11/16 is stored below for safe keeping -clark  */
	
/*	setenv("sdboot","echo beginning custom baremetal boot && "\
			"setenv ipaddr 192.168.1.20 && "\
			"setenv serverip 192.168.1.191 && "\
			"tftpboot 0x100000 SOChw.bit && " \
			"fpga load 0 0x100070 5980028 && " \
			"tftpboot 0x01000000 SOCsw.elf && " \
			"bootelf 0x01000000 ");*/
		
	
/*****************************************************************************************************************************************/


	s = bootdelay_process();
	if (cli_process_fdt(&s)){
		printf("here 456\n\r");
		printf("s: %s\n\r",s);
		cli_secure_boot_cmd(s);
	}

	printf("here 5678\n\r");
	printf("s: %s\n\r",s);

	
	autoboot_command(s);
	
	cli_loop();
	panic("No CLI available");
}
