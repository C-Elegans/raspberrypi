inline void PUT32(unsigned int address,unsigned int data){
	asm volatile("str %[data],[%[address]]":: [data] "r" (data), [address] "r" (address));
}
inline void PUT16(unsigned int address,unsigned int data){
	asm volatile("strh %[data],[%[address]]":: [data] "r" (data), [address] "r" (address));
}
inline void PUT8(unsigned int address,unsigned int data){
	asm volatile("strb %[data],[%[address]]":: [data] "r" (data), [address] "r" (address));
}

