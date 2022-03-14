#define RATIO 10

SEC("action")
int bpf_main(struct __sk_buff *skb)
{
    void *data = (void *)(uintptr_t)skb->data;
    void *data_end = (void *)(uintptr_t)skb->data_end;
    struct ethhdr *eth = data;
    struct iphdr *iph = (struct iphdr *)(eth + 1);
    struct tcphdr *tcphdr = (struct tcphdr *)(iph + 1);

    /* sanity check needed by the eBPF verifier */
    if ((void *)(tcphdr + 1) > data_end)
        return TC_ACT_OK;

    /* skip non-TCP packets */
    if (eth->h_proto != __constant_htons(ETH_P_IP) || iph->protocol != IPPROTO_TCP)
        return TC_ACT_OK;

    /* incompatible flags, or PSH already set */
    if (tcphdr->syn || tcphdr->fin || tcphdr->rst || tcphdr->psh)
        return TC_ACT_OK;

    if (bpf_get_prandom_u32() % RATIO == 0)
        tcphdr->psh = 1;

    return TC_ACT_OK;
}

char _license[] SEC("license") = "GPL";


