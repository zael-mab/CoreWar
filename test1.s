.name 		"zork  x"
.comment 	"Zork zork zork"	


x1:
l2:		sti r1, \%:live,\%1
		and	r1, \%0,r1

live:
	live \%1
	zjmp \%:live

# Executable co,pilation:
#
# 0x0b,0x68,0x01,0x00,0x0f,0x00,0x01
# 0x06,0x64,0x01,0x00,0x00,0x00,0x00,0x01
# 0x01,0x00,0x00,0x00,0x01
# 0x09,0xff,0xfb
