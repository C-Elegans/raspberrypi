inline void PUT32(unsigned int address,unsigned int data){
	asm volatile("str %[data],[%[address]]":: [data] "r" (data), [address] "r" (address));
}
inline void PUT16(unsigned int address,unsigned int data){
	asm volatile("strh %[data],[%[address]]":: [data] "r" (data), [address] "r" (address));
}
inline void PUT8(unsigned int address,unsigned int data){
	asm volatile("strb %[data],[%[address]]":: [data] "r" (data), [address] "r" (address));
}
inline unsigned int get32(unsigned int register address){
	unsigned int register data;
	asm volatile("ldr %[data],[%[address]]":[data] "=r" (data):[address] "r" (address): "r0");
	return data;
}

