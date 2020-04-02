target remote localhost:1234
symbol-file kernel.elf
break global_isr_manager
continue
quit