SEC("prog")
int xdp_main(struct xdp_md *ctx)
{
    void *data_end = (void *)(uintptr_t)ctx->data_end;
    void *data = (void *)(uintptr_t)ctx->data;

    struct ethhdr *eth = data;
    struct iphdr *iph = (struct iphdr *)(eth + 1);
    struct icmphdr *icmph = (struct icmphdr *)(iph + 1);

    /* sanity check needed by the eBPF verifier */
    if (icmph + 1 > data_end)
        return XDP_PASS;

    /* matched a pong packet */
    if (eth->h_proto != ntohs(ETH_P_IP) ||
        iph->protocol != IPPROTO_ICMP ||
        icmph->type != ICMP_ECHOREPLY)
        return XDP_PASS;

    if (iph->ttl) {
        /* save the old TTL to recalculate the checksum */
        uint16_t *ttlproto = (uint16_t *)&iph->ttl;
        uint16_t old_ttlproto = *ttlproto;

        /* set the TTL to a pseudorandom number 1 < x < TTL */
        iph->ttl = bpf_get_prandom_u32() % iph->ttl + 1;

        /* recalculate the checksum; otherwise, the IP stack will drop it */
        csum_replace2(&iph->check, old_ttlproto, *ttlproto);
    }

    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";



