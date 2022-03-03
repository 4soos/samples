from bcc import BPF

prog = """
	int kprobe__sys_clone(void *ctx) {
		bpf_trace_printk("Hello, World!\\n");
		return 0;
	}
"""


b = BPF(text=prog, debug=0x04)
b.trace_print()

# 如果运行报错，可能是缺少头文件，一般安装 kernel-devel 包即可。